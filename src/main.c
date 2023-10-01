#include "../include/utils.h"
#include <stdio.h>

int main(){
    Polynomial *answer = createPolynomial();
    Table *tab = readTable();
    
    freePolynomial(answer);
    return 0;
}