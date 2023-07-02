#ifndef BoundedBuffer_h
#define BoundedBuffer_h
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
#include "sync/KernelLock.h"


/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gef�llt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet f�r euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  m�sst.
 */
template<typename T,unsigned size>
class BoundedBuffer {
public:

	BoundedBuffer()
	{
		this->Zaehler=0;
		this->popPosition=0;
		this->pushPosition=0;
		this->aktuellActivity=0;

	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten m�ssen hier geweckt werden.
	 */
	void add(T& elem)
	{
		if(this->Zaehler< (int)size){
			buffer[pushPosition]=elem; // packe das Element in Buffer gemaess positionawert, wo dieser Wert in Zyklus geht 
			this->Zaehler++; // erhoehe der Zaehler um eins
			this->pushPosition=(this->pushPosition+1)% (int) size; // 
		}

		if(aktuellActivity !=0){ // falls es eine wartende Aktivitaet, dann wird sie aufgewacht
			this->aktuellActivity->wakeup();
			//this->aktuellActivity=0; // geloescht, um neue zu bestimmen

		}

		
	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{
		//IntLock sicher; // erlaube keine interrupts in diesem Block 

		// Wenn Buffer leer ist
		if(Zaehler==0){
			this->aktuellActivity=(Activity*) scheduler.active(); // hole die aktuelle Aktivitaet
			this->aktuellActivity->sleep(); // Suspendieren des aktiven Prozesses
		}

		this->Zaehler--; //reduziere Zaehler um eins 

		T ausgabe = buffer[popPosition]; // bestimme Ausgabe 
		this->popPosition=(this->popPosition+1)%(int) size; // bestimme die Popsition des Elements Rueckwaerts


		return ausgabe;


	}

	int getBufferZaeler(){
		return this->Zaehler;
	}

private:
	T buffer[size];
	int Zaehler; // Zaehler fuer hinzugefuegte Elemente
	int pushPosition;
	int popPosition;
	Activity* aktuellActivity; // die untergebrochene Aktivitaet 
};

#endif

