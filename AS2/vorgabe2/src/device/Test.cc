#include <iostream>
#include "/home/ahmad/Desktop/BS/BS23/AS2/vorgabe2/include/thread/Coroutine.h"



class Hello{
public:
    Hello(const char * name):name(name){
        std::cout<< name <<"\n";
        std::cout<< "ctor;" <<"\n";
    }
    ~Hello (){
        std::cout<< name <<"\n";
        std::cout<< "dtor;" <<"\n";
    }

    void body(){
        std::cout<< name <<"\n";
        std::cout<< "body ;" <<"\n";
    }

const char * name ;
 } ;

int main(){
    /*
    std::cout<<"main1;"<<"\n";
    Hello anton("Anton");
    Hello betra("Berta");
    anton.body();
    std::cout<<"main3;"<<"\n";
    */
   	struct CoroutineStack
	{
		//Flüchtige register
		unsigned edi;	//definiere Ziel (eng: destination) für Stringoperationen
		unsigned esi;	//definiere Quelle (eng: source) für Stringoperationen
		unsigned ebx;	//allgemeine register
		void* ebp;		//Basispointer
		void (*coroutine) (Coroutine*); // Anfang der Corotine mit Funktion Pointer(* um startup zu erreichen) und Parameter von Coriutine
		void* adress_ret;	// return adresse
		Coroutine* coroutine_obj; //Eingabe fuer Anfang

	};

    CoroutineStack stack;

    CoroutineStack* stack1=&stack;
    CoroutineStack* stack2=stack1 -1;
    CoroutineStack* stack3=stack1 +1;

   std::cout<<stack1<<"\n";
   std::cout<<*stack2-><<"\n";
   std::cout<<stack3<<"\n";

    return 0;
}



