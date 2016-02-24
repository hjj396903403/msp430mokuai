
#include<msp430x14x.h>
typedef unsigned char uchar;
typedef unsigned int  uint;
unsigned char keypressed,keyflag,keyvalue;

void delay(uint a)
{
  uchar j;
  for(;a>0;a--)
    for(j=120;j>0;j--);
}
void initkey()
{
  P1DIR=0XF0;
  P1OUT |=0XF0;
  keyflag=0;
  keypressed=0;
  keyvalue=0;
}
void keyscan(void)
{
  uchar temp1,temp2,i,j;
  temp1=0x80;
  for(i=0;i<4;i++)          //判断行
  {
    P1OUT=0xf0;
    P1OUT-=temp1;
    temp1>>=1;
    if((P1IN & 0X0F)< 0X0F)
    {
      temp2=0x01;
      for(j=3;j>=0;j--)            //判断列
      {
        if((P1IN & temp2)==0x00)   
        {
          keyvalue=i*4+j;
          return;             //退出循环
        }
        temp2<<=1;
      }
    }
  }
  
}

void keyevent()
{
  uchar temp;
  P1OUT &= 0X00;
  temp=P1IN;
  if((keypressed==0)&&((temp & 0x0f)<0x0f))
  {
    keypressed=1;
    delay(10);
    keyscan();
  }
  else if((keypressed==1)&&((temp & 0x0f)==0x0f))
  {
     keypressed=0;
     keyflag=1;
  }
  else
  {
    _NOP();
  }
}          