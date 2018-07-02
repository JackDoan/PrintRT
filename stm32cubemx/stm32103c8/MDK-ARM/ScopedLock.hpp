#ifndef __SCOPED_LOCK_H
#define __SCOPED_LOCK_H

#include "cmsis_os2.h"

class ScopedLock {
	public:
		ScopedLock(const osMutexId_t mutex);
		~ScopedLock();
		static const osMutexAttr_t defaultMutexAttr;
	private:
		const osMutexId_t lock;
};
#endif