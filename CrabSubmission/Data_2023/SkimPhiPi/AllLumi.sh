#!/bin/sh
# Usage:
#    AllLumi.sh

echo -e "\nData 2022_RunC"
cd reco2022_RunC
cd crab_projects
for i in 0 1 2 3 4 5 6 7
do
    echo -e "\nData $i"
    cd crab_SkimDsPhiPi_2022eraC_stream${i}_Mini_v3
    cd results
    brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json -u /fb -i processedLumis.json --hltpath "HLT_DoubleMu3_Trk_Tau3mu_v*"
    cd ..
    cd ..
    sleep 1
done
cd ..
cd ..
