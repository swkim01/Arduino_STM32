/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "arduino.h"
//#include "variant.h"


/*
 * DUE Board pin   |  PORT  | Label
 * ----------------+--------+-------
 *   0             |  PA8   | "RX0"
 *   1             |  PA9   | "TX0"
 *   2       TIOA0 |  PB25  |
 *   3       TIOA7 |  PC28  |
 *   4       NPCS1 |  PA29  |
 *           TIOB6 |  PC26  |
 *   5       TIOA6 |  PC25  |
 *   6       PWML7 |  PC24  |
 *   7       PWML6 |  PC23  |
 *   8       PWML5 |  PC22  |
 *   9       PWML4 |  PC21  |
 *  10       NPCS0 |  PA28  |
 *           TIOB7 |  PC29  |
 *  11       TIOA8 |  PD7   |
 *  12       TIOB8 |  PD8   |
 *  13       TIOB0 |  PB27  | LED AMBER "L"
 *  14       TXD3  |  PD4   | "TX3"
 *  15       RXD3  |  PD5   | "RX3"
 *  16       TXD1  |  PA13  | "TX2"
 *  17       RXD1  |  PA12  | "RX2"
 *  18       TXD0  |  PA11  | "TX1"
 *  19       RXD0  |  PA10  | "RX1"
 *  20             |  PB12  | "SDA"
 *  21             |  PB13  | "SCL"
 *  22             |  PB26  |
 *  23             |  PA14  |
 *  24             |  PA15  |
 *  25             |  PD0   |
 *  26             |  PD1   |
 *  27             |  PD2   |
 *  28             |  PD3   |
 *  29             |  PD6   |
 *  30             |  PD9   |
 *  31             |  PA7   |
 *  32             |  PD10  |
 *  33             |  PC1   |
 *  34             |  PC2   |
 *  35             |  PC3   |
 *  36             |  PC4   |
 *  37             |  PC5   |
 *  38             |  PC6   |
 *  39             |  PC7   |
 *  40             |  PC8   |
 *  41             |  PC9   |
 *  42             |  PA19  |
 *  43             |  PA20  |
 *  44             |  PC19  |
 *  45             |  PC18  |
 *  46             |  PC17  |
 *  47             |  PC16  |
 *  48             |  PC15  |
 *  49             |  PC14  |
 *  50             |  PC13  |
 *  51             |  PC12  |
 *  52       NPCS2 |  PB21  |
 *  53             |  PB14  |
 *  54             |  PA16  | "A0"
 *  55             |  PA24  | "A1"
 *  56             |  PA23  | "A2"
 *  57             |  PA22  | "A3"
 *  58       TIOB2 |  PA6   | "A4"
 *  69             |  PA4   | "A5"
 *  60       TIOB1 |  PA3   | "A6"
 *  61       TIOA1 |  PA2   | "A7"
 *  62             |  PB17  | "A8"
 *  63             |  PB18  | "A9"
 *  64             |  PB19  | "A10"
 *  65             |  PB20  | "A11"
 *  66             |  PB15  | "DAC0"
 *  67             |  PB16  | "DAC1"
 *  68             |  PA1   | "CANRX"
 *  69             |  PA0   | "CANTX"
 *  70             |  PA17  | "SDA1"
 *  71             |  PA18  | "SCL1"
 *  72             |  PC30  | LED AMBER "RX"
 *  73             |  PA21  | LED AMBER "TX"
 *  74       MISO  |  PA25  |
 *  75       MOSI  |  PA26  |
 *  76       SCLK  |  PA27  |
 *  77       NPCS0 |  PA28  |
 *  78       NPCS3 |  PB23  | unconnected!
 *
 * USB pin         |  PORT
 * ----------------+--------
 *  ID             |  PB11
 *  VBOF           |  PB10
 *
 */


#ifdef __cplusplus
extern "C" {
#endif

/*

 * Pins descriptions

 this is reworked to be a bit more abstract.  The main use of this array is for
 bit banged GPIO setup.  Since we are using the HAL libraries, the setup
 is through STM32CubeMX for our peripherals, rendering this table
 redundant for general io and peripheral setup
 
 What we have here is an Abstraction on top of another abstraction. 
 
 The abstraction is that to set or read a pin we only need two items of
 information, the port and the pin.  As Arduino abstracts by pin
 we use this abstraction to map into the following table the order
 of this table should be by Arduino D number

 The only thing the HAL API needs are the port and PIN references

 The following table is written in c shorthand it could also be set up
 with the more readable 
 
 g_Pin2PortMapArray[D1 ].GPIOx_Port = GPIOA;
 g_Pin2PortMapArray[D1 ].Pin_abstraction = GPIO_PIN_3    D0/PA3	USART_RX	 
 g_Pin2PortMapArray[D2 ].GPIOx_Port = GPIOA;
 g_Pin2PortMapArray[D2].Pin_abstraction = GPIO_PIN_2    D0/PA3	USART_RX
 ... ect ...
 Ideally this array should be non mutable and in flash	 



 
*/



extern const Pin2PortMapArray g_Pin2PortMapArray[]=
{ 

	/* DM00050135.pdf datasheet has suggested 'Aruino' mapping table */
   
	{GPIOA, GPIO_PIN_3	},	/*  PA3		D0	USART2_RX	*/
	{GPIOA, GPIO_PIN_2	},	/*  PA2		D1	USART2_TX	*/

    {GPIOB, GPIO_PIN_12,},	/*  PB12	D2	EXTI		*/
    {GPIOB, GPIO_PIN_11 },	/*  PB11	D3	~TIM2_CH4	*/
    {GPIOA, GPIO_PIN_7	}, 	/*  PA7		D4	*/
    {GPIOB, GPIO_PIN_9	}, 	/*  PB9		D5	~TIM17_CH1	*/
    {GPIOB, GPIO_PIN_8	}, 	/*  PB8		D6	~TIM16_CH1	*/
    {GPIOA, GPIO_PIN_6	}, 	/*  PA6		D7	*/
    
    {GPIOA, GPIO_PIN_5	},	/*  PA5		D8	*/
    {GPIOA, GPIO_PIN_4	}, 	/*  PA4		D9	~TIM14_CH1	*/
    {GPIOA, GPIO_PIN_11 },	/*  PA11	D10	~TIM1_CH4	*/
    {GPIOB, GPIO_PIN_5	},	/*  PB5		D11	SPI1_MOSI	*/
    {GPIOB, GPIO_PIN_4  },	/*  PB4		D12	SPI1_MISO	*/
    
/*  
	suggested mapping if SPI1 is needed
	{GPIOB, GPIO_PIN_3  },		PB3		D13 SPI1_SCK	*/
/*	or use green LED as state indicator  */
    {GPIOC, GPIO_PIN_9, },	/*  PC9		D13	LD3 [Green Led] */

    {GPIOB, GPIO_PIN_7  },	/*  PB7		D14	I2C1_SDA	*/
    {GPIOB, GPIO_PIN_6	}, 	/*  PB6		D15	I2C1_SCL	*/

    {GPIOC, GPIO_PIN_0	},  /*  PC0 	D16	A0	*/
    {GPIOC, GPIO_PIN_1	}, 	/*  PC1		D17 A1	*/
    {GPIOC, GPIO_PIN_2  },	/*  PC2		D18 A2	*/
    {GPIOC, GPIO_PIN_3  },	/*  PC3		D19 A3	*/
    {GPIOC, GPIO_PIN_4, },	/*  PC4		D20	A4	*/
	{GPIOC, GPIO_PIN_5	},	/*  PC5		D21	A5	*/

	/* 
		extra pins on headers not mapped to Arduino shield header 
		These may move about a bit depending on functions needed
	*/

    {GPIOB, GPIO_PIN_13 },	/* PB13		D22 SPI2_SCK		*/
    {GPIOB, GPIO_PIN_15 },	/* PB15		D23	SPI2_MOSI		*/
    {GPIOB, GPIO_PIN_14 },	/* PB14		D24	SPI2_MISO		*/

    {GPIOA, GPIO_PIN_0	}, 	/*	PA0 	D25	Blue pushbutton	*/
    {GPIOC, GPIO_PIN_14 },	/*	PC14	D26	RCC_OSC32_IN	*/
    {GPIOC, GPIO_PIN_15 },	/*	PC15	D27	RCC_OSC32_OUT	*/

	{GPIOC, GPIO_PIN_12 },	/*	PC12	D28 */
	{GPIOC, GPIO_PIN_13 },	/*	PC13	D29 */
	{GPIOA, GPIO_PIN_1	}, 	/*	PA1 	D30	*/

    {GPIOB, GPIO_PIN_0	}, 	/*  PB0		D31 */
	{GPIOB, GPIO_PIN_1	},	/*  PB1		D32 */
    {GPIOB, GPIO_PIN_2  },	/*  PB2		D33 */
    {GPIOB, GPIO_PIN_10	},	/*  PB10	D34 */
    {GPIOC, GPIO_PIN_6, },	/*  PC6		D35 */
    {GPIOC, GPIO_PIN_7	}, 	/*  PC7		D36 */
    {GPIOC, GPIO_PIN_8, },	/*  PC8		D37	Blue LED 	*/
/*	{GPIOC, GPIO_PIN_9, },		PC9		D38	LD3 [Green Led] */
/* or */
	{GPIOB, GPIO_PIN_3  },	/*  PB3		D38 SPI1_SCK	*/

	{GPIOA, GPIO_PIN_8}	,	/*  PA8		D39 */
	{GPIOA, GPIO_PIN_9	}, 	/*  PA9		D40	USART1_TX	*/
    {GPIOA, GPIO_PIN_10	},	/*  PA10	D41	USART1_RX	*/
    {GPIOA, GPIO_PIN_12	},	/*  DPA12	D42 */
 	{GPIOA, GPIO_PIN_15},	/*	PA15 	D43 */
    {GPIOC, GPIO_PIN_10 },	/*  PC10 	D44 */
    {GPIOC, GPIO_PIN_11 },	/*  PC11	D45 */
    {GPIOD, GPIO_PIN_2, },	/*  PD2 	D46	*/
    {GPIOF, GPIO_PIN_4, },	/*  PF4 	D47	*/
    {GPIOF, GPIO_PIN_5, },	/*  PF5 	D48	*/
    {GPIOF, GPIO_PIN_6, },	/*  PF6 	D49	*/
    {GPIOF, GPIO_PIN_7, }	/*  PF7 	D50	*/
  
	/*
		JTAG STLink pins not mapped in table
		PA13	SYS_SWDIO
		PA14	SYS_SWCLK
	*/
	
} ;

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */
RingBuffer rx_buffer1;
RingBuffer tx_buffer1;


/*
	install bridge hooks to syscalls that will allow printf() to
	access one of the USARTS
*/

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  
  /* 
  	huart6 is defined in usart.h and instantiated in usart.c 
  	usart.h is defined in chip.h and the header is loaded through UARTClass.h
  */ 
  
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF); 

  return ch;
}

//UARTClass Serial(UART, UART_IRQn, ID_UART, &rx_buffer1, &tx_buffer1);
UARTClass Serial(&huart1, USART1_IRQn, 1, &rx_buffer1, &tx_buffer1);
void serialEvent() __attribute__((weak));
void serialEvent() { }

// IT handlers
void UART_Handler(void)
{
//  Serial.IrqHandler();
}

// ----------------------------------------------------------------------------
/*
 * USART objects
 */
#if 1
RingBuffer rx_buffer2;
//RingBuffer rx_buffer3;
//RingBuffer rx_buffer4;
RingBuffer tx_buffer2;
//RingBuffer tx_buffer3;
//RingBuffer tx_buffer4;

USARTClass Serial1(&huart2, USART2_IRQn, 2, &rx_buffer2, &tx_buffer2);
void serialEvent1() __attribute__((weak));
void serialEvent1() { }
//USARTClass Serial2(USART1, USART1_IRQn, ID_USART1, &rx_buffer3, &tx_buffer3);
//void serialEvent2() __attribute__((weak));
//void serialEvent2() { }
//USARTClass Serial3(USART3, USART3_IRQn, ID_USART3, &rx_buffer4, &tx_buffer4);
//void serialEvent3() __attribute__((weak));
//void serialEvent3() { }

// IT handlers
void USART0_Handler(void)
{
//  Serial1.IrqHandler();
}

//void USART1_Handler(void)
//{
//  Serial2.IrqHandler();
//}

//void USART3_Handler(void)
//{
//  Serial3.IrqHandler();
//}

// ----------------------------------------------------------------------------

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
  if (Serial1.available()) serialEvent1();
//  if (Serial2.available()) serialEvent2();
//  if (Serial3.available()) serialEvent3();
}
#endif
