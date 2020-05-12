#ifndef		__DEFINE__
#define		__DEFINE__

#ifndef __PIC24FJ128GB206__
	#define	__PIC24FJ128GB206__
#endif
#include <xc.h>

#define		UART_1				1
#define		UART_2				2
#define		UART_3				3

// _____________________________________ DEFINE _________________________________
#define		DEVICE						"TEST"
#define		DEVICE_ID					0x0001
#define		LED_COUNT					4
#define		INPUT						INPUT_NO
#define		BUTTON_TIMEOUT_MS			200
// ______________________________ Specific HW Defines ___________________________
#include	"p24Fxxxx.h"

#endif	// __DEFINE__

