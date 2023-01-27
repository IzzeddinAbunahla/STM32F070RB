//Where is the LED connected?
//Port: A
//Pin: 5

//Peripherals From 0x4000 0000 to 0x4800 17FF
//GPIO A 0x4800 0000 -to 0x4800 03FF
#include	<stdint.h>

#define PERIPH_BASE 		(0x40000000UL) //UL for unsigned long

//0x4000 0000 + 0x0800 0000 = 0x4800 0000 offset from the peripheral base to arrive at AHB2
#define AHB2PERIPH_OFFSET	(0x08000000UL)
#define AHB2PERIPH_BASE		(PERIPH_BASE + AHB2PERIPH_OFFSET)

#define GPIOA_OFFSET		(0x00000000UL)
#define GPIOA_BASE			(AHB2PERIPH_BASE + GPIOA_OFFSET)

#define AHB1PERIPH_OFFSET	(0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define RCC_OFFSET			(0x00001000UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET) //RCC Resetting Clock Control, it is used to control whether a bus can transfer data/clock to a peripheral

#define IOPAEN				(1U<<17)

#define PIN5				(1U<<5)
#define LED_PIN				PIN5
#define __IO	volatile

typedef struct
{
	__IO uint32_t MODER; /* GPIO port mode register Address offset: 0x00 */
	uint32_t DUMMY[4];
	__IO uint32_t ODR; /* GPIO output data register Address offset: 0x14 */
} GPIO_TypeDef;

typedef struct
{
	uint32_t DUMMY[5];
	__IO uint32_t AHBENR; /* RCC AHB1 peripheral clock register Address offset: 0x14 */
} RCC_TypeDef;


#define RCC		((RCC_TypeDef*) RCC_BASE) //typecast it as RCC struct
#define GPIOA	((GPIO_TypeDef*) GPIOA_BASE)




int main(void)
{
	/* 1.Enable clock access to GPIOA*/
	RCC->AHBENR	|= IOPAEN;

	/* 2. Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10); //bitwise OR(|=)
	GPIOA->MODER &= ~(1U<<11); //bitwise AND(&=), NOT(~)
	while(1)
	{
		//3.Toggle PA5
			GPIOA->ODR	^= LED_PIN;
			for(int n=0;n<100000;n++){}
		}
}

