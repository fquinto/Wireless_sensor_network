/*
*********************************************************************************************************
* Author : FQuinto
* File: main_AP.c
* v. 1.00   | 2012-06-24 | First release
*********************************************************************************************************
*/
#include <string.h>
#include "bsp.h"
#include "mrfi.h"
#include "bsp_leds.h"
#include "bsp_buttons.h"
#include "nwk_types.h"
#include "nwk_api.h"
//#include "nwk_frame.h"
#include "nwk.h"
#include "virtual_com_cmds.h"

#ifndef APP_AUTO_ACK
#error ERROR: Must define the macro APP_AUTO_ACK for this application.
#endif

void toggleLED(uint8_t);

/* peer Link IDs */
static linkID_t sLinkID2 = 0;

/* callback handler */
static uint8_t sCB(linkID_t);

static void fromRadio( int byte );
void toRadio( char* data );
static void reset(void);
static void linkFrom(void);
static void setAP(void);
int cmd_check( char* string );

/* work loop semaphores */
static volatile uint8_t sSelfMeasureSem = 0;
static volatile uint8_t sCommandSem = 0;
static volatile uint8_t temp_loop = 0;

/* mensajería */
#define SIZE_COMANDO  15
#define SIZE_MENSAJE  16
signed int j = 0;
signed int byte_unoenviado = 0;
signed int byte_unorecibido = 0;
static uint8_t dataFromUART[SIZE_MENSAJE];
static uint8_t dataFromRADIO[SIZE_MENSAJE];
static uint8_t headResponseData[1];
static uint8_t byte_enviouno[8];
static uint8_t byte_enviodos[8];
static uint8_t comando[SIZE_COMANDO];
static void uart2radio( int byte );

/* device address */
const addr_t linkToAddr = {0x12, 0x34, 0x56, 0x78};
const addr_t linkListenAddr = {0xAA, 0xBB, 0xCC, 0xDD};
#define STATIC_PORT    0x3E

#ifdef FREQUENCY_AGILITY
/*     ************** BEGIN interference detection support */

#define INTERFERNCE_THRESHOLD_DBM (-70)
#define SSIZE    25
#define IN_A_ROW  3
//static int8_t  sSample[SSIZE];
#endif  /* FREQUENCY_AGILITY */

//data for terminal output
//const char splash[] = {"\r\n-----eZ430-RF2500\r\n"};
volatile int * tempOffset = (int *)0x10F4;

__interrupt void ADC10_ISR(void);
__interrupt void Timer_A (void);

/*     ************** END interference detection support                       */

#define SPIN_ABOUT_A_QUARTER_SECOND   NWK_DELAY(250)

void main (void)
{
	//memset(sSample, 0x0, sizeof(sSample));

	BSP_Init();

	BCSCTL3 |= LFXT1S_2;	 // LFXT1 = VLO
	TACCTL0 = CCIE;		 	 // TACCR0 interrupt enabled
	TACCR0 = 12000;			 // ~1 second
	TACTL = TASSEL_1 + MC_1; // ACLK, upmode  

	// Configurar el puerto COM
	COM_Init();
	
	setAP();

	SMPL_Init(sCB);
	/* The key purpose of providing the call back function pointer in the call to SMPL_Init
	 * is to allow the user application code access to ISR context management of packets being
	 * received on user ports.  Every time a packet is received which is associated with a link ID,
	 * it is passed to this call back function (sCB) in the ISR context. Depending on what the call back
	 * function does, the packet may be either discarded there or stored in the incoming queue
	 * for the associated link ID.
	 */
	
	linkFrom();

	while (1)
	{
		/* Wait for the Join semaphore to be set by the receipt of a Join frame from a
		 * device that supports an End Device.
		 *
		 * An external method could be used as well. A button press could be connected
		 * to an ISR and the ISR could set a semaphore that is checked by a function
		 * call here, or a command shell running in support of a serial connection
		 * could set a semaphore that is checked by a function call.
		 */
		
		if (sCommandSem)
		{
			if ( cmd_check("help") )
			{
				switch (headResponseData[0])
				{
					case 0x44: // mensaje D (4): AP->PC => emisor UART
						serial_log( "AP->PC\r\n" ); // debug
						UART_write((char *)headResponseData, 1 );
						serial_log( "comandos: help loop_on loop_off info led1_on led1_off led2_on led2_off reset init setAP linkFrom\r\n" );
						break;
				}
			}
			else if ( cmd_check("info") )
			{
				sSelfMeasureSem = 1;
			}
			else if ( cmd_check("loop_on") )
			{
				temp_loop = 1;
			}
			else if ( cmd_check("loop_off") )
			{
				temp_loop = 0;
			}
			else if ( cmd_check("led1_on") )
			{
				if (!BSP_LED1_IS_ON())
				{
					toggleLED(1); //LED verde
				}
			}
			else if ( cmd_check("led1_off") )
			{
				BSP_TURN_OFF_LED1(); //LED verde
			}
			else if ( cmd_check("led2_on") )
			{
				if (!BSP_LED2_IS_ON())
				{
					toggleLED(2); //LED rojo
				}
			}
			else if ( cmd_check("led2_off") )
			{
				BSP_TURN_OFF_LED2(); //LED rojo
			}
			else if ( cmd_check("init") )
			{
				SMPL_Init(sCB);
			}
			else if ( cmd_check("setAP") )
			{
				setAP();
			}
			else if ( cmd_check("linkFrom") )
			{
				linkFrom();
			}
			else if ( cmd_check("reset") )
			{
				reset();
			}
			else
			{
				switch (headResponseData[0])
				{
					case 0x44: // mensaje D (4): AP->PC => emisor UART
						serial_log( "AP->PC\r\n" ); // debug
						UART_write((char *)headResponseData, 1 );
						serial_log( "command error\r\n" );
						break;
					case 0x46: // mensaje F (6): AP->FG => emisor RADIO
						serial_log( "AP->FG\r\n" ); // debug
						toRadio( "Fcommand error\r" );
						break;
				}
			}
			sCommandSem = 0;
		}

		if(sSelfMeasureSem)
		{
			char msg [3];
			char addr[] = {"AP"};
			int degC, volt;
			volatile long temp;
			int results[2];
			
			ioctlRadioSiginfo_t sigInfo;
			sigInfo.lid = sLinkID2;
			SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SIGINFO, (void *)&sigInfo);

			ADC10CTL1 = INCH_10 + ADC10DIV_4;     // Temp Sensor ADC10CLK/5
			ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE + ADC10SR;
			for( degC = 240; degC > 0; degC-- );  // delay to allow reference to settle
			ADC10CTL0 |= ENC + ADC10SC;           // Sampling and conversion start
			__bis_SR_register(CPUOFF + GIE);      // LPM0 with interrupts enabled
			results[0] = ADC10MEM;

			ADC10CTL0 &= ~ENC;

			ADC10CTL1 = INCH_11;                  // AVcc/2
			ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE + REF2_5V;
			for( degC = 240; degC > 0; degC-- );  // delay to allow reference to settle
			ADC10CTL0 |= ENC + ADC10SC;           // Sampling and conversion start
			__bis_SR_register(CPUOFF + GIE);      // LPM0 with interrupts enabled
			results[1] = ADC10MEM;
			ADC10CTL0 &= ~ENC;
			ADC10CTL0 &= ~(REFON + ADC10ON);      // turn off A/D to save power

			// oC = ((A10/1024)*1500mV)-986mV)*1/3.55mV = A10*423/1024 - 278
			// the temperature is transmitted as an integer where 32.1 = 321
			// hence 4230 instead of 423
			temp = results[0];
			degC = (((temp - 673) * 4230) / 1024);
			if( (*tempOffset) != 0xFFFF )
			{
				degC += (*tempOffset); 
			}
			/* message format,  UB = upper Byte, LB = lower Byte
			-------------------------------
			|degC LB | degC UB |  volt LB |
			-------------------------------
			 0         1          2
			*/
			temp = results[1];
			volt = (temp*25)/512;
			msg[0] = degC&0xFF;
			msg[1] = (degC>>8)&0xFF;
			msg[2] = volt;
			
			switch (headResponseData[0])
			{
				case 0x44: // mensaje D (4): AP->PC => emisor UART
					serial_log( "AP->PC\r\n" ); // debug
					transmitDataString( addr, sigInfo.sigInfo.rssi, msg, 1 ); // uart = 1
					break;
				case 0x46: // mensaje F (6): AP->FG => emisor RADIO
					serial_log( "AP->FG\r\n" ); // debug
					transmitDataString( addr, sigInfo.sigInfo.rssi, msg, 0 ); // uart = 0 = radio
					break;
			}
			sSelfMeasureSem = 0;
		}
	}
}

static void reset()
{
	if (SMPL_SUCCESS == SMPL_Unlink(sLinkID2))
	{
		/* debug */
		//serial_log( "Dunlink\r\n" );
	}
	sLinkID2 = 0;
	sSelfMeasureSem = 0;
	temp_loop = 0;
	
	/* off leds */
	if (BSP_LED1_IS_ON())
	{
		toggleLED(1); //LED verde
	}
	if (BSP_LED2_IS_ON())
	{
		toggleLED(2); //LED rojo
	}
}

static void linkFrom()
{
	/* turn on LEDs. */
	if (!BSP_LED2_IS_ON())
	{
		toggleLED(2); //LED rojo
	}
	if (!BSP_LED1_IS_ON())
	{
		toggleLED(1); //LED verde
	}
	
	/* Turn off one LED so we can tell the device is now listening.
	 */
	toggleLED(1); //LED verde

	// bypass linking process
	if(SMPL_Commission((addr_t*) &linkToAddr, STATIC_PORT, STATIC_PORT, &sLinkID2) != SMPL_SUCCESS)
	{
		// trap
		while(1);
	}
	
	/* wait for a button press... */
	/*
	do {
		if (BSP_BUTTON1() || BSP_BUTTON2())
		{
			break;
		}
	} while (1);
	*/
	
	/* turn on RX. default is RX off. */
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0);
	
	/* turn both LEDs off */
	BSP_TURN_OFF_LED1();
	BSP_TURN_OFF_LED2();
}

static void setAP()
{
	// set device address
	SMPL_Ioctl(IOCTL_OBJ_ADDR, IOCTL_ACT_SET, (addr_t*) &linkListenAddr);
}

void toggleLED(uint8_t which)
{
	if (1 == which)
	{
		BSP_TOGGLE_LED1(); //LED verde
	}
	else if (2 == which)
	{
		BSP_TOGGLE_LED2(); //LED rojo
	}

	return;
}

/* Runs in ISR context. Reading the frame should be done in the */
/* application thread not in the ISR thread. */
static uint8_t sCB(linkID_t lid)
{
	if (lid)
	{
		if (byte_unorecibido)
		{
			/* recibir byte dos */
			fromRadio(2);
		}
		else
		{
			/* recibir byte uno */
			fromRadio(1);
		}
	}
	
	/* 
	 * If the function returns 0 the received frame is left in the input frame queue for later
	 * retrieval in the user thread. This is the recommended procedure. The callback can simply
	 * set a flag or otherwise store the information about the waiting frame. The actual
	 * reference to SMPL_Receive() should be done in the user thread.
	 */
	/* leave frame to be read by application. */
	return 0;
}

static void fromRadio( int byte )
{
	uint8_t     msg[8], len; // 8 = 1 byte
	uint8_t i;
	int headdata;
	
	len = sizeof(msg);
	
	if (SMPL_SUCCESS == SMPL_Receive(sLinkID2, msg, &len))
	{
		byte_unorecibido = 1;
		if (byte==1)
		{
			for (i=0; i<=7; ++i)
			{
				if ((msg[i]==0x0d) & (i>1))
				{
					dataFromRADIO[i] = msg[i]; // guardo x0d
					byte_unorecibido = 0;
					break;
				}
				else
				{
					dataFromRADIO[i] = msg[i];
				}
			}
		}
		if (byte==2)
		{
			for (i=8; i<=15; ++i)
			{
				if (msg[i]==0x0d)
				{
					break;
				}
				else
				{
					dataFromRADIO[i] = msg[i-8];
				}
			}
			byte_unorecibido = 0;
		}
		
		/* fin del mensaje: porque he detectado un ENTER o porque ha llegado el segundo byte */
		if (byte_unorecibido == 0)
		{
			/* guardo comando */
			for (i=0; i<=SIZE_COMANDO; ++i)
			{
				comando[i] = dataFromRADIO[i+1];
			}
			headdata = dataFromRADIO[0];
			switch (headdata)
			{
				case 0x47: // mensaje G (7): ED->PC => transporte RADIO2UART
					serial_log( "ED->PC\r\n" ); // debug
					UART_write( dataFromRADIO, 16 );
					serial_log( "\r\n" );
					break;
				/*
				case 0x48: // mensaje H (8): ED->AP => receptor RADIO
					serial_log( "ED->AP\r\n" ); // debug
					//UART_write( dataFromRADIO, 16 );
					headResponseData[0] = 'E'; // mensaje E (5)
					sCommandSem = 1; // semáforo comando
					break;
				*/
				case 0x4A: // mensaje J (10): FG->PC => transporte RADIO2UART
					serial_log( "FG->PC\r\n" ); // debug
					UART_write( dataFromRADIO, 16 );
					serial_log( "\r\n" );
					break;
				case 0x4B: // mensaje K (11): FG->AP => receptor RADIO
					serial_log( "FG->AP\r\n" ); // debug
					headResponseData[0] = 'F'; // mensaje F (6)
					sCommandSem = 1; /* semáforo comando */
					break;
				default: ;
			}
		}
	}
}

/*
 * toRadio: send data to Radio
 */
void toRadio( char* data )
{
	uint8_t i;
	
	/* establecer byte_enviouno */
	for (i=0; i<=7; ++i)
	{
		byte_enviouno[i] = data[i];
	}
	
	/* envio mensaje */
	SMPL_Send(sLinkID2, byte_enviouno,  sizeof byte_enviouno );
	
	/* establecer byte_enviodos */
	for (i=8; i<=15; ++i)
	{
		byte_enviodos[i-8] = data[i];
	}
	
	/* envio mensaje */
	SMPL_Send(sLinkID2, byte_enviodos,  sizeof byte_enviodos );
}

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
 * uart2radio: envia byte 1 ó 2
 */
static void uart2radio( int byte )
{
	uint8_t i;
	int headdata = dataFromUART[0];
	/* sólo envia si es un mensaje B (2) ó C (3) */
	if ( (headdata == 0x42) || (headdata == 0x43) )
	{
		if (byte==1)
		{
			/* establecer byte_enviouno */
			for (i=0; i<=7; ++i)
			{
				byte_enviouno[i] = dataFromUART[i];
			}
			
			/* envio mensaje */
			SMPL_Send(sLinkID2, byte_enviouno,  sizeof byte_enviouno );
		}
		if (byte==2)
		{
			/* establecer byte_enviodos */
			for (i=8; i<=15; ++i)
			{
				byte_enviodos[i-8] = dataFromUART[i];
			}
			
			/* envio mensaje */
			SMPL_Send(sLinkID2, byte_enviodos,  sizeof byte_enviodos );
		}
	}
}

/*------------------------------------------------------------------------------
* USCIA interrupt service routine
------------------------------------------------------------------------------*/
/*
 * Accept a command entered on the serial terminal
 */
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	uint8_t data = UCA0RXBUF;
	uint8_t i;
	
	if (j==0)
	{
		switch (data)
		{
			case 0x41: // mensaje 1: PC->AP => receptor
				serial_log( "PC->AP\r\n" ); // debug
				j++;
				break;
			case 0x42: // mensaje 2: PC->ED => transporte UART2RADIO
				serial_log( "PC->ED\r\n" ); // debug
				j++;
				break;
			case 0x43: // mensaje 3: PC->FG => transporte UART2RADIO
				serial_log( "PC->FG\r\n" ); // debug
				j++;
				break;
			default: ;
		}
		/*
		// ALTERNATIVA
		if ( (data == 0x41) || (data == 0x42) || (data == 0x43) )
		{
			j++;
		}
		*/
		dataFromUART[0] = data; // guardo cabecera
		byte_unoenviado = 0;
	}
	else
	{
		/* para j>0 */
		if( (data==0x0d) & (j>1) ) // minimo 1 byte de mensaje por eso j>1
		{
			/* establecer comando */
			for (i=0; i<=j; ++i)
			{
				comando[i] = dataFromUART[i+1]; // el comando no tiene cabecera, empiezo desde el 1
			}
			i = i - 2; // -2 porque no me interesa en el comando la cabecera
			for (i; i<=SIZE_COMANDO; ++i) // continuo agregando datos a comando
			{
				comando[i] = 0x20; // rellena el comando con espacios = 0x20
			}
			
			/* semáforo comando si mensaje es A (1)*/
			if ( dataFromUART[0] == 0x41 )
			{
				headResponseData[0] = 'D'; // mensaje D (4)
				sCommandSem = 1;
			}
			
			/* establecer final mensaje, agrega x0d */
			dataFromUART[j] = data;
			
			/* OPCIONAL: continuo agregando datos a comando */
			j++;
			for (i=j; i<=SIZE_MENSAJE; ++i)
			{
				dataFromUART[i] = 0x20; // rellena el comando con espacios = 0x20
			}
			
			if (byte_unoenviado)
			{
				/* hacer envio byte dos */
				uart2radio(2);
			}
			else
			{
				/* hacer envio byte uno */
				uart2radio(1);
			}
			j = 0;
		} else {
			if (j==7)
			{
				dataFromUART[j] = data;
				if (byte_unoenviado == 0)
				{
					/* hacer envio byte uno */
					uart2radio(1);
					
					byte_unoenviado = 1;
					j++;
				}
			}
			else if (j>=15)
			{
				dataFromUART[j] = data;
				
				/* hacer envio byte dos */
				uart2radio(2);
				
				j = 0;
			}
			else
			{
				dataFromUART[j] = data;
				j++;
			}
		}
	}
}

/*------------------------------------------------------------------------------
* ADC10 interrupt service routine
------------------------------------------------------------------------------*/
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

/*------------------------------------------------------------------------------
* Timer A0 interrupt service routine
------------------------------------------------------------------------------*/
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	if (temp_loop)
	{
		sSelfMeasureSem = 1;
	}
}
