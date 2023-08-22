# Ntuplizer and analysis code for the Tau&rarr;3mu search at Run 3

## Setting the environment

```
cmsrel CMSSW_12_4_11_patch3
cd CMSSW_12_4_11_patch3/src
cmsenv
git clone https://github.com/BariGEMJetTau/Tau23Mu.git .
scram b -j20
```
<p>&nbsp;</p>

## Make the ntuples
The ntuples useful for the analysis can be created both for the tau3mu and the control channel. This can be done by using the skims in the:
* `SkimTools/X` with `X` = `SkimTau3Mu, SkimPhiPi` \
which use the plugins in the directories `MiniAnaTau3Mu` and `DsPhiPiTreeMakerMINI`, respectively.

Example:
```
cmsRun SkimTools/SkimTau3Mu/test/run_MC2022_PatAndTree_cfg.py
```

To run the ntuple production on the grid, the crab configurations files for the submission of the jobs are in the `CrabSubmission` directory.

Example:
```
crab submit -c crab_Tau3mu_reco2023_RunC-v1_stream0_cfg.py 
```

Tto submit all the jobs use:
```
submitAllJobs.sh
```
<p>&nbsp;</p>

## Run the analysis
The analysis of the ntuples is performed by using:
* `myAnalizer.C` for the tau3mu search
* `myAnalizer_control.C` for the control channel 

<p>&nbsp;</p>

### Run analysis on single datasets (using the batch system)
The script `createRunFile_new.py` allows for the creation of jobs for the submission of the analysis on the batch system.
* If you want to run on a MC sample:
```
python createRunFile_new.py [DatasetType] [AnalysisType] --n [NTreesPerJob] --MCprocess [MCprocess_name] --outName [outNameLabel]
```
* If you want to run on data sample:
```
python createRunFile_new.py --run [DataEra] --n [NTreesPerJob] [DatasetType] [AnalysisType] --outName [outNameLabel]
```
    * `DatasetType` = `MC`, `data`, `data_control`
    * `AnalysisType` = `tau3mu`, `control`
    * `DataEra` = `2022C_0`, ..., `2022G_7`
    * `MCprocess_name` = `Ds_preE`,`Ds_postE` ... (for 2022)
    * `outNameLabel` = label you want to add to the analyzed root files 

A directory ( called `[MC/DataEra]_[AnalysisType]_[outNameLabel]` ) and the file for the submission are created. The job submission on the batch system can be launched by sourcing the .sh script that was created:\
`source submit_analysis_[MC/DataEra]_[AnalysisType]_[outNameLabel].sh` 

Here are some examples for the creation of jobs:
* to run the tau3mu analysis on the DsTau3mu MC sample:\
`python createRunFile_new.py Ds MC tau3mu --n 150 --MCprocess --outName test`
* to run the tau3mu analysis on the data: era C, stream 0:\
`python createRunFile_new.py data tau3mu --n 150 --run 2022C_0 --outName test`
* to run the control channel analysis on the DsPhiPi MC sample:\
`python createRunFile_new.py --n 150 --MCprocess DsPhiPi MC tau3mu --outName test` # N.B: use the flag `tau3mu` here! the submission needs to be fixed to have a consistent definition...
* to run the control channel analysis the data: of era E, stream 1:\
`python createRunFile_new.py data_control control --n 150 --run 2022E_1  --outName test`

<p>&nbsp;</p>

### Run analysis on ALL the datasets (using the batch system)
The script `submitAllJobs_new.sh` allows for the automatic creation and submission of jobs for the analysis for ALL the datasets.\
`source submitAllJobs_new.sh [NTreesPerJob] [analysisType] [outNameLabel]`

Here are some examples for submitting the jobs for:
* tau3mu analysis on all the 2022 datasets:\
`source submitAllJobs_new.sh 150 tau3mu test`

* control analysis on all the 2022 datasets:\
`source submitAllJobs_new.sh 150 control test`

<p>&nbsp;</p>

### Merging the analyzed files for all the datasets
The script `haddAllJobs_new.sh` allows for the automatic merging of the output files from the analysis for all the datasets.\
`source haddAllJobs_new.sh [analysisType] [outNameLabel]`

Here are some examples for merging the analyzed files for:
* tau3mu analysis on all the 2022 datasets:\
`source haddAllJobs_new.sh tau3mu test`
* control channel analysis on all the 2022 datasets:\
`source haddAllJobs_new.sh control test`

