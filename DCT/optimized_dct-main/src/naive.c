#define INV_SQRT2 0.707106781186547 // 1/sqrt(2)

// (2*i+1)*u with max i and u (7) => (2*7+1)*7 = max index of 105
// However, the values loop every 32 indices, so take (2*i+1)*u%32
// (index 32 = 1.00000000000000 again).
// A decimal string with at most 15 sigfigs converted to a double and back to
// a string should match the original string.
// Ref: https://en.wikipedia.org/wiki/Double-precision_floating-point_format
const double cosine[32] = {
  1.0, // 0
  0.980785280403230, // 1
  0.923879532511287, // 2
  0.831469612302545, // 3
  0.707106781186548, // 4
  0.555570233019602,
  0.382683432365090,
  0.195090322016128,
  0.0, // 8
  -0.195090322016128,
  -0.382683432365090,
  -0.555570233019602,
  -0.707106781186547,
  -0.831469612302545,
  -0.923879532511287,
  -0.980785280403230,
  -1.0, // 16
  -0.980785280403230,
  -0.923879532511287,
  -0.831469612302545,
  -0.707106781186548,
  -0.555570233019602,
  -0.382683432365090,
  -0.195090322016129,
  -0.0, // 24
  0.195090322016128,
  0.382683432365090,
  0.555570233019602,
  0.707106781186547,
  0.831469612302545,
  0.923879532511287,
  0.980785280403230 // 31, 32 (after this index) loops back to the start
};

void naive(int input[8][8], int output[8][8]) {
  int u, v, i, j;
  for (u = 0; u < 8; u++) {
    double Cu = (u == 0 ? INV_SQRT2 : 1)/2;

    for (v = 0; v < 8; v++) {
      double Cv = (v == 0 ? INV_SQRT2 : 1)/2;
      
      double outer_sum = 0;
      for (i = 0; i < 8; i++) {
        double inner_sum = 0;

        for (j = 0; j < 8; j++) {
          inner_sum += input[i][j] * cosine[(2*i+1)*u%32] * cosine[(2*j+1)*v%32];
        }

        outer_sum += inner_sum;
      }
      output[u][v] = Cu * Cv * outer_sum;
    }
  }
}
