## STM32F070RB
STM32F070RB an ARM Cortex-M0 based microcontroller. In this Repository I will explore the use of this microcontroller. I used the STM32CubeIDE for this project.
# LED Toggle Using Memory Address (0_led_toggle_addr)
This code is for an STM32F070RB microcontroller, which is an ARM Cortex-M0 based microcontroller. The code is written in the main.c file and it configures the microcontroller's General-Purpose Input/Output (GPIO) pins to blink an LED.

The code first defines several memory addresses and registers related to the microcontroller's clock, GPIO, and RCC (Reset and Clock Control) modules. These definitions allow the code to access specific registers and memory locations within the microcontroller in order to control its behavior.

**The main function in this code does the following:**
1. It enables clock access to the GPIOA peripheral by setting bit 17 of the RCC_AHBEN_R register to 1.
2. It configures pin PA5 as an output pin by setting bit 10 of the GPIOA_MODE_R register to 1 and clearing bit 11 of the same register.
3. It sets PA5 high by setting bit 5 of the GPIOA_OD_R register to 1.
4. It toggles PA5, by XORing it with PIN5, and this creates a loop where the LED blinks continuously.

It is worth noting that the code uses a for loop with a fixed delay of 100000 in order to blink the LED. This delay can be adjusted to change the blink frequency of the LED.

PS: This code uses direct memory manipulation to control the peripherals, it is not recommended to use this method in normal cases, it is preferred to use HAL or LL libraries to access the registers of the microcontroller.
# LED Toggle Using Structures (1_led_toggle_addr_struct)
This code is for an STM32F070RB microcontroller. It initializes and configures the microcontroller's GPIOA (General Purpose Input/Output Port A) to control an LED connected to pin 5 on port A.

The code first defines a number of constants that are used to set the addresses of various registers and peripherals within the microcontroller's memory. This includes the base addresses for the AHB2 (Advanced High-performance Bus 2) and AHB1 (Advanced High-performance Bus 1) peripherals, as well as the RCC (Reset and Clock Control) register.

The code then defines two structs, "GPIO_TypeDef" and "RCC_TypeDef", which are used to access the memory-mapped registers of the GPIOA and RCC peripherals respectively.

In the main() function, the code first enables clock access to the GPIOA peripheral by setting the appropriate bit in the RCC->AHBENR register.

Then, it sets PA5 as output pin by setting the corresponding bit in the GPIOA->MODER register.

It then enters an infinite loop, in which it repeatedly toggles the state of the LED connected to pin 5 of port A by toggling the corresponding bit in the GPIOA->ODR register. It also includes a delay by using a for loop.
