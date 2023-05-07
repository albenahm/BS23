#include "device/CgaChannel.h"

#include "io/PrintStream.h"



CgaChannel cga;		// unser CGA-Ausgabekanal

PrintStream out(cga);	// unseren PrintStream mit Ausgabekanal verknuepfen



extern "C" int main()

{



	out.println("Hello World");

	out.print(189,16);

	out.println("");

	out.print(0,10);

	out.println("");

	out.print(-4,2);

	out.println("");

	out.print(1000,16);

	out.println("");

	out.print(-2147483647,2);

	out.println("");

	out.print((unsigned) 4294967295,2);

	out.println("");

	for(int i = 0; i < 81; i++){

		out.print("a");

	}

	out.println("");

	for(int i = 0; i < 7; i++){

		out.print("a");

	}

	//out.print('\r');

	for(int i = 0; i < 5; i++) {

		out.print(i);

	}

	out.println("");

	for(int i = 0; i < 5; i++){

		out.print(i, 16);

	}

	out.println("");

	out.print("done");

	out.println();

	while(1){}



	return 0;

}
