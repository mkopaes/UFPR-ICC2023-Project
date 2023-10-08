#!/bin/bash

make
likwid-perfctr -C 0-3 -g "FLOPS_DP,FLOPS_AVX,ENERGY" -m ./ajustePol < pontos.in > resultado.out
make purge
