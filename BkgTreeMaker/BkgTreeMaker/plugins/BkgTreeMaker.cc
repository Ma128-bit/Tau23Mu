// -*- C++ -*-
// Package:    BkgTreeMaker/BkgTreeMaker
// Class:      BkgTreeMaker
//
// class BkgTreeMaker BkgTreeMaker.cc BkgTreeMaker/BkgTreeMaker/plugins/BkgTreeMaker.cc
 
#include <memory>
#include <algorithm>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include <DataFormats/MuonReco/interface/MuonFwd.h>
#include <DataFormats/MuonReco/interface/Muon.h>
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
//#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TFile.h"
#include "TH1.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TH2.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoBTag/SecondaryVertex/interface/SecondaryVertex.h"
#include "RecoVertex/AdaptiveVertexFit/interface/AdaptiveVertexFitter.h"


#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h"
#include "RecoVertex/KinematicFit/interface/MassKinematicConstraint.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFitPrimitives/interface/MultiTrackKinematicConstraint.h"
#include "RecoVertex/KinematicFit/interface/KinematicConstrainedVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/TwoTrackMassKinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/TransientTrackKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicTree.h"


#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackFromFTSFactory.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"

#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"

#include "RecoVertex/VertexPrimitives/interface/ConvertToFromReco.h"
#include "DataFormats/TrackReco/interface/TrackBase.h"
#include "RecoVertex/VertexTools/interface/VertexDistance3D.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"

#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/PatCandidates/interface/TriggerFilter.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "TrackingTools/IPTools/interface/IPTools.h"


#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/L1TGlobal/interface/GlobalAlgBlk.h"
#include "L1Trigger/L1TGlobal/interface/L1TGlobalUtil.h"
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "CondFormats/DataRecord/interface/L1TUtmTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1TUtmTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1TGlobalPrescalesVetosRcd.h"
#include "CondFormats/L1TObjects/interface/L1TGlobalPrescalesVetos.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/TrackReco/interface/TrackToTrackMap.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
////


typedef pair<const reco::MuonChamberMatch*, const reco::MuonSegmentMatch*> MatchPair;

class BkgTreeMaker : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
    explicit BkgTreeMaker(const edm::ParameterSet&);
    ~BkgTreeMaker();
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    void fillMatchInfo(const pat::Muon&); 

private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    edm::EDGetTokenT<edm::View<pat::Muon> > muons_;
    edm::EDGetTokenT<edm::View<reco::Vertex> > vertex_;
    edm::EDGetTokenT<edm::View<reco::Track> > trackToken_;
    edm::EDGetTokenT<std::vector<pat::PackedCandidate> >srcCands_;
    edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticles_;
    edm::EDGetTokenT<std::vector<PileupSummaryInfo> > puToken_ ;
    edm::EDGetTokenT<reco::BeamSpot> token_BeamSpot;
    edm::EDGetToken algToken_;
    edm::EDGetToken algTok_;
    edm::ESGetToken<TransientTrackBuilder, TransientTrackRecord> theTransientTrackBuilder_;
    HLTConfigProvider hltConfig;
    edm::Service<TFileService> fs;
    l1t::L1TGlobalUtil* gtUtil_;
    edm::InputTag algInputTag_;
    const edm::InputTag algTag_, extTag_;

    //tree
    TTree*      tree_;
    std::vector<float>  MuonPt, MuonEta, MuonPhi;
    std::vector<double> MuonEnergy,  MuonCharge;
    std::vector<int> GenParticle_PdgId, GenParticle_MotherPdgId, GenParticle_GrandMotherPdgId;
    std::vector<double> GenParticle_Pt, GenParticle_Eta,    GenParticle_Phi, GenParticle_vx, GenParticle_vy, GenParticle_vz;
    std::vector<double>  Muon_vx,  Muon_vy,  Muon_vz;
    std::vector<double>  Muon_isGlobal,  Muon_isTracker,  Muon_isSoft, Muon_isMVA, Muon_isMVASoft,  Muon_isLoose, Muon_isMedium, Muon_isTight,  Muon_isPF,  Muon_isRPCMuon,  Muon_isStandAloneMuon,  Muon_isTrackerMuon,  Muon_isCaloMuon,  Muon_isQualityValid,  Muon_isTimeValid,  Muon_isIsolationValid,  Muon_numberOfMatchedStations,  Muon_numberOfMatches;
    std::vector<double>  Muon_timeAtIpInOut,Muon_timeAtIpInOutErr;
    std::vector<double>  Muon_GLnormChi2, Muon_GLhitPattern_numberOfValidMuonHits,  Muon_trackerLayersWithMeasurement,  Muon_Numberofvalidpixelhits,  Muon_outerTrack_p,  Muon_outerTrack_eta, Muon_outerTrack_phi,  Muon_outerTrack_normalizedChi2,  Muon_outerTrack_muonStationsWithValidHits,  Muon_innerTrack_p,  Muon_innerTrack_eta,  Muon_innerTrack_phi,  Muon_innerTrack_normalizedChi2,  Muon_QInnerOuter;
    std::vector<double>   Muon_combinedQuality_updatedSta,  Muon_combinedQuality_trkKink,  Muon_combinedQuality_glbKink,  Muon_combinedQuality_trkRelChi2,  Muon_combinedQuality_staRelChi2,  Muon_combinedQuality_chi2LocalPosition,  Muon_combinedQuality_chi2LocalMomentum,  Muon_combinedQuality_localDistance,  Muon_combinedQuality_globalDeltaEtaPhi,  Muon_combinedQuality_tightMatch,  Muon_combinedQuality_glbTrackProbability,  Muon_calEnergy_em,  Muon_calEnergy_emS9,  Muon_calEnergy_emS25,  Muon_calEnergy_had,  Muon_calEnergy_hadS9,  Muon_segmentCompatibility,  Muon_caloCompatibility,  Muon_ptErrOverPt, Muon_BestTrackPt,  Muon_BestTrackPtErr, Muon_BestTrackEta,  Muon_BestTrackEtaErr,  Muon_BestTrackPhi,  Muon_BestTrackPhiErr;
    std::vector<double> Muon_combinedQuality_match1_dX, Muon_combinedQuality_match1_pullX, Muon_combinedQuality_match1_pullDxDz, Muon_combinedQuality_match1_dY, Muon_combinedQuality_match1_pullY, Muon_combinedQuality_match1_pullDyDz, Muon_combinedQuality_match2_dX, Muon_combinedQuality_match2_pullX, Muon_combinedQuality_match2_pullDxDz, Muon_combinedQuality_match2_dY, Muon_combinedQuality_match2_pullY, Muon_combinedQuality_match2_pullDyDz;
    std::vector<int>  Muon_simPdgId, Muon_simMotherPdgId, Muon_simFlavour,  Muon_simType, Muon_simBX, Muon_simTpEvent, Muon_simMatchQuality;
    std::vector<double> Muon_emEt03, Muon_hadEt03, Muon_nJets03, Muon_nTracks03, Muon_sumPt03, Muon_emEt05,    Muon_hadEt05, Muon_nJets05, Muon_nTracks05, Muon_sumPt05, Muon_hadVetoEt03, Muon_emVetoEt03, Muon_trackerVetoPt03,    Muon_hadVetoEt05,    Muon_emVetoEt05,    Muon_trackerVetoPt05;
    int TripletCollectionSize, PVCollection_Size, MuonCollectionSize;
    std::vector<double>  Muon_innerTrack_highPurity,  Muon_innerTrack_ValidFraction, Muon_Numberofvalidtrackerhits, Muon_validMuonHitComb, Muon_IP2D_BS,  Muon_IP3D_BS,  Muon_IP2D_PV,  Muon_IP3D_PV, Muon_SoftMVA_Val;
    std::vector<double> PV_x,  PV_y,  PV_z,  PV_NTracks;
    std::vector<double> BS_x,  BS_y,  BS_z;
    uint  evt, run, lumi, puN;
};

BkgTreeMaker::BkgTreeMaker(const edm::ParameterSet& iConfig){
    edm::InputTag algInputTag_;
    muons_ = consumes<edm::View<pat::Muon> >  (iConfig.getParameter<edm::InputTag>("muonLabel"));
    vertex_ = consumes<edm::View<reco::Vertex> > (iConfig.getParameter<edm::InputTag>("VertexLabel"));
    trackToken_ = consumes<edm::View<reco::Track> > (edm::InputTag("generalTracks"));
    srcCands_ = consumes<std::vector<pat::PackedCandidate> >(edm::InputTag("packedPFCandidates"));
    genParticles_ = consumes<edm::View<reco::GenParticle>  > (iConfig.getParameter<edm::InputTag>("genParticleLabel"));
    puToken_ =   consumes<std::vector<PileupSummaryInfo> >(iConfig.getParameter<edm::InputTag>("pileupSummary"));
    algToken_ = consumes<BXVector<GlobalAlgBlk>>(iConfig.getParameter<edm::InputTag>("AlgInputTag"));
    algTok_ = consumes<BXVector<GlobalAlgBlk>>(iConfig.getParameter<edm::InputTag>("algInputTag"));
    gtUtil_ = new l1t::L1TGlobalUtil(iConfig, consumesCollector(), *this, algTag_, extTag_, l1t::UseEventSetupIn::Event);
}

BkgTreeMaker::~BkgTreeMaker(){
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
}

const MatchPair& getBetterMatch(const MatchPair& match1, const MatchPair& match2){
  if (match2.first->detector() == MuonSubdetId::DT and
      match1.first->detector() != MuonSubdetId::DT)
    return match2;

  if ( abs(match1.first->x - match1.second->x) >
       abs(match2.first->x - match2.second->x) )
    return match2;
    
  return match1;
}

float dX(const MatchPair& match){
  if (match.first and match.second->hasPhi())
    return (match.first->x - match.second->x);
  else
    return -99;
}

float pullX(const MatchPair& match){
  if (match.first and match.second->hasPhi())
    return dX(match) /
      sqrt(pow(match.first->xErr, 2) + pow(match.second->xErr, 2));
  else
    return -99;
}

float pullDxDz(const MatchPair& match){
  if (match.first and match.second->hasPhi())
    return (match.first->dXdZ - match.second->dXdZ) /
           sqrt(pow(match.first->dXdZErr, 2) + pow(match.second->dXdZErr, 2));
  else
    return -99;
}
float dY(const MatchPair& match){
  if (match.first and match.second->hasZed())
    return (match.first->y - match.second->y);
  else
    return -99;
}

float pullY(const MatchPair& match){
  if (match.first and match.second->hasZed())
    return dY(match) /
      sqrt(pow(match.first->yErr, 2) + pow(match.second->yErr, 2));
  else
    return -99;
}

float pullDyDz(const MatchPair& match){
  if (match.first and match.second->hasZed())
    return (match.first->dYdZ - match.second->dYdZ) /
           sqrt(pow(match.first->dYdZErr, 2) + pow(match.second->dYdZErr, 2));
  else
    return -99;
}

void MiniAnaTau3Mu::fillMatchInfo(const pat::Muon& muon){
	// Initiate containter for results
        const int n_stations = 2;
        std::vector<MatchPair> matches;
        for (unsigned int i=0; i < n_stations; ++i)
            matches.push_back(std::pair(nullptr, nullptr));
        
        for (auto& chamberMatch : muon.matches()){
            unsigned int station = chamberMatch.station() - 1;
            if (station >= n_stations) continue;
        
            for (auto& segmentMatch : chamberMatch.segmentMatches){
              if ( not segmentMatch.isMask(reco::MuonSegmentMatch::BestInStationByDR) ||
               not segmentMatch.isMask(reco::MuonSegmentMatch::BelongsToTrackByDR) )
            continue;
        
        
            auto match_pair = MatchPair(&chamberMatch, &segmentMatch);
              
            if (matches[station].first)
                matches[station] = getBetterMatch(matches[station], match_pair);
            else
                matches[station] = match_pair;
            }
        }    
        Muon_combinedQuality_match1_dX.push_back(dX(matches[0]));
        Muon_combinedQuality_match1_pullX.push_back(pullX(matches[0]));
        Muon_combinedQuality_match1_pullDxDz.push_back(pullDxDz(matches[0]));
        Muon_combinedQuality_match1_dY.push_back(dY(matches[0]));
        Muon_combinedQuality_match1_pullY.push_back(pullY(matches[0]));
        Muon_combinedQuality_match1_pullDyDz.push_back(pullDyDz(matches[0]));
        
        Muon_combinedQuality_match2_dX.push_back(dX(matches[1]));
        Muon_combinedQuality_match2_pullX.push_back(pullX(matches[1]));
        Muon_combinedQuality_match2_pullDxDz.push_back(pullDxDz(matches[1]));
        Muon_combinedQuality_match2_dY.push_back(dY(matches[1]));
        Muon_combinedQuality_match2_pullY.push_back(pullY(matches[1]));
        Muon_combinedQuality_match2_pullDyDz.push_back(pullDyDz(matches[1]));
}







void BkgTreeMaker::beginJob() {
    tree_ = fs->make<TTree>("ntuple","LFVTau ntuple");
    tree_->Branch("evt", &evt);
    tree_->Branch("run", &run);
    tree_->Branch("lumi", &lumi);
  
    tree_->Branch("GenParticle_PdgId", &GenParticle_PdgId);
    tree_->Branch("GenParticle_Pt", &GenParticle_Pt);
    tree_->Branch("GenParticle_Eta", &GenParticle_Eta);
    tree_->Branch("GenParticle_Phi", &GenParticle_Phi);
    tree_->Branch("GenParticle_MotherPdgId", &GenParticle_MotherPdgId);
    tree_->Branch("GenParticle_vx", &GenParticle_vx);
    tree_->Branch("GenParticle_vy", &GenParticle_vy);
    tree_->Branch("GenParticle_vz", &GenParticle_vz);

    tree_->Branch("MuonCollectionSize",&MuonCollectionSize);
    tree_->Branch("MuonPt",&MuonPt);
    tree_->Branch("MuonEnergy", &MuonEnergy);
    tree_->Branch("MuonCharge", &MuonCharge);
    tree_->Branch("MuonEta",&MuonEta);
    tree_->Branch("MuonPhi",&MuonPhi);
    tree_->Branch("Muon_simPdgId", &Muon_simPdgId);
    tree_->Branch("Muon_simMotherPdgId", &Muon_simMotherPdgId);
    tree_->Branch("Muon_simFlavour", &Muon_simFlavour);
    tree_->Branch("Muon_simType", &Muon_simType);
    tree_->Branch("Muon_simBX", &Muon_simBX);

    /////Vtx position
    tree_->Branch("Muon_vx", &Muon_vx);
    tree_->Branch("Muon_vy", &Muon_vy);
    tree_->Branch("Muon_vz", &Muon_vz);
    
    /////MuonID
    tree_->Branch("Muon_isGlobal", &Muon_isGlobal);
    tree_->Branch("Muon_isSoft", &Muon_isSoft);
    tree_->Branch("Muon_isMVA", &Muon_isMVA);
    tree_->Branch("Muon_isMVASoft", &Muon_isMVASoft);
    tree_->Branch("Muon_isLoose", &Muon_isLoose);
    tree_->Branch("Muon_isMedium", &Muon_isMedium);
    tree_->Branch("Muon_isTight", &Muon_isTight);
    tree_->Branch("Muon_isPF", &Muon_isPF);
    tree_->Branch("Muon_isRPCMuon", &Muon_isRPCMuon);
    tree_->Branch("Muon_isStandAloneMuon", &Muon_isStandAloneMuon);
    tree_->Branch("Muon_isTrackerMuon", &Muon_isTrackerMuon);
    tree_->Branch("Muon_isCaloMuon", &Muon_isCaloMuon);
    tree_->Branch("Muon_isQualityValid", &Muon_isQualityValid);
    tree_->Branch("Muon_isTimeValid", &Muon_isTimeValid);
    tree_->Branch("Muon_isIsolationValid", &Muon_isIsolationValid);
    tree_->Branch("Muon_numberOfMatchedStations", &Muon_numberOfMatchedStations);
    tree_->Branch("Muon_numberOfMatches", &Muon_numberOfMatches);
    tree_->Branch("Muon_SoftMVA_Val", &Muon_SoftMVA_Val);
    
    tree_->Branch("Muon_timeAtIpInOut",&Muon_timeAtIpInOut);
    tree_->Branch("Muon_timeAtIpInOutErr",&Muon_timeAtIpInOutErr);
    //////Muon inner + outer track
    tree_->Branch("Muon_GLnormChi2", &Muon_GLnormChi2);
    tree_->Branch("Muon_GLhitPattern_numberOfValidMuonHits", &Muon_GLhitPattern_numberOfValidMuonHits);
    
    tree_->Branch("Muon_trackerLayersWithMeasurement", &Muon_trackerLayersWithMeasurement);
    tree_->Branch("Muon_Numberofvalidpixelhits", &Muon_Numberofvalidpixelhits);
    
    tree_->Branch("Muon_outerTrack_p", &Muon_outerTrack_p);
    tree_->Branch("Muon_outerTrack_eta", &Muon_outerTrack_eta);
    tree_->Branch("Muon_outerTrack_phi", &Muon_outerTrack_phi);
    tree_->Branch("Muon_outerTrack_normalizedChi2", &Muon_outerTrack_normalizedChi2);
    tree_->Branch("Muon_outerTrack_muonStationsWithValidHits", &Muon_outerTrack_muonStationsWithValidHits);
    tree_->Branch("Muon_innerTrack_p", &Muon_innerTrack_p);
    tree_->Branch("Muon_innerTrack_eta", &Muon_innerTrack_eta);
    
    tree_->Branch("Muon_innerTrack_phi", &Muon_innerTrack_phi);
    tree_->Branch("Muon_innerTrack_normalizedChi2", &Muon_innerTrack_normalizedChi2);
    tree_->Branch("Muon_QInnerOuter", &Muon_QInnerOuter);
    
    tree_->Branch("Muon_combinedQuality_updatedSta", &Muon_combinedQuality_updatedSta);
    tree_->Branch("Muon_combinedQuality_trkKink", &Muon_combinedQuality_trkKink);
    tree_->Branch("Muon_combinedQuality_glbKink", &Muon_combinedQuality_glbKink);
    tree_->Branch("Muon_combinedQuality_trkRelChi2", &Muon_combinedQuality_trkRelChi2);
    tree_->Branch("Muon_combinedQuality_staRelChi2", &Muon_combinedQuality_staRelChi2);
    tree_->Branch("Muon_combinedQuality_chi2LocalPosition", &Muon_combinedQuality_chi2LocalPosition);
    tree_->Branch("Muon_combinedQuality_chi2LocalMomentum", &Muon_combinedQuality_chi2LocalMomentum);
    tree_->Branch("Muon_combinedQuality_localDistance", &Muon_combinedQuality_localDistance);
    tree_->Branch("Muon_combinedQuality_globalDeltaEtaPhi", &Muon_combinedQuality_globalDeltaEtaPhi);
    tree_->Branch("Muon_combinedQuality_tightMatch", &Muon_combinedQuality_tightMatch);
    tree_->Branch("Muon_combinedQuality_glbTrackProbability", &Muon_combinedQuality_glbTrackProbability);

    tree_->Branch("Muon_combinedQuality_match1_dX", &Muon_combinedQuality_match1_dX);
    tree_->Branch("Muon_combinedQuality_match1_pullX", &Muon_combinedQuality_match1_pullX);
    tree_->Branch("Muon_combinedQuality_match1_pullDxDz", &Muon_combinedQuality_match1_pullDxDz);
    tree_->Branch("Muon_combinedQuality_match1_dY", &Muon_combinedQuality_match1_dY);
    tree_->Branch("Muon_combinedQuality_match1_pullY", &Muon_combinedQuality_match1_pullY);
    tree_->Branch("Muon_combinedQuality_match1_pullDyDz", &Muon_combinedQuality_match1_pullDyDz);

    tree_->Branch("Muon_combinedQuality_match2_dX", &Muon_combinedQuality_match2_dX);
    tree_->Branch("Muon_combinedQuality_match2_pullX", &Muon_combinedQuality_match2_pullX);
    tree_->Branch("Muon_combinedQuality_match2_pullDxDz", &Muon_combinedQuality_match2_pullDxDz);
    tree_->Branch("Muon_combinedQuality_match2_dY", &Muon_combinedQuality_match2_dY);
    tree_->Branch("Muon_combinedQuality_match2_pullY", &Muon_combinedQuality_match2_pullY);
    tree_->Branch("Muon_combinedQuality_match2_pullDyDz", &Muon_combinedQuality_match2_pullDyDz);

    tree_->Branch("Muon_calEnergy_em", &Muon_calEnergy_em);
    tree_->Branch("Muon_calEnergy_emS9", &Muon_calEnergy_emS9);
    tree_->Branch("Muon_calEnergy_emS25", &Muon_calEnergy_emS25);
    tree_->Branch("Muon_calEnergy_had", &Muon_calEnergy_had);
    tree_->Branch("Muon_calEnergy_hadS9", &Muon_calEnergy_hadS9);
    
    tree_->Branch("Muon_segmentCompatibility", &Muon_segmentCompatibility);
    tree_->Branch("Muon_caloCompatibility", &Muon_caloCompatibility);
    
    tree_->Branch("Muon_ptErrOverPt", &Muon_ptErrOverPt);
    tree_->Branch("Muon_BestTrackPt", &Muon_BestTrackPt);
    tree_->Branch("Muon_BestTrackPtErr", &Muon_BestTrackPtErr);
    tree_->Branch("Muon_BestTrackEta", &Muon_BestTrackEta);
    tree_->Branch("Muon_BestTrackEtaErr", &Muon_BestTrackEtaErr);
    tree_->Branch("Muon_BestTrackPhi", &Muon_BestTrackPhi);
    tree_->Branch("Muon_BestTrackPhiErr", &Muon_BestTrackPhiErr);

    tree_->Branch("Muon_emEt03", &Muon_emEt03);
    tree_->Branch("Muon_hadEt03", &Muon_hadEt03);
    tree_->Branch("Muon_nJets03", &Muon_nJets03);
    tree_->Branch("Muon_nTracks03", &Muon_nTracks03);
    tree_->Branch("Muon_sumPt03", &Muon_sumPt03);
    tree_->Branch("Muon_hadVetoEt03", &Muon_hadVetoEt03);
    tree_->Branch("Muon_emVetoEt03", &Muon_emVetoEt03);
    tree_->Branch("Muon_trackerVetoPt03", &Muon_trackerVetoPt03);

    tree_->Branch("Muon_emEt05", &Muon_emEt05);
    tree_->Branch("Muon_hadEt05", &Muon_hadEt05);
    tree_->Branch("Muon_nJets05", &Muon_nJets05);
    tree_->Branch("Muon_nTracks05", &Muon_nTracks05);
    tree_->Branch("Muon_sumPt05", &Muon_sumPt05);
    tree_->Branch("Muon_hadVetoEt05", &Muon_hadVetoEt05);
    tree_->Branch("Muon_emVetoEt05", &Muon_emVetoEt05);
    tree_->Branch("Muon_trackerVetoPt05", &Muon_trackerVetoPt05);

    tree_->Branch("Muon_innerTrack_highPurity", &Muon_innerTrack_highPurity);
    tree_->Branch("Muon_innerTrack_ValidFraction", &Muon_innerTrack_ValidFraction);
    tree_->Branch("Muon_Numberofvalidtrackerhits", &Muon_Numberofvalidtrackerhits);
    tree_->Branch("Muon_validMuonHitComb", &Muon_validMuonHitComb);
    tree_->Branch("Muon_IP2D_BS", &Muon_IP2D_BS);
    tree_->Branch("Muon_IP3D_BS", &Muon_IP3D_BS);
    tree_->Branch("Muon_IP2D_PV", &Muon_IP2D_PV);
    tree_->Branch("Muon_IP3D_PV", &Muon_IP3D_PV);

    tree_->Branch("PVCollection_Size", &PVCollection_Size);
    tree_->Branch("PV_x", &PV_x);
    tree_->Branch("PV_y", &PV_y);
    tree_->Branch("PV_z", &PV_z);
    tree_->Branch("PV_NTracks", &PV_NTracks);
    
    tree_->Branch("BS_x", &BS_x);
    tree_->Branch("BS_y", &BS_y);
    tree_->Branch("BS_z", &BS_z);
    
}//BkgTreeMaker::beginJob
    

void BkgTreeMaker::endJob() {
    tree_->GetDirectory()->cd();
    tree_->Write();
}
void BkgTreeMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    desc.setUnknown();
    descriptions.addDefault(desc);
}
DEFINE_FWK_MODULE(BkgTreeMaker);
