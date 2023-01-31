#include <stc8.h>
#include <intrins.h>
#include <math.h>

void init();
void T0_init();
extern void pwm_init();
extern void adc_init();
extern void pwm_speed(float volt);
extern void pwm_direct(float angle);
extern void pwm_brake();
extern unsigned int adc_l_read();
extern unsigned int adc_b_read();
extern unsigned int adc_r_read();
extern void road_init(unsigned int *av_max_l, unsigned int *av_max_r, unsigned int *av_flag_l, unsigned int *av_flag_r);
extern void Delay5ms();
extern void Delay50us();

/////
//extern void pwm1_setWide(unsigned int time_h);
bit flag;
unsigned int av_max_l, av_max_r, av_flag_l, av_flag_r;

void main()
{
	Delay5ms();
	flag = 1;
	T0_init();
	init();
	pwm_init();
	adc_init();
	P64 = 0;
	while (1)
	{
		while(flag)
		{
			if(P64 == 1)
			{
				Delay5ms();
				Delay5ms();
				if (P64 == 1)
				{
					P67 = 0;
					road_init(&av_max_l, &av_max_r, &av_flag_l, &av_flag_r);
					flag = 0;
					P67 = 1;
					EA = 1;
					while (P64);					
				}
			}
		}
		while(!flag);	
	}
}
/*
void main()
{
	pwm_init();
	while(1)
	{
		pwm2_setWide(1700);
		pwm2_setWide(1900);
		pwm2_setWide(2100);
		pwm2_setWide(2300);
		pwm2_setWide(2500);
		pwm2_setWide(2700);
			
	}

}

void main()
{
	pwm_init();
	while(1)
	{
		pwm1_setWide(1700);
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		pwm1_setWide(1900);
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		
		pwm1_setWide(2100);
		
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
				pwm1_setWide(2300);
		pwm1_setWide(2500);
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		pwm1_setWide(2700);
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
		Delay5ms();
				Delay5ms();
			
	}
}*/
void init()
{
	P6M0 = 0;
	P6M1 = 0;
}
void T0_init()		//10ms @ 24.000MHz
{
	AUXR &= 0x7F;	//定时器时钟12T模式
	TMOD &= 0xF0;	//设置定时器模式
	TL0 = 0xE0;		//设置定时初值
	TH0 = 0xB1;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;        //使能定时器中断
    //EA = 1;
}

void TM0_Isr() interrupt 1 
{
	float k;
	float BL, BR;
	float speed;
	BL = 100 * ((float)adc_l_read() / (float)av_max_l);
	//BL = adc_l_read();
	Delay50us();
	BR = 100 * ((float)adc_r_read() / (float)av_max_r);
	//BR = adc_r_read();
	/*if (BL < av_flag_l)
	{
		k = -32;
	}
	else if (BR < av_flag_r)
	{
		k = 32;
	}*/
	k = (BL - BR) * (fabs(BL-BR) / 32);
	/*else*/ 
	/*if (fabs(BL-BR) < 8)
	{
		k = 0;
	}
	else if ((fabs(BL - BR) > 8) && (fabs(BL - BR) < 16))
	{
		k = 0.2 * (BL-BR);
	}
	else if ((fabs(BL - BR) > 16) && (fabs(BL - BR) < 32))
	{
		k = 0.7 * (BL - BR);
	}
	else if (fabs(BL - BR) > 32)
	{
		k = (BL - BR); 
	}*/
	
	speed = 1.5;
	pwm_speed(speed);
	pwm_direct(k);
	//speed = 2.5 - fabs(k) / 20;
	pwm_speed(speed);
}

