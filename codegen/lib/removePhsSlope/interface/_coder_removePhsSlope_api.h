/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_removePhsSlope_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 09-Oct-2018 10:54:42
 */

#ifndef _CODER_REMOVEPHSSLOPE_API_H
#define _CODER_REMOVEPHSSLOPE_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_removePhsSlope_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void removePhsSlope(creal_T vna_response[90], real_T M, real_T
  SubCarrInd[30], real_T N, real_T *PhsSlope, real_T *PhsCons);
extern void removePhsSlope_api(const mxArray * const prhs[4], int32_T nlhs,
  const mxArray *plhs[2]);
extern void removePhsSlope_atexit(void);
extern void removePhsSlope_initialize(void);
extern void removePhsSlope_terminate(void);
extern void removePhsSlope_xil_terminate(void);

#endif

/*
 * File trailer for _coder_removePhsSlope_api.h
 *
 * [EOF]
 */
