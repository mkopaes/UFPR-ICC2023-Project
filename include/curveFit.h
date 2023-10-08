#include "./linearSystem.h"

#ifndef CURVEFIT_H
#define CURVEFIT_H

// Calcula o polinômio de grau n resultante do MMQ utilizando os dados da tabela
LinearSystem *minimumSquare(int n, Table *tab, Interval *solution,
                            double *tGeraSl, double *tSolSL);

#endif /* CURVEFIT_H */
