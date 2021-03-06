//
// TMR_Capture_SR04 : usi[ng Timer Capture to read Ultrasound Ranger SR-04
//
// EVB : Nu-LB-NUC140 (need to manually switch RSTCAPSEL)
// MCU : NUC140VE3CN
// Sensor: SR-04

// SR-04 connection
// Trig connected to PB8
// Echo connected to TC2/PB2 (TC0_PB15, TC1_PE5, TC2_PB2, TC3_PB3)

#include <stdio.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "stdlib.h"
#include "Seven_Segment.h"
		unsigned char car[32] = {0x80, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0x40, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x03, 0x03, 0x07, 0x0f, 0x3f, 0x7f, 0x37, 0x14, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		unsigned char stone[32] = {0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0x00, 0x00, 
0x00, 0x0e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1c};
   
		unsigned char people[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x30, 0xf0, 0xf0, 0xbc, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x40, 0x66, 0x17, 0x0f, 0x07, 0x07, 0x3f, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
		unsigned char point[32] = {0x00, 0xf0, 0xf8, 0xfc, 0xfe, 0xfe, 0x01, 0x01, 0x79, 0x79, 0x3b, 0x12, 0x86, 0xcc, 0xf8, 0xe0, 
0x00, 0x0f, 0x1f, 0x3f, 0x7f, 0x7f, 0x40, 0x40, 0x7e, 0x7e, 0x7f, 0x7f, 0x3f, 0x1f, 0x0f, 0x03};
		unsigned char car1[32] = {0x00, 0xc0, 0xc0, 0xe0, 0xf0, 0xfc, 0xfe, 0xec, 0x28, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x02, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		unsigned char snake1[32] = {0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x78, 0xf8, 0xfc, 0xfc, 0xe8, 0x78, 0x00, 0x00, 0x00, 
0x00, 0x03, 0x1f, 0x3e, 0x38, 0x70, 0x70, 0x30, 0x78, 0x7f, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00};
char Text0[16];
char Text1[16];
char Text2[16];
volatile uint8_t u8ADF;
volatile uint16_t X, Y;
volatile uint8_t  B;
int crash(int p_x,int p_y,int c_x,int c_y)
{
	//???U??
	if(c_y+12>=p_y && c_y<p_y+13 && c_x+10>p_x && c_x<p_x+11) //?i?H?F
	{
		return 1;
	}
	//???W??
	//??????
	//???k??
	
	return 0;
}
int move_up(int speed,int y)
{
		if(y<=5)
			y=47;
		else y-=speed;
	
		return y;
	//}
}
int move_down(int speed,int y)
{
	
	
		if(y>47) 
			y=0;
		else y+=speed;
		return y;



	//}
}
void showSeven(int no, int word){
	
	//7Seg PLEASE LOOK AT THIS STOP USING STRANGE METHOD
	CLK_SysTickDelay(1000);
	PC4=0;PC5=0;PC6=0;PC7=0;
	switch(no){
		case 1: PC4=1; break;
		case 2: PC5=1; break;
		case 3: PC6=1; break;
		case 4: PC7=1; break;
	}
	
	PE0=1;PE1=1;PE2=1;PE3=1;PE4=1;PE5=1;PE6=1;PE7=1;
	if(word==0 || word==1 || word==3 || word==4 || word==5 || word==6 || word==7 || word==8 || word==9 ||word=='s'||word=='u'||word=='o')
		PE0=0;
	if(word==0 || word==4 || word==5 || word==6 || word==8 || word==9 ||word=='s'||word=='u'||word=='c'||word=='e'||word=='L')
		PE2=0;
	if(word==0 || word==2 || word==3 || word==5 || word==6 || word==7 || word==8 || word==9||word=='s'||word=='c'||word=='e')
		PE3=0;
	if(word==0 || word==1 || word==2 || word==3 || word==4 || word==7 || word==8 || word==9||word=='u')
		PE4=0;
	if(word==0 || word==2 || word==3 || word==5 || word==6 || word==8||word=='s'||word=='u'||word=='c'||word=='e'||word=='o'||word=='L')
		PE5=0;
	if(word==0 || word==2 || word==6 || word==8||word=='u'||word=='c'||word=='e'||word=='o'||word=='L')
		PE6=0;
	if(word==2 || word==3 || word==4 || word==5 || word==6 || word==8 || word==9||word=='s'||word=='e'||word=='o')
		PE7=0;
	
	
	

}
void ShowLose(void){
	
	//False ?]???O
	int i,j,k,wrong[12] = {0,0,0,0,'L','o','s','e',0,0,0,0};
	
	for(i=0;i<1;i++){
		for(j=0;j<9;j++){
			for(k=0;k<100;k++){
				if(wrong[j]!=0){
					showSeven(4,wrong[j]);
				}
				if(wrong[j+1]!=0){
					showSeven(3,wrong[j+1]);
				}
				if(wrong[j+2]!=0){
					showSeven(2,wrong[j+2]);
				}
				if(wrong[j+3]!=0){
					showSeven(1,wrong[j+3]);
				}
			}
		}
	}
		CloseSevenSegment();
	
	//RGB 3 times	
	for(i=0;i<3;i++){
		CLK_SysTickDelay(100000);
		PA14 = 0;
		CLK_SysTickDelay(100000);
		PA14 = 1;
	}
}
void showSuce(void){
	int i , j ,k;
	int success[15] = {0,0,0,0,'s','u','c','c','e','s','s',0,0,0,0};
	for(i=0;i<1;i++)
	for(j=0;j<15;j++)
	for(k=0;k<100;k++)
	{
		if(success[j]!=0) 	showSeven(4,success[j]);
		if(success[j+1]!=0) showSeven(3,success[j+1]);
		if(success[j+2]!=0) showSeven(2,success[j+2]);
		if(success[j+3]!=0) showSeven(1,success[j+3]);
	}
	CloseSevenSegment();
	for(i=0;i<2;i++){
		CLK_SysTickDelay(100000);
		PA12 = 0;
		CLK_SysTickDelay(100000);
		PA12 = 1;
		PA13 = 0;
		CLK_SysTickDelay(100000);
		PA13 = 1;
		PA14 = 0;
		CLK_SysTickDelay(100000);
		PA12 = 0;
		PA14 = 0;
		CLK_SysTickDelay(100000);
		
		PA13 = 0;
		PA14 = 1;
		CLK_SysTickDelay(100000);
		PA14 = 0;
		PA12 = 1;
		CLK_SysTickDelay(100000);
		PA12 = 0;
		CLK_SysTickDelay(100000);
		
	}
	PA12 = 1;
	PA14 = 1;
	PA13 = 1;
}
void show(void)
{
	unsigned char bomb[512] = {// '0637', 64x64px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xfc, 0x08, 0x10, 0x10, 0x20, 0x20, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x20, 0x00, 0x10, 
0x08, 0x02, 0x02, 0x08, 0x10, 0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x20, 
0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x40, 0x00, 0x20, 0x10, 0x00, 0x04, 
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x80, 0x21, 0x09, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x82, 0x6c, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x40, 0x20, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x01, 0x01, 0x01, 0x01, 
0x01, 0x00, 0x04, 0x08, 0x04, 0x04, 0x04, 0x08, 0x20, 0x10, 0x08, 0x04, 0x04, 0x00, 0x00, 0x00, 
0x00, 0x04, 0x00, 0x00, 0x20, 0x60, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char bomb2[2048] = {// '0637', 128x128px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xf0, 0x60, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
0xc0, 0x60, 0x18, 0x0e, 0x06, 0x18, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x30, 0x18, 0x0e, 0x7e, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xff, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x06, 0x04, 0x04, 0x0c, 0x08, 0x08, 0x18, 0x10, 0x10, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x18, 0x08, 0x0c, 0x04, 0x02, 0x03, 0x01, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x04, 0x0c, 0x08, 0x08, 0x08, 
0x08, 0x08, 0x0c, 0x04, 0x06, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1c, 
0x10, 0x20, 0x40, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x3c, 
0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x82, 0x42, 0x22, 0x12, 0x0e, 0x06, 
0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x60, 0x60, 0xe0, 
0xe0, 0xa0, 0xb0, 0x90, 0x10, 0x10, 0x18, 0x08, 0x0c, 0x04, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x70, 0x0c, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x06, 0x04, 0x0c, 0x18, 0x70, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x38, 0x0f, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
0x60, 0x30, 0x08, 0x0c, 0x04, 0x04, 0x06, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x0c, 0x0e, 0x07, 0x06, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x02, 0x06, 0x04, 0x18, 0xf0, 0xc0, 0x60, 0x20, 0x20, 0x30, 0x30, 0x20, 0x20, 0x40, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x60, 0x20, 0x10, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
0x08, 0x18, 0x10, 0x30, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x10, 0x08, 
0x04, 0x06, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x02, 0x06, 0x0f, 
0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
0x1e, 0x0c, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x1c, 0x78, 0x7f, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};	

unsigned char bomb1[512] = {// '1', 64x64px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x08, 
0x00, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x40, 0x60, 0x20, 
0x10, 0x08, 0x02, 0x01, 0x03, 0x0c, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10, 0x08, 
0x04, 0x03, 0x07, 0x10, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x60, 0x18, 0x01, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0xc0, 0x24, 0x14, 0x0c, 0x04, 0x00, 
0x00, 0x04, 0x04, 0x04, 0x04, 0x0e, 0x0a, 0x12, 0x11, 0x21, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x58, 0x47, 0x40, 0x40, 0x40, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x00, 0x00, 
0x00, 0x40, 0x40, 0x00, 0xe0, 0x08, 0x04, 0x04, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x0e, 0x02, 0x02, 0x00, 0x02, 0x02, 0x1c, 0x30, 0x08, 0x04, 0x02, 0x00, 0x01, 0x01, 0x01, 
0x01, 0x01, 0x01, 0x02, 0x02, 0x0c, 0x10, 0x60, 0x0c, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

int i,j,k;
	clear_LCD();
for(i=0;i<3;i++)
{
	
	draw_Bmp64x64(25,0,FG_COLOR,BG_COLOR,bomb);
	printS_5x7(40,32,"B O M B");
	CLK_SysTickDelay(1000000);
	clear_LCD();
	draw_Bmp64x64(22,0,FG_COLOR,BG_COLOR,bomb1);
	//printS_5x7(50,32,"Die");
	CLK_SysTickDelay(1000000);
	clear_LCD();
}
}
void ADC_IRQHandler(void)
{
    uint32_t u32Flag;

    // Get ADC conversion finish interrupt flag
    u32Flag = ADC_GET_INT_FLAG(ADC, ADC_ADF_INT);

    if(u32Flag & ADC_ADF_INT) {
        X = ADC_GET_CONVERSION_DATA(ADC, 0);
        Y = ADC_GET_CONVERSION_DATA(ADC, 1);
    }
    ADC_CLR_INT_FLAG(ADC, u32Flag);
}

void Init_ADC(void)
{
    ADC_Open(ADC, ADC_INPUT_MODE, ADC_OPERATION_MODE, ADC_CHANNEL_MASK );
    ADC_POWER_ON(ADC);
    ADC_EnableInt(ADC, ADC_ADF_INT);
    NVIC_EnableIRQ(ADC_IRQn);
    ADC_START_CONV(ADC);	
}

int32_t main (void)
{
		uint32_t u32ADCvalue;
		int place=0;
		int flag = 0;
		uint8_t x_p,y_p;
		uint8_t x_c1,y_c1;
		uint8_t x_c2,y_c2;
		uint8_t x_c4,y_c4;
		uint8_t x_end,y_end;
		uint8_t x_s,y_s;
		uint8_t x_s1,y_s1;
		uint8_t x_stone,y_stone;
		uint8_t x_stone1,y_stone1;
		uint8_t x_stone2,y_stone2;
		uint8_t x_stone3,y_stone3;
		uint8_t x_stone4,y_stone4;
		uint8_t x_c3,y_c3;
		int num;
    SYS_Init();
    Init_ADC();
	  init_LCD();
	  clear_LCD();
	  
    u8ADF = 0;
		PD14 = 0;
    GPIO_SetMode(PB, BIT0, GPIO_MODE_INPUT); // set PC0 input for button
		//draw_Bmp16x16(55,30,FG_COLOR,BG_COLOR,car);
		//print_Line(0, "Joystick");

    while(1)
		{
			if(flag == 1){
				showSuce();
			}
			flag = 0;
			place = place%3+1;	/*?H???@?????d*//*first*/
			
			if(place == 1){		
				x_p=0,y_p=30;
				x_c1=16,y_c1=0;
				x_c2=32,y_c2=47;
				x_end=112,y_end=15;
				x_s=48,y_s=47;
				x_stone=64,y_stone=12;
				x_stone2=64,y_stone2=46;
				x_stone3=94,y_stone3=32;
				x_c3=82,y_c3=30;
			
				draw_Bmp16x16(x_p,y_p,FG_COLOR,BG_COLOR,people);
				draw_Bmp16x16(x_s,y_s,FG_COLOR,BG_COLOR,snake1);
				draw_Bmp16x16(x_c1,y_c1++,FG_COLOR,BG_COLOR,car);
				draw_Bmp16x16(x_c3,y_c3,FG_COLOR,BG_COLOR,car);
				draw_Bmp16x16(x_c2,y_c2,FG_COLOR,BG_COLOR,car1);
				draw_Bmp16x16(x_stone,y_stone,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_stone2,y_stone2,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_stone3,y_stone3,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_end,y_end,FG_COLOR,BG_COLOR,point);
				while(x_p+10<x_end||x_p>x_end+16||y_p>y_end+12||y_p+14<y_end){	//?p?G?H???S???i?J??end???I?A?N?|???򲾰?
					
					if(X>3500){					//?ޱ??H?????????A???????J?W????while??
						if((x_p>=111)||(x_p<x_stone+14&&x_p+14>=x_stone&&y_p+12>y_stone&&y_p<y_stone+11)
											||(x_p<x_stone2+14&&x_p+14>=x_stone2&&y_p+12>y_stone2&&y_p<y_stone2+11)
											||(x_p<x_stone3+14&&x_p+14>=x_stone3&&y_p+12>y_stone3&&y_p<y_stone3+11)){}
						else{
							x_p+=3;
						}
					}
					else if(X<1000){
						if(x_p<=0||(x_p<=x_stone+14&&x_p+13>=x_stone&&y_p+12>y_stone&&y_p<y_stone+11)
										||(x_p<=x_stone2+14&&x_p+13>=x_stone2&&y_p+12>y_stone2&&y_p<y_stone2+11)
										||(x_p<=x_stone3+14&&x_p+13>=x_stone3&&y_p+12>y_stone3&&y_p<y_stone3+11)){}
						else{
							x_p-=3;
						}
					}
					if(Y>3500){
						if(y_p>=48||(x_p+13>x_stone&&x_p<x_stone+14&&y_p+12>=y_stone&&y_p<y_stone+11)
											||(x_p+13>x_stone2&&x_p<x_stone2+14&&y_p+12>=y_stone2&&y_p<y_stone2+11)
											||(x_p+13>x_stone3&&x_p<x_stone3+14&&y_p+12>=y_stone3&&y_p<y_stone3+11)){}
						else
							y_p+=2;
					}
					else if(Y<1000){
						if(y_p<=0||(x_p+13>x_stone&&x_p<x_stone+14&&y_p+12>y_stone&&y_p<=y_stone+12)
											||(x_p+13>x_stone2&&x_p<x_stone2+14&&y_p+12>y_stone2&&y_p<=y_stone2+12)
											||(x_p+13>x_stone3&&x_p<x_stone3+14&&y_p+12>y_stone3&&y_p<=y_stone3+12)){}
						else
							y_p-=2;
					}
				
					clear_LCD();
					draw_Bmp16x16(x_p,y_p,FG_COLOR,BG_COLOR,people);
					draw_Bmp16x16(x_end,y_end,FG_COLOR,BG_COLOR,point);
					draw_Bmp16x16(x_stone,y_stone,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_stone2,y_stone2,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_stone3,y_stone3,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_s,y_s,FG_COLOR,BG_COLOR,snake1);
					draw_Bmp16x16(x_c1,y_c1,FG_COLOR,BG_COLOR,car);
					draw_Bmp16x16(x_c3,y_c3,FG_COLOR,BG_COLOR,car);
					draw_Bmp16x16(x_c2,y_c2,FG_COLOR,BG_COLOR,car1);
					CLK_SysTickDelay(50000);
					if(crash(x_p,y_p,x_c1,y_c1)||crash(x_p,y_p,x_c2,y_c2)||crash(x_p,y_p,x_c3,y_c3)||crash(x_p,y_p,x_s,y_s))
					{
						clear_LCD();
						show();
						ShowLose();
						flag = 2;
						break;
					}
					y_c1 = move_down(1,y_c1);
					y_c2 = move_up(1,y_c2);
					y_c3 = move_down(1,y_c3);
				  y_s = move_up(1,y_s);
					
					//CLK_SysTickDelay(100000);
				}//while2
			}
			
			
			else if(place == 2){		//?ݭn?]?p????
				
				x_p=0,y_p=31;
				x_c1=16,y_c1=16;
				x_c2=33,y_c2=47;
				x_c4=16,y_c4=30;
				x_end=112,y_end=15;
				x_s=48,y_s=47;
				x_s1=95,y_s1=0;
				x_stone=64,y_stone=17;
				x_stone1=112,y_stone1=42;
				x_stone2=64,y_stone2=47;
				x_stone3=95,y_stone3=33;
				x_c3=82,y_c3=0;
				draw_Bmp16x16(x_p,y_p,FG_COLOR,BG_COLOR,people);
				draw_Bmp16x16(x_s,y_s,FG_COLOR,BG_COLOR,snake1);
				draw_Bmp16x16(x_s1,y_s1,FG_COLOR,BG_COLOR,snake1);//????
				draw_Bmp16x16(x_c1,y_c1,FG_COLOR,BG_COLOR,car);
				draw_Bmp16x16(x_c3,y_c3,FG_COLOR,BG_COLOR,car);
				draw_Bmp16x16(x_c4,y_c4,FG_COLOR,BG_COLOR,car);
				draw_Bmp16x16(x_c2,y_c2,FG_COLOR,BG_COLOR,car1);
				draw_Bmp16x16(x_stone,y_stone,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_stone1,y_stone1,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_stone2,y_stone2,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_stone3,y_stone3,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_end,y_end,FG_COLOR,BG_COLOR,point);
				while(x_p+10<x_end||x_p>x_end+16||y_p>y_end+12||y_p+14<y_end)//?p?G?H???S???i?J??end???I?A?N?|???򲾰?
				{	
					if(X>3500){					//?ޱ??H?????????A???????J?W????while??
						if(x_p>=111||(x_p+16>x_stone&&x_p<x_stone+14&&y_p+12>y_stone&&y_p<y_stone+11)
											||(x_p+16>x_stone1&&x_p<x_stone1+14&&y_p+12>y_stone1&&y_p<y_stone1+11)
											||(x_p+16>x_stone2&&x_p<x_stone2+14&&y_p+12>y_stone2&&y_p<y_stone2+11)
											||(x_p+16>x_stone3&&x_p<x_stone3+14&&y_p+12>y_stone3&&y_p<y_stone3+11)){}
					//	if(y_end+14>=y_p&& y_end<y_p+13 && x_end+13>x_p && x_end<+10){clear_LCD();print_Line(1,"win");}
						else{
							x_p+=3;
						}
					}
					else if(X<1000){
						if(x_p<=0||(x_p+13>x_stone&&x_p<=x_stone+14&&y_p+12>y_stone&&y_p<y_stone+11)
										||(x_p+13>x_stone1&&x_p<=x_stone1+14&&y_p+12>y_stone1&&y_p<y_stone1+11)
										||(x_p+13>x_stone2&&x_p<=x_stone2+14&&y_p+12>y_stone2&&y_p<y_stone2+11)
										||(x_p+13>x_stone3&&x_p<=x_stone3+14&&y_p+12>y_stone3&&y_p<y_stone3+11)){}
						//if(x_p>=111||x_p+10<x_end||x_p>x_end+16||y_p>y_end+12||y_p+14<y_end){clear_LCD();print_Line(1,"win");}
						else{
							x_p-=3;							
					
						}
					}
					if(Y>3500){
						if(y_p>=47||(x_p+13>x_stone&&x_p<x_stone+14&&y_p+12>=y_stone&&y_p<y_stone+11)
											||(x_p+13>x_stone1&&x_p<x_stone1+14&&y_p+12>=y_stone1&&y_p<y_stone1+11)
											||(x_p+13>x_stone2&&x_p<x_stone2+14&&y_p+12>=y_stone2&&y_p<y_stone2+11)
											||(x_p+13>x_stone3&&x_p<x_stone3+14&&y_p+12>=y_stone3&&y_p<y_stone3+11)){}
						//if(x_p>=111||x_p+10<x_end||x_p>x_end+16||y_p>y_end+12||y_p+14<y_end){clear_LCD();print_Line(1,"win");}
						else
						{y_p+=2;	
						}
					}
					else if(Y<1000){
						if(y_p<=1||(x_p+13>x_stone&&x_p<x_stone+14&&y_p+12>y_stone&&y_p<=y_stone+12)
											||(x_p+13>x_stone1&&x_p<x_stone1+14&&y_p+12>y_stone1&&y_p<=y_stone1+12)
											||(x_p+13>x_stone2&&x_p<x_stone2+14&&y_p+12>y_stone2&&y_p<=y_stone2+12)
											||(x_p+13>x_stone3&&x_p<x_stone3+14&&y_p+12>y_stone3&&y_p<=y_stone3+12)){}
						//if(x_p+10<x_end||x_p>x_end+16||y_p>y_end+12||y_p+14<y_end){clear_LCD();print_Line(1,"win");}
						else
						{y_p-=2;}
					}

					clear_LCD();
					draw_Bmp16x16(x_p,y_p,FG_COLOR,BG_COLOR,people);
					draw_Bmp16x16(x_end,y_end,FG_COLOR,BG_COLOR,point);
					draw_Bmp16x16(x_stone,y_stone,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_stone1,y_stone1,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_stone2,y_stone2,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_stone3,y_stone3,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_p,y_p,FG_COLOR,BG_COLOR,people);
					draw_Bmp16x16(x_s,y_s,FG_COLOR,BG_COLOR,snake1);
					draw_Bmp16x16(x_s1,y_s1,FG_COLOR,BG_COLOR,snake1);//????
					draw_Bmp16x16(x_c1,y_c1,FG_COLOR,BG_COLOR,car);
					draw_Bmp16x16(x_c3,y_c3,FG_COLOR,BG_COLOR,car);
					draw_Bmp16x16(x_c4,y_c4,FG_COLOR,BG_COLOR,car);
					draw_Bmp16x16(x_c2,y_c2,FG_COLOR,BG_COLOR,car1);
					CLK_SysTickDelay(50000);
					if(crash(x_p,y_p,x_c1,y_c1)||crash(x_p,y_p,x_c2,y_c2)||crash(x_p,y_p,x_c3,y_c3)||crash(x_p,y_p,x_s,y_s)
						||crash(x_p,y_p,x_s1,y_s1)||crash(x_p,y_p,x_c4,y_c4))
					{
						clear_LCD();
						show();
						ShowLose();
						flag = 2;
						break;
					}
					y_c1 = move_down(1,y_c1);
					y_c4 = move_down(1,y_c4);
					y_c2 = move_up(1,y_c2);
					y_c3 = move_down(2,y_c3);
					y_s = move_up(1,y_s);
					
					/*y_c2 = move_up(3,y_c2);
					y_c3 = move_down(1,y_c3);
				  */
					//CLK_SysTickDelay(100000);
				}
			
			}
			else if(place == 3){		//?ݭn?]?p????
				//0
				x_p=0,y_p=10;
				//16+				
				x_stone=16,y_stone=0;
				x_stone2=16,y_stone2=15;
				x_stone3=16,y_stone3=45;
				//32
				x_s=32,y_s=47;
				//48
				x_c1=48,y_c1=0;
				//64
				x_stone4=64,y_stone4=28;
				//80
				x_c3=80,y_c3=47;
				//96
				x_s1=96,y_s1=47;
				//112
				x_end=112,y_end=47;
				x_c2=32,y_c2=47;

				//draw_Bmp16x16(x_p,y_p,FG_COLOR,BG_COLOR,people);
				draw_Bmp16x16(x_s,y_s,FG_COLOR,BG_COLOR,snake1);
				draw_Bmp16x16(x_s1,y_s1,FG_COLOR,BG_COLOR,snake1);
				draw_Bmp16x16(x_c1,y_c1,FG_COLOR,BG_COLOR,car);
				draw_Bmp16x16(x_c3,y_c3,FG_COLOR,BG_COLOR,car1);
				draw_Bmp16x16(x_stone,y_stone,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_stone2,y_stone2,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_stone3,y_stone3,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_stone4,y_stone4,FG_COLOR,BG_COLOR,stone);
				draw_Bmp16x16(x_end,y_end,FG_COLOR,BG_COLOR,point);
				while(x_p+10<x_end||x_p>x_end+16||y_p>y_end+12||y_p+16<y_end){	//?p?G?H???S???i?J??end???I?A?N?|???򲾰?
					if(X>3500){					//?ޱ??H?????????A???????J?W????while??
						if(x_p>=111||(x_p+15>x_stone&&x_p<x_stone+14&&y_p+12>y_stone&&y_p<y_stone+11)
											||(x_p+15>x_stone4&&x_p<x_stone4+14&&y_p+12>y_stone4&&y_p<y_stone4+11)
											||(x_p+15>x_stone2&&x_p<x_stone2+14&&y_p+12>y_stone2&&y_p<y_stone2+11)
											||(x_p+15>x_stone3&&x_p<x_stone3+14&&y_p+12>y_stone3&&y_p<y_stone3+11)){}
						else{
							x_p+=3;
						}
					}
					else if(X<1000){
						if(x_p<=0||(x_p+13>x_stone&&x_p<=x_stone+14&&y_p+12>y_stone&&y_p<y_stone+11)
										||(x_p+13>x_stone4&&x_p<=x_stone4+14&&y_p+12>y_stone4&&y_p<y_stone4+11)
										||(x_p+13>x_stone2&&x_p<=x_stone2+14&&y_p+12>y_stone2&&y_p<y_stone2+11)
										||(x_p+13>x_stone3&&x_p<=x_stone3+14&&y_p+12>y_stone3&&y_p<y_stone3+11)){}
						else{
							x_p-=3;
						}
					}
					if(Y>3500){
						if(y_p>=47||(x_p+13>x_stone&&x_p<x_stone+14&&y_p+12>=y_stone&&y_p<y_stone+11)
											||(x_p+13>x_stone4&&x_p<x_stone4+14&&y_p+12>=y_stone4&&y_p<y_stone4+11)
											||(x_p+13>x_stone2&&x_p<x_stone2+14&&y_p+12>=y_stone2&&y_p<y_stone2+11)
											||(x_p+13>x_stone3&&x_p<x_stone3+14&&y_p+13>=y_stone3&&y_p<y_stone3+11)){}
						else
						{y_p+=2;}
					}
					else if(Y<1000){
						if(y_p<=0||(x_p+13>x_stone&&x_p<x_stone+14&&y_p+12>y_stone&&y_p<=y_stone+12)
											||(x_p+13>x_stone4&&x_p<x_stone4+14&&y_p+12>y_stone4&&y_p<=y_stone4+12)
											||(x_p+13>x_stone2&&x_p<x_stone2+14&&y_p+12>y_stone2&&y_p<=y_stone2+12)
											||(x_p+13>x_stone3&&x_p<x_stone3+14&&y_p+12>y_stone3&&y_p<=y_stone3+12)){}
						else
						{y_p-=2;}
					}
					clear_LCD();
					draw_Bmp16x16(x_p,y_p,FG_COLOR,BG_COLOR,people);
					draw_Bmp16x16(x_end,y_end,FG_COLOR,BG_COLOR,point);
					draw_Bmp16x16(x_stone,y_stone,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_stone2,y_stone2,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_stone3,y_stone3,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_stone4,y_stone4,FG_COLOR,BG_COLOR,stone);
					draw_Bmp16x16(x_s,y_s,FG_COLOR,BG_COLOR,snake1);
					draw_Bmp16x16(x_s1,y_s1,FG_COLOR,BG_COLOR,snake1);
					draw_Bmp16x16(x_c1,y_c1,FG_COLOR,BG_COLOR,car);
					draw_Bmp16x16(x_c3,y_c3,FG_COLOR,BG_COLOR,car1);
					CLK_SysTickDelay(50000);
					if(crash(x_p,y_p,x_c1,y_c1)||crash(x_p,y_p,x_c2,y_c2)||crash(x_p,y_p,x_c3,y_c3)||crash(x_p,y_p,x_s,y_s))
					{
						clear_LCD();
						show();
						ShowLose();
						flag = 2;
						break;
					}
					y_c1 = move_down(1,y_c1);
					y_c3 = move_up(2,y_c3);
					y_s = move_up(2,y_s);
					y_s1 = move_up(3,y_s1);
				}
					
			}
			if(flag == 0){
				flag = 1;
			}
	    sprintf(Text0, "%d", X);
	    sprintf(Text1, "%d", Y);
			sprintf(Text2, "%d", B);

	    /*print_Line(1, Text0);
	    print_Line(2, Text1);
			print_Line(3, Text2);*/
    }
}