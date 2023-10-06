#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "../../include/interval.h"

struct Interval *intervalSum(struct Interval a, struct Interval b) {
  fesetround(FE_DOWNWARD);

  struct Interval *result = malloc(sizeof(struct Interval));

  result->first.f = a.first.f + b.first.f;
  result->second.f = a.second.f + b.second.f;

  result->first.f = nextafter(result->first.f, -INFINITY);
  result->second.f = nextafter(result->second.f, INFINITY);

  return result;
}

struct Interval *intervalSub(struct Interval a, struct Interval b) {
  fesetround(FE_DOWNWARD);

  struct Interval *result = malloc(sizeof(struct Interval));

  result->first.f = a.first.f - b.second.f;
  result->second.f = a.second.f - b.first.f;

  result->first.f = nextafter(result->first.f, -INFINITY);
  result->second.f = nextafter(result->second.f, INFINITY);

  return result;
}

struct Interval *intervalMult(struct Interval a, struct Interval b) {
  fesetround(FE_DOWNWARD);

  struct Interval *result = malloc(sizeof(struct Interval));

  result->first.f = fmin(fmin(a.first.f * b.first.f, a.first.f * b.second.f),
                         fmin(a.second.f * b.first.f, a.second.f * b.second.f));
  result->second.f =
      fmax(fmax(a.first.f * b.first.f, a.first.f * b.second.f),
           fmax(a.second.f * b.first.f, a.second.f * b.second.f));

  result->first.f = nextafter(result->first.f, -INFINITY);
  result->second.f = nextafter(result->second.f, INFINITY);

  return result;
}

struct Interval *intervalDiv(struct Interval a, struct Interval b) {
  fesetround(FE_DOWNWARD);

  struct Interval aux;
  aux.first.f = 1 / b.second.f;
  aux.second.f = 1 / b.first.f;

  return intervalMult(a, aux);
}

struct Interval *intervalPow(struct Interval a, struct Interval b) {
  fesetround(FE_DOWNWARD);

  struct Interval aux;
  aux.first.f = 1 / b.second.f;
  aux.second.f = 1 / b.first.f;

  return intervalMult(a, aux);
}
