#ifndef CURVEFIT_H
#define CURVEFIT_H

typedef struct {
    double min;
    double max;
} Interval;

typedef struct {
    int numPoints;
    Interval *x;
    Interval *y;
} Table;

typedef struct{
    Interval **coef;
    Interval *b;
} LinearSystem;

// Lê do stdin um valor K e logo em seguida lê K dados no modelo "x y".
// Cria uma tabela intervalar com os dados lidos.
// Retorna um ponteiro para a tabela criada.
Table *createTable();

// Libera a memória reservada por um tipo Table.
void freeTable(Table *t);

// Aplica o Método dos Mínimos Quadrados com base na tabela tab, utilizando um polinômio de grau n-1
Interval *minimumSquare(int n, Interval *tab);

// Debug
void testaValores(Interval *p, Table *t);

#endif
