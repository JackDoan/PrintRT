#include "Thread.hpp"
#include "cmsis_os2.h"

const int Thread::defaultStackSize = 255;

Thread::Thread(
	const osThreadFunc_t mThreadFunc,
	void* const arg,	
	const osPriority_t mPriority, 
	const uint32_t mStackSize,
	void* const mStack
){
	threadFunc = mThreadFunc;
	attrs.cb_mem = nullptr;
	attrs.priority = mPriority;
	attrs.stack_mem = mStack;
	attrs.stack_size = defaultStackSize;
	threadID = nullptr;
	run(arg);
}

bool Thread::run(void* arg) { //true == success, false == failure
	if(threadID != nullptr) {
		threadID = osThreadNew(threadFunc, arg, &attrs);
		return !(threadID == nullptr);
	}
	else {
		return false;
	}
}

Thread::~Thread() {
	switch(osThreadGetState(threadID)) {
		case osThreadTerminated:
			//the thread is dead, don't kill it again
			break;
		case osThreadError:
		case osThreadBlocked:
		case osThreadInactive:
		case osThreadReady:
		case osThreadReserved:
		case osThreadRunning:
		default:
			osThreadTerminate(threadID);
			break;
	}
}

void defaultThreadFunc(void* arg) {
	for(;;) {
		__asm__("BKPT"); //this should never be called
		auto id = osThreadGetId();
	}
}