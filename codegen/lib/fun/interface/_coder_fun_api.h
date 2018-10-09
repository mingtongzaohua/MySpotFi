/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_fun_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 09-Oct-2018 16:01:58
 */

#ifndef _CODER_FUN_API_H
#define _CODER_FUN_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_fun_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real_T fun(real_T x, real_T y);
extern void fun_api(const mxArray * const prhs[2], int32_T nlhs, const mxArray
                    *plhs[1]);
extern void fun_atexit(void);
extern void fun_initialize(void);
extern void fun_terminate(void);
extern void fun_xil_terminate(void);

#endif

/*
 * File trailer for _coder_fun_api.h
 *
 * [EOF]
 */
