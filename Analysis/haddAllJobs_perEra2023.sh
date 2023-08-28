#!/bin/sh
# Usage:
#    haddAllJobs_perEra2023.sh <AnalysisType> <OutputName>

helpstring="Usage:
haddAllJobs_perEra2023.sh [AnalysisType] [OutputName]

N_files: Number of ntuples to be used per job
AnalysisType: Choose between 'tau3mu' and 'control'
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
	hadd JobAdd_perEra/Era_${era}_${ANALYSISTYPE}.root 2023${era}_*_${ANALYSISTYPE}_PromptReco/AnalysedTree_${DATATYPE}_2023${era}_*_${ANALYSISTYPE}_merged_${OUT_NAME}.root
done
