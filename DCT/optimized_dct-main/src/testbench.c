#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/naive.h"
#include "../include/neon.h"
 
uint8_t *read(char *filepath, size_t dimensions) {
  FILE *fp = fopen(filepath, "r");
  if(fp == NULL) {
    perror("Error: unable to open file");
    exit(EXIT_FAILURE);
  }

  uint8_t *buffer = malloc(sizeof(uint8_t) * dimensions);

  // Save data to memory
  fread(buffer, sizeof(uint8_t), dimensions, fp);

  fclose(fp);

  return buffer;
}

int checkBlock(int output[8][8], int output2[8][8]){
  int i, j;
  for(i = 0; i < 8; i++) {
    for(j = 0; j < 8; j++) {
      if(output[i][j] > (output2[i][j] + 2) || output[i][j] < (output2[i][j] - 2)) {
        return 1;
      }
    }
  }
  return 0;
}

int testcase(uint8_t *image, int width, int height) {
  int i, j, k, l;
  int width_offset = width / 8;
  int height_offset = height / 8;

  for (i = 0; i < height_offset; i++) {
    for (j = 0; j < width_offset; j++) {
      int block[8][8];
      int block_transposed[8][8];
      int actual[8][8];
      int expected[8][8];

      for (k = 0; k < 8; k++) {
        for (l = 0; l < 8; l++) {
          int index = width*((i*8) + k) + ((j*8) + l);
          block[k][l] = image[index];
          block_transposed[l][k] = image[index];
        }
      }

      neon(block_transposed, actual); // change to what method will be the fully optimized algo
      naive(block, expected);

      if(checkBlock(actual, expected) == 1) {
        return 1;
      }
    }
  } 
  return 0;  
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Error: invalid number of arguments (example: ./testbench.exe ./test/8x8_64_byte 8 8)\n");
    return EXIT_FAILURE;
  }
  char *input_file = argv[1];
  int width = atoi(argv[2]);
  int height = atoi(argv[3]);

  if (width % 8 != 0 || height % 8 != 0) {
    printf("Error: the width and height of the image must each be divisible by 8\n");
    return EXIT_FAILURE;
  }
  uint8_t *image = read(input_file, width*height);

  if(testcase(image, width, height) == 0) {
    printf("testcase Success\n");
  } else {
    printf("testcase Failure\n");
  }

  return EXIT_SUCCESS;
}
