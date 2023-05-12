#include "device/CgaScreen.h"
#include  "device/CgaAttr.h"
#include "io/IOPort.h"

/*
* Hier wird die standard Merkmale gesetzt, 
* wie fg=WHITE, Color bg=BLACK, bool blink=false
* aber  vorher wird der Buchstabe an Viedo RAM geliefert.
*/
CgaScreen::CgaScreen():index(indexPort),data(dataPort){
    this->screen = (CgaChar*) Offset_0;
    CgaAttr standard = CgaAttr();
    this->setAttr(standard);
    clear();
}

/*
* Hier werden die bestimmten Merkmale gesetzt, 
* aber vorher wird der Buchstabe an Viedo RAM geliefert.
* Am Ende wird der Buchstabe entfernt
*/
CgaScreen::CgaScreen(CgaAttr attr):index(indexPort),data(dataPort){
    this->screen = (CgaChar*) Offset_0;
    this->setAttr(attr);
    clear();
}

/*Hier werden alle Zeichen vom Bildschirm entfernt*/
void CgaScreen::clear(){

    CgaAttr standard= CgaAttr();
    char leer =' ';
    // 2000 da wir 25 Zeile und 80 Spalte haben und 25 * 80 = 2000
    for(int i= 0; i<2000;i++){
        this->screen[i].setChar(leer);
        this->screen[i].setAttr(standard);
    }

    //setze Zeige auf Anfang
    setCursor(0,0);
}

/*Hier wird der Bildschirm um eine Zeile verschoben*/
void CgaScreen::scroll(){
unsigned int bildschirmGroesse = COLUMNS*ROWS; // 2000 Zellen
unsigned int bildschirmBytes = bildschirmGroesse * 2; // da jede Zelle aus 2 Bytes besteht.
unsigned int neuBildschirm    = bildschirmBytes -160; // da eine Zeile aus 160 Bytes (80 Attr)(80 Char) besteht.

for(unsigned int i = 0; i<neuBildschirm;i++ ){

    this->screen[i]= this->screen[i+COLUMNS]; // schiebe alle Char eine Zeile runter
}
// alle Bytes der Zeile (Differenz zwischen bildschirmGroesse und neuBildschirm) auf Standard setzen
for(unsigned int i=neuBildschirm;i<bildschirmGroesse;i++){

    if(i%2 !=0){

            this->screen[i].setAttr(this->attr);
    }else{
            this->screen[i].setChar((char) ' ');
    }
}
}

/*Der Zugriff auf die Steuerregister ist dagegen etwas aufwendiger: 
 *Um den Inhalt eines Steuerregisters vom Videocontroller abzufragen oder zu setzen,
 *muß zunächst über das Indexregister der Index des gewünschten Steuerregisters ausgegeben werden. 
 *Anschließend kann über das Datenregister auf das so adressierte Steuerregister zugegriffen werden.
 */
void CgaScreen::setCursor(int column, int row){

    unsigned int position = column + row * CgaScreen::COLUMNS; // hier wird die Position bezueglich der Zahl der Zeile gesetzt
    index = IOPort8(indexPort); // uebergebe den Indexport zum Zugreifen auf die Kontrollregister
    index.write(LOW); // schreibe LOW drauf 
    
    data=IOPort8(dataPort);// uebergebe den Dataport zum Zugreifen auf Data Register
    data.write(position & 0xff); // 0xff repraesentiert 00000000000000000000000011111111, somit bekommt man die letzten 8 Bits
    index.write(High);
    data.write((position >> 8)& 0xff);

}
void CgaScreen::getCursor(int& column, int& row){
    
    index = IOPort8(indexPort); // uebergebe die Indexport zum Zugreifen auf Kontrollregister
    index.write(LOW); // schreibe LOW daauf 
    data=IOPort8(dataPort);// uebergebe den Dataport zu Zugreifen auf Data Register
    
    unsigned int low = data.read();// lese die niederwertigsten 8 Bits
    index.write(High); // schreibe High daauf 
    data=IOPort8(dataPort);// uebergebe die Dataport zum Zugreifen auf Data Register
    
    unsigned int high = (data.read())<<8;
    short position = high| low;
    column= position % COLUMNS;
    row= (int) (position/ COLUMNS);
}

void CgaScreen::show(char ch, const CgaAttr& attr){
    int column,row;
    getCursor(column,row); // bekomme Zeile und Spalte
    char* position = (char*) (2*(column+row*COLUMNS)); // rechne die Position in Screen matrex
    position = position+ Offset_0; // addiere zum Startpunkt
    short chDecimal=(short) ch; 

    if(ch == '\n' && row <= 24){
        setCursor(0,row+1); // gehe eine Zeile runter
        getCursor(column,row); // aktualisiere die Werte von Cursor
    }else if (ch =='\r')
    {
        setCursor(0,row); // gehe zum Anfang der Zeile
        getCursor(column,row); // aktualisiere die Werte von Cursor 
    }
    // hier kann man die Range von ASCII kontrollieren
    if(chDecimal > 31 && chDecimal<127){

        *position = ch; // ersetze den Wert der Zeiger
        position++; // um Attr zu ereichen
        this->setAttr(attr);
        *position = this->attr.getAttr();

        if(column<79){

            setCursor(column+1,row); // schiebe eine Zelle

        }else{

            if(row < 25){
                setCursor(0,row+1); // gehe Zeile runter
            }else{
                scroll();
                setCursor(0,25);
            }
        }

    }
    
}
