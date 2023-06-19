#include "io/OutputChannel.h" 
#include "io/PrintStream.h"

PrintStream::PrintStream(OutputChannel* chan): channel(*chan)
{
}

PrintStream::PrintStream(OutputChannel& chan): channel(chan)
{
}

// Ausgabe NUll-Byte terminierter String
void PrintStream::print(const char* str){

	int i=0;
	while(str[i] != '\0'){// Wir betrachten solange Zeichen vom String, solange kein '\0' als einzelnes char kommt
        	i++;
        }
        channel.write(str,i);
}

void PrintStream::print(char ch){

   channel.write(ch); // Wir geben ch einfach weiter...
}

// Ausgabe String mit Zeilenvorschub
void PrintStream::println(const char* str){

	int i= 0;
	while(str[i] != '\0'){   
        	i++;
      	}
      	channel.write(str,i);
    	channel.write('\n'); //Selbiges wie print(const char* str) nur mit \n
}

//Zeilenvorschub
void PrintStream::println(){

	this->channel.write('\n');// einfache new line Ausgabe
}

//numerische Werte werden zur Basis base ausgegeben
// Basen 2, 10 und 16
void PrintStream::print(unsigned int x, int base){

	switch(base){//Vorzeichen fuer 2,10,16
		case 2:
			print("0b");
			break;
		case 10:
			break;
		case 16:
			print("0x");
			break;
		default:
			{print("Nur 2,10,16 als base erlaubt");
			return;};//Nicht erlaubt
	}
	int max =32;
	char ergebnis [max];
	int y= 0;//Rest
	int i =-1;//zaehler
	if(x==0){
		channel.write('0');//Null in Ascii
		return;
	}
	while( x != 0){
		i++;
        	y = x % base;
        	x = (x-y) /base;
       		switch(y){ // Hier greifen wir ab, dass ein einstelliges Zeichen über den Dezimalwert von 9 gemäß Hexaschreibweise geschrieben werden kann und wandeln die Zahlen in Zeichen um
          		case 0: 
            			ergebnis[i] = '0';
            			break;
          		case 1: 
            			ergebnis[i] = '1';
            			break;
          		case 2: 
            			ergebnis[i] = '2';
            			break;
          		case 3: 
            			ergebnis[i] = '3';
            			break;
          		case 4: 
            			ergebnis[i] = '4'; 
            			break;
          		case 5: 
          	  		ergebnis[i] = '5'; 
            			break;
          		case 6: 
            			ergebnis[i] = '6';
            			break;
          		case 7: 
            			ergebnis[i] = '7';
            			break;
          		case 8: 
            			ergebnis[i] = '8';
            			break;
          		case 9: 
            			ergebnis[i] = '9';
            			break;
          		case 10: 
            			ergebnis[i] = 'A'; // bei 10 schreibe A
            			break;
          		case 11: 
          	  		ergebnis[i] = 'B'; //...
            			break;
          		case 12: 
            			ergebnis[i] = 'C';
            			break;
          		case 13: 
            			ergebnis[i] = 'D';
            			break;
          		case 14: 
            			ergebnis[i] = 'E';
            			break;
          		case 15: 
            			ergebnis[i] = 'F';
            			break;
          		default:
            			break;
            		}
        }
	while(i!=-1){//Ausgabe
		channel.write(ergebnis[i]);
		i--;
	}	
}

void PrintStream::print(int x, int base){

	int max =32;
	if(base!=2 && base!=10 && base!=16){
		print("Nur 2,10,16 als base erlaubt");
		return;
	}
	else{
		if(x<0){//Minuszeichen
		x = x*(-1);
		print('-');
		max--;
		}
		switch(base){//Vorzeichen fuer 2,10,16
		case 2:
			print("0b");
			break;
		case 16:
			print("0x");
			break;
		default:
			break;
		}
	}
	char ergebnis [max];
	int y= 0;//Rest
	int i =-1;//zaehler
	if(x==0){
		channel.write('0');//Null in Ascii
		return;
	}
	while( x != 0){
		i++;
        	y = x % base;
        	x = (x-y) /base;
       		switch(y){ // Hier greifen wir ab, dass ein einstelliges Zeichen über den Dezimalwert von 9 gemäß Hexaschreibweise geschrieben werden kann und wandeln die Zahlen in Zeichen um
          		case 0: 
            			ergebnis[i] = '0';
            			break;
          		case 1: 
            			ergebnis[i] = '1';
            			break;
          		case 2: 
            			ergebnis[i] = '2';
            			break;
          		case 3: 
            			ergebnis[i] = '3';
            			break;
          		case 4: 
            			ergebnis[i] = '4'; 
            			break;
          		case 5: 
          	  		ergebnis[i] = '5'; 
            			break;
          		case 6: 
            			ergebnis[i] = '6';
            			break;
          		case 7: 
            			ergebnis[i] = '7';
            			break;
          		case 8: 
            			ergebnis[i] = '8';

            			break;
          		case 9: 
            			ergebnis[i] = '9';
            			break;
          		case 10: 
            			ergebnis[i] = 'A'; // bei 10 schreibe A
            			break;
          		case 11: 
          	  		ergebnis[i] = 'B'; //...
            			break;
          		case 12: 
            			ergebnis[i] = 'C';
            			break;
          		case 13: 
            			ergebnis[i] = 'D';
            			break;
          		case 14: 
            			ergebnis[i] = 'E';
            			break;
          		case 15: 
            			ergebnis[i] = 'F';
            			break;
         		default:
            			break;
            		}
        }
	while(i!=-1){//Ausgabe
		channel.write(ergebnis[i]);
		i--;
	}	
}     
//Zeigertypen zur Basis 16 ausgeben

void PrintStream::print(void* p){

  print((unsigned int) p, HEX);// Einfach zum unsigned int casten und dann in unsere eigene Hexumwandlung einpflegen

}
