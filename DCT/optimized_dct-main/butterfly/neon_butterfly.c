#include <stdint.h>
#include "arm_neon.h"

#define C1 251
#define C2 237
#define C3 213
#define C4 181
#define C5 142
#define C6 98
#define C7 50

void neonButterfly(int input[8][8], int output[8][8]) {
  register int i;
  register int32_t temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
  int32_t temp[8][8];

  int32x4_t C_row_0 = {C4, C4, C4, C4};
  int32x4_t C_row_1 = {C2, C6, -C6, -C2};
  int32x4_t C_row_2 = {C4, -C4, -C4, C4};
  int32x4_t C_row_3 = {C6, -C2, C2, -C6};
  int32x4_t C_row_4 = {C1, C3, C5, C7};
  int32x4_t C_row_5 = {C3, -C7, -C1, -C5};
  int32x4_t C_row_6 = {C5, -C1, C7, C3};
  int32x4_t C_row_7 = {C7, -C5, C3, -C1};

  int32x4_t prod;

  int64x2_t pairwiseAddedOnce;
  int32x2_t narrowed;
  int64x1_t pairwiseAddedTwice;

  for (i ^= i; !(i&8); i++) {

    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp5)
      : "r" (input[i][0]), "r" (input[i][7])
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp6)
      : "r" (input[i][1]), "r" (input[i][6])
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp7)
      : "r" (input[i][2]), "r" (input[i][5])
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp8)
      : "r" (input[i][3]), "r" (input[i][4])
    );
    temp1 = temp5 >> 16;
    temp2 = temp6 >> 16;
    temp3 = temp7 >> 16;
    temp4 = temp8 >> 16;

    int32x4_t tempVector = { temp1, temp2, temp3, temp4 };

    prod = vmulq_s32(tempVector, C_row_0);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[0][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector, C_row_1);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[2][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector, C_row_2);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[4][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector, C_row_3);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[6][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    temp1 = temp5 & 0b00000000000000001111111111111111;
    temp2 = temp6 & 0b00000000000000001111111111111111;
    temp3 = temp7 & 0b00000000000000001111111111111111;
    temp4 = temp8 & 0b00000000000000001111111111111111;

    int32x4_t tempVector2 = { temp1, temp2, temp3, temp4 };

    prod = vmulq_s32(tempVector2, C_row_4);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[1][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector2, C_row_5);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[3][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector2, C_row_6);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[5][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);

    prod = vmulq_s32(tempVector2, C_row_7);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    temp[7][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
  }

  for(i ^= i; !(i&8); i++) {
        __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp5)
      : "r" (input[i][0]), "r" (input[i][7])
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp6)
      : "r" (input[i][1]), "r" (input[i][6])
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp7)
      : "r" (input[i][2]), "r" (input[i][5])
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp8)
      : "r" (input[i][3]), "r" (input[i][4])
    );
    temp1 = temp5 >> 16;
    temp2 = temp6 >> 16;
    temp3 = temp7 >> 16;
    temp4 = temp8 >> 16;

    int32x4_t tempVector = { temp1, temp2, temp3, temp4 };

    prod = vmulq_s32(tempVector, C_row_0);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][0] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    prod = vmulq_s32(tempVector, C_row_1);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][2] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    prod = vmulq_s32(tempVector, C_row_2);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][4] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    prod = vmulq_s32(tempVector, C_row_3);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][6] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    temp1 = temp5 & 0b00000000000000001111111111111111;
    temp2 = temp6 & 0b00000000000000001111111111111111;
    temp3 = temp7 & 0b00000000000000001111111111111111;
    temp4 = temp8 & 0b00000000000000001111111111111111;

    int32x4_t tempVector2 = { temp1, temp2, temp3, temp4 };

    prod = vmulq_s32(tempVector2, C_row_4);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][1] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;;

    prod = vmulq_s32(tempVector2, C_row_5);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][3] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    prod = vmulq_s32(tempVector2, C_row_6);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][5] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;

    prod = vmulq_s32(tempVector2, C_row_7);
    pairwiseAddedOnce = vpaddlq_s32(prod);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    output[i][7] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;
  }
}