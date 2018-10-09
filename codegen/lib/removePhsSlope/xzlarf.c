/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzlarf.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 09-Oct-2018 10:54:42
 */

/* Include Files */
#include "removePhsSlope.h"
#include "xzlarf.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                double tau
 *                double C_data[]
 *                double work[2]
 * Return Type  : void
 */
void xzlarf(int m, int n, int iv0, double tau, double C_data[], double work[2])
{
  int lastv;
  int lastc;
  int i;
  boolean_T exitg2;
  int i0;
  int ix;
  int jy;
  double c;
  int j;
  int exitg1;
  int i1;
  int ijA;
  if (tau != 0.0) {
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && (C_data[i - 2] == 0.0)) {
      lastv--;
      i--;
    }

    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      i = 91;
      do {
        exitg1 = 0;
        if (i <= lastv + 90) {
          if (C_data[i - 1] != 0.0) {
            exitg1 = 1;
          } else {
            i++;
          }
        } else {
          lastc = 0;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      work[0] = 0.0;
      i0 = lastv + 90;
      ix = iv0;
      c = 0.0;
      for (i = 91; i <= i0; i++) {
        c += C_data[i - 1] * C_data[ix - 1];
        ix++;
      }

      work[0] += c;
    }

    if (-tau != 0.0) {
      i = 90;
      jy = 0;
      for (j = 0; j < lastc; j++) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau;
          ix = iv0;
          i0 = i + 1;
          i1 = lastv + i;
          for (ijA = i0; ijA <= i1; ijA++) {
            C_data[ijA - 1] += C_data[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        i += 90;
      }
    }
  }
}

/*
 * File trailer for xzlarf.c
 *
 * [EOF]
 */
