#include<reg51.h>
sbit led = P0^2;
sbit led1 = P0^4;
sbit led2 = P0^6;
unsigned char p,q;

void delay();
void init_timer_0();

	main()
	{
		P0 = 0x00;
		EA = 1;
		init_timer_0();
		
		while(1)
		{
			led =~ led;
			delay();
		}
	}
	
	void init_timer_0()
	{
		TMOD = 0x01;
		TH0 = 0x00;
		TL0 = 0x00;
		TR0 = 1;
		ET0 = 1;		
	}
	void isr_to()  interrupt 1 using 0
	{
		init_timer_0();
		led1 =~ led1;
		led2 =~ led2;
		delay();
	}
	
	
	
	void delay()
	{
		
		
			for(q=0;q<255;q++)
			{
			}
		
	}