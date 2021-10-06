#include <stdio.h>
#include <stdlib.h>

void printString(int end, char napis[]){
    for(int i=0; i <= end; i++){
        printf("%c ", napis[i]);}
};

int main()
{
    printf("Zadanie 1\n\n");
    char napis[11] = "ABRAKADABRA";
    for(int i=0; i <= 10; i++){
        for(int j=0; j<i; j++){
            printf(" ");
        }
        printString(10-i, napis);
        printf("\n");
    }

    return 0;
}
