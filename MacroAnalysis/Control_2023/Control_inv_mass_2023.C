#include<fstream>
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooArgusBG.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "TH1F.h"
#include <cmath>
#include <iomanip>
#include <sstream>

void Fit(TChain *ch, std::vector<float> &par, unsigned int yield[], TString lumi,TString era="all");

using namespace RooFit;

void Control_inv_mass_2023(){
    ofstream fout("Inv_mass_plot/yield.txt");
    fout << "Yealds_for_different_2022_era:\n";
    ofstream fout2("Inv_mass_plot/some_fit_results.txt");
    fout.close();
    fout2.close();
    TString name[7] = {"B", "C-v1", "C-v2", "C-v3", "C-v4", "D-v1", "D-v2"};
    TString lumi[7] = {"0.030", "0.215", "0.063", "0.078", "0.486", "0.381", "0.081"};
    TString lumi_tot = "1.333";
    
    unsigned int y[7][3] = {{150, 50, 3600}, {3000, 1000, 24000}, {700, 200, 4500}, {8500, 1800, 60000}, {7500, 1800, 60000}, {1000, 250, 9000}, {800, 150, 6000}};
    std::vector<float> par = {1., 1.};
    
    TChain *ch_tot = new TChain("FinalTree");
    for (int i = 0; i < 7; i++) {
        ch_tot->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_13_0_10/src/Analysis/JobAdd_perEra/Era_" + name[i] + "_control.root");
    }
    unsigned int yy[3]={10000,2200,130000};
    Fit(ch_tot,par,yy,lumi_tot,"all");
    
    //for (int i = 0; i < 7; i++) {
    for (int i = 0; i < 7; i++) {
        TChain *ch1 = new TChain("FinalTree");
        ch1->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_13_0_10/src/Analysis/JobAdd_perEra/Era_" + name[i] + "_control.root");
        Fit(ch1,par,y[i],lumi[i],name[i]);
        delete ch1;
    }
    
    delete ch_tot;
}

void Fit(TChain *ch, std::vector<float> &par, unsigned int yield[], TString lumi,TString era="all"){
    
    ofstream fout("Inv_mass_plot/yield.txt",ios::app);
    
    cout<<"Total entries era "<<era<<" = "<<ch->GetEntries()<<endl;
    
    TString invmass_SB = "(puFactor*(tripletMass<1.80 && tripletMass>1.70))";
    TString invmass_peak = "(puFactor*(tripletMass<2.01 && tripletMass>1.93))";
    TString binning_mass = "(65, 1.65, 2.05)";
    if(era=="B") binning_mass = "(30, 1.65, 2.05)";
    if(era=="C-v2") binning_mass = "(30, 1.65, 2.05)";
    
    
    TString selez="(Ptmu3 > 1.2 && ((Ptmu1>3.5 && Etamu1<1.2) || (Ptmu1>2.0 && Etamu1>=1.2 && Etamu1<=2.4)) && ((Ptmu2>3.5 && Etamu2<1.2) || (Ptmu2>2.0 && Etamu2>=1.2 && Etamu2<=2.4)))";
    
    TH1F *h_tripletmass;
    TH1F *h_tripletmass_sign;
    TH1F *h_tripletmass_bkg;
    
    ch->Draw("tripletMass>>h_tripletmass"+binning_mass,selez);
    ch->Draw("tripletMass>>h_tripletmass_bkg"+binning_mass, invmass_SB+"&&"+selez);
    ch->Draw("tripletMass>>h_tripletmass_sign"+binning_mass, invmass_peak+"&&"+selez);
    
    //ch->Draw("tripletMass>>h_data(65, 1.65, 2.05)","","N");
    //h_data = (TH1F *)gDirectory->Get("h_data");
    h_tripletmass     = (TH1F *)gDirectory->Get("h_tripletmass");
    h_tripletmass_bkg = (TH1F *)gDirectory->Get("h_tripletmass_bkg");
    h_tripletmass_sign = (TH1F *)gDirectory->Get("h_tripletmass_sign");
    
    //Double_t xMin = h_data->GetXaxis()->GetXmin();
    //Double_t xMax = h_data->GetXaxis()->GetXmax();
    //Int_t nBins = h_data->GetNbinsX();
    
    RooRealVar x("x","2mu+1trk inv. mass (GeV)",1.65,2.05);
    //RooRealVar x("x", "x", xMin, xMax);
    int nBins=65;
    if(era=="B") nBins=30;
    if(era=="C-v2") nBins=30;
    x.setBins(nBins);
    RooDataHist* data = new RooDataHist("data", h_tripletmass->GetTitle(), RooArgSet(x), Import(*h_tripletmass,kFALSE));
    
    //set ranges
    x.setRange("R1",1.83,1.89); //first peak D+(1.87GeV)
    x.setRange("R2",1.93,2.02); //second peak Ds(1.97)
    x.setRange("R3",1.65,1.84); //background
    x.setRange("R4",1.89,1.925); //background
    x.setRange("R5",1.99,2.02); //background
    x.setRange("R6",1.65,2.02); //full range
    
    //Variabili
    RooRealVar mGCB("mean", "meanCB", 1.97, 1.95, 2.0);
    RooRealVar sigma1CB("#sigma_{CB}", "sigma1CB", 0.02, 0.001, 0.1);
    RooRealVar alpha("#alpha","alpha",par[0], 0.5, 10.); //nSigma
    RooRealVar nSigma("n1","n1", par[1], 0.1, 25.); //Esponente
    
    RooCBShape sigCBPdf("sigCBPdf","sigCBPdf",x,mGCB,sigma1CB,alpha,nSigma);
    
    //RooRealVar gamm1("#gamma1", "gamm1", 0.02, 0.001, 0.1);
    //RooBreitWigner sigCBPdf("sigCBPdf","sigCBPdf",x,mGCB,sigma1CB);
    //RooVoigtian sigCBPdf("sigCBPdf","sigCBPdf",x,mGCB,gamm1,sigma1CB);

    sigCBPdf.fitTo(*data, Range("R2"));
    

    RooRealVar mGCB2("mean2", "meanCB2", 1.87, 1.85, 1.90);
    RooRealVar sigma2CB("#sigma2_{CB}", "sigma2CB", 0.03, 0.001, 0.1);
    //RooRealVar alpha2("#alpha2","alpha2",par[2], 0.5, 5.);
    //RooRealVar nSigma2("n2","n2", par[3], 1., 5.);
    //RooCBShape sig2CBPdf("sig2CBPdf","sig2CBPdf",x,mGCB2,sigma2CB,alpha2,nSigma2);
    RooGaussian sig2CBPdf("sig2CBPdf","sig2CBPdf",x,mGCB2,sigma2CB);
    sig2CBPdf.fitTo(*data, Range("R1"));
    
    RooRealVar gamma("#Gamma","Gamma",-1, -2., -1e-2) ;
    RooExponential bkgExpPdf("bkgExpPdf","bkgExpPdf",x, gamma);
    bkgExpPdf.fitTo(*data, Range("R3,R4,R5"));
    
    RooRealVar nSig2("nSig", "Number of signal candidates ", yield[0], 1., 1e+6);
    RooRealVar nSig1("nSig2", "Number of signal 2 candidates ", yield[1], 1., 1e+6);
    RooRealVar nBkg("nBkg", "Bkg component", yield[2], 1., 1e+6);
    
    //Unisco le pdf:
    RooAddPdf* totalPDF = new RooAddPdf("totalPDF", "totalPDF", RooArgList(sigCBPdf, sig2CBPdf, bkgExpPdf), RooArgList(nSig2, nSig1, nBkg));
    
    //Fit:
    RooFitResult * r =  totalPDF->fitTo(*data, Extended(kTRUE),Save(true));
    
    RooPlot* xframe = x.frame(); //definisco frame
    xframe->SetTitle("");
    xframe->SetXTitle("2mu +1trk inv. mass (GeV)");
    //totalPDF->paramOn(xframe, Parameters(RooArgSet(alpha,nSigma,nSig1,nSig2,nBkg )), Layout(0.6,0.9,0.9));
    data->plotOn(xframe); //plotto i dati
    totalPDF->plotOn(xframe, Components(RooArgSet(sigCBPdf, sig2CBPdf)), LineColor(kRed), LineStyle(kDashed));
    totalPDF->plotOn(xframe, Components(RooArgSet(bkgExpPdf)), LineColor(kGreen), LineStyle(kDashed) );
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
    //TLine *line = new TLine(xMin,0.,xMax,0.);
    //line->SetLineColor(2);
    //line->Draw("same");
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
    x.setRange("sideband",1.7,1.8);
    
    //fraction of total events in 1.93,2.01 (n_signal_region_events/n_total_events)
    RooAbsReal* fsigregion_model = totalPDF->createIntegral(x,NormSet(x),Range("signal"));
    Double_t fs = fsigregion_model->getVal();
    Double_t fs_err = fsigregion_model->getPropagatedError(*r);
    //fraction of total events in 1.70,1.80 (n_sideband_region_events/n_total_events)
    RooAbsReal* fsidebandregion_model = totalPDF->createIntegral(x,NormSet(x),Range("sideband"));

    //fraction of background events in 1.93,2.01
    RooAbsReal* fsigregion_bkg = bkgExpPdf.createIntegral(x,NormSet(x),Range("signal"));
    Double_t fb = fsigregion_bkg->getVal();
    Double_t fb_err = fsigregion_bkg->getPropagatedError(*r);
    //fraction of background events in 1.70, 1.80
    RooAbsReal* fsidebandregion_bkg = bkgExpPdf.createIntegral(x,NormSet(x),Range("sideband"));


    Double_t nsigevents = fs * (nSig2.getVal()+nSig1.getVal()+nBkg.getVal()) - fb*nBkg.getVal();
    Double_t nsig_err = pow( pow(fs_err,2) * pow(nSig2.getVal()+nSig1.getVal()+nBkg.getVal(),2)  + ( pow(nSig2.getPropagatedError(*r),2)+pow(nSig1.getPropagatedError(*r),2)+pow(nBkg.getPropagatedError(*r),2)) * pow(fs,2) + pow(fb_err,2) * pow(nBkg.getVal(),2) + pow(nBkg.getPropagatedError(*r),2)*pow(fb,2) , 0.5);

    Double_t fsig = nsigevents/(fsigregion_model->getVal()*(nSig2.getVal()+nSig1.getVal()+nBkg.getVal()));
    
    
    TString print= ""; print.Form("_= %.2f +- %.2f",nsigevents, nsig_err);
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
