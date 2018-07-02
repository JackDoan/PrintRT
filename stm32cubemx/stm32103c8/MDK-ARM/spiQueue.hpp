#ifndef __SPIQ_H
#define __SPIQ_H

#include "Thread.hpp"
#include "cmsis_os2.h"

typedef union {
	uint32_t l;
	uint8_t byte[4];
} word_t;

typedef struct __spiTransaction_s {
	uint8_t msg[5];
	uint8_t rxBuf[5];
	flag_t flag;
	bool done;
} spiMsg_t;

class SPIQueue {
	public:
		SPIQueue();
		~SPIQueue();
		void push(spiMsg_t* in);
		static spiMsg_t buildMsg(char* msg, char* rxBuf, uint32_t len, uint32_t flagToSend);
		osMemoryPoolId_t getPool() { return pool; }
	private:
		const int numQueueObjs = 10;
		osMutexId_t queueMutex;
		osMessageQueueId_t queue;
		osMemoryPoolId_t pool;
};



#endif