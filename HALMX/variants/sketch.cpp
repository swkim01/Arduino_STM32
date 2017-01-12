#define HAL 1
#if HAL
#if defined(__STM32L0__)
#include "stm32l0xx_hal.h"
#elif defined(__STM32L1__)
#include "stm32l1xx_hal.h"
#elif defined(__STM32L4__)
#include "stm32l4xx_hal.h"
#elif defined(__STM32F1__)
#include "stm32f1xx_hal.h"
#elif defined(__STM32F2__)
#include "stm32f2xx_hal.h"
#elif defined(__STM32F3__)
#include "stm32f3xx_hal.h"
#elif defined(__STM32F4__)
#include "stm32f4xx_hal.h"
#elif defined(__STM32F7__)
#include "stm32f7xx_hal.h"
#endif
#else
#include "Arduino.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

void setup() {
  // put your setup code here, to run once:
#if HAL
  GPIO_InitTypeDef gpio;

  __GPIOC_CLK_ENABLE();
  gpio.Pin = GPIO_PIN_13;
#if 0
  gpio.Mode = GPIO_MODE_INPUT;
#else
  gpio.Mode = GPIO_MODE_IT_FALLING;
#endif
  gpio.Pull = GPIO_PULLUP;
#if defined(__STM32L0__) || defined(__STM32L4__) || defined(__STM32F4__) || defined(__STM32F2__) || defined(__STM32F7__)
  gpio.Speed = GPIO_SPEED_FAST;
#else
  gpio.Speed = GPIO_SPEED_HIGH;
#endif
  HAL_GPIO_Init(GPIOC, &gpio);

  /* Enable and set EXTI lines 15-10 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
#else
  pinMode(13, OUTPUT);
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
#if HAL
  //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  /* Insert delay 100 ms */
#if 0
  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
  }
  HAL_Delay(100);
#endif

#else
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
#endif
}

#if HAL
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_13) {
    /* Toggle LED1 */
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  }
}

/**
  * @brief  This function handles external lines 15 to 10 interrupt request.
  * @param  None
  * @retval None
  */
extern "C" void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}
#endif

#ifdef __cplusplus
}
#endif
