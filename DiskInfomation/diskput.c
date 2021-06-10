#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

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
} //getFat

int getTotalSize(char* info) {
    int bytes = info[11] + (info[12] << 8);
    int sectorCount = info[19] + (info[20] << 8);
    return bytes * sectorCount;
} // getTotalSize

int getFree(int diskSize, char* info) {
    int sectors = 0;
    int counter;
    for (counter = 2; counter < (diskSize / 512); counter++) {
        if (getFat(counter, info) == 0x000) {
                sectors++;
        } // if
    } // for
    return 512 * sectors;
} // getFree

int diskContains(char* fileName, char* info) {
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
				return 1;
            } // if
		} // if
		info += 32;
	} // while
	return 0;
} // diskContains

void updateRoot(char* fileName, int size, int sector, char* info) {
	info += 512 * 19;
	while (info[0] != 0x00) {
		info += 32;
	} // while
	int counter;
	int done = -1;
	for (counter = 0; counter < 8; counter++) {
		char character = fileName[counter];
		if (character == '.') {
			done = counter;
		} // if
		info[counter] = (done == -1) ? character : ' ';
	} // for
	for (counter = 0; counter < 3; counter++) {
		info[counter+8] = fileName[counter+done+1];
	} // for
	info[11] = 0x00;
	time_t t = time(NULL);
	struct tm *now = localtime(&t);
	int year = now->tm_year + 1900;
	int month = (now->tm_mon + 1);
	int day = now->tm_mday;
	int hour = now->tm_hour;
	int minute = now->tm_min;
	info[14] = 0;
	info[15] = 0;
	info[16] = 0;
	info[17] = 0;
	info[17] |= (year - 1980) << 1;
	info[17] |= (month - ((info[16] & 0b11100000) >> 5)) >> 3;
	info[16] |= (month - (((info[17] & 0b00000001)) << 3)) << 5;
	info[16] |= (day & 0b00011111);
	info[15] |= (hour << 3) & 0b11111000;
	info[15] |= (minute - ((info[14] & 0b11100000) >> 5)) >> 3;
	info[14] |= (minute - ((info[15] & 0b00000111) << 3)) << 5;
	// Set first logical cluster
	info[26] = (sector - (info[27] << 8)) & 0xFF;
	info[27] = (sector - info[26]) >> 8;
	// Set size
	info[28] = (size & 0x000000FF);
	info[29] = (size & 0x0000FF00) >> 8;
	info[30] = (size & 0x00FF0000) >> 16;
	info[31] = (size & 0xFF000000) >> 24;
} // updateRoot

int getNextFat(char* info) {
	info += 512;
	int temp = 2;
	while (getFat(temp, info) != 0x000) {
		temp++;
	} // while
	return temp;
} // getNextFat

void setFat(int counter, int input, char* info) {
	info += 512;
	if ((counter % 2) == 0) {
		info[512 + ((3*counter) / 2) + 1] = (input >> 8) & 0x0F;
		info[512 + ((3*counter) / 2)] = input & 0xFF;
	} else {
		info[512 + (int)((3*counter) / 2)] = (input << 4) & 0xF0;
		info[512 + (int)((3*counter) / 2) + 1] = (input >> 4) & 0xFF;
	} // else
} // setFat

void copy(char* info, char* info2, char* name, int size) {
	if (!diskContains(name, info + 512 * 19)) {
		int remaining = size;
		int cur = getNextFat(info);
		updateRoot(name, size, cur, info);
		while (remaining > 0) {
			int address = 512 * (31 + cur);	
			int counter;
			for (counter = 0; counter < 512; counter++) {
				if (remaining == 0) {
					setFat(cur, 0xFFF, info);
					return;
				} // if
				info[counter + address] = info2[size - remaining];
				remaining--;
			} // for
			setFat(cur, 0x69, info);
			int next = getNextFat(info);
			setFat(cur, next, info);
			cur = next;
		} // while
	} // if
} // copy

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Input Error\n");
		exit(1);
	} // if

	// Open disk image and map memory
	int fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		printf("Cannot read Disk\n");
		exit(1);
	} // if
	struct stat sb;
	fstat(fd, &sb);
	char* mapping = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (mapping == MAP_FAILED) {
		printf("Cannot Map\n");
		close(fd);
		exit(1);
	} // if

	// Open file and map memory
	int fd2 = open(argv[2], O_RDWR);
	if (fd2 < 0) {
		printf("Cannot Find File\n");
		close(fd);
		exit(1);
	} // if
	struct stat sb2;
	fstat(fd2, &sb2);
	int size = sb2.st_size;
	char* info2 = mmap(NULL, size, PROT_READ, MAP_SHARED, fd2, 0);
	if (info2 == MAP_FAILED) {
		printf("Failed to Map\n");
		exit(1);
	} // if

	// Copy file from local directory to disk image if there's space
	int total = getTotalSize(mapping);
	int diskSize = getFree(total, mapping);
	if (diskSize >= size) {
		copy(mapping, info2, argv[2], size);
	} else {
		printf("%d %d\n", diskSize, size);
		printf("No Space\n");
	} // else

	// Clean up
	munmap(mapping, sb.st_size);
	munmap(info2, size);
	close(fd);
	close(fd2);
	return 0;
}
