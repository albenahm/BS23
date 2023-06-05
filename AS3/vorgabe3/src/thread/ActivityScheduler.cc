#include "thread/ActivityScheduler.h"
#include "thread/Dispatcher.h"
#include "interrupts/IntLock.h"
#include "device/Clock.h"
#include "device/CPU.h"
#include "io/PrintStream.h"
#include "device/CgaChannel.h"

extern CgaChannel cga;
extern PrintStream out;


extern Clock clock; // Definiere eine Uhr


/* Suspendieren des aktiven Prozesses

	 * Der korrekte Ausfuehrungszustand ist zu setzen

	 * und danach der naechste lauffaehige Prozess zu aktivieren.

	 */

void ActivityScheduler::suspend(){

	IntLock lock;
    	((Activity *)active())-> changeTo(Activity::BLOCKED); // derzeitiger Prozess wird geblockt (suspendiert)
	this->reschedule();
};

/* Explizites Terminieren des angegebenen Prozesses. Der Prozesszustand ist korrekt zu setzen und der Prozess aus der Ready-Liste des Schedulers
 * zu entfernen. Falls der aktive Prozess zerstoert wird, ist dem naechsten lauffaehigen Prozess die CPU zuzuteilen.
 */

void ActivityScheduler::kill(Activity*  actActivity){

	IntLock lock;
	actActivity-> changeTo(Activity::ZOMBIE); // derzeitiger Prozess wird zerstört (Zombie)
	(actActivity==(Activity *)active())?this->reschedule():remove(actActivity); // falls die act laeyt, dann fuehre die naechste aus der Liste aus.
};

/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */

void ActivityScheduler::exit(){

	IntLock lock;
	Activity*  actActivity= (Activity*)this->active();// bekomme die aktuelle Aktivitaet
	actActivity-> changeTo(Activity::ZOMBIE);
	reschedule(); // hole die neue
}

/* Der aktive Prozess ist, sofern er sich nicht im Zustand Blocked oder Zombie befindet, wieder auf die Ready-Liste
 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle zu �bergeben.
 */

void ActivityScheduler::activate(Schedulable* to){
	IntLock lock;

	Activity* actuellActivity = (Activity*) active();
	Activity* nextActivity = (Activity*) to;

	//hier prüfe,ob die actuelle Aktivitä aktiv ist
	if(actuellActivity -> isRunning()&&(!(actuellActivity -> isBlocked())||(actuellActivity -> isZombie()))){
	//wenn ja setze aktuelle Aktivitaet auf bereit und in Queue(bereitliste)
		actuellActivity->changeTo(Activity::READY);
		scheduler.schedule(actuellActivity);
	}
	//In diesem Punkt haben wir die laufende Aktivität deaktiviert.
	//nun Suche nach die nächste Aktivität im Fall die akutelle nicht aktiv
	while(nextActivity==0){
		
		if (! actuellActivity->isRunning()||(actuellActivity -> isBlocked()||(actuellActivity -> isZombie()))){
	//hole eine von Queue(Aktivitätsiste
		CPU::disableInterrupts();
		//CPU::halt();
		nextActivity =  (Activity*) readylist.dequeue();
		CPU::enableInterrupts();
		
		
		}
	}
	//wenn die geholte Aktivität schon exisitiert ist, dann wird sie ausgeführt.
	if(nextActivity!=0){
	nextActivity->changeTo(Activity::RUNNING);
	dispatch(nextActivity);// Zeige auf denn aktelle laufenden Prozess
	}
}	

void ActivityScheduler::checkSlice(){

	IntLock lock;
	Schedulable* actuellActivity = (Activity*) active();
	// quatum() ist das max Zeit bei dem gewechselt wird . ticks() liefert die aktuelle Zeit
/*
	if((actuellActivity->quantum()) <= (clock.ticks())){
		this->reschedule();
		clock.setTicksZahl(0);
	}
*/

if((actuellActivity->quantum()!=0)){

	actuellActivity->quantum(actuellActivity->quantum()-1); // wenn Quantum bei akutellen Aktiviutat nicht 0 ist, dann wird um 1 reduziert
				cga.setCursor(25,0);
				out.print("          ");
				cga.setCursor(16,0);
				out.print(" ");
				out.print(actuellActivity->quantum());
				out.print(" ");
				out.print(clock.ticks());
				out.println();
}else{
				cga.setCursor(25,0);
				out.print("Erfuellt !");
	actuellActivity->quantum(actuellActivity->quantumOrginal()); // wird quantum wieder gesetzt im Bezug auf dem urspruglichen Wert

	reschedule();

}
}