#include<reg51.h>
sbit s11 = P2^0;
sbit s12 = P2^1;
sbit s13 = P2^2;
sbit s14 = P2^3;
sbit kr11 = P2^4;
sbit kr12 = P2^5;
sbit kr13 = P2^6;
sbit kr14 = P2^7;

sbit sb = P2^5;

bit key_ready;
bit nkp;
bit tb;
bit s_buzzer;
bit c;

unsigned char ds1,ds2,ds3,ds4,p,q,r,sn,d_count,k_count,key_code,x,y,z;
unsigned char arr[] = {0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe4,0xfe,0xf6,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};
unsigned char ascii[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

	void sdelay();        // delay
	void init();          //inlization
	void init_key();      //key_pad setup
	void init_timer_0();   // timer 0
	void scanner();        //switch stement
	void k();              //key   checks if a key is pressed and debounces the key press.
	void rr();             // row set
	void key_release();    //key release
	void buzzer();          // buzzer

   void main()
	 {
		 init();
		 EA=1;
		 P0= 0x00;
		 while(1)
		 {
			 while(key_ready == 0);
			 ACC = key_ready;
			 ds1 = ascii[ACC];
			 key_release();
		 }
	 }
	 
	 void init()
	 {
		 init_key(); 
		 init_timer_0();
	 }
	 
	 void init_key()
	 {
		 kr11 = 1;
		 kr12 = 1;
		 kr13 = 1;
		 kr14 = 1;
		 sn = 0;
		 d_count = 33;
		 k_count = 32;
		 key_ready = 0;
		 nkp = 0;
		 s_buzzer= 0;
	 }
	 
	 void init_timer_0()
	 {
		 TMOD = 0X01;
		 TL0 = 0X66;
		 TH0 = 0XFF;
		 TR0 = 1;
		 ET0 = 1;
	 }
	 void isr_to()  interrupt 1 using 0
	 {
		 void init_timer_0();
		 void buzzer();
		 void scanner(); 
	 }
	 
	 void scanner()
	 {
		 ACC = sn;
		 
		 switch(ACC)
		 {
			 case 0:
			 s11 = 0;
			 s12 = 1;
			 s13 = 1;
			 s14 = 1;
			 P0 = arr[ds1-'0'];
			 c = kr11;
			 k();
			 sn =1;
			 break;
			 
			 case 1:
			 c = kr12;
			 k();
			 sn = 2;
			 break; 
			 
			 case 2:
			 c = kr13;
			 k();
			 sn = 3;
			 break; 
			 
			 case 3:
			 P0 = 0x00;
			 c = kr14;
			 k();
			 sn = 4;
			 break; 
			 
			 case 4:
			 s11 = 1;
			 s12 = 0;
			 s13 = 1;
			 s14 = 1;
			 P0 = arr[ds2-'0'];
			 c = kr11;
			 k();
			 sn =5;
			 break; 
			 
			 case 5:
			 c = kr12;
			 k();
			 sn = 6;
			 break; 
			 
			 case 6:
			 c = kr13;
			 k();
			 sn = 7;
			 break; 
			 
			 case 7:
			 P0 = 0x00;
			 c = kr14;
			 k();
			 sn = 8;
			 break;
			 
			 case 8:
			 s11 = 1;
			 s12 = 1;
			 s13 = 0;
			 s14 = 1;
			 P0 = arr[ds3-'0'];
			 c = kr11;
			 k();
			 sn =9;
			 break; 
			 
			 case 9:
			 c = kr12;
			 k();
			 sn = 10;
			 break; 
			 
			 case 10:
			 c = kr13;
			 k();
			 sn = 11;
			 break; 
			 
			 case 11:
			 P0 = 0x00;
			 c = kr14;
			 k();
			 sn = 12;
			 break;
			 
			 case 12:
			 s11 = 1;
			 s12 = 1;
			 s13 = 1;
			 s14 = 0;
			 P0 = arr[ds4-'0'];
			 c = kr11;
			 k();
			 sn = 13;
			 break; 
			 
			 case 13:
			 c = kr12;
			 k();
			 sn = 14;
			 break; 
			 
			 case 14:
			 c = kr13;
			 k();
			 sn = 15;
			 break; 
			 
			 case 15:
			 P0 = 0x00;
			 c = kr14;
			 k();
			 sn = 16;
			 break;
		 }
	 }
	 
	 void buzzer()
	 {
		 if(s_buzzer == 1)
		 {
			 sb =~ sb;
		 }
		 else
		 {
			 goto out_b;
		 }
		 out_b : z = 0;
	 }
	 
		void k()
		{
			if(key_ready == 1)
			{
				rr();
			}
			else
			{
				if(c == 0)
					{
						d_count--;
						key_code = sn;
						goto out_k;
					} 
				else
						{
							d_count--;
				
							if(d_count == 0)
								{
									if(c == 0)
										{
											key_ready= 1;
											s_buzzer = 1;
											d_count = 33;
											goto out_k;
										}
						    	else
										{
											d_count = 33;
											goto out_k;
										}
								}
							else
								{
									goto out_k;
								}
						}	
					}
			out_k: x = 0;
		}
			
		
		void rr()
		{
			if(c == 0)
			{
				k_count = 32;
				goto out_r;
			}
			else
			{
				k_count--;
			}
			if(k_count == 0)
			{
				nkp =1;
				s_buzzer = 0;
				k_count = 32;
				goto out_r;
			}
			else
			{
				out_r:
				y = 0;
			}
		}
		
		void key_release()
		{
			if(nkp == 1)
			{

				key_ready = 0;
				nkp = 0;
			}
		}