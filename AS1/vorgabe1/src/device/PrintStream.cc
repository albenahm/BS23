#include "device/CgaScreen.h"
#include "device/CgaChannel.h"
#include "device/CgaAttr.h"
#include "io/OutputChannel.h" 
#include "io/PrintStream.h"

using namespace PrintStream;

private:
    enum Base{
      BINARY=2;
      DECIMAL=10;
      HEX=16;
    }
public:

PrintStream(OutputChannel* chan);

PrintStream(OutputChannel& chan);

// Ausgabe NUll-Byte terminierter String
void print(const char* str){
    

}
void print(char ch){

}

// Ausgabe String mit Zeilenvorschub
void println(const char* str){

}

//Zeilenvorschub
void println(){

}

//numerische Werte werden zur Basis base ausgegeben
// Basen 2,10 und 16
void print(int x, int base = DECIMAL){

}

void print(unsigned x, int base = DECIMAL){

}

//Zeigertypen zur Basis 16 ausgeben
void print(void* p){

}

private: 
    OutputChannel& channel;
    


