#include "ScopedLock.hpp"

const osMutexAttr_t ScopedLock::defaultMutexAttr = {
	nullptr,                          // human readable mutex name
	osMutexRobust | osMutexPrioInherit,    // attr_bits
	nullptr,                                     // memory for control block   
	0U                                        // size for control block
};

ScopedLock::ScopedLock(const osMutexId_t mutex) : lock(mutex) {
	osMutexAcquire(lock, osWaitForever);
}

ScopedLock::~ScopedLock() {
	osMutexRelease(lock);
}