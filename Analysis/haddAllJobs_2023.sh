#!/bin/sh
# Usage:
#    submitAllJobs.sh <N_files> <AnalysisType>

helpstring="Usage:
haddAllJobs.sh [AnalysisType] [OutputName]

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

for i in 2023B_0 2023B_1 2023B_2 2023B_3 2023B_4 2023B_5 2023B_6 2023B_7 2023C-v1_0 2023C-v1_1 2023C-v1_2 2023C-v1_3 2023C-v1_4 2023C-v1_5 2023C-v1_6 2023C-v1_7 2023C-v2_0 2023C-v2_1 2023C-v2_2 2023C-v2_3 2023C-v2_4 2023C-v2_5 2023C-v2_6 2023C-v2_7 2023C-v3_0 2023C-v3_1 2023C-v3_2 2023C-v3_3 2023C-v3_4 2023C-v3_5 2023C-v3_6 2023C-v3_7 2023C-v4_0 2023C-v4_1 2023C-v4_2 2023C-v4_3 2023C-v4_4 2023C-v4_5 2023C-v4_6 2023C-v4_7 2023D-v1_0 2023D-v1_1 2023D-v1_2 2023D-v1_3 2023D-v1_4 2023D-v1_5 2023D-v1_6 2023D-v1_7 2023D-v2_0 2023D-v2_1 2023D-v2_2 2023D-v2_3 2023D-v2_4 2023D-v2_5 2023D-v2_6 2023D-v2_7
do
    echo -e "\nData $i"
    cd ${i}_${ANALYSISTYPE}_${OUT_NAME}
    echo -e "hadd AnalysedTree_${DATATYPE}_${i}_${ANALYSISTYPE}_merged_${OUT_NAME}.root AnalysedTree_${DATATYPE}_${i}_${ANALYSISTYPE}*.root"
    rm AnalysedTree_${DATATYPE}_${i}_${ANALYSISTYPE}_merged_${OUT_NAME}.root
    hadd AnalysedTree_${DATATYPE}_${i}_${ANALYSISTYPE}_merged_${OUT_NAME}.root AnalysedTree_${DATATYPE}_${i}_${ANALYSISTYPE}*.root
    cd ..
    sleep 1
done

