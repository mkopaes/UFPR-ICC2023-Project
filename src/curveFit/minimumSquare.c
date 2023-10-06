#include <stdlib.h>
#include "../../include/curveFit.h"

LinearSystem *minimumSquare(int n, Table *tab, Interval *solution){
    LinearSystem *LS = buildLinearSystem(n, tab);
    solution = solveLinearSystem(LS);
    return LS;
}

