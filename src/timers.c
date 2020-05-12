#include	"timers.h"
#include	"ports.h"
#include	<string.h>

extern volatile U16 Btn0_timer, Btn1_timer, Btn2_timer, Btn3_timer;
volatile U16		Sec, Ms = 0, Tics_ms = 0;
volatile S16		LedUpDurationMs = 250, LedDirection = 1;
volatile LED_BLINK_STYLE BlinkStyle = OneLedOn;
volatile TIME_ST	SysTime;


//-------------------------------------------------------------------------------------------------
//	OSC_4__MHZ_FRCDIV	Fast RC Oscillator with Postscaler (FRCDIV)
//	OSC_05_MHZ_FRC_16	Fast RC Oscillator/16 (500 KHz)
//	OSC_31_KHZ_LPRC		Low-Power RC Oscillator (LPRC)
//	OSC_0__MHZ_SOSC		Secondary Oscillator (SOSC)
//	OSC_0__MHZ_PRI_PLL	Primary Oscillator with PLL module (XTPLL, HSPLL, ECPLL)
//	OSC_0__MHZ_PRI		Primary Oscillator (XT, HS, EC)
//	OSC_32_MHZ_FRCPLL	Fast RC Oscillator with Postscaler and PLL module (FRCPLL)
//	OSC_8__MHZ_FRC		Fast RC Oscillator (FRC)
//-------------------------------------------------------------------------------------------------
OSC Oscillator = Osc_4__MHz;
const U16 BaudRates[5][8] =
{
	{
		((( 8000000 /2 / 16) / 9600) - 1),		// 26.04166
		(((32000000 /2 / 16) / 9600) - 1),		// 104.1666
		(((       0 /2 / 16) / 9600) - 1),		// 0
		(((       0 /2 / 16) / 9600) - 1),		// 0
		(((       0 /2 / 16) / 9600) - 1),		// 0
		(((   31000 /2 / 16) / 9600) - 1),		// 0
		(((  500000 /2 / 16) / 9600)),			// 1,627604
		((( 4000000 /2 / 16) / 9600) - 1)		// 13
	},
	{
		((( 8000000 /2 / 16) / 19200) - 1),		// 13.0208
		(((32000000 /2 / 16) / 19200) - 1),		// 53.0833
		(((       0 /2 / 16) / 19200) - 1),		// 0
		(((       0 /2 / 16) / 19200) - 1),		// 0
		(((       0 /2 / 16) / 19200) - 1),		// 0
		(((   31000 /2 / 16) / 19200) - 1),		// 0
		(((  500000 /2 / 16) / 19200) - 1),		// 0
		((( 4000000 /2 / 16) / 19200))			// 6.5104
	},
	{
		((( 8000000 /2 / 16) / 38400)),			// 6.5104
		(((32000000 /2 / 16) / 38400) - 1),		// 26.0416
		(((       0 /2 / 16) / 38400) - 1),		// 0
		(((       0 /2 / 16) / 38400) - 1),		// 0
		(((       0 /2 / 16) / 38400) - 1),		// 0
		(((   31000 /2 / 16) / 38400) - 1),		// 0
		(((  500000 /2 / 16) / 38400)),			// 0
		((( 4000000 /2 / 16) / 38400) - 1)		// 3.2552
	},
	{
		((( 8000000 /2 / 16) / 57600) - 1),		// 4.340278
		(((32000000 /2 / 16) / 57600) - 1),		// 17.36111
		(((       0 /2 / 16) / 57600) - 1),		// 0
		(((       0 /2 / 16) / 57600) - 1),		// 0
		(((       0 /2 / 16) / 57600) - 1),		// 0
		(((   31000 /2 / 16) / 57600) - 1),		// 0
		(((  500000 /2 / 16) / 57600)),			// 0
		((( 4000000 /2 / 16) / 57600) - 1)		// 2.170139
	},
	{
		((( 8000000 /2 / 16) / 115200) - 1),	// 2,170138
		(((32000000 /2 / 16) / 115200)),		// 8,680555
		(((       0 /2 / 16) / 115200) - 1),	// 0
		(((       0 /2 / 16) / 115200) - 1),	// 0
		(((       0 /2 / 16) / 115200) - 1),	// 0
		(((   31000 /2 / 16) / 115200) - 1),	// 0
		(((  500000 /2 / 16) / 115200)),		// 0
		((( 4000000 /2 / 16) / 115200) - 1)		// 1,085069
	},
};


void OSCconfig(OSC osc)
{
	Oscillator = osc;
//	CLKDIV	= 	0b0000000100000000
			//	  |||||||||||+++++	---	Unimplemented (Reserved)
			//	  ||||||||||+-----	---	PLLEN: 96 MHz PLL Enable bit
			//	  ||||||||++------	---	CPDIV<1:0>: System Clock Select bits (postscaler select from 32 MHz clock branch)
			//	  |||||+++--------	---	RCDIV<2:0>: FRC Postscaler Select bits
			//	  ||||+-----------	---	DOZEN: DOZE Enable bit
			//	  |+++------------	---	DOZE<2:0>: CPU Peripheral Clock Ratio Select bits
			//	  +---------------	---	ROI: Recover on Interrupt bit

	if ((osc == Osc_32_MHz) /*|| (osc == Osc_0_PriPLL)*/)
		_PLLEN = 1;					// Enable PLL 96 MHz


	__builtin_write_OSCCONH(osc);
	__builtin_write_OSCCONL(0x01);	// Initiate Clock Switch

	// Wait for Clock switch to occur
	while (_OSWEN);

	// Wait for PLL to lock
	if ((osc == Osc_32_MHz) /*|| (osc == Osc_0_PriPLL)*/)
	{
		while(_LOCK != 1);
	}
	else
		_PLLEN = 0;					// Disable PLL 96 MHz

	TimersInit();
}


// **********************************************************************
//	Init All Timers
// **********************************************************************
void TimersInit(void)
{
	T1CON				= 0;		//	Timer1 reset
	T2CON				= 0;		//	Timer2 reset
	T3CON				= 0;		//	Timer3 reset
	T4CON				= 0;		//	Timer4 reset
	OC1CON1bits.OCM		= 0; 		// Output compare channel is disabled (PWM)
	OC2CON1bits.OCM		= 0; 		// Output compare channel is disabled (PWM)

	switch (Oscillator)
	{
	case Osc_8__MHz:
		T1CONbits.TCKPS	= 0b10;				//	T1 Prescaler	| 11b - 1:256;	10b - 1:64
		T2CONbits.TCKPS	= 0b00;				//	T2 Prescaler	| 01b - 1:8;	00b - 1:1
		T3CONbits.TCKPS	= 0b10;				//	T3 Prescaler
		PR1		= (4000000 / 64 / 1000);	//	FOSC / Prescaler / 1000Hz	(mS)
//		PR2		= DC_PERIOD;				//	DC/DC period
		PR3		= (4000000 / 64 / 1000);	//	FOSC / Prescaler / 1000Hz 	(mS)
		break;
	case Osc_32_MHz:
		T1CONbits.TCKPS	= 0b10;					//	T1 Prescaler	| 00b - 1:1
		T2CONbits.TCKPS	= 0b00;					//	T2 Prescaler	| 01b - 1:8
		T3CONbits.TCKPS	= 0b10;					//	T3 Prescaler	| 10b - 1:64
		T4CONbits.TCKPS	= 0b01;					//	T4 Prescaler	| 11b - 1:256
		PR1		= (16000000 /  64 / 1000) - 1;	//	FOSC / Prescaler / 1000Hz	(1mS)
		PR2		= (DC_PERIOD	 		  - 1);	//	DC/DC period
		PR3		= (16000000	/  64 / 100)  - 1;	//	FOSC / Prescaler / 100Hz 	(10mS)
		PR4		= (16000000 /   8 / 100)  - 1;	//	FOSC / Prescaler / 100Hz
		break;
	case Osc_31_kHz:
		T1CONbits.TCKPS	= 0b00;				//	T1 Prescaler	| 11b - 1:256;	10b - 1:64
		T2CONbits.TCKPS	= 0b00;				//	T2 Prescaler	| 01b - 1:8;	00b - 1:1
		T3CONbits.TCKPS	= 0b00;				//	T3 Prescaler
		PR1		= (15500 / 1 / 1000);		//	FOSC / Prescaler / 1000Hz	(mS)
//		PR2		= DC_PERIOD;				//	DC/DC period
		PR3		= (15500 / 1 / 1000);		//	FOSC / Prescaler / 1000Hz 	(mS)
		break;
	case Osc_05_MHz:
		T1CONbits.TCKPS	= 0b00;				//	T1 Prescaler	| 11b - 1:256;	10b - 1:64
		T2CONbits.TCKPS	= 0b00;				//	T2 Prescaler	| 01b - 1:8;	00b - 1:1
		T3CONbits.TCKPS	= 0b00;				//	T3 Prescaler
		PR1		= (250000 / 1 / 1000);		//	FOSC / Prescaler / 1000Hz	(mS)
//		PR2		= DC_PERIOD;				//	DC/DC period
		PR3		= (250000 / 1 / 1000);		//	FOSC / Prescaler / 1000Hz 	(mS)
		break;
	case Osc_4__MHz:
	case Osc_0_Pri:
	case Osc_0_PriPLL:
	case Osc_0_SOSC:
	default:
		T1CONbits.TCKPS	= 0b01;				//	T1 Prescaler	| 11b - 1:256;	10b - 1:64
		T2CONbits.TCKPS	= 0b00;				//	T2 Prescaler	| 01b - 1:8;	00b - 1:1
		T3CONbits.TCKPS	= 0b10;				//	T3 Prescaler
		PR1		= (2000000 / 8 / 1000);		//	FOSC / Prescaler / 1000Hz	(mS)
//		PR2		= DC_PERIOD;				//	DC/DC period
		PR3		= (2000000 / 64 / 1000);	//	FOSC / Prescaler / 1000Hz 	(mS)
		break;
	}

	OC1R					= 0;		// Initialize Compare Register1 with 0% duty cycle				(default)
	OC1CON1bits.OCM			= 0b110;	// Edge-Aligned PWM Mode on OCx (Fault pin disabled)

	_T1IP = 4;		//	Timer1 Interrupt priority level=4
	_T2IP = 4;		//	Timer2 Interrupt priority level=4
	_T3IP = 4;		//	Timer3 Interrupt priority level=4
	_T4IP = 4;		//	Timer4 Interrupt priority level=4

	memset((char*)&SysTime, 0, sizeof(SysTime));
	T1CONbits.TON = 1;		//	Enable Timer1 and start the counter
	_T1IF = 0;				//	Reset Timer1 interrupt flag
	_T1IE = 1;				//	Enable Timer1 interrupt

	T2CONbits.TON = 1;		//	Enable Timer2 and start the counter
//	_T2IF = 0;				//	Reset Timer2 interrupt flag
//	_T2IE = 1;				//	Enable Timer2 interrupt

	T3CONbits.TON = 1;		//	Enable Timer3 and start the counter
	_T3IF = 0;				//	Reset Timer3 interrupt flag
	_T3IE = 1;				//	Enable Timer3 interrupt

	T4CONbits.TON = 1;		//	Enable Timer4 and start the counter
//	_T4IF = 0;				//	Clear  Timer4 interrupt flag
//	_T4IE = 1;				//	Enable Timer4 interrupt
}

// **********************************************************************
inline	void SysTimeIrq		(void);
inline	void LedStatusUpdate(void);
inline	void ButtonCheck	(void);
// ......................................................................
// Timer1 INTERRUPT			1000Hz - 1ms
// **********************************************************************
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt( void )
{
	_T1IF = 0;				//	Reset Timer1 interrupt flag

	Tics_ms++;
	SysTimeIrq();
	LedStatusUpdate();
	ButtonCheck();
}

inline	void SysTimeIrq	(void)
{
	if (++Ms >= 1000)
	{	Ms		= 0;
		Sec++;
		if (++SysTime.sec >= 60)
		{
			SysTime.sec = 0;
			if (++SysTime.min >= 60)
			{
				SysTime.min = 0;
				if (++SysTime.hour >= 24)
				{
					SysTime.hour = 0;
					++SysTime.day;
				}
			}
		}
	}
}


inline void LedStatusUpdate(void)
{
	static S16 ledTimer = 0, ledStatus = 0;

	if (++ledTimer < LedUpDurationMs)
		return;
	
	ledTimer = 0;
	switch (BlinkStyle)
	{
		case Blink:
			ledStatus = (ledStatus)? 0 : 1;
			LedSet(LED_CNT, (ledStatus), true);
			break;
		default:
			ledStatus += LedDirection;
			if (ledStatus >= LED_CNT)	ledStatus = 0;
			else if (ledStatus < 0)		ledStatus = LED_CNT;

			LedSet(ledStatus, true, true);
			break;
	}
}

inline	void ButtonCheck(void)
{
	if ((Btn0_timer) && (!--Btn0_timer))	// speed up
	{
		if (LedUpDurationMs > 50)
			LedUpDurationMs -= 50;
	}
	if ((Btn1_timer) && (!--Btn1_timer))	// change blink style
	{
		if (BlinkStyle == Blink)
		{
			BlinkStyle = OneLedOn;
			LedDirection = (LedDirection > 0)? -1 : 1;
		}
		else
			BlinkStyle++;
	}
	if ((Btn2_timer) && (!--Btn2_timer))	// speed down
	{
		if (LedUpDurationMs < 1000)
			LedUpDurationMs += 50;
	}
	if ((Btn3_timer) && (!--Btn3_timer))	// restart
	{
			__asm__ ("RESET");
			while(1);
	}
}

// **********************************************************************
// Timer2 INTERRUPT			50kHz
// **********************************************************************
void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void)
{
	_T2IF = 0;				//	Reset Timer2 interrupt flag
}

// **********************************************************************
// ......................................................................
// Timer3 INTERRUPT			100Hz - 10ms
// **********************************************************************
void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void)
{
	_T3IF = 0;				//	Reset Timer3 interrupt flag
}

void DelayMs(U16 ms)
{
	ms++;
	ms += Tics_ms;
	while (Tics_ms != ms);
}

U16 GetTicsMs(void)
{
	return Tics_ms;
}

U16 GetTimeSinceMs(U16 previousTics)
{
	return (Tics_ms >= previousTics)?	(Tics_ms - previousTics):((0 - previousTics) + Tics_ms);
}

U16 GetSec(void)
{
	return	Sec;
}

U16 GetTimeSinceSec(U16 previousSec)
{
	return (Sec >= previousSec)?			(Sec - previousSec):((0 - previousSec) + Sec);
}
