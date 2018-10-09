/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: removePhsSlope_emxutil.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 09-Oct-2018 10:54:42
 */

#ifndef REMOVEPHSSLOPE_EMXUTIL_H
#define REMOVEPHSSLOPE_EMXUTIL_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "removePhsSlope_types.h"

/* Function Declarations */
extern void emxEnsureCapacity_int8_T(emxArray_int8_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFree_int8_T(emxArray_int8_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_int8_T(emxArray_int8_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for removePhsSlope_emxutil.h
 *
 * [EOF]
 */
