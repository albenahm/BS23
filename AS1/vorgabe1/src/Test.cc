#include<iostream>
using namespace std;
void bin(unsigned n)
{
    /* step 1 */
    if (n > 1)
        bin(n / 2);
 
    /* step 2 */
    cout << n % 2;
}

int main(){
    enum Color {
		BLACK,
		BLUE,
		BROWN,
		CYAN,
		GRAY,
		GREEN,
		LIGHT_BLUE,
		LIGHT_CYAN,
		LIGHT_GRAY,
		LIGHT_GREEN,
		LIGHT_MAGENTA,
		LIGHT_RED,
		MAGENTA,
		RED,
		WHITE,
		YELLOW
	};

    char y = (char) RED;
    Color x = YELLOW;
    //bin(y);
    //bin(x);
    int zahl = 50;
    int* zeiger = &zahl;

    cout<< zahl<<" \n";
    cout<< zeiger <<" ohne Zeichnen\n";

    cout<< *zeiger <<" mit *  \n";
    cout<< &zeiger <<" mit  &\n";

    return 0;
}



