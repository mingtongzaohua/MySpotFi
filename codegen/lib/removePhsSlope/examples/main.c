/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 09-Oct-2018 10:54:42
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "removePhsSlope.h"
#include "main.h"
#include "removePhsSlope_terminate.h"
#include "removePhsSlope_initialize.h"

/* Function Declarations */
static void argInit_1x30_real_T(double result[30]);
static void argInit_30x3_creal_T(creal_T result[90]);
static creal_T argInit_creal_T(void);
static double argInit_real_T(void);
static void main_removePhsSlope(void);

/* Function Definitions */

/*
 * Arguments    : double result[30]
 * Return Type  : void
 */
static void argInit_1x30_real_T(double result[30])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 30; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_real_T();
  }
}

/*
 * Arguments    : creal_T result[90]
 * Return Type  : void
 */
static void argInit_30x3_creal_T(creal_T result[90])
{
  int idx0;
  creal_T result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 30; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_creal_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 30] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 60] = argInit_creal_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : creal_T
 */
static creal_T argInit_creal_T(void)
{
  creal_T result;
  double result_tmp;

  /* Set the value of the complex variable.
     Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result.re = result_tmp;
  result.im = result_tmp;
  return result;
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_removePhsSlope(void)
{
  creal_T dcv0[90];
  double dv0[30];
  double PhsSlope;
  double PhsCons;

  /* Initialize function 'removePhsSlope' input arguments. */
  /* Initialize function input argument 'vna_response'. */
  /* Initialize function input argument 'SubCarrInd'. */
  /* Call the entry-point 'removePhsSlope'. */
  argInit_30x3_creal_T(dcv0);
  argInit_1x30_real_T(dv0);
  removePhsSlope(dcv0, argInit_real_T(), dv0, argInit_real_T(), &PhsSlope,
                 &PhsCons);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  removePhsSlope_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_removePhsSlope();

  /* Terminate the application.
     You do not need to do this more than one time. */
  removePhsSlope_terminate();
    
    printf("按任意键继续……");
    getchar();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
