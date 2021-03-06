/*
********************************************************************************************************
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
*                                            CPU PORT FILE
*
*                                                PPC405
*                                            GNU C Compiler
*
* Filename      : cpu_a.s
* Version       : V1.25
* Programmer(s) : NB
*********************************************************************************************************
*/

#define _ASMLANGUAGE

/*
*********************************************************************************************************
*                                            PUBLIC FUNCTIONS
*********************************************************************************************************
*/

        .globl      CPU_SR_Save
        .globl      CPU_SR_Restore


.text

#$PAGE
/*
*********************************************************************************************************
*                                      CRITICAL SECTION FUNCTIONS
*
* Description : Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking, the
*               state of the interrupt disable flag is stored in the local variable 'cpu_sr' & interrupts
*               are then disabled ('cpu_sr' is allocated in all functions that need to disable interrupts).
*               The previous interrupt state is restored by copying 'cpu_sr' into the CPU's status register.
*
* Prototypes  : CPU_SR  CPU_SR_Save   (void);
*               void    CPU_SR_Restore(CPU_SR cpu_sr);
*
* Note(s)     : (1) These functions are used in general like this :
*
*                       void  Task (void  *p_arg)
*                       {
*                           CPU_SR_ALLOC();                     /* Allocate storage for CPU status register */
*                               :
*                               :
*                           CPU_CRITICAL_ENTER();               /* cpu_sr = CPU_SR_Save();                  */
*                               :
*                               :
*                           CPU_CRITICAL_EXIT();                /* CPU_SR_Restore(cpu_sr);                  */
*                               :
*                       }
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         DISABLE INTERRUPTS
*                                      CPU_SR  CPU_SR_Save(void);
*
* Description : Sets the MSR, disabling interrupts, and returns the previous MSR contents.  This allows 
*               the machine state to be restored at a subsequent time.
*
* Arguments   : None
*
* Returns     : Current MSR contents in GPR3
*
* Note(s)     : 1) The variable in the calling routine that will hold the return value MUST be declared 
*                  volatile for proper operation.  There is no guarantee that the proper register will 
*                  be scheduled for the subsequent 'CPU_SR_Save()' function call if the variable is 
*                  not declared volatile.
*********************************************************************************************************
*/

CPU_SR_Save:

    addis  4, 0, 0xFFFD
    ori    4, 4, 0x7FFF
    mfmsr  3
    and    4, 4, 3                                      /* Clear bits 14 and 16, corresponding to...   */
    mtmsr  4                                            /* ...critical and non-critical interrupts     */
    blr


#$PAGE
/*
*********************************************************************************************************
*                                         ENABLE INTERRUPTS
*                                    void CPU_SR_Restore(CPU_SR sr);
* 
* Description : Sets the MSR, possibly enabling interrupts, using the value passed in GPR3. 
*
* Arguments   : Saved MSR contents in GPR3
*
* Returns     : None
*
* Note(s)     : 1) The argument from the calling routine MUST be declared volatile for proper operation. 
*                  There is no guarantee that the proper register will be scheduled for the call to 
*                  CPU_SR_Restore() if the variable is not declared 'volatile'.
*********************************************************************************************************
*/

CPU_SR_Restore:

    mtmsr  3                                            /* Restore the saved MSR                       */
    blr


#$PAGE
/*
*********************************************************************************************************
*                                     CPU ASSEMBLY PORT FILE END
*********************************************************************************************************
*/

