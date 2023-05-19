#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

Activity:: Activity(){
    this->zustand = ZOMBIE;
    this->activitat=0;
    scheduler.start(this);
}

Activity:: Activity(void* tos){
    this->zustand = BLOCKED;
    this->activitat=0;
    this->Coroutine=tos;
}

Activity:: ~Activity(){
    scheduler.kill(this);
}

	/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
	 */
	void Activity::sleep(){
        scheduler.suspend();
    }

	/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
	 */
	void Activity::wakeup(){
        this->zustand=READY;
        scheduler.schedule(this);
    }

	/* Diese Aktivitaet gibt die CPU vorruebergehend ab.
	 */
	void Activity::yield(){
        scheduler.reschedule();
    }

	/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
	 * auf die Beendigung wartende Aktivit�t geweckt werden.
	 */
	void Activity::exit(){
        this->activitat != 0?this->activitat->wakeup();
        scheduler.exit();
        
    }

	/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
	 * Prozess auf dem join aufgerufen wird beendet ist. Das
	 * Wecken des wartenden Prozesses �bernimmt exit.
	 */
	void Activity::join(){
        Activity* aktuellProzess=(Activity*) scheduler.active();
        if(!(this->isZombie())&& this !=aktuellProzess){
            this->activitat=(Activity*) scheduler.active();
            scheduler.suspend();
        }
        
    }
