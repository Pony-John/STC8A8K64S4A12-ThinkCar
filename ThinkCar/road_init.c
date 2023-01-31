#include <stc8.h>
#include <intrins.h>

void Delay5ms();
void Delay50us();
extern unsigned int adc_l_read();
extern unsigned int adc_b_read();
extern unsigned int adc_r_read();

void road_init(unsigned int *av_max_l, unsigned int *av_max_r, unsigned int *av_flag_l, unsigned int *av_flag_r)
{
	unsigned int temp_l, temp_r, i;
	unsigned int max_l, max_r, flag_l, flag_r;
	
	max_l = 0;
	max_r = 0;
	flag_l = 0;
	flag_r = 0;
	
	*av_max_l = 0;
	*av_max_r = 0;
	*av_flag_l = 0;
	*av_flag_r = 0;
		
	for (i = 1; i <= 1000; i++)
	{
		temp_l = adc_l_read();
		Delay50us();
		temp_r = adc_r_read();
		if (temp_l > max_l)
		{ 
			max_l = temp_l;
			flag_r = temp_r;
		}
		if (temp_r > max_r)
		{
			max_r = temp_r;
			flag_l = temp_l;
		}
		Delay5ms();
	}

	*av_max_l = max_l;
	*av_max_r = max_r;
	*av_flag_l = flag_l;
	*av_flag_r = flag_r;

	
	*av_flag_l = (int)(100 * (float)(*av_flag_l) / (float)(*av_max_l));
	*av_flag_r = (int)(100 * (float)(*av_flag_r) / (float)(*av_max_r));
}

void Delay5ms()		//@24.000MHz —” ±5ms
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 156;
	j = 213;   
	do
	{
		while (--j);
	} while (--i);
}

void Delay50us()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 140;
	do
	{
		while (--j);
	} while (--i);
}

