#include "device/CgaScreen.h"
#include  "device/CgaAttr.h"
#include "io/IOPort.h"

/*
* Hier wird die standard Merkmale gesetzt, 
* wie fg=WHITE, Color bg=BLACK, bool blink=false
* aber  vorher wird die Buchsateb an Viedo RAM geliefert.
*/
CgaScreen::CgaScreen()::index(indexPort),data(dataPort){
    this->screen = (CgaChar*) Offset_0;
    CgaAttr standard = CgaAttr();
    this->setAttr(standard);
    clear();
}

/*
* Hier wird die bestimmten Merkmale gesetzt, 
* aber  vorher wird die Buchsateb an Viedo RAM geliefert.
* Am Ende wird die Buchstabe entfernet
*/
CgaScreen::CgaScreen(CgaAttr attr)::index(indexPort),data(dataPort){
    this->screen = (CgaChar*) Offset_0;
    this->setAttr(att);
    clear();
}

/*Hier werdenn alle Zeichen vom Bildschirm entfernet*/
void CgaScreen::clear(){

    CgaAttr standard= CgaAttr();
    char leer =' ';
    // 2000 da wir 25 Zeile und 80 Spalte haben
    for(int i= 0; i<2000;i++){
        this->screen[i].setChar(leer);
        this->screen[i].setAttr(standard);
    }

    //setze Zeige auf Anfang
    setCursor(0,0);
}

/*Hier wird dder Bildshirm um eine Zeile verschoben*/
void CgaScreen::scroll(){
unsigned int BildshirmGrosse = COLUMNS*ROWS; // 2000 Zellen
unsigned int BildschirmBytes = BildshirmGrosse * 2; // da jede Zelle aus 2 Bytes besteht.
unsigned int NeuBildschirm    = BildshirmGrosse -160; // da eine Zeile aus 160 Bytes (80 Attr)(80 Char) besteht.

for(int i = 0; i<NeuBildschirm;i++ ){

    this->sreen[i]= this->screen[i+COLUMNS]; // schiebe alle Char eine Zeile runter
}
// alle Bytes der Zeile (Differen zwischen BildshirmGrosse und NeuBildschirm) auf standard setzten
for(int i=NeuBildschirm;i<BildshirmGrosse;i++){

    if(i%2 !=0){

            this->screen[i].SetAttr(this->attr);
    }else{
            this->screen[i].SetChar((char) ' ');
    }
}
}

/*Der Zugriff auf die Steuerregister ist dagegen etwas aufwendiger: 
 *Um den Inhalt eines Steuerregisters vom Videocontroller abzufragen oder zu setzen,
 *muß zunächst über das Indexregister der Index des gewünschten Steuerregisters ausgegeben werden. 
 *Anschließend kann über das Datenregister auf das so adressierte Steuerregister zugegriffen werden.
 */
void setCursor(int column, int row){

    unsigned int position = column + row * COLUMNS; // hier wird die position bezueglich der Zahl der Zeile
    index = IOPort8(indexPort); // uebergebe die indexport zu Zugreifeen auf Kontrollregister
    index.write(LOW); // schreibe die LOW auf 
    data=IOPort8(dataPort);// uebergebe die dataport zu Zugreiffen auf Data Register
    data.write(position & 0xff); // 0xff repraestentiert 00000000000000000000000011111111. somit bekommt man die letzte 8 bits
    index.wirte(High);
    data.write((position >> 8)& 0xff);

}
void getCursor(int& column, int& row){
    index = IOPort8(indexPort); // uebergebe die indexport zu Zugreifeen auf Kontrollregister
    index.write(LOW); // schreibe die LOW auf 
    data=IOPort8(dataPort);// uebergebe die dataport zu Zugreiffen auf Data Register
    unsigned int low = data.read();// lese die niedere 8 bits
    index.write(High); // schreibe die LOW auf 
    data=IOPort8(dataPort);// uebergebe die dataport zu Zugreiffen auf Data Register
    unsigned int high = (data.read())<<8;
    short position = high| low;
    column= position % COLUMNS;
    row= (int) (position/ COLUMNS);
}

void show(char ch, const CgaAttr& attr){
    int column,row;
    getCursor(column,row); // bekomme die Zeile und Spalte
    char* position = (char*) (2*(column+row*COLUMNS)); // rechne die Position in Screen matrex
    position = position+ Offset_0; // gehe zum Startpunkte
    short chDecimal=(short) ch;

    if(ch == '\n' && row <= 24){
        setCursor(0,row+1); // gehe eine Zeile runter
        getCursor(column,row); // akulisiere die Werte von Cursor
    }else if (ch =='\r')
    {
        setCursor(0,row); // gehe yum Anfang der Zeile
        getCursor(column,row); // akulisiere die Werte von Cursor 
    }
    // jier kann man die Range von asc ii kontrollieren
    if(chDecimal > 31 && chDecimal<127){

        *position = ch;
        position++;
        this->setAttr(attr);
        *position = this->attr.getAttr();

        if(column<79){

            setCursor(column+1,row); // shiebe eine Zelle

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