#include <msp430.h>

typedef unsigned int  uint;
/********************************************
�������ƣ�Init_ADC
��    �ܣ���ʼ��ADC
��    ������
����ֵ  ����
********************************************/
void Init_ADC(void)
{
    P6SEL |= 0x01;                            // ʹ��ADCͨ��
    ADC12CTL0 = ADC12ON+SHT0_15+MSC;          // ��ADC�����ò���ʱ��
    ADC12CTL1 = SHP+CONSEQ_2;                 // ʹ�ò�����ʱ��
    ADC12IE = 0x01;                           // ʹ��ADC�ж�
    ADC12CTL0 |= ENC;                         // ʹ��ת��
    ADC12CTL0 |= ADC12SC;                     // ��ʼת��
}
/********************************************
�������ƣ�Hex2Dec
��    �ܣ���16����ADCת�����ݱ任��ʮ����
          ��ʾ��ʽ
��    ����Hex_Val--16��������  
          ptr--ָ����ת�������ָ��
����ֵ  ����
********************************************/
void Hex2Dec(uint Hex_val,uchar *ptr)
{
    uchar k;
    ptr[0] = Hex_val / 1000;        
    ptr[1] = (Hex_val - ptr[0]*1000)/100;
    ptr[2] = (Hex_val - ptr[0]*1000 - ptr[1]*100)/10;
    ptr[3] = (Hex_val - ptr[0]*1000 - ptr[1]*100 - ptr[2]*10);
    for(k=0;k<4;k++)
    {
      Disp1Char(11+k,1,ptr[k]+48);
    }
}   
/*******************************************
�������ƣ�Trans_val
��    �ܣ���16����ADCת�����ݱ任����λ10����
          ��ʵ��ģ���ѹ���ݣ�����Һ������ʾ
��    ����Hex_Val--16��������   
����ֵ  ����
********************************************/
void Trans_val(uint Hex_Val,uchar *ptr)
{
    unsigned long caltmp;
    uint Curr_Volt;
	uchar k;
   
    
    caltmp = Hex_Val;
    caltmp = (caltmp << 5) + Hex_Val;           //caltmp = Hex_Val * 33
    caltmp = (caltmp << 3) + (caltmp << 1);     //caltmp = caltmp * 10
    Curr_Volt = caltmp >> 12;                   //Curr_Volt = caltmp / 2^n
    ptr[0] = Curr_Volt / 100;                   //Hex->Dec�任
    ptr[1]=-2;
    ptr[2] = Curr_Volt%100 / 10;
    ptr[3] = Curr_Volt%10;
    for(k=0;k<4;k++)
    {
      Disp1Char(1+k,1,ptr[k]+48);
    }
}
