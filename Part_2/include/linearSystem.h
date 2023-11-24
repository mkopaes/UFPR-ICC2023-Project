// Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
#include "./interval.h"
#include "./table.h"
#include "./utils.h"
#include <sys/time.h>

#ifndef LINEAR_SYSTEM_H
#define LINEAR_SYSTEM_H

#define UNRL1 2

// Estrutura para representar nosso SL, no formato de uma matriz de coeficientes "coef" 
// de tamanho "size"x"size" e um vetor b de tamanho "size"
typedef struct {
  Interval **coef;
  Interval *b;
  int size;
} LinearSystem;

// Realiza a construção do SL de intervalos utilizado no MMQ para o ajuste a um polinômio de grau "n",
// utilizando os dados da tabela "tab", armazena o tempo gasto no processo em "tGeraSL". 
// Retorna o SL
LinearSystem *buildLinearSystem(int n, Table *tab, double *tGeraSL);

// Resolve o SL de intervalos "system" e armazena a resposta no vetor de intervalos "solution"
void solveLinearSystem(LinearSystem *system, Interval *solution);

// Calcula os resíduos de um polinômio "solution" com "size" coeficientes a partir dos dados
// de um tabela de intervalos "tab"
// Retorna os resíduos em um vetor de intervalos
Interval *calculateResidualVector(Interval *solution, Table *tab, int size);

// Faz a liberação da memória de um sistema linear SL
void freeLinearSystem(LinearSystem *LS);

#endif /* LINEAR_SYSTEM_H */
