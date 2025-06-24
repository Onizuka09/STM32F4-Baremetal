In stm32 the GPIO periph uses diffrent reg:
> first u need to enable the RCC to the bus where the GPIO is connected
> MODER (mode data reg) : this register is responsible for setting the mode of the reg ( OUTPUT , INPUT , or alternate function) 
> ODR (OUTPUT data reg) : this register enbales u to write to a pin ( set pin high) 
in this reg if you set the: reg1 to 1 (reg1= 1) => pin1 = 1 
                            reg1 to 0 (reg1=0) => pin1 =0  
opreations ( read and write ) => 16 bit reg 
* note (rm) :For atomic bit set/reset, the ODR bits can be individually set and reset.

> IDR (input data reg) : this register enables u read the state of a pin 


> BSSR (bit set reset reg) : this reg enbales u to write either high or low the register ( 32 bit reg) 
the first 16 bit are to set a reg  => pin = 1  so 
the last 16 bit are to reset a reg => pin = 0  
operation (write only) 

> pulup/pulldow reg : 
> otyper reg (push pull or open drain) 
> output speed reg 
