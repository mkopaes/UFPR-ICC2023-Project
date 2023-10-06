#include <stdlib.h>

#include "../../include/interval.h"

float absError(struct Interval interval) {
  return interval.second.f - interval.first.f;
}

float relError(struct Interval interval) {
  return (interval.second.f - interval.first.f) / interval.first.f;
}

int calcULPs(struct Interval interval) {
  return abs(interval.second.i - interval.first.i);
}
