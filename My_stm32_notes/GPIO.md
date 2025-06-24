# Interrupt GPIO: EXTI
create an Interrupt by pushing a button connected to PC13

disable global interrupt (good practise) 
enable clock access for GPIO 
configure PIN13 as Input 
EXTI is part of SYSCFG , enable clock acces to SYSCFG (APB2)
select protc for EXTI13 ( SYSCFG_EXTIx) x from 0 to 15 
unmask EXTI13: uncover, EXTI_IMR   
select falling edge trigger for (interrupt) EXTI_FSTR 
enable EXTI13 line in NVIC : NVIC_EnableIRQ(EXTI15_10_IRQn);

enable global interrupt
implement ISR function, the name of the ISR function should be identical with that defined in NVIC table adress, ( take a look under the start up file to find it) 


Note: 
EXTI15_10_IRQn number is defined in the STM32f401xe
