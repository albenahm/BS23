#include <stdio.h>
#include <stdbool.h>

extern int whileSchleife(unsigned int eingabe);
extern void forSchleife(int eingabe, int* result);

int main(){

long long int input;
int result =0;
     
printf("Bitte geben Sie ein Zahl ein ! ");
scanf("%llu",&input);
printf("%llu \n",input);

if(0<input){
     
     if(input<4294967296){

        printf("While Schleife Ergebnis = %d \n",whileSchleife(input));
        forSchleife(input,&result);
        printf("For-Schleifen-Ergebnis = %d \n",result);
     }

}else{
    printf("Die Eingabe muss echt grosser als 0 sein!");
}

    return 0;
}
