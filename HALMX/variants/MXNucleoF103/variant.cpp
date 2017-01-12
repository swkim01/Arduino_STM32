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
  
  - 08 April 2016 Modified by Vassilis Serasidis
    This file is converted for using it with ST HAL + CubeMX + Arduino SAM core files.
*/

#include "Arduino.h"
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
	{GPIOA, GPIO_PIN_3,  ADC_CHANNEL_3, hTimer2,  TIM_CHANNEL_4 },	/*  D0/PA3	USART2_RX	*/
	{GPIOA, GPIO_PIN_2,  ADC_CHANNEL_2, hTimer2,  TIM_CHANNEL_3 },	/*  D1/PA2	USART2_TX	*/
	
    {GPIOA, GPIO_PIN_10, NO_ADC       , hTimer1,  TIM_CHANNEL_3 },	/*  D2/PA10	USART1_RX	*/
    {GPIOB, GPIO_PIN_3,  NO_ADC       , NO_PWM,   NO_PWM        },	/*  D3/PB3	SWO			*/
    {GPIOB, GPIO_PIN_5,  NO_ADC       , hTimer3,  TIM_CHANNEL_2 },	/*  D4/PB5	GPIO T3		*/
    {GPIOB, GPIO_PIN_4,  NO_ADC       , hTimer3,  TIM_CHANNEL_1 },	/*  D5/PB4  GPIO T3		*/
    {GPIOB, GPIO_PIN_10, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D6/PB10	I2C2_SCL	*/
    {GPIOA, GPIO_PIN_8,  NO_ADC       , hTimer1,  TIM_CHANNEL_1 },	/*  D7/PA8	GPIO T1		*/

    {GPIOA, GPIO_PIN_9,  NO_ADC       , hTimer1,  TIM_CHANNEL_2 }, 	/*  D8/PA9	USART1_TX	*/
    {GPIOC, GPIO_PIN_7,  NO_ADC		  , hTimer3,  TIM_CHANNEL_2 }, 	/*  D9/PC7	USART6Rx GPIO */
    {GPIOB, GPIO_PIN_6,  NO_ADC       , hTimer4,  TIM_CHANNEL_1 }, 	/*  D10/PB6	I2C1_SCL USART1TXAF */
    {GPIOA, GPIO_PIN_7,  ADC_CHANNEL_7, NO_PWM,   NO_PWM        }, 	/*  D11/PA7	SPI_MOSI_NC	*/
    {GPIOA, GPIO_PIN_6,  ADC_CHANNEL_6, NO_PWM,   NO_PWM        }, 	/*  D12/PA6	SPI_MISO_NC */
    
    {GPIOA, GPIO_PIN_5,  ADC_CHANNEL_5, NO_PWM,   NO_PWM        },	/*  D13/PA5 LED - no ADC12_IN5 SPI_SCK !*/
    
    {GPIOB, GPIO_PIN_9,  NO_ADC       , hTimer4,  TIM_CHANNEL_4 }, 	/*  D14/PB9 I2C1_SDA	*/
    {GPIOB, GPIO_PIN_8,  NO_ADC       , hTimer4,  TIM_CHANNEL_3 }, 	/*  D15/PB8 I2C1_SCL	*/

    {GPIOA, GPIO_PIN_0,  ADC_CHANNEL_0, hTimer2,  TIM_CHANNEL_1 }, 	/*  D16/A0/PA0 GPIO		*/
    {GPIOA, GPIO_PIN_1,  ADC_CHANNEL_1, hTimer2,  TIM_CHANNEL_2 }, 	/*  D17/A1/PA1 GPIO		*/
    {GPIOA, GPIO_PIN_4,  ADC_CHANNEL_4, NO_PWM,   NO_PWM        }, 	/*  D18/A2/PA4 SPI_NSS	*/
    {GPIOB, GPIO_PIN_0,  ADC_CHANNEL_8, hTimer3,  TIM_CHANNEL_3 }, 	/*  D19/A3/PB0 GPIO		*/
    {GPIOC, GPIO_PIN_1,  ADC_CHANNEL_11, NO_PWM,  NO_PWM        }, 	/*  D20/A4/PC1 GPIO		*/
    {GPIOC, GPIO_PIN_7,  ADC_CHANNEL_10, NO_PWM,  NO_PWM        },  /*  D21/A5/PC0 GPIO		*/

    /*
    	 these signals are only on the Morpho headers
    	 Odd pins are on the left header
    	 Even pins are on the right header                 
    */
    
    {GPIOC, GPIO_PIN_10, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D22/PC10 	SPI_SCK				ML1 */
	{GPIOC, GPIO_PIN_12, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D23/PC12	SPI_MOSI			ML3 */
    {GPIOB, GPIO_PIN_7,  NO_ADC       , hTimer4,  TIM_CHANNEL_2 },	/*  D24/PB7		I2C1_SDA USART1RxAF	M21 */
    {GPIOC, GPIO_PIN_13, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D25/PC13	USER BLUE BUTTON	M23 */
    {GPIOC, GPIO_PIN_14, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D26/PC14	RCC_OSC32_IN 		M25 */
    {GPIOC, GPIO_PIN_15, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D27/PC15	RCC_OSC32_OUT		M26 */
    {GPIOC, GPIO_PIN_2,  ADC_CHANNEL_12, NO_PWM,  NO_PWM        },	/*  D28/PC2		SPI2_MISO			M35 */
    {GPIOC, GPIO_PIN_3,  ADC_CHANNEL_13, NO_PWM,  NO_PWM        },	/*  D29/PC3		GPIO				M37 */
    {GPIOC, GPIO_PIN_11, NO_ADC		  , NO_PWM,  NO_PWM        },	/*  D30/PC11	SPI3_MISO	 ADC1_EXTI11	ML2 */
    {GPIOD, GPIO_PIN_2,  NO_ADC       , NO_PWM,   NO_PWM        },	/*  D31/PD2 	GPIO				ML4 */
    {GPIOC, GPIO_PIN_9,  NO_ADC       , hTimer3,  TIM_CHANNEL_4 },	/*  D32/PC9		GPIO				MR1 */
    {GPIOC, GPIO_PIN_8,  NO_ADC       , hTimer3,  TIM_CHANNEL_3 },	/*  D33/PC8		GPIO				MR2 */
    {GPIOC, GPIO_PIN_6,  NO_ADC       , hTimer3,  TIM_CHANNEL_1 },	/*  D34/PC6		USART6Tx GPOO		MR4 */
    {GPIOC, GPIO_PIN_5,  ADC_CHANNEL_15, NO_PWM,  NO_PWM        },	/*  D35/PC5		GPIO				MR6 */
    {GPIOA, GPIO_PIN_12, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D36/PA12	USB_DP USART6_RX 	M12 AF */
    {GPIOA, GPIO_PIN_11, NO_ADC       , hTimer1,  TIM_CHANNEL_4 },	/*  D37/PA11	USB_DM USART6_TX 	M14 AF */
    {GPIOB, GPIO_PIN_12, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D38/PB12	SPI2_NSS			M16 */
    {GPIOB, GPIO_PIN_11, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D39/PB11	VCAPPower			M18 PWM-not working?*/
    {GPIOB, GPIO_PIN_2,  NO_ADC       , NO_PWM,   NO_PWM        },	/*  D40/PB2		BOOT1 !!			ML7 */
    {GPIOB, GPIO_PIN_1,  ADC_CHANNEL_9, hTimer3,  TIM_CHANNEL_4 },	/*  D41/PB1		GPIO 				M24 */
    {GPIOB, GPIO_PIN_15, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D42/PB15	SPI2_MOSI			M26 */
    {GPIOB, GPIO_PIN_14, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D43/PB14	SPI2_MISO			M28 */
    {GPIOB, GPIO_PIN_13, NO_ADC       , NO_PWM,   NO_PWM        },	/*  D44/PB13	SPI2_SCK			M30 */
    {GPIOC, GPIO_PIN_4,  ADC_CHANNEL_15, NO_PWM,  NO_PWM        }	/*  D45/PC4		GPIO				M34 */

  	// JTAG Single wire pins
	// {GPIOA, NULL,   NULL, 13, 0, ADCx},/* Dxx/PA13 	TMS	do not use	M13 */
	// {GPIOA, NULL,   NULL, 14, 0, ADCx},/* Dxx/PA14	TCK do not use	M15 */

	// sheepdoll -- not sure why this one is locked out?
	// {GPIOA, TIMER2, NULL, 15, 1, ADCx},/* Dxx/PA15 	TDI do not use	M17 */
	
	
} ;

#ifdef __cplusplus
}
#endif

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/* ----------------------------------------------------------------------------
 *     USART objects
 * ----------------------------------------------------------------------------*/

#ifdef USE_USART1
UARTClass Serial1(&huart1, USART1_IRQn, 0, USART1);
void Tx1_Handler(void){
  Serial1.TxHandler();
}
void Rx1_Handler(void){
  Serial1.RxHandler();
}
#endif

#ifdef USE_USART2
UARTClass Serial2(&huart2, USART2_IRQn, 1, USART2);
void Tx2_Handler(void){
  Serial2.TxHandler();
}
void Rx2_Handler(void){
  Serial2.RxHandler();
}
#endif

#ifdef USE_USART3
UARTClass Serial3(&huart3, USART3_IRQn, 2, USART3);
void Tx3_Handler(void){
  Serial3.TxHandler();
}
void Rx3_Handler(void){
  Serial3.RxHandler();
}
#endif

#ifdef USE_USBSerial
//uint8_t CDC_RxBuffer[CDC_RX_DATA_SIZE];
//uint8_t CDC_TxBuffer[CDC_TX_DATA_SIZE];

//RingBuffer USB_rx_buffer;
//USBSerial Serial(CDC_RxBuffer, CDC_TxBuffer);
USBSerial Serial;

void USBSerial_Tx_Handler(uint8_t *data, uint16_t len){
  Serial.CDC_TxHandler();
}

void USBSerial_Rx_Handler(uint8_t *data, uint16_t len){
  Serial.CDC_RxHandler(data, len);
}

void StartUSBSerial (void){
  Serial.begin(9600);
}
#endif

