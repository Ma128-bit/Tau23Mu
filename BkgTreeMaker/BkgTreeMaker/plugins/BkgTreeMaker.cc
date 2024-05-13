// -*- C++ -*-
// Package:    BkgTreeMaker/BkgTreeMaker
// Class:      BkgTreeMaker
//
/* class BkgTreeMaker BkgTreeMaker.cc BkgTreeMaker/BkgTreeMaker/plugins/BkgTreeMaker.cc
 
 Description: [one line class summary]
 
 Implementation:
 [Notes on implementation]
*/
//
// Original Author:  venditti
//         Created:  Tue, 18 Dec 2018 09:30:06 GMT
//
//

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
    
    //tree branches
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
    int PVCollection_Size, MuonCollectionSize;
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

void BkgTreeMaker::fillMatchInfo(const pat::Muon& muon){
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


void BkgTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
    using namespace edm;
    using namespace std;
    using namespace reco;
    using std::vector;
    
    edm::Handle< edm::View<reco::Vertex> >vertices;
    iEvent.getByToken(vertex_, vertices);
    if (vertices->empty()) return; // skip the event if no PV found
    const reco::Vertex &PV = vertices->front();
    
    edm::Handle< edm::View<pat::Muon> > muons;
    iEvent.getByToken(muons_, muons);
    
    edm::Handle< edm::View<reco::GenParticle> > genParticles;
    iEvent.getByToken(genParticles_, genParticles);
    
    edm::Handle<edm::View<reco::Track> > trackCollection;
    iEvent.getByToken(trackToken_, trackCollection);
    
    Handle<BXVector<GlobalAlgBlk>> alg;
    iEvent.getByToken(algToken_,alg);
    
    edm::ESHandle<TransientTrackBuilder> theTransientTrackBuilder = iSetup.getHandle(theTransientTrackBuilder_);
    
    edm::Handle<std::vector<pat::PackedCandidate> > PFCands;
    iEvent.getByToken(srcCands_,PFCands);
    
    reco::BeamSpot beamSpot;
    edm::Handle<reco::BeamSpot> beamSpotHandle;
    iEvent.getByToken(token_BeamSpot, beamSpotHandle);
    const reco::BeamSpot& beamspot = *beamSpotHandle.product();
    double x_bs = 0.0;
    double y_bs = 0.0;
    double z_bs = 0.0;
    if ( beamSpotHandle.isValid() ) {
        beamSpot = *beamSpotHandle;
        x_bs = beamSpot.x0();
        y_bs = beamSpot.y0();
        z_bs = beamSpot.z0();
    } else {
        cout << "No beam spot available from EventSetup \n" << endl;
    }
    
    //Primary Vtx
    PVCollection_Size = vertices->size();
    
    //             ************** Fill Genparticles **************
    if(isMc){
        uint j=0;
        uint ngenP=genParticles->size();
        std::vector<int> genPidx;
        
        for(edm::View<reco::GenParticle>::const_iterator gp=genParticles->begin(); gp!=genParticles->end(), j<ngenP; ++gp , ++j){
            
            if( fabs(gp->pdgId())==13 || fabs(gp->pdgId())==211 || fabs(gp->pdgId())==321) {
                GenParticle_PdgId.push_back(gp->pdgId());
                GenParticle_Pt.push_back(gp->pt());
                GenParticle_Eta.push_back(gp->eta());
                GenParticle_Phi.push_back(gp->phi());
                GenParticle_vx.push_back(gp->vx());
                GenParticle_vy.push_back(gp->vy());
                GenParticle_vz.push_back(gp->vz());
                if (gp->numberOfMothers()) {
                    GenParticle_MotherPdgId.push_back(gp->mother(0)->pdgId());
                    if(gp->mother(0)->mother(0)) { GenParticle_GrandMotherPdgId.push_back(gp->mother(0)->mother(0)->pdgId()); }
                    else{ GenParticle_GrandMotherPdgId.push_back(-99); }
                }
                else{
                    GenParticle_MotherPdgId.push_back(-99);
                }
            } //pdgId
        }
    } //End GenParticles
    
    //             ************** ParticleFlow Candidates **************
    uint kk=0;
    std::vector<uint> VtxIdV;
    std::vector<uint> SelectedCandIdx;
    vector<pat::PackedCandidate> MyPFCands;
    cout<<"    Number of PFCands="<<PFCands->size()<<endl;
    for (std::vector<pat::PackedCandidate>::const_iterator cand = PFCands->begin(); cand != PFCands->end(), kk!= PFCands->size(); ++cand, ++kk) {
        
        if (cand->charge()==0 || cand->vertexRef().isNull() ) continue;
        
        int key = cand->vertexRef().key();
        int quality = cand->pvAssociationQuality();
        if(cand->fromPV(cand->vertexRef().key())<2) continue;
        if(cand->fromPV(cand->vertexRef().key())==2 && quality!=pat::PackedCandidate::UsedInFitLoose) continue;
        
        if ( !(cand->bestTrack()) ) continue;
        //if (quality != pat::PackedCandidate::UsedInFitTight)  continue;
        //if (quality != pat::PackedCandidate::UsedInFitLoose)  continue;
        //cout<<kk<<" vtx ref key="<<key<<" cand pt="<<cand->pt()<<" vtx x="<<cand->vertexRef()->x()<<endl;
        VtxIdV.push_back(key);
        SelectedCandIdx.push_back(kk);
        MyPFCands.push_back(*cand);
    } // End loop PFCandidates
    sort( VtxIdV.begin(), VtxIdV.end() );
    VtxIdV.erase( unique(VtxIdV.begin(), VtxIdV.end() ), VtxIdV.end() );
    
    //             ************** Loop on primavy vertices associated to good PF candidates after sorting and cleaning the list VtxIdV **************
    typedef vector<double> MyPt;
    vector<MyPt> AssoPtToVtx;
    vector<pat::PackedCandidate> SelPFCands;
    vector<vector<pat::PackedCandidate>> AssoCandToVtx;
    for(uint i=0; i<VtxIdV.size(); i++){
        vector<double> tmp_pt;
        vector<pat::PackedCandidate> tmp_cand;
        //cout<<i<<"----------Stored Vtx id="<<VtxIdV.at(i)<<"---------------"<<endl;
        for (vector<pat::PackedCandidate>::const_iterator myc = MyPFCands.begin(); myc != MyPFCands.end(); ++myc) {
            //cout<<"cand vtx="<<myc->vertexRef().key()<<" cand pt="<<myc->pt()<<endl;
            if(myc->vertexRef().key()==VtxIdV.at(i)) {
                tmp_pt.push_back(myc->pt());
                tmp_cand.push_back(*myc);
            }
        }
        AssoPtToVtx.push_back(tmp_pt);
        AssoCandToVtx.push_back(tmp_cand);
    }// End loop VtxIdV
    
    vector<vector<reco::TransientTrack>> transTracksAssoToVtx;
    for(uint i=0; i<AssoCandToVtx.size(); i++){
        std::auto_ptr<reco::TrackCollection> newTrackCollection = std::auto_ptr<reco::TrackCollection>(new TrackCollection);
        std::vector<reco::TransientTrack> transTracks;
        for(vector<pat::PackedCandidate>::const_iterator c = AssoCandToVtx.at(i).begin(); c != AssoCandToVtx.at(i).end(); ++c) {
            newTrackCollection->push_back(*(c->bestTrack()));
        }
        for (std::vector<reco::Track>::const_iterator iter = newTrackCollection->begin(); iter != newTrackCollection->end(); ++iter){
            reco::TransientTrack tt = theTransientTrackBuilder->build(*iter);
            transTracks.push_back(tt);
        }
        transTracksAssoToVtx.push_back(transTracks);
    }//End loop AssoCandToVtx
    
    //             ************** Fill RecoMu variables **************
    MuonCollectionSize = muons->size();
    uint k=0;
    for(edm::View<pat::Muon>::const_iterator mu=muons->begin(); mu!=muons->end(), k<muons->size(); ++mu, ++k){
        //Basic Kinematics
        MuonPt.push_back(mu->pt());
        MuonEta.push_back(mu->eta());
        MuonPhi.push_back(mu->phi());
        MuonEnergy.push_back(mu->energy());
        MuonCharge.push_back(mu->charge());
        
        Muon_simPdgId.push_back(mu->simPdgId());
        Muon_simMotherPdgId.push_back(mu->simMotherPdgId());
        Muon_simFlavour.push_back(mu->simFlavour());
        Muon_simType.push_back(mu->simType());
        Muon_simBX.push_back(mu->simBX());
        //Muon_simTpEvent.push_back(mu->simTpEvent());
        //Muon_simMatchQuality.push_back(mu->simMatchQuality());
        
        //Vtx position
        Muon_vx.push_back(mu->vx());
        Muon_vy.push_back(mu->vy());
        Muon_vz.push_back(mu->vz());
        Muon_IP2D_BS.push_back(pat::Muon::BS2D);
        Muon_IP3D_BS.push_back(pat::Muon::BS3D);
        Muon_IP2D_PV.push_back(pat::Muon::PV2D);
        Muon_IP3D_PV.push_back(pat::Muon::PV3D);
        
        //MuonID
        Muon_isGlobal.push_back(mu->isGlobalMuon());
        Muon_isSoft.push_back(mu->isSoftMuon(PV));
        Muon_isMVA.push_back(mu->mvaIDValue());
        Muon_isMVASoft.push_back(mu->softMvaValue());
        Muon_isLoose.push_back(mu->isLooseMuon());
        Muon_isMedium.push_back(mu->isMediumMuon());
        Muon_isTight.push_back(mu->isTightMuon(PV));
        Muon_isPF.push_back(mu->isPFMuon());
        Muon_isRPCMuon.push_back(mu->isRPCMuon());
        Muon_isStandAloneMuon.push_back(mu->isStandAloneMuon());
        Muon_isTrackerMuon.push_back(mu->isTrackerMuon());
        Muon_isCaloMuon.push_back(mu->isCaloMuon());
        Muon_isQualityValid.push_back(mu->isQualityValid());
        Muon_isTimeValid.push_back(mu->isTimeValid());
        Muon_isIsolationValid.push_back(mu->isIsolationValid());
        Muon_numberOfMatchedStations.push_back(mu->numberOfMatchedStations());
        Muon_numberOfMatches.push_back(mu->numberOfMatches(reco::Muon::SegmentArbitration));
        Muon_SoftMVA_Val.push_back(mu->softMvaValue());
        
        Muon_timeAtIpInOut.push_back(mu->time().timeAtIpInOut);
        Muon_timeAtIpInOutErr.push_back(mu->time().timeAtIpInOutErr);
        
        std::vector<int> fvDThits{0, 0, 0, 0};
        std::vector<int> fvRPChits{0, 0, 0, 0};
        std::vector<int> fvCSChits{0, 0, 0, 0};
        
        float kVMuonHitComb = 0;
        if(mu->isGlobalMuon()) {
            reco::TrackRef gTrack = mu->globalTrack();
            const reco::HitPattern& gMpattern = gTrack->hitPattern();
            for(int i=0; i<gMpattern.numberOfAllHits(reco::HitPattern::TRACK_HITS); i++) {
                uint32_t hit = gMpattern.getHitPattern(reco::HitPattern::TRACK_HITS, i);
                if(!gMpattern.validHitFilter(hit)) continue;
                
                int muStation0 = gMpattern.getMuonStation(hit) - 1;
                if(muStation0 >= 0 && muStation0 < 4) {
                    if(gMpattern.muonDTHitFilter(hit)) fvDThits[muStation0]++;
                    if(gMpattern.muonRPCHitFilter(hit)) fvRPChits[muStation0]++;
                    if(gMpattern.muonCSCHitFilter(hit)) fvCSChits[muStation0]++;
                }
            }
            
            for (unsigned int station = 0; station < 4; ++station) {
                kVMuonHitComb += (fvDThits[station]) / 2.;
                kVMuonHitComb += fvRPChits[station];
                if(fvCSChits[station] > 6) kVMuonHitComb += 6;
                else kVMuonHitComb += fvCSChits[station];
            }
            Muon_validMuonHitComb.push_back(kVMuonHitComb);
        }else{
            Muon_validMuonHitComb.push_back(-99);
        }
        
        if (mu->isGlobalMuon()) {
            Muon_GLnormChi2.push_back(mu->globalTrack()->normalizedChi2());
            Muon_GLhitPattern_numberOfValidMuonHits.push_back(mu->globalTrack()->hitPattern().numberOfValidMuonHits());
        }else{
            Muon_GLnormChi2.push_back(-999);
            Muon_GLhitPattern_numberOfValidMuonHits.push_back(-999);
        }
        
        if (mu->innerTrack().isNonnull()){
            Muon_trackerLayersWithMeasurement.push_back(mu->innerTrack()->hitPattern().trackerLayersWithMeasurement());
            bool ishighq = mu->innerTrack()->quality(reco::Track::highPurity);
            Muon_innerTrack_highPurity.push_back(ishighq);
            Muon_Numberofvalidpixelhits.push_back(mu->innerTrack()->hitPattern().numberOfValidPixelHits());
            Muon_innerTrack_ValidFraction.push_back( mu->innerTrack()->validFraction() );
            Muon_Numberofvalidtrackerhits.push_back(mu->innerTrack()->hitPattern().numberOfValidTrackerHits());
            Muon_innerTrack_p.push_back(mu->innerTrack()->p());
            Muon_innerTrack_eta.push_back(mu->innerTrack()->eta());
            Muon_innerTrack_phi.push_back(mu->innerTrack()->phi());
            Muon_innerTrack_normalizedChi2.push_back(mu->innerTrack()->normalizedChi2());
        }else{
            Muon_innerTrack_ValidFraction.push_back( -99);
            Muon_innerTrack_highPurity.push_back( -99);
            Muon_trackerLayersWithMeasurement.push_back(-999);
            Muon_Numberofvalidpixelhits.push_back(-999);
            Muon_Numberofvalidtrackerhits.push_back(-999);
            Muon_trackerLayersWithMeasurement.push_back(-999);
            Muon_innerTrack_p.push_back(-999);
            Muon_innerTrack_eta.push_back(-999);
            Muon_innerTrack_phi.push_back(-999);
            Muon_innerTrack_normalizedChi2.push_back(-999);
        }
        if (mu->outerTrack().isNonnull()){
            Muon_outerTrack_p.push_back(mu->outerTrack()->p());
            Muon_outerTrack_eta.push_back(mu->outerTrack()->eta());
            Muon_outerTrack_phi.push_back(mu->outerTrack()->phi());
            Muon_outerTrack_normalizedChi2.push_back(mu->outerTrack()->normalizedChi2());
            Muon_outerTrack_muonStationsWithValidHits.push_back(mu->outerTrack()->hitPattern().muonStationsWithValidHits());
        }else{
            Muon_outerTrack_p.push_back(-999);
            Muon_outerTrack_eta.push_back(-999);
            Muon_outerTrack_phi.push_back(-999);
            Muon_outerTrack_normalizedChi2.push_back(-999);
            Muon_outerTrack_muonStationsWithValidHits.push_back(-999);
        }
        if (mu->innerTrack().isNonnull() && mu->outerTrack().isNonnull()){
            Muon_QInnerOuter.push_back(mu->outerTrack()->charge()*mu->innerTrack()->charge());
        }else{
            Muon_QInnerOuter.push_back(-999);
        }
        
        Muon_combinedQuality_updatedSta.push_back(mu->combinedQuality().updatedSta);
        Muon_combinedQuality_trkKink.push_back(mu->combinedQuality().trkKink);
        Muon_combinedQuality_glbKink.push_back(mu->combinedQuality().glbKink);
        Muon_combinedQuality_trkRelChi2.push_back(mu->combinedQuality().trkRelChi2);
        Muon_combinedQuality_staRelChi2.push_back(mu->combinedQuality().staRelChi2);
        Muon_combinedQuality_chi2LocalPosition.push_back(mu->combinedQuality().chi2LocalPosition);
        Muon_combinedQuality_chi2LocalMomentum.push_back(mu->combinedQuality().chi2LocalMomentum);
        Muon_combinedQuality_localDistance.push_back(mu->combinedQuality().localDistance);
        Muon_combinedQuality_globalDeltaEtaPhi.push_back(mu->combinedQuality().globalDeltaEtaPhi);
        Muon_combinedQuality_tightMatch.push_back(mu->combinedQuality().tightMatch);
        Muon_combinedQuality_glbTrackProbability.push_back(mu->combinedQuality().glbTrackProbability);
        
        //muon-segment matching variables
        BkgTreeMaker::fillMatchInfo(*mu);
        
        Muon_calEnergy_em.push_back(mu->calEnergy().em);
        Muon_calEnergy_emS9.push_back(mu->calEnergy().emS9);
        Muon_calEnergy_emS25.push_back(mu->calEnergy().emS25);
        Muon_calEnergy_had.push_back(mu->calEnergy().had);
        Muon_calEnergy_hadS9.push_back(mu->calEnergy().hadS9);
        
        Muon_segmentCompatibility.push_back(muon::segmentCompatibility(*mu));
        Muon_caloCompatibility.push_back(muon::caloCompatibility(*mu));
        
        Muon_ptErrOverPt.push_back( (mu->muonBestTrack()->ptError()/mu->muonBestTrack()->pt()) );
        Muon_BestTrackPt.push_back( mu->muonBestTrack()->pt() );
        Muon_BestTrackPtErr.push_back( mu->muonBestTrack()->ptError() );
        
        Muon_BestTrackEta.push_back( mu->muonBestTrack()->eta() );
        Muon_BestTrackEtaErr.push_back( mu->muonBestTrack()->etaError() );
        
        Muon_BestTrackPhi.push_back( mu->muonBestTrack()->phi() );
        Muon_BestTrackPhiErr.push_back( mu->muonBestTrack()->phiError() );
        
        const reco::MuonIsolation Iso03 = mu->isolationR03();
        const reco::MuonIsolation Iso05 = mu->isolationR05();
        if (mu->isIsolationValid()) {
            Muon_emEt03.push_back(Iso03.emEt);
            Muon_hadEt03.push_back(Iso03.hadEt);
            Muon_nJets03.push_back(Iso03.nJets);
            Muon_nTracks03.push_back(Iso03.nTracks);
            Muon_sumPt03.push_back(Iso03.sumPt);
            Muon_emVetoEt03.push_back(Iso03.emVetoEt);
            Muon_hadVetoEt03.push_back(Iso03.hadVetoEt);
            Muon_trackerVetoPt03.push_back(Iso03.trackerVetoPt);
            
            Muon_emEt05.push_back(Iso05.emEt);
            Muon_hadEt05.push_back(Iso05.hadEt);
            Muon_nJets05.push_back(Iso05.nJets);
            Muon_nTracks05.push_back(Iso05.nTracks);
            Muon_sumPt05.push_back(Iso05.sumPt);
            Muon_hadVetoEt05.push_back(Iso05.hadVetoEt);
            Muon_trackerVetoPt05.push_back(Iso05.trackerVetoPt);
            Muon_emVetoEt05.push_back(Iso05.emVetoEt);
            
        } else { // if isolation is not valid use -1 as default
            Muon_emEt03.push_back(-1);
            Muon_hadEt03.push_back(-1);
            Muon_nJets03.push_back(-1);
            Muon_nTracks03.push_back(-1);
            Muon_sumPt03.push_back(-1);
            
            Muon_hadVetoEt03.push_back(-1);
            Muon_emVetoEt03.push_back(-1);
            Muon_trackerVetoPt03.push_back(-1);
            
            Muon_emEt05.push_back(-1);
            Muon_hadEt05.push_back(-1);
            Muon_nJets05.push_back(-1);
            Muon_nTracks05.push_back(-1);
            Muon_sumPt05.push_back(-1);
            
            Muon_emVetoEt05.push_back(-1);
            Muon_trackerVetoPt05.push_back(-1);
            Muon_hadVetoEt05.push_back(-1);
        }
    }
    
    evt  = iEvent.id().event();
    run  = iEvent.id().run();
    lumi = iEvent.luminosityBlock();
    
    tree_->Fill();
    
    //             ************** Clear **************
    run= -999;
    evt= -999;
    lumi= -999;
    
    GenParticle_PdgId.clear();
    GenParticle_Pt.clear();
    GenParticle_Eta.clear();
    GenParticle_Phi.clear();
    GenParticle_MotherPdgId.clear();
    GenParticle_vx.clear();
    GenParticle_vy.clear();
    GenParticle_vz.clear();
    
    MuonCollectionSize=0;
    MuonPt.clear();
    MuonEta.clear();
    MuonPhi.clear();
    
    Muon_simPdgId.clear();
    Muon_simMotherPdgId.clear();
    Muon_simFlavour.clear();
    Muon_simType.clear();
    Muon_simBX.clear();
    MuonEnergy.clear();
    MuonCharge.clear();
    
    /////Vtx position
    Muon_vx.clear();
    Muon_vy.clear();
    Muon_vz.clear();
    
    /////MuonID
    Muon_isGlobal.clear();
    Muon_isSoft.clear();
    Muon_isMVA.clear();
    Muon_isMVASoft.clear();
    Muon_isLoose.clear();
    Muon_isMedium.clear();
    Muon_isTight.clear();
    Muon_isPF.clear();
    Muon_isRPCMuon.clear();
    Muon_isStandAloneMuon.clear();
    Muon_isTrackerMuon.clear();
    Muon_isCaloMuon.clear();
    Muon_isQualityValid.clear();
    Muon_isTimeValid.clear();
    Muon_isIsolationValid.clear();
    Muon_numberOfMatchedStations.clear();
    Muon_numberOfMatches.clear();
    Muon_SoftMVA_Val.clear();
    /////MuonTime
    Muon_timeAtIpInOut.clear();
    Muon_timeAtIpInOutErr.clear();
    
    /////Muon inner + outer track
    Muon_GLnormChi2.clear();
    Muon_GLhitPattern_numberOfValidMuonHits.clear();
    
    Muon_trackerLayersWithMeasurement.clear();
    Muon_Numberofvalidpixelhits.clear();
    
    Muon_innerTrack_highPurity.clear();
    Muon_innerTrack_ValidFraction.clear();
    Muon_Numberofvalidtrackerhits.clear();
    Muon_validMuonHitComb.clear();
    Muon_IP2D_BS.clear();
    Muon_IP3D_BS.clear();
    Muon_IP2D_PV.clear();
    Muon_IP3D_PV.clear();
    
    Muon_outerTrack_p.clear();
    Muon_outerTrack_eta.clear();
    Muon_outerTrack_phi.clear();
    Muon_outerTrack_normalizedChi2.clear();
    Muon_outerTrack_muonStationsWithValidHits.clear();
    Muon_innerTrack_p.clear();
    Muon_innerTrack_eta.clear();
    Muon_innerTrack_phi.clear();
    Muon_innerTrack_normalizedChi2.clear();
    Muon_QInnerOuter.clear();
    
    Muon_combinedQuality_updatedSta.clear();
    Muon_combinedQuality_trkKink.clear();
    Muon_combinedQuality_glbKink.clear();
    Muon_combinedQuality_trkRelChi2.clear();
    Muon_combinedQuality_staRelChi2.clear();
    Muon_combinedQuality_chi2LocalPosition.clear();
    Muon_combinedQuality_chi2LocalMomentum.clear();
    Muon_combinedQuality_localDistance.clear();
    Muon_combinedQuality_globalDeltaEtaPhi.clear();
    Muon_combinedQuality_tightMatch.clear();
    Muon_combinedQuality_glbTrackProbability.clear();
    
    Muon_combinedQuality_match1_dX.clear();
    Muon_combinedQuality_match1_pullX.clear();
    Muon_combinedQuality_match1_pullDxDz.clear();
    Muon_combinedQuality_match1_dY.clear();
    Muon_combinedQuality_match1_pullY.clear();
    Muon_combinedQuality_match1_pullDyDz.clear();
    
    Muon_combinedQuality_match2_dX.clear();
    Muon_combinedQuality_match2_pullX.clear();
    Muon_combinedQuality_match2_pullDxDz.clear();
    Muon_combinedQuality_match2_dY.clear();
    Muon_combinedQuality_match2_pullY.clear();
    Muon_combinedQuality_match2_pullDyDz.clear();
    
    Muon_calEnergy_em.clear();
    Muon_calEnergy_emS9.clear();
    Muon_calEnergy_emS25.clear();
    Muon_calEnergy_had.clear();
    Muon_calEnergy_hadS9.clear();
    
    Muon_segmentCompatibility.clear();
    Muon_caloCompatibility.clear();
    
    Muon_ptErrOverPt.clear();
    Muon_BestTrackPt.clear();
    Muon_BestTrackPtErr.clear();
    
    Muon_BestTrackEta.clear();
    Muon_BestTrackEtaErr.clear();
    
    Muon_BestTrackPhi.clear();
    Muon_BestTrackPhiErr.clear();
    
    Muon_emEt03.clear();
    Muon_hadEt03.clear();
    Muon_nJets03.clear();
    Muon_nTracks03.clear();
    Muon_sumPt03.clear();
    Muon_hadVetoEt03.clear();
    Muon_emVetoEt03.clear();
    Muon_trackerVetoPt03.clear();
    
    Muon_emEt05.clear();
    Muon_hadEt05.clear();
    Muon_nJets05.clear();
    Muon_nTracks05.clear();
    Muon_sumPt05.clear();
    Muon_hadVetoEt05.clear();
    Muon_emVetoEt05.clear();
    Muon_trackerVetoPt05.clear();
    
    PV_x.clear();
    PV_y.clear();
    PV_z.clear();
    PV_NTracks.clear();
    
    BS_x.clear();
    BS_y.clear();
    BS_z.clear();
    
    PVCollection_Size =0;
    
} //END: BkgTreeMaker::analyze



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
    
    ////// Muon inner + outer track
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
