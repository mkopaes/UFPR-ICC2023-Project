#include <stdio.h>
#include <stdlib.h>
#include "../../include/utils.h"

Polynomial *createPolynomial(){
    Polynomial *poly = malloc(sizeof(Polynomial));
    int degree, numCoef;

    scanf("%d", &degree);

    numCoef = (degree + 1);

    poly->min = malloc(numCoef * sizeof(double));
    poly->max = malloc(numCoef * sizeof(double));
    poly->size = numCoef;

    return poly;
}

void freePolynomial(Polynomial *p){ 
    free(p->min);
    free(p->max);
    free(p);
}