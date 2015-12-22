#include "time.h"

//100us进一次中断

void Timer0_ISR() interrupt 1
{

	timer0_xbase++;
	if(timer0_xbase==10){
		timer0_xbase=0;

		if(mt7681_wdt)
			mt7681_wdt--;

		if(Timer_Delay1)
			Timer_Delay1--;	
	}	
}

void Wait_mSec(uint16 x){
	
	Timer_Delay1 = x;
	while(Timer_Delay1);
}


void pdelay(char t)
{
	while(t!=0){
		t--;
	}  
}


