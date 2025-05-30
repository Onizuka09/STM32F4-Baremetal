//#define STM32F401xE
#include "ADC.h"
#define GPIO_pin_A1 1
#define GPIO_pin_A3 3
#define GPIO_pin_A5 5

volatile  uint32_t data;
int main(void)
{
	init_ADC_it();

	Start_conversion();
	while (1)
		{


		}
return 0;
}
void ADC_IRQHandler()
{
	// check if the conversion is completed
if  ((ADC1->SR & SR_EOC)!=0){
	//clear EOC flag
	ADC1->SR &=~ SR_EOC ;
	data = Read_ADC1();

}
}
