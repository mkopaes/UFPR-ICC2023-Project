#include <stdlib.h>

#include "../../include/interval.h"

void freeExpression(struct Expression *expression) { free(expression); }

void freeIntervalVector(struct Interval **interval) {
  for (int i = 0; i < OPS + 1; i++) {
    free(interval[i]);
  }

  free(interval);
}

void freeAnsIntervalVector(struct Interval **interval) {
  for (int i = 0; i < OPS; i++) {
    free(interval[i]);
  }

  free(interval);
}
