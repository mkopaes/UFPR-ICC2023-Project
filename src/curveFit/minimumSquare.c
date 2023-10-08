#include "../../include/curveFit.h"
#include <likwid.h>
#include <stdlib.h>

LinearSystem *minimumSquare(int n, Table *tab, Interval *solution,
                            double *tGeraSl, double *tSolSL) {
  LinearSystem *LS = buildLinearSystem(n, tab, tGeraSl);

  LIKWID_MARKER_INIT;

  *tSolSL = timestamp();
  LIKWID_MARKER_START("Solve_Linear_System");

  solveLinearSystem(LS, solution);

  LIKWID_MARKER_STOP("Solve_Linear_System");
  *tSolSL = timestamp() - *tSolSL;

  LIKWID_MARKER_CLOSE;

  return LS;
}
