## Introduction
In this Repository, I will extensively explore and document the use of this microcontroller and understanding of its function. I will create simple functions to demontstrate a feature of this device. Each involvement of a feature is distinguished by its number prefixed onto the section name. The aim of this repository is to aid in the understanding of ARM Cortex STM32 based MCUs, it can be translated very easily onto different models you would just have to check the relevant datasheet, reference manual, and user manual for your MCU/devkit and use the correct memory addresses for peripheral function or a HAL. I used the STM32CubeIDE for this project.

## STM32F070RB
STM32F070RB an ARM Cortex-M0 based microcontroller. 

# LED Toggle Using Memory Address (0_led_toggle_addr)
The code is written in the main.c file and configures the microcontroller's General-Purpose Input/Output (GPIO) pins to have a blinking LED.

The code has manually defined memory addresses and registers related to the microcontroller's clock, GPIO, and RCC (Reset and Clock Control) modules. These definitions allow the code to access specific registers and memory locations within the microcontroller in order to control its behavior.

**The main function in this code does the following:**
1. It enables clock access to the GPIOA peripheral by setting bit 17 of the RCC_AHBEN_R register to 1.
2. It configures pin PA5 as an output pin by setting bit 10 of the GPIOA_MODE_R register to 1 and clearing bit 11 of the same register.
3. It sets PA5 high by setting bit 5 of the GPIOA_OD_R register to 1.
4. It toggles PA5, by XORing it with PIN5, and this creates a loop where the LED blinks continuously.

It is worth noting that the code uses a for loop with a fixed delay of 100000 in order to blink the LED. This delay can be adjusted to change the blink frequency of the LED.

PS: This code uses direct memory manipulation to control the peripherals, it is not recommended to use this method in normal cases, it is preferred to use HAL or LL libraries to access the registers of the microcontroller.
# LED Toggle Using Structures (1_led_toggle_addr_struct)
Following the previous code, this code initializes and configures the microcontroller's GPIOA (General Purpose Input/Output Port A) to control an LED connected to pin 5 on port A.

A number of constants are used to set the addresses of various registers and peripherals within the microcontroller's memory. This includes the base addresses for the AHB2 (Advanced High-performance Bus 2) and AHB1 (Advanced High-performance Bus 1) peripherals, as well as the RCC (Reset and Clock Control) register.

The code then defines two structs, "GPIO_TypeDef" and "RCC_TypeDef", which are used to access the memory-mapped registers of the GPIOA and RCC peripherals respectively.

In the main() function, the code first enables clock access to the GPIOA peripheral by setting the appropriate bit in the RCC->AHBENR register.

Then, it sets PA5 as output pin by setting the corresponding bit in the GPIOA->MODER register.

It then enters an infinite loop, in which it repeatedly toggles the state of the LED connected to pin 5 of port A by toggling the corresponding bit in the GPIOA->ODR register. It also includes a delay by using a for loop.
# LED Toggle Using Standard Peripheral Library Header files (2_gpio_output)
This code performs the following tasks:
1. Enables clock access to the GPIOA port by setting the 17th bit in the RCC (Reset and Clock Control) AHB (Advanced High-performance Bus) register.
2. Configures pin 5 on the GPIOA port as an output pin. It sets the 10th bit in the GPIOA MODER (mode) register to 1 (output) and clears the 11th bit in the same register to 0 (input). 
3. In an infinite loop, toggles the state of pin 5 on the GPIOA port by using the bitwise exclusive OR operator (^=) on the GPIOA ODR (output data) register and the LED_PIN value, which is defined as PIN5. Before each iteration of the loop, the code waits for 100000 iterations of an empty for loop. This is used to create a delay between toggles.

The main difference between this and 1_led_toggle_addr_struct is that it has manually defined the required data structures and memory offsets to access different peripherals and registers of the STM32F070RB microcontroller, while this one includes the "stm32f0xx.h" header file which is a standard peripheral library header file for STM32F0xx devices from the STM32Cube MCU Package for STM32F0 series that includes definitions for all peripherals, including the RCC and GPIOA peripherals. 

PS: In this code we use a hardware abstraction layer (HAL) as it defines a set of routines, protocols and tools for interacting with the hardware.

This means that the second code uses the definitions and declarations already provided in the header file, whereas in the first code, the required definitions and memory offsets are defined manually. This makes the second code more concise and readable compared to the first one, but at the same time, it relies on the header file to be present and up-to-date with the correct definitions.


