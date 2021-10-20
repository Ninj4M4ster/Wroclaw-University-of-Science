#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* autor - Jakub Drzewiecki */

int czyCalkowita(double n){
    while(n>0){
        n /= 10;
    }
    if(n==0)
        return 1;
    else
        return 0;
}

int main()
{
    printf("Zadanie 3\n\n");
    double n = 1, suma = 0;
    while(suma <= 10){
        assert(n>0 && czyCalkowita(n));
        suma += (1/n);
        n++;
    }
    printf("Najmniejsze n spelniajace nierownosc wynosi: %lf", n-1);
    return 0;
}
