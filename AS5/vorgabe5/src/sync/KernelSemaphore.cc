#include "sync/KernelSemaphore.h"
#include "system/Thread.h"

		/*
    * hier wird gepruefft, ob Zaehler echt grosser als 0 dann wird er dekrimentiert, sonst
    * der laufende Prozess auf sleep gesetzt
    */
    void KernelSemaphore::wait(){
        if(zaehlerSemaphore > 0){ //Signalevorhanden
            zaehlerSemaphore--; //Signalevorhanden
        }else{
            Activity* aktuellAct= (Activity*) scheduler.active(); //hole aktuelle Aktivitaet
            sleepers.enqueue(aktuellAct);// in queue einfuegen
            aktuellAct->sleep();// schlafen
        }

    }

	/*
    * hier wird die geschlaffenen Aktivitaeten aufgewacht, wenn es keine gibt,
    * dann erhoehe die Zeahler um eins 
    */
    void KernelSemaphore::signal(){
            Activity* aktuellAct= (Activity*) sleepers.dequeue(); //hole aktuelle Aktivitaet

        if(aktuellAct != 0){
                aktuellAct->wakeup(); // wartender Prozess aufwache
        }else{
            zaehlerSemaphore++; // schlaeft kein Prozess, so erhoehe counter um eins
        }

    }