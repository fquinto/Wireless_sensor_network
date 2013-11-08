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
#include "nwk_frame.h"
#include "nwk.h"
#include "virtual_com_cmds.h"

#ifndef APP_AUTO_ACK
#error ERROR: Must define the macro APP_AUTO_ACK for this application.
#endif

void toggleLED(uint8_t);

/* reserve space for the maximum possible peer Link IDs */
static linkID_t sLID[NUM_CONNECTIONS] = {0};
static uint8_t  sNumCurrentPeers = 0;

/* callback handler */
static uint8_t sCB(linkID_t);

/* received message handler */
static void processMessage(linkID_t, uint8_t *, uint8_t);

/* Frequency Agility helper functions */
static void checkChangeChannel(void);
static void changeChannel(void);

static void fromRadio( int byte );
static void reset(void);
static void linkFrom(void);
static void setAP(void);
int cmd_check( char* string );

/* work loop semaphores */
static volatile uint8_t sPeerFrameSem = 0;
static volatile uint8_t sJoinSem = 0;
static volatile uint8_t sSelfMeasureSem = 0;
static volatile uint8_t sCommandSem = 0;
static volatile uint8_t temp_loop = 0;
static volatile uint8_t enableCommission = 1;

/* mensajería */
#define SIZE_COMANDO  15
#define SIZE_MENSAJE  16
signed int j = 0;
signed int byte_unoenviado = 0;
signed int byte_unorecibido = 0;
static uint8_t dataFromUART[SIZE_MENSAJE];
static uint8_t dataFromRADIO[SIZE_MENSAJE];
static uint8_t byte_enviouno[8];
static uint8_t byte_enviodos[8];
static uint8_t comando[SIZE_COMANDO];
static void toRadio( int byte );

/* device address */
const addr_t linkToAddr = {0x12, 0x34, 0x56, 0x78};
const addr_t linkListenAddr = {0xAA, 0xBB, 0xCC, 0xDD};
#define STATIC_PORT    0x3E

#ifdef FREQUENCY_AGILITY
/*     ************** BEGIN interference detection support */

#define INTERFERNCE_THRESHOLD_DBM (-70)
#define SSIZE    25
#define IN_A_ROW  3
static int8_t  sSample[SSIZE];
static uint8_t sChannel = 0;
#endif  /* FREQUENCY_AGILITY */

/* blink LEDs when channel changes... */
static volatile uint8_t sBlinky = 0;

//data for terminal output
//const char splash[] = {"\r\n-----eZ430-RF2500\r\n"};
volatile int * tempOffset = (int *)0x10F4;

__interrupt void ADC10_ISR(void);
__interrupt void Timer_A (void);

/*     ************** END interference detection support                       */

#define SPIN_ABOUT_A_QUARTER_SECOND   NWK_DELAY(250)

void main (void)
{
	bspIState_t intState;

	memset(sSample, 0x0, sizeof(sSample));

	BSP_Init();

	BCSCTL3 |= LFXT1S_2;	 // LFXT1 = VLO
	TACCTL0 = CCIE;		 	 // TACCR0 interrupt enabled
	TACCR0 = 12000;			 // ~1 second
	TACTL = TASSEL_1 + MC_1; // ACLK, upmode  

	// Configurar el puerto COM
	COM_Init();
	//Transmit splash screen and network init notification
	//serial_log( (char*)splash);
	serial_log( "Dinicio\r\n" ); // mensaje 4: AP->PC => emisor
	
	if (enableCommission)
	{
		setAP();
	}

	SMPL_Init(sCB);
	/* The key purpose of providing the call back function pointer in the call to SMPL_Init
	 * is to allow the user application code access to ISR context management of packets being
	 * received on user ports.  Every time a packet is received which is associated with a link ID,
	 * it is passed to this call back function (sCB) in the ISR context. Depending on what the call back
	 * function does, the packet may be either discarded there or stored in the incoming queue
	 * for the associated link ID.
	 */
	
	if (enableCommission)
	{
		linkFrom();
	}

	/* main work loop */
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
		if (sJoinSem && (sNumCurrentPeers < NUM_CONNECTIONS) && (enableCommission == 0))
		{
			/* listen for a new connection */
			serial_log( "Dconectando...\r\n" ); // mensaje 4: AP->PC => emisor
			while (1)
			{
				if (SMPL_SUCCESS == SMPL_LinkListen(&sLID[sNumCurrentPeers]))
				{
					break;
				}
				/* Implement fail-to-link policy here. otherwise, listen again. */
			}
			serial_log( "Dconectado!\r\n" ); // mensaje 4: AP->PC => emisor
			sNumCurrentPeers++;

			BSP_ENTER_CRITICAL_SECTION(intState);
			sJoinSem--;
			BSP_EXIT_CRITICAL_SECTION(intState);
		}

		if (sCommandSem)
		{
			
			if ( cmd_check("help") )
			{
				serial_log( "Dcomandos: help info_loop_on info_loop_off info led1_on led1_off led2_on led2_off reset init setAP linkFrom commission_on commission_off\r\n" ); // mensaje 4: AP->PC => emisor
			}
			else if ( cmd_check("info") )
			{
				sSelfMeasureSem = 1;
			}
			else if ( cmd_check("info_loop_on") )
			{
				temp_loop = 1;
			}
			else if ( cmd_check("info_loop_off") )
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
			else if ( cmd_check("commission_on") )
			{
				enableCommission = 1;
			}
			else if ( cmd_check("commission_off") )
			{
				enableCommission = 0;
			}
			else
			{
				serial_log( "Dcommand error\r\n" ); // mensaje 4: AP->PC => emisor
			}
			sCommandSem = 0;
		}

		// if it is time to measure our own temperature...
		if(sSelfMeasureSem)
		{
		  char msg [6];
		  char addr[] = {"HUB0"};
		  char rssi[] = {"000"};
		  int degC, volt;
		  volatile long temp;
		  int results[2];
		  
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
		  
		  temp = results[1];
		  volt = (temp*25)/512;
		  msg[0] = degC&0xFF;
		  msg[1] = (degC>>8)&0xFF;
		  msg[2] = volt;
		  transmitDataString( addr, rssi, msg );
		  toggleLED(1); //LED verde
		  sSelfMeasureSem = 0;
		}
    
		/* Have we received a frame on one of the ED connections?
		 * No critical section -- it doesn't really matter much if we miss a poll
		 */
		if (sPeerFrameSem  && (enableCommission == 0))
		{
		  uint8_t     msg[MAX_APP_PAYLOAD], len, i; // MAX_APP_PAYLOAD = 10

		  /* process all frames waiting */
		  for (i=0; i<sNumCurrentPeers; ++i)
		  {
			if (SMPL_SUCCESS == SMPL_Receive(sLID[i], msg, &len))
			{
			  ioctlRadioSiginfo_t sigInfo; 
			  
			  processMessage(sLID[i], msg, len);

			  sigInfo.lid = sLID[i];
			  
			  SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SIGINFO, (void *)&sigInfo);
			  
			  transmitData( i, sigInfo.sigInfo.rssi, (char*)msg );
			  toggleLED(2); //LED rojo
			  
			  BSP_ENTER_CRITICAL_SECTION(intState);
			  sPeerFrameSem--;
			  BSP_EXIT_CRITICAL_SECTION(intState);
			}
		  }
		}
		
		if (enableCommission == 0)
		{
			if (BSP_BUTTON1())
			{
			  SPIN_ABOUT_A_QUARTER_SECOND;  /* debounce */
			  changeChannel();
			  serial_log( "DchangeChannel\r\n" ); // mensaje 4: AP->PC => emisor
			}
			else
			{
			  checkChangeChannel();
			}
		}
		
		BSP_ENTER_CRITICAL_SECTION(intState);
		if (sBlinky)
		{
		  if (++sBlinky >= 0xF)
		  {
			sBlinky = 1;
			toggleLED(1); //LED verde
			toggleLED(2); //LED rojo
		  }
		}
		BSP_EXIT_CRITICAL_SECTION(intState);
	}
}

static void reset()
{
	/* esta parte solo tiene en cuenta 1 ED en el sistema */
	if (SMPL_SUCCESS == SMPL_Unlink(sLID[0]))
	{
		/* debug */
		//serial_log( "Dunlink\r\n" );
	}
	sJoinSem = 0; // para SMPL_LinkListen
	sNumCurrentPeers = 0;
	sPeerFrameSem = 0;
	sBlinky = 0;
	sChannel = 0;
	sLID[0] = 0;
	sLID[1] = 0;
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
	 * Received messages will toggle the other LED.
	 */
	toggleLED(1); //LED verde

	// bypass linking process
	if(SMPL_Commission((addr_t*) &linkToAddr, STATIC_PORT, STATIC_PORT, &sLID[0]) != SMPL_SUCCESS)
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
	serial_log( "DsetAP()\r\n" ); // debug
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
	if (lid && enableCommission)
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
	else
	{
		if (lid)
		{
			sPeerFrameSem++;
			sBlinky = 0;
		}
		else
		{
			sJoinSem++;
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
	
	if (SMPL_SUCCESS == SMPL_Receive(sLID[0], msg, &len))
	{
		serial_log( "Drecibido!\r\n" ); // debug
		byte_unorecibido = 1;
		if (byte==1)
		{
			for (i=0; i<=7; ++i)
			{
				if ((msg[i]==0x0d) & (i>1))
				{
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
		
		headdata = dataFromRADIO[0];
		switch (headdata)
		{
			case 0x47: // mensaje 7: ED->PC => transporte RADIO2UART
				serial_log( "ED->PC\r\n" ); // debug
				break;
			case 0x48: // mensaje 8: ED->AP => receptor RADIO
				serial_log( "ED->AP\r\n" ); // debug
				break;
			case 0x4A: // mensaje 10: FG->PC => transporte RADIO2UART
				serial_log( "FG->PC\r\n" ); // debug
				break;
			case 0x4B: // mensaje 11: FG->AP => receptor RADIO
				serial_log( "FG->AP\r\n" ); // debug
				break;
			default: ;
		}
		
		/*
		ioctlRadioSiginfo_t sigInfo; 
			  
		processMessage(sLID[0], msg, len);

		sigInfo.lid = sLID[0];

		SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SIGINFO, (void *)&sigInfo);

		transmitData( 0, sigInfo.sigInfo.rssi, (char*)msg );
		toggleLED(2); //LED rojo
		*/
		//toggleLED(*msg);
		//serial_log((char*)msg );
		serial_log((char*)dataFromRADIO );
		serial_log( "\r\n" );
	}
}

static void processMessage(linkID_t lid, uint8_t *msg, uint8_t len)
{
	/* do something useful */
	if (len)
	{
		toggleLED(*msg);
	}
	return;
}

static void changeChannel(void)
{
#ifdef FREQUENCY_AGILITY
  freqEntry_t freq;

  if (++sChannel >= NWK_FREQ_TBL_SIZE)
  {
    sChannel = 0;
  }
  freq.logicalChan = sChannel;
  SMPL_Ioctl(IOCTL_OBJ_FREQ, IOCTL_ACT_SET, &freq);
  BSP_TURN_OFF_LED1(); //LED verde
  BSP_TURN_OFF_LED2(); //LED rojo
  sBlinky = 1;
#endif
  return;
}

/* implement auto-channel-change policy here... */
static void  checkChangeChannel(void)
{
#ifdef FREQUENCY_AGILITY
  int8_t dbm, inARow = 0;

  uint8_t i;

  memset(sSample, 0x0, SSIZE);
  for (i=0; i<SSIZE; ++i)
  {
    /* quit if we need to service an app frame */
    if (sPeerFrameSem || sJoinSem)
    {
      return;
    }
    NWK_DELAY(1);
    SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RSSI, (void *)&dbm);
    sSample[i] = dbm;

    if (dbm > INTERFERNCE_THRESHOLD_DBM)
    {
      if (++inARow == IN_A_ROW)
      {
        changeChannel();
        break;
      }
    }
    else
    {
      inARow = 0;
    }
  }
#endif
  return;
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
 * toRadio: envia byte 1 ó 2
 */
static void toRadio( int byte )
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
			SMPL_Send(sLID[0], byte_enviouno,  sizeof byte_enviouno );
			
			/* debug */
			//serial_log( "VAR byte_enviouno:\r\n" );
			//serial_log( (char*)byte_enviouno );
			//serial_log( "\r\n" );
		}
		if (byte==2)
		{
			/* establecer byte_enviodos */
			for (i=8; i<=15; ++i)
			{
				byte_enviodos[i-8] = dataFromUART[i];
			}
			
			/* envio mensaje */
			SMPL_Send(sLID[0], byte_enviodos,  sizeof byte_enviodos );
			
			/* debug */
			//serial_log( "VAR byte_enviodos:\r\n" );
			//serial_log( (char*)byte_enviodos );
			//serial_log( "\r\n" );
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
			
			/* debug */
			//serial_log( "\f" );
			//serial_log( "\r\nVAR comando:\r\n" );
			//serial_log( (char*)comando );
			//serial_log( "\r\n" );
			
			/* semáforo comando */
			sCommandSem = 1;
			
			/* establecer final mensaje, agrega x0d */
			dataFromUART[j] = data;
			j++;
			for (i=j; i<=SIZE_MENSAJE; ++i) // continuo agregando datos a comando
			{
				dataFromUART[i] = 0x20; // rellena el comando con espacios = 0x20
			}
			
			/* debug */
			//serial_log( "\r\nVAR dataFromUART:\r\n" );
			//serial_log( (char*)dataFromUART );
			//serial_log( "\r\n" );
			
			if (byte_unoenviado)
			{
				/* hacer envio byte dos */
				toRadio(2);
			}
			else
			{
				/* hacer envio byte uno */
				toRadio(1);
			}
			j = 0;
		} else {
			if (j==7)
			{
				dataFromUART[j] = data;
				if (byte_unoenviado == 0)
				{
					/* debug */
					//serial_log( "\r\nENVIO PRIMERO:\r\n" );
					//serial_log( (char*)dataFromUART );
					//serial_log( "\r\n" );
					
					/* hacer envio byte uno */
					toRadio(1);
					
					byte_unoenviado = 1;
					j++;
				}
			}
			else if (j>=15)
			{
				dataFromUART[j] = data;
			
				/* debug */
				//serial_log( "\r\nENVIO SEGUNDO:\r\n" );
				//serial_log( (char*)dataFromUART );
				//serial_log( "\r\n" );
				
				/* hacer envio byte dos */
				toRadio(2);
				
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
