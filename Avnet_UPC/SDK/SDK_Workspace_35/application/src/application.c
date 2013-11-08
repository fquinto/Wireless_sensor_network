/*
*********************************************************************************************************
* Author : FQuinto
* File: application.c
* v. 1.00   | 2012-06-14 | First release
*********************************************************************************************************
*/

#include <stdio.h>
#include "includes.h"

#define char_c 99 // tecla c = 0x63
#define char_C 67 // tecla C = 0x43
#define char_t 116 // tecla t = 0x74
#define char_T 84 // tecla T = 0x54
#define CRTL_C 3 // tecla CONTROL+C = 0x3


/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK   AppTaskFirstStk [APP_TASK_FIRST_STK_SIZE];    /* Start task stack                        */
static  OS_STK   AppTaskSecondStk [APP_TASK_SECOND_STK_SIZE];  /* Start task stack                        */
static  OS_STK   AppTaskUARTStk [APP_TASK_UART_STK_SIZE];      /* Start task stack                        */

INT8U tecla;



/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskFirst(void *p_arg);
static  void  AppTaskSecond(void *p_arg);
static  void  AppTaskUART(void *p_arg);
static  void  AppTaskCreate ();

/*
*********************************************************************************************************
*                                                main()
* 
* Descripció: Aquest és el punt d'entrada estàndar de C.  main() fa el següent:
*              
*              1) Inicialitza el sistema operatiu
*              2) Crea una primera tasca
*              3) Inicia el sistema operatiu
*
* Arguments  : Cap
*********************************************************************************************************
*/

int  main (void)
{
	if (DEBUG)
		xil_printf("DEBUG: INSIDE main\n\r");

	CPU_INT08U    err;

	// inicialització de la variable que conté el caràcter rebut
	//caracter = 0;
	tecla = 0;
	
	// S'inhabiliten les interrupcions fins que el sistema operatiu no estigui inicialitzat
	if (DEBUG)
		xil_printf("DEBUG: GOING BSP_IntDisAll\n\r");

    BSP_IntDisAll();
	
	if (DEBUG)
		xil_printf("DEBUG: GOING OSInit\n\r");

    OSInit(); // Inicialitza el sistema operatiu

	OSTaskCreateExt(AppTaskFirst,
                   (void *)0,
                   &AppTaskFirstStk[APP_TASK_FIRST_STK_SIZE - 1],
                   APP_TASK_FIRST_PRIO,
                   APP_TASK_FIRST_ID,
                   &AppTaskFirstStk[0],
                   APP_TASK_FIRST_STK_SIZE,
                   (void *)0,
                   OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskNameSet(APP_TASK_FIRST_PRIO, (CPU_INT08U *)"App Task First", &err);

	// Aquesta funció proporciona un nom a la tasca dins del sistema operatiu
	// Només s'utilitza a efectes de depuració
    //OSTaskNameSet(TASK1_PRIO, (CPU_INT08U *)"InterficieControl", &err);
	
	if (DEBUG)
	{
		xil_printf("DEBUG: GOING OSStart\n\r");
	}

	OSStart(); //Inicia el sistema operatiu

	return 0;                                   
}

/*
*********************************************************************************************************
*                                             AppTaskFirst()
* 
* Description: This is the first task executed by uC/OS-II following OSStart()
*              
* Arguments  : p_arg        Argument passed to this task when task is created.  The argument is not used.
*
* Returns    : None
*********************************************************************************************************
*/
#define LEDS	4									// S3A400 - number of LEDS on the board
static  void  AppTaskFirst (void *p_arg)
{
	if (DEBUG)
		xil_printf("DEBUG: INSIDE AppTaskFirst\n\r");

	p_arg = p_arg;				/* Prevent compiler warning by doing something with argument */
	
	BSP_InitIO();				/* Initialize the I/Os                                       */

#if OS_TASK_STAT_EN > 0
    OSStatInit();				/* Initialize uC/OS-II's statistics                          */
#endif

    AppTaskCreate();            /* La resta de tasques de l'aplicació es crean normalment       */
                                /* dins d'una altra funció per tal de mantenir neta la secció  */
                                /* de codi corresponent a la funció m                           */

	int	led = 0; // S3A400 - initialize LED selector

    while (1) {
		if (DEBUG)
			xil_printf("DEBUG: INSIDE AppTaskFirst while\n\r");
		//BSP_LEDToggle(led + 1); // S3A400 - Light selected LED, all others off
		
        OSTimeDlyHMSM(0,0,5,0); // Release the CPU (every 5 second)

		//led = (led + 1) % LEDS;				// S3A400 - Select next LED
    }
}

/*
*********************************************************************************************************
*                                             AppTaskSecond()
* 
* Description: This task was added to perform any generic task.
*              
* Arguments  : p_arg        Argument passed to this task when task is created.  The argument is a string.
*
* Returns    : None
*********************************************************************************************************
*/
static  void  AppTaskSecond (void *p_arg)
{
	if (DEBUG)
		xil_printf("DEBUG: INSIDE AppTaskSecond\n\r");

    p_arg = p_arg;
	
	while (1)
    {
		if (DEBUG)
			xil_printf("DEBUG: INSIDE AppTaskSecond while\n\r");
		
		procesa_comandos();
		
    	OSTimeDlyHMSM(0,0,0,500); // 500m second
    }
}

/*
*********************************************************************************************************
*                                             AppTaskUART()
* 
* Description: This task was added to perform any generic task.
*              
* Arguments  : p_arg        Argument passed to this task when task is created.  The argument is a string.
*
* Returns    : None
*********************************************************************************************************
*/
static  void  AppTaskUART (void *p_arg)
{
	if (DEBUG)
		xil_printf("DEBUG: INSIDE AppTaskUART\n\r");

    p_arg = p_arg;
		
	while (1)
    {
		if (DEBUG)
			xil_printf("DEBUG: INSIDE AppTaskUART while\n\r");
		
		enviaMSP430(ReceiveBuffer);
	
		OSTimeDlyHMSM(0,0,0,500); // 500m second
	}
}

/*
*********************************************************************************************************
*                                          AppTaskCreate()
* 
* Descripció: Funció separada per generar la resta de tasques de l'aplicació
*              
* Arguments  : Cap
*
* Returna    : Res
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
	if (DEBUG)
			xil_printf("DEBUG: INSIDE AppTaskCreate\n\r");

	CPU_INT08U err;
	
	/* Crea la segunda tarea de la aplicación */
	OSTaskCreateExt(AppTaskSecond,
                   (void *)0,
                   &AppTaskSecondStk[APP_TASK_SECOND_STK_SIZE - 1],
                   APP_TASK_SECOND_PRIO,
                   APP_TASK_SECOND_ID,
                   &AppTaskSecondStk[0],
                   APP_TASK_SECOND_STK_SIZE,
                   (void *)0,
                   OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskNameSet(APP_TASK_SECOND_PRIO, (CPU_INT08U *)"App Task Second", &err);
	
	/* Crea la segunda tarea de la aplicación */
	OSTaskCreateExt(AppTaskUART,
                   (void *)0,
                   &AppTaskUARTStk[APP_TASK_UART_STK_SIZE - 1],
                   APP_TASK_UART_PRIO,
                   APP_TASK_UART_ID,
                   &AppTaskUARTStk[0],
                   APP_TASK_UART_STK_SIZE,
                   (void *)0,
                   OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskNameSet(APP_TASK_UART_PRIO, (CPU_INT08U *)"App Task UART", &err);
}
