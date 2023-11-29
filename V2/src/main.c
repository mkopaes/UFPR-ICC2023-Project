// Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
#include "../include/curveFit.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Arrange
  int degree_N;
  double tGeraSL, tSolSL, tResiduo;

  scanf("%d", &degree_N);

  Interval *solution = malloc(sizeof(Interval) * (degree_N + 1));
  Table *tab = createTable();

  // Calculate
  LinearSystem *LS = minimumSquare(degree_N, tab, solution, &tGeraSL, &tSolSL);
  Interval *residue =
      calculateResidualVector(solution, tab, LS->size, &tResiduo);

  // Print
  // printIntervalVector(solution, LS->size);
  // printIntervalVector(residue, tab->numPoints);
  printf("TempoGera\n%1.8e\n", tGeraSL);
  printf("TempoSolve\n%1.8e\n", tSolSL);
  printf("TempoResiduo\n%1.8e\n", tResiduo);

  // Free
  freeIntervalVector(solution);
  freeIntervalVector(residue);
  freeLinearSystem(LS);
  freeTable(tab);
  return 0;
}
