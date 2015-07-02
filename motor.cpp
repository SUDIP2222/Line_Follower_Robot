#include "sfr_r834c.h"
#define PERIOD 40000
enum {STOP,FORWARD,BACKWARD};
long maxValue;
extern unsigned short  ad_data[4];
void Motor(int dir, int left, int right);
void RightTurn(int left, int right);
void LeftTurn(int left, int right);
void motor_control();
bool  runFlag;

void InitMotor(int rate)
{
	maxValue=((long)PERIOD*rate)/100;
	trdgra0=trdgrc0=PERIOD-1;
	trdgrb0=trdgrd0=maxValue/2;
	trdgra1=trdgrc1=maxValue/2;
	
	trdstr=0x05;
     runFlag=false;
}

void motor_control()
{
 

 if ( runFlag == false ){
    if ( p2_0 == 0 ){
       Motor(FORWARD, 55, 55);
        runFlag = true ;
    }
}
 else if ( p2_0 == 0 ){
        Motor(STOP,0,0);
        runFlag = false ;
    }
   else if ( ad_data[1]<ad_data[2]-50 ){
        //  Speed down ;
         RightTurn(20, 10);
        }
        else if ( ad_data[1]>ad_data[2]+50 ){
           // Speed down ;
         LeftTurn(10, 20);
        }
	/*	else if  (ad_data[0]!=0x01FF &  ad_data[1]!=0x01FF & ad_data[2]!=0x01FF & ad_data[3]!=0x01FF){
					
				 Motor(FORWARD, 0, 0);
				 } */
        else {
            // Speed Up;            
			 Motor(FORWARD, 55,55);
        }
    }


	



void Motor(int dir, int left, int right)
{
	if(dir==STOP) //STOP
	{
		p2_1=0;
		p2_6=0;
		p2_3=0;
		p2_7=0;
	}
	else
	{
		trdgrd0=(maxValue*left)/100;
		trdgrc1=(maxValue*right)/100;
		if(dir==FORWARD)
		{
			p2_1=0;
			p2_6=1;
			p2_3=0;
			p2_7=1;
		}
		else
		{
			p2_1=1;
			p2_6=0;
			p2_3=1;
			p2_7=0;
		}
	}
}

void RightTurn(int left, int right){
	
	trdgrd0=(maxValue*left)/100;
	trdgrc1=(maxValue*right)/100;
			p2_1=0;
			p2_6=1;
			p2_3=1;
			p2_7=0;
	
}

void LeftTurn(int left, int right)
{
	trdgrd0=(maxValue*left)/100;
	trdgrc1=(maxValue*right)/100;
			p2_1=1;
			p2_6=0;
			p2_3=0;
			p2_7=1;	
	}