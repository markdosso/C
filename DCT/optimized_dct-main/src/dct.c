#include <stdio.h>
#include <stdint.h>

void print_matrix(int matrix[8][8], int width, int height) {
  int i, j;
  for (i = 0; i < width; i++) {
    for (j = 0; j < height; j++) {
      printf("%4d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void dct(uint8_t *image, int width, int height, void (*algorithm)(int[8][8], int[8][8])) {
  int i, j, k, l;
  int width_offset = width >> 3;
  int height_offset = height >> 3;
  for (i = 0; i < height_offset; i++) {
    for (j = 0; j < width_offset; j++) {
      int block[8][8];
      int output[8][8];

      for (k = 0; k < 8; k++) {
        for (l = 0; l < 8; l++) {
          int index = width*((i*8) + k) + ((j*8) + l);
#ifndef TRANSPOSE
          block[k][l] = image[index];
#endif
#ifdef TRANSPOSE
          block[l][k] = image[index]; // transpose the image!
#endif
        }
      }

      printf("Block with top-left coordinates: (%d,%d)\n", j*8, i*8);

      algorithm(block, output);

      print_matrix(output, 8, 8);
    } 
  }
}
