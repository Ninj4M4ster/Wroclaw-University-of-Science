#include <stdio.h>
#include <stdlib.h>

/* autor - Jakub Drzewiecki */

void drukujProstokat(int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<2*n; j++){
            printf("*");
        }
        printf("\n");
    }
}

int main()
{
    int n=0;

    printf("Zadanie 3\n");

    printf("Wprowadz liczbe od 1 do 20: ");
    scanf("%d", &n);

    if(n < 1 || n > 20){
        printf("Wprowadzono niepoprawna liczbe\n");
    }
    else
        drukujProstokat(n);
    return 0;
}
