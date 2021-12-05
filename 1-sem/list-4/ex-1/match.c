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
            if(i == strlen(wzorzec))
                return true;
            if(wzorzec[i] == '*')
                continue;
            tmp_i = i;
            while(wzorzec[i] != '*' && i < strlen(wzorzec)){         // liczymy dlugosc wzorca do kolejnego znaku gwiazdki lub konca wzorca
                i++;
            }
            int dlugosc_sprawdzanego_ciagu = i - tmp_i;
            if(i == strlen(wzorzec)){                                // sprawdzamy znaki lancucha i wzorca od konca
                i = strlen(wzorzec) - dlugosc_sprawdzanego_ciagu;
                j = strlen(lancuch) - dlugosc_sprawdzanego_ciagu;
            }
            else {
                while(j <= strlen(lancuch) - dlugosc_sprawdzanego_ciagu){       // sprawdzamy kolejne znaki lancucha, az j bedzie krotsze od dlugosci porownywanego wzorca
                    int kolejny_znak_lancucha = 0
                    for(int k = tmp_i; k < tmp_i + dlugosc_sprawdzanego_ciagu; k++){
                        if(wzorzec[k] == '?')
                            kolejny_znak_lancucha++;
                            continue;
                        else if(wzorzec[k] != lancuch[j + kolejny_znak_lancucha])
                            break;
                        kolejny_znak_lancucha++;
                    }
                    if(kolejny_znak_lancucha + 1 == dlugosc_sprawdzanego_ciagu) {
                        j += kolejny_znak_lancucha + 1;
                        break;
                    }
                    else {
                        j++;
                        if(j > strlen(lancuch) - dlugosc_sprawdzanego_ciagu)        // jesli wzorzec nie zgadzal sie z ciagiem w napisie, to j przekroczy dlugosc porownywanego wzorca
                            return false;
                    }
                }
            }
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