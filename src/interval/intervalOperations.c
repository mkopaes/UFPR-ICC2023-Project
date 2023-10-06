#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "../../include/interval.h"

Interval intervalSum(Interval a, Interval b) {
  fesetround(FE_DOWNWARD);

  Interval result;

  result.min = a.min + b.min;
  result.max = a.max + b.max;

  result.min = nextafter(result.min, -INFINITY);
  result.max = nextafter(result.max,  INFINITY);

  return result;
}

Interval intervalSub(Interval a, Interval b) {
  fesetround(FE_DOWNWARD);

  Interval result;

  result.min = a.min - b.max;
  result.max = a.max - b.min;

  result.min = nextafter(result.min, -INFINITY);
  result.max = nextafter(result.max, INFINITY);

  return result;
}

Interval intervalMult(Interval a, Interval b) {
  fesetround(FE_DOWNWARD);

  Interval result;

  result.min = fmin(fmin(a.min * b.min, a.min * b.max),
                    fmin(a.max * b.min, a.max * b.max));
  result.max =
      fmax(fmax(a.min * b.min, a.min * b.max),
           fmax(a.max * b.min, a.max * b.max));

  result.min = nextafter(result.min, -INFINITY);
  result.max = nextafter(result.max,  INFINITY);

  return result;
}

Interval intervalDiv(Interval a, Interval b) {
  fesetround(FE_DOWNWARD);

  Interval aux;
  aux.min = 1 / b.max;
  aux.max = 1 / b.min;

  return intervalMult(a, aux);
}

Interval intervalPow(Interval a, int b) {
  fesetround(FE_DOWNWARD);

  Interval aux;
  // aux.min = 1 / b.max;
  // aux.max = 1 / b.min;

  return intervalMult(a, aux);
}

double intervalMean(Interval a) {
  return (a.min + a.max)/2;
}