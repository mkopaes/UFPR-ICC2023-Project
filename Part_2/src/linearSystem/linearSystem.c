// Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
#include "../../include/linearSystem.h"
#include <likwid.h>
#include <stdio.h>
#include <stdlib.h>

// Aloca memória para o Sistema Linear usado pelo polinônimo de grau n (alocação
// em vetor único)
LinearSystem *allocLinearSystem(int n) {
  LinearSystem *LS = malloc(sizeof(LinearSystem));

  // Grau n = n+1 coeficientes
  n = n + 1;
  LS->size = n;

  // Alocação do vetor B
  LS->b = malloc(sizeof(Interval) * n);

  // Alocação das linhas
  LS->coef = malloc(sizeof(Interval *) * n);

  // Alocação da matriz como um único vetor
  LS->coef[0] = malloc(sizeof(Interval) * n * n);

  // Ajuste dos ponteiros para a posição correta
  for (int i = 1; i < n; i++)
    LS->coef[i] = LS->coef[0] + (i * n);

  return LS;
}

// Calcula os somatórios dos coeficientes do SL criado no Método dos Mínimos
// Quadrados Retorna o vetor de somatório dos coeficientes
void calculateSums(int n, Table *tab, restrict Interval *sumsB, restrict Interval *sumsCoef) {
  // Somatórios vão de expoente zero até 2n
  int totalSums = 2 * n + 1;
  int numCoef = n + 1;

  // Calcula os somatórios dos coeficientes da primeira linha e do vetor B
  for (int p = 0; p < numCoef; p++) {
    Interval xp = intervalPow(tab->x[0], p); // xp = x^p
    Interval sumCoef = xp;

    Interval y_xp = intervalMult(tab->y[0], xp); // y_xp = y * x^p
    Interval sumB = y_xp;

    for (int i = 1; i < tab->numPoints; i++) {
      xp = intervalPow(tab->x[i], p);
      sumCoef = intervalSum(sumCoef, xp);

      y_xp = intervalMult(tab->y[i], xp);
      sumB = intervalSum(sumB, y_xp);
    }

    sumsCoef[p] = sumCoef;
    sumsB[p] = sumB;
  }

  // Calcula os somatórios dos coeficientes que faltaram
  for (int p = numCoef; p < totalSums; p++) {
    Interval xp = intervalPow(tab->x[0], p);
    Interval sumCoef = xp;

    for (int i = 1; i < tab->numPoints; i++) {
      xp = intervalPow(tab->x[i], p);
      sumCoef = intervalSum(sumCoef, xp);
    }
    sumsCoef[p] = sumCoef;
  }
}

// Constrói o Sistema Linear usado no MMQ para um polinômio de grau n,
// utilizando a tabela tab
LinearSystem *buildLinearSystem(int n, Table *tab, double *tGeraSL) {
  LinearSystem *LS = allocLinearSystem(n);

  Interval *sumsB = malloc(sizeof(Interval) * (n + 1));
  Interval *sumsCoef = malloc(sizeof(Interval) * (2 * n + 1));

  LIKWID_MARKER_INIT;

  *tGeraSL = timestamp();
  LIKWID_MARKER_START("Build_Linear_System");

  calculateSums(n, tab, sumsB, sumsCoef);

// Unrol & Jam
  int n_coef = n + 1;
  for (int i = 0; i < n_coef - n_coef%UNRL1; i+=UNRL1) {
    for (int j = 0; j < n_coef; j++) {
      LS->coef[i][j] = sumsCoef[i + j];
      LS->coef[i + 1][j] = sumsCoef[i + 1 + j];
    }

    LS->b[i] = sumsB[i];
    LS->b[i + 1] = sumsB[i + 1];
  }

  // Resíduo
  for (int i = n_coef - n_coef%UNRL1; i < n_coef; i++) {
    for (int j = 0; j < n_coef; j++)
      LS->coef[i][j] = sumsCoef[i + j];

    LS->b[i] = sumsB[i];
  }
// Fim unroll

  LIKWID_MARKER_STOP("Build_Linear_System");
  *tGeraSL = timestamp() - *tGeraSL;

  LIKWID_MARKER_CLOSE;

  free(sumsB);
  free(sumsCoef);

  return LS;
}

// Libera a memória reservada pelo Sistema Linear
void freeLinearSystem(LinearSystem *LS) {
  free(LS->coef[0]);
  free(LS->coef);
  free(LS->b);
  free(LS);
}

Interval *calculateResidualVector(Interval *solution, Table *tab, int size) {
  Interval *residue = malloc(sizeof(Interval) * tab->numPoints);

  for (int i = 0; i < tab->numPoints; i++) {
    Interval res = solution[0];
    Interval powX = tab->x[i]; 

    for (int j = 1; j < size; j++) {
      res = intervalSum(res, intervalMult(solution[j], powX));
      powX = intervalMult(powX, powX);
    }

    residue[i] = intervalSub(tab->y[i], res);
  }

  return residue;
}
