for era in B C-v1 C-v2 C-v3 C-v4 D-v1 D-v2
do
	hadd JobAdd_perEra/Era_${era}_control.root 2023${era}_*_control_PromptReco/AnalysedTree_data_control_2023${era}_*_control_merged_PromptReco.root
done
