from CRABClient.UserUtilities import config, getUsername
config = config()

config.General.requestName = 'SkimTau3mu_MC_23_Run3_Ds_new_Mini_preBPix'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'


config.JobType.psetName = '/lustrehome/mbuonsante/Tau_3mu/Ntuple/CMSSW_13_0_13/src/SkimTools/SkimTau3Mu/test/run_MC2023_PatAndTree_cfg.py'
config.Data.inputDataset = '/DstoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v1/MINIAODSIM'
config.Data.allowNonValidInputDataset = True
config.Data.inputDBS = 'global'
#config.Data.splitting = 'LumiBased'
config.Data.splitting = 'Automatic'
config.Data.unitsPerJob = 2500
config.Data.outLFNDirBase = '/store/user/mbuonsan/'
#config.Data.publication = True
config.Data.outputDatasetTag = 'SkimTau3mu_MC_23_Run3_Ds_new_Mini_preBPix'
config.JobType.allowUndistributedCMSSW = True 
config.Site.storageSite = 'T2_IT_Bari'
config.Site.ignoreGlobalBlacklist  = True

