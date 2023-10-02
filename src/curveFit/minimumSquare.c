#include "../../include/curveFit.h"

// --------------- Funções Internas

// Cria a matriz Sistema Linear de tamanho n (alocação em vetor único)
LinearSystem *allocLinearSystem(int n){
    LinearSystem *LS = malloc(sizeof(LinearSystem));

    // Alocação do vetor B
    LS->b = malloc(sizeof(Interval) * n);

    // Alocação das linhas
    LS->coef = malloc(sizeof(Interval*) * n);

    // Alocação da matriz como um único vetor
    LS->coef[0] = malloc(sizeof(Interval) * n * n);
    
    // Ajuste dos ponteiros para a posição correta
    for(int i = 1; i < n; i++)
        LS->coef[i] = mat[0] + (i * n);

    return LS;
}

// Calcula os somatórios dos coeficientes do SL criado no Método dos Mínimos Quadrados
// Retorna o vetor de somatório dos coeficientes
Interval *calculateSums(int n, Table *tab, Interval *sumsB){
    int totalSums = 2*n - 1; // 2n-1 somatórios distintos

    Interval *sumsCoef = malloc(sizeof(Interval) * totalSums);
    sumsB = malloc(sizeof(Interval) * n);

    // Calcula os somatórios dos coeficientes da primeira linha e do vetor B
    for(int p = 0; p < n; p++){
        Interval xp = powInterval(tab->x[0], p); // xp = x^p
        Interval sumCoef = xp;

        Interval y_xp = multInterval(tab->y[0], xp); // y_xp = y * x^p
        Interval sumB = y_xp;

        for(int i = 1; i < tab->numPoints; i++){
            xp = powInterval(tab->x[i], p);
            sumCoef = sumInterval(sumCoef, xp);

            y_xp = multInterval(tab->y[i], xp);
            sumB = sumInterval(sumB, yxp);
        }

        sumsCoef[p] = sumCoef;
        sumsB[p] = sumB;
    }

    // Calcula os somatórios dos coeficientes que faltaram
    for(int p = n; p < totalSums; p++){
        Interval xp = powInterval(tab->x[0], p);
        Interval sumCoef = xp;

        for(int i = 1; i < tab->numPoints; i++){
            xp = powInterval(tab->x[i], p);
            sumCoef = sumInterval(sumCoef, xp);
        }
        sumsCoef[p] = sumCoef;
    }

    return sumsCoef;
}

// Constrói o Sistema Linear a ser resolvido
void buildLinearSystem(int n, LinearSystem *LS, Table *tab){
    Interval *sumsB;
    Interval *sumsCoef = calculateSums(n, tab, sumsB);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            LS->coef[i][j] = sumsCoef[i + j];

        LS->b[i] = sumsB[i];
    }
}

// Libera a memória reservada pelo Sistema Linear
void freeLinearSystem(LinearSystem *LS){
    free(LS->coef[0]);
    free(LS->coef);
    free(LS->b);
    free(LS);
}

// --------------- Funções Externas

Interval *minimumSquare(int n, Interval *tab){
    LinearSystem *LS = allocLinearSystem(n);

    buildLinearSystem(n, LS, tab);

    Interval *answer = solveLinearSystem(n, LS);

    freeLinearSystem(LS);

    return answer;
}

