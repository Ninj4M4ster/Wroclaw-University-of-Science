// autor - Jakub Drzewiecki

#include "funs.h"
#include <math.h>
#include <assert.h>

double rozwiazanie(double a, double b, double eps){
  assert(a<b);
  double c = (a + b) / 2.0;
  while (fabs(a - b) > eps) {
    c = (a+b) / 2;
    if (f(c) == 0)
      return c;
    if (f(a) < 0) {     // f(a) < f(b)
      if (f(c) < 0)
        a = c;
      else
        b = c;
    } else {
      if (f(c) < 0)         // f(a) > f(b)
        b = c;
      else
        a = c;
    }
  }
  return a;
}
