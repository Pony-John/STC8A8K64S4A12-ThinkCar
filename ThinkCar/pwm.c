#include <stc8.h>

void pwm_init();								//PWM CYCLE = 0x7530
void pwm0_setWide(unsigned int time_h);
void pwm1_setWide(unsigned int time_h);
void pwm2_setWide(unsigned int time_h);
void pwm_speed(float volt);
void pwm_direct(float angle);
void pwm_brake();

void pwm_init()
{
	P_SW2 |= 0x80;
    PWMCKS = 0x0f;                              //PWMʱ��Ϊϵͳʱ��/16
    PWMC = 0x7530;                              //����PWM����Ϊ7530H��PWMʱ��
	//PWMC = 0x1770;
	PWM0T1= 0x0000;                             //PWM0�ڼ���ֵΪ08caH�ط�����͵�ƽ
    PWM0T2= 0x0000;                             //PWM0�ڼ���ֵΪ0100H�ط�����ߵ�ƽ   
    PWM0CR= 0x80;								//ʹ��PWM0���
	PWM1T1= 0x08ca;                             //PWM1�ڼ���ֵΪ08caH�ط�����͵�ƽ
	//PWM1T1= 0x01c2;  
    PWM1T2= 0x0000;                             //PWM1�ڼ���ֵΪ0000H�ط������ƽ   
    PWM1CR= 0x80;								//ʹ��PWM1���
    PWM2T1= 0x08ca;                             //PWM2�ڼ���ֵΪ08caH�ط�����͵�ƽ
    PWM2T2= 0x0000;                             //PWM2�ڼ���ֵΪ0100H�ط�����ߵ�ƽ   
    PWM2CR= 0x80;                               //ʹ��PWM2���
    P_SW2 &= ~0x80;

    PWMCR |= 0x80;                               //����PWMģ��
}
void pwm0_setWide(unsigned int time_h)		//for speed control
{
	//PWMCR &= ~0x80;							//stop pwm
	P_SW2 |= 0x80;
	PWM0T1 = time_h;
	P_SW2 &= ~0x80;
	//PWMCR |= 0x80; 							//start pwm
}


void pwm1_setWide(unsigned int time_h)		//for speed control
{	
	//PWMCR &= ~0x80;							//stop pwm
	P_SW2 |= 0x80;
	PWM1T1 = time_h;
	P_SW2 &= ~0x80;
	//PWMCR |= 0x80;  						//start pwm
}

void pwm2_setWide(unsigned int time_h)		//for direct control
{
	//PWMCR &= ~0x80;							//stop pwm
	P_SW2 |= 0x80;
	PWM2T1 = time_h;
	P_SW2 &= ~0x80;
	//PWMCR |= 0x80;  						//start pwm
}
void pwm_speed(float volt)
{
	unsigned int temp;
	/*if(volt < 2)
	{
		volt = 2;
	}*/
	
	temp = (unsigned int)(volt * 0x1046);		
	pwm1_setWide(temp);						
}

void pwm_direct(float angle)
{
	int temp;
	temp = 0x08ca - (int)(angle * 16);	/*while temp = n, the car go along a straight line;
													while temp < n, the car turns left; 
													while temp > n, the car turns rignt;*/
	if(temp > 3000)
	{
		temp = 3000;
	}
	if(temp < 1500)
	{
		temp = 1500;
	}
	pwm2_setWide(temp);						
}

void pwm_brake()
{
	pwm1_setWide(0);	
}






