#include "delay.h"

u32 fac_us;

void delay_init(void)
{
	SysTick->CTRL=0x00;
	SYS_UnlockReg();
	CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLKSEL_HXT);	//systickʱ��ԴΪHXT
	SYS_LockReg();
	fac_us=12;			//HXT=12MHz	����12��=1us
}


void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD=nus*fac_us;
	SysTick->VAL=0x00;        								//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;		//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));			//�ȴ�ʱ�䵽�� 
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      									//��ռ�����	
}

void delay_ms(u32 nms)											//���0xFFFFFF/1000/12=1398.10125ms
{
	u32 temp;
	SysTick->LOAD=nms*fac_us*1000;
	SysTick->VAL=0x00;        								//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;		//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));			//�ȴ�ʱ�䵽�� 
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      									//��ռ�����	
}

