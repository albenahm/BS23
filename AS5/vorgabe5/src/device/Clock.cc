#include "device/Clock.h"
#include "device/PIC.h"
#include "device/CPU.h"
#include "interrupts/InterruptVector.h"
#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
#include "device/CgaScreen.h"
#include "device/CgaChannel.h"
#include "io/PrintStream.h"


//extern CgaChannel cga;         // unser CGA-Ausgabekanal
//extern PrintStream out; 


/**	Spaetere Initialisierung...
 *	Hier ist nur im Konstruktor dafuer zu sorgen,
    *	dass sich Gate korrekt initialisieren kann
    */
Clock::Clock():Gate(Timer){

}

/**	Initialisierung des "Ticks" der Uhr
 *	Standardmaessig setzen wir das
    *	Uhrenintervall auf 20 Millisekunden
    *	und wir bekommen damit 50 Interrupts pro Sekunde
    *
    *	Zum Testen koennt Ihr bei Bedarf einen hoeheren Wert einstellen
    *	Weitere Hinweise zur Implementierung siehe "windup"
    */
Clock::Clock (int us):Gate(Timer),PIT(us){
    windup(us);
}

/**	Initialisierung des "Ticks" der Uhr
 * 	Die Einheit sind Mikrosekunden.
 * 	Hier ist der PIT geeignet zu initialisieren
 * 	und der PIT beim PIC anzustellen.
 */
void Clock::windup(int us){

    ticksZahl=0; // Initialisierung
    pic.enable(PIC::PIT);//melde pit bei pic an
    interval(us);// us an pit uebergeben und pit faenget zu zaehlen an
}

/** 	Der Interrupt-Handler fuer die Uhr.
 *	Hier ist der Interrupt am PIC zu bestaetigen
    *	und die Systemzeit zu aktualisieren.
    *	Die Systemzeit wird in Uhrenticks gemessen,
    *	Ihr muesst hier also nur mitzaehlen,
    *	wie oft die Uhr getickt hat.
    *
    *	Ueberpruefe zunaechst die Funktion des Timers
    *	indem Du jede Sekunde eine Ausgabe an der Bildschirmstelle (0,0)
    *	in Form eines rotierenden Propellers machst, der sich pro Sekunde
    *	ein kleines Stueck weiterdreht, wie der Sekundenzeiger einer Uhr.
    *	Der Propeller besteht aus der Zeichenfolge '/', '-', '\\', '|',
    *	d.h. nach 4 Sekunden ist eine komplette Umdrehung geschafft.
    *
    *	Achtung: Kommentiert alle anderen Ausgaben Eures Testprogrammes
    *	aus, sonst seht Ihr nichts!
    *
    *	Wenn der Uhrentest erfolgreich verlaufen ist, kommentiert
    *	den Propeller wieder aus und ruft stattdessen
    *	die "checkSlice" Methode des Schedulers auf,
    *	um diesen ggf. zum praeemptiven Rescheduling zu veranlassen.
    */

/*

void Clock::handle(){
    IntLock sicher; // spere Interrupts ab jetzt
    ticksZahl++;
    pic.ack(); // Interrupt am PIC zu bestaetigen
    scheduler.checkSlice();
    
      cga.setCursor(0,15);
      out.print(ticksZahl); 
      out.println();
      cga.setCursor(0,16);
      if(ticksZahl%4==0){out.print("\r/");}
      if(ticksZahl%4==1){out.print("\r-");}
      if(ticksZahl%4==2){out.print("\r\\");}
      if(ticksZahl%4==3){out.print("\r|");}
*/

/*Hier wird die handel Methode auf zwei methoden aufgeteilet
* prologue stellt die Vorbedingung dar oder was muss zuerst ausgefuert werden 
*/
bool Clock::prologue(){
    ticksZahl++;
    pic.ack(); // Interrupt am PIC zu bestaetigen
    return true;
}

// epilogue setlle die Nachbedingung dar oder was muss spaeter ausgefuehrt werden
void Clock::epilogue(){
    scheduler.checkSlice();
}

