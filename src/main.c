#include "../include/curveFit.h"
#include <stdio.h>

int main(){
    int degree_N;

    scanf("%d", &degree_N);

    Table *tab = createTable();
    Interval *answer = minimumSquare(degree_N, tab);
    //Interval *residual = calculateResidual(answer, tab);

    //printVectorInterval(answer, numCoef);
    //printVectorInterval(residual, numCoef);

    //freeInterval(answer);
    //freeInterval(residual);
    freeTable(tab);
    return 0;
}