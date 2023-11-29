#!/bin/bash

if [ ! -d "graphs" ]; then
  mkdir "graphs"
fi

OUT=("Cache_miss_L2_Gera" "Cache_miss_L2_Residuo"
     "Banda_De_Memoria_Gera" "Banda_De_Memoria_Residuo"
     "Tempo_Medio_Gera" "Tempo_Medio_Solve" "Tempo_Medio_Residuo"
     "FlopsDP_Gera" "FlopsDP_Solve" "FlopsDP_Residuo"
     "FlopsAVXDP_Gera" "FlopsAVX_Solve" "FlopsAVX_Residuo")

FILENAMES=("L2Gera.csv" "L2Residuo.csv"
           "L3Gera.csv" "L3Residuo.csv"
           "TempoGera.csv" "TempoSolve.csv" "TempoResiduo.csv"
           "FlopsDPGera.csv" "FlopsDPSolve.csv" "FlopsDPResiduo.csv"
           "FlopsAVXGera.csv" "FlopsAVXSolve.csv" "FlopsAVXResiduo.csv")

TITLES=("Cache miss L2 Gera" "Cache miss L2 Residuo"
        "Banda De Memória Gera" "Banda De Memória Residuo"
        "Tempo Médio Gera" "Tempo Médio Solve" "Tempo Médio Residuo"
        "FlopsDP Gera" "FlopsDP Solve" "FlopsDP Residuo"
        "FlopsAVXDP Gera" "FlopsAVX Solve" "FlopsAVX Residuo")

YLABELS=("Cache Miss L2 (ratio)" "Cache Miss L2 (ratio)"
         "Banda de Memória (MBYTE/s)" "Banda de Memória (MBYTE/s)"
         "Tempo (milisegundos)" "Tempo (milisegundos)" "Tempo (milisegundos)"
         "MFLOP/s" "MFLOP/s" "MFLOP/s"
         "MFLOP/s" "MFLOP/s" "MFLOP/s")

for i in {0..12}
do
  gnuplot <<- EOM
  set terminal png size 1080, 1080 enhanced font 'Helvetica,20' linewidth 3
  set output "./graphs/${OUT[$i]}.png"
  set title "${TITLES[$i]}"
  set xlabel "Número de pontos"
  set ylabel "${YLABELS[$i]}"
  set grid
  set logscale x

  set datafile separator ","

  plot "./resultados/${FILENAMES[$i]}" \
          using 1:2 \
          w lp \
          lt 5 \
          lc 7 \
          title 'Sem otimização (V1)', \
       "./resultados/${FILENAMES[$i]}"\
          using 1:3 \
          w lp \
          lt 7 \
          lc 6 \
          title 'Com otimização (V2)'
EOM
done

# gnuplot <<- EOM
# set terminal png size 1080, 1080 enhanced font 'Helvetica,20' linewidth 3 
# set output "./graphs/FLOPS_MMM.png"
# set title "Operações Aritméticas MMM"
# set xlabel "Tamanho da matriz"
# set ylabel "MFLOP/s"
# set grid
#
# set datafile separator ","
#
# plot "./resultados/AritmeticaMatMat.csv" \
#         using 1:2 \
#         w lp \
#         lt 5 \
#         lc 7 \
#         title 'FLOPS DP Sem otimização', \
#      "./resultados/AritmeticaMatMat.csv"\
#         using 1:3 \
#         w lp \
#         lt 7 \
#         lc 6 \
#         title 'FLOPS DP Com otimização', \
#      "./resultados/AritmeticaMatMat.csv"\
#         using 1:4 \
#         w lp \
#         lt 7 \
#         lc 9 \
#         title 'FLOPS AVX Com otimização', \
#      "./resultados/AritmeticaMatMat.csv"\
#         using 1:5 \
#         w lp \
#         lt 7 \
#         lc 4 \
#         title 'FLOPS AVX Com otimização'
# EOM
#
# gnuplot <<- EOM
# set terminal png size 1080, 1080 enhanced font 'Helvetica,20' linewidth 3
# set output "./graphs/FLOPS_MVM.png"
# set title "Operações Aritméticas MVM"
# set xlabel "Tamanho da matriz"
# set ylabel "MFLOP/s"
# set grid
#
# set datafile separator ","
#
# plot "./resultados/AritmeticaMatMat.csv" \
#         using 1:2 \
#         w lp \
#         lt 5 \
#         lc 7 \
#         title 'FLOPS DP Sem otimização', \
#      "./resultados/AritmeticaMatVet.csv"\
#         using 1:3 \
#         w lp \
#         lt 7 \
#         lc 6 \
#         title 'FLOPS DP Com otimização', \
#      "./resultados/AritmeticaMatVet.csv"\
#         using 1:4 \
#         w lp \
#         lt 7 \
#         lc 9 \
#         title 'FLOPS AVX Com otimização', \
#      "./resultados/AritmeticaMatVet.csv"\
#         using 1:5 \
#         w lp \
#         lt 7 \
#         lc 4 \
#         title 'FLOPS AVX Com otimização'
# EOM
