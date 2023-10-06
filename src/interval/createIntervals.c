#include <fenv.h>
#include <math.h>
#include <stdlib.h>

#include "../../include/interval.h"

void createInterval(double num, Interval *inter) {
  fesetround(FE_DOWNWARD);
  inter->min = nextafter(num, -INFINITY);
  inter->max = nextafter(num, INFINITY);
}