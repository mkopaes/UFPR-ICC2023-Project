#include <fenv.h>
#include <math.h>
#include <stdlib.h>

#include "../../include/interval.h"

struct Interval *makeInterval(float num) {
  struct Interval *inter = malloc(sizeof(struct Interval));

  fesetround(FE_DOWNWARD);

  inter->first.f = nextafter(num, -INFINITY);
  inter->second.f = nextafter(num, INFINITY);

  return inter;
}

struct Interval **makeIntervalVector(struct Expression *expr) {
  struct Interval **intervalVectors =
      malloc(sizeof(struct Interval *) * (OPS + 1));

  for (int i = 0; i < OPS + 1; i++) {
    intervalVectors[i] = makeInterval(expr->nums[i].f);
  }

  return intervalVectors;
}
