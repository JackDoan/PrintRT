#include "spiQueue.hpp"
#include "ScopedLock.hpp"

SPIQueue::SPIQueue() {
	queueMutex = osMutexNew(&ScopedLock::defaultMutexAttr);
	queue = osMessageQueueNew(numQueueObjs, sizeof(spiMsg_t*), nullptr);
	pool = osMemoryPoolNew(numQueueObjs, sizeof(spiMsg_t), nullptr);
}

void SPIQueue::push(spiMsg_t* in) {
	osMessageQueuePut(queue, in, osPriorityNormal, osWaitForever);
	//auto lock = ScopedLock(queueMutex);
}

