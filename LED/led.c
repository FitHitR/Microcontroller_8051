#include <reg51.h>

sbit led1 = P0^0;
sbit led2 = P0^1;
sbit led3 = P0^2;
sbit led4 = P0^3; 
sbit led5 = P0^4;
sbit led6 = P0^5;
sbit led7 = P0^6;
sbit led8 = P0^7;
void delay();
void main() {
    P0= 0x00; // 

    while(1) {
        // Turn on LED1-LED8 sequentially
        led1 = 1; 
				delay();
        led2 = 1;
				delay();
        led3 = 1; 
				delay();
        led4 = 1; 
				delay();
        led5 = 1; 
				delay();
        led6 = 1; 
				delay();
        led7 = 1; 
				delay();
        led8 = 1; 
				delay();

        // Turn off LED1-LED8 sequentially
        led1 = 0; 
				delay();
        led2 = 0; 
				delay();
        led3 = 0;
				delay();
        led4 = 0; 
				delay();
        led5 = 0; 
				delay();
        led6 = 0; 
				delay();
        led7 = 0; 
				delay();
        led8 = 0;
				delay();
    }
}

	void delay() 
		{
			unsigned int i;
			for(i=0;i<255;i++)
			{
			}
}
