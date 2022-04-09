// autor - Jakub Drzewiecki

#include <stdio.h>
#include "funs.h"

int main(){
  for(int i = 1; i <= 100; i++){
    int wynik = phi(i);
    printf("Wynikiem funkcji phi dla n = %d jest %d\n", i, wynik);
  }
}
