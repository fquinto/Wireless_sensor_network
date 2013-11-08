/*
*********************************************************************************************************
* Author : FQuinto
* File: virtual_com_cmds_TOT.c
* v. 1.00   | 2012-07-16 | First release
*********************************************************************************************************
*/
#include <string.h>
#include "bsp.h"
#include "virtual_com_cmds_TOT.h"

/******************************************************************************/
// End Virtual Com Port Communication
/******************************************************************************/
void COM_Init(void)
{  
  P3SEL |= 0x30;                            // P3.4,5 = USCI_A0 TXD/RXD
  UCA0CTL1 = UCSSEL_2;                      // SMCLK
  UCA0BR0 = 0x41;                           // 9600 from 8Mhz - (UCAxBR0 + UCAxBR1x256)=preescaler
  UCA0BR1 = 0x3;							//   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 
  UCA0MCTL = UCBRS_2;                       
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
  __enable_interrupt(); 
}

void serial_log( char* string )
{
  int j;
  int length = strlen(string);
  for( j = 0; j < length; j++)
  {
    volatile int i;
	while (!(IFG2&UCA0TXIFG)); // USCI_A0 TX buffer ready?
    UCA0TXBUF = string[j]; // send data to UART
  }
}

void UART_write( const char *string, int length)
{
	int i;
	for( i = 0; i < length; i++)
	{
		if (string[i]==0x0d)
		{
			break;
		}
		else
		{
			UART_putChar (string[i]);
		}
	}
}

void UART_putChar (char c)
{
	while (!(IFG2&UCA0TXIFG));
	UCA0TXBUF = c; // send data to UART
}

void transmitDataString( int isAP, signed char rssi, char msg[MESSAGE_LENGTH], int uart, int type )
{
  char temp_string[] = {" XX.XC"};
  int temp = msg[0] + (msg[1]<<8);
  char rssiString[3];
  volatile signed int rssi_int;
  /*
  if(!(degCMode))
  {
    temp = (((float)temp)*1.8)+320;
    temp_string[5] = 'F';
  }
  */
  if( temp < 0 )
  {
    temp_string[0] = '-';
    temp = temp * -1;
  }
  else if( ((temp/1000)%10) != 0 )
  {
    temp_string[0] = '0'+((temp/1000)%10);
  }
  temp_string[4] = '0'+(temp%10);
  temp_string[2] = '0'+((temp/10)%10);
  temp_string[1] = '0'+((temp/100)%10);
  
  rssi_int = (signed int) rssi;
  rssi_int = rssi_int+128;
  rssi_int = (rssi_int*100)/256;
  rssiString[0] = '0'+(rssi_int%10);
  rssiString[1] = '0'+((rssi_int/10)%10);
  rssiString[2] = '0'+((rssi_int/100)%10);
  
  if(uart)
  {
	/* to uart */
    //char output_verbose[] = {"xNode:XX,Temp:-XX.XC,Battery:X.XV,Strength:XXX%\r\n"};
	char output_verbose[] = {"xR5xxxx\r\n"};
	
	if (isAP==1)
	{
		output_verbose[0] = 'D';
		/* Node */
		//output_verbose[6] = 'A';
		//output_verbose[7] = 'P';
	}
	if (isAP==0)
	{
		output_verbose[0] = 'I';
		/* Node */
		//output_verbose[6] = 'E';
		//output_verbose[7] = 'D';
	}
    // answer with R from read
	output_verbose[1] = 'R';
	
	// type: 0 = Temperature, 1 = RSSI, 2 = Voltage
	switch (type)
	{
		case 0: // Temperature (50)
			/* Temperature */
			/*
			output_verbose[14] = temp_string[0]; // sign
			output_verbose[15] = temp_string[1];
			output_verbose[16] = temp_string[2];
			output_verbose[17] = temp_string[3]; // point
			output_verbose[18] = temp_string[4];
			output_verbose[19] = temp_string[5]; // unit
			*/
			output_verbose[2] = '5';
			output_verbose[3] = '0';
			output_verbose[4] = temp_string[1];
			output_verbose[5] = temp_string[2];
			output_verbose[6] = temp_string[4];
			break;
		case 1: // RSSI (51)
			/* Strength signal: RSSI */
			/*
			output_verbose[43] = rssiString[2];
			output_verbose[44] = rssiString[1];
			output_verbose[45] = rssiString[0];
			*/
			output_verbose[2] = '5';
			output_verbose[3] = '1';
			output_verbose[4] = rssiString[2];
			output_verbose[5] = rssiString[1];
			output_verbose[6] = rssiString[0];
			break;
		case 2: // Voltage (52)
			/* Batery voltage */
			/*
			output_verbose[29] = '0'+(msg[2]/10)%10;
			output_verbose[31] = '0'+(msg[2]%10);
			*/
			output_verbose[2] = '5';
			output_verbose[3] = '2';
			output_verbose[4] = '0'+(msg[2]/10)%10;
			output_verbose[5] = '0'+(msg[2]%10);
			output_verbose[6] = '0';
			break;
	}
	
    serial_log(output_verbose); // send data to UART
  }
  else
  {
	/* to radio */
    //char output_short[] = {"xxx,-XX.X,VV,RSI"};
	char output_short[] = {"xR5xxxx"};
	
	if (isAP==1)
	{
		output_short[0] = 'F';
		/* Node */
		//output_short[1] = 'A';
		//output_short[2] = 'P';
	}
	if (isAP==0)
	{
		output_short[0] = 'G';
		/* Node */
		//output_short[1] = 'E';
		//output_short[2] = 'D';
	}
    // answer with R from read
	output_short[1] = 'R';
	
    // type: 0 = Temperature, 1 = RSSI, 2 = Voltage
	switch (type)
	{
		case 0: // Temperature (50)
			/* Temperature */
			output_short[2] = '5';
			output_short[3] = '0';
			output_short[4] = temp_string[1];
			output_short[5] = temp_string[2];
			output_short[6] = temp_string[4];
			break;
		case 1: // RSSI (51)
			/* Strength signal: RSSI */
			output_short[2] = '5';
			output_short[3] = '1';
			output_short[4] = rssiString[2];
			output_short[5] = rssiString[1];
			output_short[6] = rssiString[0];
			break;
		case 2: // Voltage (52)
			/* Batery voltage */
			output_short[2] = '5';
			output_short[3] = '2';
			output_short[4] = '0'+(msg[2]/10)%10;
			output_short[5] = '0'+(msg[2]%10);
			output_short[6] = '0';
			break;
	}
	
	toRadio( output_short ); // send data to RADIO
  }
}
