"thread/Scheduler.cc" // .cc ?
"thread/ActivityScheduler.h"
"thread/Dispatcher.h"

ActivityScheduler::ActivityScheduler(){}

/* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
void ActivityScheduler::suspend(){
    scheduler.sleep();
    scheduler.reschedule();
};

/* Explizites Terminieren des angegebenen Prozesses Der Prozesszustand ist korrekt zu setzen und der Prozess aus der Ready-Liste des Schedulers
 * zu entfernen. Falls der aktive Prozess zerstoert wird, ist dem naechsten lauffaehigen Prozess die CPU zuzuteilen.
 */
void ActivityScheduler::kill(Activity*){

}



/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
void ActivityScheduler::exit(){

}

/* Der aktive Prozess ist, sofern er sich nicht im Zustand Blocked oder Zombie befindet, wieder auf die Ready-Liste
 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle zu �bergeben.
 */
void ActivityScheduler::activate(Schedulable* to){


    readyList.enqueue(process) // Prozess noch nicht hier

}