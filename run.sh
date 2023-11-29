#!/bin/bash

# Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158

# Ns="64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000"
Ns="64 128 200 256 512 600 800 1024"
METRICA="FLOPS_DP L3 L2CACHE" 
LOGS_FOLDER="logs/"
RESULT_FOLDER="resultados/"
VERSIONS="V1 V2"

# ================================ PREPARA AMBIENTE ================================
for VERSION in $VERSIONS
do
  cd ${VERSION}
  make
  cd ..
done

if [ ! -d "${RESULT_FOLDER}" ]; then
  mkdir "${RESULT_FOLDER}"
fi

if [ ! -d "${LOGS_FOLDER}" ]; then
  mkdir "${LOGS_FOLDER}"
fi

# ================================ PERCORRE AS VERSOES ================================
for n in $Ns
do
  echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
  printf "\n\n N = ${n}\n\n"

  # ================================ PERCORRE OS PONTOS ================================
  for VERSION in $VERSIONS
  do
    cd ${VERSION}
    # ============================= PERCORRE AS METRICAS LIKWID =============================
    for k in $METRICA
    do
      ../gera_entrada $n | likwid-perfctr -C 3 -g ${k} -m ./ajustePol > ../${LOGS_FOLDER}${k}_${n}_${VERSION}.log
    done

    ../gera_entrada $n | ./ajustePol > ../${LOGS_FOLDER}TIME_${n}_${VERSION}.log
    
    cd ..
  done

  # Tempo 
  TIME_NAMES="TempoGera TempoSolve TempoResiduo"
  GROUP="TIME"
  for NAME in $TIME_NAMES
  do
    if [ ! -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      touch "${RESULT_FOLDER}${NAME}.csv"
    fi

    if [ -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      echo -n "$n," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V1.log | grep -A 1 "${NAME}" | tail -n 1 | tr -d '\n' >> "${RESULT_FOLDER}${NAME}.csv"
      echo -n "," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V2.log | grep -A 1 "${NAME}" | tail -n 1 >> "${RESULT_FOLDER}${NAME}.csv"
    fi
  done

  # Mem 
  L3_NAMES="L3Gera L3Residuo"
  GROUP="L3"
  i=1
  for NAME in $L3_NAMES
  do
    if [ ! -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      touch "${RESULT_FOLDER}${NAME}.csv"
    fi

    if [ -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      echo -n "$n," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V1.log | grep -m $i "L3 bandwidth" | tail -n 1 | grep -oE '[0-9]+\.[0-9]+' | tr -d '\n' >> "${RESULT_FOLDER}${NAME}.csv"
      echo -n "," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V2.log | grep -m $i "L3 bandwidth" | tail -n 1 | grep -oE '[0-9]+\.[0-9]+'  >> "${RESULT_FOLDER}${NAME}.csv"
      let "i+=2"
    fi
  done

  #Cache 
  L2CACHE_NAMES="L2Gera L2Residuo"
  GROUP="L2CACHE"
  i=1
  for NAME in $L2CACHE_NAMES
  do
    if [ ! -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      touch "${RESULT_FOLDER}${NAME}.csv"
    fi

    if [ -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      echo -n "$n," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V1.log | grep -m $i "L2 miss ratio" | tail -n 1 | grep -oE '[0-9]+\.[0-9]+' | tr -d '\n' >> "${RESULT_FOLDER}${NAME}.csv"
      echo -n "," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V2.log | grep -m $i "L2 miss ratio" | tail -n 1 | grep -oE '[0-9]+\.[0-9]+' >> "${RESULT_FOLDER}${NAME}.csv"
      let "i+=2"
    fi
  done

  # Flops 
  FLOPS_NAMES="FlopsDPGera FlopsDPSolve FlopsDPResiduo"
  GROUP="FLOPS_DP"
  i=1
  for NAME in $FLOPS_NAMES
  do
    if [ ! -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      touch "${RESULT_FOLDER}${NAME}.csv"
    fi

    if [ -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      echo -n "$n," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V1.log | grep -m $i "DP MFLOP\/s" | tail -n 1 | grep -oE '[0-9]+(\.[0-9]+)?' | tr -d '\n' >> "${RESULT_FOLDER}${NAME}.csv"
      echo -n "," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V2.log | grep -m $i "DP MFLOP\/s"| tail -n 1 | grep -oE '[0-9]+(\.[0-9]+)?' >> "${RESULT_FOLDER}${NAME}.csv"
      let "i+=2"
    fi
  done

  # AVX 
  FLOPS_NAMES="FlopsAVXGera FlopsAVXSolve FlopsAVXResiduo"
  GROUP="FLOPS_DP"
  i=1
  for NAME in $FLOPS_NAMES
  do
    if [ ! -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      touch "${RESULT_FOLDER}${NAME}.csv"
    fi

    if [ -f "${RESULT_FOLDER}${NAME}.csv" ]; then
      echo -n "$n," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V1.log | grep -m $i "AVX DP MFLOP\/s" | tail -n 1 | grep -oE '[0-9]+(\.[0-9]+)?' | tr -d '\n' >> "${RESULT_FOLDER}${NAME}.csv"
      echo -n "," >> "${RESULT_FOLDER}${NAME}.csv" 
      cat ${LOGS_FOLDER}${GROUP}_${n}_V2.log | grep -m $i "AVX DP MFLOP\/s"| tail -n 1 | grep -oE '[0-9]+(\.[0-9]+)?'>> "${RESULT_FOLDER}${NAME}.csv"
      let "i+=1"
    fi
  done

done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
# make clean
