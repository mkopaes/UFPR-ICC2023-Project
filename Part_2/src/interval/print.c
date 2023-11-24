// Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
#include <stdio.h>

#include "../../include/interval.h"

void printInterval(Interval interval) {
  printf("[%1.8e,%1.8e]", interval.min, interval.max);
}

void printIntervalVector(Interval *interval, int size) {
  for (int i = 0; i < size; i++) {
    printInterval(interval[i]);
    printf(" ");
  }
  printf("\n");
}
