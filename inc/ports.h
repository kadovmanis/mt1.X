#ifndef	_ports_h_
#define	_ports_h_

#include	"typedef.h"

enum ppsConfig
{
	pps_system = 0,
	pps_default
};

void InitPorts  (void);
void PPSconfig  (enum ppsConfig ppsSwitch);
void Reset      (void);
void LedSet		(U16 ledNum, bool set, bool inverseOthers);
void InputInit	(void);

// PERIPHERAL PIN SELECT OUTPUT SOURCES
#define IO_PORT		0		//	RPn tied to default port pin
#define IO_C1OUT	1		//	RPn tied to Comparator1 Output
#define IO_C2OUT	2		//	RPn tied to Comparator2 Output
#define IO_U1TX		3		//	RPn tied to UART1 Transmit
#define IO_U1RTS	4		//	RPn tied to UART1 Ready To Send
#define IO_U2TX		5		//	RPn tied to UART2 Transmit
#define IO_U2RTS	6		//	RPn tied to UART2 Ready To Send
#define IO_SDO1		7		//	RPn tied to SPI1 Data Output
#define IO_SCK1OUT	8		//	RPn tied to SPI1 Clock Output
#define IO_SS1OUT	9		//	RPn tied to SPI1 Slave Select Output
#define IO_SDO2		10		//	RPn tied to SPI2 Data Output
#define IO_SCK2OUT	11		//	RPn tied to SPI2 Clock Output
#define IO_SS2OUT	12		//	RPn tied to SPI2 Slave Select Output
#define IO_OC1		18		//	RPn tied to Output Compare 1
#define IO_OC2		19		//	RPn tied to Output Compare 2
#define IO_OC3		20		//	RPn tied to Output Compare 3
#define IO_OC4		21		//	RPn tied to Output Compare 4
#define IO_OC5		22		//	RPn tied to Output Compare 5
#define IO_OC6		23		//	RPn tied to Output Compare 6 
#define IO_OC7		24		//	RPn tied to Output Compare 7
#define IO_OC8		25		//	RPn tied to Output Compare 8
#define IO_U3TX		28		//	RPn tied to UART3 Transmit
#define IO_U3RTS	29		//	RPn tied to UART3 Ready To Send
#define IO_U4TX		30		//	RPn tied to UART4 Transmit
#define IO_U4RTS	31		//	RPn tied to UART4 Ready To Send
#define IO_SDO3		32		//	RPn tied to SPI3 Data Output
#define IO_SCK3OUT	33		//	RPn tied to SPI3 Clock Output
#define IO_SS3OUT	34		//	RPn tied to SPI3 Slave Select Output
#define IO_OC9		35		//	RPn tied to Output Compare 9
#define IO_C3OUT	36		//	RPn tied to Comparator3 Output

// PERIPHERAL PIN SELECT OUTPUT REGISTERS
#define PPS_OUT_B0		_RP0R
#define PPS_OUT_B1		_RP1R
#define PPS_OUT_B2		_RP13R
#define PPS_OUT_B3
#define PPS_OUT_B4		_RP28R
#define PPS_OUT_B5		_RP18R
#define PPS_OUT_B6		_RP6R
#define PPS_OUT_B7		_RP7R
#define PPS_OUT_B8		_RP8R
#define PPS_OUT_B9		_RP9R
#define PPS_OUT_B10
#define PPS_OUT_B11
#define PPS_OUT_B12
#define PPS_OUT_B13
#define PPS_OUT_B14		_RP14R
#define PPS_OUT_B15		_RP29R

#define PPS_OUT_C12
#define PPS_OUT_C13
#define PPS_OUT_C14		// RPI37 - input only
#define PPS_OUT_C15

#define PPS_OUT_D0		_RP11R
#define PPS_OUT_D1		_RP24R
#define PPS_OUT_D2		_RP23R
#define PPS_OUT_D3		_RP22R
#define PPS_OUT_D4		_RP25R
#define PPS_OUT_D5		_RP20R
#define PPS_OUT_D6
#define PPS_OUT_D7
#define PPS_OUT_D8		_RP2R
#define PPS_OUT_D9		_RP4R
#define PPS_OUT_D10		_RP3R
#define PPS_OUT_D11		_RP12R

#define PPS_OUT_E0
#define PPS_OUT_E1
#define PPS_OUT_E2
#define PPS_OUT_E2
#define PPS_OUT_E3
#define PPS_OUT_E4
#define PPS_OUT_E5
#define PPS_OUT_E6
#define PPS_OUT_E7

#define PPS_OUT_F0
#define PPS_OUT_F1
#define PPS_OUT_F3		_RP16R
#define PPS_OUT_F4		_RP10R
#define PPS_OUT_F5		_RP17R
#define PPS_OUT_F7

#define PPS_OUT_G2
#define PPS_OUT_G3
#define PPS_OUT_G6		_RP21R
#define PPS_OUT_G7		_RP26R
#define PPS_OUT_G8		_RP19R
#define PPS_OUT_G9		_RP27R



// PERIPHERAL PIN SELECT INTPUT REGISTERS
#define	PPS_IN_VSS		0b11111		//	Periferal INput tied to Vss by default
#define PPS_IN_B0		0
#define PPS_IN_B1		1
#define PPS_IN_B2		13
#define PPS_IN_B3
#define PPS_IN_B4		28
#define PPS_IN_B5		18
#define PPS_IN_B6		6
#define PPS_IN_B7		7
#define PPS_IN_B8		8
#define PPS_IN_B9		9
#define PPS_IN_B10
#define PPS_IN_B11
#define PPS_IN_B12
#define PPS_IN_B13
#define PPS_IN_B14		14
#define PPS_IN_B15		29

#define PPS_IN_C12
#define PPS_IN_C13
#define PPS_IN_C14		37			// i
#define PPS_IN_C15

#define PPS_IN_D0		11
#define PPS_IN_D1		24
#define PPS_IN_D2		23
#define PPS_IN_D3		22
#define PPS_IN_D4		25
#define PPS_IN_D5		20
#define PPS_IN_D6
#define PPS_IN_D7
#define PPS_IN_D8		2
#define PPS_IN_D9		4
#define PPS_IN_D10		3
#define PPS_IN_D11		12

#define PPS_IN_E0
#define PPS_IN_E1
#define PPS_IN_E2
#define PPS_IN_E2
#define PPS_IN_E3
#define PPS_IN_E4
#define PPS_IN_E5
#define PPS_IN_E6
#define PPS_IN_E7

#define PPS_IN_F0
#define PPS_IN_F1
#define PPS_IN_F3		16
#define PPS_IN_F4		10
#define PPS_IN_F5		17
#define PPS_IN_F7

#define PPS_IN_G2
#define PPS_IN_G3
#define PPS_IN_G6		21
#define PPS_IN_G7		26
#define PPS_IN_G8		19
#define PPS_IN_G9		27

//_________________________________________________I/O_________________________________
//#define LED_ALL			(LATB & 0xFFC0)

#define InitPort_B()	LATB = 0x0000; TRISB = 0x003F; ODCB = 0x0000; ANSB = 0x003F
#define LED_0			_LATB15		//				O	0
#define LED_1			_LATB14		//				O	0
#define LED_2			_LATB13		//				O	0
#define LED_3			_LATB12		//				O___0______
#define LED_4			_LATB11		//				O	0
#define LED_5			_LATB10		//				O	0
#define LED_6			_LATB9		//				O	0
#define LED_7			_LATB8		//				O___0______
#define LED_8			_LATB7		//				O	0
#define LED_9			_LATB6		//				O	0
#define AN_EXT0			ADC1BUF5	// _RB5	// AN5	I	0	A
#define AN_EXT1			ADC1BUF4	// _RB4	// AN4	I___0___A_
#define AN_EXT2			ADC1BUF3	// _RB3	// AN3	I	0	A
#define AN_EXT3			ADC1BUF2	// _RB2	// AN2	I	0	A
#define AN_BAT			ADC1BUF1	// _RB1	// AN1	I	0	A
#define AN_POW			ADC1BUF0	// _RB0	// AN0	I___0___A_
#define AN_V18			ADC1BUF6	// Vcap					A

#define LED_CNT			10
//___________________________________________________________________________________
#define InitPort_C()	LATC = 0x0000; TRISC = 0x9FFF; ODCC = 0x0000; ANSC = 0x0000
#define OSCO			_LATC15		//				I	0
//#define NC			_LATC14		//				O	0
//#define NC			_LATC13		//				O	0
#define OSCI			_LATC12		//				I___0______
//___________________________________________________________________________________
#define InitPort_D()	LATD = 0x0000; TRISD = 0x0000; ODCD = 0x0000; ANSD = 0x0000
//#define NC			_LATD15		//				O	0
//#define NC			_LATD14		//				O	0
//#define NC			_LATD13		//				O	0
//#define NC			_LATD12		//				O___0______
//#define NC			_LATD13		//				O	0
#define PWM_LED8		PPS_OUT_D10	//				O	0
#define PWM_LED7		PPS_OUT_D9	//				O	0
#define PWM_LED6		PPS_OUT_D8	//				O___0______
//#define NC			_LATD7		//				O	0
//#define NC			_LATD6		//				O	0
#define PWM_LED5		PPS_OUT_D5	//				O	0
#define PWM_LED4		PPS_OUT_D4	//				O___0______
#define PWM_LED3		PPS_OUT_D3	//				O	0
#define PWM_LED2		PPS_OUT_D2	//				O	0
#define PWM_LED1		PPS_OUT_D1	//				O	0
#define PWM_LED0		PPS_OUT_D0	//				O___0______

//___________________________________________________________________________________
#define InitPort_E()	LATE = 0x0000; TRISE = 0x0000; ODCE = 0x0000
//#define NC			_LATE15		//				O	0
//#define NC			_LATE14		//				O	0
//#define NC			_LATE13		//				O	0
//#define NC			_LATE12		//				O___0______
//#define NC			_LATE11		//				O	0
//#define NC			_LATE10		//				O	0
//#define NC			_LATE9		//				O	0
//#define NC			_LATE9		//				O___0______
//#define NC			_LATE7		//				O	0
//#define NC			_LATE6		//				O	0
//#define NC			_LATE5		//				O	0
//#define NC			_LATE4		//				O___0______
//#define NC			_LATE3		//				O	0
//#define NC			_LATE2		//				O	0
//#define NC			_LATE1		//				O	0
//#define NC			_LATE0		//				O___0______

//___________________________________________________________________________________
#define InitPort_F()	LATF = 0x0000; TRISF = 0x0030; ODCF = 0x0002; ANSF = 0x0000
//#define NC			_LATF15		//				O	0
//#define NC			_LATF14		//				O	0
//#define NC			_LATF13		//				O	0
//#define NC			_LATF12		//				O___0______
//#define NC			_LATF11		//				O	0
//#define NC			_LATF10		//				O	0
//#define NC			_LATF9		//				O	0
//#define NC			_LATF8		//				O___0______
//#define NC			_LATF7		//				O	0
//#define NC			_LATF6		//				O	0
#define SET_TX			PPS_OUT_D5	//				I	0
#define SET_RX			PPS_IN_D4	//				I___0______
//#define NC			_LATF3		//				O	0	
//#define NC			_LATF3		//				O	0
//#define NC			_LATF2		//				O	0
//#define NC			_LATF1		//				O	0
//#define NC			_LATF0		//				O___0______

//___________________________________________________________________________________
#define InitPort_G()	LATG = 0x0000; TRISG = 0xFFFF; ODCG = 0x0000; ANSG = 0x0000; U1CNFG2bits.UTRDIS = 1
//#define NC			_RD2		//				I	0
//#define NC			_RD3		//				I	0
#define BTN_3			_RD6		//				I	0
#define BTN_2			_RD7		//				I___0______
#define BTN_1			_RD8		//				I	0
#define BTN_0			_RD9		//				I	0

//------------------------------------------------------------------------------------
#define	CN1_PORTS	0b0000111100000000
/*					  |||||||||||||||+-	CN0IE	C14
					  ||||||||||||||+--	CN1IE	C13
					  |||||||||||||+---	CN2IE	B0
					  ||||||||||||+----	CN3IE	B1
					  |||||||||||+-----	CN4IE	B2
					  ||||||||||+------	CN5IE	B3
					  |||||||||+-------	CN6IE	B4
					  ||||||||+--------	CN7IE	B5
					  |||||||+---------	CN8IE	G6
					  ||||||+----------	CN9IE	G7
					  |||||+-----------	CN10IE	G8
					  ||||+------------	CN11IE	G9
					  |||+-------------	CN12IE	B15
					  ||+--------------	CN13IE	D4
					  |+---------------	CN14IE	D5
					  +----------------	CN15IE	D6				*/
#define	CN2_PORTS	0b0000000000000000
/*					  |||||||||||||||+-	CN16IE	D7
					  ||||||||||||||+--	CN17IE	F4
					  |||||||||||||+---	CN18IE	F5
					  ||||||||||||+----	CN19IE	
					  |||||||||||+-----	CN20IE	
					  ||||||||||+------	CN21IE	
					  |||||||||+-------	CN22IE	C15
					  ||||||||+--------	CN23IE	C12
					  |||||||+---------	CN24IE	B6
					  ||||||+----------	CN25IE	B7
					  |||||+-----------	CN26IE	B8
					  ||||+------------	CN27IE	B9
					  |||+-------------	CN28IE	B10
					  ||+--------------	CN29IE	B11
					  |+---------------	CN30IE	B12
					  +----------------	CN31IE	B13				*/
#define	CN3_PORTS	0b0000000000000000
/*					  |||||||||||||||+-	CN32IE	B14
					  ||||||||||||||+--	CN33IE	B15
					  |||||||||||||+---	CN34IE	
					  ||||||||||||+----	CN35IE	
					  |||||||||||+-----	CN36IE	
					  ||||||||||+------	CN37IE	
					  |||||||||+-------	CN38IE	
					  ||||||||+--------	CN39IE	
					  |||||||+---------	CN40IE	
					  ||||||+----------	CN41IE	
					  |||||+-----------	CN42IE	
					  ||||+------------	CN43IE	
					  |||+-------------	CN44IE	
					  ||+--------------	CN45IE	
					  |+---------------	CN46IE	
					  +----------------	CN47IE					*/
#define	CN4_PORTS	0b0000000000000000
/*					  |||||||||||||||+-	CN48IE	
					  ||||||||||||||+--	CN49IE	D0	BTN_0
					  |||||||||||||+---	CN50IE	D1	BTN_1
					  ||||||||||||+----	CN51IE	D2	BTN_2
					  |||||||||||+-----	CN52IE	D3	BTN_3
					  ||||||||||+------	CN53IE	D8
					  |||||||||+-------	CN54IE	D9
					  ||||||||+--------	CN55IE	D10
					  |||||||+---------	CN56IE	D11
					  ||||||+----------	CN57IE	
					  |||||+-----------	CN58IE	E0
					  ||||+------------	CN59IE	E1
					  |||+-------------	CN60IE	E2
					  ||+--------------	CN61IE	E3
					  |+---------------	CN62IE	E4
					  +----------------	CN63IE	E5			*/
#define	CN5_PORTS	0b0000000000000000
/*					  |||||||||||||||+-	CN64IE	E6
					  ||||||||||||||+--	CN65IE	E7	SW2
					  |||||||||||||+---	CN66IE	
					  ||||||||||||+----	CN67IE	
					  |||||||||||+-----	CN68IE	F0
					  ||||||||||+------	CN69IE	F1
					  |||||||||+-------	CN70IE	
					  ||||||||+--------	CN71IE	F3	USB_ID
					  |||||||+---------	CN72IE	
					  ||||||+----------	CN73IE	
					  |||||+-----------	CN74IE	
					  ||||+------------	CN75IE	
					  |||+-------------	CN76IE	
					  ||+--------------	CN77IE	
					  |+---------------	CN78IE	
					  +----------------	CN79IE					*/
#define	CN6_PORTS	0b0000000000000000
/*					  |||||||||||||||+-	CN80IE	
					  ||||||||||||||+--	CN81IE	
					  |||||||||||||+---	CN82IE	
					  ||||||||||||+----	CN83IE	G2
					  |||||||||||+-----	CN84IE	G3
					  ||||||||||+------	CN85IE	
					  |||||||||+-------	CN86IE	
					  ||||||||+--------	CN87IE	
					  |||||||+---------	CN88IE	
					  ||||||+----------	CN89IE	
					  |||||+-----------	CN90IE	
					  ||||+------------	CN91IE	
					  |||+-------------	CN92IE	
					  ||+--------------	CN93IE	
					  |+---------------	CN94IE	
					  +----------------	CN95IE					*/

#endif


