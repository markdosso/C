#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int getFat(int counter, char* info) {
	int result;
	int first;
	int second;
	if ((counter % 2) == 0) {
		first = info[512 + ((3*counter) / 2) + 1] & 0x0F;
		second = info[512 + ((3*counter) / 2)] & 0xFF;
		result = (first << 8) + second;
	} else {
		first = info[512 + (int)((3*counter) / 2)] & 0xF0;
		second = info[512 + (int)((3*counter) / 2) + 1] & 0xFF;
		result = (first >> 4) + (second << 4);
	} // else
	return result;
} // getFat

int getSize(char* fileName, char* info) {
	while (info[0] != 0x00) {
		if ((info[11] & 0b00000010) == 0 && (info[11] & 0b00001000) == 0) {
			char* name = malloc(sizeof(char*));
			char* extension = malloc(sizeof(char*));
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
				int size = (info[28] & 0xFF); 
				size += ((info[29] & 0xFF) << 8); 
				size += ((info[30] & 0xFF) << 16); 
				size += ((info[31] & 0xFF) << 24);
				return size;
			} // if
		} // if
		info += 32;
	} // while
	return -1;
} // getSize

int getSector(char* fileName, char* info) {
    while (info[0] != 0x00) {
        if ((info[11] & 0b00000010) == 0 && (info[11] & 0b00001000) == 0) {
            char* name = malloc(sizeof(char*));
            char* extension = malloc(sizeof(char*));
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
				return (info[26]) + (info[27] << 8);
            } // if
        } // if
        info += 32;
    } // while
    return -1;
} // getSector

void copy(char* info, char* info2, char* fileName) {
	int firstSector = getSector(fileName, info + 512 * 19);
	int temp = firstSector;
	int size = getSize(fileName, info + 512 * 19);
	int remaining = size;
	int address = 512 * (31 + temp);
	do {
		temp = (remaining == size) ? firstSector : getFat(temp, info);
		address = 512 * (31 + temp);
		int counter;
		for (counter = 0; counter < 512; counter++) {
			if (remaining == 0) {
				break;
			} // if
			info2[size - remaining] = info[counter + address];
			remaining--;
		} // for
	} while (getFat(temp, info) != 0xFFF);
} // copy

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Input Error\n");
		exit(1);
	} // if
	int diskIm = open(argv[1], O_RDWR);
	if (diskIm < 0) {
		printf("Cannot read Image\n");
		exit(1);
	} // if
	struct stat sb;
	fstat(diskIm, &sb);
	char* mapping = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, diskIm, 0);
	if (mapping == MAP_FAILED) {
		printf("Cannot Map Image\n");
		close(diskIm);
		exit(1);
	} // if
	int fileSize = getSize(argv[2], mapping + 512 * 19);
	if (fileSize > 0) {
		// Create new file to be written
		int diskIm2 = open(argv[2], O_RDWR | O_CREAT, 0666);
		if (diskIm2 < 0) {
			printf("Cannot Open File\n");
			close(diskIm);
			exit(1);
		} // if
		int result = lseek(diskIm2, fileSize-1, SEEK_SET);
		if (result == -1) {
			munmap(mapping, sb.st_size);
			close(diskIm);
			close(diskIm2);
			printf("Error\n");
			exit(1);
		} // if
		result = write(diskIm2, "", 1);
		if (result != 1) {
			munmap(mapping, sb.st_size);
			close(diskIm);
			close(diskIm2);
			printf("Failed to Write\n");
			exit(1);
		} // if
		// Map memory for file to be written
		char* mapping2 = mmap(NULL, fileSize, PROT_WRITE, MAP_SHARED, diskIm2, 0);
		if (mapping2 == MAP_FAILED) {
			printf("Cannot Map Image\n");
			exit(1);
		} // if
		// Copy file from disk image to local directory
		copy(mapping, mapping2, argv[2]);
		munmap(mapping2, fileSize);
		close(diskIm2);
	} else {
		printf("Cannot Find File\n");
	} // else
	return 0;
} // main
