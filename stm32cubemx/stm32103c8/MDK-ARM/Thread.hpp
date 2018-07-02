#ifndef __THREAD_H
#define __THREAD_H

#include "cmsis_os2.h"
//note: do not directly use this class
//instead, compose it into another class
//that provides a threadFunc
class Thread {
	public:
		Thread(
			const osThreadFunc_t mThreadFunc,
			void* const arg = 0,
			const osPriority_t mPriority=osPriorityNormal, 
			const uint32_t mStackSize = defaultStackSize,
			void* const mStack = 0
			);
		
		~Thread();
		osThreadId_t getId() {
			return threadID;
		}
		bool run(void* arg = 0);
	private:
		static const int defaultStackSize;
		osThreadAttr_t attrs;
		osThreadId_t threadID;
		osThreadFunc_t threadFunc;
		
	private:
		static void defaultThreadFunc(void* arg);
};

typedef struct __flag_s {
	osThreadId_t thread;
	uint32_t flag;
} flag_t;

#endif