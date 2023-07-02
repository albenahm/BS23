#include "thread/ActivityScheduler.h"
#include "thread/Dispatcher.h"
#include "interrupts/IntLock.h"
#include "device/Clock.h"
#include "device/CPU.h"
#include "sync/Monitor.h"



extern Clock clock; // Definiere eine Uhr
bool warten = true;// hilft bei suche nach naechstem Prozess


/* Suspendieren des aktiven Prozesses

	 * Der korrekte Ausfuehrungszustand ist zu setzen

	 * und danach der naechste lauffaehige Prozess zu aktivieren.

	 */

void ActivityScheduler::suspend(){

	//IntLock sicher;
    	((Activity *)active())-> changeTo(Activity::BLOCKED); // derzeitiger Prozess wird geblockt (suspendiert)
	this->reschedule();
};

/* Explizites Terminieren des angegebenen Prozesses. Der Prozesszustand ist korrekt zu setzen und der Prozess aus der Ready-Liste des Schedulers
 * zu entfernen. Falls der aktive Prozess zerstoert wird, ist dem naechsten lauffaehigen Prozess die CPU zuzuteilen.
 */

void ActivityScheduler::kill(Activity*  actActivity){

	//IntLock sicher;
	actActivity-> changeTo(Activity::ZOMBIE); // derzeitiger Prozess wird zerstört (Zombie)
	if (actActivity==(Activity *)active()){this->reschedule();}
	remove((Schedulable *)actActivity); // falls die act laeyt, dann fuehre die naechste aus der Liste aus.
};

/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */

void ActivityScheduler::exit(){

	//IntLock sicher;
	Activity*  actActivity= (Activity*)this->active();// bekomme die aktuelle Aktivitaet
	//actActivity-> changeTo(Activity::ZOMBIE);
	kill(actActivity);
	reschedule(); // hole die neue
}

/* Der aktive Prozess ist, sofern er sich nicht im Zustand Blocked oder Zombie befindet, wieder auf die Ready-Liste
 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle zu �bergeben.
 */

void ActivityScheduler::activate(Schedulable* to){

	Activity* actuellActivity = (Activity*) active();
	Activity* nextActivity = (Activity*) to;
	
	// wenn nextActivity nicht vorhanden ist
	if(nextActivity==0){
		if(actuellActivity->isRunning()){
			// wenn actuellActivity laeuft, brauchen wir nichts zu tun

		}else{

		//nun Suche nach die nächste Aktivität im Fall die akutelle nicht aktiv
			if(warten){

				while(nextActivity==0){
			
					if (! actuellActivity->isRunning()||(actuellActivity -> isBlocked()||(actuellActivity -> isZombie()))){
						//hole eine von Queue
						warten=false;
						nextActivity =  (Activity*) readylist.dequeue();
						//CPU::enableInterrupts(); //Zulassen der Interrupts
						monitor.leave();
						CPU::halt();// Anhalten der CPU bis zum naechsten Interrupt
						monitor.enter();
						//CPU::disableInterrupts();// Sperren der Interrupts.
					}
				}

				warten=true;

				//wenn die geholte Aktivität schon exisitiert ist, dann wird sie ausgeführt.
				if(nextActivity!=0){
					nextActivity->changeTo(Activity::RUNNING);
					dispatch(nextActivity);// Zeige auf denn aktelle laufenden Prozess
				}
			}
		}

	}else{
		// hier ist die nextActivity verfuegbar und muss die actuellActivity auf redylist gesetzt werden
		if(!(nextActivity->isZombie()||nextActivity->isBlocked())){
			
			//hier prüfe,ob die actuelle Aktivitä aktiv ist
			if(actuellActivity -> isRunning()&&(!(actuellActivity -> isBlocked())||(actuellActivity -> isZombie()))){
		
				//wenn ja setze aktuelle Aktivitaet auf bereit und in Queue(bereitliste)
				actuellActivity->changeTo(Activity::READY);
				scheduler.schedule(actuellActivity);
			}
			//In diesem Punkt haben wir die laufende Aktivität deaktiviert.
			nextActivity->changeTo(Activity::RUNNING);
			dispatch(nextActivity);// Zeige auf denn aktelle laufenden Prozess
		}else{
			// nextActivity nicht bereit 
			return;
		}
	}


	
}	

void ActivityScheduler::checkSlice(){

	Schedulable* actuellActivity = (Activity*) active();
	// quatum() ist das max Zeit bei dem gewechselt wird . ticks() liefert die aktuelle Zeit
	if(actuellActivity){
		if((actuellActivity->quantum()) <= (clock.ticks())){
			clock.setTicksZahl(0);
			reschedule();

		}
	}

}
