#include "spiHandler.hpp"
#include "spi.h"
#include "cmsis_os2.h"

extern "C" {
	void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
	void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
	void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
};


void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
	if(hspi == &hspi1) {
		osThreadFlagsSet(SPIHandler::getHandlerId(), SPIHandler::txDoneFlag);
	}
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
	if(hspi == &hspi1) {
		osThreadFlagsSet(SPIHandler::getHandlerId(), SPIHandler::rxDoneFlag);
	}
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
	if(hspi == &hspi1) {
		osThreadFlagsSet(SPIHandler::getHandlerId(), SPIHandler::txDoneFlag);
		osThreadFlagsSet(SPIHandler::getHandlerId(), SPIHandler::rxDoneFlag);
	}
}