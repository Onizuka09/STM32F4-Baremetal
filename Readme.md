# 🚀 STM32 Bare-Metal Programming

This repository documents my learning journey into **bare-metal development** on the **STM32F401RE Nucleo Board** using **direct register access**, without relying on HAL or CMSIS abstraction layers.

Each folder or file represents a hands-on project focusing on a specific peripheral or functionality of the STM32 microcontroller.

---

## 📘 Topics Covered

- GPIO Input/Output
- External Interrupts (EXTI)
- Timers and SysTick
- UART (Blocking, Interrupt, and DMA)
- I2C Communication
- SPI Communication
- ADC (Single and Multi-Channel, with/without Interrupts)
- DMA
- Register-level Bit Manipulation

---

## 📁 Project Structure

| Folder/File                             | Description |
|----------------------------------------|-------------|
| `0_led_toggle_addr`                    | Toggle LED using register address directly |
| `1_led_toggle_addr_struct`            | Toggle LED using register struct access |
| `GPIO_input_btn`                      | Read button input using polling |
| `GPIO_input_btn_EXTI`                 | Handle button press using EXTI (external interrupt) |
| `BSSR_reg`                            | Use BSRR register for GPIO bit setting/resetting |
| `SysTick`                             | Blink LED using SysTick timer delay |
| `SysTick_it`                          | Use SysTick with interrupt handler |
| `Timers`                              | Generate time-based events using general-purpose timers |
| `UART_transmit`                       | Send data over UART (blocking) |
| `UART_transmit_DMA`                   | Send data over UART using DMA |
| `UART_receive`                        | Receive data over UART (blocking) |
| `UART_receive_it`                     | Receive data over UART using interrupt |
| `UART_DMA`                            | UART full duplex using DMA |
| `ADC_single_channel_conversion`       | Read analog input using ADC (single channel) |
| `ADC_single_channel_conversion_it`    | ADC single channel using interrupt |
| `ADC_multi_channel_continues_conversion` | Read multiple ADC channels continuously |
| `I2C_ADXL345`                         | Interface with ADXL345 accelerometer via I2C |
| `SPI_ADXL345`                         | Interface with ADXL345 accelerometer via SPI |

---

## 🛠 Development Environment

- **Board**: STM32F401RE Nucleo
- **Toolchain**: `arm-none-eabi-gcc`
- **Flashing Tool**: `st-flash` or STM32CubeProgrammer
- **Editor**: VSCode 

---

## 📎 Notes

- All examples are written in **C** using **low-level register manipulation**.
- This project serves as a personal reference and learning base. Contributions and improvements are welcome!

---


