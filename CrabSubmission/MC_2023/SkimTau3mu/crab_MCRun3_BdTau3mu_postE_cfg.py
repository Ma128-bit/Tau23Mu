from CRABClient.UserUtilities import config, getUsername
config = config()

config.General.requestName = 'SkimTau3mu_MC_23_Run3_Bd_Mini_postE'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'


config.JobType.psetName = '/lustrehome/mbuonsante/Tau_3mu/Ntuple/CMSSW_13_0_13/src/SkimTools/SkimTau3Mu/test/run_MC2023_PatAndTree_postE_cfg.py'
config.Data.inputDataset = '/BdtoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM'
config.Data.inputDBS = 'global'
#config.Data.splitting = 'LumiBased'
config.Data.splitting = 'Automatic'
config.Data.unitsPerJob = 2500
config.Data.outLFNDirBase = '/store/user/mbuonsan/'
#config.Data.publication = True
config.Data.outputDatasetTag = 'SkimTau3mu_MC_23_Run3_Bd_Mini_postE'
config.JobType.allowUndistributedCMSSW = True 
config.Site.storageSite = 'T2_IT_Bari'
config.Site.ignoreGlobalBlacklist  = True

