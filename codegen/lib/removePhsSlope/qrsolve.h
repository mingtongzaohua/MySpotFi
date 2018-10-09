/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qrsolve.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 09-Oct-2018 10:54:42
 */

#ifndef QRSOLVE_H
#define QRSOLVE_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "removePhsSlope_types.h"

/* Function Declarations */
extern void LSQFromQR(const double A_data[], const double tau_data[], const int
                      jpvt[2], double B[90], int rankA, double Y[2]);
extern int rankFromQR(const double A_data[]);

#endif

/*
 * File trailer for qrsolve.h
 *
 * [EOF]
 */
