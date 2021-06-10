#include <stdio.h>
#include <unistd.h>

int main() {
	usleep(100);
	printf("Start");
	printf("processing");
	usleep(4000000);
	printf("Done");
	return 0;
}
