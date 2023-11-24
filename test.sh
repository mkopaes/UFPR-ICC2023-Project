#!/bin/bash

### Old
echo "======================= Parte 1 ======================="
cd Part_1/
make
./ajustePol < ../pontos.in

###

cd ../

### Optmized
echo "======================= Parte 2 ======================="
cd Part_2/
make
./ajustePol < ../pontos.in
