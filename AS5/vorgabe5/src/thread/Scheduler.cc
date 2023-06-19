#include "thread/Scheduler.h"
#include "io/PrintStream.h"


//Einfuegen in Ready Liste
void Scheduler::schedule(Schedulable* sched){
    
    IntLock sicher;
    readylist.enqueue(sched);//Objekt schon erstellt in header(void Methode)
};
//Entfernen eines Elements aus der Ready Liste
void Scheduler::remove(Schedulable* sched){
    
    IntLock sicher;
    readylist.remove(sched);
};
//Aktiviert das vorderste Element
void Scheduler::reschedule(){
    
    IntLock sicher;
    activate((Schedulable*) readylist.dequeue());

};
