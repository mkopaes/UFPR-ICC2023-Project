// Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
#include "./linearSystem.h"

#ifndef CURVEFIT_H
#define CURVEFIT_H

// Calcula o polinômio de grau "n" resultante de um SL gerado pelo MMQ a partir dos dados de uma tabela "tab"
// e armazena a resposta em um vetor de intervalos "solution". Salva em "tGeraSl" o tempo para gerar o SL e
// salva em "tSolSL" o tempo para resolver o SL.
// Retorna o próprio SL
LinearSystem *minimumSquare(int n, Table *tab, Interval *solution,
                            double *tGeraSl, double *tSolSL);

#endif /* CURVEFIT_H */
