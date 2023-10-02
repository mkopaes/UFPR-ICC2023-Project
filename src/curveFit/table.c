#include <stdio.h>
#include <stdlib.h>
#include "../../include/curveFit.h"

Table *createTable() {
    int x, y, numPoints;

    scanf("%d", &numPoints);

    Table *tab = malloc(sizeof(Table));
    tab->x = malloc(sizeof(Interval) * numPoints);
    tab->y = malloc(sizeof(Interval) * numPoints);
    tab->numPoints = numPoints;

    for(int i = 0; i < numPoints; i++){
        scanf("%lf %lf", &x, &y);
        tab->x[i] = createInterval(x);
        tab->y[i] = createInterval(y);
    }

    return tab;
}

void freeTable(Table *tab) { 
    free(tab->x);
    free(tab->y);
    free(tab); 
}
