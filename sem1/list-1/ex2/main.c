#include <stdio.h>
#include <stdlib.h>

/* autor - Jakub Drzewiecki */

float wbez(float a, float b){
    if(a < b)
    	return b - a;
    else
    	return a - b;
}

float pierwiastek(float a) {
    float pole = a;
    float b = 1;
    while(wbez(a, b) > 0.000001){
    	a = (a + b)/2;
    	b = pole / a;
    }
    return a;
}

int main()
{
    float a=0, b=0, c=0;
    float delta = 0;

    printf("Zadanie 2\n\n");

    printf("Wprowadz wspolczynnik a: ");
    scanf("%f", &a);
    printf("Wprowadz wspolczynnik b: ");
    scanf("%f", &b);
    printf("Wprowadz wspolczynnik c: ");
    scanf("%f", &c);
    printf("\n\n");

    delta = (b*b) - (4*a*c);

    if(delta < 0){
        printf("W zbiorze liczb rzeczywistych nie ma rozwiazania.");
    }
    else
    if(delta == 0){
        float rozwiazanie = -b / 2 * a;
        printf("Rozwiazaniem rownania jest liczba %f", rozwiazanie);
    }
    else{
        float rozwiazanie1 = (-b - pierwiastek(delta)) / (2 * a);
        float rozwiazanie2 = (-b + pierwiastek(delta)) / (2 * a);
        printf("Rozwiazaniami rownania sa liczby %f i %f", rozwiazanie1, rozwiazanie2);
    }
    printf("\n");
    return 0;
}
