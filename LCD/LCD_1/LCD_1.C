#include<reg51.h>
#include<intrins.h>
unsigned char dc1,dc2,r,s;
sbit sl = P0^0;
sbit rs = P0^1;  //commands==0 or data==1
sbit rw = P0^2;  // read==1 or wright==0
sbit e = P0^3;   // enabled 
sbit d4 = P0^4;
sbit d5 = P0^5;
sbit d6 = P0^6;
sbit d7 = P0^7;

sbit a0 = ACC^0;
sbit a1 = ACC^1;
sbit a2 = ACC^2;
sbit a3 = ACC^3;
sbit a4 = ACC^4;
sbit a5 = ACC^5;
sbit a6 = ACC^6;
sbit a7 = ACC^7;

bit c;           //temporary storage bit

void init_lcd();
void c_wr();        // commands
void d_wr();        // Data
void delay();
void map();         //accumulator bits to the LCD data pins.
void toggle();      // generates a pulse on the LCD enable pin.


unsigned char arr[] = {'R','A','N','J','E','E','T',};
unsigned char arr1[] = {'M','U','N','D','F','A','N','F'};

	main()
   {
		 init_lcd();		
		 ACC = 0x84;    //lcd start with 80 to 8f we waant the name in
		 c_wr();
		 delay();
		 
		 for(r=0; r<=6; r++)
		 {
			 ACC = arr[r];
			 d_wr();
			 delay();
		 }
		 
		 ACC = 0xC5;
		 c_wr();
     delay();
		 for(s=0; s<=7;s++)
		 {
			 ACC = arr[s];
			 d_wr();
			 delay(); 
		 }
		 while(1)
		 {
		 }		 
	 }
	 
	 void init_lcd()
	 {
		 delay();
		 delay();
		 delay();
		 
		 ACC = 0x03;
		 c_wr();
		 delay();
		 
		 ACC = 0x03;
		 c_wr();
		 delay();
		 
		 ACC = 0x03;
		 c_wr();
		 delay();
		 
		 ACC = 0x02;
		 c_wr();
		 delay();
		 
		 ACC = 0x28;
		 c_wr();
		 delay();
		 
		  ACC = 0x01;
		 c_wr();
		 delay();
		 
		  ACC = 0x06;
		 c_wr();
		 delay();
		 
		  ACC = 0x0f;
		 c_wr();
		 delay();
		 sl = 0;
	 }
	 
	 void c_wr()
	 {
		 rs = 0;   //command
		 rw = 0;  //wright
		 map();
		 toggle();
		 a7 = a3;
		 a6 = a2;
		 a5 = a1;
		 a4 = a0;
		 map();
		 toggle();		 
	 }
	 
	 void d_wr()
	 {
		 rs = 1;   //data
		 rw = 0;   //wright
		 map();
		 toggle();
		 a4 = a0;
		 a5 = a1;
		 a6 = a2;
		 a7 = a3;
		 map();
		 toggle();		 
	 }
	 
	 void delay()
	 {
		 for(dc2=0; dc2<80; dc2++)
		 {
			 for(dc1=0; dc1<250; dc1++)
			 {
			 }
		 }
	 }
	 
	 void map()
	 {
		 c = a4;
		 d4 = c;
		 c = a5 ;
		 d5 = c;
		 c = a6;
		 d6 = c;
		 c = a7;
		 d6 = c;
	 }
	 
	 void toggle()
	 {                    //e==0; receive data or commands
		 _nop_();           //e== 1; can not be
		 e = 0;
		 _nop_();           //_nop_ = "No Operation".
		 e = 1;
		 _nop_();
		 _nop_();
		 e = 0;
		 _nop_();
	 }