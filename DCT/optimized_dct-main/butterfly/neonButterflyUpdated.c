#include <stdint.h>
#include "arm_neon.h"

#define C1 251
#define C2 237
#define C3 213
#define C4 181
#define C5 142
#define C6 98
#define C7 50

void neonButterflyUpdated(int input[8][8], int output[8][8]) {
  register int i;
  register int64_t temp1, temp2, temp3, temp4;
  int32_t temp[8][8];

  int64x2_t pairwiseAddedOnce;
  int32x2_t narrowed;
  int64x1_t pairwiseAddedTwice;
  int64x2_t pairwiseAddedOnce2;
  int32x2_t narrowed2;
  int64x1_t pairwiseAddedTwice2;

  for (i ^= i; !(i&8); i++) {
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp1)
      : "r" (input[i][0]), "r" (input[i][7]), "r" (1)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp2)
      : "r" (input[i][1]), "r" (input[i][6]), "r" (2)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp3)
      : "r" (input[i][2]), "r" (input[i][5]), "r" (3)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp4)
      : "r" (input[i][3]), "r" (input[i][4]), "r" (4)
    );

    int32x4_t tempVector = { (int32_t)(temp1 >> 32), (int32_t)(temp2 >> 32), (int32_t)(temp3 >> 32), (int32_t)(temp4 >> 32)};
    int32x4_t tempVector2 = { (int32_t)temp1 & 0b00000000000000000000000000000000011111111111111111111111111111111, 
                               (int32_t)temp2 & 0b00000000000000000000000000000000011111111111111111111111111111111, 
                               (int32_t)temp3 & 0b00000000000000000000000000000000011111111111111111111111111111111, 
                               (int32_t)temp4 & 0b00000000000000000000000000000000011111111111111111111111111111111};

    pairwiseAddedOnce = vpaddlq_s32(tempVector);
    pairwiseAddedOnce2 = vpaddlq_s32(tempVector2);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    narrowed2 = vmovn_s64(pairwiseAddedOnce2);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    pairwiseAddedTwice2 = vpaddl_s32(narrowed2);
    temp[0][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
    temp[1][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice2, 0);

    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp1)
      : "r" (input[i][0]), "r" (input[i][7]), "r" (6)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp2)
      : "r" (input[i][1]), "r" (input[i][6]), "r" (6)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp3)
      : "r" (input[i][2]), "r" (input[i][5]), "r" (7)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2\n"
      : "=r" (temp4)
      : "r" (input[i][3]), "r" (input[i][4]), "r" (8)
    );

    int32x4_t tempVector3 = { (int32_t)(temp1 >> 32), (int32_t)(temp2 >> 32), (int32_t)(temp3 >> 32), (int32_t)(temp4 >> 32)};
    int32x4_t tempVector4 = { (int32_t)temp1 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp2 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp3 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp4 & 0b00000000000000000000000000000000011111111111111111111111111111111};

    pairwiseAddedOnce = vpaddlq_s32(tempVector3);
    pairwiseAddedOnce2 = vpaddlq_s32(tempVector4);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    narrowed2 = vmovn_s64(pairwiseAddedOnce2);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    pairwiseAddedTwice2 = vpaddl_s32(narrowed2);
    temp[2][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
    temp[3][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice2, 0);

        __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp1)
      : "r" (input[i][0]), "r" (input[i][7]), "r" (9)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp2)
      : "r" (input[i][1]), "r" (input[i][6]), "r" (10)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp3)
      : "r" (input[i][2]), "r" (input[i][5]), "r" (11)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp4)
      : "r" (input[i][3]), "r" (input[i][4]), "r" (12)
    );

    int32x4_t tempVector5 = { (int32_t)(temp1 >> 32), (int32_t)(temp2 >> 32), (int32_t)(temp3 >> 32), (int32_t)(temp4 >> 32)};
    int32x4_t tempVector6 = { (int32_t)temp1 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp2 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp3 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp4 & 0b00000000000000000000000000000000011111111111111111111111111111111};

    pairwiseAddedOnce = vpaddlq_s32(tempVector5);
    pairwiseAddedOnce2 = vpaddlq_s32(tempVector6);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    narrowed2 = vmovn_s64(pairwiseAddedOnce2);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    pairwiseAddedTwice2 = vpaddl_s32(narrowed2);
    temp[4][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
    temp[5][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice2, 0);

    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp1)
      : "r" (input[i][0]), "r" (input[i][7]), "r" (13)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp2)
      : "r" (input[i][1]), "r" (input[i][6]), "r" (14)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp3)
      : "r" (input[i][2]), "r" (input[i][5]), "r" (15)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp4)
      : "r" (input[i][3]), "r" (input[i][4]), "r" (16)
    );

    int32x4_t tempVector7 = { (int32_t)(temp1 >> 32), (int32_t)(temp2 >> 32), (int32_t)(temp3 >> 32), (int32_t)(temp4 >> 32)};
    int32x4_t tempVector8 = { (int32_t)temp1 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp2 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp3 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp4 & 0b00000000000000000000000000000000011111111111111111111111111111111};
    
    pairwiseAddedOnce = vpaddlq_s32(tempVector7);
    pairwiseAddedOnce2 = vpaddlq_s32(tempVector8);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    narrowed2 = vmovn_s64(pairwiseAddedOnce2);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    pairwiseAddedTwice2 = vpaddl_s32(narrowed2);
    temp[6][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0);
    temp[7][i] = (int32_t)vget_lane_s64(pairwiseAddedTwice2, 0);

  }

  for(i ^= i; !(i&8); i++) {
        __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp1)
      : "r" (input[i][0]), "r" (input[i][7]), "r" (1)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp2)
      : "r" (input[i][1]), "r" (input[i][6]), "r" (2)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp3)
      : "r" (input[i][2]), "r" (input[i][5]), "r" (3)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp4)
      : "r" (input[i][3]), "r" (input[i][4]), "r" (4)
    );

    int32x4_t tempVector9 = { (int32_t)(temp1 >> 32), (int32_t)(temp2 >> 32), (int32_t)(temp3 >> 32), (int32_t)(temp4 >> 32)};
    int32x4_t tempVector10 = { (int32_t)temp1 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp2 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp3 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp4 & 0b00000000000000000000000000000000011111111111111111111111111111111};

    pairwiseAddedOnce = vpaddlq_s32(tempVector9);
    pairwiseAddedOnce2 = vpaddlq_s32(tempVector10);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    narrowed2 = vmovn_s64(pairwiseAddedOnce2);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    pairwiseAddedTwice2 = vpaddl_s32(narrowed2);
    output[i][0] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;
    output[i][1] = (int32_t)vget_lane_s64(pairwiseAddedTwice2, 0) >> 18;

        __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp1)
      : "r" (input[i][0]), "r" (input[i][7]), "r" (5)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp2)
      : "r" (input[i][1]), "r" (input[i][6]), "r" (6)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp3)
      : "r" (input[i][2]), "r" (input[i][5]), "r" (7)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp4)
      : "r" (input[i][3]), "r" (input[i][4]), "r" (8)
    );

    int32x4_t tempVector11 = { (int32_t)(temp1 >> 32), (int32_t)(temp2 >> 32), (int32_t)(temp3 >> 32), (int32_t)(temp4 >> 32)};
    int32x4_t tempVector12 = { (int32_t)temp1 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp2 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp3 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp4 & 0b00000000000000000000000000000000011111111111111111111111111111111};
    
    pairwiseAddedOnce = vpaddlq_s32(tempVector11);
    pairwiseAddedOnce2 = vpaddlq_s32(tempVector12);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    narrowed2 = vmovn_s64(pairwiseAddedOnce2);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    pairwiseAddedTwice2 = vpaddl_s32(narrowed2);
    output[i][2] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;
    output[i][3] = (int32_t)vget_lane_s64(pairwiseAddedTwice2, 0) >> 18;

        __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp1)
      : "r" (input[i][0]), "r" (input[i][7]), "r" (9)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp2)
      : "r" (input[i][1]), "r" (input[i][6]), "r" (10)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp3)
      : "r" (input[i][2]), "r" (input[i][5]), "r" (11)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp4)
      : "r" (input[i][3]), "r" (input[i][4]), "r" (12)
    );

    int32x4_t tempVector13 = { (int32_t)(temp1 >> 32), (int32_t)(temp2 >> 32), (int32_t)(temp3 >> 32), (int32_t)(temp4 >> 32)};
    int32x4_t tempVector14 = { (int32_t)temp1 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp2 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp3 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp4 & 0b00000000000000000000000000000000011111111111111111111111111111111};
    
    pairwiseAddedOnce = vpaddlq_s32(tempVector13);
    pairwiseAddedOnce2 = vpaddlq_s32(tempVector14);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    narrowed2 = vmovn_s64(pairwiseAddedOnce2);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    pairwiseAddedTwice2 = vpaddl_s32(narrowed2);
    output[i][4] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;
    output[i][5] = (int32_t)vget_lane_s64(pairwiseAddedTwice2, 0) >> 18;

        __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp1)
      : "r" (input[i][0]), "r" (input[i][7]), "r" (13)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp2)
      : "r" (input[i][1]), "r" (input[i][6]), "r" (14)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp3)
      : "r" (input[i][2]), "r" (input[i][5]), "r" (15)
    );
    __asm__ __volatile__ (
      "btrfly\t%0, %1, %2 %3\n"
      : "=r" (temp4)
      : "r" (input[i][3]), "r" (input[i][4]), "r" (16)
    );

    int32x4_t tempVector15 = { (int32_t)(temp1 >> 32), (int32_t)(temp2 >> 32), (int32_t)(temp3 >> 32), (int32_t)(temp4 >> 32)};
    int32x4_t tempVector16 = { (int32_t)temp1 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp2 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp3 & 0b00000000000000000000000000000000011111111111111111111111111111111, (int32_t)temp4 & 0b00000000000000000000000000000000011111111111111111111111111111111};

    pairwiseAddedOnce = vpaddlq_s32(tempVector15);
    pairwiseAddedOnce2 = vpaddlq_s32(tempVector16);
    narrowed = vmovn_s64(pairwiseAddedOnce);
    narrowed2 = vmovn_s64(pairwiseAddedOnce2);
    pairwiseAddedTwice = vpaddl_s32(narrowed);
    pairwiseAddedTwice2 = vpaddl_s32(narrowed2);
    output[i][6] = (int32_t)vget_lane_s64(pairwiseAddedTwice, 0) >> 18;
    output[i][7] = (int32_t)vget_lane_s64(pairwiseAddedTwice2, 0) >> 18;
  }
}