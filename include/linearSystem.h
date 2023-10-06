#include <sys/time.h>

#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

struct LinearSystem {
  double **m;
  double *b;
  int size;
};

struct LinearSystem *createLinearSystem(int size);

void readLinearSystem(struct LinearSystem *system);

struct LinearSystem *copyLinearSystem(struct LinearSystem *system);

double *solveLinearSystem(struct LinearSystem *system);

void printSolution(double *solution, int size);

double *calculateResidualVector(struct LinearSystem *system, double *solution);

void printResidualVector(double *residualVector, int size);

void printTime(struct timeval start, struct timeval end);

void freeSystem(struct LinearSystem *system);

void freeDoubleArray(double *array);

#endif
