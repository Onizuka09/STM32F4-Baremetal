

//led port
//led pin
#define PERIPH_base (0x40000000UL) //Addresse
#define AHB1_PERIPH_OFFSET (0x00020000UL)
#define AHB1_PERIPH_BASE (PERIPH_base + AHB1_PERIPH_OFFSET)//Addresse

#define GPIOA_OFFSET (0x0000UL)
#define GPIOA_BASE (AHB1_PERIPH_BASE+ GPIOA_OFFSET)//Addresse

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1_PERIPH_BASE+ RCC_OFFSET)//Addresse

#define AHB1_EN_R_OFFSET (0x30UL)
#define RCC_AHB1_EN_R (*(volatile unsigned int*) (RCC_BASE+AHB1_EN_R_OFFSET))//register

#define GPIOA_MODER_OFFSET (0x0000UL )
#define GPIOA_MODER_R (*(volatile unsigned int*) (GPIOA_BASE+GPIOA_MODER_OFFSET))//register

#define GPIOA_ODR_OFFSET (0x14UL)
#define GPIOA_ODR_R (*(volatile unsigned int*) (GPIOA_BASE + GPIOA_ODR_OFFSET))//Addresse

#define GPIOA_en (1U<<0)//enable the clock source (set 1 at pos 0)
#define PIN5 (1U<<5)
#define LED_pin PIN5
int main ()
{
	//  enable clock
	RCC_AHB1_EN_R |= GPIOA_en ;
	//set pin5 to output mode
	GPIOA_MODER_R |= (1U<< 10);
	GPIOA_MODER_R &= ~(1U<< 11);

	while (1)
	{
	//Set pin 	1
//		GPIOA_ODR_R |= LED_pin;
		// toggle pin
		GPIOA_ODR_R ^= LED_pin;
		for (int i=0;i<100000;i++)
		{}
	}

	return 0;
}
