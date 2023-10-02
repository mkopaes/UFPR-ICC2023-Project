#include "../include/curveFit.h"
#include <stdio.h>

int main(){
    int degree_N, numCoef;

    scanf("%d", &degree_N);

    // Se o grau é N, temos N + 1 coeficientes
    numCoef = degree_N + 1;

    Table *tab = createTable();
    Interval *answer = minimumSquare(numCoef, tab);
    Interval *residual = calculateResidual(answer, tab);

    printVectorInterval(answer, numCoef);
    printVectorInterval(residual, numCoef);

    freeInterval(answer);
    freeInterval(residual);
    freeTable(tab);
    return 0;
}