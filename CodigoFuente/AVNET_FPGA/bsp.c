/*
*********************************************************************************************************
* Author : FQuinto
* File: bsp.c
* v. 1.00   | 2012-06-14 | First release
*********************************************************************************************************
* UART EXAMPLES: C:\Xilinx\12.3\ISE_DS\EDK\sw\XilinxProcessorIPLib\drivers\uartlite_v2_00_a\examples\
*/

#include <stdio.h>
#include "includes.h"

/*
*********************************************************************************************************
*                                         LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

XUartLite UartLite1;            /* The instance of the UartLite Device MSP430 */
XUartLite UartLite2;            /* The instance of the UartLite Device USB */

XIntc    int_ctl;

/* work loop semaphores */
INT8U sCommandSem = 0;
INT8U sSendUARTMSP430Sem = 0;
INT8U waitingresponse = 0;


static INT8U headResponseData;
/*
 * cmd_check: Return 1 if diferent, return 0 if equal
 */
int cmd_check( char* string )
{
  int i,diferentes;
  int length = strlen(string);
  
  diferentes = 0;
	  for( i = 0; i < length; i++)
	  {
		if (comando[i] == string[i])
		{
			diferentes = 1;
		}
		else
		{
			return 0;
		}
	  }
	  return diferentes;
}

/*
*********************************************************************************************************
*                                                BSP_LEDOn()
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to control
*
* Returns     : None
*********************************************************************************************************
*/

void  BSP_LEDOn (INT8U led)
{
	if (DEBUG)
				xil_printf("DEBUG: INSIDE BSP_LEDOn\n\r");

    INT32U  led_status;

#if OS_CRITICAL_METHOD == 3                        /* Allocate storage for CPU status register         */
    OS_CPU_SR  cpu_sr;
#endif    

    led_status = XGpio_ReadReg(BSP_GPIO_ADDR,1);

    OS_ENTER_CRITICAL();
    switch (led) {
        case 0:
            led_status |= 0x0000000F;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
        case 1:
            led_status |= 0x00000001;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
        case 2:
            led_status |= 0x00000002;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
        case 3:
            led_status |= 0x00000004;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
        case 4:
            led_status |= 0x00000008;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
    }
    OS_EXIT_CRITICAL();
}

/*
*********************************************************************************************************
*                                               BSP_LEDOff()
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to turn OFF
*
* Returns     : None
*********************************************************************************************************
*/

void  BSP_LEDOff (INT8U led)
{
	if (DEBUG)
				xil_printf("DEBUG: INSIDE BSP_LEDOff\n\r");

    INT32U  led_status;

#if OS_CRITICAL_METHOD == 3                        /* Allocate storage for CPU status register         */
    OS_CPU_SR  cpu_sr;
#endif    

    led_status = XGpio_ReadReg(BSP_GPIO_ADDR,1);

    //OS_ENTER_CRITICAL();
    switch (led) {
        case 0:
            led_status &= ~0x0000000F;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
        case 1:
            led_status &= ~0x00000001;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
        case 2:
            led_status &= ~0x00000002;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
        case 3:
            led_status &= ~0x00000004;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
        case 4:
            led_status &= ~0x00000008;
            XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
            break;
    }
    //OS_EXIT_CRITICAL();
}

/*
*********************************************************************************************************
*                                             LED_Get()
*
* Description : This function is used to retrieve the LED state.
*
* Arguments   : None
*
* Returns     : Contents of the LED data register.
*********************************************************************************************************
*/

INT32U  LED_Get (void)
{
	return(XGpio_ReadReg(BSP_GPIO_ADDR,1));
}

/*
*********************************************************************************************************
*                                             Button_Get()
*
* Description : This function is used to retrieve the button state.
*
* Arguments   : None
*
* Returns     : Contents of the button data register.
*********************************************************************************************************
*/

INT32U  Button_Get (void)
{
	return(XGpio_ReadReg(BSP_BUTTON_ADDR,1));
}

/*
*********************************************************************************************************
*                                             BSP_LEDToggle()
*
* Description : This function is used to alternate the state of an LED
*
* Arguments   : led    is the number of the LED to control
*
* Returns     : None
*********************************************************************************************************
*/

void  BSP_LEDToggle (INT8U led)
{
	//if (DEBUG)
				//xil_printf("DEBUG: INSIDE BSP_LEDToggle\n\r");

	INT32U  led_status;

#if OS_CRITICAL_METHOD == 3                        /* Allocate storage for CPU status register         */
	OS_CPU_SR  cpu_sr;
#endif    

	led_status = XGpio_ReadReg(BSP_GPIO_ADDR,1);

	OS_ENTER_CRITICAL();
	switch (led) {
		case 0:
			led_status ^= 0x0000000F;
			XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
			break;
		case 1:
			led_status ^= 0x00000001;
			XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
			break;
		case 2:
			led_status ^= 0x00000002;
			XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
			break;
		case 3:
			led_status ^= 0x00000004;
			XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
			break;
		case 4:
			led_status ^= 0x00000008;
			XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
			break;
	}
	OS_EXIT_CRITICAL();

}

/*
*********************************************************************************************************
*                                               BSP_LEDInit()
*
* Description: This function initializes all of the board's LEDs
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_LEDInit (void)
{
	if (DEBUG)
				xil_printf("DEBUG: INSIDE BSP_LEDInit\n\r");

    XGpio_WriteReg(BSP_GPIO_ADDR, XGPIO_TRI_OFFSET, 0x00000000); 
    BSP_LEDOff(0);                                    /* Turn off all of the LEDs                         */
}

// BUTTON START
/*
*********************************************************************************************************
*                                               button_read()
*
* Description: This function read the button pushed
*
* Arguments  : None
*
* Returns    : INT32U
*********************************************************************************************************
*/
INT32U button_read(void)
{
	//if (DEBUG)
				//xil_printf("DEBUG: INSIDE button_read\n\r");

	INT32U current_state = 0;
	static INT32U button_latched_state = 0;

	// Read the current button input.
	current_state = Button_Get();

	// Check to see if a button is depreseed or not, latch a button press
	// to the upper 16 bits of the latched button state.
	button_latched_state |= (current_state << 16);

	return (button_latched_state | current_state);
}

/*
*********************************************************************************************************
*                                               button_check_state()
*
* Description: This function check the state of button
*
* Arguments  : INT32U bitno, INT32U push_button_state, INT32U push_button_state_change
*
* Returns    : None
*********************************************************************************************************
*/
void button_check_state(INT32U bitno, INT32U push_button_state, INT32U push_button_state_change)
{
	if (DEBUG)
				xil_printf("DEBUG: INSIDE button_check_state\n\r");

	// Check to see if pushbutton EFx has changed state.
	if ((push_button_state_change & (1 << bitno)) == (1 << bitno))
	{
		// Erase current line so that it can be typed over.
		xil_printf("\033[2K");

		// Display the current button state.
		xil_printf("Jboton");

		if (bitno == 0)
		{
			xil_printf("A");
		}
		else if (bitno == 1)
		{
			xil_printf("B");
		}
		else if (bitno == 2)
		{
			xil_printf("C");
		}
		else
		{
			xil_printf("?");
		}

		// EFx state was changed, determine what the new state is.
		if ((push_button_state & (1 << bitno)) == (1 << bitno))
		{
			// The push button was activated.
			xil_printf("_on");
		}
		else
		{
			// The push button was deactivated.
			xil_printf("_off");
		}

		xil_printf("\r");
	}
}

// ---------------------------------------------------------------------------
void button_display_state_all(void)
{
	if (DEBUG)
		xil_printf("DEBUG: INSIDE button_display_state_all\n\r");

	INT32U push_button_state = 0;

	// The current push button state should be read to determine the
	// state of each of the push buttons.
	push_button_state = button_read();

	// Display the current state of the EFA button.
	button_display_state_single(2, push_button_state);

	// Determine the state of the EFB button.
	button_display_state_single(1, push_button_state);

	// Determine the state of the EFC button.
	button_display_state_single(0, push_button_state);

	xil_printf("*   EF4:  Connected To FPGA System Reset                          *\r\n");
}

// ---------------------------------------------------------------------------
void button_display_state_single(INT32U bitno, INT32U push_button_state)
{
	xil_printf("Jboton");

	if (bitno == 0)
	{
		xil_printf("A");
	}
	else if (bitno == 1)
	{
		xil_printf("B");
	}
	else if (bitno == 2)
	{
		xil_printf("C");
	}
	else
	{
		xil_printf("?");
	}

	xil_printf(":  ");

	// EFx state was changed, determine what the new state is.
	if ((push_button_state & (1 << bitno)) == (1 << bitno))
	{
		// The push button was activated.
		xil_printf("_on");
	}
	else
	{
		// The push button was deactivated.
		xil_printf("_off");
	}

	xil_printf("\r");
}

// ---------------------------------------------------------------------------
int button_process(void)
{
	int push_button_index;
	int push_button_change_deteted = BUTTON_STATE_NO_CHANGE;
	INT32U push_button_current_state = 0;
	INT32U push_button_state_change = 0;
	static INT32U push_button_state = 0;

	// The current push button state should be read and compared to the 
	// previous state to determine if a button was pressed or not.
	push_button_current_state = button_read();

	if (push_button_current_state != push_button_state)
	{
		// A button state change was detected, determine which buttons
		// have changed state.  The XOR operator will highlight which 
		// bits have changed state.
		push_button_state_change = push_button_current_state ^ push_button_state;

		for (push_button_index = 0; push_button_index < BUTTON_COUNT; push_button_index++)
		{
			// Check to see if push button EFx has changed state.
			button_check_state(push_button_index, push_button_current_state, push_button_state_change);
		}

		// Update the push button state with the current status.
		push_button_state = push_button_current_state;

		// Since a push button state change was detected, return a 
		// status indicating so.
		push_button_change_deteted = BUTTON_STATE_CHANGE;
	}

	return push_button_change_deteted;
}


/*
*********************************************************************************************************
*                                          BSP_Timer0Handler()
* 
* Description: This function services interrupts produced by the timer counter.  These interrupts serve
*              as uC/OS-II's tick source.

* Arguments  : baseaddr_p     is a pointer to the XTmrCtr driver structure
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_Timer0Handler (void *baseaddr_p)
{
    INT32S  baseaddr;
    INT32U  csr;

    baseaddr = *(INT32S *)baseaddr_p;
    csr      = XTmrCtr_GetControlStatusReg(BSP_TIMER0_ADDR, 0);
    if (csr & XTC_CSR_INT_OCCURED_MASK) {              
        XTmrCtr_SetControlStatusReg(BSP_TIMER0_ADDR, 0, csr);
                                                   /* Notify uC/OS-II that a tick interrupt occurred   */
        OSTimeTick();                                                
    }
}

/*
*********************************************************************************************************
*                                               BSP_TmrInit()
*
* Description: This function should intialize the timers used by your application
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_TmrInit (void)
{
                                                   /* Set the timer's period                           */
    XTmrCtr_SetLoadReg(BSP_TIMER0_ADDR, 0, BSP_TMR_VAL);
                                                   /* Reset the timer                                  */
    XTmrCtr_SetControlStatusReg(BSP_TIMER0_ADDR, 0, XTC_CSR_INT_OCCURED_MASK | XTC_CSR_LOAD_MASK);
                                                   /* Start the timer                                  */
    XTmrCtr_SetControlStatusReg(BSP_TIMER0_ADDR, 0, XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_ENABLE_INT_MASK | XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_DOWN_COUNT_MASK);
}

/*
*********************************************************************************************************
*                                            BSP_IntHandler()
*
* Description: This function is called by OS_CPU_ISR() in os_cpu_a.s to service all active interrupts 
*              from the interrupt controller.  Two versions of this function are provided.  One of these 
*              versions uses the interrupt controller's IVR to determine the highest priority pending 
*              interrupt, while the other version consults the relevant status register.  The code that 
*              uses the IVR is capable of processing interrupts quickly, so the relatively slow code that 
*              uses a status register is excluded with a #if 0 directive.  If, however, your interrupt 
*              controller has been modified from the default configuration and it doesn't offer the IVR, 
*              you will need to place a #if 0 around the faster code, and include the code that is 
*              currently ignored in your project.
*
*              Handlers for devices connected to the interrupt controller can be registered in one of 
*              two ways: via the "Interrupt Handlers" section of your project's "Software Platform
*              Settings", or by calling XIntc_Connect(), which is used to register a handler for the 
*              operating system's tick interrupt in this file's BSP_InitIntCtrl().  Both of these methods 
*              achieve similar results, placing a pointer to your handler in the table accessed by 
*              BSP_IntHandler().  Regardless of which method is used, then, the interrupt corresponding 
*              to your device should be enabled by calling XIntc_Enable() or a similar function.
* 
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/
#if 1
void  BSP_IntHandler (void) 
{	 
                                                   /* This handler uses the interrupt controller's IVR */
    INT32U                  int_status;   
    INT32U                  int_mask;
    INT32U                  int_vector;
    XIntc_Config           *CfgPtr;
    XIntc_VectorTableEntry *tbl_ptr;

    CfgPtr = &XIntc_ConfigTable[0];
    int_status = XIntc_GetIntrStatus(BSP_INTC_ADDR);

    while (int_status != 0) {
                                                   /* Get the interrupts waiting to be serviced        */
        int_vector = *(INT32U *)(BSP_INTC_ADDR + 0x00000018);
        int_mask   = 1 << int_vector;
       
        if (((CfgPtr->AckBeforeService) & int_mask) != 0) {
            XIntc_AckIntr(BSP_INTC_ADDR, int_mask);
        }
        tbl_ptr = &(CfgPtr->HandlerTable[int_vector]);
        tbl_ptr->Handler(tbl_ptr->CallBackRef);    /* Call the handler assigned to the interrupt       */
        if (((CfgPtr->AckBeforeService) & int_mask) == 0) {
            XIntc_AckIntr(BSP_INTC_ADDR, int_mask);
        }
        int_status = XIntc_GetIntrStatus(BSP_INTC_ADDR);
    }
}
#endif

#if 0
void  BSP_IntHandler (void) 
{	 	 
	/* This handler doesn't use the IVR                 */
	
    INT32U    IntrStatus;                                         
    INT32U    IntrMask = 1;                                           
    INT32U    IntrNumber;                                                 
    XIntc_Config *CfgPtr;

    CfgPtr = &XIntc_ConfigTable[(Xuint32)BSP_INTC_DEVICE_ID];

    IntrStatus = XIntc_mGetIntrStatus(CfgPtr->BaseAddress);
  
    for (IntrNumber = 0; IntrNumber < XPAR_INTC_MAX_NUM_INTR_INPUTS;
         IntrNumber++)
    {
        if (IntrStatus & 1)
        {
            XIntc_VectorTableEntry *TablePtr;

            if (CfgPtr->AckBeforeService & IntrMask)
            {
                XIntc_mAckIntr(CfgPtr->BaseAddress, IntrMask);
            }

            TablePtr = &(CfgPtr->HandlerTable[IntrNumber]);
            TablePtr->Handler(TablePtr->CallBackRef);

            if ((CfgPtr->AckBeforeService & IntrMask) == 0)
            {
                XIntc_mAckIntr(CfgPtr->BaseAddress, IntrMask);
            }

            if (CfgPtr->Options == XIN_SVC_SGL_ISR_OPTION)
            {
                return;
            }
        }

        IntrMask <<= 1;
        IntrStatus >>= 1;
  
        if (IntrStatus == 0)
        {
            break;
        }
    } 
}
#endif

/*
*********************************************************************************************************
*                                            BSP_IntDisAll()
* 
* Description: Disable all interrupts at the interrupt controller.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
    if (DEBUG)
		xil_printf("DEBUG: INSIDE BSP_IntDisAll\n\r");

    XIntc_MasterDisable(BSP_INTC_ADDR);
}

/*
*********************************************************************************************************
*                                           BSP_InitIntCtrl()
*
* Description: This function initializes the interrupt controller by registering the appropriate handler
*              functions and enabling interrupts.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_InitIntCtrl (XIic *IicInstPtr, XUartLite *UartLitePtrMSP430, XUartLite *UartLitePtrUSB)
{
    XStatus  init_status;

                                                   /* Initialize a handle for the interrupt controller */
    init_status = XIntc_Initialize(&int_ctl, BSP_INTC_DEVICE_ID);
                                                   /* Connect the first timer with its handler         */
    init_status = XIntc_Connect(&int_ctl, BSP_INTC_TIMER0_ID,BSP_Timer0Handler,(void *)0);
											       /* Connect the IIC device with its handler          */
    init_status = XIntc_Connect(&int_ctl, IIC_INTR_ID,(XInterruptHandler) XIic_InterruptHandler,IicInstPtr);
	                                               /* Connect the MSP430 UART device with its handler  */
    init_status = XIntc_Connect(&int_ctl, MSP430_INTR_ID,(XInterruptHandler)XUartLite_InterruptHandler,
			   (void *)UartLitePtrMSP430);
	                                               /* Connect the USB UART device with its handler     */
    init_status = XIntc_Connect(&int_ctl, USB_INTR_ID,(XInterruptHandler)XUartLite_InterruptHandler,
			   (void *)UartLitePtrUSB);
                                                   /* Enable interrupts from the first timer           */
    XIntc_Enable(&int_ctl, BSP_INTC_TIMER0_ID);
												   /* Enable interrupts from the IIC device            */
    XIntc_Enable(&int_ctl, IIC_INTR_ID);
												   /* Enable interrupts from the MSP430 UART device    */
    XIntc_Enable(&int_ctl, MSP430_INTR_ID);
												   /* Enable interrupts from the USB UART device       */
    XIntc_Enable(&int_ctl, USB_INTR_ID);
                                                   /* Start the interrupt controller                   */
    init_status = XIntc_Start(&int_ctl, XIN_REAL_MODE);
	
	/*
	* Initialize the exception table.
	*/
	//Xil_ExceptionInit();

	/*
	* Register the interrupt controller handler with the exception table.
	*/
	//Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
	//(Xil_ExceptionHandler)XIntc_InterruptHandler,
	//&int_ctl);

	/*
	* Enable exceptions.
	*/
	//Xil_ExceptionEnable();

}


/*
*********************************************************************************************************
*                                           BSP_IicInit()
*
* Description: This function initializes the IIC device
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_IicInit (void)
{
	//u8 Index;
	int Index;
    XStatus  init_status;

                                                   /* Initialize the IIC Instance */
    init_status = XIic_Initialize(&IicInstance, IIC_DEVICE_ID);
												   /* Set the Transmit and Receive handlers */
    XIic_SetSendHandler(&IicInstance, &IicInstance,(XIic_Handler) SendHandler);
    XIic_SetRecvHandler(&IicInstance, &IicInstance,(XIic_Handler) ReceiveHandler);
												   /* Set the address of the slave */
    init_status = XIic_SetAddress(&IicInstance, XII_ADDR_TO_SEND_TYPE,SLAVE_ADDRESS);
	
	/* MSP430 UART */
	
	/* Initialize the instance */
	if (XUartLite_Initialize(&UartLite1, MSP430_DEVICE_ID)!=XST_SUCCESS) printf("Error initialize MSP430" );
	if (XUartLite_SelfTest(&UartLite1)!=XST_SUCCESS) printf("Error selftest MSP430" );
	XUartLite_ResetFifos(&UartLite1);
	/* Set the Transmit and Receive handlers */
	//XUartLite_SetSendHandler(&UartLite1, SendHandlerMSP430, &UartLite1);
	XUartLite_SetRecvHandler(&UartLite1, RecvHandlerMSP430, &UartLite1);
	XUartLite_ResetFifos(&UartLite1);
	/* Enable the interrupt of the UartLite so that interrupts will occur. */
	XUartLite_EnableInterrupt(&UartLite1);
	
	
	/* USB UART */
	
	/* Initialize the instance */
	if (XUartLite_Initialize(&UartLite2, USB_DEVICE_ID)!=XST_SUCCESS) printf("Error initialize USB" );
	if (XUartLite_SelfTest(&UartLite2)!=XST_SUCCESS) printf("Error selftest USB" );
	XUartLite_ResetFifos(&UartLite2);
	/* Set the Transmit and Receive handlers */
	//XUartLite_SetSendHandler(&UartLite2, SendHandlerUSB, &UartLite2);
	XUartLite_SetRecvHandler(&UartLite2, RecvHandlerUSB, &UartLite2);
	XUartLite_ResetFifos(&UartLite2);
	/* Enable the interrupt of the UartLite so that interrupts will occur. */
	XUartLite_EnableInterrupt(&UartLite2);
	
	/*
	* Initialize the send buffer bytes with a pattern to send and the
	* the receive buffer bytes to zero to allow the receive data to be
	* verified.
	*/
	for (Index = 0; Index < TEST_BUFFER_SIZE; Index++) {
		SendBuffer[Index] = Index;
		ReceiveBuffer[Index] = 0;
	}
	
	/*
	 * Write two bytes to the IIC Slave to set the PointerRegister to
     *   address the Configuration Register and set it to 12-bit
     *   resolution (r[1:0] = b11).
	 */
	WriteBuffer[0] = 0x01;  // Address Configuration register
	WriteBuffer[1] = 0x60;  // Set 12-bit resolution
	WriteData(2);
	/*
	 * Write one byte to the IIC Slave to set the PointerRegister to
     *   address the Temperature Register
	 */
	WriteBuffer[0] = 0;
	WriteData(1);
	/*
     * Initialize the the read buffer (temperature)
	 */
	for (Index = 0; Index < SEND_COUNT; Index++) {
		ReadBuffer[Index] = 0;
	}
}

/*
*********************************************************************************************************
*                                           SendHandler()
*
* Description: This Send handler is called asynchronously from an interrupt context and
* indicates that data in the specified buffer has been sent.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/
void SendHandler(XIic * InstancePtr)
{
	TransmitComplete = 0;
}

/*
*********************************************************************************************************
*                                           ReceiveHandler()
*
* Description: This Send handler is called asynchronously from an interrupt context and
* indicates that data in the specified buffer has been received.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/
void ReceiveHandler(XIic * InstancePtr)
{
	ReceiveComplete = 0;
}

/*****************************************************************************/
/**
*
* This function is the handler which performs processing to send data to the
* UartLite. It is called from an interrupt context such that the amount of
* processing performed should be minimized. It is called when the transmit
* FIFO of the UartLite is empty and more data can be sent through the UartLite.
*
* This handler provides an example of how to handle data for the UartLite,
* but is application specific.
*
* @param	CallBackRef contains a callback reference from the driver.
*		In this case it is the instance pointer for the UartLite driver.
* @param	EventData contains the number of bytes sent or received for sent
*		and receive events.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
/*
void SendHandlerMSP430(void *CallBackRef, unsigned int EventData)
{
	//XTft_Write(&TftInstance,'S');
	TotalSentCountMSP430 = EventData;
	if (DEBUG)
		xil_printf("DEBUG: INSIDE SendHandlerMSP430\n\r");
}
*/
/****************************************************************************/
/**
*
* This function is the handler which performs processing to receive data from
* the UartLite. It is called from an interrupt context such that the amount of
* processing performed should be minimized.  It is called data is present in
* the receive FIFO of the UartLite such that the data can be retrieved from
* the UartLite. The size of the data present in the FIFO is not known when
* this function is called.
*
* This handler provides an example of how to handle data for the UartLite,
* but is application specific.
*
* @param	CallBackRef contains a callback reference from the driver, in
*		this case it is the instance pointer for the UartLite driver.
* @param	EventData contains the number of bytes sent or received for sent
*		and receive events.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void RecvHandlerMSP430(void *CallBackRef, unsigned int EventData)
{
	unsigned int ReceivedCount = 0;
	int Index;
	int i=0;
	int newBuffer = TEST_BUFFER_SIZE -1;
	u8 data;

	TotalReceivedCountMSP430 = EventData;
	
	if (DEBUG)
		xil_printf("DEBUG: INSIDE RecvHandlerMSP430\n\r");
	
	while (1) {
		ReceivedCount += XUartLite_Recv(&UartLite1,
					   ReceiveBuffer + ReceivedCount,
					   TEST_BUFFER_SIZE - ReceivedCount);
		if (ReceivedCount == TEST_BUFFER_SIZE) {
			if (DEBUG)
				xil_printf("DEBUG: RecvHandlerMSP430 TEST_BUFFER_SIZE exit\n\r");
			break;
		}
		/*
		if (ReceivedCount == newBuffer) {
			if (DEBUG)
				xil_printf("DEBUG: RecvHandlerMSP430 newBuffer exit\n\r");
			break;
		}
		if ( (ReceiveBuffer[i] == 0x0d) && (i>0) ) {
			if (DEBUG)
				xil_printf("DEBUG: RecvHandlerMSP430 0x0d i \n\r");
			break;
		}
		++i;
		*/
	}
	if (DEBUG)
		xil_printf("DEBUG: RecvHandlerMSP430 while exit!\n\r");
	/* check received message structure
	*  [0] = data is from (3 = C = x43) or (6 = F = x46) or (9 = I = x49)
	*  [1] = data is from (R = x52) or (W = x57)
	*  [7] = data is from (\r = x0d = d13)
	*/
	if ( (ReceiveBuffer[0]==0x43) || (ReceiveBuffer[0]==0x46) || (ReceiveBuffer[0]==0x49) )
	{
		if ( (ReceiveBuffer[1]==0x52) || (ReceiveBuffer[1]==0x57) )
		{
			if ( ReceiveBuffer[7]==0x0d )
			{
				/* set semaphore */
				sCommandSem = 1;
			}
		}
	}
	/* mensaje recibido por comprobación de la estructura */
	if (sCommandSem)
	{
		if ( waitingresponse == 0 )
		{
			/* process command received */
			if (DEBUG)
				xil_printf("DEBUG: RecvHandlerMSP430 waitingresponse=0\n\r");
			
			/* save command */
			for (i=0; i<=(SIZE_COMANDO-1); ++i) // maximo = SIZE_COMANDO-1
			{
				comando[i] = ReceiveBuffer[i+1]; // el comando no tiene cabecera, empiezo desde el 1
			}
		
			if ( cmd_check("R") )
			{
				/* read message = response, set header */
				
				/* set header */
				switch (ReceiveBuffer[0])
				{
					case 0x43: // mensaje C (3): PC->FG
						headResponseData = 0x4A; // mensaje J (10): FG->PC
						break;
					case 0x46: // mensaje F (6): AP->FG
						headResponseData = 0x4B; // mensaje K (11): FG->AP
						break;
					case 0x49: // mensaje I (9): ED->FG
						headResponseData = 0x4C; // mensaje L (12): FG->ED
						break;
					default: ;
				}
			}
			
			if ( cmd_check("W") )
			{
				/* write message = no response, only process */
				headResponseData = 0x00;
			}
		}
		else
		{
			/* return data received to USB UART */
			if (DEBUG)
				xil_printf("DEBUG: RecvHandlerMSP430 waitingresponse=1\n\r");

			/* clear semaphore */
			sCommandSem = 0;
			waitingresponse = 0;
		}
		
		/* DEBUG: print buffer */
		/*
		for (Index = 0; Index <= newBuffer; Index++) {
			if ( (ReceiveBuffer[Index]!=0x0D) && (ReceiveBuffer[Index]!=0x0A) )
			{
				xil_printf("%c",ReceiveBuffer[Index]);
			}
		}
		xil_printf("\r\n");
		*/
		
		/* DEBUG: see data */
		for (Index = 0; Index < TEST_BUFFER_SIZE; Index++) {
			xil_printf("tecla: ");
			if (ReceiveBuffer[Index]==0x0D)
			{
				xil_printf(" (0x0D");
			}
			else if (ReceiveBuffer[Index]==0x0A)
			{
				xil_printf(" (0x0A");
			}
			else
			{
				xil_printf("%c (",ReceiveBuffer[Index]); xil_printf("0x%x",ReceiveBuffer[Index]);
			}
			xil_printf(")\r\n");
		}
	}
	/*
	if(!XUartLite_IsReceiveEmpty(XPAR_MSP430_UART_BASEADDR)) {
		data = XUartLite_ReadReg(XPAR_MSP430_UART_BASEADDR, XUL_RX_FIFO_OFFSET); // receive FIFO, read only
		xil_printf("DEBUG: enviaMSP430 data:%x\n\r",data);
	}
	*/
	/* reset fifos */
	//if (DEBUG)
		//xil_printf("DEBUG: RecvHandlerMSP430 reset fifos!\n\r");
	//XUartLite_ResetFifos(&UartLite1);
	//XUartLite_EnableIntr(XPAR_MSP430_UART_BASEADDR);
	
	if (DEBUG)
		xil_printf("DEBUG: RecvHandlerMSP430 EXIT!\n\r");
}

/*****************************************************************************/
/**
*
* This function is the handler which performs processing to send data to the
* UartLite. It is called from an interrupt context such that the amount of
* processing performed should be minimized. It is called when the transmit
* FIFO of the UartLite is empty and more data can be sent through the UartLite.
*
* This handler provides an example of how to handle data for the UartLite,
* but is application specific.
*
* @param	CallBackRef contains a callback reference from the driver.
*		In this case it is the instance pointer for the UartLite driver.
* @param	EventData contains the number of bytes sent or received for sent
*		and receive events.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
/*
void SendHandlerUSB(void *CallBackRef, unsigned int EventData)
{
	//XTft_Write(&TftInstance,'S');
	TotalSentCountUSB = EventData;
	if (DEBUG)
		xil_printf("DEBUG: INSIDE SendHandlerUSB\n\r");
}
*/
/****************************************************************************/
/**
*
* This function is the handler which performs processing to receive data from
* the UartLite. It is called from an interrupt context such that the amount of
* processing performed should be minimized.  It is called data is present in
* the receive FIFO of the UartLite such that the data can be retrieved from
* the UartLite. The size of the data present in the FIFO is not known when
* this function is called.
*
* This handler provides an example of how to handle data for the UartLite,
* but is application specific.
*
* @param	CallBackRef contains a callback reference from the driver, in
*		this case it is the instance pointer for the UartLite driver.
* @param	EventData contains the number of bytes sent or received for sent
*		and receive events.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void RecvHandlerUSB(void *CallBackRef, unsigned int EventData)
{
	unsigned int ReceivedCount = 0;
	int Index;
	int i=0;
	int newBuffer = TEST_BUFFER_SIZE -1;
	u8 data;
	
	TotalReceivedCountUSB = EventData;
	
	if (DEBUG)
		xil_printf("DEBUG: INSIDE RecvHandlerUSB\n\r");
	
	while (1) {
		ReceivedCount += XUartLite_Recv(&UartLite2,
					   ReceiveBuffer + ReceivedCount,
					   newBuffer - ReceivedCount);
		if ( ReceivedCount == newBuffer ) {
			break;
		}
		if ( (ReceiveBuffer[i] == 0x0d) && (i>0) ) {
			break;
		}
		++i;
	}
	
	/* check received message structure
	*  [0] = data is from (10 = J = x4A) or (11 = K = x4B) or (12 = L = x4C)
	*  [1] = data is from (R = x52) or (W = x57)
	*  [7] = data is from (\r = x0d = d13)
	*/
	if ( (ReceiveBuffer[0]==0x4A) || (ReceiveBuffer[0]==0x4B) || (ReceiveBuffer[0]==0x4C) )
	{
		if ( (ReceiveBuffer[1]==0x52) || (ReceiveBuffer[1]==0x57) )
		{
			if ( ReceiveBuffer[7]==0x0d )
			{
				/* set semaphore */
				sSendUARTMSP430Sem = 1;
			}
		}
	}
	/* send data using UART MSP430 */
	if (sSendUARTMSP430Sem)
	{
		/* save command */
		for (i=0; i<=(SIZE_COMANDO-1); ++i) // maximo = SIZE_COMANDO-1
		{
			comando[i] = ReceiveBuffer[i+1]; // el comando no tiene cabecera, empiezo desde el 1
		}
		
		if ( cmd_check("R") )
		{
			/* set semaphore */
			waitingresponse = 1;
		}
		
		/* print buffer */
		for (Index = 0; Index <= newBuffer; Index++) {
			if (ReceiveBuffer[Index]==0x0D)
			{
				//xil_printf(" (0x0D");
			}
			else if (ReceiveBuffer[Index]==0x0A)
			{
				//xil_printf(" (0x0A");
			}
			else
			{
				xil_printf("%c",ReceiveBuffer[Index]);
			}
			//xil_printf(")\r\n");
		}
		xil_printf("\r\n");
	}
	/*
	if(!XUartLite_IsReceiveEmpty(XPAR_MSP430_UART_BASEADDR)) {
		data = XUartLite_ReadReg(XPAR_MSP430_UART_BASEADDR, XUL_RX_FIFO_OFFSET); // receive FIFO, read only
		xil_printf("DEBUG: enviaMSP430 data:%x\n\r",data);
	}
	*/
	
	/* reset fifos */
	//XUartLite_ResetFifos(&UartLite2);
	//XUartLite_EnableIntr(XPAR_USB_UART_BASEADDR);
}

void enviaMSP430(u8 data2MSP430[])
{
	int newBuffer = TEST_BUFFER_SIZE -1;
	int Index=0;
	u8 data;
	
	if (DEBUG)
		xil_printf("DEBUG: enviaMSP430()\n\r");
	if (sSendUARTMSP430Sem)
	{
		if (DEBUG)
			xil_printf("DEBUG: enviaMSP430 sSendUARTMSP430Sem=1\n\r");
		/*
		if(!XUartLite_IsReceiveEmpty(XPAR_MSP430_UART_BASEADDR)) {
			data = XUartLite_ReadReg(XPAR_MSP430_UART_BASEADDR, XUL_RX_FIFO_OFFSET); // receive FIFO, read only
			xil_printf("DEBUG: enviaMSP430 data1:%x\n\r",data);
		}
		*/
		
		/* disable interruptions */
		if (DEBUG)
			xil_printf("DEBUG: enviaMSP430 inter disable\n\r");
		//XUartLite_DisableIntr(XPAR_MSP430_UART_BASEADDR);
		XUartLite_DisableInterrupt(&UartLite1);
		
		/* send using MPS430 UART */
		if (DEBUG)
				xil_printf("DEBUG: enviaMSP430 start send\n\r");
		for (Index = 0; Index <= newBuffer; Index++) {
			XUartLite_SendByte(XPAR_MSP430_UART_BASEADDR,data2MSP430[Index]);
		}
		
		/* wait in a loop until send */
		while ( XUartLite_IsSending(&UartLite1) );
		if (DEBUG)
				xil_printf("DEBUG: enviaMSP430 end send\n\r");
		
		/* clear semaphore */
		sSendUARTMSP430Sem = 0;
		
		/* clear ReceiveBuffer */
		if (DEBUG)
				xil_printf("DEBUG: enviaMSP430 clear ReceiveBuffer\n\r");
		for (Index = 0; Index < TEST_BUFFER_SIZE; Index++) {
			ReceiveBuffer[Index] = 0;
		}
		
		/* enable interruptions */
		if (DEBUG)
			xil_printf("DEBUG: enviaMSP430 inter enable\n\r");
		//XUartLite_EnableIntr(XPAR_MSP430_UART_BASEADDR);
		XUartLite_EnableInterrupt(&UartLite1);
	}
	
	if (DEBUG)
		xil_printf("DEBUG: enviaMSP430 EXIT\n\r");
}

void procesa_comandos(void)
{
	INT32U  led_status;
	INT32U  button_status;
	int bit;
	int data;
	int decimals;
	int newBuffer = TEST_BUFFER_SIZE -1;
	int Index;
	
	if (DEBUG)
			xil_printf("DEBUG: procesa_comandos()\n\r");
	
	if (sCommandSem)
	{
		if (DEBUG)
			xil_printf("DEBUG: procesa_comandos sCommandSem=1\n\r");
		
		// bit
		if (comando[2]=='0')
		{
			bit = BIT0;
		}
		if (comando[2]=='1')
		{
			bit = BIT1;
		}
		if (comando[2]=='2')
		{
			bit = BIT2;
		}
		if (comando[2]=='3')
		{
			bit = BIT3;
		}
		if (comando[2]=='4')
		{
			bit = BIT4;
		}
		if (comando[2]=='5')
		{
			bit = BIT5;
		}
		if (comando[2]=='6')
		{
			bit = BIT6;
		}
		if (comando[2]=='7')
		{
			bit = BIT7;
		}
		
		/* write message */
		if ( cmd_check("W") )
		{
			// data
			if (comando[5]=='1')
			{
				data = 1;
			}
			if (comando[5]=='0')
			{
				data = 0;
			}
			
			/* read led status */
			led_status = XGpio_ReadReg(BSP_GPIO_ADDR,1);
			if (data)
			{
				//led off
				led_status &= ~bit;
				XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
			} else {
				//led on
				led_status |= bit;
				XGpio_WriteReg(BSP_GPIO_ADDR,1,led_status);
			}
			
			/* debug */
			if ( cmd_check("Wdebug") )
			{
				if (DEBUG)
				{
					DEBUG = 0;
				}
				else
				{
					DEBUG = 1;
				}
			}
		}
		
		/* read message */
		if ( cmd_check("R") )
		{
			/* temperature */
			if ( cmd_check("R50000") )
			{
				ReadData(ReadBuffer, 2);
				/*
				 * El primer byte representa la part sencera de la lectura de 
				 *  temperatura en graus Celsius
				 * El segon byte es la part decimal de la temperatura
				 * Els quatre bits menys significatius del segon byte
				 * es descarten. Els quatre bits restants representen
				 * la part decimal de la tempetarura en fraccions de
				 * 1/16 de grau
				 */
				decimals = (ReadBuffer[1]>>4)*10000/16;
				xil_printf("Temperatura actual:  %d.%04d graus\n\r", ReadBuffer[0], decimals );
				
				SendBuffer[0] = headResponseData;
				SendBuffer[1] = 0x52; // R
				SendBuffer[2] = 0x35; // 5
				SendBuffer[3] = (ReadBuffer[0] / 10)+0x30;
				SendBuffer[4] = (ReadBuffer[0] % 10)+0x30; //atoi ( ReadBuffer[0] ); // ( "%d", ReadBuffer[0] );
				SendBuffer[5] = (decimals / 1000)+0x30;//atoi ( (ReadBuffer[1]>>4)*10000/16 ); //sprintf ( "%02d", ((ReadBuffer[1]>>4)*10000/16) );
				SendBuffer[6] = ((decimals % 1000)/100)+0x30; //0x30; // 0
				SendBuffer[7] = 0x0d; // 0x0d = \r = 13d
			}
			if ( cmd_check("R2") )
			{
				
				SendBuffer[0] = headResponseData;
				SendBuffer[1] = 0x52; // R
				SendBuffer[2] = 0x32; // 2
				
				SendBuffer[4] = 0x30; // 0
				SendBuffer[5] = 0x30; // 0
				
				button_status = XGpio_ReadReg(BSP_BUTTON_ADDR,1);
				if ( (button_status & bit) == bit )
				{
					SendBuffer[6] = 0x31; // 1
				}
				else
				{
					SendBuffer[6] = 0x30; // 0
				}
				
				SendBuffer[7] = 0x0d; // 0x0d = \r = 13d
				/* button 1 */
				if ( cmd_check("R20000") )
				{
					SendBuffer[3] = 0x30; // 0
				}
				/* button 2 */
				if ( cmd_check("R21000") )
				{
					SendBuffer[3] = 0x31; // 1
				}
				/* button 3 */
				if ( cmd_check("R22000") )
				{
					SendBuffer[3] = 0x32; // 2
				}
			}
		}
		
		if (headResponseData != 0x00)
		{
			/* set semaphore */
			sSendUARTMSP430Sem = 1;
			
			/* send */
			if (DEBUG)
				xil_printf("DEBUG: procesa_comandos SendBuffer\n\r");

			for (Index = 0; Index <= newBuffer; Index++) {
				ReceiveBuffer[Index] = SendBuffer[Index];
			}
			//enviaMSP430(SendBuffer);
		}
		
		/* clear semaphore */
		sCommandSem = 0;
	}
}

void setEDaddress(void)
{
	// set ED address
	sSendUARTMSP430Sem=1;
	ReceiveBuffer[0] = 0x4C; // L;
	ReceiveBuffer[1] = 0x57; // W;
	ReceiveBuffer[2] = 0x36; // 6;
	ReceiveBuffer[3] = 0x30; // 0;
	ReceiveBuffer[4] = 0x31; // 1;
	ReceiveBuffer[5] = 0x32; // 2;
	ReceiveBuffer[6] = 0x33; // 3;
	ReceiveBuffer[7] = 0x0d; // \r;
	enviaMSP430(ReceiveBuffer);
}

void setAPaddress(void)
{
	// set AP address
	sSendUARTMSP430Sem=1;
	ReceiveBuffer[0] = 0x4C; // L;
	ReceiveBuffer[1] = 0x57; // W;
	ReceiveBuffer[2] = 0x36; // 6;
	ReceiveBuffer[3] = 0x31; // 1;
	ReceiveBuffer[4] = 0x61; // a;
	ReceiveBuffer[5] = 0x62; // b;
	ReceiveBuffer[6] = 0x63; // c;
	ReceiveBuffer[7] = 0x0d; // \r;
	enviaMSP430(ReceiveBuffer);
}

void setEDconfig(void)
{
	// config as ED
	sSendUARTMSP430Sem=1;
	ReceiveBuffer[0] = 0x4C; // L;
	ReceiveBuffer[1] = 0x57; // W;
	ReceiveBuffer[2] = 0x36; // 6;
	ReceiveBuffer[3] = 0x32; // 2;
	ReceiveBuffer[4] = 0x30; // 0;
	ReceiveBuffer[5] = 0x30; // 0;
	ReceiveBuffer[6] = 0x30; // 0;
	ReceiveBuffer[7] = 0x0d; // \r;
	enviaMSP430(ReceiveBuffer);
}

/*
*********************************************************************************************************
*                                              BSP_InitIO()
* 
* Description: Initialize all the I/O devices.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_InitIO (void)    
{
	BSP_InitIntCtrl(&IicInstance, &UartLite1, &UartLite2); /* Initialize the interrupt controller */
	BSP_TmrInit();                                 /* Initialize the timers                            */
    BSP_LEDInit();                                    /* Initialize LEDs                        */
	BSP_IicInit();                                 /* Initialize the timers                            */
}


