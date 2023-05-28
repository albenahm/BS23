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



};



/* Explizites Terminieren des angegebenen Prozesses. Der Prozesszustand ist korrekt zu setzen und der Prozess aus der Ready-Liste des Schedulers

 * zu entfernen. Falls der aktive Prozess zerstoert wird, ist dem naechsten lauffaehigen Prozess die CPU zuzuteilen.

 */

void ActivityScheduler::kill(Activity*  actActivity){

	actActivity-> changeTo(Activity::ZOMBIE); // derzeitiger Prozess wird zerstört (Zombie)

	(actActivity==(Activity *)active())?this->reschedule():remove(actActivity); // falls actActivity laedt, dann fuehre die naechste aus der Liste aus.

};





/* Terminieren des aktiven Prozesses,

	 * und Wechsel zum naechsten lauffaehigen Prozess

	 */

void ActivityScheduler::exit(){

	Activity*  actActivity= (Activity*)this->active();// bekomme die aktuelle Aktivitaet

	actActivity-> changeTo(Activity::ZOMBIE);

	reschedule(); // hole die neue

}



/* Der aktive Prozess ist, sofern er sich nicht im Zustand Blocked oder Zombie befindet, wieder auf die Ready-Liste

 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle zu �bergeben.

 */

void ActivityScheduler::activate(Schedulable* to){



Activity* actuellActivity = (Activity*) active();

Activity* nextActivity = (Activity*) to;


//hier prüfe,ob die actuelle Aktivitä aktiv ist
if(actuellActivity -> isRunning()&&(!(actuellActivity -> isBlocked())||(actuellActivity -> isZombie()))){
	//wenn ja setze aktuelle Aktivitaet auf bereit und in Queue(ReadyList)
	actuellActivity->changeTo(Activity::READY);
	scheduler.schedule(actuellActivity);

}

//In diesem Punkt haben wir die laufende Aktivität deaktiviert.

//nun Suche nach der nächsten Aktivität im Fall, dass die akutelle nicht aktivn ist
while(nextActivity==0){
		
	if (! actuellActivity->isRunning()||(actuellActivity -> isBlocked()||(actuellActivity -> isZombie()))){
	//hole eine von Queue(Aktivitätsiste)
	nextActivity =  (Activity*) readylist.dequeue();}
		}


//wenn die geholte Aktivität schon exisitiert ist, dann wird sie ausgeführt.
if(nextActivity!=0){
nextActivity->changeTo(Activity::RUNNING);

dispatch(nextActivity);// Zeige auf den aktuell laufenden Prozess
}
	}

