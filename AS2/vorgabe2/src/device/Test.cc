#include "/home/ahmad/Desktop/BS/BS23/AS2/vorgabe2/include/device/CgaChannel.h"
#include "/home/ahmad/Desktop/BS/BS23/AS2/vorgabe2/include/io/PrintStream.h"

PrintStream::PrintStream(OutputChannel* chan): channel(*chan)
{
}

PrintStream::PrintStream(OutputChannel& chan): channel(chan)
{
}

class Hello{

Hello(const char * name): name(name) {
 out.print( name ) ;
 out.print("ctor;");
 }

~ Hello() {
 out.print(name);
 out.print("dtor;") ;
 }

 void body ( ) {
 out.print( name );
 out.print("body ;");
 }

 const char ∗ name ;
 } ;

int main(){
   out.print("main1;");
Hello anton("Anton");
Hello berta("Berta");
out.print("main2;");
anton.body();
out.print("main3;");
    return 0;
}



