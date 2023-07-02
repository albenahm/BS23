#include "system/Console.h"
#include "device/Keyboard.h"


Console::Console(InputChannel& input, OutputChannel& output): input(input),output(output),semaphore(1){

}

/** 	Konsole reservieren
 */
void Console::attach(){
    semaphore.wait();
}

/** 	Konsole wieder freigeben
 */
void Console::detach(){
    semaphore.signal();
}


/** 	Daten auf der Console ausgeben
 */
int Console::write(const char* data, int size){
    return output.write(data,size);
}


/** 	Jedes von der Tastatur eingelesene Zeichen
 * 	soll auf dem Bildschirm dargestellt werden (Echo Funktion!)
 * 	Wenn ein '\n' erkannt wurde oder bereits "size" Zeichen
 *	gelesen wurden, ist eine Zeile zuende und read() kehrt zurueck.
*	Alle gelesenen Ascii-zeichen sind in den Puffer einzutragen
*	und zaehlen als gueltiges Zeichen!
*/
int Console::read(char *data, int size){
    KernelLock lock;
    int count=0;

    while (size>count)
    {
        char buchstabe=read(); // lese die Buchstabe
        data[count++]=buchstabe; // speicher in data Buffer
        output.write(buchstabe); // liefere Buchstabe zu Bildschirm
        if(buchstabe=='\n'){
                break;
        }
    }
    return count;
    

}

/** 	Liefert das n�chste Zeichen aus dem Eingabepuffer zur�ck.
 */
char Console::read(){
    
    //unsigned char val= keyboard.read().getValue();
    char val;
    input.read(&val,1);
    return val;

}
