
#include <stdint.h>
#define PERIPH_base (0x40000000UL) //Addresse
#define AHB1_PERIPH_OFFSET (0x00020000UL)
#define AHB1_PERIPH_BASE (PERIPH_base + AHB1_PERIPH_OFFSET)//Addresse

#define GPIOA_OFFSET (0x0000UL)
#define GPIOA_BASE (AHB1_PERIPH_BASE+ GPIOA_OFFSET)//Addresse

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1_PERIPH_BASE+ RCC_OFFSET)//Addresse

/* #define AHB1_EN_R_OFFSET (0x30UL) */
/* #define RCC_AHB1_EN_R (*(volatile unsigned int*) (RCC_BASE+AHB1_EN_R_OFFSET))//register */

/* #define GPIOA_MODER_OFFSET (0x0000UL ) */
/* #define GPIOA_MODER_R (*(volatile unsigned int*) (GPIOA_BASE+GPIOA_MODER_OFFSET))//register */

/* #define GPIOA_ODR_OFFSET (0x14UL) */
/* #define GPIOA_ODR_R (*(volatile unsigned int*) (GPIOA_BASE + GPIOA_ODR_OFFSET))//Addresse */

#define GPIOA_en (1U<<0)//enable the clock source (set 1 at pos 0)

#define PIN5 (1U<<5)
#define LED_pin PIN5

// struct of offset's RCC 
typedef struct {
// see RCC register map
	uint32_t DUMMY[12];// offset 0x00 -> 0x2c
	volatile uint32_t RCC_AHB1ENR;
	//....
}RCC_typedef;

// struct of offsets GPIO 
typedef struct {
	volatile uint32_t MODER; // offset 0x00
//	volatile uint32_t OTYPER;
//	volatile uint32_t MODEROSPEEDR;
//	volatile uint32_t PUPDR;
//	volatile uint32_t IDR;
	uint32_t DUMMY [4]; //offset 0x04 *4 -> 0x10
	volatile uint32_t ODR;//offset 0x14
//	volatile uint32_t BSRR;
//	volatile uint32_t LCKR;
//	volatile uint32_t ALFR[2];
}GPIO_typedef;

// cast the RCC_base pointer to the struct RCC_typedef  
#define RCC ((RCC_typedef *) RCC_BASE)
// cast the GPIOA_base pointer to the struct GPIO_typedef  
#define GPIOA ((GPIO_typedef *)GPIOA_BASE)

int main ()
{
	//  enable clock
	RCC->RCC_AHB1ENR |= GPIOA_en ;
GPIOA->MODER |= (1U<< 10);
GPIOA->MODER &= ~(1U<< 11);

while (1)
	{
    // toggle LED 
	GPIOA->ODR^= LED_pin;
		for (int i=0;i<100000;i++)
		{}
	}

	return 0;
}
