#!/bin/bash

### Old
echo "======================= Parte 1 ======================="
cd Part_1/
make
../gera_entrada $1 | ./ajustePol

###

cd ../

### Optmized
echo "======================= Parte 2 ======================="
cd Part_2/
make
../gera_entrada $1 | ./ajustePol
