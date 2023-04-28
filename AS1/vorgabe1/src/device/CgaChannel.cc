#include "device/CgaScreen.h"
#include "device/CgaChannel.h"
#include "device/CgaAttr.h"
#include "io/OutputChannel.h"

using namespace CgaChannel;

/*
* initiale die Ausgabekanal
*/
CgaChannel(){
    this->setAttr(CgaAttr());
}

/*
*initiale die Ausgabekanal mit bestimmten Attributen
*/
CgaChannel(const CgaAttr& attr){
    this->setAttr(attr);

}

// Die von OutputChannel deklarierte Ausgaberoutine
int write(const char *data, int size){
    for(int i=0;i<=size;i++){
        this->show(data[i]);
    }

    return size;
}

// Bluescreen mit eigener Fehlermeldung
virtual void blueScreen(const char* error){

    CgaAttr fehler;
    fehler.getBackground(CgaAttr::BLUE);
    this->attr.setAttr(fehler);

    // Zeilen mal Spalten
    for(int i=0;i<2000;i++){
        this->screen[i].setChar(' ');
        this->screen[i].setAttr(fehler);
    }

    setCursor(0,0);

    // wenn der fehler nicht null ist
    while (*error)
    {
        show(*error,fehler);
        (char)error++;
    }
    
}