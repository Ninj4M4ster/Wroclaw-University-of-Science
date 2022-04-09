// autor - Jakub Drzewiecki

#include "funs.h"

int NWD(long int i, long int n){
  while(i != 0){
    int tmp = n%i;
    n = i;
    i = tmp;
  }
  return n;
}
