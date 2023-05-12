#ifndef CgaAttr_h
#define CgaAttr_h

/*
 * CgaAttr: 	Softwareprototyp fuer CGA Darstellungsattribute
 *		Hier braucht man Bitoperationen!
 *
 *		Da *alle* Operationen sehr einfach und kurz sind,
 *		duerft Ihr sie direkt in der Klasse
 *		als inline Methoden deklarieren.
 */

class CgaAttr {
private:
char attrMerk;

	enum AttrMaskAndShifts {
		Blinken=0b10000000,
		Hintergrund=0b01110000,
		Vorgrund=0b00001111,
		BlinkenMask=0b01111111,
		HintergrundMask=0b10001111,
		VorgrundMask=0b11110000
	};


public:
	/** 	Diese Aufz�hlung enth�lt die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		LIGHT_GRAY,
		GRAY,
		LIGHT_BLUE,
		LIGHT_GREEN,
		LIGHT_CYAN,
		LIGHT_RED,
		LIGHT_MAGENTA,
		YELLOW,
		WHITE
	};


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten f�r
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false)
	{
		setForeground(fg);
		setBackground(bg);
		setBlinkState(blink);
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
		this->attrMerk=this->attrMerk & VorgrundMask; // loesche alte Farbe mit und 
		this->attrMerk=this->attrMerk | col; // setze die neue Farbe mit oder
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
		int checkColor = (int) col;
		if(checkColor<=8){
			this->attrMerk=this->attrMerk & HintergrundMask;// losche alte Farbe mit und
			this->attrMerk=this->attrMerk | (col<<4); // setze die neue Farbe mit oder und schiebe die Farbe 4 bits, um Hintergrund bits zu erreichen
		}else{
			setBackground(Color::BLACK);//standard
		}
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
		this->attrMerk=this->attrMerk&BlinkenMask;// loesche die bits fuer Blinker
		this->attrMerk=this->attrMerk | (blink<<7);
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
		// Die Werte werden vom Paramenter entnommen.
		setBlinkState(attr.getBlinkState());
		setForeground(attr.getForeground());
		setBackground(attr.getBackground());
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
		Color f = (Color)(this->attrMerk & Vorgrund);
		return f;
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
		Color b = (Color) ((this->attrMerk&Hintergrund)>>4);// Setze alle bits ausser Hintergrund null und dann werfe die bits von Vorgrund
		return b;
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
		bool blinker = (bool) ((this->attrMerk&Blinken)>>7);// Setze alle bits auf null und dann werfen
		return blinker;
	}

	char getAttr(){
		return this->attrMerk;
	}

private:


};

#endif
