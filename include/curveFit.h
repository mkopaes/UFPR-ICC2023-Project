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
// Cria uma tabela intervalar com os dados lidos. Retorna um ponteiro para a tabela criada.
Table *createTable();

// Libera a memória reservada por um tipo Table.
void freeTable(Table *t);

// Calcula o polinômio de grau n resultante do MMQ utilizando os dados da tabela tab
Interval *minimumSquare(int n, Table *tab);

// Debug
void testaValores(Interval *p, Table *t);

#endif