#include "thread/Scheduler.cc" // .cc ?
#include "thread/ActivityScheduler.h"
#include "thread/Dispatcher.h"

ActivityScheduler::ActivityScheduler(){}

/* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
void ActivityScheduler::suspend(){
    (scheduler.active())-> changeTo(Activity::BLOCKED); // derzeitiger Prozess wird geblockt (suspendiert)
	scheduler.reschedule();
    //scheduler.dispatch(scheduler.reschedule()); // Wechsel den Prozess
	//(scheduler.active())-> changeTo(Activity::RUNNING) // Aktiviere Prozess
};

/* Explizites Terminieren des angegebenen Prozesses. Der Prozesszustand ist korrekt zu setzen und der Prozess aus der Ready-Liste des Schedulers
 * zu entfernen. Falls der aktive Prozess zerstoert wird, ist dem naechsten lauffaehigen Prozess die CPU zuzuteilen.
 */
void ActivityScheduler::kill(Activity*){
	(scheduler.active())-> changeTo(Activity::ZOMBIE); // derzeitiger Prozess wird zerstört (Zombie)
	scheduler.remove(scheduler.active()); // Löschen des Prozesses aus der Ready-Liste
	scheduler.reschedule();
   // scheduler.dispatch(scheduler.reschedule()); // Wechsel den Prozess
	//(scheduler.active())-> changeTo(Activity::RUNNING) // Aktiviere Prozess
};





/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
void ActivityScheduler::exit(){
	(scheduler.active())-> changeTo(Activity::READY); // derzeitiger Prozess wird zerstört (Zombie)
	scheduler.reschedule();
   // scheduler.dispatch(scheduler.reschedule()); // Wechsel den Prozess
	//(scheduler.active())-> changeTo(Activity::RUNNING) // Aktiviere Prozess
}

/* Der aktive Prozess ist, sofern er sich nicht im Zustand Blocked oder Zombie befindet, wieder auf die Ready-Liste
 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle zu �bergeben.
 */
void ActivityScheduler::activate(Schedulable* to){

	if(((scheduler.active()).isBlocked || (scheduler.active()).isZombie)== false){ // Falls Prozess nicht im BLOCKED oder ZOMBIE- Zustand ist
		scheduler.schedule(scheduler.active()); //Setzen auf die Ready Liste im scheduler.cc
	}
    
	this->dispatch(to); // Wechsel den Prozess
	to-> changeTo(Activity::RUNNING) // Aktiviere Prozess
}