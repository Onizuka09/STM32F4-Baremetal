# STM32 GPIO Peripheral Overview

## Key Registers

### 1. RCC (Reset and Clock Control)
- **Purpose**: Enable clock to the GPIO bus (AHB/APB)
- **Note**: Must enable clock before using GPIO

### 2. MODER (Mode Register) - 32-bit
- **Purpose**: Sets pin mode
- **Bit fields**: 2 bits per pin (00-11)
  - `00`: Input mode
  - `01`: Output mode
  - `10`: Alternate function mode
  - `11`: Analog mode

### 3. ODR (Output Data Register) - 16-bit
- **Purpose**: Write output values
- **Behavior**:
  - `ODRx = 1` → Pin x = HIGH
  - `ODRx = 0` → Pin x = LOW
- **Operations**: Read/Write
- **Note**: For atomic operations, use BSSR instead

### 4. IDR (Input Data Register) - 16-bit
- **Purpose**: Read input values
- **Behavior**: 
  - `IDRx` reflects pin x state (0=LOW, 1=HIGH)
- **Operations**: Read-only

### 5. BSSR (Bit Set/Reset Register) - 32-bit
- **Purpose**: Atomic pin control
- **Structure**:
  - **Bits 0-15**: Set bits (1=set pin, 0=no effect)
  - **Bits 16-31**: Reset bits (1=reset pin, 0=no effect)
- **Operations**: Write-only
- **Example**: 
  - Set pin 3: `BSSR = (1 << 3)`
  - Reset pin 3: `BSSR = (1 << (16 + 3))`

### 6. PUPDR (Pull-up/Pull-down Register) - 32-bit
- **Purpose**: Configure pull resistors
- **Bit fields**: 2 bits per pin
  - `00`: No pull
  - `01`: Pull-up
  - `10`: Pull-down

### 7. OTYPER (Output Type Register) - 32-bit
- **Purpose**: Configure output type
- **Bit fields**: 1 bit per pin
  - `0`: Push-pull
  - `1`: Open-drain

### 8. OSPEEDR (Output Speed Register) - 32-bit
- **Purpose**: Configure output speed
- **Bit fields**: 2 bits per pin
  - `00`: Low speed
  - `01`: Medium speed
  - `10`: High speed
  - `11`: Very high speed

## Typical Workflow
1. Enable clock in RCC
2. Configure MODER (input/output/alternate)
3. Configure additional settings:
   - OTYPER (push-pull/open-drain)
   - OSPEEDR (speed)
   - PUPDR (pull-up/down)
4. Use:
   - Output: ODR or BSSR
   - Input: Read IDR

## Tips
- For atomic operations, prefer BSSR over ODR
- Always check reference manual for specific bit patterns
- Consider using HAL/LL libraries for portability 





# My notes that i wrote 
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
