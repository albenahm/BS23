#ifndef CgaScreen_h
#define CgaScreen_h

#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"

/*
 * CgaScreen:	Diese Klasse ist der Softwareprototyp fuer den
 *		CGA-Bildschirm
 *		
 *      Hier soll es ausschliesslich um die Kontrolle der Hardware
 *      gehen. Komplexere Aufgaben koennen in den erbenden Klassen
 *      implementiert werden.
 */


class CgaScreen {

private:

	// Die I/O-Ports des Grafikcontrollers
	enum Ports  {
		indexPort=0x3d4,
		dataPort=0x3d5
	};

	// Die Kommandos zum Cursor setzen
	enum Cursor {
		High=14,
		LOW=15
	};

	// Die Adresse des Video RAMs
	enum Video  {
		Offset_0=0xb8000
	};

public:
	// Die Bildschirmdimensionen
	enum Screen {
		ROWS = 25,
		COLUMNS = 80
	};

	// Standardattribute waehlen und Bildschirm loeschen
	CgaScreen();

	// Angegebene Attribute setzen und Bildschirm loeschen
	explicit CgaScreen(CgaAttr attr);

	// Loeschen des Bildschirms
	void clear ();

	// Verschieben des Bildschirms um eine Zeile
	void scroll();

	// Setzen/Lesen der globalen Bildschirmattribute
	void setAttr(const CgaAttr& attr)
	{
		this->attr=attr;
	}

	void getAttr(CgaAttr& attr)
	{
		attr=this->attr;
	}

	// Setzen/Lesen des HW-Cursors
	void setCursor(int column, int row);
	void getCursor(int& column, int& row);


	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit angegebenen Bildschirmattributen
	void show(char ch, const CgaAttr& attr);

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit aktuellen Bildschirmattributen
	void show(char ch)
	{
		show(ch,this->attr);
	}


protected:

	CgaAttr attr;
	IOPort8 index;
	IOPort8 data;
	CgaChar* screen;
};

#endif
