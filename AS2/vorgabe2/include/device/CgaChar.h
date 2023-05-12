#ifndef CgaChar_h
#define CgaChar_h

#include "CgaAttr.h"

/*
 * CgaChar:
 * 
 *	Diese Klasse stellt den Prototyp eines
 *	Zeichens des Bildschirms dar.
 *	Dieses besteht aus darstellbarem Zeichen
 *	und Darstellungsattributen.
 */


class CgaChar {

public:

	// setzen des Zeichens
	void setChar(char c){
		this->cgaZeichen=c;
	}
	
	// auslesen des Zeichens
	char getChar(){
		return this->cgaZeichen;
	}
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr){
		this->attrMerk=attr;
	}
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr(){
		return this->attrMerk;
	}

private:
char cgaZeichen;
CgaAttr attrMerk;


};

#endif

