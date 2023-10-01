#ifndef UTILS_H
#define UTILS_H

typedef struct {
    int size;
    double *min;
    double *max;
} Polynomial;

typedef struct{
    int numPoints;
    double *x;
    double *y;
} Table;

// Cria a estrutura que irá conter os coeficientes do polinômio
Polynomial *createPolynomial();

// Libera a memória reservada por um polinômio p
void freePolynomial(Polynomial *p);

// Função interna: Aloca memória e cria uma tabela de pontos
Table *createTable();

// Faz a leitura de dados (x, y) e retorna um ponteiro para a tabela criada
Table *readTable();

// Libera a memória reservada por uma tabela t
void freeTable(Table *t);

// Debug
void testaValores(Polynomial *p, Table *t);

#endif