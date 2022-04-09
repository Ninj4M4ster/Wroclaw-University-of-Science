#include <stdio.h>
#include <stdlib.h>

// autor - Jakub Drzewiecki

int sumaDzielnikow(int liczba){
    int suma=0;
    for(int i=1; i<=liczba/2; i++){
        if(liczba%i == 0)
            suma += i;
    }
    return suma;
}

int main()
{
    int tablica_sum_dzielnikow[1000], m;
    printf("Zadanie 6\n\n");

    printf("Liczby doskonale:\n");
    for(int i=1; i<=1000; i++){
        tablica_sum_dzielnikow[i-1] = sumaDzielnikow(i);
        if(tablica_sum_dzielnikow[i-1] == i){
            printf("\t%d\n", i);
        }
    }
    printf("Zaprzyjaznione pary liczb:\n");
    for(int n=1; n<1000; n++){
        m = tablica_sum_dzielnikow[n-1];
        if(m <= 1000 && n < m){
            if(tablica_sum_dzielnikow[m-1] == n)
                printf("\t%d i %d\n", n, m);
        }
    }
    return 0;
}
