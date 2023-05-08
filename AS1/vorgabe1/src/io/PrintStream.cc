#include "io/OutputChannel.h" 

#include "io/PrintStream.h"



PrintStream::PrintStream(OutputChannel* chan): channel(*chan)

{

}

PrintStream::PrintStream(OutputChannel& chan): channel(chan){

}



// Ausgabe NUll-Byte terminierter String

void PrintStream::print(const char* str){

	int i=0;

	while(str[i] != '\0'){

        	i++;

        }

        channel.write(str,i);

}

void PrintStream::print(char ch){

   channel.write(ch);

}

// Ausgabe String mit Zeilenvorschub

void PrintStream::println(const char* str){

	int i= 0;

	while(str[i] != '\0'){   

        	i++;

      	}

      	channel.write(str,i);

    	channel.write('\n');

}

//Zeilenvorschub

void PrintStream::println(){

	print('\n');

}

//numerische Werte werden zur Basis base ausgegeben

// Basen 2, 10 und 16

void PrintStream::print(unsigned int x, int base){

	switch(base){//Vorzeichen fuer 2,10,16

		case 2:

			print("0b");

			break;

		case 10:

			print("0d");

			break;

		case 16:

			print("0x");

			break;

		default:

			{print("Nur 2,10,16 als base erlaubt");

			return;};//Nicht erlaubt

	}

	int max =32;

	int i =0;

	char ergebnis [max];

	if(x==0){

		channel.write('0');//Null in Ascii

		return;

	}

	const char character [] = {"0123456789ABCDEF"};

	while(x!=0){

		

		ergebnis[i]=character[ (x%base)];

		x = x/base;

		i++;

		

	}

	while(i){//Ausgabe

		channel.write(ergebnis[i-1]);

		i--;

	}	

}

void PrintStream::print(int x, int base){

	

	switch(base){//Vorzeichen fuer 2,10,16

		case 2:

			print("0b");

			

			break;

		case 10:

			print("0d");

			break;

		case 16:

			print("0x");

			break;

		default:

			{print("Nur 2,10,16 als base erlaubt");

			return;};//Nicht erlaubt

	}

	int max =32;

	if(x<0){//Minuszeichen

		x = x*(-1);

		channel.write('-');

		max--;

	}

	int i =0;

	char ergebnis [max];

	if(x==0){

		channel.write('0');//Null in Ascii

		return;

	}

	const char character [] = {"0123456789ABCDEF"};

	while(x!=0){

		

		ergebnis[i]=character[ (x%base)];

		x = x/base;

		i++;

		

	}

	while(i){//Ausgabe

		channel.write(ergebnis[i-1]);

		i--;

	}	

}     

//Zeigertypen zur Basis 16 ausgeben

void PrintStream::print(void* p){

  print((unsigned int) p, HEX);

}
