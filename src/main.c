#include		"typedef.h"
#include		"config.h"

#include		"ports.h"
#include		"timers.h"

#include		<stdio.h>


int main (void)
{
	InitPorts();
	OSCconfig(Osc_32_MHz);
	PPSconfig(pps_system);
	InputInit();

	while (true)
	{
	}
	return 0;
}

