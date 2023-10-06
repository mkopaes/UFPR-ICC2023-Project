#include "./interval.h"

#ifndef TABLE_H
#define TABLE_H

typedef struct {
    int numPoints;
    Interval *x;
    Interval *y;
} Table;

// Lê do stdin um valor K e logo em seguida lê K dados no modelo "x y".
// Cria uma tabela intervalar com os dados lidos. Retorna um ponteiro para a tabela criada.
Table *createTable();

// Libera a memória reservada por um tipo Table.
void freeTable(Table *t);

#endif /* TABLE_H */