#include <stc8.h>
#include <intrins.h>

unsigned int temp_buf;
//
void Init();
void delay();	//5ms
void delay1(unsigned char i);
void adc_init();
unsigned int adc_l_read();
unsigned int adc_b_read();
unsigned int adc_r_read();

void adc_init()
{
	P1M0 = 0x00;
	P1M1 = 0x07;
	ADC_CONTR = 0x80;	//start adc_power
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	ADCCFG = 0x20;		//set adc_speed and shijugeshi
}

unsigned int adc_l_read()
{
	ADC_CONTR = 0x82;	//set adc_channel
	ADC_CONTR |= 0x40;	//start adc
	while(!(ADC_CONTR & 0x20));	//wait adc finish
	ADC_CONTR &= ~0x20;		//clear adc_flag
	temp_buf = (ADC_RES << 8) + ADC_RESL;
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	return temp_buf;
}

unsigned int adc_b_read()
{
	ADC_CONTR = 0x81;	//set adc_channel
	ADC_CONTR |= 0x40;	//start adc
	while(!(ADC_CONTR & 0x20));	//wait adc finish
	ADC_CONTR &= ~0x20;		//clear adc_flag
	temp_buf = (ADC_RES << 8) + ADC_RESL;
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	return temp_buf;
}

unsigned int adc_r_read()
{
	ADC_CONTR = 0x80;	//set adc_channel
	ADC_CONTR |= 0x40;	//start adc
	while(!(ADC_CONTR & 0x20));	//wait adc finish
	ADC_CONTR &= ~0x20;		//clear adc_flag
	temp_buf = (ADC_RES << 8) + ADC_RESL;
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	return temp_buf;
}