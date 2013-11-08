/*
*********************************************************************************************************
*                                                uC/CPU
*                                    CPU CONFIGURATION & PORT LAYER
*
*                          (c) Copyright 2004-2010; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CPU is provided in source form to registered licensees ONLY.  It is 
*               illegal to distribute this source code to any third party unless you receive 
*               written permission by an authorized Micrium representative.  Knowledge of 
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest 
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           CORE CPU MODULE
*
* Filename      : cpu_core.h
* Version       : V1.25
* Programmer(s) : SR
*                 ITJ
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  CPU_CORE_MODULE_PRESENT
#define  CPU_CORE_MODULE_PRESENT


/*$PAGE*/
/*
*********************************************************************************************************
*                                   CORE CPU MODULE VERSION NUMBER
*
* Note(s) : (1) (a) The core CPU module software version is denoted as follows :
*
*                       Vx.yy
*
*                           where
*                                   V               denotes 'Version' label
*                                   x               denotes major software version revision number
*                                   yy              denotes minor software version revision number
*
*               (b) The software version label #define is formatted as follows :
*
*                       ver = x.yy * 100
*
*                           where
*                                   ver             denotes software version number scaled as an integer value
*                                   x.yy            denotes software version number
*********************************************************************************************************
*/

#define  CPU_CORE_VERSION                                125u   /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   CPU_CORE_MODULE
#define  CPU_CORE_EXT
#else
#define  CPU_CORE_EXT  extern
#endif


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <cpu_cfg.h>

#include  <lib_mem.h>
#include  <lib_str.h>


/*$PAGE*/
/*
*********************************************************************************************************
*                                          CPU CONFIGURATION
*
* Note(s) : (1) The following pre-processor directives correctly configure CPU parameters.  DO NOT MODIFY.
*
*           (2) CPU timestamp timer feature is required for :
*
*               (a) CPU timestamps
*               (b) CPU interrupts disabled time measurement
*
*               See also 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                      & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1'.
*********************************************************************************************************
*/

#ifdef   CPU_CFG_TS_EN
#undef   CPU_CFG_TS_EN
#endif


#if    ((CPU_CFG_TS_32_EN == DEF_ENABLED) || \
        (CPU_CFG_TS_64_EN == DEF_ENABLED))
#define  CPU_CFG_TS_EN                          DEF_ENABLED
#else
#define  CPU_CFG_TS_EN                          DEF_DISABLED
#endif

#if    ((CPU_CFG_TS_EN == DEF_ENABLED) || \
(defined(CPU_CFG_INT_DIS_MEAS_EN)))
#define  CPU_CFG_TS_TMR_EN                      DEF_ENABLED
#else
#define  CPU_CFG_TS_TMR_EN                      DEF_DISABLED
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  CPU_TIME_MEAS_NBR_MIN                             1u
#define  CPU_TIME_MEAS_NBR_MAX                           128u


/*
*********************************************************************************************************
*                                           CPU ERROR CODES
*********************************************************************************************************
*/

#define  CPU_ERR_NONE                                      0u
#define  CPU_ERR_NULL_PTR                                 10u

#define  CPU_ERR_NAME_SIZE                              1000u

#define  CPU_ERR_TS_FREQ_INVALID                        2000u


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      CPU ERROR CODES DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT16U  CPU_ERR;


/*
*********************************************************************************************************
*                                      CPU TIMESTAMP DATA TYPES
*
* Note(s) : (1) CPU timestamp timer data type defined to the binary-multiple of 8-bit octets as configured 
*               by 'CPU_CFG_TS_TMR_SIZE' (see 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #2').
*********************************************************************************************************
*/

typedef  CPU_INT32U  CPU_TS32;
typedef  CPU_INT64U  CPU_TS64;

typedef  CPU_TS32    CPU_TS;                                    /* Req'd for backwards-compatibility.                   */


#if     (CPU_CFG_TS_TMR_EN   == DEF_ENABLED)                    /* CPU ts tmr defined to cfg'd word size (see Note #1). */
#if     (CPU_CFG_TS_TMR_SIZE == CPU_WORD_SIZE_08)
typedef  CPU_INT08U  CPU_TS_TMR;
#elif   (CPU_CFG_TS_TMR_SIZE == CPU_WORD_SIZE_16)
typedef  CPU_INT16U  CPU_TS_TMR;
#elif   (CPU_CFG_TS_TMR_SIZE == CPU_WORD_SIZE_64)
typedef  CPU_INT64U  CPU_TS_TMR;
#else                                                           /* CPU ts tmr dflt size = 32-bits.                      */
typedef  CPU_INT32U  CPU_TS_TMR;
#endif
#endif


/*
*********************************************************************************************************
*                               CPU TIMESTAMP TIMER FREQUENCY DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT32U  CPU_TS_TMR_FREQ;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

#if    (CPU_CFG_NAME_EN   == DEF_ENABLED)
CPU_CORE_EXT  CPU_CHAR         CPU_Name[CPU_CFG_NAME_SIZE];     /* CPU host name.                                       */
#endif


#if ((CPU_CFG_TS_32_EN    == DEF_ENABLED)  && \
     (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_32))
CPU_CORE_EXT  CPU_TS32         CPU_TS_32_Accum;                 /* 32-bit accum'd ts  (in ts tmr cnts).                 */
CPU_CORE_EXT  CPU_TS_TMR       CPU_TS_32_TmrPrev;               /* 32-bit ts prev tmr (in ts tmr cnts).                 */
#endif

#if ((CPU_CFG_TS_64_EN    == DEF_ENABLED)  && \
     (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_64))
CPU_CORE_EXT  CPU_TS64         CPU_TS_64_Accum;                 /* 64-bit accum'd ts  (in ts tmr cnts).                 */
CPU_CORE_EXT  CPU_TS_TMR       CPU_TS_64_TmrPrev;               /* 64-bit ts prev tmr (in ts tmr cnts).                 */
#endif

#if  (CPU_CFG_TS_TMR_EN   == DEF_ENABLED)
CPU_CORE_EXT  CPU_TS_TMR_FREQ  CPU_TS_TmrFreq_Hz;               /* CPU ts tmr freq (in Hz).                             */
#endif


#ifdef  CPU_CFG_INT_DIS_MEAS_EN
CPU_CORE_EXT  CPU_INT16U       CPU_IntDisMeasCtr;               /* Nbr tot    ints dis'd ctr.                           */
CPU_CORE_EXT  CPU_INT16U       CPU_IntDisNestCtr;               /* Nbr nested ints dis'd ctr.                           */
                                                                /* Ints dis'd time (in ts tmr cnts) : ...               */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasStart_cnts;        /* ...  start time.                                     */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasStop_cnts;         /* ...  stop  time.                                     */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasOvrhd_cnts;        /* ...        time meas ovrhd.                          */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasMaxCur_cnts;       /* ...     resetable max time dis'd.                    */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasMax_cnts;          /* ... non-resetable max time dis'd.                    */
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*
* Note(s) : (1) CPU interrupts disabled time measurement functions prototyped/defined only if 
*               CPU_CFG_INT_DIS_MEAS_EN  #define'd in 'cpu_cfg.h'.
*
*           (2) CPU_CntLeadZeros() prototyped/defined respectively in :
*
*               (a) 'cpu.h'/'cpu_a.asm',       if CPU_CFG_LEAD_ZEROS_ASM_PRESENT      #define'd in 'cpu.h'/
*                                                 'cpu_cfg.h' to enable assembly-version function
*
*               (b) 'cpu_core.h'/'cpu_core.c', if CPU_CFG_LEAD_ZEROS_ASM_PRESENT  NOT #define'd in 'cpu.h'/
*                                                 'cpu_cfg.h' to enable C-source-version function otherwise
*********************************************************************************************************
*/

void             CPU_Init                 (void);



#if (CPU_CFG_NAME_EN == DEF_ENABLED)                                    /* -------------- CPU NAME FNCTS -------------- */
void             CPU_NameClr              (void);

void             CPU_NameGet              (CPU_CHAR         *p_name,
                                           CPU_ERR          *p_err);

void             CPU_NameSet              (CPU_CHAR         *p_name,
                                           CPU_ERR          *p_err);
#endif



                                                                        /* --------------- CPU TS FNCTS --------------- */
#if (CPU_CFG_TS_32_EN == DEF_ENABLED)
CPU_TS32         CPU_TS_Get32             (void);
#endif

#if (CPU_CFG_TS_64_EN == DEF_ENABLED)
CPU_TS64         CPU_TS_Get64             (void);
#endif

#if (CPU_CFG_TS_EN    == DEF_ENABLED)
void             CPU_TS_Update            (void);
#endif


#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)                                  /* ------------- CPU TS TMR FNCTS ------------- */
CPU_TS_TMR_FREQ  CPU_TS_TmrFreqGet        (CPU_ERR          *p_err);

void             CPU_TS_TmrFreqSet        (CPU_TS_TMR_FREQ   freq_hz);
#endif



#ifdef  CPU_CFG_INT_DIS_MEAS_EN                                         /* -------- CPU INT DIS TIME MEAS FNCTS ------- */
                                                                        /* See Note #1.                                 */
CPU_TS_TMR       CPU_IntDisMeasMaxCurReset(void);

CPU_TS_TMR       CPU_IntDisMeasMaxCurGet  (void);

CPU_TS_TMR       CPU_IntDisMeasMaxGet     (void);


void             CPU_IntDisMeasStart      (void);

void             CPU_IntDisMeasStop       (void);
#endif



#ifndef  CPU_CFG_LEAD_ZEROS_ASM_PRESENT                                 /* --------- CPU CNT LEAD ZEROS FNCTS --------- */
CPU_DATA         CPU_CntLeadZeros         (CPU_DATA          val);      /* See Note #2.                                 */
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                      DEFINED IN PRODUCT'S BSP
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          CPU_TS_TmrInit()
*
* Description : Initialize & start CPU timestamp timer.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_TS_Init().
*
*               This function is an INTERNAL CPU module function & MUST be implemented by application/
*               BSP function(s) [see Note #1] but MUST NOT be called by application function(s).
*
* Note(s)     : (1) CPU_TS_TmrInit() is an application/BSP function that MUST be defined by the developer 
*                   if either of the following CPU features is enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) Timer count values MUST be returned via word-size-configurable 'CPU_TS_TMR' 
*                       data type.
*
*                       (1) If timer has more bits, truncate timer values' higher-order bits greater 
*                           than the configured 'CPU_TS_TMR' timestamp timer data type word size.
*
*                       (2) Since the timer MUST NOT have less bits than the configured 'CPU_TS_TMR' 
*                           timestamp timer data type word size; 'CPU_CFG_TS_TMR_SIZE' MUST be 
*                           configured so that ALL bits in 'CPU_TS_TMR' data type are significant.
*
*                           In other words, if timer size is not a binary-multiple of 8-bit octets 
*                           (e.g. 20-bits or even 24-bits), then the next lower, binary-multiple 
*                           octet word size SHOULD be configured (e.g. to 16-bits).  However, the 
*                           minimum supported word size for CPU timestamp timers is 8-bits.
*
*                       See also 'cpu_cfg.h   CPU TIMESTAMP CONFIGURATION  Note #2'
*                              & 'cpu_core.h  CPU TIMESTAMP DATA TYPES     Note #1'.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                   (c) When applicable, timer period SHOULD be less than the typical measured time 
*                       but MUST be less than the maximum measured time; otherwise, timer resolution 
*                       inadequate to measure desired times.
*
*                   See also 'CPU_TS_TmrRd()  Note #2'.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrInit(void);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           CPU_TS_TmrRd()
*
* Description : Get current CPU timestamp timer count value.
*
* Argument(s) : none.
*
* Return(s)   : Timestamp timer count (see Notes #2a & #2b).
*
* Caller(s)   : CPU_TS_Init(),
*               CPU_TS_Get32(),
*               CPU_TS_Get64(),
*               CPU_IntDisMeasStart(),
*               CPU_IntDisMeasStop().
*
*               This function is an INTERNAL CPU module function & MUST be implemented by application/
*               BSP function(s) [see Note #1] but SHOULD NOT be called by application function(s).
*
* Note(s)     : (1) CPU_TS_TmrRd() is an application/BSP function that MUST be defined by the developer 
*                   if either of the following CPU features is enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) Timer count values MUST be returned via word-size-configurable 'CPU_TS_TMR' 
*                       data type.
*
*                       (1) If timer has more bits, truncate timer values' higher-order bits greater 
*                           than the configured 'CPU_TS_TMR' timestamp timer data type word size.
*
*                       (2) Since the timer MUST NOT have less bits than the configured 'CPU_TS_TMR' 
*                           timestamp timer data type word size; 'CPU_CFG_TS_TMR_SIZE' MUST be 
*                           configured so that ALL bits in 'CPU_TS_TMR' data type are significant.
*
*                           In other words, if timer size is not a binary-multiple of 8-bit octets 
*                           (e.g. 20-bits or even 24-bits), then the next lower, binary-multiple 
*                           octet word size SHOULD be configured (e.g. to 16-bits).  However, the 
*                           minimum supported word size for CPU timestamp timers is 8-bits.
*
*                       See also 'cpu_cfg.h   CPU TIMESTAMP CONFIGURATION  Note #2'
*                              & 'cpu_core.h  CPU TIMESTAMP DATA TYPES     Note #1'.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                       (1) If timer is a 'down' counter whose values decrease with each time count,
*                           then the returned timer value MUST be ones-complemented.
*
*                   (c) (1) When applicable, the amount of time measured by CPU timestamps is 
*                           calculated by either of the following equations :
*
*                           (A) Time measured  =  Number timer counts  *  Timer period
*
*                                   where
*
*                                       Number timer counts     Number of timer counts measured 
*                                       Timer period            Timer's period in some units of 
*                                                                   (fractional) seconds
*                                       Time measured           Amount of time measured, in same 
*                                                                   units of (fractional) seconds 
*                                                                   as the Timer period
*
*                                                  Number timer counts
*                           (B) Time measured  =  ---------------------
*                                                    Timer frequency
*
*                                   where
*
*                                       Number timer counts     Number of timer counts measured
*                                       Timer frequency         Timer's frequency in some units 
*                                                                   of counts per second
*                                       Time measured           Amount of time measured, in seconds
*
*                       (2) Timer period SHOULD be less than the typical measured time but MUST be less 
*                           than the maximum measured time; otherwise, timer resolution inadequate to 
*                           measure desired times.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS_TMR  CPU_TS_TmrRd(void);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         CPU_TSxx_to_uSec()
*
* Description : Convert a 32-/64-bit CPU timestamp from timer counts to microseconds.
*
* Argument(s) : ts_cnts   CPU timestamp (in timestamp timer counts [see Note #2aA]).
*
* Return(s)   : Converted CPU timestamp (in microseconds           [see Note #2aD]).
*
* Caller(s)   : Application.
*
*               This function is an (optional) CPU module application interface (API) function which 
*               MAY be implemented by application/BSP function(s) [see Note #1] & MAY be called by 
*               application function(s).
*
* Note(s)     : (1) CPU_TS32_to_uSec()/CPU_TS64_to_uSec() are application/BSP functions that MAY be 
*                   optionally defined by the developer when either of the following CPU features is 
*                   enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) The amount of time measured by CPU timestamps is calculated by either of 
*                       the following equations :
*
*                                                                        10^6 microseconds
*                       (1) Time measured  =   Number timer counts   *  -------------------  *  Timer period
*                                                                            1 second
*
*                                              Number timer counts       10^6 microseconds
*                       (2) Time measured  =  ---------------------  *  -------------------
*                                                Timer frequency             1 second
*
*                               where
*
*                                   (A) Number timer counts     Number of timer counts measured
*                                   (B) Timer frequency         Timer's frequency in some units 
*                                                                   of counts per second
*                                   (C) Timer period            Timer's period in some units of 
*                                                                   (fractional)  seconds
*                                   (D) Time measured           Amount of time measured, 
*                                                                   in microseconds
*
*                   (b) Timer period SHOULD be less than the typical measured time but MUST be less 
*                       than the maximum measured time; otherwise, timer resolution inadequate to 
*                       measure desired times.
*
*                   (c) Specific implementations may convert any number of CPU_TS32 or CPU_TS64 bits 
*                       -- up to 32 or 64, respectively -- into microseconds.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_32_EN == DEF_ENABLED)
CPU_INT64U  CPU_TS32_to_uSec (CPU_TS32  ts_cnts);
#endif

#if (CPU_CFG_TS_64_EN == DEF_ENABLED)
CPU_INT64U  CPU_TS64_to_uSec (CPU_TS64  ts_cnts);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  CPU_CFG_NAME_EN
#error  "CPU_CFG_NAME_EN                       not #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_ENABLED ]           "
#error  "                                [     ||  DEF_DISABLED]           "

#elif  ((CPU_CFG_NAME_EN != DEF_ENABLED ) && \
        (CPU_CFG_NAME_EN != DEF_DISABLED))
#error  "CPU_CFG_NAME_EN                 illegally #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_ENABLED ]           "
#error  "                                [     ||  DEF_DISABLED]           "


#elif   (CPU_CFG_NAME_EN == DEF_ENABLED)

#ifndef  CPU_CFG_NAME_SIZE
#error  "CPU_CFG_NAME_SIZE                     not #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  >=   1]                 "
#error  "                                [     &&  <= 255]                 "

#elif  ((CPU_CFG_NAME_SIZE <                   1) || \
        (CPU_CFG_NAME_SIZE > DEF_INT_08U_MAX_VAL))
#error  "CPU_CFG_NAME_SIZE               illegally #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  >=   1]                 "
#error  "                                [     &&  <= 255]                 "
#endif

#endif




#ifndef  CPU_CFG_TS_32_EN
#error  "CPU_CFG_TS_32_EN                      not #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "

#elif  ((CPU_CFG_TS_32_EN != DEF_DISABLED) && \
        (CPU_CFG_TS_32_EN != DEF_ENABLED ))
#error  "CPU_CFG_TS_32_EN                illegally #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "

#endif


#ifndef  CPU_CFG_TS_64_EN
#error  "CPU_CFG_TS_64_EN                      not #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "

#elif  ((CPU_CFG_TS_64_EN != DEF_DISABLED) && \
        (CPU_CFG_TS_64_EN != DEF_ENABLED ))
#error  "CPU_CFG_TS_64_EN                illegally #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "

#endif

                                                                /* Correctly configured in 'cpu_core.h'; DO NOT MODIFY. */
#ifndef  CPU_CFG_TS_EN
#error  "CPU_CFG_TS_EN                         not #define'd in 'cpu_core.h'"
#error  "                                [MUST be  DEF_DISABLED]            "
#error  "                                [     ||  DEF_ENABLED ]            "

#elif  ((CPU_CFG_TS_EN != DEF_DISABLED) && \
        (CPU_CFG_TS_EN != DEF_ENABLED ))
#error  "CPU_CFG_TS_EN                   illegally #define'd in 'cpu_core.h'"
#error  "                                [MUST be  DEF_DISABLED]            "
#error  "                                [     ||  DEF_ENABLED ]            "

#endif


                                                                /* Correctly configured in 'cpu_core.h'; DO NOT MODIFY. */
#ifndef  CPU_CFG_TS_TMR_EN
#error  "CPU_CFG_TS_TMR_EN                     not #define'd in 'cpu_core.h'"
#error  "                                [MUST be  DEF_DISABLED]            "
#error  "                                [     ||  DEF_ENABLED ]            "

#elif  ((CPU_CFG_TS_TMR_EN != DEF_DISABLED) && \
        (CPU_CFG_TS_TMR_EN != DEF_ENABLED ))
#error  "CPU_CFG_TS_TMR_EN               illegally #define'd in 'cpu_core.h'"
#error  "                                [MUST be  DEF_DISABLED]            "
#error  "                                [     ||  DEF_ENABLED ]            "


#elif   (CPU_CFG_TS_TMR_EN == DEF_ENABLED)

#ifndef  CPU_CFG_TS_TMR_SIZE
#error  "CPU_CFG_TS_TMR_SIZE                   not #define'd in 'cpu_cfg.h'       "
#error  "                                [MUST be  CPU_WORD_SIZE_08   8-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_16  16-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_32  32-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_64  64-bit timer]"

#elif  ((CPU_CFG_TS_TMR_SIZE != CPU_WORD_SIZE_08) && \
        (CPU_CFG_TS_TMR_SIZE != CPU_WORD_SIZE_16) && \
        (CPU_CFG_TS_TMR_SIZE != CPU_WORD_SIZE_32) && \
        (CPU_CFG_TS_TMR_SIZE != CPU_WORD_SIZE_64))
#error  "CPU_CFG_TS_TMR_SIZE             illegally #define'd in 'cpu_cfg.h'       "
#error  "                                [MUST be  CPU_WORD_SIZE_08   8-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_16  16-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_32  32-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_64  64-bit timer]"
#endif

#endif



#ifndef  CPU_CFG_INT_DIS_MEAS_EN
#if 0                                                           /* Optionally configured in 'cpu_cfg.h'; DO NOT MODIFY. */
#error  "CPU_CFG_INT_DIS_MEAS_EN               not #define'd in 'cpu_cfg.h'"
#endif

#else

#ifndef  CPU_CFG_INT_DIS_MEAS_OVRHD_NBR
#error  "CPU_CFG_INT_DIS_MEAS_OVRHD_NBR        not #define'd in 'cpu_cfg.h' "
#error  "                                [MUST be  >= CPU_TIME_MEAS_NBR_MIN]"
#error  "                                [     ||  <= CPU_TIME_MEAS_NBR_MAX]"

#elif  ((CPU_CFG_INT_DIS_MEAS_OVRHD_NBR < CPU_TIME_MEAS_NBR_MIN) || \
        (CPU_CFG_INT_DIS_MEAS_OVRHD_NBR > CPU_TIME_MEAS_NBR_MAX))
#error  "CPU_CFG_INT_DIS_MEAS_OVRHD_NBR  illegally #define'd in 'cpu_cfg.h' "
#error  "                                [MUST be  >= CPU_TIME_MEAS_NBR_MIN]"
#error  "                                [     ||  <= CPU_TIME_MEAS_NBR_MAX]"

#endif

#endif




#ifndef  CPU_CFG_LEAD_ZEROS_ASM_PRESENT
#if 0                                                           /* Optionally configured in 'cpu_cfg.h'; DO NOT MODIFY. */
#error  "CPU_CFG_LEAD_ZEROS_ASM_PRESENT        not #define'd in 'cpu.h'/'cpu_cfg.h'"
#endif
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of CPU core module include.                      */

