#include "sync/KernelSemaphore.h"
#include "system/Thread.h"

	void KernelSemaphore::wait(){
        if(zaehlerSemaphore > 0){ //Signalevorhanden
            zaehlerSemaphore--; //Signalevorhanden
        }else{
            Activity* aktuellAct= (Activity*) scheduler.active(); //hole aktuelle Aktivitaet
            sleepers.enqueue(aktuellAct);// in queue einfuegen
            aktuellAct->sleep();// schlafen
        }

    }

	void KernelSemaphore::signal(){
            Activity* aktuellAct= (Activity*) sleepers.dequeue(); //hole aktuelle Aktivitaet

        if(aktuellAct != 0){
                aktuellAct->wakeup(); // wartender Prozess aufwache
        }else{
            zaehlerSemaphore++; // schlaeft kein Prozess, so erhoehe counter um eins
        }

    }