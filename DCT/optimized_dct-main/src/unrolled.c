#include <stdint.h>

// Scale factor << 8
#define C1 251
#define C2 237
#define C3 213
#define C4 181
#define C5 142
#define C6 98
#define C7 50

// This algorithm builds on top of UNOPTIMIZED
// It unrolls the loop
// Reduces the strength of operators
// Attempts to minimize cache misses
// Optimizes loop initialization and exit
// Lowers the SF so values fit into 1 register
void unrolled(int32_t input[8][8], int32_t output[8][8]) {
  register int i;
  register int32_t temp1, temp2, temp3, temp4;
  int32_t temp[8][8];

  for (i ^= i; !(i&8); i++) {
    temp1 = input[i][0] + input[i][7];
    temp2 = input[i][1] + input[i][6];
    temp3 = input[i][2] + input[i][5];
    temp4 = input[i][3] + input[i][4];

    // Maintain transpose-ness
    temp[0][i] = (temp1 + temp4 + temp2 + temp3) * C4;
    temp[4][i] = (temp1 + temp4 - temp2 - temp3) * C4;
    temp[2][i] = (temp1 - temp4) * C2 + (temp2 - temp3) * C6;
    temp[6][i] = (temp1 - temp4) * C6 + (temp3 - temp2) * C2;

    temp1 -= input[i][7] << 1;
    temp2 -= input[i][6] << 1;
    temp3 -= input[i][5] << 1;
    temp4 -= input[i][4] << 1;

    temp[1][i] = (C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4);
    temp[3][i] = (C3 * temp1) - (C7 * temp2) - (C1 * temp3) - (C5 * temp4);
    temp[5][i] = (C5 * temp1) - (C1 * temp2) + (C7 * temp3) + (C3 * temp4);
    temp[7][i] = (C7 * temp1) - (C5 * temp2) + (C3 * temp3) - (C1 * temp4);
  }

  for(i ^= i; !(i&8); i++) {
    temp1 = temp[i][0] + temp[i][7];
    temp2 = temp[i][1] + temp[i][6];
    temp3 = temp[i][2] + temp[i][5];
    temp4 = temp[i][3] + temp[i][4];

    // Transpose again to get original image
    // Divide each output element by SF
    // Divide by an additional factor of 4 (>> 2)
    output[i][0] = ((temp1 + temp4 + temp2 + temp3) * C4) >> 18;
    output[i][4] = ((temp1 + temp4 - temp2 - temp3) * C4) >> 18;
    output[i][2] = ((temp1 - temp4) * C2 + (temp2 - temp3) * C6) >> 18;
    output[i][6] = ((temp1 - temp4) * C6 + (temp3 - temp2) * C2) >> 18;

    temp1 -= temp[i][7] << 1;
    temp2 -= temp[i][6] << 1;
    temp3 -= temp[i][5] << 1;
    temp4 -= temp[i][4] << 1;

    output[i][1] = ((C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4)) >> 18;
    output[i][3] = ((C3 * temp1) - (C7 * temp2) - (C1 * temp3) - (C5 * temp4)) >> 18;
    output[i][5] = ((C5 * temp1) - (C1 * temp2) + (C7 * temp3) + (C3 * temp4)) >> 18;
    output[i][7] = ((C7 * temp1) - (C5 * temp2) + (C3 * temp3) - (C1 * temp4)) >> 18;
  }
}
