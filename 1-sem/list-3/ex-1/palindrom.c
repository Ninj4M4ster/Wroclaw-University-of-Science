#include <stdio.h>
#include "funs.h"
#include <stdbool.h>

// autor - Jakub Drzewiecki

bool palindrom(char napis[]){
  char otrzymany_napis[100];
  int dlugosc = 0, i = 0;
  while (napis[dlugosc] != '\0'){
    dlugosc++;
  }
  for(int j = dlugosc-1; j >= 0; j--){
    otrzymany_napis[i] = napis[j];
    i ++;
  }
  for(int j=0; j < dlugosc; j++){
    if (otrzymany_napis[j] != napis[j])
      return false;
  }
  return true;
}
