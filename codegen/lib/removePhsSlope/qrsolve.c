/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qrsolve.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 09-Oct-2018 10:54:42
 */

/* Include Files */
#include <math.h>
#include "removePhsSlope.h"
#include "qrsolve.h"

/* Function Definitions */

/*
 * Arguments    : const double A_data[]
 *                const double tau_data[]
 *                const int jpvt[2]
 *                double B[90]
 *                int rankA
 *                double Y[2]
 * Return Type  : void
 */
void LSQFromQR(const double A_data[], const double tau_data[], const int jpvt[2],
               double B[90], int rankA, double Y[2])
{
  double wj;
  int i;
  int j;
  int Y_tmp;
  int b_Y_tmp;
  Y[0] = 0.0;
  if (tau_data[0] != 0.0) {
    wj = B[0];
    for (i = 2; i < 91; i++) {
      wj += A_data[i - 1] * B[i - 1];
    }

    wj *= tau_data[0];
    if (wj != 0.0) {
      B[0] -= wj;
      for (i = 2; i < 91; i++) {
        B[i - 1] -= A_data[i - 1] * wj;
      }
    }
  }

  Y[1] = 0.0;
  if (tau_data[1] != 0.0) {
    wj = B[1];
    for (i = 3; i < 91; i++) {
      wj += A_data[i + 89] * B[i - 1];
    }

    wj *= tau_data[1];
    if (wj != 0.0) {
      B[1] -= wj;
      for (i = 3; i < 91; i++) {
        B[i - 1] -= A_data[i + 89] * wj;
      }
    }
  }

  for (i = 0; i < rankA; i++) {
    Y[jpvt[i] - 1] = B[i];
  }

  for (j = rankA; j >= 1; j--) {
    Y_tmp = jpvt[j - 1] - 1;
    b_Y_tmp = 90 * (j - 1);
    Y[Y_tmp] /= A_data[(j + b_Y_tmp) - 1];
    for (i = 0; i <= j - 2; i++) {
      Y[jpvt[0] - 1] -= Y[Y_tmp] * A_data[b_Y_tmp];
    }
  }
}

/*
 * Arguments    : const double A_data[]
 * Return Type  : int
 */
int rankFromQR(const double A_data[])
{
  int r;
  double tol;
  r = 0;
  tol = 1.9984014443252818E-13 * fabs(A_data[0]);
  while ((r < 2) && (fabs(A_data[r + 90 * r]) > tol)) {
    r++;
  }

  return r;
}

/*
 * File trailer for qrsolve.c
 *
 * [EOF]
 */
