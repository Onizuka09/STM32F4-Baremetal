## Timers 
* counting events 
* measuring time between events 
* creating delays 

## timer VS counter
a timer is an internal clock source ( PLL, RC , XTAL ) 
a counter is an external clock source ( clock fed up the CPU ( crystal ossillater) 
## STM32 Timers  
* can be used as a base generator  
* input capture mode: measure the frequency of an external event 
* output compare mode: control an output waveform or indicate when a period of time has elapsed
* one pulse mode (OPM): allows the counter to be started in response to a stimulus and to generate a pulse with a programmable length after a programmable delay. 
* Pulse with Modulation PWM: used to generate a pulsing signal to drive DC motors. it is a analog like single generated from digital devices.
It it basically varying the width of the signle when it's ON or OFF at a period.( like 20% ON and 80% OFF at a period T) 
## Timer Registers 
* Timer Count Registers (TIMx_CNT) 
shows the current counter value. Size Could be 32-bit or 16-bit depending on timer module. 
* Timer Auto-Reload Register (TIMx_ARR) 
Timer raises a flag and the counter restarts automatically when counter value reaches the value in the auto_reload register. 
the Timer can be configured to count up or down. 
* Timer Prescaler Register (TIMx_PSC) 
the prescaler slows down the counting speed of the timer by dividing the input clock of the timer (1,2,4,8,16,....)
* the timer control register CRx which offers a lot of functionalities like enabling and disabling the timer
* status register SR, this where to find the flag of certain operations like interrupts, timeouts ...
* capture/compare Register (CCR1,CCR2,CCR3,CCR4): there is capture/compare register for each of the 4 channels. 
this register is used to get the current value (timestamp) of the timer   
example: timer 1 channel3 attached to CCR3 
* Capture Compare Mode Register (1,2) CCMRx 
configuring capture/compare functionality channel x 
CCRM1: channel 1 and 2
CCRM2: channel 3 and 4 
example: configuring the CCRMx to capture the value at falling ,rising both edges 
* Capture/Compare Enable Register CCER
used to enable any of the timer channels to either as input capture or output compare 
Note: 
ST offers advanced timer and basic timers, the difference is the size and other functionality. 
Note2: 
update events: when a timeout occurs , or how long it takes for a flag to be raised 
Period: the value located in the auto_reload register. 
update event = (Timer clock )/ ( (Prescaler + 1 ) * ( Period + 1 ) )
## Programming 
the STM32 has 11 timers 
each timer could have from 1 to 4 channels 
it has variety of 32 advanced timers and 16 bit basic timers  
# Basic timer setup (1 second timeout == delay) 
generate a timeout every 1 second (1Hrz)
default SYSCLK: 16MHrz -> Bus frequency (16MHrz) -> timerx clock (16MHrz)
- enable clock access to timer  
- set prescaler value (PSC register) 
- set auto reload value 
- clear counter 
- enable timer 
- the UIF update interrupt flag register (located in TIM2_SR register) will indicate that a timeout has occurred. 
- clear the UIF register  
# Output compare mode 
I will set timer2 to toggle a pin PA5 when a period elapses (1s) 
## GPIO configuration 
enable clock to GPIOA 
set pin mode to alternate function 
configure alternate function typeto be time2 channel 1 AF01 == AF1 (0:  low register)
## timer configuration 
enable timer 2 
set prescaler value 
set autorload value
reset counter value to 0 
set output compare toggle mode TIMx_CCRx OC1M 
enable output compare mode to timer2 channel1 CCER CC


Note:
in datasheet at the laterante function pinout description: 
PA5 is connected to timer2 channel 1  
CCMR1,2: are set to configure both input capture and ouput compare 
OCxM: the x indicate wich channel you are working with
CCER: same register that enables input capture and ouput compare to enable the capture or compare
CCxE : x refers to the channel (1..4) 
0: disable capture/compare mode 
1: enables Capture/compare mode 


## Input capture 
will use a new timer to capture the toggle rate that happens at PINA5  
will be using PA6: timer3 channel 2 
 ## pin configuration 
enable clock to GPIOA 
set pin mode to alternate function 
configure alternate function typeto be time3 channel 1 AF02 == AF1 (0:  low register)
## timer configuration 
- enable timer 3
- set prescaler value 
- set CH1 to input capture CCMR1 at CC1S (01 Channel is configured as input capture 1)  
- specify at which edge to capture (rising edge == default mode): CCER enable CC1E   
- enable timer3 : timer control register enable CEN 
- check if rsing edge is captured  (Timerx_SR CC1IF Capture compare flag) 
- read the captured value: CCR1 register  

