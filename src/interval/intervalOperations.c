// Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "../../include/interval.h"

Interval intervalSum(Interval a, Interval b) {
  Interval result;

  result.min = a.min + b.min;
  result.max = a.max + b.max;

  return result;
}

Interval intervalSub(Interval a, Interval b) {
  Interval result;

  result.min = a.min - b.max;
  result.max = a.max - b.min;

  return result;
}

Interval intervalMult(Interval a, Interval b) {
  Interval result;

  result.min = fmin(fmin(a.min * b.min, a.min * b.max),
                    fmin(a.max * b.min, a.max * b.max));
  result.max = fmax(fmax(a.min * b.min, a.min * b.max),
                    fmax(a.max * b.min, a.max * b.max));

  return result;
}

Interval intervalDiv(Interval a, Interval b) {
  Interval aux;

  // Se zero está contido no intervalo
  if(b.min * b.max < 0) {
    aux.min = -INFINITY;
    aux.max = INFINITY;
    return aux; 
  }

  aux.min = 1 / b.max;
  aux.max = 1 / b.min;

  return intervalMult(a, aux);
}

Interval intervalPow(Interval a, int p) {
  Interval aux;
  if (p == 0) {
    aux.min = 1.0;
    aux.max = 1.0;
    return aux;
  } else if (p % 2 == 1 || (p % 2 == 0 && a.min >= 0)) {
    aux.min = pow(a.min, p);
    aux.max = pow(a.max, p);

    return aux;
  } else if (p % 2 == 0 && a.max < 0) {
    aux.min = pow(a.max, p);
    aux.max = pow(a.min, p);

    return aux;
  } else {
    aux.min = 0;
    aux.max = fmax(a.min * p, a.max * p);

    return aux;
  }
}

double intervalMean(Interval a) { return (a.min + a.max) / 2; }
