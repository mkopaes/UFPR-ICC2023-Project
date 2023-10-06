#include "./linearSystem.h"

#ifndef CURVEFIT_H
#define CURVEFIT_H


// Calcula o polinômio de grau n resultante do MMQ utilizando os dados da tabela tab
LinearSystem *minimumSquare(int n, Table *tab, Interval *solution);

// Debug
void testaValores(Interval *p, Table *t);

#endif /* CURVEFIT_H */