#include <math.h>
#include <stdlib.h>

#include "../../include/linearSystem.h"

void substitution(LinearSystem *system, Interval *solution) {
  int size = system->size;

  for (int i = size - 1; i >= 0; i--) {
    solution[i] = system->b[i];
    for (int j = i + 1; j < size; j++)
      solution[i] = intervalSub(solution[i],
                                intervalMult(system->coef[i][j], solution[j]));
    solution[i] = intervalDiv(solution[i], system->coef[i][i]);
  }
}

int findMax(Interval **A, int col, int size) {
  int row = col;

  for (int i = col; i < size; i++) {
    if (fabs(intervalMean(A[i][col])) > fabs(intervalMean(A[row][col]))) {
      row = i;
    }
  }

  return row;
}

void swapRow(LinearSystem *system, int rowA, int rowB) {
  Interval **A = system->coef;
  Interval *B = system->b;

  for (int i = 0; i < system->size; i++) {
    Interval aux = A[rowA][i];
    A[rowA][i] = A[rowB][i];
    A[rowB][i] = aux;
  }

  Interval aux = B[rowA];
  B[rowA] = B[rowB];
  B[rowB] = aux;
}

void gaussElimination(LinearSystem *system) {
  int size = system->size;

  for (int i = 0; i < size; ++i) {
    int rowPivot = findMax(system->coef, i, system->size);

    if (i != rowPivot) {
      swapRow(system, i, rowPivot);
    }

    for (int k = i + 1; k < size; k++) {
      Interval m = intervalDiv(system->coef[k][i], system->coef[i][i]);
      system->coef[k][i].min = 0.0;
      system->coef[k][i].max = 0.0;

      for (int j = i + 1; j < size; j++) {
        system->coef[k][j] = intervalSub(system->coef[k][j],
                                         intervalMult(system->coef[i][j], m));
      }

      system->b[k] = intervalSub(system->b[k], intervalMult(system->b[i], m));
    }
  }
}

void solveLinearSystem(LinearSystem *system, Interval *solution) {
  gaussElimination(system);
  substitution(system, solution);
}
