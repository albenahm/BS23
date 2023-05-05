#include <stdbool.h>
#include <stdio.h>

extern int whileSchleife(unsigned int eingabe);
extern void forSchleife(int eingabe, int* result);

int main(){

long long int input;
int result =0;
     
printf("Bitte geben Sie eine Zahl ein! ");
scanf("%llu",&input);
printf("%lld \n",input);

if(0<input){
     
     if(input<4294967296){

        printf("While-Schleife Ergebnis = %d \n",whileSchleife(input));
     }
     else{
     	printf("Die Eingabe ist zu gross!(While-Schleife)");
     }
}else{
    printf("Die Eingabe muss echt groesser sein als 0 fuer die While-Schleife!");
}
if(input<=2147483647){
	if(input>=-2147483647){
		if(input ==0){
			printf("Die Eingabe Null ist nicht gueltig!");
		}
		else if(input >=0){
			forSchleife(input,&result);
        		printf("For-Schleifen-Ergebnis = %d \n",result);
		}
		else{
			input = input*-1;
			forSchleife(input,&result);
        		printf("For-Schleifen-Ergebnis = %d \n",result);
		}
	}else{
		printf("Die Eingabe ist zu klein!");
	}
}
else{
	printf("Die Eingabe ist zu gross!(For-Schleife)");
}


    return 0;
}
