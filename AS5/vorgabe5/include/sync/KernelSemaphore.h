#ifndef KernelSemaphore_h
#define KernelSemaphore_h

#include "lib/Queue.h"


/**
 * KernelSemaphore: Semaphorenimplementation f�r kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */
class KernelSemaphore {
public:
	// Initialisierung des Zaehlers
	explicit KernelSemaphore(int count = 1)
	{
		this->zaehlerSemaphore=count;
	}

	void wait();
	void signal();

private:

int zaehlerSemaphore;
Queue sleepers;

};

#endif

