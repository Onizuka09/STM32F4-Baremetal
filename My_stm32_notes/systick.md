# Systick:
* its a peripheral that is found in all ARM Cortex-Microcontrollers;
* Used for taking actions periodically 
example:
- used as a time base for real time operating systems
- computing delays         
* the Systick is a 24-bits down counter diven by the processor clock.  
Counts initial value down to zero 
24-bits imply maximum value: 2^24 = 0xFFFFFF = 16,777,216
## Systick registers
* STCVR: Systick Current Value Register 
this register contains the current count value 
* STCSR: Systick Control and Status Register
this register allows us to configure the Systick clock source, 
enable/disable interrupts and enable/disable the Systick counter. 
* STRVR: Systick Reload Value Register
This is where the initial count value is placed 
## Computing delays 
by loading the amount of delay X-1 to the STRVR

SYSCLK = 16Mhz -> 1 second -> 16Mhz = 16 Million cycles 

How many seconds to execute 1 cycle ? 

1/16Mhz = 62,5 nano-seconds 
N: number of cycles 

delay achieved = N * 1/ SYSCLK

N = delay achieved * SYSCLK 

then load N-1 to STRVR 

## Programming the Systick (delay function in ms) 
Since the Systick is a peripheral developed by ARM, the registers configuration is found in a seperate guide called:
STM32 Cortex®-M4 MCUs and MPUs programming manual - Programming manual

* Load the number of Cycles to Load register 
* clear systick current value register (set to 0)
* enable systick in the control register by setting CTRL_ENABLE to 1
* set clock source (internal(1) or external(0)) in the control register by setting CTRL_CLK_SOURCE tpo ( 1 or 0) 
* check if the control count flag is 0 (delay ended) 
* disable the control register (CTRL=0) 

Note : 

there is 2 methods to create the delay function 

- Method 1: is to do as i said above is to calculate the number of cycles N that corresponds to amount of the delay you want. 

- Method 2: is to set the Load register to the Clock source frequency 16Mhz divded by 1000 this means we get 1 cycle per 1 milli-second, then just multiply that to the amount of delay you want (for loop from 0 to delay)  

## to enable interrutpt 
set the TICKINT to 1, this will enable interrupt in the systick configuration register. 
enable the SYStick_interrupt service routine in the NVIC 
create the SYStick interruot service routine function 
create the callback function that you wan to excute when the interrupt occures (put it inside the SYStick service routine function) 
