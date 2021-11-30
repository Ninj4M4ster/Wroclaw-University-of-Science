// autor - Jakub Drzewiecki

#include "funs.h"
#include <math.h>
#include <assert.h>

double rozwiazanie(double a, double b, double eps){
  assert(a<b);
  double c = (a + b) / 2.0;
  double wynik = 0;
  while (fabs(c - wynik) > eps) {
    wynik = c;
    if (f(wynik) == 0)
      return wynik;
    if (f(a) < 0) {     // f(a) < f(b)
      if (f(wynik) < 0)
        a = c;
      else
        b = c;
    } else {
      if (f(wynik) < 0)         // f(a) > f(b)
        b = c;
      else
        a = c;
    }
    c = (a + b) / 2.0;
  }
  return c;
}
