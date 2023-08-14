#include<fstream>
using namespace RooFit;
void Plot_DMC2(){
    
    //Data preE
    TChain *ch_pre = new TChain("FinalTree");
    TString name[2]={"C","D-v2"};
    for(int i=0; i<2; i++){
        for(int j=0;j<8;j++){
            TString num;
            num.Form("%d",j);
            ch_pre->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022"+name[i]+"_"+num+"_tau3mu_test/AnalysedTree_data_2022"+name[i]+"_"+num+"_tau3mu_merged_test.root");
        }
    }
    //Data PostE
    TChain *ch_post = new TChain("FinalTree");
    TString name2[3]={"E","F","G"};
    for(int i=0; i<3; i++){
        for(int j=0;j<8;j++){
            TString num;
            num.Form("%d",j);
            ch_post->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022"+name2[i]+"_"+num+"_tau3mu_test/AnalysedTree_data_2022"+name2[i]+"_"+num+"_tau3mu_merged_test.root");
        }
    }
    //MC B0 preE
    TChain *B0_pre_mc = new TChain("FinalTree");
    B0_pre_mc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/B0_preE_tau3mu_test/AnalysedTree_MC_B0_preE_tau3mu0.root");
    //MC B0 postE
    TChain *B0_post_mc = new TChain("FinalTree");
    B0_post_mc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/B0_postE_tau3mu_test/AnalysedTree_MC_B0_postE_tau3mu0.root");
    B0_post_mc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/B0_postE_tau3mu_test/AnalysedTree_MC_B0_postE_tau3mu1.root");
    
    //MC Bp preE
    TChain *Bp_pre_mc = new TChain("FinalTree");
    Bp_pre_mc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/Bp_preE_tau3mu_test/AnalysedTree_MC_Bp_preE_tau3mu0.root");
    //MC Bp postE
    TChain *Bp_post_mc = new TChain("FinalTree");
    Bp_post_mc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/Bp_postE_tau3mu_test/AnalysedTree_MC_Bp_postE_tau3mu0.root");
    //Bp_post_mc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/Bp_postE_tau3mu_test/AnalysedTree_MC_Bp_postE_tau3mu1.root");
    
    //MC Ds preE
    TChain *Ds_pre_mc = new TChain("FinalTree");
    Ds_pre_mc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/Ds_preE_tau3mu_test/AnalysedTree_MC_Ds_preE_tau3mu0.root");
    //MC Ds postE
    TChain *Ds_post_mc = new TChain("FinalTree");
    Ds_post_mc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/Ds_postE_tau3mu_test/AnalysedTree_MC_Ds_postE_tau3mu0.root");
    Ds_post_mc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/Ds_postE_tau3mu_test/AnalysedTree_MC_Ds_postE_tau3mu1.root");
    
    //# MC
    double n_B0_pre = B0_pre_mc->GetEntries(), n_B0_post = B0_post_mc->GetEntries(), n_Bp_pre = Bp_pre_mc->GetEntries(), n_Bp_post = Bp_post_mc->GetEntries(), n_Ds_pre = Ds_pre_mc->GetEntries(), n_Ds_post = Ds_post_mc->GetEntries();
    
    //# Data
    double n_pre = ch_pre->GetEntries(), n_post = ch_post->GetEntries();
    
    
    TString titles[] = {"Dati_preE", "B0_preE", "Bp_preE", "Ds_preE","Dati_PostE", "B0_postE", "Bp_postE", "Ds_postE"};
    TString reso_range[] = {"reso<0.0065","0.0065<reso<0.0105","0.0105<reso<0.02"};
    TString reso_ca[] = {"category==0","category==1","category==2"};
    TString mass_raneg[] = {"(tripletMass<1.753 || tripletMass>1.801)", "(tripletMass<1.739 || tripletMass>1.815)", "(tripletMass<1.727 || tripletMass>1.827)"};
    
    float cs_pre[] = {3.520, 3.508, 9.827}; //Ordine B0 Bp Ds
    float cs_post[] = {3.525, 3.538, 9.815};
    float sf_pre[3], sf_post[3];
    //Sf mc:
    float sum1=0, sum2=0;
    for(int j=0;j<3;j++){
        sum1+=cs_pre[j]; sum2+=cs_post[j];
    }
    for (int i=0; i<3;i++){
        //sf_pre[i]=cs_pre[i]/sum1;
        //sf_post[i]=cs_post[i]/sum2;
        sf_pre[i]=cs_pre[i]/(sum1+sum2);
        sf_post[i]=cs_post[i]/(sum1+sum2);
    }
    //variables plot
    TString var[] = {
                  //   "Ptmu1","Ptmu2","Ptmu3","Etamu1","Etamu2","Etamu3",
                 //    "SVx", "SVy", "SVz",
                 //    "RefVx1", "RefVy1", "RefVz1",
                     "Pmu3","cLP","tKink","segmComp","fv_nC","d0sig","fv_dphi3D","fv_d3Dsig",
                 //    "bs_sv_d3D","bs_sv_d3Dsig","pv_sv_dxy","pv_sv_dxy_sig",
                 //    "pv_sv_dxy/pv_sv_dxy_sig",
                     "mindca_iso","trkRel","d0sig_max"
                //  "nMatchesMu3"
                    };

    int n = sizeof(var)/sizeof(var[0]);
    
    float factor=1.;
    
    for (int yy=0; yy<3; yy++){
        
        TH1F *hdata_pre[n];
        TH1F *hdata_post[n];
        TH1F *hmc_Ds_pre[n];
        TH1F *hmc_Ds_post[n];
        TH1F *hmc_B0_pre[n];
        TH1F *hmc_B0_post[n];
        TH1F *hmc_Bp_pre[n];
        TH1F *hmc_Bp_post[n];
        THStack *hs_pre[n];
        THStack *hs_post[n];
        
        TString binning;
        
        for(int k = 0; k<n; k++){
            //            continue;
            TString varname = var[k];
            TString s = std::to_string(k);
            
            if(varname=="Ptmu1" || varname=="Ptmu2" || varname=="Ptmu3") binning = "(30,0,30)";
            if(varname=="Etamu1" || varname=="Etamu2" || varname=="Etamu3") binning = "(30,0,2.5)";
            if(varname=="Pmu3") binning = "(100,0,50)";
            if(varname=="cLP") binning = "(60,0,20)";
            if(varname=="segmComp") binning = "(100,-0.1,1.1)";
            if(varname=="tKink") binning = "(50,0,50)";
            if(varname=="fv_nC") binning = "(50,-0.1,5.1)";
            if(varname=="d0sig") binning = "(36,-0.1,18)";
            if(varname=="d0sig_max") binning = "(36,-0.1,30)";
            if(varname=="mindca_iso") binning = "(40,0,0.4)";
            if(varname=="trkRel") binning = "(40,0.05,1.1)";
            if(varname=="nMatchesMu3") binning = "(20,0,20)";
            if(varname=="tripletMassReso") binning = "(80,0,0.02)";
            if(varname=="fv_dphi3D") binning = "(42,-0.01,0.20)";
            if(varname=="fv_d3Dsig") binning = "(50,-0.1,80)";
            if(varname=="fv_d3D") binning = "(40,0,8)";
            if(varname=="fv_d3D/fv_d3Dsig") binning = "(50,0,0.12)";
            if(varname=="bs_sv_d3Dsig") binning = "(80,-0.1,150)";
            if(varname=="bs_sv_d3D") binning = "(50,0,5)";
            if(varname=="bs_sv_d3D/bs_sv_d3Dsig") binning = "(50,0,0.06)";
            if(varname=="abs(dxy1/dxyErr1)" || varname=="abs(dxy2/dxyErr2)" || varname=="abs(dxy3/dxyErr3)" )  binning = "(50,0,40)";
            if(varname=="dxyErr1" || varname=="dxyErr2" || varname=="dxyErr3" )  binning = "(50,0,0.02)";
            if(varname.Contains("mu_pt")) binning = "(80,0,40)";
            if(varname.Contains("mu_eta")) binning = "(80,-2.4,2.4)";
            if(varname.Contains("BestTrackPt")) binning = "(80,0,40)";
            if(varname.Contains("BestTrackEta")) binning = "(80,-2.4,2.4)";
            if(varname.Contains("BestTrackPhi")) binning = "(80,0,3.2)";
            if(varname.Contains("BestTrack") && varname.Contains("Err")) binning = "(80,0,0.0025)";
            if(varname.Contains("BestTrackPtErr")) binning = "(80,0,0.5)";
            if(varname=="abs(RefVz1 - SVz)") binning = "(40,0,8)";
            if(varname=="SVz"|| varname=="RefVz1") binning = "(40,-15,15)";
            if(varname=="SVx" || varname=="SVy") binning = "(40,-1.5,1.5)";
            if(varname=="RefVx1" || varname=="RefVy1") binning = "(120,-0.1,0.1)";
            if(varname=="pv_sv_dxy") binning = "(40,0,3)";
            if(varname=="pv_sv_dxy_sig") binning = "(80,0,100)";
            if(varname=="pv_sv_dxy/pv_sv_dxy_sig") binning = "(80,0,0.04)";
            
            ch_pre->Draw(varname+">>hdata_pre"+s+binning, mass_raneg[yy]+"&&"+reso_ca[yy],"");
            ch_post->Draw(varname+">>hdata_post"+s+binning, mass_raneg[yy]+"&&"+reso_ca[yy]);
            Ds_pre_mc->Draw(varname+">>hmc_Ds_pre"+s+binning, reso_ca[yy]);
            Ds_post_mc->Draw(varname+">>hmc_Ds_post"+s+binning, reso_ca[yy]);
            Bp_pre_mc->Draw(varname+">>hmc_Bp_pre"+s+binning, reso_ca[yy]);
            Bp_post_mc->Draw(varname+">>hmc_Bp_post"+s+binning, reso_ca[yy]);
            B0_pre_mc->Draw(varname+">>hmc_B0_pre"+s+binning, reso_ca[yy]);
            B0_post_mc->Draw(varname+">>hmc_B0_post"+s+binning, reso_ca[yy]);
            
            hdata_pre[k] = (TH1F *)gDirectory->Get("hdata_pre"+s);
            hdata_post[k] = (TH1F *)gDirectory->Get("hdata_post"+s);
            hmc_Ds_pre[k] = (TH1F *)gDirectory->Get("hmc_Ds_pre"+s);
            hmc_Ds_post[k] = (TH1F *)gDirectory->Get("hmc_Ds_post"+s);
            hmc_Bp_pre[k] = (TH1F *)gDirectory->Get("hmc_Bp_pre"+s);
            hmc_Bp_post[k] = (TH1F *)gDirectory->Get("hmc_Bp_post"+s);
            hmc_B0_pre[k] = (TH1F *)gDirectory->Get("hmc_B0_pre"+s);
            hmc_B0_post[k] = (TH1F *)gDirectory->Get("hmc_B0_post"+s);
            
            TCanvas *c2 = new TCanvas("c2","c2",150,10,990,660);
            //gStyle->SetOptTitle(0);
            gStyle->SetOptStat(0);
            c2->cd();
            
            //Scalo MC:->
            hmc_Ds_pre[k]->Scale(factor*sf_pre[2]/hmc_Ds_pre[k]->Integral());
            hmc_Ds_post[k]->Scale(factor*sf_post[2]/hmc_Ds_post[k]->Integral());
            hmc_Bp_pre[k]->Scale(factor*sf_pre[1]/hmc_Bp_pre[k]->Integral());
            hmc_Bp_post[k]->Scale(factor*sf_post[1]/hmc_Bp_post[k]->Integral());
            hmc_B0_pre[k]->Scale(factor*sf_pre[0]/hmc_B0_pre[k]->Integral());
            hmc_B0_post[k]->Scale(factor*sf_post[0]/hmc_B0_post[k]->Integral());
            
            hmc_Ds_pre[k]->SetLineColor(kBlue);
            hmc_Ds_pre[k]->SetLineWidth(3);
            hmc_Ds_pre[k]->SetFillStyle(3004);
            hmc_Ds_pre[k]->SetFillColor(kBlue);
            
            hmc_Bp_pre[k]->SetLineColor(kGreen);
            hmc_Bp_pre[k]->SetLineWidth(3);
            hmc_Bp_pre[k]->SetFillStyle(3004);
            hmc_Bp_pre[k]->SetFillColor(kGreen);
            
            hmc_B0_pre[k]->SetLineColor(kYellow);
            hmc_B0_pre[k]->SetLineWidth(3);
            hmc_B0_pre[k]->SetFillStyle(3004);
            hmc_B0_pre[k]->SetFillColor(kYellow);
            
            hmc_Ds_post[k]->SetLineColor(kBlue);
            hmc_Ds_post[k]->SetLineWidth(3);
            hmc_Ds_post[k]->SetFillStyle(3004);
            hmc_Ds_post[k]->SetFillColor(kBlue);
            
            hmc_Bp_post[k]->SetLineColor(kGreen);
            hmc_Bp_post[k]->SetLineWidth(3);
            hmc_Bp_post[k]->SetFillStyle(3004);
            hmc_Bp_post[k]->SetFillColor(kGreen);
            
            hmc_B0_post[k]->SetLineColor(kYellow);
            hmc_B0_post[k]->SetLineWidth(3);
            hmc_B0_post[k]->SetFillStyle(3004);
            hmc_B0_post[k]->SetFillColor(kYellow);
            
            //Scalo Dati:
            hdata_pre[k]->Add(hdata_post[k]); //ADD Data
            hdata_pre[k]->Scale(1./hdata_pre[k]->Integral());
    
            
            //Unisco le ere:
            hmc_Bp_pre[k]->Add(hmc_Bp_post[k]);
            hmc_B0_pre[k]->Add(hmc_B0_post[k]);
            hmc_Ds_pre[k]->Add(hmc_Ds_post[k]);

            hs_pre[k] = new THStack("hs_pre","");
            hs_pre[k]->Add(hmc_Bp_pre[k]);
            hs_pre[k]->Add(hmc_B0_pre[k]);
            hs_pre[k]->Add(hmc_Ds_pre[k]);
            
            
            //plot makeup
            double Y_max_pre = std::max(hdata_pre[k]->GetMaximum(), hs_pre[k]->GetMaximum());
            Y_max_pre = Y_max_pre*1.05;
            
            hdata_pre[k]->SetTitle(var[k]+" 2022 in "+reso_range[yy]);
            hdata_pre[k]->GetYaxis()->SetRangeUser(0, Y_max_pre);
            /*
            hdata_post[k]->GetYaxis()->SetRangeUser(0, Y_max_post);
            
            hdata_post[k]->SetTitle(var[k]+" Post_EE in "+reso_range[yy]);
            hdata_post[k]->GetXaxis()->SetTitle(var[k]);
            hdata_post[k]->GetYaxis()->SetTitle("a.u.");
            hdata_post[k]->GetYaxis()->SetTitleSize(22);
            hdata_post[k]->GetYaxis()->SetTitleFont(43);
            hdata_post[k]->GetYaxis()->SetTitleOffset(1.25);
            hdata_post[k]->SetLineColor(kRed);
            hdata_post[k]->SetLineWidth(3);
            hdata_post[k]->SetFillStyle(3005);
            hdata_post[k]->SetFillColor(kRed);
            */
            hdata_pre[k]->GetXaxis()->SetTitle(var[k]);
            hdata_pre[k]->GetYaxis()->SetTitle("a.u.");
            hdata_pre[k]->GetYaxis()->SetTitleSize(22);
            hdata_pre[k]->GetYaxis()->SetTitleFont(43);
            hdata_pre[k]->GetYaxis()->SetTitleOffset(1.25);
            hdata_pre[k]->SetLineColor(kRed);
            hdata_pre[k]->SetLineWidth(3);
            hdata_pre[k]->SetFillStyle(3005);
            hdata_pre[k]->SetFillColor(kRed);
            
            
            
            hdata_pre[k]->Draw("hist");
            hs_pre[k]->Draw("hist same");
            hdata_pre[k]->Draw("hist same");
            
            //hs_pre[k]->SetStats(0);
            Double_t x_leg_left  = 0.55;
            Double_t x_leg_right = 0.90;
            Double_t y_leg_left  = 0.63;
            Double_t y_leg_right = 0.90;
            if(varname=="segmComp") { x_leg_left = 0.1; x_leg_right = 0.45; }
            TLegend*leg = new TLegend(x_leg_left,y_leg_left,x_leg_right,y_leg_right);
            leg->AddEntry(hmc_Bp_pre[k],"MC Bp","f");
            leg->AddEntry(hmc_B0_pre[k],"MC B0","f");
            leg->AddEntry(hmc_Ds_pre[k],"MC Ds","f");
            leg->AddEntry(hdata_pre[k],"data","f");
            leg->Draw();
            
            //c2->SaveAs("plot_MCD/"+varname+reso_range[yy]+"_preE_.png");
            c2->SaveAs("plot_MCD2/"+varname+"_"+reso_range[yy]+"_.png");
        }
    }
    
}
