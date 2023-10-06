#include <sys/time.h>
#include "./interval.h"
#include "./table.h"

#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

typedef struct{
    Interval **coef;
    Interval *b;
    int size;
} LinearSystem;

LinearSystem *buildLinearSystem(int n, Table *tab);

Interval *solveLinearSystem(LinearSystem *system);

void printSolution(double *solution, int size);

Interval *calculateResidualVector(LinearSystem *system, Interval *solution);

void printResidualVector(double *residualVector, int size);

void freeLinearSystem(LinearSystem *LS);

//void printTime(timeval start, timeval end);

//void freeSystem(LinearSystem *system);

//void freeDoubleArray(double *array);

#endif /* LINEAR_SYSTEM_H */
