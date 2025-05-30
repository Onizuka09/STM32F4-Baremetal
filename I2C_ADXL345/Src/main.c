//#define STM32F401xE


#include <stdint.h>
#include"ADXL345.h"
#define GPIOA_en (1U<<0)//enable the clock source (set 1 at pos 0)

#define PIN5 (1U<<5)
#define LED_pin PIN5
#define FOUR_G_SCALE_FACTOR  0.0078;


double xg,yg,zg;
int16_t x,y,z;
extern char data;
extern uint8_t data_rec[6];

int main(void)
{
	RCC->AHB1ENR |=GPIOA_en ;
	GPIOA->MODER |= (1U<< 10);
	GPIOA->MODER &= ~(1U<< 11);
	ADXL_init();


	while (1)
	{
		ADXL_Read_values(DATA_START_ADDR);
		x= ((data_rec[1]<<8) | data_rec[0]);
		y=((data_rec[3]<<8) | data_rec[2]);
		z= ((data_rec[5]<<8) | data_rec[4]);
		xg= (x*0.0078);
		yg= (y*0.0078);
		zg = (z*0.0078);
		//Set pin 	1
	//		GPIOA_ODR_R |= LED_pin;
			// toggle pin
	//		GPIOA_ODR_R ^= LED_pin;
//		GPIOA->ODR^= LED_pin;


		}
return 0;
}
