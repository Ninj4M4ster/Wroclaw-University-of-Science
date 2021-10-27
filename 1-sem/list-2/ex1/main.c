#include <stdio.h>
#include <stdlib.h>

// autor - Jakub Drzewiecki

void rozmienNominal(int* zlote, int nominal, int czyZlotowki){
    int i = 0;
    while(*zlote >= nominal){
        *zlote -= nominal;
        i++;
    }
    if(czyZlotowki){
        printf("\t\t%d x %d zl\n", i, nominal);
    }
    else{
        printf("\t\t%d x %d gr\n", i, nominal);
    }
}

int main()
{
    int zlote, grosze;
    printf("Zadanie 1\n\n");
    printf("podaj liczbe zloty: ");
    scanf("%d", &zlote);
    printf("podaj liczbe groszy: ");
    scanf("%d", &grosze);
    printf("\tbanknoty: \n");
    if(zlote >= 200){
        rozmienNominal(&zlote, 200, 1);
    }
    if(zlote >= 100){
        rozmienNominal(&zlote, 100, 1);
    }
    if(zlote >= 50){
        rozmienNominal(&zlote, 50, 1);
    }
    if(zlote >= 20){
        rozmienNominal(&zlote, 20, 1);
    }
    if(zlote >= 10){
        rozmienNominal(&zlote, 10, 1);
    }
    if(zlote > 0 || grosze > 0){
        printf("\tmonety:\n");
        if(zlote >= 5){
            rozmienNominal(&zlote, 5, 1);
        }
        if(zlote >= 2){
            rozmienNominal(&zlote, 2, 1);
        }
        if(zlote >= 1){
            rozmienNominal(&zlote, 1, 1);
        }
        if(grosze >= 50){
            rozmienNominal(&grosze, 50, 0);
        }
        if(grosze >= 20){
            rozmienNominal(&grosze, 20, 0);
        }
        if(grosze >= 10){
            rozmienNominal(&grosze, 10, 0);
        }
        if(grosze >= 5){
            rozmienNominal(&grosze, 5, 0);
        }
        if(grosze >= 2){
            rozmienNominal(&grosze, 2, 0);
        }
        if(grosze >= 1){
            rozmienNominal(&grosze, 1, 0);
        }
    }

    return 0;
}
