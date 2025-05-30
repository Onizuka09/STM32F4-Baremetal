#include "stm32f4xx.h"
#include <stdint.h>

#include "uart.h"


	char buff[40]= "hello world 2024 from stm32 DMA !!\n\r";


int main(void)
{
	RCC->AHB1ENR |=(1U<<0);

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
    usart2_tx_init();
    dma1_stream6_ini((uint32_t)buff,(uint32_t)&USART2->DR,40);
	while (1)
		{
//		USART_write(USART2, 'Y');

		}
return 0;
}



void DMA1_Stream6_IRQHandler (void)
{
	// check if transfer complete did happen in the interrupt status regiser
	if ( (DMA1->HISR & (1U<<21) )!=0)
	{
		GPIOA->ODR |=(1U<<5);

		// clear interrupt flag
		DMA1->HIFCR |= (1U<<21);
	}

}
