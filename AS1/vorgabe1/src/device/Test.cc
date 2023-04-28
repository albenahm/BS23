#include "/home/ahmad/Desktop/BS/BS23/AS1/vorgabe1/include/device/CgaAttr.h"
#include "/home/ahmad/Desktop/BS/BS23/AS1/vorgabe1/include/device/CgaChar.h"

#include<iostream>


void bin(unsigned n)
{
    /* step 1 */
    if (n > 1)
        bin(n / 2);
 
    /* step 2 */
    std::cout << n % 2;
}

int main(){
 /*  

 Teste CgaAttr 
CgaAttr a= CgaAttr();
a.setBackground(CgaAttr::GRAY);
bin(a.getForeground());
std::cout<<"\n";
bin(a.getBackground());
std::cout<<"\n";
bin(a.getBlinkState());
std::cout<<"\n";

*/

/*

Teste CgaChar

CgaChar a = CgaChar();
a.setChar('s');
std::cout<< a.getChar();
std::cout<<"\n";
bin(a.getAttr().getBackground());

*/
    return 0;
}



