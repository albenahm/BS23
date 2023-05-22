#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

/* Verpacken des aktuellen Kontrollflusses als Thread.
* Wird nur f�r den Hauptkontrollfluss "main" ben�tigt.
* Es wird hier kein Stack initialisiert.
* Beachte das Activity wegen der Vererbungsbeziehung von
* Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
* aufgerufen werden.
*/
Activity:: Activity(){
    this->zustand = BLOCKED; // nicht sofort ausfuehrbar, warte auf wakeup
    this->activitat=0;
    scheduler.start(this);
}

/* Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
* da der Thread erst laufen darf, wenn der spezielle Konstruktor
* der abgeleiteten Klasse abgearbeitet ist. Die Aktivierung
* erfolgt von der abgeleiteten Klasse mittels "wakeup".
*/
Activity:: Activity(void* tos):Coroutine(tos){
    this->zustand = READY;
    this->activitat=0;
}

Activity:: ~Activity(){
    scheduler.kill(this); // terminierung
}

	/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
	 */
	void Activity::sleep(){
        scheduler.suspend();// Unterbrechung der laufenden Prozess
    }

	/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
	 */
	void Activity::wakeup(){
	if(this->isBlocked()){
        this->zustand=READY;
        scheduler.schedule(this);// in ready list gebracht
    }}

	/* Diese Aktivitaet gibt die CPU vorruebergehend ab.
	 */
	void Activity::yield(){
        scheduler.reschedule(); // neuer Plan
    }

	/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
	 * auf die Beendigung wartende Aktivit�t geweckt werden.
	 */
	void Activity::exit(){
        if(this->activitat != 0){
        	this->activitat->wakeup();
        	this->activitat=0;
        } // wenn Aktinitat nicht leer dann aufwachen
        scheduler.exit(); // schliesen 
        
    }

	/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
	 * Prozess auf dem join aufgerufen wird beendet ist. Das
	 * Wecken des wartenden Prozesses �bernimmt exit.
	 */
	void Activity::join(){
        Activity* aktuellProzess=(Activity*) scheduler.active();// acktive Prozess in einer lokal Variable 
        //Es existiert eine Aktivität und nicht derselbe laufende Prozess.
        this->activitat=(Activity*) scheduler.active();
        while(!(this->isZombie())&& this !=aktuellProzess){
            scheduler.suspend();// Unterbrechung der laufenden Prozess
        }
        
    }
