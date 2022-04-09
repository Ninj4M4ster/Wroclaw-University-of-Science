// autor - Jakub Drzewiecki

#include "funs.h"
#include <stdio.h>

int main(){
  if(match("a*b*a", "abababababababababa"))
    printf("a*b*a oraz abababababababababa po porownaniu zwrocily prawde\n");
  else
    printf("a*b*a oraz abababababababababa po porownaniu zwrocily falsz\n\n");
  if(match("a*b*a", "ababababababababab"))
    printf("a*b*a oraz ababababababababab po porownaniu zwrocily prawde\n");
  else
    printf("a*b*a oraz ababababababababab po porownaniu zwrocily falsz\n");
}
