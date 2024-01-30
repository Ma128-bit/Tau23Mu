import FWCore.ParameterSet.Config as cms

process = cms.Process('Tau3MuSkim')

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load("SkimTools.SkimTau3Mu.Tau3MuSkim_miniAOD_noHLT_cff")

process.GlobalTag.globaltag = '106X_upgrade2018_realistic_v16_L1v1' #MC2018 

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      '/store/user/caruta/Pythia8_DsTau3mu_Run3_2022/124X_mcRun3_2022_realistic_v12_MINIAODSIM/221120_083655/0000/DsTau3mu_2022_step2_1.root'
    ),
)


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("TreeMC.root"))

process.unpackedPatTrigger = cms.EDProducer("PATTriggerObjectStandAloneUnpacker",
    patTriggerObjectsStandAlone = cms.InputTag( 'slimmedPatTrigger' ),
    triggerResults              = cms.InputTag( 'TriggerResults::HLT' ),
    unpackFilterLabels = cms.bool(True)
)

process.TreeMakerBkg = cms.EDAnalyzer("MiniAnaTau3Mu",
                                      isMcLabel = cms.untracked.bool(True),
                                      isAnaLabel = cms.untracked.bool(True),
                                      is2016Label = cms.untracked.bool(True),
                                      is2017Label = cms.untracked.bool(True),
                                      is2018Label = cms.untracked.bool(True),
                                      isBParkingLabel = cms.untracked.bool(False),
                                      muonLabel=cms.InputTag("looseMuons"),
                                      photonLabel=cms.InputTag("slimmedPhotons"),
                                      VertexLabel=cms.InputTag("offlineSlimmedPrimaryVertices"),
                                      genParticleLabel=cms.InputTag("prunedGenParticles"),
                                      pileupSummary = cms.InputTag("slimmedAddPileupInfo"),
                                      Cand3MuLabel=cms.InputTag("ThreeMuonsVtxKalmanFit"),
                                      triggerResults = cms.InputTag("TriggerResults", "", "HLT"),
                                      objects = cms.InputTag("unpackedPatTrigger"),
                                      AlgInputTag = cms.InputTag( "gtStage2Digis" ),
                                      algInputTag = cms.InputTag( "gtStage2Digis" ),
                                      extInputTag = cms.InputTag( "gtStage2Digis" )
                                      
)


process.Tau3MuSkim = cms.Path(process.ThreeMuonSelSeq*
                              process.unpackedPatTrigger*
                              process.TreeMakerBkg
                     )




