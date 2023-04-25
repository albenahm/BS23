#ifndef CgaChar_h
#define CgaChar_h

#include "device/CgaAttr.h"

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
		return cgaZeichen;
	}
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr){
		attrMerk.setAttr(attr);
	}
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr(){
		return attrMerk;
	}

private:
char cgaZeichen;
CgaAttr attrMerk;


};

#endif

