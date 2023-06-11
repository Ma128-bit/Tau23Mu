from CRABClient.UserUtilities import config, getUsername
config = config()

config.General.requestName = 'SkimDsPhiPi_2023eraC-v3_stream1_Mini_v3'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'

config.JobType.psetName	= '/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/SkimTools/SkimPhiPi/test/run_Data2023C-v1-3_DsPhiPiSkimAndTree_cfg.py'

config.Data.inputDataset = '/ParkingDoubleMuonLowMass1/Run2023C-PromptReco-v3/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
#config.Data.splitting = 'Automatic'
config.Data.unitsPerJob = 50
config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions23/Cert_Collisions2023_eraC_367095_368224_Golden.json'
#config.Data.runRange = '193093-193999' # '193093-194075'
#config.Data.publication = True
config.Data.outputDatasetTag = 'SkimDsPhiPi_2023eraC-v3_stream1_Mini_v3'
config.JobType.allowUndistributedCMSSW = True 
config.Site.storageSite = 'T2_IT_Bari'
config.Site.ignoreGlobalBlacklist  = True
