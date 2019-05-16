/*
 * 004button_interrupt.c
 *
 *  Created on: 15 May 2019
 *      Author: ARUN
 */
#include <string.h>
#include "stm32f407xx.h"

#define HIGH            1
#define LOQ             0
#define BTN_PRESSED     HIGH

void delay()
{
    for (uint32_t i = 0 ; i < 500000/2 ; ++i);
}

int main(void)
{
    GPIO_Handle_t GpioLed, GpioBtn;
    memset(&GpioLed, 0, sizeof(GpioLed));
    memset(&GpioBtn, 0, sizeof(GpioBtn));

    GpioLed.pGPIOx = GPIOD;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeriClockControl(GPIOD, ENABLE);
    GPIO_Init(&GpioLed);

    GpioBtn.pGPIOx = GPIOA;
    GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_Init(&GpioBtn);

    // IRQ Configuration
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, NVIC_IRQ_PRIO15);
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);

    while(1);
}

void EXTI0_IRQHandler(void)
{
    delay(); // 200ms
    GPIO_IRQHandling(GPIO_PIN_NO_0); // Clear the pending event from EXTI line
    GPIO_ToggleOutPin(GPIOD, GPIO_PIN_NO_12);
}
