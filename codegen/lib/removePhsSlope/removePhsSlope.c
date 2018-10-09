/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: removePhsSlope.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 09-Oct-2018 10:54:42
 */

/* Include Files */
#include <float.h>
#include <math.h>
#include "removePhsSlope.h"
#include "removePhsSlope_emxutil.h"
#include "mldivide.h"

/* Function Declarations */
static double rt_remd(double u0, double u1);
static double rt_roundd(double u);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_remd(double u0, double u1)
{
  double y;
  double q;
  if ((u1 != 0.0) && (u1 != trunc(u1))) {
    q = fabs(u0 / u1);
    if (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q) {
      y = 0.0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }

  return y;
}

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : const creal_T vna_response[90]
 *                double M
 *                const double SubCarrInd[30]
 *                double N
 *                double *PhsSlope
 *                double *PhsCons
 * Return Type  : void
 */
void removePhsSlope(const creal_T vna_response[90], double M, const double
                    SubCarrInd[30], double N, double *PhsSlope, double *PhsCons)
{
  int k;
  int i2;
  double PhsRelFirstPac[90];
  int i;
  int i1;
  int ip;
  double cumsum_dp_corr;
  double vwork[30];
  emxArray_real_T *b;
  double pkm1;
  int exitg1;
  emxArray_int8_T *varargin_2;
  double dp_corr;
  emxArray_real_T *b_b;
  double x[2];
  for (k = 0; k < 90; k++) {
    PhsRelFirstPac[k] = atan2(vna_response[k].im, vna_response[k].re);
  }

  i2 = 1;
  for (i = 0; i < 3; i++) {
    i1 = i2;
    i2 += 30;
    ip = i1;
    for (k = 0; k < 30; k++) {
      vwork[k] = PhsRelFirstPac[ip - 1];
      ip++;
    }

    cumsum_dp_corr = 0.0;
    k = 0;
    pkm1 = vwork[0];
    do {
      exitg1 = 0;
      k++;
      if (k + 1 > 30) {
        exitg1 = 1;
      } else {
        pkm1 = vwork[k] - pkm1;
        dp_corr = pkm1 / 6.2831853071795862;
        if (fabs(rt_remd(dp_corr, 1.0)) <= 0.5) {
          dp_corr = trunc(dp_corr);
        } else {
          dp_corr = rt_roundd(dp_corr);
        }

        if (fabs(pkm1) >= 3.1415926535897931) {
          cumsum_dp_corr += dp_corr;
        }

        pkm1 = vwork[k];
        vwork[k] -= 6.2831853071795862 * cumsum_dp_corr;
      }
    } while (exitg1 == 0);

    ip = i1;
    for (k = 0; k < 30; k++) {
      PhsRelFirstPac[ip - 1] = vwork[k];
      ip++;
    }
  }

  /*  angle提取相位角,复数数组vna_response 的每个元素返回相位角（以弧度为单位）。此角度介于 ±π 之间。 */
  /*  unwrap 解卷绕，使相位在pi处不发生跳变，从而反应出真实的相位变化,通过在向量 P 中增加 ±2π 的倍数来更正弧度相位角 */
  /*  % Below code is for when you are using phase relative to */
  /*  % the first packet. */
  ip = (int)M;
  for (i2 = 0; i2 < ip; i2++) {
    pkm1 = PhsRelFirstPac[30 * i2] - PhsRelFirstPac[0];
    if (pkm1 > 3.1415926535897931) {
      for (i1 = 0; i1 < 30; i1++) {
        i = i1 + 30 * i2;
        PhsRelFirstPac[i] -= 6.2831853071795862;
      }

      /*  满足条件后此列所有元素都进行了这样的处理 */
    } else {
      if (pkm1 < -3.1415926535897931) {
        for (i1 = 0; i1 < 30; i1++) {
          i = i1 + 30 * i2;
          PhsRelFirstPac[i] += 6.2831853071795862;
        }
      }
    }
  }

  emxInit_real_T(&b, 1);
  i1 = b->size[0];
  b->size[0] = 30 * ip;
  emxEnsureCapacity_real_T(b, i1);
  for (i2 = 0; i2 < ip; i2++) {
    i1 = i2 * 30;
    for (k = 0; k < 30; k++) {
      b->data[i1 + k] = SubCarrInd[k];
    }
  }

  emxInit_int8_T(&varargin_2, 1);
  ip = varargin_2->size[0];
  i2 = (int)(N * M);
  varargin_2->size[0] = i2;
  emxEnsureCapacity_int8_T(varargin_2, ip);
  for (ip = 0; ip < i2; ip++) {
    varargin_2->data[ip] = 1;
  }

  emxInit_real_T(&b_b, 2);
  ip = b_b->size[0] * b_b->size[1];
  b_b->size[0] = b->size[0];
  b_b->size[1] = 2;
  emxEnsureCapacity_real_T(b_b, ip);
  i2 = b->size[0];
  for (ip = 0; ip < i2; ip++) {
    b_b->data[ip] = b->data[ip];
  }

  emxFree_real_T(&b);
  i2 = varargin_2->size[0];
  for (ip = 0; ip < i2; ip++) {
    b_b->data[ip + b_b->size[0]] = varargin_2->data[ip];
  }

  emxFree_int8_T(&varargin_2);
  mldivide(b_b, PhsRelFirstPac, x);

  /* 则相当于inv（A）*B，意思就是A左除B,相当于A的逆矩阵左乘B。 */
  /* x = A\B 是方程 Ax = B 的解。矩阵 A 和 B 必须拥有相同的行数。 */
  /* PhsRelFirstPac(:) */
  /* 按照列展开为90*1，1234-1324 */
  *PhsSlope = x[0];
  *PhsCons = x[1];

  /* x为2阶矩阵 */
  /*      sprintf('estimation error is %f', norm(PhsRelFirstPac(:) - A*x)/length(PhsRelFirstPac(:))) */
  /*      figure(100); plot(PhsRelFirstPac(:) - A*x); hold on; */
  /*      % % % % % % % % Removing exact slope */
  /*              cvx_begin quiet */
  /*                  variable PhsSlope */
  /*                  variable PhsCons */
  /*          %         PhsRelFirstPac = exp(1i*angle(csi_plot))./phaseFirstPac; */
  /*                  PhsRelFirstPac = unwrap(angle(vna_response)); */
  /*                  % % Below code is for when you are using phase relative to */
  /*                  % % the first packet. */
  /*                  for antIdForPhs = 1:M */
  /*                      if  PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) > pi */
  /*                          PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) - 2*pi; */
  /*                      elseif PhsRelFirstPac(1,antIdForPhs) - PhsRelFirstPac(1,1) < -pi */
  /*                          PhsRelFirstPac(:,antIdForPhs) = PhsRelFirstPac(:,antIdForPhs) + 2*pi; */
  /*                      end */
  /*                  end */
  /*                  minimize( norm( PhsRelFirstPac - PhsSlope*repmat(SubCarrInd(:),1,M) - PhsCons*ones(N,M), 'fro' ) ) */
  /*              cvx_end */
  /*              PhsSlope */
  /*              PhsCons */
  emxFree_real_T(&b_b);
}

/*
 * File trailer for removePhsSlope.c
 *
 * [EOF]
 */
