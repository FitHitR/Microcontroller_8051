//keypad interfacing start freez reset

#include<reg51.h>
sbit sl1=P2^0;
sbit sl2=P2^1;
sbit sl3=P2^2;
sbit sl4=P2^3;
sbit krl1=P2^4;
sbit krl2=P2^5;
sbit krl3=P2^6;
sbit krl4=P3^7;
sbit sb=P1^5;
bit key_ready;
bit nkp;                 //no key press
bit tb;
bit start_sw;
bit sl_over;
bit s_buzzer;
bit c;                    //count
unsigned char ds1,ds2,ds3,ds4,y,r,n,b,key_code,z;
unsigned char dcount,krcount,x,sn,cnt_1sl,cnt_1sh,k1,m;

unsigned char arr[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};


unsigned char ascii[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

	void init_delay();
	void delay1s();
	void init();
	void init_keypad();
	void init_timer0();
	void scanner();
	void k();
	void rr();
	void inc();
	void disp_sw();
	void keyprocess();
	void process_a();
	void process_b();
	void process_c();
	void get_key();
	void init_delay1s();
	void key_release();
	void buzzer();
	
		void main()
			{
				init();
				EA=1;
				disp_sw();
				
				while(1)
					{
						get_key();
						keyprocess();
					}
			}
		
			void init()
				{
					init_keypad();
					init_timer0();
					init_delay();
				}

				void init_keypad()
					{
						krl1=1;
						krl2=1;
						krl3=1;
						krl4=1;
						sn=0;
						dcount=33;
						krcount=32;
						key_ready=0;
						nkp=0;
						s_buzzer=0;
					}

		void init_timer0()
			{
				TMOD=0x01;
				TL0=0x66;
				TH0=0xfc;
				TR0=1;
				ET0=1;
			}
	
		void isr_t0() interrupt 1 using 0
			{
				init_timer0();
				delay1s();
				buzzer();
				scanner();
				while(sl_over==0)
					{
						goto out_isr;	 
					}		 
					inc();
					sl_over=0;
					out_isr:
					m=0; 
			}
	
		void init_delay1s()
			{
				cnt_1sl=0xe8;
				cnt_1sh=0x04;
				sl_over=1;
			}

		void delay1s()
			{
				if(sl_over==1)
					{
						goto out_ds1sec;	 
					}
					cnt_1sl--;			
					if(cnt_1sh!=0)
						{
							cnt_1sl=0xff;
						}
						cnt_1sh--;
						if(cnt_1sh!=0)
							{
								cnt_1sl=0xff;
							}
							cnt_1sh=0x04;
							cnt_1sl=0xe8;
							sl_over=1;							
							out_ds1sec:
							k1=0;
			}
	
	
	void scanner()
	{
	 ACC=sn;
		switch(ACC)
			{
			case 0:
			sl1=0;
		  sl2=1;
		  sl3=1;
		  sl4=1;
		  P0=arr[ds1-'0'];
		  c=krl1;
		  k();
		  sn=1;
		  break;
		
			case 1:
			c=krl2;
		  k();
		  sn=2;
		  break;
		
			case 2:
			c=krl3;
		  k();
		  sn=3;
		  break;
		
			case 3:
		  c=krl4;
		  k();
		  P0=0x00;
		  sn=4;
		  break;
		
		case 4:
		  sl1=1;
		  sl2=0;
		  sl3=1;
		  sl4=1;
		  P0=arr[ds2-'0'];
		  c=krl1;
		  k();
		  sn=5;
		  break;
		
		case 5:
			c=krl2;
		  k();
		  sn=6;
		  break;
		
		case 6:
			c=krl3;
		  k();
		  sn=7;
		  break;
		
		case 7:
			c=krl4;
		  k();
		  P0=0x00;
		  sn=8;
		  break;
		
		case 8:
			sl1=1;
		  sl2=1;
		  sl3=0;
		  sl4=1;
		  P0=arr[ds3-'0'];
		  c=krl1;
		  k();
		  sn=9;
		  break;
		
		case 9:
			c=krl2;
		  k();
		  sn=10;
		  break;
		
		case 10:
			c=krl3;
		  k();
		  sn=11;
		  break;
	
		case 11:
			P0=0x00;
		  c=krl4;
		  k();
		  sn=12;
		  break;
		
		case 12:
			sl1=1;
		  sl2=1;
		  sl3=1;
		  sl4=0;
		  P0=arr[ds4-'0'];
		  c=krl1;
		  k();
		  sn=13;
		  break;
		
		case 13:
			c=krl2;
		  k();
		  sn=14;
		  break;
		
		case 14:
			c=krl3;
		  k();
		  sn=15;
		  break;
		
		case 15:
			P0=0x00;
		  c=krl4;
		  k();
		  sn=0;
		  break;	
			}
	}
	
	void k()
	{
	  if(key_ready==1)
	    {
	       rr();
	    }
			else
	    {	
				if(dcount==33)
	        {
						if(c==0)
							{
								dcount--;
								key_code=sn;
								goto out_k;
							}
					}
					else
						{
							dcount--;
							if(dcount==0)
								{
									if(c==0)
										{
											key_ready=1;
											s_buzzer=1;
											dcount=33;
											goto out_k;
										}
										else
											{
												dcount=33;
												goto out_k;
											}
								}
								else
									{
										goto out_k;
									}
						}
			}
			out_k:
			x=0;
	}
	void rr()
		{
			if(c==0)
				{
					krcount=32;
					goto out_r;
				}
				else
					{
						krcount--;
						if(krcount==0)
							{
								nkp=1;
								s_buzzer=0;
								krcount=32;
								goto out_r;		
							}
							else
								{
									goto out_r;
								}
					}
					out_r:
					y=0;
		}
	
		void inc()
			{
				while(start_sw==0)		
					{
						goto out_id;
					}
					ds1++;
					if(ds1==0x09+'0'+1)
						{
							ds1=0x00+'0';
							ds2++;
							
							if(ds2==0x09+'0'+1)
								{
									ds2=0x00+'0'+1;
									ds3++;

									if(ds3==0x09+'0'+1)			
										{
											ds3=0x00+'0';
											ds4++;

											if(ds4==0x09+'0'+1)
												{
													ds1=ds2=ds3=ds4='0';
												}
										}
								}
						}
						out_id:
						n=0;
			}


			void key_release()
				{
					while(nkp==1)
						{
							key_ready=0;
							nkp=0;
						}
				}


			void gate_key()
				{
					while(key_ready==0)
						{
						}
						ACC=key_code;
						key_code=ascii[ACC];
				}
	

				void keyprocess()
					{

						ACC=key_code;
						switch(ACC)
						{
								case '5':
								process_a();
  							key_release();
	  						break;
	
								case '6':
							  process_b();
							  key_release();
							  break;
							
								case '7':
								process_c();
							  key_release();
	
								default:
								key_release();
						}
					}
					

					void process_a()
						{
							ds1='0';
							ds2='0';
  						ds3='0';
						  ds4='0';
						  start_sw=0;
					  }


					void process_b()
					{
						start_sw=0;
					}
					
					
					void process_c()
						{
							start_sw=0;
							ds1='0';
							ds2='0';
							ds3='0';
							ds4='0';
						}
						
						void disp_sw()
							{
								ds1=arr[0];
								ds2=arr[0];
								ds3=arr[0];
								ds4=arr[0];
							}

							void buzzer()

							{
								if(s_buzzer==1)
									{
										sb=~sb;
									}		
									else
										{
											goto out_b;
										}
									 out_b:
										z=0;
									}
							
							
							