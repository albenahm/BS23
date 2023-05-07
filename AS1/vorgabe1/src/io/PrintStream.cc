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

			print("Nur 2,10,16 als base erlaubt");//Nicht erlaubt

	}

	int max =32;

	char zahl[max];//

	int i =0;

	int y;

	if(x==0){

		channel.write(48);

		return;

	}

	while(x!=0){

		

		y = x%base;

		x = (x-y)/base;

		if(y <10){

			zahl[i]=y+48; 

		}

		else{

			switch (y){

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

		i++;

	}

	i--;

	while(i!=-1){//Ausgabe

		channel.write(zahl[i]);

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

			print("Nur 2,10,16 als base erlaubt");//Nicht erlaubt

	}

	int max =32;

	if(x<0){//Minuszeichen

		x = x*(-1);

		print('-');

		max--;

	}

	char zahl[max];//

	int i =0;

	int y;

	if(x==0){

		channel.write(48);

		return;

	}

	while(x!=0){

		

		y = x%base;

		x = (x-y)/base;

		if(y <10){

			zahl[i]=y+48; 

		}

		else{

			switch (y){

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

		i++;

	}

	

	i--;

	while(i!=-1){//Ausgabe

		channel.write(zahl[i]);

		i--;

	}	

}     

//Zeigertypen zur Basis 16 ausgeben

void PrintStream::print(void* p){

   

  print((unsigned int) p, HEX);



}
