## ADC: analog to digital converters 
> physical world : every physical quantity is analog or continues 
> micro-controller(computers) : the data is binary ( 0 or 1) 
An ADC is an analog to digital converter: it converts analog signals to digital numbers so that the micro-controller could process it
An ADC is characterised with resolution 
Taking Vref as 5V 

| n-bit | number of steps | step size            |
| :---: | :-------------: | :------------------: |
| 8     | 256             | 5v / 256 = 16.39mV   |
| 10    | 1024            | 5v / 1024 =4.88mV    |
| 12    | 4096            | 5v / 4096 = 1.2mV    |
| 16    | 65536           | 5v / 65536 = 0.076mV |


** Note:

in stm32 the analog input is referred to as channel, you might find in a pin multiple channels
in the NUCLEO board there are multiple ADC, so each ADC has a number of channels (16 channels) that are connected to GPIO pin. 
the stm32f4 ADC peripheral supports only 6, 8, 10, 12 bit resolution 
you can change the resolution of the ADC in the ADC_CR1 register 
# ADC independent modes
* [Single-channel, single conversion mode](#single-channel-single-conversion-mode)
* [Multi-channel(scan), single conversion mode](#multi-channel-scan-single-conversion-mode)
* [Single-channel continues conversion mode](#single-channel-continues-conversion-mode)
* [Multi-channel continues conversion mode](#multi-channel-continues-conversion-mode)
* [Injected continues conversion mode](#injected-continues-conversion-mode)

## Single-channel, single conversion mode {#single-channel-single-conversion-mode}

Simplest ADC mode 
ADC performs a single conversion of a single channel X and stops after conversion is completed.
Use case: 
Measurement of a voltage level to determine if a system should be started or not (check one time)
## Multi-channel(scan), single conversion mode {#multi-channel-scan-single-conversion-mode}

Used to convert multiple channels successively but stops after conversion is completed. 
Use case: 
Measurement of multiple sensors to determine whether a system should start or not. 

## Single-channel continues conversion mode {#single-channel-continues-conversion-mode}

Used to convert Single channel non stop (continuously).
Use case: 
Measurement of room temperature continuously to adjust air-conditioner 


## Multi-channel continues conversion mode {#multi-channel-continues-conversion-mode}

Used to convert multiple channels non stop (continuously).
Use case: 
continuously measuring multiple accelerometers to adjust joints of a robot arm 

## Injected continues conversion mode {#injected-continues-conversion-mode}

 Intended for use when conversion is triggered by an external event or by software 
 The injected group (could be a channel or multiple channels) has priority over the regular channel group 
 Interrupts the conversion of the channel of the current channel in the regular channel group 

Use case: 
for synchronizing the conversion of channels to an event
 
# Programming 
the stm32f4 nucleao board has 1 ADC connected to APB2 bus 
## GPIO Configuration 
* select the pin (PA1) to configure as ADC:ADC1 channel1 

* enable clock access to the GPIOx port 
* set pin as analog mode
## ADC Configuration 
* set conversion start: ADC_SQRx 
* set conversion length: ADC_SQR1
* set conversion sequence: ADC_SQRx
* enable ADC: ADC_CR2 (ADON)
* set conversion mode: ADC_CRx( single or continues mode) 
* enable start conversion: ADC_CRx 
Note: 
the information regarding which pin is connected to which ADC channel is in the datasheet pin definition table additional function.
ADC sequenc regular registers ADC_SQRx[1,2,3]: these registers has mini registers called SQx the x represent the channel number, 
so for ADC_SQRx:

> ADC_SQR3
SQ6 -> SQ1 => 5bits 
SQ1 represents the first squence , SQ6 represents the 6 sequence (you are using 6 channels) 

> ADC_SQR2 
SQ12 -> SQ7

> ADC_SQR1: 
L[3:0]: represents the number of conversions,( 3 channels 4, channels) 
SQ16 -> SQ13: the registers represents the n sequence of the channels, ( you write the num of channel according to theire sequence)    

Example: i using ch3 , ch4, ch16, ch1 in this order => 4 channels so i will use ADC_SQR3: SQ1 to SQ4 
SQ1= ch3    = (00011) => start 
SQ2= ch4    = (00100)
SQ3= ch16   = (11111)
SQ4= ch1    = (00001)
in the ADC_SQR1: length register L[0..3] 
L = 4 = (0100) 

## Reading ADC value
check the status of the register regular channel en fo conversion EOC ( 0 conversion not complete): ADC_SR
read converted data from DR register 

### Interrupt ADC 
to enable the enterrupt: 
enable interrupt in the NVIC vector table  
enable interrupt in the control register, EOCIE: end of conversion interrupt flag  
create the ADC inetrrupt service routine function: this function will be executed when the EOCIE is set,
create a callback function (read ADC value)  that gets executed in the ADC interrupt service routine, 
