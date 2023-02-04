/*
 * Water_Tank_Plant_Model_private.h
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

#ifndef RTW_HEADER_Water_Tank_Plant_Model_private_h_
#define RTW_HEADER_Water_Tank_Plant_Model_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "Water_Tank_Plant_Model_types.h"
#include "Water_Tank_Plant_Model.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

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
  ;

/* private model entry point functions */
extern void Water_Tank_Plant_Model_derivatives(void);

#endif                        /* RTW_HEADER_Water_Tank_Plant_Model_private_h_ */
