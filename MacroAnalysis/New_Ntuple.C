#include<fstream>
void RM_Branch(TFile *oldfile, TFile *newfile, TString s = "tau3mu");
void Add_Branch(TFile *f, const TH2F* _h, const TH1F* _h1, TString Tipe="Data");
void GetMuonSF(const TH2F* _h, const double pt, const double eta, Double_t *SF, Double_t *SF_e);

void New_Ntuple(){
    TString name[13]={"C","D","E","F", "G", "Ds_preE", "Ds_postE", "B0_preE", "B0_postE", "Bp_preE", "Bp_postE", "DsPhiPi_preE", "DsPhiPi_postE"};
    cout<<"Data:"<<endl;
    for(int i=0; i<5; i++){
        cout<<"Era "<<name[i]<<endl;
        for(int j=0;j<8;j++){
            TString num;
            num.Form("%d",j);
            auto oldfile = TFile::Open("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022"+name[i]+"_"+num+"_tau3mu_ReReco/AnalysedTree_data_2022"+name[i]+"_"+num+"_tau3mu_merged_ReReco.root");
            auto newfile = TFile::Open("New_Ntuple/Name_"+name[i]+"_S"+num+"_tau3mu.root","recreate");
            RM_Branch(oldfile, newfile, "tau3mu");
            // Clean
            oldfile->Close();
            newfile->Close();
            delete oldfile;
            delete newfile;
            TFile *f = new TFile("New_Ntuple/Name_"+name[i]+"_S"+num+"_tau3mu.root","update");
            Add_Branch(f,NULL, NULL, "Data");
            f->Close();
        }
    }
    cout<<"C.C.:"<<endl;
    for(int i=0; i<5; i++){
        cout<<"Era "<<name[i]<<endl;
        for(int j=0;j<8;j++){
            TString num;
            num.Form("%d",j);
            auto oldfile = TFile::Open("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022"+name[i]+"_"+num+"_control_ReReco/AnalysedTree_data_control_2022"+name[i]+"_"+num+"_control_merged_ReReco.root");
            auto newfile = TFile::Open("New_Ntuple/Name_"+name[i]+"_S"+num+"_control.root","recreate");
            RM_Branch(oldfile, newfile, "control");
            // Clean
            oldfile->Close();
            newfile->Close();
            delete oldfile;
            delete newfile;
            TFile *f = new TFile("New_Ntuple/Name_"+name[i]+"_S"+num+"_control.root","update");
            Add_Branch(f, NULL, NULL, "Data");
            f->Close();
        }
    }
    TFile *file = new TFile("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/MacroAnalysis/GM_PF_SF/SF_preE.root","read");
    TH2F *SF_preE = (TH2F*)file->Get("NUM_GlobalMuons_PF_DEN_genTracks_abseta_pt");
    TFile *file2 = new TFile("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/MacroAnalysis/GM_PF_SF/SF_postE.root","read");
    TH2F *SF_postE = (TH2F*)file2->Get("NUM_GlobalMuons_PF_DEN_genTracks_abseta_pt");
    
    TFile *file3 = new TFile("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/MacroAnalysis/histogram_ratio.root","read");
    TH1F *h_Ds_preE =  (TH1F*)file3->Get("ratio_h_Ds_preE");
    TH1F *h_Ds_postE =  (TH1F*)file3->Get("ratio_h_Ds_postE");
    TH1F *h_Bp_preE =  (TH1F*)file3->Get("ratio_h_Bp_preE");
    TH1F *h_Bp_postE =  (TH1F*)file3->Get("ratio_h_Bp_postE");
    TH1F *h_B0_preE =  (TH1F*)file3->Get("ratio_h_B0_preE");
    TH1F *h_B0_postE =  (TH1F*)file3->Get("ratio_h_B0_postE");
    TH1F *h_DsPhiPi_preE =  (TH1F*)file3->Get("ratio_h_DsPhiPi_preE");
    TH1F *h_DsPhiPi_postE =  (TH1F*)file3->Get("ratio_h_DsPhiPi_postE");
    
    cout<<"MC:"<<endl;
    for(int i=5; i<13; i++){
        cout<<"Dataset "<<name[i]<<endl;
        auto oldfile = TFile::Open("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/"+name[i]+"_tau3mu_ReReco/AnalysedTree_MC_"+name[i]+"_tau3mu_merged_ReReco.root");
        TString n="";
        if(i!=12 && i!=11) n="tau3mu";
        else n="control";
        auto newfile = TFile::Open("New_Ntuple/Name_"+name[i]+"_"+n+".root","recreate");
        if(name[i] != "DsPhiPi_preE" && name[i] != "DsPhiPi_postE")RM_Branch(oldfile, newfile, "tau3mu");
        else RM_Branch(oldfile, newfile, "control");
        oldfile->Close();
        newfile->Close();
        delete oldfile;
        delete newfile;
        TFile *f = new TFile("New_Ntuple/Name_"+name[i]+"_"+n+".root","update");
        TFile *file;
        if(name[i]=="Ds_preE" || name[i]=="B0_preE" || name[i]=="Bp_preE" || name[i]=="DsPhiPi_preE"){
            if(name[i]=="Ds_preE") Add_Branch(f, SF_preE, h_Ds_preE,  name[i]);
            if(name[i]=="B0_preE") Add_Branch(f, SF_preE, h_B0_preE,  name[i]);
            if(name[i]=="Bp_preE") Add_Branch(f, SF_preE, h_Bp_preE,  name[i]);
            if(name[i]=="DsPhiPi_preE") Add_Branch(f, SF_preE, h_DsPhiPi_preE,  name[i]);
        }
        if(name[i]=="Ds_postE" || name[i]=="B0_postE" || name[i]=="Bp_postE" || name[i]=="DsPhiPi_postE"){
            if(name[i]=="Ds_postE") Add_Branch(f, SF_postE, h_Ds_postE,  name[i]);
            if(name[i]=="B0_postE") Add_Branch(f, SF_postE, h_B0_postE,  name[i]);
            if(name[i]=="Bp_postE") Add_Branch(f, SF_postE, h_Bp_postE,  name[i]);
            if(name[i]=="DsPhiPi_postE") Add_Branch(f, SF_postE, h_DsPhiPi_postE,  name[i]);
        }
        f->Close();
    }
    
}

void RM_Branch(TFile *oldfile, TFile *newfile, TString s = "tau3mu") {
    
    //Get old file, old tree and set top branch address
    
    TTree* oldtree;
    oldfile->GetObject("FinalTree", oldtree);
    // Deactivate all branches
    oldtree->SetBranchStatus("*",0);
    
    // Activate our branches only:
    oldtree->SetBranchStatus("isMC",1);
    oldtree->SetBranchStatus("lumi",1);
    oldtree->SetBranchStatus("run",1);
    oldtree->SetBranchStatus("evt",1);
    oldtree->SetBranchStatus("puFactor",1);
    oldtree->SetBranchStatus("DeltaR_max",1);
    oldtree->SetBranchStatus("DeltaZ_max",1);
    oldtree->SetBranchStatus("Pmu3",1);
    oldtree->SetBranchStatus("cLP",1);
    oldtree->SetBranchStatus("tKink",1);
    oldtree->SetBranchStatus("segmComp",1);
    oldtree->SetBranchStatus("tripletMass",1);
    oldtree->SetBranchStatus("fv_nC",1);
    oldtree->SetBranchStatus("fv_dphi3D",1);
    oldtree->SetBranchStatus("fv_d3D",1);
    oldtree->SetBranchStatus("fv_d3Dsig",1);
    oldtree->SetBranchStatus("d0",1);
    oldtree->SetBranchStatus("d0sig",1);
    oldtree->SetBranchStatus("d0sig_max",1);
    oldtree->SetBranchStatus("mindca_iso",1);
    oldtree->SetBranchStatus("trkRel",1);
    oldtree->SetBranchStatus("Ptmu1",1);
    oldtree->SetBranchStatus("Etamu1",1);
    oldtree->SetBranchStatus("Ptmu2",1);
    oldtree->SetBranchStatus("Etamu2",1);
    oldtree->SetBranchStatus("Ptmu3",1);
    oldtree->SetBranchStatus("Etamu3",1);
    oldtree->SetBranchStatus("Pmu1",1);
    oldtree->SetBranchStatus("Pmu2",1);
    oldtree->SetBranchStatus("P_tripl",1);
    oldtree->SetBranchStatus("Pt_tripl",1);
    oldtree->SetBranchStatus("Eta_tripl",1);
    oldtree->SetBranchStatus("MVA1",1);
    oldtree->SetBranchStatus("MVA2",1);
    oldtree->SetBranchStatus("MVASoft1",1);
    oldtree->SetBranchStatus("MVASoft2",1);
    oldtree->SetBranchStatus("ChargeMu1",1);
    oldtree->SetBranchStatus("ChargeMu2",1);
    oldtree->SetBranchStatus("ChargeMu3",1);
    oldtree->SetBranchStatus("nVtx",1);
    if(s=="tau3mu"){
        oldtree->SetBranchStatus("tripletMassReso",1);
        oldtree->SetBranchStatus("category",1);
        oldtree->SetBranchStatus("MVA3",1);
        oldtree->SetBranchStatus("MVASoft3",1);
        oldtree->SetBranchStatus("dimu_OS1",1);
        oldtree->SetBranchStatus("dimu_OS2",1);
    }
    //Create a clone of old tree header. Do not copy events
    //TTree *newtree;
    auto newtree = oldtree->CloneTree(0);
    
    // Here we copy the branches
    newtree->CopyEntries(oldtree);
    
    // Flush to disk
    newfile->Write();
}

void Add_Branch(TFile *f, const TH2F* _h, const TH1F* _h1, TString Tipe) {
    TTree *T = (TTree*)f->Get("FinalTree");
    //float px,py;
    Double_t weight=99.0;
    Double_t weight_MC=99.00; //Peso complessivo
    Double_t weight_MC2=99.00; //Peso complessivo
    
    Double_t weight_nVtx=99.0;
    Double_t weight_nVtx_err=0.0;
    
    Double_t weight_CC = 99.0;
    Double_t weight_CC_err=0.0;
    
    Double_t mu1_muSF=1.0;
    Double_t mu1_muSF_err=0.0;
    Double_t mu2_muSF=1.0;
    Double_t mu2_muSF_err=0.0;
    Double_t mu3_muSF=1.0;
    Double_t mu3_muSF_err=0.0;
    
    //Costanti:
    Double_t xsection_Bp_preE=3.508e+9, xsection_Bp_postE=3.538e+9;
    Double_t xsection_Ds_preE=9.827e+9, xsection_Ds_postE=9.815e+9;
    Double_t xsection_B0_preE=3.520e+9, xsection_B0_postE=3.525e+9;
    Double_t xsection_DsPhiPi_preE=1.106e+10, xsection_DsPhiPi_postE=1.103e+10;
    
    Double_t lumi_tau3mu_preE=8.052, lumi_tau3mu_postE=26.758;
    Double_t lumi_control_preE=0.397, lumi_control_postE=1.33;
    
    Double_t BR_tau3mu=1.0e-7, BR_control=1.29e-5; //τ->3μ or Phi->2μ (la parte finale)
    
    Double_t BR_Dstau= 5.48e-2, BR_DsPhiPi=1.3e-5, BR_Bptau= 3.33e-2, BR_B0tau=3.35e-2; //Controlla BR B devo inculdere anche B->Ds ?
    
    Double_t N_Bp_preE=515160, N_Bp_postE=1627733;
    Double_t N_Ds_preE=2077873, N_Ds_postE=7428463;
    Double_t N_B0_preE=837468, N_B0_postE=2702174;
    Double_t N_DsPhiPi_preE=297926, N_DsPhiPi_postE=1199059;
    
    Double_t weight_CC_preE =0.77;
    Double_t weight_CC_postE =1.03;
    Double_t weight_CC_preE_err =0.09;
    Double_t weight_CC_postE_err =0.05;
    
    
    TBranch *b_weight = T->Branch("weight",&weight,"weight/D");
    TBranch *b_weight_MC = T->Branch("weight_MC",&weight_MC,"weight_MC/D");
    TBranch *b_weight_MC2 = T->Branch("weight_MC2",&weight_MC2,"weight_MC2/D");
    
    TBranch *b_mu1_muSF = T->Branch("mu1_muSF",&mu1_muSF,"mu1_muSF/D");
    TBranch *b_mu1_muSF_err = T->Branch("mu1_muSF_err",&mu1_muSF_err,"mu1_muSF_err/D");
    TBranch *b_mu2_muSF = T->Branch("mu2_muSF",&mu2_muSF,"mu2_muSF/D");
    TBranch *b_mu2_muSF_err = T->Branch("mu2_muSF_err",&mu2_muSF_err,"mu2_muSF_err/D");
    TBranch *b_mu3_muSF = T->Branch("mu3_muSF",&mu3_muSF,"mu3_muSF/D");
    TBranch *b_mu3_muSF_err = T->Branch("mu3_muSF_err",&mu3_muSF_err,"mu3_muSF_err/D");
    
    TBranch *b_weight_nVtx = T->Branch("weight_nVtx",&weight_nVtx,"weight_nVtx/D");
    TBranch *b_weight_nVtx_err = T->Branch("weight_nVtx_err",&weight_nVtx_err,"weight_nVtx_err/D");
    TBranch *b_weight_CC = T->Branch("weight_CC",&weight_CC,"weight_CC/D");
    TBranch *b_weight_CC_err = T->Branch("weight_CC_err",&weight_CC_err,"weight_CC_err/D");
    
    Double_t pt1, eta1, pt2, eta2, pt3, eta3;
    Double_t Vtx;
    
    T->SetBranchAddress("Ptmu1",&pt1);
    T->SetBranchAddress("Ptmu2",&pt2);
    T->SetBranchAddress("Ptmu3",&pt3);
    T->SetBranchAddress("Etamu1",&eta1);
    T->SetBranchAddress("Etamu2",&eta2);
    T->SetBranchAddress("Etamu3",&eta3);
    
    T->SetBranchAddress("nVtx",&Vtx);
    
    Long64_t nentries = T->GetEntries();
    for (Long64_t i=0;i<nentries;i++) {
        T->GetEntry(i);
        if(Tipe=="Data") weight =1.0;
        if(Tipe=="Ds_preE") weight = (xsection_Ds_preE*lumi_tau3mu_preE*BR_tau3mu*BR_Dstau)/N_Ds_preE;
        if(Tipe=="Ds_postE") weight = xsection_Ds_postE*lumi_tau3mu_postE*BR_tau3mu*BR_Dstau/N_Ds_postE; //avevo diviso per le pre E
        if(Tipe=="B0_preE") weight= xsection_B0_preE*lumi_tau3mu_preE*BR_tau3mu*BR_B0tau/N_B0_preE;
        if(Tipe=="B0_postE") weight = xsection_B0_postE*lumi_tau3mu_postE*BR_tau3mu*BR_B0tau/N_B0_postE;
        if(Tipe=="Bp_preE") weight= xsection_Bp_preE*lumi_tau3mu_preE*BR_tau3mu*BR_Bptau/N_Bp_preE;
        if(Tipe=="Bp_postE") weight = xsection_Bp_postE*lumi_tau3mu_postE*BR_tau3mu*BR_Bptau/N_Bp_postE;
        if(Tipe=="DsPhiPi_preE") weight= xsection_DsPhiPi_preE*lumi_control_preE*BR_control*BR_DsPhiPi/N_DsPhiPi_preE;
        if(Tipe=="DsPhiPi_postE") weight = xsection_DsPhiPi_postE*lumi_control_postE*BR_control*BR_DsPhiPi/N_DsPhiPi_postE;
        
        
        Double_t SF1[2]={1.,0.};
        Double_t SF2[2]={1.,0.};
        Double_t SF3[2]={1.,0.};
        if(Tipe!="Data"){
            GetMuonSF(_h, pt1, eta1, &SF1[0], &SF1[1]);
            GetMuonSF(_h, pt2, eta2, &SF2[0], &SF2[1]);
            if(Tipe!="DsPhiPi_preE" && Tipe!="DsPhiPi_postE"){
                GetMuonSF(_h, pt3, eta2, &SF3[0], &SF3[1]);
            }
            int ind = _h1->GetXaxis()->FindBin(Vtx);
            weight_nVtx =_h1->GetBinContent(ind);
            weight_nVtx_err =_h1->GetBinError(ind);
        }
        if(Tipe=="Data"){
            weight_nVtx = 1.0;
            weight_nVtx_err = 0.0;
            weight_CC =1.0;
            weight_CC_err =0.0;
        }
        mu1_muSF=SF1[0]; mu2_muSF=SF2[0]; mu3_muSF=SF3[0];
        mu1_muSF_err=SF1[1]; mu2_muSF_err=SF2[1]; mu3_muSF_err=SF3[1];
        
        if(Tipe!="Data"){
            if(Tipe=="Ds_preE" || Tipe=="B0_preE" || Tipe=="Bp_preE"){
                weight_CC =weight_CC_preE;
                weight_CC_err =weight_CC_preE_err;
            }
            if(Tipe=="Ds_postE" || Tipe=="B0_postE" || Tipe=="Bp_postE"){
                weight_CC =weight_CC_postE;
                weight_CC_err =weight_CC_postE_err;
            }
            if(Tipe=="DsPhiPi_preE" || Tipe=="DsPhiPi_postE"){
                weight_CC =1.0;
                weight_CC_err =0.0;
            }
        }
        
        
        weight_MC=weight*weight_CC*mu3_muSF*weight_nVtx;
        weight_MC2=1.;
        if(Tipe=="Ds_preE") weight_MC2= (N_Bp_preE/N_Ds_preE)*(BR_Dstau/BR_Bptau)*weight_CC*mu3_muSF*weight_nVtx;
        if(Tipe=="Ds_postE") weight_MC2 = (N_Bp_postE/N_Ds_postE)*(BR_Dstau/BR_Bptau)*weight_CC*mu3_muSF*weight_nVtx;
        if(Tipe=="B0_preE") weight_MC2= (N_Bp_preE/N_B0_preE)*(BR_B0tau/BR_Bptau)*weight_CC*mu3_muSF*weight_nVtx;
        if(Tipe=="B0_postE") weight_MC2 = (N_Bp_postE/N_B0_postE)*(BR_B0tau/BR_Bptau)*weight_CC*mu3_muSF*weight_nVtx;
        if(Tipe=="Bp_preE") weight_MC2= (N_Bp_preE/N_Bp_preE)*(BR_Bptau/BR_Bptau)*weight_CC*mu3_muSF*weight_nVtx;
        if(Tipe=="Bp_postE") weight_MC2 = (N_Bp_postE/N_Bp_postE)*(BR_Bptau/BR_Bptau)*weight_CC*mu3_muSF*weight_nVtx;
        
        /*
        if(Tipe!="Data" && Tipe!="DsPhiPi_postE" && Tipe!="DsPhiPi_preE" && i%100==0){
            cout<<"*******"<<i<<"*******"<<endl;
            cout<<pt1<<" "<<pt2<<" "<<pt3<<endl;
            cout<<eta1<<" "<<eta2<<" "<<eta3<<endl;
            cout<<mu1_muSF<<" "<<mu2_muSF<<" "<<mu3_muSF<<endl;
        }
         */
        b_weight->Fill();
        b_weight_MC->Fill();
        b_weight_MC2->Fill();
        
        b_mu1_muSF->Fill();
        b_mu2_muSF->Fill();
        b_mu3_muSF->Fill();
        b_mu1_muSF_err->Fill();
        b_mu2_muSF_err->Fill();
        b_mu3_muSF_err->Fill();
        
        b_weight_nVtx->Fill();
        b_weight_nVtx_err->Fill();
        b_weight_CC->Fill();
        b_weight_CC_err->Fill();
    }
    //T->Print();
    T->Write("", TObject::kOverwrite);
    delete T;
    

}

void GetMuonSF(const TH2F* _h, const double pt, const double eta, Double_t *SF, Double_t *SF_e){
    if( pt < _h->GetYaxis()->GetXmax() && pt > _h->GetYaxis()->GetXmin() &&
       std::abs(eta) < _h->GetXaxis()->GetXmax() && std::abs(eta) > _h->GetXaxis()->GetXmin()){
        int ipt = _h->GetYaxis()->FindBin(pt);
        int ieta = _h->GetXaxis()->FindBin(std::abs(eta));
        *SF = _h->GetBinContent(ieta, ipt);
        *SF_e = _h->GetBinError(ieta, ipt);
    }else{
        *SF = 1.;
        *SF_e = 0.;
    }
}
