#include "delay.h"

u32 fac_us;

void delay_init(void)
{
	SysTick->CTRL=0x00;
	SYS_UnlockReg();
	CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLKSEL_HXT);	//systick时钟源为HXT
	SYS_LockReg();
	fac_us=12;			//HXT=12MHz	计数12次=1us
}


void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD=nus*fac_us;
	SysTick->VAL=0x00;        								//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;		//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));			//等待时间到达 
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      									//清空计数器	
}

void delay_ms(u32 nms)											//最大0xFFFFFF/1000/12=1398.10125ms
{
	u32 temp;
	SysTick->LOAD=nms*fac_us*1000;
	SysTick->VAL=0x00;        								//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;		//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));			//等待时间到达 
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      									//清空计数器	
}

