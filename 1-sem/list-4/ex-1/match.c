// autor - Jakub Drzewiecki

#include "funs.h"
#include <cstring>
#include <assert.h>

bool match(char* wzorzec, char* lancuch){
    assert(strlen(wzorzec) < strlen(lancuch));
    int i=0, j=0;
    while(i < strlen(wzorzec) && j < strlen(lancuch)) {
        if (wzorzec[i] == '?') {
            i++;
            j++;
        } else if(wzorzec[i] == '*') {
            i++;
            if(wzorzec[i] == '*')
                continue;

        } else if(wzorzec[i] == lancuch[j]) {
            i++;
            j++;
        } else
            return false;
    }
    if(i == strlen(wzorzec) && j == strlen(lancuch))
        return true;
    else
        return false;
}