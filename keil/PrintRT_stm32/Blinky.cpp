/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>

#include "main.h"
extern "C" {

}
#include "RTE_Components.h"             /* Component selection */
#include "stm32f0xx_hal.h"              /* Keil::Device:STM32Cube HAL:Common */

// Main stack size must be multiple of 8 Bytes
#define APP_MAIN_STK_SZ (512U)
uint64_t app_main_stk[APP_MAIN_STK_SZ / 8];
const osThreadAttr_t app_main_attr = {
  .stack_mem  = &app_main_stk[0],
  .stack_size = sizeof(app_main_stk)
};

static volatile uint32_t delay_val = 500U;

static osThreadId_t tid_thrLED;                /* Thread id of thread: LED */
static osThreadId_t tid_thrBUT;                /* Thread id of thread: BUT */


/*----------------------------------------------------------------------------
  thrLED: blink LED
 *----------------------------------------------------------------------------*/
__NO_RETURN static void thrLED(void *argument) {



  (void)argument;

  for (;;) {
    osThreadFlagsWait(0x0001U, osFlagsWaitAny ,osWaitForever);
    //LED_On(led_num);                                           /* Turn specified LED on */
    osThreadFlagsWait(0x0001U, osFlagsWaitAny ,osWaitForever);
    //LED_Off(led_num);                                          /* Turn specified LED off */


  }

}



/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
__NO_RETURN void app_main (void *argument) {

  (void)argument;
                                     /* initalize Buttons */


  for (;;) {}
}
