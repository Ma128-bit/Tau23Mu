#include<fstream>
using namespace RooFit;
void Control_plot(){
    //Luminosità totale
    float lumi=1.754213258; //recorded lumi by HLT_DoubleMu3_Trk_Tau3mu_v*
    float lumi_preE=0.403852348; //recorded lumi by HLT_DoubleMu3_Trk_Tau3mu_v*
    float lumi_postE=1.35036091; //recorded lumi by HLT_DoubleMu3_Trk_Tau3mu_v*
    Double_t xsection_mc_postE =1.103e10; //Ds Production Cross section
    Double_t xsection_mc_preE =1.106e10; //Ds Production Cross section
    Double_t BR = 1.29e-5;  //Branching ratio Ds to Phi Pi
    //Data ALL
    TChain *ch_tot = new TChain("FinalTree");
    TString name[6]={"C","D", "E","F", "G"};
    for(int i=0; i<5; i++){
        for(int j=0;j<8;j++){
            TString num;
            num.Form("%d",j);
            ch_tot->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022"+name[i]+"_"+num+"_control_ReReco/AnalysedTree_data_control_2022"+name[i]+"_"+num+"_control_merged_ReReco.root");
        }
    }
    //MC ALL
    TChain *tmc_1 = new TChain("FinalTree");
    tmc_1->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/DsPhiPi_preE_tau3mu_ReReco/AnalysedTree_MC_DsPhiPi_preE_tau3mu0.root");
    double n1 = tmc_1->GetEntries();
    TChain *tmc_2 = new TChain("FinalTree");
    tmc_2->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/DsPhiPi_postE_tau3mu_ReReco/AnalysedTree_MC_DsPhiPi_postE_tau3mu0.root");
    double n2 = tmc_2->GetEntries();
    //double N_MC = n1+n2;  //rereco Total number of events in MC sample
    double N_MC= 297926+1199059;
    
    Double_t xsection_mc =(xsection_mc_postE*n1+xsection_mc_postE*n2)/(N_MC);
    
    TString invmass_SB = "(tripletMass<1.80 && tripletMass>1.70)";
    TString invmass_peak = "(tripletMass<2.01 && tripletMass>1.93)";
    TString binning_mass = "(42, 1.60, 2.02)";
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
    TH1F *hdata_bkg[n];
    TH1F *hdata_sgn[n];
    TH1F *hmc_sgn[n];
    TH1F *hmc_sgn2[n];
    
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
        
        ch_tot->Draw(varname+">>hdata_bkg"+s+binning, invmass_SB);
        ch_tot->Draw(varname+">>hdata_sgn"+s+binning, invmass_peak);
        tmc_1->Draw(varname+">>hmc_sgn"+s+binning, invmass_peak);
        tmc_2->Draw(varname+">>hmc_sgn2"+s+binning, invmass_peak);
        
        hdata_bkg[k] = (TH1F *)gDirectory->Get("hdata_bkg"+s);
        hdata_sgn[k] = (TH1F *)gDirectory->Get("hdata_sgn"+s);
        hmc_sgn[k] = (TH1F *)gDirectory->Get("hmc_sgn"+s);
        hmc_sgn2[k] = (TH1F *)gDirectory->Get("hmc_sgn2"+s);
        
        TCanvas *c2 = new TCanvas("c2","c2",150,10,990,660);
        //gStyle->SetOptTitle(0);
        gStyle->SetOptStat(0);
        // Upper plot will be in pad1
        TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
        pad1->SetBottomMargin(0); // Upper and lower plot are joined
        pad1->SetGridx();      // Vertical grid
        pad1->Draw();          // Draw the upper pad: pad1
        pad1->cd();            // pad1 becomes the current pad
        gStyle->SetOptTitle(0);
        hmc_sgn[k]->SetTitle(varname); hmc_sgn2[k]->SetTitle(varname);

        //Normalizzazione MC preE
        Double_t normMC = hmc_sgn[k]->GetEntries();
        //Normalizing Monte Carlo
        Double_t wNorm = lumi_preE*xsection_mc_preE*BR/N_MC;
        //Double_t wNorm = lumi*xsection_mc*BR/N_MC  *  n_mc_peak/hmc_sgn[k]->GetEntries();
        cout<<"wNorm * BR = "<<wNorm<<endl;
        hmc_sgn[k]->Scale(wNorm);

        //Normalizzazione MC postE
        Double_t normMC2 = hmc_sgn2[k]->GetEntries();
        //Normalizing Monte Carlo
        Double_t wNorm2 = lumi_postE*xsection_mc_postE*BR/N_MC;
        //Double_t wNorm = lumi*xsection_mc*BR/N_MC  *  n_mc_peak/hmc_sgn[k]->GetEntries();
        cout<<"wNorm * BR = "<<wNorm2<<endl;
        hmc_sgn2[k]->Scale(wNorm2);
        
        //Unisco i due MC
        hmc_sgn[k]->Add(hmc_sgn2[k]);
        //scaling the SB distribution to number of background events in 1.93,2.01
        Double_t normSB = hdata_bkg[k]->GetEntries();
        
        ifstream fin("Inv_mass_plot/some_fit_results.txt");
        TString var="";
        fin>>var;
        float fsigregion_bkg_val = var.Atof();
        TString var2="";
        fin>>var2;
        float nbkg_val = var2.Atof();
        fin.close();
        
        hdata_bkg[k]->Scale(fsigregion_bkg_val*nbkg_val/normSB);

        cout<<"Entries in  hdata_sgn[k] before SB subtraction "<<hdata_sgn[k]->GetEntries()<<endl;
        hdata_sgn[k]->Add(hdata_bkg[k],-1); //subtract h2 from h1 : h1->Add(h2,-1)

        //rebinning
        //hmc_sgn[k]->Rebin(2);
        //hdata_sgn[k]->Rebin(2);

        //rescaling
        hdata_sgn[k]->Scale( hmc_sgn[k]->Integral()/hdata_sgn[k]->Integral() );

        cout<<"Entries in  hdata_sgn[k] after SB subtraction "<<hdata_sgn[k]->GetEntries()<<endl;
        cout<<"Entries in  hmc_sgn[k] after rescaling "<<hmc_sgn[k]->GetEntries()<<endl;
        //plot makeup
        double Y_max = std::max(hmc_sgn[k]->GetMaximum(), hdata_sgn[k]->GetMaximum());
        Y_max = Y_max*1.05;
        hmc_sgn[k]->GetYaxis()->SetRangeUser(0, Y_max);

        hmc_sgn[k]->GetYaxis()->SetTitle("a.u.");
        hmc_sgn[k]->GetYaxis()->SetTitleSize(22);
        hmc_sgn[k]->GetYaxis()->SetTitleFont(43);
        hmc_sgn[k]->GetYaxis()->SetTitleOffset(1.25);

        hmc_sgn[k]->SetLineColor(kBlue);
        hmc_sgn[k]->SetLineWidth(3);
        hmc_sgn[k]->SetFillStyle(3004);
        hmc_sgn[k]->SetFillColor(kBlue);
        hdata_sgn[k]->SetLineColor(kRed);
        hdata_sgn[k]->SetLineWidth(3);
        hdata_sgn[k]->SetFillStyle(3005);
        hdata_sgn[k]->SetFillColor(kRed);


        hmc_sgn[k]->Draw("hist");
        hdata_sgn[k]->Draw("hist same");

        hmc_sgn[k]->SetStats(0);
        Double_t x_leg_left  = 0.55;
        Double_t x_leg_right = 0.90;
        Double_t y_leg_left  = 0.63;
        Double_t y_leg_right = 0.90;
        if(varname=="segmComp") { x_leg_left = 0.1; x_leg_right = 0.45; }
        TLegend*leg = new TLegend(x_leg_left,y_leg_left,x_leg_right,y_leg_right);
        leg->AddEntry(hmc_sgn[k],"MC DsPhiPi","f");
        leg->AddEntry(hdata_sgn[k],"data (SB subtracted)","f");
        leg->Draw();

        // lower plot will be in pad2
        c2->cd();          // Go back to the main canvas before defining pad2
        TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        pad2->SetTopMargin(0);
        pad2->SetBottomMargin(0.2);
        pad2->SetGridx(); // vertical grid
        pad2->Draw();
        pad2->cd();       // pad2 becomes the current pad
        // Define the ratio plot
        TH1F *h_x_ratio = (TH1F*)hdata_sgn[k]->Clone("h_x_ratio");
        h_x_ratio->Sumw2();
        h_x_ratio->Divide(hmc_sgn[k]);
        h_x_ratio->SetStats(0);
        // Ratio plot settings
        gStyle->SetLineWidth(2);
        h_x_ratio->SetTitle(""); // Remove the ratio title
        h_x_ratio->GetYaxis()->SetTitle("ratio data/MC");
        h_x_ratio->GetYaxis()->SetRangeUser(-0.5,2);
        if(varname=="pv_sv_dxy/pv_sv_dxy_sig") h_x_ratio->GetXaxis()->SetTitle("Error on PV-SV distance on transverse plane (cm)");
        h_x_ratio->SetLineColor(kBlack);
        h_x_ratio->GetYaxis()->SetTitleSize(22);
        h_x_ratio->GetYaxis()->SetTitleFont(43);
        h_x_ratio->GetYaxis()->SetTitleOffset(1.25);
        h_x_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
        h_x_ratio->GetYaxis()->SetLabelSize(15);
     
        // X axis ratio plot settings
        h_x_ratio->GetXaxis()->SetTitle(varname);
        h_x_ratio->GetXaxis()->SetTitleSize(22);
        h_x_ratio->GetXaxis()->SetTitleFont(43);
        h_x_ratio->GetXaxis()->SetTitleOffset(2.0);
        h_x_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
        h_x_ratio->GetXaxis()->SetLabelSize(15);
        //Compute weighted average ratio
        Double_t mean = 0;
        Double_t std_dev = 0;
        for (int c=1; c<=(h_x_ratio->GetNbinsX()); c++)
        {
            if(h_x_ratio->GetBinContent(c) == 0 || h_x_ratio->GetBinError(c) == 0) continue;
            //cout<<c<<" "<<h_x_ratio->GetBinContent(c)<<" +- "<<h_x_ratio->GetBinError(c)<<endl;
            mean = mean + h_x_ratio->GetBinContent(c) / ( h_x_ratio->GetBinError(c) * h_x_ratio->GetBinError(c) );
            std_dev = std_dev + 1/( h_x_ratio->GetBinError(c) * h_x_ratio->GetBinError(c));
        }
        mean = mean/std_dev;
        std_dev = 1/std_dev;
        //Get mean value and error of ratio plot
        //cout<<var[k]+" Mean: "<<mean<<endl;
        //cout<<var[k]+" StdDev: "<<std_dev<<endl;
        //Draw line corresponding to mean value on ratio plot
        TLine l;
        h_x_ratio->Draw("ep");
        l.DrawLine(0,mean,h_x_ratio->GetXaxis()->GetXmax(),mean);
        h_x_ratio->Draw("same");
        c2->cd();
        c2->Update();
        if(varname=="pv_sv_dxy/pv_sv_dxy_sig") varname = "dxy_err";
        c2->SaveAs("control_plots/"+varname+"_.png");
        //c2->SaveAs("plots/"+varname+"_"+run_lable+".pdf");
    }
    
}
