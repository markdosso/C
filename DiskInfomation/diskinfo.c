#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char* getOS (char* info) {
	int counter;
	char* OS = malloc(sizeof(char));
	for(int counter = 0; counter < 8; counter++) {
		OS[counter] = info[counter+3];
	} // for
	return OS;
} // getOS

int getDiskSize(char* info) {
    int sectorByte; 
	int countSector;
	sectorByte = info[11];
	sectorByte += (info[12] << 8);
	countSector = info[19];
	countSector += (info[20] << 8);
    return sectorByte * countSector;
} // getDiskSize

int getSectorFat(char* info) {
	return info[22] + (info[23] << 8);
} //getSectorFat

char* getLabel(char* info) {
	int counter;
	char* label = malloc(sizeof(char));
    for (counter = 0; counter < 8; counter++) {
		label[counter] = info[counter+43];
    } // for
    if (label[0] == ' ') {
		info += 512 * 19;
        while (info[0] != 0x00) {
			if (info[11] == 8) {
				for (counter = 0; counter < 8; counter++) {
					label[counter] = info[counter];
                } // for
            } // if
            info += 32;
        } // while
    } // if
	return label;
} // getLabel

int getNumOfFiles(char* info) {
	info += 512 * 19;
    int count = 0;
    while (info[0] != 0x00) {
		if ((info[11] & 0b00000010) == 0 && (info[11] & 0b00001000) == 0 && (info[11] & 0b00010000) == 0) {
			count++;
        } // if
		if ((info[11] & 0b00010000) == 1) {		
			info += 64;
			while(info[0] != 0x00) {
				if((info[11] & 0b00000010) == 0 && (info[11] & 0b00010000)) {
					count++;
				} // if
				info += 32;
			} // while
		} // if
		info += 32;
	} // while
    return count;
} // getNumOfFiles

int fatCopies(char* info) {
	return info[16];
} // fatCopies

int getFreeSpace(int disk, char* info) {
    int free = 0;
	int result;
    int first;
    int second;
    int counter;
	for (counter = 2; counter < (disk / 512); counter++) {
		if ((counter % 2) == 0) {
			first = info[512 + ((3*counter) / 2) + 1] & 0x0F;
			second = info[512 + ((3*counter) / 2)] & 0xFF;
			result = (first << 8) + second;
        } else {
            first = info[512 + (int)((3*counter) / 2)] & 0xF0;
			second = info[512 + (int)((3*counter) / 2) + 1] & 0xFF;
            result = (first >> 4) + (second << 4);
		} // else
		if (result == 0x000) {
			free++;
        } // if
    } // for
	return 512 * free;
} // getFreeSpace

int main(int argc, char* argv[]) {
	// check to see if the user has put the correct number of inputs
	if (argc < 2) {
		printf("Input Error");
		exit(1);
	} // if
	int diskIm = open(argv[1], O_RDWR);
	if(diskIm < 0) {
		printf("Error Reading Disk");	
		exit(1);
	} // if
	struct stat sb;
    fstat(diskIm, &sb);
    char* mapping = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, diskIm, 0);
    if (mapping == MAP_FAILED) {
		printf("Error Failed to map memory\n");
        exit(1);
    } // if
	printf("OS Name: %s\n", getOS(mapping));
    printf("Label of the disk: %s\n", getLabel(mapping));
    printf("Total size of the disk: %d bytes\n", getDiskSize(mapping));
    printf("Free size of the disk: %d bytes\n\n", getFreeSpace(getDiskSize(mapping), mapping));
    printf("==============\n");
    printf("The number of files in the disk: %d\n\n", getNumOfFiles(mapping));
    printf("=============\n");
    printf("Number of FAT copies: %d\n", fatCopies(mapping));
    printf("Sectors per FAT: %d\n", getSectorFat(mapping));
	munmap(mapping, sb.st_size);
	close(diskIm);
	return 0;
} // main

