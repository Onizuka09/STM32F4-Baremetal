## Interrupt: 
it's a signal that interrupts the CPU excution of the main function, to excuted another function need by the module who interrupted the CPU 
The function that gets excuted when an interrupts occurs is called:
Interrupt Service Routine (ISR) or Interrupt Handler. 
## Polling: 
the CPU continiously monitors the statuts of a given module ( register) when a particular statuts condition is met the CPU the services the module.
This mode block other modules from excuting until the condition of the status module is met. 

| Interrupts                   | Polling            |
+==============================|====================+
| main ()  {                   | main(){            |
| while (1){                   | while(1){          |
| // executing other functions | if (switch == ON){ |
| }}                           | getData()}         |
| OnSwitch_ISR{                | }                  |
| get_data()}                  | }                  |
+------------------------------|--------------------+
## NVIC: Nested vector Interrupt Controller : 
A dedicated hardware inside the Cortex-Microcontroller
It is responsible for handling interrupts 
the NVIC handles interrupts coming from 
- CPU 
- SysTicks 
- CSS: clock security system 
- peripherals (UART,SPI, I2C, ...) 
- EXTI: External interrupts from GPIOs 
Note: 
* Interrupts from CPU are called Exceptions 
* Interrupts from outside CPU are called Hardware Exceptions or Interrupts Requests
* the interrupt vector table conrtains the addresses of the Interrupt Handler and Exceptions Handler.
## EXTI 
GPIO pins are connected to EXTI lines 
it is possible to enable interrupt for any GPIO pin 
Multiple pins share the same EXTI line 
Pinx of every Port is connected to EXTIx_IRQ 

Example: Pin0 of every Port is connected to EXTI0_IRQ

Each EXTx (multiplexer) is connetced to the NVCI EXTIx_IRQ

Note 
* this means we cannot have both PB0 and PA0 as input interrupt pins at the same time since they are connected to the same multiplexer EXTI0 
* Pins from 10 to 15 shares the same EXTI_IRQ (EXTI15_10_IRQ), the both have theire onw mutiplexer (EXTI10 ... EXTI15) 
## Interrupts state: 
Disabled: default state 
Enabled: Interrupt is enabled 
Pending: waiting to be serviced 
Active: Being serviced 

Note: 
- Pending interrupt means that there is an interrupt with higher interrupt is being serviced 
## Priority and Interrupts (M4/M3/M7) 
- Each interrupt is set to a priority  
- The interrupt with the highest priority gets executed first 
- An interrupt the higher priority can interrupt an interrupt with low priority 
- low number priority High priority 
- the vector table describes the priority of the ISR functions 
EXAMPLE: 
Exceptions: 
RESET : -3 , fixed 
NMI ( Non maskable interrupt, clock security system): -2, fixedHard fault : -1 fixed 
caanot change the priority 
others:
EXTI
DAM 
RCC 
we can change the priori: setable 

Priority of each interrupts is defined using one of the Interrupt Priority regsiters (IPR) 
Each Interrupt request (IRQ) uses 8_bit inside a single IPR register which means there is 255 priority level. 
One PIR register allows us to configure the priority of 4 diffrent interrupts Requests 
IPR0: holds the priority of IRQ0 to IRQ3
there are 60 IPR's IRP0 to IPR59
there are 60* 4 = 240 interrups Requests (IRQ)  
the stm32 use only the 4 uppper bits to configure the priority of each IRQ, which means there is 16 priority levels 
the 16 prioriy levels: 
highest priority: 0x00 = 0
lowest priority: 0xF0 = 16

* ro find the IPR number:
deved the IRQ number by 4, the reminder will determine which byyte it is in the IPR register 
* because only the highest 4 bits are used fro priority, the priority number needs to be mutplied by 16 or left shift ' bits 

* to simplify the calculation, the NVIC_IPRx are defined as an array of 8 bit registers IP[x] in the core_cm4.h 
Such that the priority of IRQx is controoled by IP[x]
Example: setting Timer2 interrupt priority to 3, Timer2 is IRQ28:
(the IRQ number is placed in the stm32f4xxe.h)
NVIC->IP[28]= 3 <<4 or NVIC_SetPriority(TIM2_IRQn,3) 

