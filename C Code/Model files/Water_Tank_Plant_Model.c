/*
 * Water_Tank_Plant_Model.c
 *
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * Code generation for model "Water_Tank_Plant_Model".
 *
 * Model version              : 1.70
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Sat Feb  4 21:48:03 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "Water_Tank_Plant_Model.h"
#include "rtwtypes.h"
#include "Water_Tank_Plant_Model_private.h"
#include <string.h>

/* Named constants for Chart: '<Root>/Stateflow' */
#define Water_Tank_P_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define Water_Tank_Plant_Model_IN_Empty ((uint8_T)1U)
#define Water_Tank_Plant_Model_IN_Fill ((uint8_T)2U)
#define Water_Tank_Plant_Model_IN_High ((uint8_T)1U)
#define Water_Tank_Plant_Model_IN_Low  ((uint8_T)2U)
#define Water_Tank_Plant_Model_IN_Off  ((uint8_T)1U)

/* Block signals (default storage) */
B_Water_Tank_Plant_Model_T Water_Tank_Plant_Model_B;

/* Continuous states */
X_Water_Tank_Plant_Model_T Water_Tank_Plant_Model_X;

/* Block states (default storage) */
DW_Water_Tank_Plant_Model_T Water_Tank_Plant_Model_DW;

/* Real-time model */
static RT_MODEL_Water_Tank_Plant_Mod_T Water_Tank_Plant_Model_M_;
RT_MODEL_Water_Tank_Plant_Mod_T *const Water_Tank_Plant_Model_M =
  &Water_Tank_Plant_Model_M_;

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 * (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 * (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                 /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;
  real_T* tBuf = uBuf + bufSz;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Water_Tank_Plant_Model_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Water_Tank_Plant_Model_step();
  Water_Tank_Plant_Model_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Water_Tank_Plant_Model_step();
  Water_Tank_Plant_Model_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Water_Tank_Plant_Model_step(void)
{
  /* local block i/o variables */
  real_T rtb_Integrator;
  real_T rtb_Sum;
  if (rtmIsMajorTimeStep(Water_Tank_Plant_Model_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&Water_Tank_Plant_Model_M->solverInfo,
                          ((Water_Tank_Plant_Model_M->Timing.clockTick0+1)*
      Water_Tank_Plant_Model_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Water_Tank_Plant_Model_M)) {
    Water_Tank_Plant_Model_M->Timing.t[0] = rtsiGetT
      (&Water_Tank_Plant_Model_M->solverInfo);
  }

  /* TransportDelay: '<Root>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &Water_Tank_Plant_Model_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T simTime = Water_Tank_Plant_Model_M->Timing.t[0];
    real_T tMinusDelay = simTime - 0.05;
    Water_Tank_Plant_Model_B.TransportDelay = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *uBuffer,
      Water_Tank_Plant_Model_DW.TransportDelay_IWORK.CircularBufSize,
      &Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Last,
      Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Tail,
      Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  if (rtmIsMajorTimeStep(Water_Tank_Plant_Model_M)) {
    /* Chart: '<Root>/Stateflow' */
    if (Water_Tank_Plant_Model_DW.temporalCounter_i1 < 31U) {
      Water_Tank_Plant_Model_DW.temporalCounter_i1++;
    }

    if (Water_Tank_Plant_Model_DW.temporalCounter_i2 < 63U) {
      Water_Tank_Plant_Model_DW.temporalCounter_i2++;
    }

    if (Water_Tank_Plant_Model_DW.is_active_c1_Water_Tank_Plant_M == 0U) {
      Water_Tank_Plant_Model_DW.is_active_c1_Water_Tank_Plant_M = 1U;
      Water_Tank_Plant_Model_DW.is_Operating = Water_Tank_Plant_Model_IN_Empty;
      Water_Tank_Plant_Model_B.Hin = 0.0;
      Water_Tank_Plant_Model_DW.is_Boost = Water_Tank_Plant_Model_IN_Off;
    } else {
      switch (Water_Tank_Plant_Model_DW.is_Operating) {
       case Water_Tank_Plant_Model_IN_Empty:
        if (Water_Tank_Plant_Model_B.TransportDelay < 0.01) {
          Water_Tank_Plant_Model_DW.is_Operating =
            Water_Tank_Plant_Model_IN_Fill;
          Water_Tank_Plant_Model_DW.is_Fill = Water_Tank_Plant_Model_IN_Low;
          Water_Tank_Plant_Model_B.Hin = 2.0;
        } else {
          Water_Tank_Plant_Model_B.Hin = 0.0;
        }
        break;

       case Water_Tank_Plant_Model_IN_Fill:
        switch (Water_Tank_Plant_Model_DW.is_Fill) {
         case Water_Tank_Plant_Model_IN_High:
          Water_Tank_Plant_Model_B.Hin = 16.0;
          break;

         case Water_Tank_Plant_Model_IN_Low:
          Water_Tank_Plant_Model_DW.is_Fill = Water_Tank_Plant_Model_IN_High;
          Water_Tank_Plant_Model_B.Hin = 16.0;
          break;

         default:
          /* case IN_Med: */
          Water_Tank_Plant_Model_DW.is_Fill = Water_Tank_Plant_Model_IN_High;
          Water_Tank_Plant_Model_B.Hin = 16.0;
          break;
        }
        break;

       default:
        /* case IN_Hold: */
        Water_Tank_Plant_Model_DW.is_Operating = Water_Tank_Plant_Model_IN_Fill;
        Water_Tank_Plant_Model_DW.is_Fill = Water_Tank_Plant_Model_IN_Low;
        Water_Tank_Plant_Model_B.Hin = 2.0;
        break;
      }

      if (Water_Tank_Plant_Model_DW.is_Boost != Water_Tank_Plant_Model_IN_Off) {
        /* case IN_On: */
        if (Water_Tank_Plant_Model_DW.temporalCounter_i2 >= 50U) {
          Water_Tank_Plant_Model_DW.is_Boost = Water_Tank_Plant_Model_IN_Off;
        } else {
          Water_Tank_Plant_Model_B.Hin += Water_Tank_Plant_Model_B.Hin * 0.1;
        }
      }
    }

    /* End of Chart: '<Root>/Stateflow' */
  }

  /* Sum: '<Root>/Sum' */
  rtb_Sum = Water_Tank_Plant_Model_B.Hin -
    Water_Tank_Plant_Model_B.TransportDelay;

  /* Gain: '<S32>/Integral Gain' */
  Water_Tank_Plant_Model_B.IntegralGain = 0.92 * rtb_Sum;

  /* Gain: '<S38>/Filter Coefficient' incorporates:
   *  Gain: '<S29>/Derivative Gain'
   *  Integrator: '<S30>/Filter'
   *  Sum: '<S30>/SumD'
   */
  Water_Tank_Plant_Model_B.FilterCoefficient = (0.29 * rtb_Sum -
    Water_Tank_Plant_Model_X.Filter_CSTATE) * 0.0;

  /* Integrator: '<S3>/Integrator' */
  rtb_Integrator = Water_Tank_Plant_Model_X.Integrator_CSTATE_c;

  /* Sum: '<S44>/Sum' incorporates:
   *  Gain: '<S40>/Proportional Gain'
   *  Integrator: '<S35>/Integrator'
   */
  rtb_Sum = (7.2 * rtb_Sum + Water_Tank_Plant_Model_X.Integrator_CSTATE) +
    Water_Tank_Plant_Model_B.FilterCoefficient;

  /* Saturate: '<S42>/Saturation' */
  if (rtb_Sum > 50.0) {
    rtb_Sum = 50.0;
  } else if (rtb_Sum < -0.0) {
    rtb_Sum = -0.0;
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/1//A'
   *  Product: '<S3>/(1//A)*Qin(t)'
   *  Product: '<S3>/(1//RA)*h(t)'
   *  Saturate: '<S42>/Saturation'
   */
  Water_Tank_Plant_Model_B.Sum = rtb_Sum * 0.125 - 0.125 * rtb_Integrator;
  if (rtmIsMajorTimeStep(Water_Tank_Plant_Model_M)) {
    /* Update for TransportDelay: '<Root>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)
        &Water_Tank_Plant_Model_DW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T simTime = Water_Tank_Plant_Model_M->Timing.t[0];
      Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Head =
        ((Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Head <
          (Water_Tank_Plant_Model_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Head+1) : 0);
      if (Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Head ==
          Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Tail) {
        Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Tail =
          ((Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Tail <
            (Water_Tank_Plant_Model_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
           (Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*uBuffer + Water_Tank_Plant_Model_DW.TransportDelay_IWORK.CircularBufSize)
        [Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Head] =
        rtb_Integrator;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Water_Tank_Plant_Model_M)) {
    rt_ertODEUpdateContinuousStates(&Water_Tank_Plant_Model_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++Water_Tank_Plant_Model_M->Timing.clockTick0;
    Water_Tank_Plant_Model_M->Timing.t[0] = rtsiGetSolverStopTime
      (&Water_Tank_Plant_Model_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      Water_Tank_Plant_Model_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Water_Tank_Plant_Model_derivatives(void)
{
  XDot_Water_Tank_Plant_Model_T *_rtXdot;
  _rtXdot = ((XDot_Water_Tank_Plant_Model_T *) Water_Tank_Plant_Model_M->derivs);

  /* Derivatives for Integrator: '<S30>/Filter' */
  _rtXdot->Filter_CSTATE = Water_Tank_Plant_Model_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S35>/Integrator' */
  _rtXdot->Integrator_CSTATE = Water_Tank_Plant_Model_B.IntegralGain;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE_c = Water_Tank_Plant_Model_B.Sum;
}

/* Model initialize function */
void Water_Tank_Plant_Model_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Water_Tank_Plant_Model_M, 0,
                sizeof(RT_MODEL_Water_Tank_Plant_Mod_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Water_Tank_Plant_Model_M->solverInfo,
                          &Water_Tank_Plant_Model_M->Timing.simTimeStep);
    rtsiSetTPtr(&Water_Tank_Plant_Model_M->solverInfo, &rtmGetTPtr
                (Water_Tank_Plant_Model_M));
    rtsiSetStepSizePtr(&Water_Tank_Plant_Model_M->solverInfo,
                       &Water_Tank_Plant_Model_M->Timing.stepSize0);
    rtsiSetdXPtr(&Water_Tank_Plant_Model_M->solverInfo,
                 &Water_Tank_Plant_Model_M->derivs);
    rtsiSetContStatesPtr(&Water_Tank_Plant_Model_M->solverInfo, (real_T **)
                         &Water_Tank_Plant_Model_M->contStates);
    rtsiSetNumContStatesPtr(&Water_Tank_Plant_Model_M->solverInfo,
      &Water_Tank_Plant_Model_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Water_Tank_Plant_Model_M->solverInfo,
      &Water_Tank_Plant_Model_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Water_Tank_Plant_Model_M->solverInfo,
      &Water_Tank_Plant_Model_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Water_Tank_Plant_Model_M->solverInfo,
      &Water_Tank_Plant_Model_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Water_Tank_Plant_Model_M->solverInfo,
                          (&rtmGetErrorStatus(Water_Tank_Plant_Model_M)));
    rtsiSetRTModelPtr(&Water_Tank_Plant_Model_M->solverInfo,
                      Water_Tank_Plant_Model_M);
  }

  rtsiSetSimTimeStep(&Water_Tank_Plant_Model_M->solverInfo, MAJOR_TIME_STEP);
  Water_Tank_Plant_Model_M->intgData.y = Water_Tank_Plant_Model_M->odeY;
  Water_Tank_Plant_Model_M->intgData.f[0] = Water_Tank_Plant_Model_M->odeF[0];
  Water_Tank_Plant_Model_M->intgData.f[1] = Water_Tank_Plant_Model_M->odeF[1];
  Water_Tank_Plant_Model_M->intgData.f[2] = Water_Tank_Plant_Model_M->odeF[2];
  Water_Tank_Plant_Model_M->contStates = ((X_Water_Tank_Plant_Model_T *)
    &Water_Tank_Plant_Model_X);
  rtsiSetSolverData(&Water_Tank_Plant_Model_M->solverInfo, (void *)
                    &Water_Tank_Plant_Model_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&Water_Tank_Plant_Model_M->solverInfo,
    false);
  rtsiSetSolverName(&Water_Tank_Plant_Model_M->solverInfo,"ode3");
  rtmSetTPtr(Water_Tank_Plant_Model_M, &Water_Tank_Plant_Model_M->Timing.tArray
             [0]);
  Water_Tank_Plant_Model_M->Timing.stepSize0 = 0.2;

  /* block I/O */
  (void) memset(((void *) &Water_Tank_Plant_Model_B), 0,
                sizeof(B_Water_Tank_Plant_Model_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Water_Tank_Plant_Model_X, 0,
                  sizeof(X_Water_Tank_Plant_Model_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Water_Tank_Plant_Model_DW, 0,
                sizeof(DW_Water_Tank_Plant_Model_T));

  /* Start for TransportDelay: '<Root>/Transport Delay' */
  {
    real_T *pBuffer =
      &Water_Tank_Plant_Model_DW.TransportDelay_RWORK.TUbufferArea[0];
    Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Tail = 0;
    Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Head = 0;
    Water_Tank_Plant_Model_DW.TransportDelay_IWORK.Last = 0;
    Water_Tank_Plant_Model_DW.TransportDelay_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = Water_Tank_Plant_Model_M->Timing.t[0];
    Water_Tank_Plant_Model_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
  }

  /* InitializeConditions for Integrator: '<S30>/Filter' */
  Water_Tank_Plant_Model_X.Filter_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S35>/Integrator' */
  Water_Tank_Plant_Model_X.Integrator_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  Water_Tank_Plant_Model_X.Integrator_CSTATE_c = 0.0;

  /* SystemInitialize for Chart: '<Root>/Stateflow' */
  Water_Tank_Plant_Model_DW.is_Boost = Water_Tank_P_IN_NO_ACTIVE_CHILD;
  Water_Tank_Plant_Model_DW.temporalCounter_i2 = 0U;
  Water_Tank_Plant_Model_DW.is_Operating = Water_Tank_P_IN_NO_ACTIVE_CHILD;
  Water_Tank_Plant_Model_DW.is_Fill = Water_Tank_P_IN_NO_ACTIVE_CHILD;
  Water_Tank_Plant_Model_DW.temporalCounter_i1 = 0U;
  Water_Tank_Plant_Model_DW.is_active_c1_Water_Tank_Plant_M = 0U;
  Water_Tank_Plant_Model_B.Hin = 0.0;
}

/* Model terminate function */
void Water_Tank_Plant_Model_terminate(void)
{
  /* (no terminate code required) */
}
