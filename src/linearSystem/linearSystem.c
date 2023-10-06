#include <stdlib.h>
#include <stdio.h>
#include "../../include/linearSystem.h"

// Aloca memória para o Sistema Linear usado pelo polinônimo de grau n (alocação em vetor único)
LinearSystem *allocLinearSystem(int n){
    LinearSystem *LS = malloc(sizeof(LinearSystem));

    // Grau n = n+1 coeficientes
    n = n + 1;
    LS->size = n;

    // Alocação do vetor B
    LS->b = malloc(sizeof(Interval) * n);

    // Alocação das linhas
    LS->coef = malloc(sizeof(Interval*) * n);

    // Alocação da matriz como um único vetor
    LS->coef[0] = malloc(sizeof(Interval) * n * n);
    
    // Ajuste dos ponteiros para a posição correta
    for(int i = 1; i < n; i++)
        LS->coef[i] = LS->coef[0] + (i * n);

    return LS;
}

// Calcula os somatórios dos coeficientes do SL criado no Método dos Mínimos Quadrados
// Retorna o vetor de somatório dos coeficientes
Interval *calculateSums(int n, Table *tab, Interval *sumsB){
    // Somatórios vão de expoente zero até 2n
    int totalSums = 2*n + 1;
    int numCoef = n + 1;

    Interval *sumsCoef = malloc(sizeof(Interval) * totalSums);
    sumsB = malloc(sizeof(Interval) * numCoef);

    // Calcula os somatórios dos coeficientes da primeira linha e do vetor B
    for(int p = 0; p < numCoef; p++){
        Interval xp = intervalPow(tab->x[0], p); // xp = x^p
        Interval sumCoef = xp;

        Interval y_xp = intervalMult(tab->y[0], xp); // y_xp = y * x^p
        Interval sumB = y_xp;

        for(int i = 1; i < tab->numPoints; i++){
            xp = intervalPow(tab->x[i], p);
            sumCoef = intervalSum(sumCoef, xp);

            y_xp = intervalMult(tab->y[i], xp);
            sumB = intervalSum(sumB, y_xp);
        }

        sumsCoef[p] = sumCoef;
        sumsB[p] = sumB;
    }

    // Calcula os somatórios dos coeficientes que faltaram
    for(int p = numCoef; p < totalSums; p++){
        Interval xp = intervalPow(tab->x[0], p);
        Interval sumCoef = xp;

        for(int i = 1; i < tab->numPoints; i++){
            xp = intervalPow(tab->x[i], p);
            sumCoef = intervalSum(sumCoef, xp);
        }
        sumsCoef[p] = sumCoef;
    }

    return sumsCoef;
}

// Constrói o Sistema Linear usado no MMQ para um polinômio de grau n, utilizando a tabela tab
LinearSystem *buildLinearSystem(int n, Table *tab){
    LinearSystem *LS = allocLinearSystem(n);
    Interval *sumsB;
    Interval *sumsCoef = calculateSums(n, tab, sumsB);

    for(int i = 0; i < n + 1; i++){
        for(int j = 0; j < n + 1; j++)
            LS->coef[i][j] = sumsCoef[i + j];

        LS->b[i] = sumsB[i];
    }

    return LS;
}

// Libera a memória reservada pelo Sistema Linear
void freeLinearSystem(LinearSystem *LS){
    free(LS->coef[0]);
    free(LS->coef);
    free(LS->b);
    free(LS);
}


// Revisar aqui pra BAIXO

Interval *calculateResidualVector(LinearSystem *system, Interval *solution) {
  Interval *residue = malloc(sizeof(Interval) * system->size);

  for (int i = 0; i < system->size; i++) {
    Interval res;
    createInterval(0.0, &res);

    for (int j = 0; j < system->size; j++) {
        res = intervalSum(res, intervalMult(system->coef[i][j], solution[j]));
    }
    residue[i] = intervalSub(res, system->b[i]);
  }

  return residue;
}

void printResidualVector(double *residualVector, int size) {
  printf("Resíduo = [ ");
  for (int i = 0; i < size; i++) {
    printf("%lf ", residualVector[i]);
  }
  printf("]\n");
}