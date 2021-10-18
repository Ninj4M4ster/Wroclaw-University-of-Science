#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i = 0;
    float suma, x;
    printf("Zadanie 2\n\n");

    printf("Wprowadz liczbe n: ");
    scanf("%d", &n);
    while(i < n){
        printf("Wprowadz %d liczbe: ", i+1);
        scanf("%f", &x);
        suma += x;
        i ++;
    }
    suma = suma / n;
    printf("Srednia arytmetyczna wynosi %f", suma);
    return 0;
}
