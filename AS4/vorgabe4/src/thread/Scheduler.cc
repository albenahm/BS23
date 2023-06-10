#include "thread/Scheduler.h"
#include "io/PrintStream.h"


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
    activate((Schedulable*) readylist.dequeue());

};
