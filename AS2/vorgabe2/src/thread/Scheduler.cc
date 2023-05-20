#include "lib/Queue.h"
#include "thread/Scheduler.h"
#include "thread/ActivityScheduler.h"
#include "thread/Schedulable.h"

//Einfuegen in Ready Liste
void Scheduler::schedule(Schedulable* sched){
   this->readylist.enqueue(sched);//Objekt schon erstellt in header(void Methode)
};
//Entfernen eines Elements aus der Ready Liste
void Scheduler::remove(Schedulable* sched){
    this->readylist.remove(sched);
};
//Aktiviert das vorderste Element
void Scheduler::reschedule(){
   this->readylist.dequeue();
   scheduler.activate(this);

};
