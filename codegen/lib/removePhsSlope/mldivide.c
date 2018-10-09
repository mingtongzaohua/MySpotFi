/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mldivide.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 09-Oct-2018 10:54:42
 */

/* Include Files */
#include <math.h>
#include <string.h>
#include "removePhsSlope.h"
#include "mldivide.h"
#include "qrsolve.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "xswap.h"

/* Function Declarations */
static double rt_hypotd(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/*
 * Arguments    : const emxArray_real_T *A
 *                const double B[90]
 *                double Y[2]
 * Return Type  : void
 */
void mldivide(const emxArray_real_T *A, const double B[90], double Y[2])
{
  int loop_ub;
  int itemp;
  int jpvt[2];
  double A_data[180];
  double work[2];
  double xnorm;
  double scale;
  double vn1[2];
  double absxk;
  double t;
  double tau_data[2];
  double b_B[90];
  loop_ub = A->size[0] * A->size[1];
  for (itemp = 0; itemp < loop_ub; itemp++) {
    A_data[itemp] = A->data[itemp];
  }

  jpvt[0] = 1;
  work[0] = 0.0;
  xnorm = 0.0;
  scale = 3.3121686421112381E-170;
  for (loop_ub = 1; loop_ub < 91; loop_ub++) {
    absxk = fabs(A->data[loop_ub - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      xnorm = 1.0 + xnorm * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      xnorm += t * t;
    }
  }

  vn1[0] = scale * sqrt(xnorm);
  jpvt[1] = 2;
  work[1] = 0.0;
  xnorm = 0.0;
  scale = 3.3121686421112381E-170;
  for (loop_ub = 91; loop_ub < 181; loop_ub++) {
    absxk = fabs(A->data[loop_ub - 1]);
    if (absxk > scale) {
      t = scale / absxk;
      xnorm = 1.0 + xnorm * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      xnorm += t * t;
    }
  }

  loop_ub = 0;
  if (scale * sqrt(xnorm) > vn1[0]) {
    loop_ub = 1;
  }

  if (loop_ub != 0) {
    xswap(A_data, 1 + 90 * loop_ub, 1);
    itemp = jpvt[loop_ub];
    jpvt[loop_ub] = 1;
    jpvt[0] = itemp;
  }

  scale = A_data[0];
  tau_data[0] = 0.0;
  xnorm = xnrm2(89, A_data, 2);
  if (xnorm != 0.0) {
    absxk = rt_hypotd(A_data[0], xnorm);
    if (A_data[0] >= 0.0) {
      absxk = -absxk;
    }

    if (fabs(absxk) < 1.0020841800044864E-292) {
      itemp = -1;
      do {
        itemp++;
        for (loop_ub = 2; loop_ub < 91; loop_ub++) {
          A_data[loop_ub - 1] *= 9.9792015476736E+291;
        }

        absxk *= 9.9792015476736E+291;
        scale *= 9.9792015476736E+291;
      } while (!(fabs(absxk) >= 1.0020841800044864E-292));

      absxk = rt_hypotd(scale, xnrm2(89, A_data, 2));
      if (scale >= 0.0) {
        absxk = -absxk;
      }

      tau_data[0] = (absxk - scale) / absxk;
      xnorm = 1.0 / (scale - absxk);
      for (loop_ub = 2; loop_ub < 91; loop_ub++) {
        A_data[loop_ub - 1] *= xnorm;
      }

      for (loop_ub = 0; loop_ub <= itemp; loop_ub++) {
        absxk *= 1.0020841800044864E-292;
      }

      scale = absxk;
    } else {
      tau_data[0] = (absxk - A_data[0]) / absxk;
      xnorm = 1.0 / (A_data[0] - absxk);
      for (loop_ub = 2; loop_ub < 91; loop_ub++) {
        A_data[loop_ub - 1] *= xnorm;
      }

      scale = absxk;
    }
  }

  A_data[0] = 1.0;
  xzlarf(90, 1, 1, tau_data[0], A_data, work);
  A_data[0] = scale;
  scale = A_data[91];
  tau_data[1] = 0.0;
  xnorm = xnrm2(88, A_data, 93);
  if (xnorm != 0.0) {
    absxk = rt_hypotd(A_data[91], xnorm);
    if (A_data[91] >= 0.0) {
      absxk = -absxk;
    }

    if (fabs(absxk) < 1.0020841800044864E-292) {
      itemp = -1;
      do {
        itemp++;
        for (loop_ub = 93; loop_ub < 181; loop_ub++) {
          A_data[loop_ub - 1] *= 9.9792015476736E+291;
        }

        absxk *= 9.9792015476736E+291;
        scale *= 9.9792015476736E+291;
      } while (!(fabs(absxk) >= 1.0020841800044864E-292));

      absxk = rt_hypotd(scale, xnrm2(88, A_data, 93));
      if (scale >= 0.0) {
        absxk = -absxk;
      }

      tau_data[1] = (absxk - scale) / absxk;
      xnorm = 1.0 / (scale - absxk);
      for (loop_ub = 93; loop_ub < 181; loop_ub++) {
        A_data[loop_ub - 1] *= xnorm;
      }

      for (loop_ub = 0; loop_ub <= itemp; loop_ub++) {
        absxk *= 1.0020841800044864E-292;
      }

      scale = absxk;
    } else {
      tau_data[1] = (absxk - A_data[91]) / absxk;
      xnorm = 1.0 / (A_data[91] - absxk);
      for (loop_ub = 93; loop_ub < 181; loop_ub++) {
        A_data[loop_ub - 1] *= xnorm;
      }

      scale = absxk;
    }
  }

  A_data[91] = scale;
  memcpy(&b_B[0], &B[0], 90U * sizeof(double));
  LSQFromQR(A_data, tau_data, jpvt, b_B, rankFromQR(A_data), Y);
}

/*
 * File trailer for mldivide.c
 *
 * [EOF]
 */
