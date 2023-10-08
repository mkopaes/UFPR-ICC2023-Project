// Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
#include "./interval.h"
#include "./table.h"
#include "./utils.h"
#include <sys/time.h>

#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

typedef struct {
  Interval **coef;
  Interval *b;
  int size;
} LinearSystem;

LinearSystem *buildLinearSystem(int n, Table *tab, double *tGeraSL);

void solveLinearSystem(LinearSystem *system, Interval *solution);

Interval *calculateResidualVector(Interval *solution, Table *tab, int size);

void freeLinearSystem(LinearSystem *LS);

#endif /* LINEAR_SYSTEM_H */
