#include<reg51.h>
sbit led2 =P0^7;
sbit led1 =P0^4;
unsigned char p,q;

void delay();
void init_timer_1();

	main()
	{
		P0 = 0xFF;
		EA = 1;
		init_timer_1();
		
		while(1)
		{
			led2 =~led2;
			delay();
		}
	}
	

	
	void init_timer_1()
	{
		TMOD = 0x10;
		TH1 = 0x00;
		TL1 = 0x00;
		TR1 = 1;
		ET1 = 0;		
	}
	void isr_to()  interrupt 1 using 0
	{
		init_timer_1();
		led1 =~led1;
			delay();
		
		delay();
	}
	
	void delay()
	{
		
			for(q=0;q<255;q++)
			{
			}
			
	}