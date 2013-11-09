/*
*********************************************************************************************************
* Author : FQuinto
* File: main_TOT.c
* v. 1.00   | 2012-07-16 | First release
*********************************************************************************************************
*/
#include "bsp.h"
#include "mrfi.h"
#include "bsp_leds.h"
#include "bsp_buttons.h"
#include "nwk_types.h"
#include "nwk_api.h"
#include "nwk.h"
#include "virtual_com_cmds_TOT.h"

#ifndef APP_AUTO_ACK
#error ERROR: Must define the macro APP_AUTO_ACK for this application.
#endif

void toggleLED(uint8_t);

/* peer Link IDs */
static linkID_t sLinkID0 = 0;

/* callback handler */
static uint8_t sCB(linkID_t);

static void fromRadio( int byte );
void toRadio( char* data );
static void reset(void);
//static void cls(void);
static void linkFrom(void);
static void setAP(void);
static void linkTo(void);
static void setED(void);
int cmd_check( char* string );

/* work loop semaphores */
static volatile uint8_t sSelfMeasureSem = 0;
static volatile uint8_t sCommandSem = 0;
static volatile uint8_t temp_loop = 0;

/* mensajería */
//#define SIZE_COMANDO  15
//#define SIZE_MENSAJE  16
#define SIZE_COMANDO  6
#define SIZE_MENSAJE  8
signed int isAP = 5;
signed int j = 0;
//signed int byte_unoenviado = 0;
//signed int byte_unorecibido = 0;
static uint8_t dataFromUART[SIZE_MENSAJE];
static uint8_t dataFromRADIO[SIZE_MENSAJE];
static uint8_t headResponseData[1];
static uint8_t byte_enviouno[8];
//static uint8_t byte_enviodos[8];
static uint8_t comando[SIZE_COMANDO];
static void uart2radio( int byte );

/* device address */
addr_t linkToAddr; // = {0x12, 0x34, 0x56, 0x78}; // ED
addr_t linkListenAddr; // = {0xAA, 0xBB, 0xCC, 0xDD}; // AP
#define STATIC_PORT    0x3E

volatile int * tempOffset = (int *)0x10F4;

__interrupt void ADC10_ISR(void);
__interrupt void Timer_A (void);

#define SPIN_ABOUT_A_SECOND   NWK_DELAY(1000)

void main (void)
{
	//WDTCTL = WDTPW + WDTHOLD;       //stop watchdog timer
	
	// Switch interrupts
	// Configure Switch on P1.2
	//P1REN = BIT2;					// P1.2 Enable pullup / pulldown
	//P1OUT = BIT2;					// P1.2 pullup
	P1IE |= BIT2;					// P1.2 interrupt enabled
	P1IES |= BIT2;					// P1.2 hi/lo falling edge
	P1IFG &= ~BIT2;					// P1.2 IFG cleared just in case
	
	//_EINT(); // Enable interrupts
	
	BSP_Init();
	
	BCSCTL3 |= LFXT1S_2;	 // LFXT1 = VLO  (Set LFXT1 to the VLO @ 12kHz)
	TACCTL0 = CCIE;		 	 // TACCR0 interrupt enabled
	TACCR0 = 12000;			 // ~1 second
	TACTL = TASSEL_1 + MC_1; // ACLK, upmode  

	// Configurar el puerto COM
	COM_Init();
	
	// PxSEL: 0 = GPIO
	P2SEL = ~(0x1F); // set 2.0, 2.1, 2.2, 2.3 to GPIO mode
	P4SEL = ~(0x78); // set 4.3, 4.4, 4.5, 4.6 to GPIO mode
	
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
		
		int type;
		
		if (sCommandSem)
		{
			/*
			if ( cmd_check("help") )
			{
				if (headResponseData[0]==0x44 & isAP==1)
				{
					//serial_log( "AP->PC\r\n" ); // debug
					UART_write((char *)headResponseData, 1 );
					serial_log( "comandos: help aAP aED loop_on loop_off info led1_on led1_off led2_on led2_off reset setupAP setupED\r\n" );
				}
				if (headResponseData[0]==0x49 & isAP==0)
				{
					//serial_log( "ED->FG\r\n" ); // debug
					UART_write((char *)headResponseData, 1 );
					serial_log( "comandos: help aAP aED loop_on loop_off info led1_on led1_off led2_on led2_off reset setupAP setupED\r\n" );
				}
			}
			*/
			/*
			if ( cmd_check("info") )
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
			*/
			if ( cmd_check("W") )
			{
				int puerto;
				int bit;
				int data;
				
				// puerto
				if (comando[1]=='1')
				{
					puerto = 1;
				}
				if (comando[1]=='2')
				{
					puerto = 2;
				}
				if (comando[1]=='4')
				{
					puerto = 4;
				}
				if (comando[1]=='6')
				{
					puerto = 6;
					if ( cmd_check("W61") )
					{
						if ( (isAP == 5)  || (isAP == 3) )
						{
							/* set address AP */
							linkListenAddr.addr[0]=0;
							linkListenAddr.addr[1]=comando[3];
							linkListenAddr.addr[2]=comando[4];
							linkListenAddr.addr[3]=comando[5];
							
							/* set status */
							if (isAP == 5)
							{
								BSP_TURN_ON_LED2(); // LED rojo turn on
								isAP = 4; // address AP is set, address ED pending
							}
							if (isAP == 3)
							{
								BSP_TURN_ON_LED2(); // LED rojo turn on
								isAP = 2; // address ED & AP is set
							}
						}
					}
					else if ( cmd_check("W60") )
					{
						if ( (isAP == 5) || (isAP == 4) )
						{
							/* set address ED */
							linkToAddr.addr[0]=0;
							linkToAddr.addr[1]=comando[3];
							linkToAddr.addr[2]=comando[4];
							linkToAddr.addr[3]=comando[5];

							/* set status */
							if (isAP == 5)
							{
								BSP_TURN_ON_LED1(); // LED verde turn on
								isAP = 3; // address ED is set, address AP pending
							}
							if (isAP == 4)
							{
								BSP_TURN_ON_LED1(); // LED verde turn on
								isAP = 2; // address ED & AP is set
							}
						}
					}
					else if ( cmd_check("W62001") )
					{
						/* set AP */
						if (isAP == 2)
						{
							setAP();
							SMPL_Init(sCB);
							linkFrom();
							isAP = 1;
						}
					}
					else if ( cmd_check("W62000") )
					{
						/* set ED */
						if (isAP == 2)
						{
							setED();
							SMPL_Init(sCB);
							linkTo();
							isAP = 0;
						}
					}
				}
				
				// data
				if (comando[5]=='1')
				{
					data = 1;
				}
				if (comando[5]=='0')
				{
					data = 0;
				}
				
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
				
				// entradas y salidas
				if (puerto==1)
				{
					//st( if (data) { P1OUT &= ~BV(bit); } else { P1OUT |= BV(bit); } );
					st( if (data) { P1OUT &= ~(bit); } else { P1OUT |= (bit); } );
				}
				if (puerto==2)
				{
					if (comando[3]=='0')
					{
						// REN:   0 = no pull-up    1 = pull-up
						P2REN = ~(bit); // no pull-ups    (0xff = pull-up)              (0x00 = no pull-up, para LEDs)
					} else {
						P2REN = (bit);
					}
					
					if (comando[4]=='0')
					{
						// DIR:   0 = input    1 = output
						P2DIR |= bit; // P2.0 outputs     (0xff = P2.0-P2.7 output)     (0xc0 = P2.0-P2.5 input, P2.6-P2.7 output)
						//P2DIR = 0xFF; // All P2.x outputs
					} else {
						P2DIR &= ~bit;
					}
					
					//              Clear P2.x LED off          Set P2.x LED on            x = bit
					//st( if (data) { P2OUT &= ~BV(bit); } else { P2OUT |= BV(bit); } );
					st( if (data) { P2OUT &= ~(bit); } else { P2OUT |= (bit); } );
				}
				if (puerto==4)
				{
					if (comando[3]=='0')
					{
						// REN:   0 = no pull-uo    1 = pull-up
						P4REN = ~(bit); // P4.bit => 0 = no pull-ups
					} else {
						P4REN = (bit);
					}
					
					if (comando[4]=='0')
					{
						// DIR:   0 = input    1 = output
						P4DIR |= bit; // P4.bit => 1 = output
					} else {
						P4DIR &= ~bit;
					}
					
					//              Clear P4.x LED off          Set P4.x LED on            x = bit
					st( if (data) { P4OUT &= ~(bit); } else { P4OUT |= (bit); } );
				}
				
				if ( cmd_check("W00") )
				{
					reset();
				}
			}
			if ( cmd_check("R") )
			{
				if ( cmd_check("R50000") )
				{
					// Temperature
					type = 0;
					sSelfMeasureSem = 1;
				}
				else if ( cmd_check("R51000") )
				{
					// RSSI
					type = 1;
					sSelfMeasureSem = 1;
				}
				else if ( cmd_check("R52000") )
				{
					// Voltage
					type = 2;
					sSelfMeasureSem = 1;
				}
				/*
				else if ( cmd_check("R12") )
				{
					char chardata;
					// lectura boton
					if (P1IN &  ~BIT2) // P1.2 is Low?
					{
						chardata = '0';
					} else {
						chardata = '1';
					}
					if (isAP==1)
					{
						switch (headResponseData[0])
						{
							case 0x44: // mensaje D (4): AP->PC => emisor UART
								UART_write((char *)headResponseData, 1 );
								serial_log( "R1200" );
								UART_write((char *)chardata, 1 );
								serial_log( "\r" );
								break;
							case 0x46: // mensaje F (6): AP->FG => emisor RADIO
								toRadio( "FR1200x\r" );
								break;
						}
					}
					if (isAP==0)
					{
						switch (headResponseData[0])
						{
							case 0x49: // mensaje I (9): ED->FG => emisor UART
								UART_write((char *)headResponseData, 1 );
								serial_log( "R1200" );
								UART_write((char *)chardata, 1 );
								serial_log( "\r" );
								break;
							case 0x47: // mensaje G (7): ED->PC => emisor RADIO
								toRadio( "GR1200x\r" );
								break;
						}
					}
				}
				*/
			}
			/*
			else if ( cmd_check("led1_off") )
			{
				BSP_TURN_OFF_LED1(); //LED verde turn off
			}
			else if ( cmd_check("led2_on") )
			{
				BSP_TURN_ON_LED2(); // LED rojo turn on
			}
			else if ( cmd_check("led2_off") )
			{
				BSP_TURN_OFF_LED2(); //LED rojo turn off
			}
			*/
			/*
			else if ( cmd_check("cls") )
			{
				cls();
			}
			*/
			//else
			//{
				/*
				if (isAP==1)
				{
					switch (headResponseData[0])
					{
						case 0x44: // mensaje D (4): AP->PC => emisor UART
							//serial_log( "AP->PC\r\n" ); // debug
							UART_write((char *)headResponseData, 1 );
							serial_log( "command error\r\n" );
							break;
						case 0x46: // mensaje F (6): AP->FG => emisor RADIO
							//serial_log( "AP->FG\r\n" ); // debug
							toRadio( "Fcommand error\r" );
							break;
					}
				}
				if (isAP==0)
				{
					switch (headResponseData[0])
					{
						case 0x49: // mensaje I (9): ED->FG => emisor UART
							//serial_log( "ED->FG\r\n" ); // debug
							UART_write((char *)headResponseData, 1 );
							serial_log( "command error\r\n" );
							break;
						case 0x47: // mensaje G (7): ED->PC => emisor RADIO
							//serial_log( "ED->PC\r\n" ); // debug
							toRadio( "Gcommand error\r" );
							break;
					}
				}
				*/
			//}
			sCommandSem = 0;
		}

		if(sSelfMeasureSem)
		{
			char msg [3];
			int degC, volt;
			volatile long temp;
			int results[2];
			
			/* RSSI */
			ioctlRadioSiginfo_t sigInfo;
			sigInfo.lid = sLinkID0;
			SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SIGINFO, (void *)&sigInfo);
			
			/* Temperature */
			ADC10CTL1 = INCH_10 + ADC10DIV_4;     // Temp Sensor ADC10CLK/5
			ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE + ADC10SR;
			for( degC = 240; degC > 0; degC-- );  // delay to allow reference to settle
			ADC10CTL0 |= ENC + ADC10SC;           // Sampling and conversion start
			__bis_SR_register(CPUOFF + GIE);      // LPM0 with interrupts enabled
			results[0] = ADC10MEM;
			ADC10CTL0 &= ~ENC;
			
			/* Voltage */
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
			if (isAP==1)
			{
				switch (headResponseData[0])
				{
					case 0x44: // mensaje D (4): AP->PC => emisor UART
						//serial_log( "AP->PC\r\n" ); // debug
						transmitDataString( 1, sigInfo.sigInfo.rssi, msg, 1, type ); // 1 = AP, 1 = uart
						break;
					case 0x46: // mensaje F (6): AP->FG => emisor RADIO
						//serial_log( "AP->FG\r\n" ); // debug
						transmitDataString( 1, sigInfo.sigInfo.rssi, msg, 0, type ); // 1 = AP, 0 = radio
						break;
				}
			}
			if (isAP==0)
			{
				switch (headResponseData[0])
				{
					case 0x49: // mensaje I (9): ED->FG => emisor UART
						//serial_log( "ED->FG\r\n" ); // debug
						transmitDataString( 0, sigInfo.sigInfo.rssi, msg, 1, type ); // 0 = ED, 1 = uart
						break;
					case 0x47: // mensaje G (7): ED->PC => emisor RADIO
						//serial_log( "ED->PC\r\n" ); // debug
						transmitDataString( 0, sigInfo.sigInfo.rssi, msg, 0, type ); // 0 = ED, 0 = radio
						break;
				}
			}
			sSelfMeasureSem = 0;
		}
		/*
		if ( BSP_BUTTON1() )
		{
			if (isAP==1)
			{
				serial_log( "Dboton\r\n" );
				SPIN_ABOUT_A_SECOND;
			}
			if (isAP==0)
			{
				serial_log( "Iboton\r\n" );
				SPIN_ABOUT_A_SECOND;
			}
		}
		*/
	}
}

/*
 * reset: set to initial conditions
 */
static void reset()
{
	SMPL_Unlink(sLinkID0);
	sLinkID0 = 0;
	//sSelfMeasureSem = 0;
	temp_loop = 0;
	isAP = 5;
	
	WDTCTL = 0;
	/* clear screen */
	//cls();
}

/*
 * cls: clear screen
 */
/*
static void cls()
{
	serial_log( "\f" );
}
*/

/*
 * linkFrom: used by AP to link device address
 */
static void linkFrom()
{
	/* FOR AP */
	
	// bypass linking process
	if(SMPL_Commission((addr_t*) &linkToAddr, STATIC_PORT, STATIC_PORT, &sLinkID0) != SMPL_SUCCESS)
	{
		// trap
		while(1)
		{
			toggleLED(2); //LED rojo
		}
	}
	
	BSP_TURN_OFF_LED2(); //LED rojo OFF
	
	/* turn on RX. default is RX off. */
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0);
}

/*
 * linkTo: used by ED to link device address
 */
static void linkTo()
{
	/* FOR ED */

	// bypass linking process
	if(SMPL_Commission((addr_t*) &linkListenAddr, STATIC_PORT, STATIC_PORT, &sLinkID0) != SMPL_SUCCESS)
	{
		// trap
		while(1)
		{
			toggleLED(2); //LED rojo
		}
	}

	BSP_TURN_OFF_LED2(); //LED rojo OFF

	/* turn on RX. default is RX off. */
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0);
}

/*
 * setAP: set AP device address
 */
static void setAP()
{
	SMPL_Ioctl(IOCTL_OBJ_ADDR, IOCTL_ACT_SET, (addr_t*) &linkListenAddr);
}

/*
 * setED: set ED device address
 */
static void setED()
{
	SMPL_Ioctl(IOCTL_OBJ_ADDR, IOCTL_ACT_SET, (addr_t*) &linkToAddr);
}

/*
 * toggleLED: set LED on when off and set LED off when on
 */
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
		/*
		if (byte_unorecibido)
		{
			// recibir byte dos
			fromRadio(2);
		}
		else
		{
			// recibir byte uno
			fromRadio(1);
		}
		*/
		fromRadio(1);
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

/*
 * fromRadio: receive data from radio. Input 1 = byte uno, 2 = byte dos
 */
static void fromRadio( int byte )
{
	uint8_t     msg[8], len; // 8 = 1 byte
	uint8_t i;
	int headdata;
	
	len = sizeof(msg);
	
	if (SMPL_SUCCESS == SMPL_Receive(sLinkID0, msg, &len))
	{
		//byte_unorecibido = 1;
		if (byte==1)
		{
			for (i=0; i<=SIZE_COMANDO+1; ++i) // +1 por el 0x0d
			{
				if ((msg[i]==0x0d) & (i>1))
				{
					dataFromRADIO[i] = 0x0d; // guardo x0d
					//byte_unorecibido = 0;
					break;
				}
				else
				{
					dataFromRADIO[i] = msg[i];
				}
			}
		}
		/*
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
		*/
		
		/* fin del mensaje: porque he detectado un ENTER o porque ha llegado el segundo byte */
		//if (byte_unorecibido == 0)
		//{
		
		/* guardo comando */
		for (i=0; i<=(SIZE_COMANDO-1); ++i) // máximo = SIZE_COMANDO-1
		{
			comando[i] = dataFromRADIO[i+1]; // el comando no tiene cabecera, empiezo desde el 1
		}
		headdata = dataFromRADIO[0];
		if (isAP==1)
		{
			switch (headdata)
			{
				case 0x47: // mensaje G (7): ED->PC => transporte RADIO2UART
					//serial_log( "ED->PC\r\n" ); // debug
					UART_write( dataFromRADIO, SIZE_MENSAJE );
					serial_log( "\r" );
					break;
				case 0x4A: // mensaje J (10): FG->PC => transporte RADIO2UART
					//serial_log( "FG->PC\r\n" ); // debug
					UART_write( dataFromRADIO, SIZE_MENSAJE );
					serial_log( "\r" );
					break;
				case 0x4B: // mensaje K (11): FG->AP => receptor RADIO
					//serial_log( "FG->AP\r\n" ); // debug
					headResponseData[0] = 'F'; // mensaje F (6)
					sCommandSem = 1; /* semáforo comando */
					break;
				default: ;
			}
		}
		if (isAP==0)
		{
			switch (headdata)
			{
				case 0x42: // mensaje B (2): PC->ED => receptor RADIO
					//serial_log( "PC->ED\r\n" ); // debug
					headResponseData[0] = 'G'; // mensaje G (7)
					sCommandSem = 1; /* semáforo comando */
					break;
				case 0x43: // mensaje C (3): PC->FG => transporte RADIO2UART
					//serial_log( "PC->FG\r\n" ); // debug
					UART_write( dataFromRADIO, SIZE_MENSAJE );
					serial_log( "\r" );
					break;
				case 0x46: // mensaje F (6): AP->FG => transporte RADIO2UART
					//serial_log( "AP->FG\r\n" ); // debug
					UART_write( dataFromRADIO, SIZE_MENSAJE );
					serial_log( "\r" );
					break;
				default: ;
			}
		}
		//}
	}
}

/*
 * toRadio: send data to Radio
 */
void toRadio( char* data )
{
	uint8_t i;
	
	/* establecer byte_enviouno */
	for (i=0; i<=SIZE_COMANDO+1; ++i) // +1 por el 0x0d
	{
		byte_enviouno[i] = data[i];
	}
	
	/*
	To establish a packet-error rate the newest send command can be used (SMPL _SendOpt(linkID_t lid, uint8 *msg, uint8 len, uint8 opt) instead of SMPL _Send(linkID_t lid, uint8 *msg, uint8 len)) which uses the opt bitmap to add different features for the transmission, such as implementing an ACK (parameter SMPL_TXOPTION_ACKREQ). This will tell the program to request an acknowledgement from the peer and the return status of the SMPL_SendOpt can be checked to determine transmission success. If no acknowledgment is received then the program can perform error checking or implement a resend routine. For more information on these features see the SimpliciTI API guide, most notably page 13.
	http://processors.wiki.ti.com/index.php/EZ430_Chat
	*/
	
	/* envio mensaje */
	SMPL_Send(sLinkID0, byte_enviouno,  sizeof byte_enviouno );
	
	/* establecer byte_enviodos */
	/*
	for (i=8; i<=15; ++i)
	{
		byte_enviodos[i-8] = data[i];
	}
	*/
	/* envio mensaje */
	//SMPL_Send(sLinkID0, byte_enviodos,  sizeof byte_enviodos );
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
	
	/* Envia si mensaje ( B = 0x42  O  C = 0x43 ) Y isAP = 1
	 * o
	 * si mensaje ( J = 0x4A  O  K = 0x4B ) Y isAP = 0
	 */
	if ( (((headdata == 0x42) || (headdata == 0x43)) & isAP==1) || (((headdata == 0x4A) || (headdata == 0x4B)) & isAP==0) )
	{
		if (byte==1)
		{
			/* establecer byte_enviouno */
			for (i=0; i<=SIZE_COMANDO+1; ++i) // +1 por el 0x0d
			{
				byte_enviouno[i] = dataFromUART[i];
			}
			
			/* envio mensaje */
			SMPL_Send(sLinkID0, byte_enviouno,  sizeof byte_enviouno );
		}
		/*
		if (byte==2)
		{
			// establecer byte_enviodos
			for (i=8; i<=15; ++i)
			{
				byte_enviodos[i-8] = dataFromUART[i];
			}
			
			// envio mensaje
			SMPL_Send(sLinkID0, byte_enviodos,  sizeof byte_enviodos );
		}
		*/
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
		/* 0x41 = A, 0x42 = B, 0x43 = C (from PC) */
		if ( ((data == 0x41) || (data == 0x42) || (data == 0x43)) )
		{
			j++;
		}
		/* 0x4A = J, 0x4B = K, 0x4C = L (from FPGA) */
		if ( ((data == 0x4A) || (data == 0x4B) || (data == 0x4C)) )
		{
			j++;
		}
		dataFromUART[0] = data; // guardo cabecera
		//byte_unoenviado = 0;
	}
	else
	{
		/* para j>0 */
		if( (data==0x0d) & (j>1) ) // minimo 1 byte de mensaje por eso j>1
		{
			/* guardo comando */
			// j es el valor actual, luego -1 para quitar cabecera y -1 para quitar el x0d = -2
			for (i=0; i<=(j-2); ++i)
			{
				comando[i] = dataFromUART[i+1]; // el comando no tiene cabecera, empiezo desde el 1
			}
			for (i; i<=(SIZE_COMANDO-1); ++i) // máximo = SIZE_COMANDO-1
			{
				comando[i] = 0x20; // rellena el comando con espacios = 0x20
			}
			
			/* semáforo comando si mensaje es A (1)*/
			if ( (dataFromUART[0] == 0x41) & isAP==1 )
			{
				headResponseData[0] = 'D'; // mensaje D (4)
				sCommandSem = 1;
			}
			/* semáforo comando si mensaje es L (12)*/
			if ( (dataFromUART[0] == 0x4C) & isAP==0 )
			{
				headResponseData[0] = 'I'; // mensaje 9
				sCommandSem = 1;
			}
			/* Para los estados 5, 4, 3, 2 procesa lo recibido (configuración) */
			if ( (isAP != 0) && (isAP != 1) )
			{
				sCommandSem = 1;
			}
			
			/* establecer final mensaje, agrega x0d */
			dataFromUART[j] = 0x0d;
			
			/* OPCIONAL: continuo agregando datos a comando */
			/*
			j++;
			for (i=j; i<=SIZE_MENSAJE; ++i)
			{
				dataFromUART[i] = 0x20; // rellena el comando con espacios = 0x20
			}
			*/
			
			/*
			if (byte_unoenviado)
			{
				// hacer envio byte dos
				uart2radio(2);
			}
			else
			{
				// hacer envio byte uno
				uart2radio(1);
			}
			*/
			// hacer envio byte uno
			uart2radio(1);
			
			j = 0;
		} else {
			/*
			if (j==SIZE_COMANDO)
			{
				dataFromUART[j] = data;
				if (byte_unoenviado == 0)
				{
					// hacer envio byte uno
					uart2radio(1);
					
					byte_unoenviado = 1;
					j++;
				}
			}
			else if (j>=15)
			{
				dataFromUART[j] = data;
				
				// hacer envio byte dos
				uart2radio(2);
				
				j = 0;
			}
			*/
			if (j>=SIZE_COMANDO+1) // +1 por el 0x0d
			{
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
	/*
	if (temp_loop)
	{
		sSelfMeasureSem = 1;
	}
	*/
}

/*------------------------------------------------------------------------------
* Port1 interrupt service routine (switch)
------------------------------------------------------------------------------*/
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	volatile unsigned int i;
	
	if (isAP==1)
	{
		serial_log( "DR12001\r\n" );
		SPIN_ABOUT_A_SECOND;
	}
	if (isAP==0)
	{
		serial_log( "IR12001\r\n" );
		SPIN_ABOUT_A_SECOND;
	}
	
	//P1OUT ^= BIT1;            // Toggle Port P1.1 using exclusive-OR
	/*
	i=1500;                   // Delay, button debounce 
	do (i--);
	while (i !=0);
	while (! (P1IN & BIT2)); // Wait for the release of the button
	i=1500;                 // Delay, button debounce 
	do (i--);
	while (i !=0);
	*/
	P1IFG &= ~BIT2;     // P1.2 Interrupt Flag cleared
}
