// autor - Jakub Drzewiecki

#include "funs.h"
#include <assert.h>

int phi(long int n){
  assert(n>=1);
  int ilosc = 0;
  for(int i = 1; i <= n; i ++){
    if(NWD(i, n) == 1)
      ilosc ++;
  }
  return ilosc;
}
