void Plot_nVtx_nPu(){
    TChain *ch_data = new TChain("/TreeMakerBkg/ntuple");
    for(int j=0;j<8;j++){
        TString num;
        num.Form("%d",j);
        for(int k=0;k<100;k++){
            TString num2;
            num2.Form("%d",k);
            ch_data->Add("/lustre/cms/store/user/caruta/ParkingDoubleMuonLowMass5/SkimDsTau3mu_2022eraC_stream5_Mini_v6/221215_112702/000"+num+"/TreeData_"+num2+".root");
            ch_data->Add("/lustre/cms/store/user/caruta/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraG_stream5_Mini_v6/221219_091945/000"+num+"/TreeData_"+num2+".root");
            ch_data->Add("/lustre/cms/store/user/caruta/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraF_stream5_Mini_v6/221216_083351/000"+num+"/TreeData_"+num2+".root");
            ch_data->Add("/lustre/cms/store/user/caruta/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraE_stream5_Mini_v6/221215_181121/000"+num+"/TreeData_"+num2+".root");
            ch_data->Add("/lustre/cms/store/user/caruta/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraD-v2_stream5_Mini_v6/221215_170636/000"+num+"/TreeData_"+num2+".root");
        }
    }
    TChain *ch_MC = new TChain("/TreeMakerBkg/ntuple");
    for(int k=0;k<173;k++){
        TString num2;
        num2.Form("%d",k);
        ch_MC->Add("/lustre/cms/store/user/mbuonsan/DstoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Ds_new_Mini_postE/230324_155859/0000/TreeMC_"+num2+".root");
        ch_MC->Add("/lustre/cms/store/user/mbuonsan/BdtoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bd_Mini_postE/230324_154250/0000/TreeMC_"+num2+".root");
        ch_MC->Add("/lustre/cms/store/user/mbuonsan/ButoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bu_Mini_postE/230324_154610/0000/TreeMC_"+num2+".root");
    }
    
    TString var[2]={"PVCollection_Size","nPileUpInt"};
    TString reng[2]={"(75,0,75)","(75,0,75)"};
    TH1F *hm_nP, *hm_PV;
    for(int i=0;i<2;i++){
        gStyle->SetOptStat(0);
        TH1F *h, *h2;
        ch_data->Draw(var[i]+">>h"+reng[i],"","N");
        ch_MC->Draw(var[i]+">>h2"+reng[i],"","N");
        
        h = (TH1F *)gDirectory->Get("h");
        h2 = (TH1F *)gDirectory->Get("h2");
        
        TCanvas *c=new TCanvas("c","c",1200,800);
        c->cd();
        h->Scale(1./h->Integral()); h2->Scale(1./h2->Integral());
        h->SetLineColor(kBlue);
        h->SetLineWidth(3);
        h->SetFillStyle(3004);
        h->SetFillColor(kBlue);
        
        h2->SetLineColor(kGreen);
        h2->SetLineWidth(3);
        h2->SetFillStyle(3004);
        h2->SetFillColor(kGreen);
        Double_t x_leg_left  = 0.55;
        Double_t x_leg_right = 0.90;
        Double_t y_leg_left  = 0.63;
        Double_t y_leg_right = 0.90;
        
        
        TLegend*leg = new TLegend(x_leg_left,y_leg_left,x_leg_right,y_leg_right);
        leg->AddEntry(h2,"MC Ds","f");
        leg->AddEntry(h,"data","f");
        leg->Draw("same");
        
        //h2->Draw("histo");
        h->Draw("histo");
        h2->Draw("histo same");
        c->SaveAs("Plot_nVtx_nPu/"+var[i]+".png");
        delete c;
    }
    
    ch_MC->Draw("nPileUpInt>>hm_nP(75,0,75)","","N");
    ch_MC->Draw("PVCollection_Size>>hm_PV(75,0,75)","","N");
    hm_PV = (TH1F *)gDirectory->Get("hm_PV");
    hm_nP = (TH1F *)gDirectory->Get("hm_nP");
    TCanvas *c3=new TCanvas("c3","c3",1200,800);
    c3->cd();
    hm_nP->Scale(1./hm_nP->Integral()); hm_PV->Scale(1./hm_PV->Integral());
    hm_nP->SetLineColor(kBlue);
    hm_nP->SetLineWidth(3);
    hm_nP->SetFillStyle(3004);
    hm_nP->SetFillColor(kBlue);
    
    hm_PV->SetLineColor(kRed);
    hm_PV->SetLineWidth(3);
    hm_PV->SetFillStyle(3004);
    hm_PV->SetFillColor(kRed);
    Double_t x_leg_left  = 0.55;
    Double_t x_leg_right = 0.90;
    Double_t y_leg_left  = 0.63;
    Double_t y_leg_right = 0.90;
    hm_PV->Draw("histo");
    hm_nP->Draw("histo same");
    TLegend*leg = new TLegend(x_leg_left,y_leg_left,x_leg_right,y_leg_right);
    leg->AddEntry(hm_nP,"MC "+var[1],"f");
    leg->AddEntry(hm_PV,"MC "+var[0],"f");
    leg->Draw("same");
    
    /*
    ch_data->Draw("nPileUpInt>>h4(30,4294000000,4296000000","","N");
    TCanvas *c2= new TCanvas("c2","c2",1200,800);
    c2->cd();
    TH1F *h4;
    h4 = (TH1F *)gDirectory->Get("h4");
    h4->Scale(1./h4->Integral());
    h4->SetLineColor(kBlue);
    h4->SetLineWidth(3);
    h4->SetFillStyle(3004);
    h4->SetFillColor(kBlue);
    h4->Draw("histo");
    c2->SaveAs("Plot_nVtx_nPu/nPileUpInt_2.png");
     */
    
}
