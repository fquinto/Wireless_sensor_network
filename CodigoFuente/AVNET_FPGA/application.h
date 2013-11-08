/*
*********************************************************************************************************
* Author : FQuinto
* File: application.h
* v. 1.00   | 2012-06-14 | First release
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            TASKS PRIORITIES
*********************************************************************************************************
*/

#define  APP_TASK_FIRST_ID                  2
#define  APP_TASK_SECOND_ID                 APP_TASK_FIRST_ID + 1
#define  APP_TASK_UART_ID                   APP_TASK_SECOND_ID + 1
#define  APP_TASK_FIRST_PRIO                3
#define  APP_TASK_SECOND_PRIO               APP_TASK_FIRST_PRIO - 1
#define  APP_TASK_UART_PRIO                 APP_TASK_SECOND_PRIO - 1
/*
*********************************************************************************************************
*                                              STACK SIZES
*                            Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_TASK_FIRST_STK_SIZE         256
#define  APP_TASK_SECOND_STK_SIZE        APP_TASK_FIRST_STK_SIZE
#define  APP_TASK_UART_STK_SIZE          APP_TASK_FIRST_STK_SIZE
