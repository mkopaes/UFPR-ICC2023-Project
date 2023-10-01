#include <stdio.h>
#include <stdlib.h>
#include "../../include/utils.h"

Table *createTable() {
    Table *tab = malloc(sizeof(Table));
    scanf("%d", &tab->numPoints);

    tab->x = malloc(tab->numPoints * sizeof(double));
    tab->y = malloc(tab->numPoints * sizeof(double));

    return tab;
}

Table *readTable() {
    Table *tab = createTable();

    for(int i = 0; i < tab->numPoints; i++)
        scanf("%lf %lf", &tab->x[i], &tab->y[i]);

    return tab;
}

void freeTable(Table *t) { 
    free(t->x);
    free(t->y);
    free(t); 
}
