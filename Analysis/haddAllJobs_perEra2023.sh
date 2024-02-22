#!/bin/sh
# Usage:
#    haddAllJobs_perEra2023.sh <AnalysisType> <OutputName>

helpstring="Usage:
haddAllJobs_perEra2023.sh [AnalysisType] [OutputName]
"

ANALYSISTYPE=$1
OUT_NAME=$2


# Check inputs
if [ -z ${2+x} ]
then
echo ${helpstring}
return
fi

# Control channel
if [ ${ANALYSISTYPE} == "control" ]
then
    echo -e "\nDsPhiPi analysis"
    DATATYPE='data_control'
elif [ ${ANALYSISTYPE} == "tau3mu" ]
then
    echo -e "\nTau3mu analysis"
    DATATYPE='data'
fi

for era in B C-v1 C-v2 C-v3 C-v4 D-v1 D-v2
do
	hadd JobAdd_perEra_2023/Era_${era}_${ANALYSISTYPE}.root 2023${era}_*_${ANALYSISTYPE}_${OUT_NAME}/AnalysedTree_${DATATYPE}_2023${era}_*_${ANALYSISTYPE}*.root
done

hadd JobAdd_perEra_2023/Era_C_tau3mu.root JobAdd_perEra_2023/Era_C-v*_tau3mu.root
hadd JobAdd_perEra_2023/Era_D_tau3mu.root JobAdd_perEra_2023/Era_D-v*_tau3mu.root
rm JobAdd_perEra_2023/Era_C-v*_tau3mu.root
rm JobAdd_perEra_2023/Era_D-v*_tau3mu.root
