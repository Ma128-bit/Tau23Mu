#!/bin/sh
# Usage:
#    submitAllJobs.sh <N_files> <AnalysisType>

helpstring="Usage:
submitAllJobs.sh [N_files] [AnalysisType] [OutputName]

N_files: Number of ntuples to be used per job
AnalysisType: Choose between 'tau3mu' and 'control'
"

N_FILES=$1
ANALYSISTYPE=$2
OUT_NAME=$3


# Check inputs
if [ -z ${3+x} ]
then
echo ${helpstring}
return
fi

# Control channel
if [ ${ANALYSISTYPE} == "control" ]
then
    echo -e "\nDsPhiPi MC analysis"
    DATATYPE='data_control'
elif [ ${ANALYSISTYPE} == "tau3mu" ]
then
    echo -e "\nTau3mu MC analysis"
    DATATYPE='data'
fi

if [ ${ANALYSISTYPE} == "tau3mu" ]
then
	for i in Ds_preE Ds_postE B0_preE B0_postE Bp_preE Bp_postE DsPhiPi_preE DsPhiPi_postE
	do
	    echo -e "\nMC dataset $i"
	    echo -e "\npython createRunFile_new.py MC ${ANALYSISTYPE} --n ${N_FILES} --MCprocess $i --outName ${OUT_NAME}"
	    python createRunFile_new.py MC ${ANALYSISTYPE} --n ${N_FILES} --MCprocess $i --outName ${OUT_NAME}
	    sleep 1
	    echo -e "\nsubmit_analysis_${i}_${ANALYSISTYPE}_${OUT_NAME}.sh"
	    source submit_analysis_${i}_${ANALYSISTYPE}_${OUT_NAME}.sh
	    cd ..
	    sleep 1
	done
elif [ ${ANALYSISTYPE} == "control" ]
then
	for i in DsPhiPi_preE DsPhiPi_postE DsPhiMuNu
	do
	    echo -e "\nMC dataset $i"
	    echo -e "\npython createRunFile_new.py MC ${ANALYSISTYPE} --n ${N_FILES} --MCprocess $i --outName ${OUT_NAME}"
	    python createRunFile_new.py MC ${ANALYSISTYPE} --n ${N_FILES} --MCprocess $i --outName ${OUT_NAME}
	    sleep 1
	    echo -e "\nsubmit_analysis_${i}_${ANALYSISTYPE}_${OUT_NAME}.sh"
	    source submit_analysis_${i}_${ANALYSISTYPE}_${OUT_NAME}.sh
	    cd ..
	    sleep 1
	done
fi
