#include<reg51.h>
// seven segment 
unsigned char ds1,ds2,ds3,ds4,p,q,r;
unsigned arr[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};

	void delay();
	void inc();
	void display();
		
		sbit s11 = P2^0;
		sbit s12 = P2^1;
		sbit s13 = P2^2;
		sbit s14 = P2^3;

		main()
		 {
			 		ds1 = 0x00;
			 		ds2 = 0x00;
			 		ds3 = 0x00;
			 		ds4 = 0x00;
			 while(1)
			 {
				 {
					 for(r=28;r>0;r--)
					 display();
				 }
				 inc();
			 }
		 }
		 
		 void display()
		 {
			 s11 = 0;
			 s12 = 1;
			 s13 = 1;
			 s14 = 1;
			 P0 =arr[ds1];
			 delay();
			 
			 s11 = 1;
			 s12 = 0;
			 s13 = 1;
			 s14 = 1;
			 P0 =arr[ds2];
			 delay();
			 
			 s11 = 1;
			 s12 = 1;
			 s13 = 0;
			 s14 = 1;
			 P0 =arr[ds3];
			 delay();
			 
			 s11 = 1;
			 s12 = 1;
			 s13 = 1;
			 s14 = 0;
			 P0 =arr[ds4];
			 delay();
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
		 
		 void inc()
		 {
			 ds1++;
			 if(ds1 == 0x0f+1)
			 {
				 ds1 = 0x00;
				 ds2++;
				 if(ds2 == 0x0f+1)
			 {
				 ds2 = 0x00;
				 ds3++;
				 if(ds3 == 0x0f+1)
			 {
				 ds3 = 0x00;
				 ds4++;
				 if(ds4 == 0x0f+1)
			 {
				 ds1 = ds2 = ds3 = ds4 = 0x00;
			 }
		   }
	     }		
	     }
     }
    