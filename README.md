## STM32F070RB
STM32F070RB an ARM Cortex-M0 based microcontroller. In this Repository I will explore the use of this microcontroller. I used the STM32CubeIDE for this project.
# LED Toggle Using Memory Address (0_led_toggle_addr)
This code is for an STM32F070RB microcontroller, which is an ARM Cortex-M0 based microcontroller. The code is written in C and it configures the microcontroller's General-Purpose Input/Output (GPIO) pins to blink an LED.

The code first defines several memory addresses and registers related to the microcontroller's clock, GPIO, and RCC (Reset and Clock Control) modules. These definitions allow the code to access specific registers and memory locations within the microcontroller in order to control its behavior.

**The main function in this code does the following:**
1. It enables clock access to the GPIOA peripheral by setting bit 17 of the RCC_AHBEN_R register to 1.
2. It configures pin PA5 as an output pin by setting bit 10 of the GPIOA_MODE_R register to 1 and clearing bit 11 of the same register.
3. It sets PA5 high by setting bit 5 of the GPIOA_OD_R register to 1.
4. It toggles PA5, by XORing it with PIN5, and this creates a loop where the LED blinks continuously.

It is worth noting that the code uses a for loop with a fixed delay of 100000 in order to blink the LED. This delay can be adjusted to change the blink frequency of the LED.

PS: This code uses direct memory manipulation to control the peripherals, it is not recommended to use this method in normal cases, it is preferred to use HAL or LL libraries to access the registers of the microcontroller.
