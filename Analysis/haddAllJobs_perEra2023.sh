for era in B C-v1 C-v2 C-v3 C-v4
do
	hadd JobAdd_perEra/Era_${era}_control.root 2023${era}_*_control_ReReco/AnalysedTree_data_control_2023${era}_*_control_merged_ReReco.root
done
