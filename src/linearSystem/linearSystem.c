#include <stdio.h>
#include <stdlib.h>

#include "../include/linearSystem.h"

struct LinearSystem *createLinearSystem(int size) {
  struct LinearSystem *system = malloc(sizeof(struct LinearSystem));

  system->size = size;
  system->b = malloc(sizeof(double) * size);
  system->m = malloc(sizeof(double) * size);

  for (int i = 0; i < size; i++) {
    system->m[i] = malloc(sizeof(double) * size);
  }

  return system;
}

void readLinearSystem(struct LinearSystem *system) {
  int size = system->size;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j <= size; j++) {
      if (j == size) {
        scanf("%lf", &system->b[i]);
      } else {
        scanf("%lf", &system->m[i][j]);
      }
    }
  }
}

struct LinearSystem *copyLinearSystem(struct LinearSystem *system) {
  int size = system->size;

  struct LinearSystem *systemCopy = createLinearSystem(size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      systemCopy->m[i][j] = system->m[i][j];
    }
  }

  for (int i = 0; i < size; i++) {
    systemCopy->b[i] = system->b[i];
  }

  return systemCopy;
}

double *calculateResidualVector(struct LinearSystem *system, double *solution) {
  double *residue = malloc(sizeof(double) * system->size);

  for (int i = 0; i < system->size; i++) {
    double res = 0;
    for (int j = 0; j < system->size; j++) {
      res += system->m[i][j] * solution[j];
    }
    residue[i] = res - system->b[i];
  }

  return residue;
}

void printResidualVector(double *residualVector, int size) {
  printf("Resíduo = [ ");
  for (int i = 0; i < size; i++) {
    printf("%lf ", residualVector[i]);
  }
  printf("]\n");
}

void printSolution(double *solution, int size) {
  printf("X = [ ");
  for (int i = 0; i < size; i++) {
    printf("%lf ", solution[i]);
  }
  printf("]\n");
}

void freeSystem(struct LinearSystem *system) {
  free(system->b);

  for (int i = 0; i < system->size; i++) {
    free(system->m[i]);
  }

  free(system->m);
  free(system);
}

void freeDoubleArray(double *array) { free(array); }
