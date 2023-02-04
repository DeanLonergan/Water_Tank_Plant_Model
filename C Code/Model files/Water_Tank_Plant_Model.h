/*
 * Water_Tank_Plant_Model.h
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

#ifndef RTW_HEADER_Water_Tank_Plant_Model_h_
#define RTW_HEADER_Water_Tank_Plant_Model_h_
#ifndef Water_Tank_Plant_Model_COMMON_INCLUDES_
#define Water_Tank_Plant_Model_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                             /* Water_Tank_Plant_Model_COMMON_INCLUDES_ */

#include "Water_Tank_Plant_Model_types.h"
#include <float.h>
#include <math.h>
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T TransportDelay;               /* '<Root>/Transport Delay' */
  real_T IntegralGain;                 /* '<S32>/Integral Gain' */
  real_T FilterCoefficient;            /* '<S38>/Filter Coefficient' */
  real_T Sum;                          /* '<S3>/Sum' */
  real_T Hin;                          /* '<Root>/Stateflow' */
} B_Water_Tank_Plant_Model_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay_RWORK;              /* '<Root>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<Root>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<Root>/Transport Delay' */

  uint8_T is_Operating;                /* '<Root>/Stateflow' */
  uint8_T is_Fill;                     /* '<Root>/Stateflow' */
  uint8_T is_Boost;                    /* '<Root>/Stateflow' */
  uint8_T is_active_c1_Water_Tank_Plant_M;/* '<Root>/Stateflow' */
  uint8_T temporalCounter_i1;          /* '<Root>/Stateflow' */
  uint8_T temporalCounter_i2;          /* '<Root>/Stateflow' */
} DW_Water_Tank_Plant_Model_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Filter_CSTATE;                /* '<S30>/Filter' */
  real_T Integrator_CSTATE;            /* '<S35>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S3>/Integrator' */
} X_Water_Tank_Plant_Model_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Filter_CSTATE;                /* '<S30>/Filter' */
  real_T Integrator_CSTATE;            /* '<S35>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S3>/Integrator' */
} XDot_Water_Tank_Plant_Model_T;

/* State disabled  */
typedef struct {
  boolean_T Filter_CSTATE;             /* '<S30>/Filter' */
  boolean_T Integrator_CSTATE;         /* '<S35>/Integrator' */
  boolean_T Integrator_CSTATE_c;       /* '<S3>/Integrator' */
} XDis_Water_Tank_Plant_Model_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_Water_Tank_Plant_Mode_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_Water_Tank_Plant_Model_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_Water_Tank_Plant_Model_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[3];
  real_T odeF[3][3];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_Water_Tank_Plant_Model_T Water_Tank_Plant_Model_B;

/* Continuous states (default storage) */
extern X_Water_Tank_Plant_Model_T Water_Tank_Plant_Model_X;

/* Block states (default storage) */
extern DW_Water_Tank_Plant_Model_T Water_Tank_Plant_Model_DW;

/* Model entry point functions */
extern void Water_Tank_Plant_Model_initialize(void);
extern void Water_Tank_Plant_Model_step(void);
extern void Water_Tank_Plant_Model_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Water_Tank_Plant_Mod_T *const Water_Tank_Plant_Model_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Height (output)' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Water_Tank_Plant_Model'
 * '<S1>'   : 'Water_Tank_Plant_Model/PID Controller'
 * '<S2>'   : 'Water_Tank_Plant_Model/Stateflow'
 * '<S3>'   : 'Water_Tank_Plant_Model/Water Tank'
 * '<S4>'   : 'Water_Tank_Plant_Model/PID Controller/Anti-windup'
 * '<S5>'   : 'Water_Tank_Plant_Model/PID Controller/D Gain'
 * '<S6>'   : 'Water_Tank_Plant_Model/PID Controller/Filter'
 * '<S7>'   : 'Water_Tank_Plant_Model/PID Controller/Filter ICs'
 * '<S8>'   : 'Water_Tank_Plant_Model/PID Controller/I Gain'
 * '<S9>'   : 'Water_Tank_Plant_Model/PID Controller/Ideal P Gain'
 * '<S10>'  : 'Water_Tank_Plant_Model/PID Controller/Ideal P Gain Fdbk'
 * '<S11>'  : 'Water_Tank_Plant_Model/PID Controller/Integrator'
 * '<S12>'  : 'Water_Tank_Plant_Model/PID Controller/Integrator ICs'
 * '<S13>'  : 'Water_Tank_Plant_Model/PID Controller/N Copy'
 * '<S14>'  : 'Water_Tank_Plant_Model/PID Controller/N Gain'
 * '<S15>'  : 'Water_Tank_Plant_Model/PID Controller/P Copy'
 * '<S16>'  : 'Water_Tank_Plant_Model/PID Controller/Parallel P Gain'
 * '<S17>'  : 'Water_Tank_Plant_Model/PID Controller/Reset Signal'
 * '<S18>'  : 'Water_Tank_Plant_Model/PID Controller/Saturation'
 * '<S19>'  : 'Water_Tank_Plant_Model/PID Controller/Saturation Fdbk'
 * '<S20>'  : 'Water_Tank_Plant_Model/PID Controller/Sum'
 * '<S21>'  : 'Water_Tank_Plant_Model/PID Controller/Sum Fdbk'
 * '<S22>'  : 'Water_Tank_Plant_Model/PID Controller/Tracking Mode'
 * '<S23>'  : 'Water_Tank_Plant_Model/PID Controller/Tracking Mode Sum'
 * '<S24>'  : 'Water_Tank_Plant_Model/PID Controller/Tsamp - Integral'
 * '<S25>'  : 'Water_Tank_Plant_Model/PID Controller/Tsamp - Ngain'
 * '<S26>'  : 'Water_Tank_Plant_Model/PID Controller/postSat Signal'
 * '<S27>'  : 'Water_Tank_Plant_Model/PID Controller/preSat Signal'
 * '<S28>'  : 'Water_Tank_Plant_Model/PID Controller/Anti-windup/Passthrough'
 * '<S29>'  : 'Water_Tank_Plant_Model/PID Controller/D Gain/Internal Parameters'
 * '<S30>'  : 'Water_Tank_Plant_Model/PID Controller/Filter/Cont. Filter'
 * '<S31>'  : 'Water_Tank_Plant_Model/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S32>'  : 'Water_Tank_Plant_Model/PID Controller/I Gain/Internal Parameters'
 * '<S33>'  : 'Water_Tank_Plant_Model/PID Controller/Ideal P Gain/Passthrough'
 * '<S34>'  : 'Water_Tank_Plant_Model/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S35>'  : 'Water_Tank_Plant_Model/PID Controller/Integrator/Continuous'
 * '<S36>'  : 'Water_Tank_Plant_Model/PID Controller/Integrator ICs/Internal IC'
 * '<S37>'  : 'Water_Tank_Plant_Model/PID Controller/N Copy/Disabled'
 * '<S38>'  : 'Water_Tank_Plant_Model/PID Controller/N Gain/Internal Parameters'
 * '<S39>'  : 'Water_Tank_Plant_Model/PID Controller/P Copy/Disabled'
 * '<S40>'  : 'Water_Tank_Plant_Model/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S41>'  : 'Water_Tank_Plant_Model/PID Controller/Reset Signal/Disabled'
 * '<S42>'  : 'Water_Tank_Plant_Model/PID Controller/Saturation/Enabled'
 * '<S43>'  : 'Water_Tank_Plant_Model/PID Controller/Saturation Fdbk/Disabled'
 * '<S44>'  : 'Water_Tank_Plant_Model/PID Controller/Sum/Sum_PID'
 * '<S45>'  : 'Water_Tank_Plant_Model/PID Controller/Sum Fdbk/Disabled'
 * '<S46>'  : 'Water_Tank_Plant_Model/PID Controller/Tracking Mode/Disabled'
 * '<S47>'  : 'Water_Tank_Plant_Model/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S48>'  : 'Water_Tank_Plant_Model/PID Controller/Tsamp - Integral/Passthrough'
 * '<S49>'  : 'Water_Tank_Plant_Model/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S50>'  : 'Water_Tank_Plant_Model/PID Controller/postSat Signal/Forward_Path'
 * '<S51>'  : 'Water_Tank_Plant_Model/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                /* RTW_HEADER_Water_Tank_Plant_Model_h_ */
