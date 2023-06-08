from CRABClient.UserUtilities import config, getUsername
config = config()

config.General.requestName = 'SkimTau3mu_MCRun3_Bd_Mini_preE'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'


config.JobType.psetName = '/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/SkimTools/SkimTau3Mu/test/run_MC2022_PatAndTree_cfg.py'
config.Data.inputDataset = '/BdtoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v2/MINIAODSIM'
config.Data.inputDBS = 'global'
#config.Data.splitting = 'LumiBased'
config.Data.splitting = 'Automatic'
config.Data.unitsPerJob = 2500
config.Data.outLFNDirBase = '/store/user/mbuonsan/' 
#config.Data.publication = True
config.Data.outputDatasetTag = 'SkimTau3mu_MCRun3_Bd_Mini_preE'
config.JobType.allowUndistributedCMSSW = True 
config.Site.storageSite = 'T2_IT_Bari'
config.Site.ignoreGlobalBlacklist  = True

