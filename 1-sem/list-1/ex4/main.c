#include <stdio.h>
#include <stdlib.h>

void drukujTrojkat(int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1; j++){
            printf(" ");
        }
        for(int j=0; j<i*2 + 1; j++){
            printf("*");
        }
        printf("\n");
    }
}

int main()
{
    int n=0;

    printf("Zadanie 4\n");

    printf("Wprowadz liczbe wierszy: ");
    scanf("%d", &n);

    if(n<1){
        printf("Wprowadzono niepoprawna liczbe");
    }
    else
        drukujTrojkat(n);
    return 0;
}
