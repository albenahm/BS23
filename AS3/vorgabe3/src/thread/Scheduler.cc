#include "thread/Scheduler.h"
#include "io/PrintStream.h"
#include "device/CgaChannel.h"

extern CgaChannel cga;
extern PrintStream out;

//Einfuegen in Ready Liste
void Scheduler::schedule(Schedulable* sched){
    
    IntLock lock;
    readylist.enqueue(sched);//Objekt schon erstellt in header(void Methode)
};
//Entfernen eines Elements aus der Ready Liste
void Scheduler::remove(Schedulable* sched){
    
    IntLock lock;
    readylist.remove(sched);
};
//Aktiviert das vorderste Element
void Scheduler::reschedule(){
    
    IntLock lock;
    cga.setCursor(40,0);
    out.print("Scheduler !");
    activate((Schedulable*) readylist.dequeue());

};
