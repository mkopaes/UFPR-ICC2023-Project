// Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
#include <stdint.h>

#ifndef INTERVAL_H
#define INTERVAL_H

// Estrutura de um intervalo no formato [min, max]
typedef struct {
  double min;
  double max;
} Interval;

// A partir de um double "num" cria um tipo intervalo, salvando-o no ponteiro "inter"
void createInterval(double num, Interval *inter);

// Realiza a soma de dois intervalos (a + b)
// Retorna o resultado da operação
Interval intervalSum(Interval a, Interval b);

// Realiza a subtração de dois intevalos (a - b)
// Retorna o resultado da operação
Interval intervalSub(Interval a, Interval b);

// Realiza a multiplicação de dois intervalos (a * b)
// Retorna o resultado da operação
Interval intervalMult(Interval a, Interval b);

// Realiza a divisão de dois intervalos (a / b)
// Retorna o resultado da operação
Interval intervalDiv(Interval a, Interval b);

// Realiza a potenciação de um intervalo por um inteiro (a ^ b)
// Retorna o resultado da operação
Interval intervalPow(Interval a, int b);

// Calcula o valor médio de um intervalo a
// Retorna o resultado da operação
double intervalMean(Interval a);

// Realiza a impressão de um intervalo a
void printInterval(Interval a);

// Realiza a impressão de um vetor de intervalos "interval" de tamanho "size"
void printIntervalVector(Interval *interval, int size);

// Libera da memório um vetor de intervalos "interval"
void freeIntervalVector(Interval *interval);

#endif /* INTERVAL_H */
