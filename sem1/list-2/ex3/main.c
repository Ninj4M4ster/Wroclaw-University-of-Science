#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* autor - Jakub Drzewiecki */

int main()
{
    printf("Zadanie 3\n\n");
    double n = 0, suma = 0;
    while(suma <= 10){
        n++;
        assert(n>0);
        suma += (1/n);
    }
    printf("Najmniejsze n spelniajace nierownosc wynosi: %lf", n);
    return 0;
}
