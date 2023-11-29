#!/bin/bash

# Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158

# METRICA="FLOPS_DP ENERGY" 
METRICA="FLOPS_DP" 

make

for k in $METRICA
do
  likwid-perfctr -C 3 -g ${k} -m ./ajustePol < pontos.in > ${k}_resultado.log
done

# printf "Resultado: \n" > resultado.out
# ./ajustePol < pontos.in >> resultado.out
# printf "\n" >> resultado.out

# echo "Build Linear System" >> resultado.out
# cat FLOPS_DP_resultado.log | grep -m 1 "DP MFLOP/s (scalar assumed)" >> resultado.out
# cat FLOPS_DP_resultado.log | grep -m 1 "DP MFLOP/s (AVX assumed)" >> resultado.out
# cat ENERGY_resultado.log | grep -m 1 "Energy Core" >> resultado.out
# printf "\n" >> resultado.out
# echo "Solve Linear System" >> resultado.out
# cat FLOPS_DP_resultado.log | grep -m 2 "DP MFLOP/s (scalar assumed)" | tail -n 1 >> resultado.out
# cat FLOPS_DP_resultado.log | grep -m 2 "DP MFLOP/s (AVX assumed)" | tail -n 1 >> resultado.out
# cat ENERGY_resultado.log | grep -m 2 "Energy Core" | tail -n 1 >> resultado.out

# make purge
