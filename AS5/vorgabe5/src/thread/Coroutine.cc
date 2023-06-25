#include "thread/Coroutine.h"
#include "sync/Monitor.h"


/* Diese Funktion hat nur die Aufgabe
    * den Rumpf der uebergebenen Coroutine aufzurufen
    * und nach der Rueckkehr exit() aufzurufen,
    * um die Termination des Rumpfes bekanntzugeben.
    * Diese Prozedur dient so als eine Bruecke zwischen der
    * nicht objektorientierten und der objektorientierten Welt
    * Beachte, das "startup" als "static deklariert ist
    * und deshalb keinen impliziten "this"-Zeiger uebergeben bekommt.
    */
void Coroutine::startup(Coroutine* obj){
    //cpu.enableInterrupts(); // fuer die Interrupts
    monitor.leave();
    obj->body(); // wird die Body fuer Coroutine erstellt
    obj->exit();  // wird die Coroutine beendet
}

/* Aufsetzen einer neuen Coroutine.
    * Der Parameter "tos" (top of stack) ist der
    * initiale Stackpointerwert fuer die neue Coroutine
    * ACHTUNG: tos kann NULL sein (siehe Constructor)!
    */
void Coroutine::setup(void* tos){
    if(tos==0){return;}
    else{
        CoroutineStack *stack = ((CoroutineStack*) tos); // 48 bytes 384 bits
        stack->edi=0;
        stack->esi=0;
        stack->ebx=0;
        stack->ebp=0;

        stack->coroutine = &startup; // Zeiger auf startup 
        stack->adress_ret= 0;
        stack->coroutine_obj=this;
        this->sp=stack;


    }

}
