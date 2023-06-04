#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "interrupts/InterruptGuardian.h"
#include "device/PIC.h"
#include "device/Clock.h"
#include "interrupts/Gate.h"
#include "interrupts/SpuriousGate.h"
#include "device/CPU.h"

CPU cpu;
PIC pic;
InterruptGuardian interruptGuardian;
Clock clock(1000);


ActivityScheduler scheduler; 

int main() {

	cpu.enableInterrupts();
	while(1){

	}

}
