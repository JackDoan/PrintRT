#include "spiHandler.hpp"
#include "ScopedLock.hpp"
#include <cstring>
#include "spi.h"

SPIHandler::~SPIHandler() {
	//osMutexAcquire(queueMutex, osWaitForever);
	//osMutexDelete(queueMutex);
}

Thread SPIHandler::handlerThread = Thread(handlerFunc);

SPIHandler::SPIHandler() {
	if(handlerThread.getId() == nullptr) {
		handlerThread.run();
	}
}
	
//note: you are in charge of freeing the block returned by this function once you
//receive the flag!
spiMsg_t* SPIHandler::enqueue(const uint8_t addr, const uint32_t data, const uint32_t flag) {
	spiMsg_t* block;
	
	do {
		block = (spiMsg_t*)osMemoryPoolAlloc(queue.getPool(), osWaitForever);
	} while(block == nullptr); //make sure we get a block!
	
	word_t mdata;
	mdata.l = data;
	block->msg[0] = addr;
	memcpy( &(block->msg[1]), mdata.byte, 4); //copy our data into the packet
	memset( &(block->rxBuf[0]), 0, 5); //zero out the response section
	block->done = false;
	block->flag.thread = osThreadGetId(); //this is the thread our ISR will notify
	block->flag.flag = flag;
	
	queue.push(block); //put this block in the queue
	
	return block;
}

void SPIHandler::handlerFunc(void* arg) {
	while(1) {
		
	}
}

void SPIHandler::txNext() {
	//dequeue
	//hal_send?
}
