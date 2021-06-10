#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int getSize(char* fileName, char* info) {
	while (info[0] != 0x00) {
		if ((info[11] & 0b00000010) == 0 && (info[11] & 0b00001000) == 0) {
			char* name = malloc(sizeof(char));
			char* extension = malloc(sizeof(char));
            int counter;
			for (counter = 0; counter < 8; counter++) {
				if (info[counter] == ' ') {
					break;
                } // if
                name[counter] = info[counter];
            } // for
            for (counter = 0; counter < 3; counter++) {
				extension[counter] = info[counter+8];
            } // for
            strcat(name, ".");
            strcat(name, extension);
			if (strcmp(fileName, name) == 0) {
				int size = (info[28] & 0xFF) + ((info[29] & 0xFF) << 8) + ((info[30] & 0xFF) << 16) + ((info[31] & 0xFF) << 24);
                return size;
            } // if           
        } // if
        info += 32;
    } // while
    return -1;
} // getSize

void printInfo(char* info) {
	printf("Root\n==================\n");
    while (info[0] != 0x00) {
		char type;
        if ((info[11] & 0b00010000) == 0b00010000) {
			type = 'D';
        } else {
			type = 'F';
        } // else
        char* name = malloc(sizeof(char));
        int counter;
		for (counter = 0; counter < 8; counter++) {
			if (info[counter] == ' ') {
				break;
            } // if
            name[counter] = info[counter];
        } // for
        char* extension = malloc(sizeof(char));       
		for (counter = 0; counter < 3; counter++) {
			extension[counter] = info[counter+8];
        } // for
		strcat(name, ".");
        strcat(name, extension);
        int size = getSize(name, info);
        int year = (((info[17] & 0b11111110)) >> 1) + 1980;
        int month = ((info[16] & 0b11100000) >> 5) + (((info[17] & 0b00000001)) << 3);
        int day = (info[16] & 0b00011111);
        int hour = (info[15] & 0b11111000) >> 3;
        int minute = ((info[14] & 0b11100000) >> 5) + ((info[15] & 0b00000111) << 3);
		if ((info[11] & 0b00000010) == 0 && (info[11] & 0b00001000) == 0) {
			printf("%c %10d %20s %d-%d-%d %02d:%02d\n", type, size, name, year, month, day, hour, minute);
		} // if
		info += 32;
    } // while
} // printInfo

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Input Error\n");
        exit(1);
    } // if
	int diskIm = open(argv[1], O_RDWR);
    if (diskIm < 0) {
		printf("Cannot Read Disk\n");
        exit(1);
    }  // if      
	struct stat sb;
    fstat(diskIm, &sb);
    char* mapping = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, diskIm, 0);
    if (mapping == MAP_FAILED) {
		printf("Failed to Map\n");
        exit(1);
    } // if
	printInfo(mapping + 512 * 19);
    munmap(mapping, sb.st_size);
    close(diskIm);
	return 0;
} // main

