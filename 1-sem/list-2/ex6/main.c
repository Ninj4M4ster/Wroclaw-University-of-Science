#include <stdio.h>
#include <stdlib.h>

int sumaDzielnikow(int liczba){
    int suma=0;
    for(int i=1; i<liczba; i++){
        if(liczba%i == 0)
            suma += i;
    }
    return suma;
}

int czyDoskonala(int sprawdzana){
    int suma = sumaDzielnikow(sprawdzana);
    if(suma == sprawdzana)
        return 1;
    else
        return 0;
}
int main()
{
    printf("Zadanie 6\n\n");

    printf("Liczby doskonale:\n");
    for(int i=1; i<=1000; i++){
        if(czyDoskonala(i)){
            printf("\t%d\n", i);
        }
    }
    printf("Zaprzyjaznione pary liczb:\n");
    for(int n=1; n<1000; n++){
        for(int m=n+1; m<=1000; m++){
            if(sumaDzielnikow(n) == m && sumaDzielnikow(m) == n)
                printf("\t%d i %d\n", n, m);
        }
    }
    return 0;
}
