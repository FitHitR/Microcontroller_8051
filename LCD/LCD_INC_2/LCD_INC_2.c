#include<reg51.h>
#include<intrins.h>
unsigned char ds1,ds2,ds3,ds4,p,q,r;
unsigned char arr[] = {0xfc,0x60,0xda,0xf2,0x66,0xb6,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};
sbit s11 = P2^0;
sbit s12 = P2^1;
sbit s13 = P2^2;
sbit s14 = P2^3;

sbit s1 = P0^0;
sbit rs = P0^1; //commands==0; data_==1;
sbit rw = P0^2; //read==0; wright==1
sbit e = P0^3;  //eanable

sbit d4 = P0^4;
sbit d5 = P0^5;
sbit d6 = P0^6;
sbit d7 = P0^7;


sbit a0 = ACC^0;   //acc bir register_0 to 7
sbit a1 = ACC^1;
sbit a2 = ACC^2;
sbit a3 = ACC^3;
sbit a4 = ACC^4;
sbit a5 = ACC^5;
sbit a6 = ACC^6;
sbit a7 = ACC^7;

bit c;

void delay();                  // delay
void inc();                   //  increments the counter value.
void display();              // current counter value on the LCD
void init_lcd();            // inlization
void c_wr();               // comands fuction
void d_wr();              // data_ function
void map();              // c = a4; d4 = c; to 7
void toggle();          // _nop_ e=0;

		main()
		{
			init_lcd();
			ds1 = '0';  //counter to 0
			ds2 = '0';
			ds3 = '0';
			ds4 = '0';
			while(1)
			{
				for(r=0; r<1; r++)
				display();
				inc();
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
			s1 = 0;
		}
			
		void display()
		{
			ACC = 0x84;
			c_wr();
			delay();
			
			ACC = ds4;
			c_wr();
			delay();
			
			ACC = ds3;
			c_wr();
			delay();
			
			ACC = ds2;
			c_wr();
			delay();
			
			ACC = ds1;
			c_wr();
			delay();
		}
		
		void delay()
		{
			for(p=0; p<80; p++)
			{
				for(q=0; q<250;q++)
				{
				}
			}
		}
		
		void inc()
		{
			ds1++;
			if(ds1 == '9'+1)
			{
				ds1 ='0';
				
				ds2++;
				if(ds2 == '9'+1)
				{
					ds2 = '0';
					
					ds3++;
				if(ds3 == '9'+1)
				{
					ds3 = '0';
					
					ds4++;
				if(ds4 == '9'+1)
				{
					ds1=ds2=ds3=ds4='0';
				}
				}
				}
			}
		}
			
			void c_wr()
			{
				rs = 0;
				rw = 0;
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
				rs = 1;
				rw = 0;
				map();
				toggle();
				a4 = a0;
				a5 = a1;
				a6 = a2;
				a7 = a3;
				map();
				toggle();
			}
			
			void map()
			{
				c = a4;
				d4 = c;
				c = a5;
				d5 = c;
				c = a6;	
				d6 = c;
				c = a7;
				d7 = c;
			}
			
			void toggle()
			{
				_nop_();
				e = 0;
				_nop_();
				e = 1;
				_nop_();
				_nop_();
				e = 0;
				_nop_();
			}
			
			
