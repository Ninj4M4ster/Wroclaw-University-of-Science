#include <stdio.h>
#include "funs.h"

// autor - Jakub Drzewiecki

int main(){
  char napis[100];
  for(;;){
    printf("Wprowadz wyraz do przetestowania funkcji (wprowadzenie '0' zakonczy testowanie): ");
    scanf("%s", &napis);
    if (napis[0] == '0') {
      printf("Koniec testowania programu\n");
      break;
    } else if (palindrom(napis))
      printf("Sprawdzany wyraz byl palindromem\n\n");
    else
      printf("Sprawdzany wyraz nie byl palindromem\n\n");
  }
  return 0;
}