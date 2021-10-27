#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// autor - Jakub Drzewiecki

int main()
{
    double wynik=1;
    printf("Zadanie 4\n\n");

    for(double i=2.0; i<=1000; i++){
        wynik *= pow(i, (1.0/1000.0));
    }

    printf("Wynik dzialania to: %f\n", wynik);
    return 0;
}
