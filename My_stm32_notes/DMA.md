## DMA 
the DMA allows for data transfer to take place without CPU intervention 
During the tranfer process the CPU can execute other tasks
## DMA proporties to configure

DMA stream/channel 
Stream priority
Source and destination adresses 
transfer mode 
transfer size 
source/destinationadress incrementing or non-incrementing
source and destination data width 
transfer type 
FIFO mode
Source/destination burst size
Doub-buffer mode 
Flow control
## DMA ports 
the DMA has 2 ports 
Memory port 
Peripheral port 
## DMA Streams 
the STM32F4 has only to DMA modues (DMA1 and DMA2) 
each module has 8 streams
each stream is dedicated to manage a memory acess request from one or more peripheral
each stream has up to 8 selectable channels (requests) in total via a multiplexer  

REQ_STREAMx_CH7   |
.                 | --->  REQ_STREAMx
REQ_STREAMx_CH0   |

the channel selection is software configurable and allows several peripherals to initiate a DMA requests 
Only one channel/request can be active at the same time in a stream 
in the refrence manual, there is a table that describes which peripheral should be connected to which stream 
(ie: Stream0->channel0->SPI3_RX)
here inoder to configure SPI3_RX you need to set the DAM to Stream0 channel0 

## DAM Stream priority
the DMA has an arbiter for handling the priority between the DMA streams 
stream prioriy is software configurable 
there are 4 levels 
if 2 or more DMA streams have the same software prioriy level, the hardware priority is used 
Hardware priority: Stream0 has priority over stream1 ... etc 
## DMA source/determination adresses
A DMA transfer is defined by a source adress and a destination adress 
both the source and the destination should be in the AHB and APB memory ranges 
DMA transfer refers to the process where the data is moved from one memory area to another (without the CPU intervention) 
en Example using USART to transfer a data: 
the source adress is the buffer to transmit 
the destination adress the USART data register (DR) 
then the USART peripheral will handel the data transmition 
## DMA transfer modes 
Peripheral to Memory
Memory to peripheral 
Memory to Memory (only available in DMA2 module) 
## tranfer size 
the transfer size defines the volume of data to be transferred from source to determination
the has to be defined only when the DMA is the Flow controler 

## DMA Incrementing adress 
when transfer data form a sensor (source) to an array stored in memory(destination), the destination adress must be incremented. 
DMA can automatically increment source and destination after each transfer 
## DMA soruce and Destination width 
3 options for data width 
8 bit: byte 
16 bit: half-word 
32 bit: word 
## DMA transfer mode 
* circular mode: (continuously collecting sesnor value) 
For handling circular buffer and continues data flow 
the DMA_SxNDTR register is then reloaded automatically with the previously programmed value 
* Normal mode 
once the DMA_SxNDTR register reaches 0, the stream is disabled

## DMA FIFO in F4 
Each stream has an independent 4-word(128bit) FIFO
the FIFO is used to temporarily (short amount of time) store data comming from the source before transmitting it to the destination
if the DMA FIFO is enabled, data packing/unpacking and/or Burst mode can be used 
The configured DMA threshold defines the DMA memory request time (if the FIFO is half full notify us .. ) 
* Benefits of FIFO 
reduces SRAM access and si gives more time for the other masters to access the bus matrix without additional concurrency 
Allow software to do burst transaction which optimize the transfer bandwith 
Allow packing/unpacking data to adapt source and destination data width with  no extra DMA access 
## configuring DMA : Configuring USART2_tx with DMA 
* in the refrece Manual DMA1 request mapping locate which streams are connected to USART 
USART2_tx (Stream6, channel_4)
	// enable clk access to DMA 
	// Disable DMA1 Stream6 (DMA_SxCR: DMA stream (0..7) control register   
    // Clear all interrupt flags of stream6 ( DMA_HIFCR: high interrupt clear register) (starts from stream 0)
		set all interrupt related flags to 1 of stream6 
	// set the destination buff ( DMA_SxPAR: Streamx peripheral adress ) 
	// set the src buff (the source here is the memory,DMA_SxM0AR: Sreamx memory 0 adress  )
	// set length (DMA_SxNDTR: number of data items  be transferred) 
	// select stream6 CH4 ( DMA_SxCR, set the 3bit CHSEl channel selection to 6)  
	// enable memory increlment ( enable memory increment bit 10 in the CR register) 
	// configure transfer direction memory->peripheral ( in the Cr register bit 7,6 direction bit ) 
	enable DMA interrupt transfer complete ( bit number 4 uin the CR register transfer complete interrupt)
	// Enable Direct mode, Disable FIFO ( DMA1_SxFCR FIFO control register set bit number 2 to 0 to enable direct mode 
	// enable DMA1 Steam6
	// Enable USART2 transmitter DMA ( in USART2 CR3 regitser enbale DMAT : DMA transmit 
	// enable INterrupt requet for DMA in NVIC for the DMA1_Stream6_IRQn 
Note: 
in DMA, there you can impoly 2 memeroy Areas, MEM0 and MEM1 
MEM1 is used for double buffering. 
While the DMA is transfering data from MEM0, the CPU i swriting the DATA to MEM1, an so on ... 
the method utilize parallelism to prevent contention for the same memory adress between the CPU and DMA. 
