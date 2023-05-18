//Einfuegen in Ready Liste
void schedule(Schedulable* sched){
    readyList.enqueue(sched);//Objekt schon erstellt in header(void Methode)
};
//Entfernen eines Elements aus der Ready Liste
void remove(Schedulable* sched){
    readyList.remove(sched);
};
//Aktiviert das vorderste Element
void reschedule(){
    activate(readyList.dequeue());//kann man das so verwenden . dequeue gibt einen return wert

};