/*
 * Tanks_Template.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Tanks_Template".
 *
 * Model version              : 17.20
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Tue Mar 17 16:12:41 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Tanks_Template.h"
#include "Tanks_Template_private.h"
#include "Tanks_Template_dt.h"

/* Block signals (default storage) */
B_Tanks_Template_T Tanks_Template_B;

/* Continuous states */
X_Tanks_Template_T Tanks_Template_X;

/* Block states (default storage) */
DW_Tanks_Template_T Tanks_Template_DW;

/* Real-time model */
static RT_MODEL_Tanks_Template_T Tanks_Template_M_;
RT_MODEL_Tanks_Template_T *const Tanks_Template_M = &Tanks_Template_M_;
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Tanks_Template_M->Timing.TaskCounters.TID[2])++;
  if ((Tanks_Template_M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.01s, 0.0s] */
    Tanks_Template_M->Timing.TaskCounters.TID[2] = 0;
  }

  Tanks_Template_M->Timing.sampleHits[2] =
    (Tanks_Template_M->Timing.TaskCounters.TID[2] == 0) ? 1 : 0;
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Tanks_Template_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  Tanks_Template_output();
  Tanks_Template_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  Tanks_Template_output();
  Tanks_Template_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  Tanks_Template_output();
  Tanks_Template_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void Tanks_Template_output(void)
{
  /* local block i/o variables */
  real_T rtb_sensor_tank2;
  real_T rtb_sensor_tank1;
  if (rtmIsMajorTimeStep(Tanks_Template_M)) {
    /* set solver stop time */
    if (!(Tanks_Template_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Tanks_Template_M->solverInfo,
                            ((Tanks_Template_M->Timing.clockTickH0 + 1) *
        Tanks_Template_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Tanks_Template_M->solverInfo,
                            ((Tanks_Template_M->Timing.clockTick0 + 1) *
        Tanks_Template_M->Timing.stepSize0 +
        Tanks_Template_M->Timing.clockTickH0 *
        Tanks_Template_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Tanks_Template_M)) {
    Tanks_Template_M->Timing.t[0] = rtsiGetT(&Tanks_Template_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Tanks_Template_M) &&
      Tanks_Template_M->Timing.TaskCounters.TID[1] == 0) {
    /* Constant: '<Root>/Constant' */
    Tanks_Template_B.Constant = Tanks_Template_P.v_pump;

    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog1' */

    /* S-Function Block: Tanks_Template/HIL Write Analog1 (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(Tanks_Template_DW.HILInitialize_Card,
        &Tanks_Template_P.HILWriteAnalog1_channels, 1,
        &Tanks_Template_B.Constant);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
      }
    }
  }

  if (rtmIsMajorTimeStep(Tanks_Template_M) &&
      Tanks_Template_M->Timing.TaskCounters.TID[2] == 0) {
    /* S-Function (hil_read_analog_block): '<Root>/HIL Read Analog1' */

    /* S-Function Block: Tanks_Template/HIL Read Analog1 (hil_read_analog_block) */
    {
      t_error result = hil_read_analog(Tanks_Template_DW.HILInitialize_Card,
        Tanks_Template_P.HILReadAnalog1_channels, 2,
        &Tanks_Template_DW.HILReadAnalog1_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
      }

      rtb_sensor_tank2 = Tanks_Template_DW.HILReadAnalog1_Buffer[0];
      rtb_sensor_tank1 = Tanks_Template_DW.HILReadAnalog1_Buffer[1];
    }

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/Constant2'
     *  Gain: '<Root>/Gain'
     */
    Tanks_Template_B.Sum = Tanks_Template_P.gain_2 * rtb_sensor_tank2 -
      Tanks_Template_P.offset_2;

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/Constant1'
     *  Gain: '<Root>/Gain1'
     */
    Tanks_Template_B.Sum1 = Tanks_Template_P.gain_1 * rtb_sensor_tank1 -
      Tanks_Template_P.offset_1;
  }

  /* StateSpace: '<Root>/State-Space' */
  Tanks_Template_B.StateSpace[0] = 0.0;
  Tanks_Template_B.StateSpace[1] = 0.0;
  Tanks_Template_B.StateSpace[0] += Tanks_Template_P.C[0] *
    Tanks_Template_X.StateSpace_CSTATE[0];
  Tanks_Template_B.StateSpace[1] += Tanks_Template_X.StateSpace_CSTATE[0] *
    Tanks_Template_P.C[1];
  Tanks_Template_B.StateSpace[0] += Tanks_Template_X.StateSpace_CSTATE[1] *
    Tanks_Template_P.C[2];
  Tanks_Template_B.StateSpace[1] += Tanks_Template_X.StateSpace_CSTATE[1] *
    Tanks_Template_P.C[3];
  if (rtmIsMajorTimeStep(Tanks_Template_M) &&
      Tanks_Template_M->Timing.TaskCounters.TID[1] == 0) {
  }

  if (rtmIsMajorTimeStep(Tanks_Template_M) &&
      Tanks_Template_M->Timing.TaskCounters.TID[2] == 0) {
  }
}

/* Model update function */
void Tanks_Template_update(void)
{
  if (rtmIsMajorTimeStep(Tanks_Template_M)) {
    rt_ertODEUpdateContinuousStates(&Tanks_Template_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Tanks_Template_M->Timing.clockTick0)) {
    ++Tanks_Template_M->Timing.clockTickH0;
  }

  Tanks_Template_M->Timing.t[0] = rtsiGetSolverStopTime
    (&Tanks_Template_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Tanks_Template_M->Timing.clockTick1)) {
      ++Tanks_Template_M->Timing.clockTickH1;
    }

    Tanks_Template_M->Timing.t[1] = Tanks_Template_M->Timing.clockTick1 *
      Tanks_Template_M->Timing.stepSize1 + Tanks_Template_M->Timing.clockTickH1 *
      Tanks_Template_M->Timing.stepSize1 * 4294967296.0;
  }

  if (rtmIsMajorTimeStep(Tanks_Template_M) &&
      Tanks_Template_M->Timing.TaskCounters.TID[2] == 0) {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick2" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick2"
     * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick2 and the high bits
     * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Tanks_Template_M->Timing.clockTick2)) {
      ++Tanks_Template_M->Timing.clockTickH2;
    }

    Tanks_Template_M->Timing.t[2] = Tanks_Template_M->Timing.clockTick2 *
      Tanks_Template_M->Timing.stepSize2 + Tanks_Template_M->Timing.clockTickH2 *
      Tanks_Template_M->Timing.stepSize2 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void Tanks_Template_derivatives(void)
{
  XDot_Tanks_Template_T *_rtXdot;
  _rtXdot = ((XDot_Tanks_Template_T *) Tanks_Template_M->derivs);

  /* Derivatives for StateSpace: '<Root>/State-Space' */
  _rtXdot->StateSpace_CSTATE[0] = 0.0;
  _rtXdot->StateSpace_CSTATE[1] = 0.0;
  _rtXdot->StateSpace_CSTATE[0] += Tanks_Template_P.A[0] *
    Tanks_Template_X.StateSpace_CSTATE[0];
  _rtXdot->StateSpace_CSTATE[1] += Tanks_Template_X.StateSpace_CSTATE[0] *
    Tanks_Template_P.A[1];
  _rtXdot->StateSpace_CSTATE[0] += Tanks_Template_X.StateSpace_CSTATE[1] *
    Tanks_Template_P.A[2];
  _rtXdot->StateSpace_CSTATE[1] += Tanks_Template_X.StateSpace_CSTATE[1] *
    Tanks_Template_P.A[3];
  _rtXdot->StateSpace_CSTATE[0] += Tanks_Template_P.B[0] *
    Tanks_Template_B.Constant;
  _rtXdot->StateSpace_CSTATE[1] += Tanks_Template_P.B[1] *
    Tanks_Template_B.Constant;
}

/* Model initialize function */
void Tanks_Template_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Tanks_Template/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &Tanks_Template_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Tanks_Template_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Tanks_Template_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
      return;
    }

    if ((Tanks_Template_P.HILInitialize_AIPStart && !is_switching) ||
        (Tanks_Template_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &Tanks_Template_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Tanks_Template_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &Tanks_Template_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Tanks_Template_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(Tanks_Template_DW.HILInitialize_Card,
        Tanks_Template_P.HILInitialize_AIChannels, 8U,
        &Tanks_Template_DW.HILInitialize_AIMinimums[0],
        &Tanks_Template_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }
    }

    if ((Tanks_Template_P.HILInitialize_AOPStart && !is_switching) ||
        (Tanks_Template_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &Tanks_Template_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Tanks_Template_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &Tanks_Template_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Tanks_Template_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(Tanks_Template_DW.HILInitialize_Card,
        Tanks_Template_P.HILInitialize_AOChannels, 8U,
        &Tanks_Template_DW.HILInitialize_AOMinimums[0],
        &Tanks_Template_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }
    }

    if ((Tanks_Template_P.HILInitialize_AOStart && !is_switching) ||
        (Tanks_Template_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Tanks_Template_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Tanks_Template_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Tanks_Template_DW.HILInitialize_Card,
        Tanks_Template_P.HILInitialize_AOChannels, 8U,
        &Tanks_Template_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }
    }

    if (Tanks_Template_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Tanks_Template_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Tanks_Template_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Tanks_Template_DW.HILInitialize_Card,
         Tanks_Template_P.HILInitialize_AOChannels, 8U,
         &Tanks_Template_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }
    }

    if ((Tanks_Template_P.HILInitialize_EIPStart && !is_switching) ||
        (Tanks_Template_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &Tanks_Template_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = Tanks_Template_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (Tanks_Template_DW.HILInitialize_Card,
         Tanks_Template_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &Tanks_Template_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }
    }

    if ((Tanks_Template_P.HILInitialize_EIStart && !is_switching) ||
        (Tanks_Template_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &Tanks_Template_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = Tanks_Template_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(Tanks_Template_DW.HILInitialize_Card,
        Tanks_Template_P.HILInitialize_EIChannels, 8U,
        &Tanks_Template_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }
    }

    if ((Tanks_Template_P.HILInitialize_POPStart && !is_switching) ||
        (Tanks_Template_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Tanks_Template_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Tanks_Template_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Tanks_Template_DW.HILInitialize_Card,
        Tanks_Template_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Tanks_Template_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Tanks_Template_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &Tanks_Template_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Tanks_Template_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            Tanks_Template_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              Tanks_Template_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Tanks_Template_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            Tanks_Template_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = Tanks_Template_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(Tanks_Template_DW.HILInitialize_Card,
          &Tanks_Template_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &Tanks_Template_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(Tanks_Template_DW.HILInitialize_Card,
          &Tanks_Template_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &Tanks_Template_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Tanks_Template_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Tanks_Template_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &Tanks_Template_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = Tanks_Template_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &Tanks_Template_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = Tanks_Template_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(Tanks_Template_DW.HILInitialize_Card,
        Tanks_Template_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &Tanks_Template_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &Tanks_Template_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &Tanks_Template_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &Tanks_Template_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Tanks_Template_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Tanks_Template_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Tanks_Template_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Tanks_Template_DW.HILInitialize_Card,
        Tanks_Template_P.HILInitialize_POChannels, 8U,
        &Tanks_Template_DW.HILInitialize_POSortedFreqs[0],
        &Tanks_Template_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }
    }

    if ((Tanks_Template_P.HILInitialize_POStart && !is_switching) ||
        (Tanks_Template_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Tanks_Template_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Tanks_Template_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Tanks_Template_DW.HILInitialize_Card,
        Tanks_Template_P.HILInitialize_POChannels, 8U,
        &Tanks_Template_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }
    }

    if (Tanks_Template_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Tanks_Template_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Tanks_Template_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (Tanks_Template_DW.HILInitialize_Card,
         Tanks_Template_P.HILInitialize_POChannels, 8U,
         &Tanks_Template_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for Constant: '<Root>/Constant' */
  Tanks_Template_B.Constant = Tanks_Template_P.v_pump;

  /* InitializeConditions for StateSpace: '<Root>/State-Space' */
  Tanks_Template_X.StateSpace_CSTATE[0] =
    Tanks_Template_P.StateSpace_InitialCondition;
  Tanks_Template_X.StateSpace_CSTATE[1] =
    Tanks_Template_P.StateSpace_InitialCondition;
}

/* Model terminate function */
void Tanks_Template_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Tanks_Template/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Tanks_Template_DW.HILInitialize_Card);
    hil_monitor_stop_all(Tanks_Template_DW.HILInitialize_Card);
    is_switching = false;
    if ((Tanks_Template_P.HILInitialize_AOTerminate && !is_switching) ||
        (Tanks_Template_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Tanks_Template_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Tanks_Template_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Tanks_Template_P.HILInitialize_POTerminate && !is_switching) ||
        (Tanks_Template_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Tanks_Template_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Tanks_Template_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(Tanks_Template_DW.HILInitialize_Card
                         , Tanks_Template_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Tanks_Template_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &Tanks_Template_DW.HILInitialize_AOVoltages[0]
                         , &Tanks_Template_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(Tanks_Template_DW.HILInitialize_Card,
            Tanks_Template_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &Tanks_Template_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(Tanks_Template_DW.HILInitialize_Card,
            Tanks_Template_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &Tanks_Template_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Tanks_Template_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Tanks_Template_DW.HILInitialize_Card);
    hil_monitor_delete_all(Tanks_Template_DW.HILInitialize_Card);
    hil_close(Tanks_Template_DW.HILInitialize_Card);
    Tanks_Template_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  Tanks_Template_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Tanks_Template_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  Tanks_Template_initialize();
}

void MdlTerminate(void)
{
  Tanks_Template_terminate();
}

/* Registration function */
RT_MODEL_Tanks_Template_T *Tanks_Template(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Tanks_Template_M, 0,
                sizeof(RT_MODEL_Tanks_Template_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Tanks_Template_M->solverInfo,
                          &Tanks_Template_M->Timing.simTimeStep);
    rtsiSetTPtr(&Tanks_Template_M->solverInfo, &rtmGetTPtr(Tanks_Template_M));
    rtsiSetStepSizePtr(&Tanks_Template_M->solverInfo,
                       &Tanks_Template_M->Timing.stepSize0);
    rtsiSetdXPtr(&Tanks_Template_M->solverInfo, &Tanks_Template_M->derivs);
    rtsiSetContStatesPtr(&Tanks_Template_M->solverInfo, (real_T **)
                         &Tanks_Template_M->contStates);
    rtsiSetNumContStatesPtr(&Tanks_Template_M->solverInfo,
      &Tanks_Template_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Tanks_Template_M->solverInfo,
      &Tanks_Template_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Tanks_Template_M->solverInfo,
      &Tanks_Template_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Tanks_Template_M->solverInfo,
      &Tanks_Template_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Tanks_Template_M->solverInfo, (&rtmGetErrorStatus
      (Tanks_Template_M)));
    rtsiSetRTModelPtr(&Tanks_Template_M->solverInfo, Tanks_Template_M);
  }

  rtsiSetSimTimeStep(&Tanks_Template_M->solverInfo, MAJOR_TIME_STEP);
  Tanks_Template_M->intgData.y = Tanks_Template_M->odeY;
  Tanks_Template_M->intgData.f[0] = Tanks_Template_M->odeF[0];
  Tanks_Template_M->intgData.f[1] = Tanks_Template_M->odeF[1];
  Tanks_Template_M->intgData.f[2] = Tanks_Template_M->odeF[2];
  Tanks_Template_M->intgData.f[3] = Tanks_Template_M->odeF[3];
  Tanks_Template_M->contStates = ((real_T *) &Tanks_Template_X);
  rtsiSetSolverData(&Tanks_Template_M->solverInfo, (void *)
                    &Tanks_Template_M->intgData);
  rtsiSetSolverName(&Tanks_Template_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Tanks_Template_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "Tanks_Template_M points to
       static memory which is guaranteed to be non-NULL" */
    Tanks_Template_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Tanks_Template_M->Timing.sampleTimes =
      (&Tanks_Template_M->Timing.sampleTimesArray[0]);
    Tanks_Template_M->Timing.offsetTimes =
      (&Tanks_Template_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Tanks_Template_M->Timing.sampleTimes[0] = (0.0);
    Tanks_Template_M->Timing.sampleTimes[1] = (0.001);
    Tanks_Template_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    Tanks_Template_M->Timing.offsetTimes[0] = (0.0);
    Tanks_Template_M->Timing.offsetTimes[1] = (0.0);
    Tanks_Template_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(Tanks_Template_M, &Tanks_Template_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Tanks_Template_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    mdlSampleHits[2] = 1;
    Tanks_Template_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Tanks_Template_M, -1);
  Tanks_Template_M->Timing.stepSize0 = 0.001;
  Tanks_Template_M->Timing.stepSize1 = 0.001;
  Tanks_Template_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  Tanks_Template_M->Sizes.checksums[0] = (3786016533U);
  Tanks_Template_M->Sizes.checksums[1] = (52842443U);
  Tanks_Template_M->Sizes.checksums[2] = (1668776041U);
  Tanks_Template_M->Sizes.checksums[3] = (3782317031U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    Tanks_Template_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Tanks_Template_M->extModeInfo,
      &Tanks_Template_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Tanks_Template_M->extModeInfo,
                        Tanks_Template_M->Sizes.checksums);
    rteiSetTPtr(Tanks_Template_M->extModeInfo, rtmGetTPtr(Tanks_Template_M));
  }

  Tanks_Template_M->solverInfoPtr = (&Tanks_Template_M->solverInfo);
  Tanks_Template_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&Tanks_Template_M->solverInfo, 0.001);
  rtsiSetSolverMode(&Tanks_Template_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Tanks_Template_M->blockIO = ((void *) &Tanks_Template_B);

  {
    Tanks_Template_B.Constant = 0.0;
    Tanks_Template_B.Sum = 0.0;
    Tanks_Template_B.Sum1 = 0.0;
    Tanks_Template_B.StateSpace[0] = 0.0;
    Tanks_Template_B.StateSpace[1] = 0.0;
  }

  /* parameters */
  Tanks_Template_M->defaultParam = ((real_T *)&Tanks_Template_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Tanks_Template_X;
    Tanks_Template_M->contStates = (x);
    (void) memset((void *)&Tanks_Template_X, 0,
                  sizeof(X_Tanks_Template_T));
  }

  /* states (dwork) */
  Tanks_Template_M->dwork = ((void *) &Tanks_Template_DW);
  (void) memset((void *)&Tanks_Template_DW, 0,
                sizeof(DW_Tanks_Template_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Tanks_Template_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Tanks_Template_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Tanks_Template_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Tanks_Template_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Tanks_Template_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Tanks_Template_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Tanks_Template_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Tanks_Template_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  Tanks_Template_DW.HILReadAnalog1_Buffer[0] = 0.0;
  Tanks_Template_DW.HILReadAnalog1_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Tanks_Template_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 20;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Tanks_Template_M->Sizes.numContStates = (2);/* Number of continuous states */
  Tanks_Template_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  Tanks_Template_M->Sizes.numY = (0);  /* Number of model outputs */
  Tanks_Template_M->Sizes.numU = (0);  /* Number of model inputs */
  Tanks_Template_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Tanks_Template_M->Sizes.numSampTimes = (3);/* Number of sample times */
  Tanks_Template_M->Sizes.numBlocks = (15);/* Number of blocks */
  Tanks_Template_M->Sizes.numBlockIO = (4);/* Number of block outputs */
  Tanks_Template_M->Sizes.numBlockPrms = (153);/* Sum of parameter "widths" */
  return Tanks_Template_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
