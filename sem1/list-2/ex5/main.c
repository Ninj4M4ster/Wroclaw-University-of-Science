#include <stdio.h>
#include <stdlib.h>

// autor - Jakub Drzewiecki

int NWD(int a, int b){
    int c;
    while(b != 0){
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}
int main()
{
    printf("Zadanie 5\n\n");
    float wynik;
    float ile = 0;
    for(float i=1; i<=1000; i++){
        ile = 0;
        for(int a=1; a<=i; a++){
            for(int b=1; b<=i; b++){
                if(NWD(a, b) == 1){
                    ile += 1;
                }
            }
        }
        wynik = (ile/(i*i));
        printf("%f; %f\n", i, wynik);
    }
    return 0;
}
