* UART serail communication 
> synchronos method : clock is transmeted  with the data 
* USART asynch 
> asynchronos method : the trans and recv agree on the clock speed for the data transmition (baudrate bit/s) 
both of the modes work as  ( Recievers and transmiters ) 
NOTE:  
Full duplex : the device can transmit and receive both ways at the same time (both direction) 
Half duplex : the device can only transmit or receive one way at a time (both direction ) 
simplex : the deiveccan transmet only or receive only ( one direction) 
## Configuration Asynch 
each byte should be transmited is packed between a start bit and a stop bit
start bit: is a 1 bit with a value that is usually 0. 
stop bit : could be represented by 1 or 2 bits with a value equal to 1. 
Data : the package to transmit ( 8 or 9 ) 
EX: ASCII 'A': 0100 0001  

Frame :         11 0100 0001 0 
            Stop bit   A     Start bit  
NB: transmition from left to right 
Other configuration: 
Bauderate: connection speed (ie: 9600 bit/s)  
Stop bit:  1 or 2 
Parity: to indicate the mode (odd or even) for error checking 
## Programming:
in STM32F401Retx,
* GPIO configuration 
the USART2 is connected to the USB  ( uses APB1 bus) 
IN datasheet alterante function mapping (AF07):
USART2_TX: PA2
USART2_RX: PA3
in the Alterante function regsiter therse is(GPIO): 
Alterante function register low: corresponds to all the pin from 0 to 7 
Alterante function register high: corresponds to all the pin from 8 to 15 
* USART configuration:  
to configure transmition mode (Rx,Tx), the stop bit, the  start bit , word lengh .... : there are special registers in the USART calle CRx [1,2,3] 
by default in the the usart is configure to 1 stop bit, 1 parity bit (even) , 8 word lengh  
## setiing UART transmit in stm32f4 
1- choose which uart to work on and get its pinout (USART2, PA2: Tx , PA3) 
* GPIO configuration 
2- enable clock access to gpiox ( which gpio the pin are connected to) : AHB1 
3- set alternate function in the moder register mode (moder = 10) 
4- in the alternate function register set type to be USART: 
    IN datasheet alterante function mapping (AF07):
    in the defenition of the AFR will find which AF07 coreesenponds to (0111) .
NB: 
- in the Alterante function regsiter therse is(GPIO): 
- Alterante function register low: corresponds to all the pin from 0 to 7 
- Alterante function register high: corresponds to all the pin from 8 to 15 

* USART configfuration 
1- enable clock access to uart 2: 
2- configure baude rate (BR reg)  
3- configure transfer direction (Tx) in CR1, TE: enable tranmitter
4- configure receive direction (Rx) in CR1, RE: enable tranmitter
5- enable uart module UE in CR1 

NB: 
- in the blcok diagram you wil find usart2 on which bus is connected to (APB1) 
- there are special registers in the USART calle CRx [1,2,3] : to configure transmition mode (Rx,Tx), the stop bit, the  start bit , word lengh .... :
-to set the baude rate you need this equation: ((PeriphClk + (Baudrate/2U)) /Baudrate);

* transmitting: 
1- make sure the transmit data register is empty (status register SR TXE: returns 0 register not empty , 1 if register is empty) 
2- write to the transmit data registe (DR: 16 bit reg) 

* receiving : 
1- make sure the receive register not empty (SR_RXNE) is not empty 
2- read from the data register 
## Interrupt 
* USART receive interrupt 
- enable usart receive interrupt (RXNEIE) in the USART_CR register 
- enable USART2 interrupt request in the NVIC 
* in the receive Interrupt function 
* Create the USART2 interrupt request handler function (the name should match the one that is in the NVIC interrupt table) 
* check if the SR_RXNE is set  
* create a callback function that excutes whaterver you want when data is received 

