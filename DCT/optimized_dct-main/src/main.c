#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/dct.h"
#include "../include/naive.h"
#include "../include/unoptimized.h"
#include "../include/unrolled.h"
#include "../include/pipelined.h"
#include "../include/neon.h"

uint8_t *read_image(char *filepath, size_t dimensions) {
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

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Error: invalid number of arguments (example: ./dct.exe ./test/8x8_64_byte 8 8)\n");
    return EXIT_FAILURE;
  }
  char *input_file = argv[1];
  int width = atoi(argv[2]);
  int height = atoi(argv[3]);

  if (width % 8 != 0 || height % 8 != 0) {
    printf("Error: the width and height of the image must each be divisible by 8\n");
    return EXIT_FAILURE;
  }
  uint8_t *image = read_image(input_file, width*height);

  // Use the selected DCT algorithm
  void (*algorithm)(int[8][8], int[8][8]);

  printf("Selected DCT algorithm: ");

#ifdef NAIVE
  algorithm = naive;
  printf("naive");
#endif

#ifdef UNOPTIMIZED
  algorithm = unoptimized;
  printf("unoptimized");
#endif

#ifdef UNROLLED
  algorithm = unrolled;
  printf("unrolled");
#endif

#ifdef PIPELINED
  algorithm = pipelined;
  printf("pipelined");
#endif

#ifdef NEON
  algorithm = neon;
  printf("neon");
#endif

  printf("\n\n");

  dct(image, width, height, algorithm);

  return EXIT_SUCCESS;
}
