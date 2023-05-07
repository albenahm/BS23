#include "io/OutputChannel.h" 

#include "io/PrintStream.h"



PrintStream::PrintStream(OutputChannel* chan): channel(*chan)

{

}

PrintStream::PrintStream(OutputChannel& chan): channel(chan){

}



// Ausgabe NUll-Byte terminierter String

void PrintStream::print(const char* str){

	int i=0; // Wir verwenden i, um die Zeichen hochzuzählen

	while(str[i] != '\0'){

        	i++;

        }

        channel.write(str,i); // Wir geben den char an der Stelle aus indem wir es der write Funktion übergeben

}

void PrintStream::print(char ch){



   channel.write(ch); //Wir geben unseren char weiter 



}



// Ausgabe String mit Zeilenvorschub

void PrintStream::println(const char* str){

	int i= 0;
	// Identisch wie bei print(const char* str), aber am Emde wird noch \n generiert
	while(str[i] != '\0'){      

        	i++;

      	}

      	channel.write(str,i);

    	channel.write('\n'); 

}



//Zeilenvorschub

void PrintStream::println(){

	channel.write('\n');

}



//numerische Werte werden zur Basis base ausgegeben

// Basen 2, 10 und 16



// Ausgabe der Zahlen in die angegebene Basis base

void PrintStream::print(int x, int base){

	switch(base){//Vorzeichen fuer 2,10,16

		case 2:

			print("0b"); // Binaerdarstellung

			break;

		case 10:

			print("0d"); // Dezimaldarstellung

			break;

		case 16:

			print("0x"); // Hexadezimaldarstellung

			break;

		default:

			print("Nur 2,10,16 als base erlaubt"); //Nicht erlaubte Basen

	}

	int max =32;

	if(x<0){ //Minuszeichen: Wir nehmen das Minuszeichen von der Zahl weg und fügen es nach dem Rechnen hinzu

		x = x*(-1);

		print('-');

		max--;

	}

	char zahl[max];// Maximale Bitlänge des zu erwartenden Arrays. 32 Int

	int i =0;

	int y;

	while(x!=0){

		i++;

		y = x%base;

		x = (x-y)/base;

		if(y <10){

			zahl[i]=y+48; //Laut Dokumentation fangen in ASCII-Code die Zahlen bei Zeichen 48 an, geordnet,
			//daher können wir wir 48 drauf addieren
			
		}

		else{ 

			switch (y){// Wir möchten Zahlen, welche größer als 10 sind mit dem entsprechendem Bushtaben ausgeben

				case 10:

					zahl[i]=65;

					break;

				case 11:

					zahl[i]=66;

					break;

				case 12:

					zahl[i]=67;

					break;

				case 13:

					zahl[i]=68;

					break;

				case 14:

					zahl[i]=69;

					break;

				case 15:

					zahl[i]=70;

					break;

				default:print("Fehler");

			}

		

		}

	char ergebnis[i];

	int k = i;

	for(int j=0;i!=0;j++){//Array umkehren, j variable fuer Ergebnis (zaehlt hoch), i Variable fuer zahl (zaehlt runter)

		ergebnis[j]=zahl[i-1];

		i--;

	}

	channel.write(ergebnis,k);

	}

	

}     

//Zeigertypen zur Basis 16 ausgeben

void PrintStream::print(void* p){

   

  print((unsigned int) p, HEX); // Wir machen p einfach zu einem unsigned int und rechenen es in unserer Methode zu HEX um



}
