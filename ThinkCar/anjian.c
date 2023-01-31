#include<stc8.h>
#include<intrins.h>

void Delay10ms();
void keyscan();


void keyscan()
{
	if(P64==0)
	{
		Delay10ms();
		if(P64==0)
		{
			//Ð´´úÂë
			while(!P64);
			
		}
	}
}	

void Delay10ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 234;
	k = 113;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}