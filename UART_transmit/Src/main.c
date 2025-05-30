#include "stm32f4xx.h"
#include <stdint.h>

#include "uart.h"




int main(void)
{
    usart2_tx_init();
	while (1)
		{
//		USART_write(USART2, 'Y');
		printf("hello world %d .... :) \n\r",2024);
		}
return 0;
}



