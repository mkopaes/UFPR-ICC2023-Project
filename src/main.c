#include "../include/curveFit.h"
#include <stdio.h>

int main(){
    Interval *solution;
    int degree_N;

    scanf("%d", &degree_N);

    Table *tab = createTable();
    LinearSystem *LS = minimumSquare(degree_N, tab, solution);
    Interval *residue = calculateResidualVector(LS, solution);

    //printVectorInterval(answer, numCoef);
    //printVectorInterval(residual, numCoef);

    //freeInterval(answer);
    //freeInterval(residual);
    freeTable(tab);
    return 0;
}