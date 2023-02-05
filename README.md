# Introduction
In this Repository, I will extensively explore and document the use of this microcontroller and understanding of its function. I will create simple functions to demontstrate a feature of this device. Each involvement of a feature is distinguished by its number prefixed onto the section name. The aim of this repository is to aid in the understanding of ARM Cortex STM32 based MCUs, it can be translated very easily onto different models you would just have to check the relevant datasheet, reference manual, and user manual for your MCU/devkit and use the correct memory addresses for peripheral function or a HAL. I used the STM32CubeIDE for this project.

## What Hardware did i use?
In this project i used the STM32F070RB, it is an ARM Cortex-M0 based microcontroller. 

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

From this section to the end I will be using the HAL
# LED toggle using Bit Set Reset Register (3_gpio_bsrr)
The code performs the following tasks:
1. Enables clock access to the GPIOA port by setting the 17th bit in the RCC AHB register.
2. Sets Pin 5 of GPIOA as an output pin using the MODER register, by setting the 10th bit using the bitwise OR operator(|=) and clearing the 11th bit using the bitwise AND and NOT operator (&= ~).
3. In a continuous loop, the code sets the Pin 5 of GPIOA (PA5) high by setting the 5th bit in the BSRR register. After a delay of 100000 cycles, the code then sets the Pin 5 of GPIOA low by resetting the 21st bit in the BSRR register.

The changes from the previous code is as follows:
1. Instead of using the ODR register to toggle the state of the LED, the code uses the bit set reset register (BSRR) to set (1) and reset (0) the LED pin.
# Configuring GPIO Input for LED Button Press (4_gpio_input)
In this code two ports, GPIOA and GPIOC, are used and one pin from each port is set as an output (GPIOA Pin 5) and input (GPIOC Pin 13) respectively. The code also enables clock access to the two ports by setting the appropriate bits in the RCC AHBENR register.

In the infinite loop, the code checks the state of the input pin, or otherwise the button in this case (PC13) by reading its value from the GPIOC input data register (IDR). If the button is not pressed (it is at a high state), the LED on GPIOA Pin 5 is turned on by setting the corresponding bit in the GPIOA BSRR register. If the button is pressed (it is at a low state), the LED on GPIOA Pin 5 is turned off by resetting the corresponding bit in the GPIOA BSRR register.

1. The code starts by including the header file "stm32f0xx.h", which contains definitions and prototypes for the STM32F070RB microcontroller.
2. Then, three macros are defined:
      GPIO_A_EN sets the 17th bit of the RCC AHB (Advanced High-performance Bus) register, which enables the clock access to GPIOA.
      GPIO_C_EN sets the 19th bit of the RCC AHB register, which enables the clock access to GPIOC.
      PIN5 sets the 5th bit location in the GPIOA register, which represents pin 5 of GPIOA.
      PIN13 sets the 13th bit location in the GPIOC register, which represents pin 13 of GPIOC.
      LED_PIN is defined as PIN5.
      BTN_PIN is defined as PIN13.
3. The main function starts with enabling the clock access to both GPIOA and GPIOC using the RCC AHBENR register.
4. Then, pin 5 of GPIOA is set as an output pin by setting the 10th bit of the GPIOA MODER (mode) register to 1, and the 11th bit to 0.
5. Pin 13 of GPIOC is set as an input pin by clearing the 26th and 27th bits of the GPIOC MODER register.
6. The program enters an infinite loop. In the loop, the state of the input pin PC13 is checked using the IDR (input data) register.
      If the state of the pin is high (the button is not pressed), the LED is turned on by setting the 5th bit of the GPIOA BSRR (bit set/reset) register.
      If the state of the pin is low (the button is pressed), the LED is turned off by resetting the 21st bit of the GPIOA BSRR register.
      The loop repeats indefinitely, continuously checking the state of the button and turning the LED on or off accordingly.
