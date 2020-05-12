#include	"ports.h"

volatile U16 Btn0_timer = 0, Btn1_timer = 0, Btn2_timer = 0, Btn3_timer = 0;

void InitPorts(void)
{
	InitPort_B();
	InitPort_C();
	InitPort_D();
	InitPort_E();
	InitPort_F();
	InitPort_G();
}


//-------------------------------------------------------------------------------------------------
//	Default PPS configuration after RESET
//-------------------------------------------------------------------------------------------------
void PPSconfig(enum ppsConfig ppsSwitch)
{
//	SistemState = ppsSwitch;
	// Unlock Registers
	__builtin_write_OSCCONL(OSCCONL & 0xbf);

	switch (ppsSwitch)
	{
	case pps_system:
		#if ((defined SET_RX) && (defined SET_TX))
			_U1RXR	= SET_RX;		// RD4	< Rx
			SET_TX	= IO_U1TX;		// RD5	< Tx
		#endif

		PWM_LED0	= IO_OC1;		// PWM
		PWM_LED1	= IO_OC2;		// PWM
		PWM_LED2	= IO_OC3;		// PWM
		PWM_LED3	= IO_OC4;		// PWM
		PWM_LED4	= IO_OC5;		// PWM
		PWM_LED5	= IO_OC6;		// PWM
		PWM_LED6	= IO_OC7;		// PWM
		PWM_LED7	= IO_OC8;		// PWM
		PWM_LED8	= IO_OC9;		// PWM
		break;
	default:
		break;
	}

	// Lock Registers
	__builtin_write_OSCCONL(OSCCONL | 0x40);
}

void _ledSet(U16 num, bool set)
{
	switch (num)
	{
		case 0:	LED_0 = set;	break;
		case 1:	LED_1 = set;	break;
		case 2:	LED_2 = set;	break;
		case 3:	LED_3 = set;	break;
		case 4:	LED_4 = set;	break;
		case 5:	LED_5 = set;	break;
		case 6:	LED_6 = set;	break;
		case 7:	LED_7 = set;	break;
		case 8:	LED_8 = set;	break;
		case 9:	LED_9 = set;	break;
		default:				break;
	}
}

void ledSetAll(bool set)
{
	register U16 i;
	for (i = 0; i < LED_CNT; i++)
		_ledSet(i, set);
}

void LedSet(U16 ledNum, bool set, bool inverseOthers)
{
	if (ledNum >= LED_CNT)
	{
		ledSetAll(set);
		return;
	}
	if (inverseOthers)
		ledSetAll(!set);
		
	_ledSet(ledNum, set);
  #ifdef LED_ALL
  #else
  #endif
}

void InputInit	(void)
{
	
	#if (CN1_PORTS > 0)
		CNEN1 = CN1_PORTS;	// interrupt enable on pin change
		CNPU1 = CN1_PORTS;	// enable pullup for same pins
	#endif
	#if (CN2_PORTS > 0)
		CNEN2 = CN2_PORTS;
		CNPU2 = CN2_PORTS;
	#endif
	#if (CN3_PORTS > 0)
		CNEN3 = CN3_PORTS;
		CNPU3 = CN3_PORTS;
	#endif
	#if (CN4_PORTS > 0)
		CNEN4 = CN4_PORTS;
		CNPU4 = CN4_PORTS;
	#endif
	#if (CN5_PORTS > 0)
		CNEN5 = CN5_PORTS;
		CNPU5 = CN5_PORTS;
	#endif
	#if (CN6_PORTS > 0)
		CNEN6 = CN6_PORTS;
		CNPU6 = CN6_PORTS;
	#endif

	_CNIF = 0;				// Clear CN interrupt flag
	_CNIE = 1;				// Enable CN interrupt
}

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt( void )
{
	_CNIF = 0;				// Clear CN interrupt flag

	if (BTN_0)					Btn0_timer = 0;
	else if (Btn0_timer == 0)	Btn0_timer = BUTTON_TIMEOUT_MS;

	if (BTN_1)					Btn1_timer = 0;
	else if (Btn1_timer == 0)	Btn1_timer = BUTTON_TIMEOUT_MS;

	if (BTN_2)					Btn2_timer = 0;
	else if (Btn2_timer == 0)	Btn2_timer = BUTTON_TIMEOUT_MS;

	if (BTN_3)					Btn3_timer = 0;
	else if (Btn3_timer == 0)	Btn3_timer = BUTTON_TIMEOUT_MS;
}
