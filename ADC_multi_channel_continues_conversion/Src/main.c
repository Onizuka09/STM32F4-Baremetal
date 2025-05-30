#include "ADC.h"
#define GPIO_pin_A1 1
#define GPIO_pin_A3 3
#define GPIO_pin_A5 5

uint32_t data,data2,data3 ;
int main(void)
{
	init_GPIO(GPIO_pin_A1);
	init_GPIO(GPIO_pin_A3);
	init_GPIO(GPIO_pin_A5);
	init_ADC();
	Start_conversion();
	while (1)
		{
		data = Read_ADC1();
		data2 = Read_ADC1();
		data3 = Read_ADC1();

		}
return 0;
}

