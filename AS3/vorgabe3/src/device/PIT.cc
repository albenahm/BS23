#include "device/PIT.h"
//#include<cmath>

/** Default-Konstruktor. Das Interval wird spaeter
     * mit der interval-Methode initialisiert */
PIT::PIT ():kontroll(CONTROL_PORT),data(DATA_PORT){

}

/** Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
     * ausgeloest wird */
PIT::PIT (int us):kontroll(CONTROL_PORT),data(DATA_PORT){
    interval(us); // Aufrufe Interval methode, um die Timer mit eingegebene Zahl aufzusetyen
}

/** Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
     * ausgeloest wird.
     * 
     * BEACHTE: Hier muss die Hardware korrekt programmiert werden.
     * Naeheres steht in der Web-Dokumentation.
     */
void PIT::interval (int us){

    int nsBasis = us* 1000; // umwandle Basis von ns in us 
    //int statt roundeven ?
    int tickzahlen = (nsBasis /TIME_BASE); //rechne die tick Anzahlen und speichere in short (16 bits)

    char lowByte= (char) tickzahlen; // da char nur 8 bit ist, wird die erste 8 bit genommen (low byte)
    char highByte= (char) tickzahlen>>8;// l;sche die erste 8 bits und so bekommt man High Byte

    kontroll.write(0b00110100); //0b 00 11 010 0 mit diesem Steuerwort stellt man die Zaeler 0 auf modus 2 auf und schreibt auf niederwertiges Zählerbyte und hoeherwertiges Zählerbyte  
    data.write(lowByte);
    //kontroll.write(0b00100100);
    data.write(highByte);
    
}
