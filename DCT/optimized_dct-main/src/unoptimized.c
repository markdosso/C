#define C1 32138
#define C2 30274
#define C3 27246
#define C4 23170
#define C5 18205
#define C6 12540
#define C7 6393

// This algorithm builds on top of NAIVE
// It implements the brute-force implementation with symmetry exploited
// It uses fixed-point arithmetic
void unoptimized(int input[8][8], int output[8][8]) {
  int x, y, i, j;
  for (y = 2; y != 0; y--) {
    for (x = 0; x < 8; x++) {
      int temp1, temp2, temp3, temp4;

      temp1 = input[0][x] + input[7][x];
      temp2 = input[1][x] + input[6][x];
      temp3 = input[2][x] + input[5][x];
      temp4 = input[3][x] + input[4][x];

      output[x][0] = ((C4 * temp1) + (C4 * temp2) + (C4 * temp3) + (C4 * temp4)) >> 15;
      output[x][2] = ((C2 * temp1) + (C6 * temp2) + (-C6 * temp3) + (-C2 * temp4)) >> 15;
      output[x][4] = ((C4 * temp1) + (-C4 * temp2) + (-C4 * temp3) + (C4 * temp4)) >> 15;
      output[x][6] = ((C6 * temp1) + (-C2 * temp2) + (C2 * temp3) + (-C6 * temp4)) >> 15;

      temp1 = input[0][x] - input[7][x];
      temp2 = input[1][x] - input[6][x];
      temp3 = input[2][x] - input[5][x];
      temp4 = input[3][x] - input[4][x];

      output[x][1] = ((C1 * temp1) + (C3 * temp2) + (C5 * temp3) + (C7 * temp4)) >> 15;
      output[x][3] = ((C3 * temp1) + (-C7 * temp2) + (-C1 * temp3) + (-C5 * temp4)) >> 15;
      output[x][5] = ((C5 * temp1) + (-C1 * temp2) + (C7 * temp3) + (C3 * temp4)) >> 15;
      output[x][7] = ((C7 * temp1) + (-C5 * temp2) + (C3 * temp3) + (-C1 * temp4)) >> 15;
    }

    for (i = 0; i < 8; i++) {
      for (j = 0; j < 8; j++){
        input[i][j] = output[i][j];
      }
    }
  }

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      output[i][j] >>= 2;
    }
  }
}
