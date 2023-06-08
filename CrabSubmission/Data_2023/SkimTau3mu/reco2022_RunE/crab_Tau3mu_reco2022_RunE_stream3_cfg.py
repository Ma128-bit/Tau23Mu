from CRABClient.UserUtilities import config, getUsername
config = config()

config.General.requestName = 'SkimTau3mu_2022eraE_stream3_Mini_v3'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'

config.JobType.psetName = '/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/SkimTools/SkimTau3Mu/test/run_Data2022E_PatAndTree_cfg.py'

config.Data.inputDataset = '/ParkingDoubleMuonLowMass3/Run2022E-10Dec2022-v2/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
#config.Data.splitting = 'Automatic'
config.Data.unitsPerJob = 50
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions22/Cert_Collisions2022_eraE_359022_360331_Golden.json'
#config.Data.runRange = '193093-193999' # '193093-194075'
#config.Data.publication = True
config.Data.outputDatasetTag = 'SkimTau3mu_2022eraE_stream3_Mini_v3'
config.JobType.allowUndistributedCMSSW = True 
config.Site.storageSite = 'T2_IT_Bari'
config.Site.ignoreGlobalBlacklist  = True

