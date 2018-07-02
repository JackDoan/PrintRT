#include "stm32f10x.h"                  // Device header
#include "cmsis_os2.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "RTE_Components.h"             // Component selection

extern "C" {
	int app_main(void);
}

int app_main (void) {
	osKernelInitialize();  /* Initialize CMSIS-RTOS2 */
	//todo create threads
	osKernelStart(); //start the kernel
	for(;;) { } //loop forever; kernel should never stop
}
