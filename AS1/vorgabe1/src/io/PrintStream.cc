#include "device/CgaScreen.h"
#include "device/CgaChannel.h"
#include "device/CgaAttr.h"
#include "io/OutputChannel.h" 


using namespace PrintStream;

private:
    enum Base{
      BINARY=2;
      DECIMAL=10;
      HEX=16;
    }
public:

PrintStream(OutputChannel* chan);

PrintStream(OutputChannel& chan);

// Ausgabe NUll-Byte terminierter String
void print(const char* str){
    for (int i = 0, i <2000 ,i++){

      if (str[i] == '\0'){
        break;
      } else{
        this -> channel.write(str[i]);
      }

    }
}
void print(char ch){

   this -> channel.write(ch);

}

// Ausgabe String mit Zeilenvorschub
void println(const char* str){
    for (int i = 0, i <2000 ,i++){

      if (str[i] == '\0'){
        break;
      } else{
        this -> channel.write(str[i]);
      }
    }
    this -> channel.write('\n') ;

}

//Zeilenvorschub
void println(){

   this -> channel.write('\n');
}

//numerische Werte werden zur Basis base ausgegeben
// Basen 2, 10 und 16

// Basis 2
void print(int x, int base = BINARY){
    //Fange negative Zahlen ab (else- Zweig)
    if ( x > 0){  //x ist positiv
    
      char xout[31]; // 31- Stelliges Array wegen Groesse von Integer, das höchstwertigste Bit ist für den Fall ein extra ausgegebenes "-" | 2 ^31 = ca 2 Mrd
      int y;
      int i = 0;
      // Rechne x/2 solange wie x != 0 und schreibe 1 oder 0 währenddessen
      while( x != 0){
        y = x % 2;
        x = (x-y) /2;
        xout[i] = y; 
        i++;       
      }    
      this -> channel.write('b'); // Wir schreiben ein "b" zum Kennzeichnen eines Binärwertes
      for (int j = 0, j <= i, j++){
        
        this -> channel.write([i-j]+48); // Wir schreiben +48 wegen ASCII-Stelle 

      }
    }
    else {  // x ist negativ
      char xout[31]; // 31- Stelliges Array wegen Groesse von Integer, das höchstwertigste Bit ist für den Fall ein extra ausgegebenes "-" 2 ^31 = ca 2 Mrd
      x = x * (-1);
      int y;
      int i = 0;
      // Rechne x/2 solange wie x != 0 und schreibe 1 oder 0 währenddessen
      while( x != 0){
        y = x % 2;
        x = (x-y) /2;
        xout[i] = y;  
        i++;       
      }    
      this -> channel.write('b'); // Wir schreiben ein "b" zum Kennzeichnen eines Binärwertes
      this -> channel.write('-');
      for (int j = 0, j <= i, j++){
        
        this -> channel.write([i-j]+48); // Wir schreiben +48 wegen ASCII-Stelle 
        
      }
    }
}
// Hier gibt es keine negativen Zahlen, also ist ein if-else-Zweig unnötig
void print(unsigned x, int base = BINARY){
    char xout[32]; // Hier 32 Bit, weil 0 - ca. 4 Mrd Range da 2^32
      int y;
      int i = 0;
      // Rechne x/2 solange wie x != 0 und schreibe 1 oder 0 währenddessen
      while( x != 0){
        y = x % 2;
        x = (x-y) /2;
        xout[i] = y;  //0 
        i++;       
      }    
      this -> channel.write('b'); // Wir schreiben ein "b" zum Kennzeichnen eines Binärwertes
      for (int j = 0, j <= i, j++){
        
        this -> channel.write([i-j]+48); // Wir schreiben +48 wegen ASCII-Stelle
      }
    
}

void print(int x, int base = DECIMAL){
  this -> channel.write(x); // müssen wir hier groß was machen?

}

void print(unsigned x, int base = DECIMAL){
  this -> channel.write(x);
}

void print(int x, int base = HEX){
    //Fange negative Zahlen ab (else- Zweig)
    if ( x > 0){  //x ist positiv
    
      char xout[7]; // 7- Stelliges Array wegen Groesse von Integer, das höchstwertigste Bit ist für den Fall ein extra ausgegebenes "-" 16^7 = ca 2 Mrd
      int y;
      int i = 0;
      // Rechne x/2 solange wie x != 0 und schreibe 1 oder 0 währenddessen
      while( x != 0){
        y = x % 16;
        x = (x-y) /16;
        
        switch(y){ // Hier greifen wir ab, dass ein einstelliges Zeichen über den Dezimalwert von 9 gemäß Hexaschreibweise geschrieben werden kann
          case 10: 
            xout[i] = A; // bei 10 schreibe A
            break;
          case 11: 
            xout[i] = B; //...
            break;
          case 12: 
            xout[i] = C;
            break;
          case 13: 
            xout[i] = D;
            break;
          case 14: 
            xout[i] = E;
            break;
          case 15: 
            xout[i] = F;
            break;
          default:
            xout[i] = y;
        }
        i++;       
      }    
      this -> channel.write('h'); // Wir schreiben ein "h" zum Kennzeichnen eines Binärwertes
      for (int j = 0, j <= i, j++){
        switch(xout[i-j]){ // Hier greifen wir ab, dass ein einstelliges Zeichen über den Dezimalwert von 9 gemäß Hexaschreibweise geschrieben werden kann
          case 'A': 
            this -> channel.write(65); // 65 weil ASCII Code Buchtaben beginnend bei A
            break;
          case 'B': 
            this -> channel.write(66); // ...
            break;
          case 'C': 
            this -> channel.write(67);
            break;
          case 'D': 
            this -> channel.write(68);
            break;
          case 'E': 
            this -> channel.write(69);
            break;
          case 'F': 
            this -> channel.write(70);
            break;
          default:
            this -> channel.write([i-j]+48); // 48 weil ASCII COde Zahlen beginnend bei 0
        }
      }
    }
    else {  // x ist negativ
      char xout[7]; // 7- Stelliges Array wegen Groesse von Integer, das höchstwertigste Bit ist für den Fall ein extra ausgegebenes "-" 16 ^7 = ca 2Mrd
      x = x * (-1);
      int y;
      int i = 0;
      // Rechne x/2 solange wie x != 0 und schreibe 1 oder 0 währenddessen
      while( x != 0){
        y = x % 16;
        x = (x-y) /16;
        
        switch(y){ // Hier greifen wir ab, dass ein einstelliges Zeichen über den Dezimalwert von 9 gemäß Hexaschreibweise geschrieben werden kann
          case 10: 
            xout[i] = A; // bei 10 schreibe A
            break;
          case 11: 
            xout[i] = B; //...
            break;
          case 12: 
            xout[i] = C;
            break;
          case 13: 
            xout[i] = D;
            break;
          case 14: 
            xout[i] = E;
            break;
          case 15: 
            xout[i] = F;
            break;
          default:
            xout[i] = y;
        }
        i++;       
      }    
      this -> channel.write('h'); // Wir schreiben ein "h" zum Kennzeichnen eines Binärwertes
      this -> channel.write('-'); // Wir schreiben ein "-" weil negativ
      for (int j = 0, j <= i, j++){
        switch(xout[i-j]){ // Hier greifen wir ab, dass ein einstelliges Zeichen über den Dezimalwert von 9 gemäß Hexaschreibweise geschrieben werden kann
          case 'A': 
            this -> channel.write(65); // 65 weil ASCII Code Buchtaben beginnend bei A
            break;
          case 'B': 
            this -> channel.write(66); // ...
            break;
          case 'C': 
            this -> channel.write(67);
            break;
          case 'D': 
            this -> channel.write(68);
            break;
          case 'E': 
            this -> channel.write(69);
            break;
          case 'F': 
            this -> channel.write(70);
            break;
          default:
            this -> channel.write([i-j]+48); // 48 weil ASCII COde Zahlen beginnend bei 0
        }
      }
    }   

}

void print(unsigned x, int base = HEX){
    char xout[8]; //16^8 = ca 4 MRD 
    int y;
    int i = 0;
      // Rechne x/2 solange wie x != 0 und schreibe 1 oder 0 währenddessen
    while( x != 0){
       y = x % 16;
       x = (x-y) /16;
        
      switch(y){ // Hier greifen wir ab, dass ein einstelliges Zeichen über den Dezimalwert von 9 gemäß Hexaschreibweise geschrieben werden kann
         case 10: 
          xout[i] = A; // bei 10 schreibe A
          break;
        case 11: 
          xout[i] = B; //...
          break;
         case 12: 
          xout[i] = C;
          break;
         case 13: 
          xout[i] = D;
           break;
         case 14: 
           xout[i] = E;
           break;
         case 15: 
           xout[i] = F;
           break;
         default:
          xout[i] = y;
      }
       i++;       
    }    
      this -> channel.write('h'); // Wir schreiben ein "h" zum Kennzeichnen eines Binärwertes
      for (int j = 0, j <= i, j++){
        switch(xout[i-j]){ // Hier greifen wir ab, dass ein einstelliges Zeichen über den Dezimalwert von 9 gemäß Hexaschreibweise geschrieben werden kann
          case 'A': 
            this -> channel.write(65); // 65 weil ASCII Code Buchtaben beginnend bei A
            break;
          case 'B': 
            this -> channel.write(66); // ...
            break;
          case 'C': 
            this -> channel.write(67);
            break;
          case 'D': 
            this -> channel.write(68);
            break;
          case 'E': 
            this -> channel.write(69);
            break;
          case 'F': 
            this -> channel.write(70);
            break;
          default:
            this -> channel.write([i-j]+48); // 48 weil ASCII Code Zahlen beginnend bei 0
        }
      }
}


//Zeigertypen zur Basis 16 ausgeben
void print(void* p){
  
  unsigned int zahl = p;
   
  print(zahl, HEX);

}

private: 
    OutputChannel& channel;

