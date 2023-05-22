//#include "thread/Scheduler.cc" // .cc ?
#include "thread/ActivityScheduler.h"
#include "thread/Dispatcher.h"


/* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
void ActivityScheduler::suspend(){
    ((Activity *)active())-> changeTo(Activity::BLOCKED); // derzeitiger Prozess wird geblockt (suspendiert)
	this->reschedule();
    //scheduler.dispatch(scheduler.reschedule()); // Wechsel den Prozess
	//(scheduler.active())-> changeTo(Activity::RUNNING) // Aktiviere Prozess
};

/* Explizites Terminieren des angegebenen Prozesses. Der Prozesszustand ist korrekt zu setzen und der Prozess aus der Ready-Liste des Schedulers
 * zu entfernen. Falls der aktive Prozess zerstoert wird, ist dem naechsten lauffaehigen Prozess die CPU zuzuteilen.
 */
void ActivityScheduler::kill(Activity*  actActivity){
	actActivity-> changeTo(Activity::ZOMBIE); // derzeitiger Prozess wird zerstört (Zombie)
	(actActivity==(Activity *)active())?this->reschedule():remove(actActivity); // falls die act laeyt, dann fuehre die naechste aus der Liste aus.
	 // Löschen des Prozesses aus der Ready-Liste
	//scheduler.reschedule();
   // scheduler.dispatch(scheduler.reschedule()); // Wechsel den Prozess
	//(scheduler.active())-> changeTo(Activity::RUNNING) // Aktiviere Prozess
};





/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
void ActivityScheduler::exit(){
	Activity*  actActivity= (Activity*)this->active();// bekomme die aktuelle Aktivitaet
	actActivity-> changeTo(Activity::ZOMBIE);
	//kill(actActivity); // terminiere
	reschedule(); // hole die neue
   // scheduler.dispatch(scheduler.reschedule()); // Wechsel den Prozess
	//(scheduler.active())-> changeTo(Activity::RUNNING) // Aktiviere Prozess
}

/* Der aktive Prozess ist, sofern er sich nicht im Zustand Blocked oder Zombie befindet, wieder auf die Ready-Liste
 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle zu �bergeben.
 */
void ActivityScheduler::activate(Schedulable* to){
/*
	if(((scheduler.active()).isBlocked || (scheduler.active()).isZombie)== false){ // Falls Prozess nicht im BLOCKED oder ZOMBIE- Zustand ist
		scheduler.schedule(scheduler.active()); //Setzen auf die Ready Liste im scheduler.cc
	}
    
	this->dispatch(to); // Wechsel den Prozess
	to-> changeTo(Activity::RUNNING) // Aktiviere Prozess
	*/

Activity* actuellActivity = (Activity*) active();
Activity* nextActivity = (Activity*) to;



if(nextActivity !=0 ){
bool nextActivityNotReady = (nextActivity->isBlocked() || nextActivity->isZombie());
if(nextActivityNotReady){return;}// der naechste Prozess ist in der Lage auszufuehren, wenn nicht stoppt
	if((nextActivity!=actuellActivity)){
	actuellActivity->changeTo(Activity::READY);
	nextActivity->changeTo(Activity::RUNNING);
	scheduler.schedule(actuellActivity); // add zu ready liste
	dispatch(nextActivity);// Zeige auf denn aktelle laufenden Prozess
	}
}else{
	// wenn der laufende Prozess nicht laeuft, dann suche nach dem naechsten
	if(!(actuellActivity->isRunning())){ 

		
		
		nextActivity =  (Activity*) readylist.dequeue();
		
		if (nextActivity!=0)
		{
			nextActivity->changeTo(Activity::RUNNING);
			dispatch(nextActivity);// Zeige auf denn aktelle laufenden Prozess
		}

	}else{

		
	}
}
}
