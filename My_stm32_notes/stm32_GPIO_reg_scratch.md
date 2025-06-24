

# How to Toggle an LED from Scratch Using an STM32 Microcontroller
## Introduction
Have you ever wondered how digitalWrite() or HAL_GPIO_Write() functions work under the hood? In this article, we’ll explore how to toggle an LED on an STM32 microcontroller without relying on the HAL or CMSIS libraries. We’ll start from the basics and cover everything from setting up the base registers to flashing the firmware onto the microcontroller.

For this tutorial, we’ll be using the STM32F401RET6-NUCLEO board, specifically focusing on toggling the green LED connected to pin PA5 (pin 21).

## Getting Started
Before diving into the code, let’s first take a look at some essential resources:

Block Diagram: Located in the datasheet of the STM32F401R2T6.
Memory Map: Found in the user manual, particularly on page 51, where the peripherals' memory map is detailed.
Understanding the Memory Map
In the STM32F4 series, the memory map for peripherals starts at address 0x4000 0000 and ends at 0xE00F FFFF. This memory block contains all the registers related to the peripherals. Each peripheral is routed through a specific bus, such as AHB1, AHB2, APB1, or APB2.

Now, we need to locate the memory region where the GPIOA resides (which controls our LED on PA5) and determine which bus controls this peripheral.

By examining the tables in the user manual, we can see that GPIOA is connected to the AHB1 bus, and its memory address range is from 0x4002 0000 to 0x4002 03FF.

The Role of the Bus
Understanding the bus architecture is crucial. The bus is responsible for transporting the clock signal to various peripherals. Without the clock signal, peripherals like GPIOA won’t function.

The AHB (Advanced High-performance Bus) is faster than the APB (Advanced Peripheral Bus). The GPIOA peripheral, connected to the AHB1 bus, requires the clock signal to be enabled for it to operate.

The peripheral responsible for enabling the clock signal is the Reset and Clock Control (RCC).

Configuring the Registers
Enabling the Clock
To make GPIOA functional, we need to enable the AHB1 bus clock. This is done through the RCC AHB1 enable register.

```C
// Enable clock for GPIOA (AHB1ENR)
*(volatile unsigned int*) 0x40023830 |= (1 << 0);
```

## Configuring GPIOA
After enabling the clock, we need to configure GPIOA to control the LED on PA5.

MODER (Mode Register): Sets the pin direction (input, output, or alternate function).
MODR (Output Data Register): Controls the data written to the GPIO pin.

```C 
// Set PA5 as output (MODER)
*(volatile unsigned int*) 0x40020000 |= (1 << 10);

// Toggle PA5 (ODR)
*(volatile unsigned int*) 0x40020014 ^= (1 << 5);


```
## GPIO Input
Now, let’s add a push button input to our setup. The push button is located on PC13 (Port C, Pin 13).

Enable the Clock: Just like with GPIOA, we need to enable the clock for GPIOC.
Configure MODER: Set the mode to input for PC13.

```C 
// Enable clock for GPIOC (AHB1ENR)
*(volatile unsigned int*) 0x40023830 |= (1 << 2);

// Set PC13 as input (MODER)
*(volatile unsigned int*) 0x40020800 &= ~(3 << 26);


```
Additional Components
Makefile
A Makefile is essential for compiling our code. It defines the compilation process and the necessary flags.

Linker Script
The linker script is used to define the memory regions and how the sections of the code are placed in memory.

Start-up File
The start-up file initializes the hardware and sets up the stack before jumping to the main function.

Flashing the Firmware
Finally, after setting up everything, we need to flash the firmware onto the STM32 board. This can be done using tools like OpenOCD or STM32CubeProgrammer.

Conclusion
By following these steps, you can gain a deeper understanding of how to control an STM32 microcontroller at the register level, bypassing the abstraction layers provided by the HAL and CMSIS libraries. This knowledge can be especially valuable for low-level programming and debugging.

Stay tuned for more articles where we dive deeper into the intricacies of STM32 microcontrollers! 
