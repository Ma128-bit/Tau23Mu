outlable="PromptReco"
rm -r JobAdd_perEra
mkdir JobAdd_perEra
for era in C D-v1 D-v2 E F G
do
	hadd JobAdd_perEra/Era_${era}_tau3mu.root 2022${era}_*_tau3mu_${outlable}/AnalysedTree_data_2022${era}_*_tau3mu*.root
	hadd JobAdd_perEra/Era_${era}_control.root 2022${era}_*_control_${outlable}/AnalysedTree_data_control_2022${era}_*_control*.root
done

hadd JobAdd_perEra/Era_D_tau3mu.root JobAdd_perEra/Era_D-v*_tau3mu.root
hadd JobAdd_perEra/Era_D_control.root JobAdd_perEra/Era_D-v*_control.root
rm JobAdd_perEra/Era_D-v*.root

for MC in B0_preE B0_postE Bp_preE Bp_postE DsPhiPi_postE DsPhiPi_preE Ds_preE Ds_postE
do
  	echo "Start MC_${MC}!"
        hadd JobAdd_perEra/MC_${MC}.root ${MC}_tau3mu_${outlable}/AnalysedTree_MC_${MC}_tau3mu*.root
done

