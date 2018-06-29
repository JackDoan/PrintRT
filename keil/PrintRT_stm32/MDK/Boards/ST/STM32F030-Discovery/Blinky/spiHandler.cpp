#include "Thread.hpp"
#include "cmsis_os2.h"

#include "stm32f0xx_hal.h"
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi1_rx;
extern DMA_HandleTypeDef hdma_spi1_tx;
extern DMA_HandleTypeDef hdma_spi2_rx;
extern DMA_HandleTypeDef hdma_spi2_tx;

class SPIHandler {
	public:
		SPIHandler() {
			
		}
	
};