#ifndef __SPIHANDLE_H
#define __SPIHANDLE_H

#include "Thread.hpp"
#include "cmsis_os2.h"
#include "spiQueue.hpp"

class SPIHandler {
	public:
		SPIHandler();
		~SPIHandler();
		spiMsg_t* enqueue(const uint8_t addr, const uint32_t data, const uint32_t flag);
		static spiMsg_t buildMsg(char* msg, char* rxBuf, uint32_t len, uint32_t flagToSend);
		static osThreadId_t getHandlerId() { return SPIHandler::handlerThread.getId(); }
		static const uint32_t txDoneFlag;
		static const uint32_t rxDoneFlag;
	private:
		static spiMsg_t* currentMsg;
		static SPIQueue queue;
		static Thread handlerThread;
		static void handlerFunc(void * arg);
		void txNext();
};



#endif