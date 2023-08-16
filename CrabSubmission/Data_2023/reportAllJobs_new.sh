#!/bin/sh
# Usage:
#    reportAllJobs.sh

#cd SkimTau3mu
#for i in 2023_RunB 2023_RunC-v1 2023_RunC-v2 2023_RunC-v3 2023_RunC-v4 
#do
#    echo -e "\nData $i"
#    cd reco${i}
#    source report.sh
#    cd ..
#    sleep 1
#done

#cd ..
cd SkimPhiPi
for i in 2023_RunB 2023_RunC-v1 2023_RunC-v2 2023_RunC-v3 2023_RunC-v4
do
    echo -e "\nData $i"
    cd reco${i}
    source report.sh
    cd ..
    sleep 1
done
