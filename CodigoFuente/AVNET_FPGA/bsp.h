/*
*********************************************************************************************************
* Author : FQuinto
* File: bsp.h
* v. 1.00   | 2012-06-14 | First release
*********************************************************************************************************
*/

#ifndef _BSP_H_
#define _BSP_H_

#include   "includes.h"

/*
*********************************************************************************************************
*                                             CONSTANTS
*********************************************************************************************************
*/

#define  BSP_INTC_DEVICE_ID     XPAR_INTC_0_DEVICE_ID
#define  BSP_INTC_TIMER0_ID     XPAR_INTC_0_TMRCTR_0_VEC_ID
#define  BSP_INTC_ADDR          XPAR_INTC_0_BASEADDR
#define  BSP_TIMER0_ADDR        XPAR_XPS_TIMER_0_BASEADDR

#define  BSP_GPIO_ADDR          XPAR_LEDS_4BIT_BASEADDR
#define  BSP_TMR_VAL            (XPAR_CPU_DPLB_FREQ_HZ / OS_TICKS_PER_SEC)
#define  BSP_BUTTON_ADDR        XPAR_CS_PUSH_3BIT_BASEADDR


// BUTTON START
// Define the number of available push buttons.
#define BUTTON_COUNT								3
// Define the return states for the button_process.
#define BUTTON_STATE_NO_CHANGE						0
#define BUTTON_STATE_CHANGE							1
// BUTTON END

#define IIC_DEVICE_ID               XPAR_IIC_0_DEVICE_ID
#define INTC_DEVICE_ID              XPAR_INTC_0_DEVICE_ID
#define IIC_INTR_ID                 XPAR_INTC_0_IIC_0_VEC_ID

// MSP430 UART
#define MSP430_DEVICE_ID            XPAR_UARTLITE_1_DEVICE_ID
#define MSP430_INTR_ID              XPAR_INTC_0_UARTLITE_1_VEC_ID

// USB UART
#define USB_DEVICE_ID               XPAR_UARTLITE_2_DEVICE_ID
#define USB_INTR_ID                 XPAR_INTC_0_UARTLITE_2_VEC_ID

/*
 * The following constant controls the length of the buffers to be sent
 * and received with the UartLite device.
 */
#define TEST_BUFFER_SIZE        8

/*
 * The following constant defines the address of the IIC
 * device on the IIC bus. This is the 7-bit value found
 * in the TMP100 datasheet for ADD[1:0] = b00.
 */
#define SLAVE_ADDRESS 0x48

#define SEND_COUNT      TEST_BUFFER_SIZE
#define RECEIVE_COUNT   TEST_BUFFER_SIZE

#define SIZE_COMANDO  6

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80
/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/
void  BSP_TmrInit            (void);
void  BSP_Init               (void);
void  BSP_IntDisAll          (void);
void  BSP_InitIntCtrl        (XIic * IicInstPtr, XUartLite *UartLitePtrMSP430, XUartLite *UartLitePtrUSB);
void  BSP_InitIO             (void);
void  BSP_IicInit            (void);

void enviaMSP430(u8 data2MSP430[]);

// LED START
INT32U LED_Get (void);
void BSP_LEDToggle (INT8U led);
void BSP_LEDOff (INT8U led);
void BSP_LEDOn (INT8U led);
void BSP_LEDInit (void);
// LED END

// TEMP START
void SendHandler (XIic * InstancePtr);
void ReceiveHandler (XIic * InstancePtr);
// TEMP END

// BUTTON START
INT32U Button_Get (void);
INT32U button_read (void);
int button_process (void);
void button_display_state_all (void);
void button_display_state_single (INT32U bitno, INT32U push_button_state);
// BUTTON END

// MSP430 and USB UART START
//void SendHandlerMSP430(void *CallBackRef, unsigned int EventData);
void RecvHandlerMSP430(void *CallBackRef, unsigned int EventData);
//void SendHandlerUSB(void *CallBackRef, unsigned int EventData);
void RecvHandlerUSB(void *CallBackRef, unsigned int EventData);
// MSP430 and USB UART END

void procesa_comandos(void);
void setEDaddress(void);
void setAPaddress(void);
void setEDconfig(void);
/*
*********************************************************************************************************
*                                             Variable Definitions
*********************************************************************************************************
*/
XIic IicInstance;
volatile u8 TransmitComplete;
volatile u8 ReceiveComplete;
u8 WriteBuffer[SEND_COUNT];	/* Write buffer for writing a page. */
u8 ReadBuffer[RECEIVE_COUNT];	/* Read buffer for reading a page. */

u8 DEBUG;

INT8U comando[SIZE_COMANDO];


/*
 * The following buffers are used in this example to send and receive data
 * with the UartLite.
 */
u8 SendBuffer[TEST_BUFFER_SIZE];	/* Buffer for Transmitting Data */
u8 ReceiveBuffer[TEST_BUFFER_SIZE];	/* Buffer for Receiving Data */


/*
 * The following counters are used to determine when the entire buffer has
 * been sent and received.
 */
static volatile int TotalReceivedCountMSP430;
//static volatile int TotalSentCountMSP430;
static volatile int TotalReceivedCountUSB;
//static volatile int TotalSentCountUSB;
/*
*********************************************************************************************************
*                                           WriteData()
*
* Description: This function writes a buffer of data to IIC Slave
*
* Arguments  : ByteCount contains the number of bytes in the buffer to be written
*
* Returns    : None
*********************************************************************************************************
*/
static void WriteData(u16 ByteCount)
{
	int Status;
	int BusBusy;

	/*
	 * Set the defaults.
	 */
	TransmitComplete = 1;

	/*
	 * Start the IIC device.
	 */
	Status = XIic_Start(&IicInstance);

	/*
	 * Set the Repeated Start option.
	 */
	IicInstance.Options = XII_REPEATED_START_OPTION;

	/*
	 * Send the data.
	 */
	Status = XIic_MasterSend(&IicInstance, WriteBuffer, ByteCount);

	/*
	 * Wait till data is transmitted.
	 */
	while (TransmitComplete) {

	}

	/*
	 * This is for verification that Bus is not released and still Busy.
	 */
	BusBusy = XIic_IsIicBusy(&IicInstance);

	TransmitComplete = 1;
	IicInstance.Options = 0x0;

	/*
	 * Send the Data.
	 */
	Status = XIic_MasterSend(&IicInstance, WriteBuffer, ByteCount);

	/*
	 * Wait till data is transmitted.
	 */
	while ((TransmitComplete) || (XIic_IsIicBusy(&IicInstance) == TRUE)) {

	}

	/*
	 * Stop the IIC device.
	 */
	Status = XIic_Stop(&IicInstance);
}

/*
*********************************************************************************************************
*                                           ReadData()
*
* Description:  This function reads a data from the IIC Slave into a specified buffer.
*
* Arguments  : 	BufferPtr contains the address of the data buffer to be filled
* 				ByteCount contains the number of bytes to be read.
*
* Returns    : None
*********************************************************************************************************
*/
static void ReadData(u8 *BufferPtr, u16 ByteCount)
{
	int Status;
	int BusBusy;

	/*
	 * Set the defaults.
	 */
	ReceiveComplete = 1;

	/*
	 * Start the IIC device.
	 */
	Status = XIic_Start(&IicInstance);

	/*
	 * Set the Repeated Start option.
	 */
	IicInstance.Options = XII_REPEATED_START_OPTION;

	/*
	 * Receive the data.
	 */
	Status = XIic_MasterRecv(&IicInstance, BufferPtr, ByteCount);

	/*
	 * Wait till all the data is received.
	 */
	while (ReceiveComplete) {

	}

	/*
	 * This is for verification that Bus is not released and still Busy.
	 */
	BusBusy = XIic_IsIicBusy(&IicInstance);

	ReceiveComplete = 1;
	IicInstance.Options = 0x0;

	/*
	 * Receive the Data.
	 */
	Status = XIic_MasterRecv(&IicInstance, BufferPtr, ByteCount);

	/*
	 * Wait till all the data is received.
	 */
	while ((ReceiveComplete) || (XIic_IsIicBusy(&IicInstance) == TRUE)) {

	}

	/*
	 * Stop the IIC device.
	 */
	Status = XIic_Stop(&IicInstance);
}

#endif /* _BSP_H_ */
