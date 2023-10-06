#include <stdio.h>

#include "../../include/interval.h"

void printInterval(Interval interval) {
  printf("[%1.8e,%1.8e]", interval.min, interval.max);
}