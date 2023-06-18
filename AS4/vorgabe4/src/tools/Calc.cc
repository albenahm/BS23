#include "tools/Calc.h"
#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor
#include "device/Keyboard.h" // ermöglicht Eingaben durch Tastatur
#include "io/PrintStream.h" // ermöglicht Linefeeds und Ausgabe von Zahlen

extern CgaChannel cga;
extern PrintStream out;
extern Key key;

Calculator::Calculator()
{
    init();
}

Calculator::Calculator(void* sp)
    : Activity(sp)
{
    init();
    wakeup();
}

void Calculator::init()
{
    clearBuffer();
    cga.clear();
}

void Calculator::body()
{	
	Key key;
	do{
		key=keyboard.read();//liefert ein zeichen aus dem Tastaturpuffer
		char value;
		value = key.getValue();
		if(key.isAscii()){// getValue liefert eine Zahl oder den Buchstaben?

			if( (((int)value) == 32) || ((((int)value) <= 43) && (((int)value) >= 40)) || (((int)value) == 45) ||  ((((int)value) <= 57) && (((int)value) >= 47)) || ((((int)value) <= 70) && (((int)value) >= 65)) || ((((int)value) <= 102) && (((int)value) >= 97)) || (((int)value) == 120) || (((int)value) == 37)){//32 Space , 40-43 (Klammer auf,zu und Plus), 45 Minus, 47 geteilt, 48-57 0-9, 65-70 A-F, 97-102 a-f, 120 x und 37 für Prozentzeichen %

				insert(value);
				moveRight();
			}
			if((((int)value) == 10)){//enter Taste
				enter();	
			}
			if((((int)value) == 8)){//loesch Taste
				loesche();
				moveLeft();
			}
		}
		else{
			switch(((int)value)){
			//case 79 ://enter , vielleicht END gemeint?
			//	enter();
			//	break;
			case 75:// links
				moveLeft();
				break;
			case 77://rechts
				moveRight();
				break;
			default:
				break;
			}
		}
	}
	while(((int)key.getValue()) != 27);
	out.println();
	out.print("ENDE");
}

/* Eigene Methode um Zeichen zu löschen und neu schreiben zu können (ohne Zeilenumbruch)
*/

void Calculator::loesche(){

	int stelle;//Stelle im Buffer
	cga.getCursor(stelle,row); // Richtige Zelle ausfindig machen
	if(stelle !=0){
		buffer[stelle-1] = 32; // Vor dem Cursor das soll gelöscht werden, also leer machen mit 32 (Leerzeichen)
		// Alles andere rückt nach
		for(int i=0; buffer[stelle] != 0;i++){
			int transfer = buffer[stelle-1];
			buffer[stelle-1]=buffer[stelle];
			buffer[stelle]= transfer;
			stelle++;
		}
	}
	renderBuffer();
}


void Calculator::insert(char c)

{
	int stelle;//Stelle im Buffer
	cga.getCursor(stelle,row);
	bool nichtleer = true;// boolwert fuer unsere While-Schleife
	char transfer;// wird genutzt falls ein Wert an der Stelle steht, an der eingefuegt wird

	while (nichtleer){
	
		if(buffer[stelle] != 0){
			// Das Zeichen das gerade an der Stelle steht auf c setzen und das was auf c steht an diese Stelle in den Buffer
			transfer = buffer[stelle];//char an der Stelle
			buffer[stelle] = (int)c;
			c = transfer;
			
			if((EXPR_SIZE_MAX+1) == (stelle+1)){// falls der buffer an Stelle 79 ist und weiterschreiben soll wird das Zeichen was geschoben wird verworfen
				nichtleer = false;
			}
			stelle++;
		}
		else{
			buffer[stelle] = (int) c;
			nichtleer = false;

		}

	}
	//buffer[0] = 49;
	//buffer[1] = 43;
	//buffer[2] = 49;
	renderBuffer();//?
}



void Calculator::enter()

{	
	unsigned code;
	// return endweder Null (Berechnung erfolgreich) oder Fehlercode
	// result gibt den Wert raus
	code = interp.eval(buffer,result);
	if(code == 0){
		// Ergebnis ausgabe
		out.println();
		out.print("= ");
	 	out.print(result);
	}
	else{
		// Fehlercode ausgabe 
		out.println();
		printErrorMsg(code);
	}

	clearBuffer();
	// neue Zeile Cursor platzieren
	out.println("");
}

void Calculator::moveLeft()
{
	// Cursor Standpunkt holen
	cga.getCursor(column,row);
	// Darf sich nicht ueber den linken Rand hinaus bewegen
	if(column != 0){
		column--;
		cga.setCursor(column,row);
	}
}



void Calculator::moveRight()
{	
	// Cursor Standpunkt holen
	cga.getCursor(column,row);
	// Darf sich nicht ueber den rechten Rand hinaus bewegen
	if(column != 31){
		column++;
		cga.setCursor(column,row);
	}
}



void Calculator::renderBuffer()
{
    // Cursor sichern
    // column und row schon in header
    //int column, row;
    cga.getCursor(column, row);
    // Zeile schreiben
    cga.setCursor(0, row);
    cga.write(buffer, EXPR_SIZE_MAX);
    // Cursor wiederherstellen
    cga.setCursor(column, row);
}

void Calculator::clearBuffer()
{
    // Alle Zeichen nullen und Null-Byte hinter der höchsten Stelle setzen
    for (unsigned i=0; i<=EXPR_SIZE_MAX; ++i)
        buffer[i] = 0;
}
 /* Fehlermeldungen */
void Calculator::printErrorMsg(unsigned code)
{
    switch (code) {
    case Interpreter::UNEXP_EOT:
        out.print("Error: Unexpected end of expression!");
        break;

    case Interpreter::UNEXP_SYMBOL:
        out.print("Error: Unexpected symbol!");
        break;

    case Interpreter::ARITHM_ERROR:
        out.print("Error: Arithmetic error!");
        break;

    case Interpreter::BAD_BUFFER:
        out.print("Error: Invalid buffer!");
        break;

    default:
        break;
    }
}
