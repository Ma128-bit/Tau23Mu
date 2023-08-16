#include<fstream>
void Fit_each_era(TString [], TString [], TString);
void Fit(TChain *, float [], unsigned int [], TString, TString);

using namespace RooFit;
void Control_inv_mass(){
    ofstream fout("Inv_mass_plot/yield.txt");
    fout<<"Yealds_for_different_2022_era:\n";
    ofstream fout2("Inv_mass_plot/some_fit_results.txt");
    fout.close();
    fout2.close();
    TString name[5]={"C","D","E","F", "G"};
    TString lumi[5]={"0.25", "0.147", "0.29", "0.887", "0.153"};
    TString lumi_tot="1.727";
    Fit_each_era(name, lumi, lumi_tot);
}
void Fit(TChain *ch, float par[], unsigned int yield[], TString lumi,TString era="all"){
    TString common_cut =
                         " Ptmu3 > 1.2 && "
                         "((Ptmu1>3.5 && Etamu1<1.2) || (Ptmu1>2.0 && Etamu1>=1.2 && Etamu1<=2.4)) && "
                         "((Ptmu2>3.5 && Etamu2<1.2) || (Ptmu2>2.0 && Etamu2>=1.2 && Etamu2<=2.4)) ";
    ofstream fout("Inv_mass_plot/yield.txt",ios::app);
    cout<<"Total entries era "<<era<<" = "<<ch->GetEntries()<<endl;
    TH1F *h_data;
    ch->Draw("tripletMass>>h_data(65, 1.65, 2.05)",common_cut,"N");
    h_data = (TH1F *)gDirectory->Get("h_data");
    Double_t xMin = h_data->GetXaxis()->GetXmin();
    Double_t xMax = h_data->GetXaxis()->GetXmax();
    Int_t nBins = h_data->GetNbinsX();
    RooRealVar x("x", "x", xMin, xMax);
    x.setBins(nBins);
    RooDataHist* data = new RooDataHist("data", h_data->GetTitle(), RooArgSet(x), Import(*h_data,kFALSE));
    
    float sig1_d=0;
    float sig1_u=0;
    float mGCB_u=0;
    if (era!="G"){
       sig1_d=0.001;
    }
    if (era=="G"){
       sig1_d=0.01;
    }
    sig1_u=0.1;

    //Variabili
    RooRealVar meanCB("meanCB", "meanCB", 1.966, 1.965, 1.968);
    RooRealVar sigmaCB("#sigma_{CB}", "sigmaCB", 0.02, 0.001, 0.1);
    RooRealVar alpha("#alpha","alpha",par[0], 0.5, 10.); //nSigma
    RooRealVar nSigma("n1","n1", par[1], 0.1, 25.); //Esponente
    RooRealVar gamm1("#gamma1", "gamma1", 0.02, 0.001, 0.1);
    
    RooRealVar sigmaG("#sigma_{G}","sigmaG", 0.02, 0.001, 0.1);

    RooCBShape sig_CB("sig_{CB}","sig_CB",x,meanCB,sigmaCB,alpha,nSigma);
    
    RooGaussian sig_G("sig_{G}","sig_G",x,meanCB,sigmaG);
    
    RooRealVar mean2("mean2", "mean2", 1.87, 1.85, 1.90);
    RooRealVar sigma2("#sigma2", "sigma2", 0.03, 0.001, 0.1);
    //RooRealVar alpha2("#alpha2","alpha2",par[2], 0.5, 5.);
    //RooRealVar nSigma2("n2","n2", par[3], 1., 5.);
    //RooCBShape sig_2("sig_2","sig_2",x,mean2,sigma2,alpha2,nSigma2);
    RooGaussian sig_2("sig_2","sig_2",x,mean2,sigma2);
    
    RooRealVar gamma("#Gamma","Gamma",-1, -2., -1e-2) ;
    RooExponential bkgExp("bkgExpPdf","bkgExpPdf",x, gamma);

    RooRealVar nSig_CB("nSig_CB", "Number of signal candidates CB", (int)(8*yield[0]/11), 1., 1e+6);
    RooRealVar nSig_G("nSig_G", "Number of signal candidates G", (int)(3*yield[0]/11), 1., 1e+6);
    RooRealVar nSig2("nSig2", "Number of signal 2 candidates ", yield[1], 1., 1e+6);
    RooRealVar nBkg("nBkg", "Bkg component", yield[2], 1., 1e+6);
    
    //Unisco le pdf:
    RooAddPdf* totalPDF = new RooAddPdf("totalPDF", "totalPDF", RooArgList(sig_CB, sig_G, sig_2, bkgExp), RooArgList(nSig_CB, nSig_G, nSig2, nBkg));
    
    //Fit:
    RooFitResult * r =  totalPDF->fitTo(*data, Extended(kTRUE),Save(true));
    
    RooPlot* xframe = x.frame(); //definisco frame
    xframe->SetTitle("");
    xframe->SetXTitle("2mu +1trk inv. mass (GeV)");
    //totalPDF->paramOn(xframe, Parameters(RooArgSet(nSig, nSig2, nBkg, alpha, nSigma)), Layout(0.6,0.9,0.9));
    data->plotOn(xframe); //plotto i dati
    totalPDF->plotOn(xframe, Components(RooArgSet(sig_CB, sig_G, sig_2)), LineColor(kRed), LineStyle(kDashed));
    totalPDF->plotOn(xframe, Components(RooArgSet(bkgExp)), LineColor(kGreen), LineStyle(kDashed) );
    totalPDF->plotOn(xframe);
    
    
    TCanvas *c1=new TCanvas("c1","c1",900,900);
    c1->Divide(1,2);
    //plotto oltre al fit anche le pull:
    RooPlot *xframePull =x.frame(); //creo un nuovo frame
    xframePull->SetTitle("Pulls bin-by-bin");
    xframePull->SetXTitle("2mu +1trk inv. mass (GeV)");
    xframePull->SetYTitle("Pulls");
    xframePull->addObject((TObject*)xframe->pullHist(),"p");
    xframePull->SetMinimum(-4);
    xframePull->SetMaximum(4);
    c1->cd(2); //Qui disegno le pull
    gPad->SetPad(0.,0.,1.,0.3);
    xframePull->Draw();
    TLine *line = new TLine(xMin,0.,xMax,0.);
    line->SetLineColor(2);
    line->Draw("same");
    c1->cd(1); //qui il grafico con il fit
    gPad->SetPad(0.,0.3,1.,1.);
    xframe->Draw();
    TLatex* text = new TLatex(0.62,0.91, "Data era "+era+"            L = "+lumi+"fb^{-1}");
    text->SetNDC(kTRUE);
    text->SetTextSize(0.032);
    text->SetTextFont(42);
    text->Draw("same");
    TLatex* text2 = new TLatex(0.15,0.81, "#bf{CMS Preliminary}");
    text2->SetNDC(kTRUE);
    text2->SetTextSize(0.032);
    text2->SetTextFont(42);
    text2->Draw("same");
    
    //Integrale
    x.setRange("signal",1.93,2.01);
    RooAbsReal* sig_int_CB = sig_CB.createIntegral(x,NormSet(x),Range("signal"));
    RooAbsReal* sig_int_G = sig_G.createIntegral(x,NormSet(x),Range("signal"));
    RooAbsReal* sig_int2 = sig_2.createIntegral(x,NormSet(x),Range("signal"));
    RooAbsReal* fsigregion_bkg = bkgExp.createIntegral(x,NormSet(x),Range("signal"));
    
    float ysig=sig_int2->getVal()*nSig2.getVal() +sig_int_CB->getVal()*nSig_CB.getVal() + sig_int_G->getVal()*nSig_G.getVal();
    
    float ysig_e2 = pow(sig_int2->getPropagatedError(*r) * nSig2.getVal(),2)+pow(sig_int2->getVal() * nSig2.getError(),2)+pow(sig_int_CB->getPropagatedError(*r) * nSig_CB.getVal(),2)+pow(sig_int_CB->getVal() * nSig_CB.getError(),2) +pow(sig_int_G->getPropagatedError(*r) * nSig_G.getVal(),2)+pow(sig_int_G->getVal() * nSig_G.getError(),2);

    float ysig_e =TMath::Sqrt(ysig_e2);
    TString print= ""; print.Form("_= %.2f +- %.2f",ysig, ysig_e);
    //TString print= ""; print.Form("_= %.2f +- %.2f",nSig.getVal(), nSig.getError());
    print = "Signal_events_in_era_"+era +print;
    fout<<print<<"\n";
    fout.close();
    
    //Chi2
    RooChi2Var chi2("chi2","chi2",*totalPDF,*data);
    cout << "chi2.getVal() " << chi2.getVal() << endl ;
    int ndof=nBins-7;
    TString chi=""; chi.Form("#chi^{2}/NDOF = %.2f",chi2.getVal()/ndof);
    TLatex* text3 = new TLatex(0.15,0.77, chi);
    text3->SetNDC(kTRUE);
    text3->SetTextSize(0.032);
    text3->SetTextFont(42);
    text3->Draw("same");
    
    if(era=="all"){
        ofstream fout2("Inv_mass_plot/some_fit_results.txt",ios::app);
        fout2<<fsigregion_bkg->getVal()<<" "<<nBkg.getVal();
        fout2.close();
    }
    
    c1->SaveAs("Inv_mass_plot/inv_mass_"+era+".png");
    c1->Clear();
    delete c1;

}
void Fit_each_era(TString name[], TString lumi[], TString lumi_tot){
    unsigned int y[5][3]={{1500,300,21000},{1000,250,9000},{2000,650,20000},{7500,1800,60000},{800,180,10000}};
    float par[2]={1.,1.};
    TChain *ch_tot = new TChain("FinalTree");
    for(int i=0; i<5; i++){
	//if(i==0) {par[1]=2.; par[0]=2.;}
	//else {par[1]=1.; par[0]=1.;}
        TChain *ch1 = new TChain("FinalTree");
        for(int j=0;j<8;j++){
            TString num;
            num.Form("%d",j);
            ch1->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022"+name[i]+"_"+num+"_control_ReReco/AnalysedTree_data_control_2022"+name[i]+"_"+num+"_control_merged_ReReco.root");
            //if(i==1) ch1->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022D-v1_"+num+"_control_test/AnalysedTree_data_control_2022D-v1_"+num+"_control_merged_test.root");
            ch_tot->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022"+name[i]+"_"+num+"_control_ReReco/AnalysedTree_data_control_2022"+name[i]+"_"+num+"_control_merged_ReReco.root");
            //if(i==1) ch_tot->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022D-v1_"+num+"_control_test/AnalysedTree_data_control_2022D-v1_"+num+"_control_merged_test.root");
        }
        Fit(ch1,par,y[i],lumi[i],name[i]);
        delete ch1;
    }
    unsigned int yy[3]={12500,3080,112000};
    Fit(ch_tot,par,yy,lumi_tot,"all");
    //Fit(ch_tot,par,yy,"1.33","all");
}
