for era in C D E F G
do
	hadd JobAdd_perEra/Era_${era}_tau3mu.root 2022${era}_*_tau3mu_ReReco/AnalysedTree_data_2022${era}_*_tau3mu_merged_ReReco.root
done

