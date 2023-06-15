#include "tools/Calc.h"



#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor

#include "device/Keyboard.h" // ermöglicht Eingaben durch Tastatur

#include "io/PrintStream.h" // ermöglicht Linefeeds und Ausgabe von Zahlen



extern CgaChannel cga;

extern PrintStream out;



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

}



void Calculator::insert(char c)

{

	

}



void Calculator::enter()

{	

	unsigned code;

	// return endweder Null (Berechnung erfolgreich) oder Fehlercode

	// result gibt den Wert raus

	code = interp.eval(buffer,result);

	if(code == 0){

		// Ergebnis ausgabe

	 	out.print(result)

	}

	else{

		// Fehlercode ausgabe 

		(Calculator*) printErrorMsg(code);

	}

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

	if(column != 79){

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
