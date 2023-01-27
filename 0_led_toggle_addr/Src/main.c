//Where is the LED connected?
//Port: A
//Pin: 5

//Peripherals From 0x4000 0000 to 0x4800 17FF
//GPIO A 0x4800 0000 -to 0x4800 03FF

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

#define AHBEN_R_OFFSET		(0x14UL)
#define RCC_AHBEN_R			(*(volatile unsigned int *)(RCC_BASE + AHBEN_R_OFFSET)) //RCC Enable Register for AHB2 (GPIOA)

#define MODE_R_OFFSET	(0x00UL)
#define GPIOA_MODE_R	(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET)) //PIN Mode Register
/*
 * (1U<<10) //set bit 10 to 1
 * &=~(1U<<11)	//set bit 11 to 0
 */
#define OD_R_OFFSET		(0x14UL)
#define GPIOA_OD_R		(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))  //Output Data Register

#define IOPAEN				(1U<<17)

#define PIN5				(1U<<5)
#define LED_PIN				PIN5

int main(void)
{
	/* 1.Enable clock access to GPIOA*/
	RCC_AHBEN_R	|= IOPAEN;

	/* 2. Set PA5 as output pin*/

	GPIOA_MODE_R |= (1U<<10); //bitwise OR(|=)
	GPIOA_MODE_R &= ~(1U<<11); //bitwise AND(&=), NOT(~)
	while(1)
	{
		/* 3.Set PA5 high*/
		//GPIOA_OD_R	|= LED_PIN;
		//4.toggle PA5
			GPIOA_OD_R	^= LED_PIN;
			for(int n=0;n<100000;n++){}
		}
}

