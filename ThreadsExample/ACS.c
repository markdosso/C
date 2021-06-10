#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

struct node {
	int user_id;
	struct node* next;
};

struct customer_info {
	int user_id;
	int class_type;
	int service_time;
	int arrival_time;
};

struct timeval curr_waiting;
struct timeval init_time;
double init_time_double;
double init_time_double_sec;
int queue_length[2];

struct node* bus;
struct node* econ;

int queue_status[2];
int winner_selected[2];

double waiting_time_start[3];
double waiting_time_end[3];

pthread_mutex_t business;
pthread_mutex_t economy;

pthread_mutex_t mutex_clerk1;
pthread_mutex_t mutex_clerk2;
pthread_mutex_t mutex_clerk3;
pthread_mutex_t mutex_clerk4;
pthread_mutex_t mutex_time;

pthread_cond_t clerk1;
pthread_cond_t clerk2;
pthread_cond_t clerk3;
pthread_cond_t clerk4;

pthread_cond_t condBus;
pthread_cond_t condEcon;

void * customer_entry(void * cus_info) {
	// Initalize nessisary variables
	double start_time;
	double end_time;	
	struct customer_info * p_myInfo = (struct customer_info *) cus_info;
	
	// Simulate the arrival time
	usleep(p_myInfo->arrival_time * 100000);
	
	fprintf(stdout, "A customer arrives: customer ID %2d. \n", p_myInfo->user_id);
	
	// Initalize the information to add to the queue 
	struct node* add = NULL;
	add = (struct node*)malloc(sizeof(struct node));
	add->next = NULL;
	add->user_id = p_myInfo->user_id;
	
	// Lock the mutex for the queue that you will add the customer to 
	if(p_myInfo->class_type == 0) {
		pthread_mutex_lock(&economy);
		if (econ == NULL) {	
			queue_length[0]++;
			econ = add;
		} else {
			struct node* curr = econ;
			while(curr->next != NULL) {
				curr = curr->next;
			}

			curr->next = add;
			queue_length[0]++;
		}
	} else {
		pthread_mutex_lock(&business);
		if (bus == NULL) {
			queue_length[1]++;
			bus = add;
		} else {
			struct node* curr = bus;
			while(curr->next != NULL) {
				curr = curr->next;
			}
			curr->next = add;
			queue_length[1]++;
		}
	}
		
	// Lock Mutex time to add the time entered queue
	pthread_mutex_lock(&mutex_time);
	gettimeofday(&curr_waiting, NULL);
	start_time = ((double)curr_waiting.tv_usec - init_time_double) / 1000000 + (double)curr_waiting.tv_sec - init_time_double_sec;
	waiting_time_start[2] += start_time;
	waiting_time_start[p_myInfo->class_type] += start_time;;
	pthread_mutex_unlock(&mutex_time);
	
	fprintf(stdout, "Customer %2d enters Queue ID: %2d and has a length %2d\n", p_myInfo->user_id, p_myInfo->class_type, queue_length[p_myInfo->class_type]);

	// Check to see if Clerk is ready for the customer and remove them from the queue
	while (true) {
		if(p_myInfo->class_type == 0) {
			pthread_cond_wait(&condEcon, &economy);
			if(econ->user_id == p_myInfo->user_id && !winner_selected[0]) {
				econ = econ->next;
				queue_length[0]--;
				winner_selected[0] = 1;
				break;
			}
		} else {
			pthread_cond_wait(&condBus, &business);
			if (bus->user_id == p_myInfo->user_id && !winner_selected[1]) {
				bus = bus->next;
				queue_length[1]--;
				winner_selected[1] = 1;
				break;
			}
		}
	}

	// Allow other to use the queues
	if(p_myInfo->class_type == 0) {
		pthread_mutex_unlock(&economy);
	} else {
		pthread_mutex_unlock(&business);
	}
	usleep(10);

	// get the clerk who woke you and allow other use to use the queue
	int clerk_woke = queue_status[p_myInfo->class_type];
	queue_status[p_myInfo->class_type] = 0;

	// Lock time mutex for the end of waiting period
	pthread_mutex_lock(&mutex_time);
	gettimeofday(&curr_waiting, NULL);
	end_time = ((double)curr_waiting.tv_usec - init_time_double) / 1000000 + ((double)curr_waiting.tv_sec - init_time_double_sec);
	waiting_time_end[2] += end_time;
	waiting_time_end[p_myInfo->class_type] += end_time;
	pthread_mutex_unlock(&mutex_time);


	fprintf(stdout, "Clerk %d starts serving a customer: %1d  at time %2f\n", clerk_woke, p_myInfo->user_id, end_time);
	
	// Simulate service time
	usleep(p_myInfo->service_time * 100000);

	pthread_mutex_lock(&mutex_time);
	gettimeofday(&curr_waiting, NULL);
	fprintf(stdout, "Clerk %d finished serving customer %1d at time %2f\n", clerk_woke, p_myInfo->user_id, ((double)curr_waiting.tv_usec - init_time_double) / 1000000 + (double)curr_waiting.tv_sec - init_time_double_sec);
	pthread_mutex_unlock(&mutex_time);
	
	// Signal the clerk that woke you so they can wake another customer	
	if(clerk_woke == 1) {
		pthread_cond_signal(&clerk1);
	} else if(clerk_woke == 2) {
		pthread_cond_signal(&clerk2);
	} else if(clerk_woke == 3) {
		pthread_cond_signal(&clerk3);
	} else  {
		pthread_cond_signal(&clerk4);
	}

	pthread_exit(NULL);
	return NULL;
}

void * clerk_entry(void * clerkNum) {
	int selected_queue;
	int clerk = *(int *) clerkNum;	
	
	while(true) {
		while(true) {
			// check if business queue has people waiting
			if(queue_length[1] > 0 && queue_status[1] == 0) {
				queue_status[1] = clerk;
				selected_queue = 1;
				pthread_mutex_lock(&business);
				break;
			// check if economy queue has people waiting
			} else if(queue_length[0] > 0 && queue_status[0] == 0) {
				queue_status[0] = clerk;
				selected_queue = 0;
				pthread_mutex_lock(&economy);
				break;
			}
			usleep(100);	
		}	
		// change the status of the selected queue to signal it is used by the clerk
		queue_status[selected_queue] = clerk;
		
		// signal the business or economy queue that the clerk is ready
		if (selected_queue == 0) {
			pthread_cond_broadcast(&condEcon);
			winner_selected[selected_queue] = 0;
			pthread_mutex_unlock(&economy);
		} else {
			pthread_cond_broadcast(&condBus);
			winner_selected[selected_queue] = 0;
			pthread_mutex_unlock(&business);
		}
		
		// wait until the customer is served before getting another customer
		if (clerk == 1) {
			pthread_cond_wait(&clerk1, &mutex_clerk1);
		} else if(clerk == 2) {
			pthread_cond_wait(&clerk2, &mutex_clerk2);
		} else if(clerk == 3) {
			pthread_cond_wait(&clerk3, &mutex_clerk3);
		} else  {
			pthread_cond_wait(&clerk4, &mutex_clerk4);
		}
		
	}
	pthread_exit(NULL);
	return NULL;
}

int main(int argc, char* arg[]) {	
	
	// Initalize the variables
	gettimeofday(&init_time, NULL);
	init_time_double = init_time.tv_usec;
	init_time_double_sec = init_time.tv_sec;
	int numberof[3];
	int r;
	for(r = 0; r < 2; r++) {
		queue_status[r] = 0;
		queue_length[r] = 0;
		winner_selected[r] = 0;
		waiting_time_start[r] = 0;
		waiting_time_end[r] = 0;	
		numberof[r] = 0;
	}
	waiting_time_start[2] = 0;
	waiting_time_end[2] = 0;
	numberof[2] = 0;	

	pthread_mutex_init(&business, NULL);
	pthread_mutex_init(&economy, NULL);
	pthread_mutex_init(&mutex_time, NULL);
	
	pthread_cond_init(&clerk1 ,NULL);
	pthread_cond_init(&clerk2 ,NULL);
	pthread_cond_init(&clerk3 ,NULL);	
	pthread_cond_init(&clerk4 ,NULL);
	pthread_cond_init(&condBus ,NULL);
	pthread_cond_init(&condEcon ,NULL);

	bus = NULL;
	econ = NULL;
	
	// Read in the contents of the file
	FILE* in; 
	in = fopen(arg[1], "r");

	if(in == NULL) {
		perror("Error");
		return -1;
	}

	char line[100];
	
	fgets(line, 100, in);

	int x = atoi(line);
	char* str;	
	struct customer_info customer[x];
	int i;

	for(i = 0; i < x; i++) {
		fgets(line, 100, in);
		str = strtok(line, ":");
		customer[i].user_id = atoi(str);
		
		str = strtok(NULL, ",");
		customer[i].class_type = atoi(str);

		str = strtok(NULL, ",");
		customer[i].service_time = atoi(str);
		
		str = strtok(NULL, ",");
		customer[i].arrival_time = atoi(str);
		numberof[2]++;
		numberof[customer[i].class_type]++;
	}

	pthread_t clerks[4];
	pthread_t customers[x];	
	
	// Create the Customer and Clerk Threads
	for(i = 1; i < 5; i++) {
		pthread_create(&clerks[i], NULL, clerk_entry, &i);
		usleep(10);
	}

	for(i = 0; i < x; i++) {
		pthread_create(&customers[i], NULL, customer_entry, (void *) &customer[i]);
		usleep(10);
	}
	
	// Wait for the customer threads to end
	for(i = 0; i < x; i++) {
		pthread_join(customers[i], NULL);
	}	

	// Print the Average run times
	printf("Average Waiting Time for All Classes: %f seconds\n", (((waiting_time_end[2] - waiting_time_start[2])/numberof[2])));
	printf("Average Waiting Time for Economy Class: %f seconds\n",(((waiting_time_end[0] - waiting_time_start[0])/numberof[0])));
	printf("Average Waiting Time for Business Class: %f seconds\n",(((waiting_time_end[1] - waiting_time_start[1])/numberof[1])));

	return 0;
}
