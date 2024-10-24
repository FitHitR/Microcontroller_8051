#include<reg51f.h>
unsigned char ds1,ds2,ds3,ds4,p,q;
sbit s11 = P2^0;
sbit s12 = P2^1;
sbit s13 = P2^2;
sbit s14 = P2^3;
	void delay();
	
	main()
	{
		P0 = 0x00;  //0ut put
		while(1)
		{
			s11 = 0;
			s12 = 1;
			s13 = 1;
			s14 = 1;
			ds1 = 0x60; //1
			P0 = ds1;
			delay();
			
			s11 = 1;
			s12 = 0;
			s13 = 1;
			s14 = 1;
			ds1 = 0xf2; //3
			P0 = ds2;
			delay();
			
			s11 = 1;
			s12 = 1;
			s13 = 0;
			s14 = 1;
			ds1 = 0xda; //2
			P0 = ds3;
			delay();
			
			s11 = 1;
			s12 = 1;
			s13 = 1;
			s14 = 0;
			ds1 = 0x66; //4
			P0 = ds4;
			delay();
		}
	}
	
	void delay()
	{
		for(p=0;p<5;p++)
		{
			for(q=0;q<255;q++)
			{
			}
		}
	}
