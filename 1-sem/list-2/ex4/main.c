#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double wynik=1;
    printf("Zadanie 4\n\n");

    for(int i=2; i<=1000; i++){
        wynik *= i;
    }
    for(int i=1; i<500; i++){
        wynik = sqrt(wynik);
    }
    printf("Wynik dzialania to: %f", wynik);
    return 0;
}
