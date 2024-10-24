#include<reg51.h>
	 
	 void Tx();
	 void Rx();
	 
	 void init_UART()
	 {
		 SCON = 0x52;
		 TMOD = 0x20;
		 TH1 = 0xFD;
		 TR1 = 1;
	 }
	 
	 main()
	 {
		 P0 = 0x00;
		 init_UART();
		 ACC = 'M';
		 while(1)
		 {
			 Tx();
			 Rx();
		 }
	 }
	 
	 void Tx()
	 {
		 while(!TI)
			 SBUF = ACC;
		   TI = 1;
	 }
		 
	 void Rx()
	 {
		 while(!RI)
			 ACC = SBUF;
		   P0 = ACC;
		   RI = 0;
	 }