// autor - Jakub Drzewiecki

#include <stdio.h>
#include "funs.h"
#include <math.h>

int main(){
  int a = 2, b = 4;
  for(int k = 1; k <= 8; k++) {
    double wynik = rozwiazanie(a, b, pow(10, -k));
    printf("Miejscem zerowym funkcji jest: %lf\n", wynik);
  }
}
