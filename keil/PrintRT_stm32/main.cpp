extern "C" {
	#include "main.h"
}

void os_main() {
	osKernelInitialize();  /* Initialize CMSIS-RTOS2 */
	//todo create threads
	osKernelStart(); //start the kernel
	for(;;) { } //loop forever; kernel should never stop
}
