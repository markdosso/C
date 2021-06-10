#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// linked list datastructure for storage of processes
struct node {
	int pid;
	char* testing;
	struct node* next;
};

// bg command to run process in the background
void bg(char* command, struct node* head) {
	int pid = fork();
	
	// child process
	if(pid == 0) {
		char *arglist[3];
		arglist[0] = command;
		arglist[1] = "&";
		arglist[2] = 0;
		execvp(command, arglist);
	}// if 
	// parent process
	else if(pid > 0) {
		struct node* temp = head;
		struct node* nextNode = (struct node*)malloc(sizeof(struct node));
		nextNode->pid = pid;
		nextNode->testing = command;
		if(temp != NULL) {
			while(temp->next) {
				temp = temp->next;
			}// while
			temp -> next = nextNode; 
		}// if
	}// else if
	//printf("added to head %d\n", head->next->pid);
}// bg

//bglist command to display the list of background programs
void bglist(struct node* head) {
	struct node* temp = head;
	int counter = 0;

	// loops through the linked list and prints the process information
	if (temp != NULL) {
		while(temp->next) {
			printf("%d:   %s\n",temp->next->pid, temp->next->testing);
			counter = counter + 1;
			temp = temp->next;
		}// while
		printf("Total background jobs: %d\n",counter);
	} else {
		printf("Empty");
	}// else
}// bglist

// bgkill command to kill background processes
void bgkill(char* command) {
	kill(atoi(command), SIGKILL);
}// bgkill

// bgstop command to stop background processes
void bgstop(char* command) {
	kill(atoi(command), SIGSTOP);
}// bgstop 

// bgstart command to start background processes that were stopped
void bgstart(char* command) {
	kill(atoi(command), SIGCONT);
}// bgstart

// pstat command to display process information
void pstat(char* command) {	
	int numArr[24];
	char charArr[24][100];
	char pid[strlen(command)+15];	
	snprintf(pid, sizeof(pid), "/proc/%s/stat", command);
	
	FILE *fp;
	char buff[255];
	fp = fopen(pid, "r");

	if(fp == NULL) {
		printf("Error: Process %s does not exist\n", command);
	} else {
		fscanf(fp,"%d %s %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &numArr[0], charArr[0], charArr[1], &numArr[1], &numArr[2], &numArr[3], &numArr[4], &numArr[5], &numArr[6], &numArr[7], &numArr[8], &numArr[9], &numArr[10], &numArr[11], &numArr[12], &numArr[13], &numArr[14], &numArr[15], &numArr[16], &numArr[17], &numArr[18], &numArr[19], &numArr[20], &numArr[21]);
		fclose(fp);
	}// else

	printf("Comm: %s\n", charArr[0]);
	printf("State: %s\n", charArr[1]);
	printf("uTime: %d\n", numArr[11]);
	printf("sTime: %d\n", numArr[12]);
	printf("RSS: %d\n", numArr[21]);

	FILE *fq;
	char pid2[strlen(command)+15];
	char line[100];
	snprintf(pid2, sizeof(pid2), "/proc/%s/status", command);
	fq = fopen(pid2, "r");

	if(fq == NULL) {
		printf("Error: Process %s does not exist\n", command);
	} else {
		int i;
		for(i = 0; i < 36; i++) {
			fgets(line, 100, fq);
		}
		printf("%s", line);
		fgets(line, 100, fq);
		fclose(fq);
		printf("%s", line);
	}// else
}// pstat

//checkKill command to check if any background processes to removed from the linked list
void checkKill(struct node* head) {
	int status;
	struct node* preNode = head;
	struct node* CurrNode = head;

	//receives information if a child process has ended 
	int toRemove = waitpid(-1, &status, WNOHANG);
	
	// if a child process has ended loop through the linked list to find and remove that node
	if(toRemove > 0) {
		while(CurrNode != NULL) {
			if(CurrNode->pid == toRemove) {
				if(CurrNode->next == NULL) {
					printf("Process %d has ended\n",toRemove);
					preNode->next = NULL;
					return;
				} else {
					printf("Process %d has ended\n",toRemove);
					preNode->next = CurrNode->next;
					return;
				}// else
			}// if
			preNode = CurrNode;
			CurrNode = CurrNode->next;
		}// while
	}// if
}// checkKill

//main function
int main () {
	struct node* head = (struct node*)malloc(sizeof(struct node));
	char* command = (char *)malloc(100);
	char* parameter = (char *)malloc(100);
	char* temp = NULL;
	int a = 5;
	int length = 0;
	size_t size;
	while (a != 0) {
		// accpets input from the user
		printf("PMan: > ");
		getline(&command, &size, stdin);
		length = strlen(command);
		
		//removes the \n from the input
		if(command[length-1] == '\n') {
			command[length-1] = '\0';
		}// if
		
		// used to parse command from parameters found at https://stackoverflow.com/questions/15961253/c-correct-usage-of-strtok-r
		command = strtok_r(command, " ", &temp);
		parameter = strtok_r(NULL, " ", &temp);
		
		// checks which command to execute
		if(strcmp(command, "bg") == 0) {
			bg(parameter, head);
		} else if(strcmp(command, "bglist") == 0) {
			bglist(head);
		} else if(strcmp(command, "bgkill") == 0) {
			bgkill(parameter);
		} else if(strcmp(command, "bgstop") == 0) {
			bgstop(parameter);	
		} else if(strcmp(command, "bgstart") == 0) {
			bgstart(parameter);
		} else if(strcmp(command, "pstat") == 0) {
			pstat(parameter);
		} else if(strcmp(command, "end") == 0) {
			exit(0);
		} else {
			printf("Command not found");
		}// else
		
		usleep(100000);
		checkKill(head); // to check if any background process are needed to be removed
	}// while
	
	printf("Closing");
	return 0;
}// main



