// Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
#include "./interval.h"

#ifndef TABLE_H
#define TABLE_H

// Estrutura para armazenar uma tabela com "numPoints" pares ordenados (x, y)
// Os dados da tabela são armazenados num vetor de intervalos "x" e "y"
typedef struct {
  int numPoints;
  Interval *x;
  Interval *y;
} Table;

// Lê do stdin um valor K e logo em seguida lê K dados no modelo "x y".
// Cria uma tabela intervalar com os dados lidos. 
// Retorna um ponteiro para a tabela criada.
Table *createTable();

// Libera a memória reservada por um tipo Table.
void freeTable(Table *t);

#endif /* TABLE_H */
