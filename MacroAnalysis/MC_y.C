#include<fstream>
using namespace RooFit;
void MC_y(){
    //MC ALL
    TChain *tmc = new TChain("FinalTree");
    tmc->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/DsPhiPi_preE_tau3mu_test/AnalysedTree_MC_DsPhiPi_preE_tau3mu0.root");
    //tmc_2->Add("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/DsPhiPi_postE_tau3mu_test/AnalysedTree_MC_DsPhiPi_postE_tau3mu0.root");
    TH1F *h_MC;
    tmc->Draw("tripletMass>>h_MC(42, 1.65, 2.05)","","N");
    h_MC = (TH1F *)gDirectory->Get("h_MC");
    Double_t xMin = h_MC->GetXaxis()->GetXmin();
    Double_t xMax = h_MC->GetXaxis()->GetXmax();
    Int_t nBins = h_MC->GetNbinsX();
    RooRealVar x("x", "x", xMin, xMax);
    x.setBins(nBins);
    RooDataHist* data = new RooDataHist("data", h_MC->GetTitle(), RooArgSet(x), Import(*h_MC,kFALSE));
    RooRealVar mGCB("mean", "meanCB", 1.97, 1.95, 2.0);
    RooRealVar sigma1CB("#sigma_{CB}", "sigma1CB", 0.02, 0.001, 0.1);
    RooGaussian sig2CBPdf("sig2CBPdf","sig2CBPdf",x,mGCB,sigma1CB);
    RooRealVar nSig("nSig", "Number of signal candidates ", 1., 1e+6);
    
    //Fondo:
    RooRealVar d1("d_{1}", "d1", -0.1 ,-10, 10);
    RooRealVar d2("d_{2}", "d2", -0.1 ,-10, 10);
    RooChebychev bkgPDF("bkgPDF", "bkgPDF", x, RooArgSet(d1,d2));
    RooRealVar nBkg("nBkg", "Bkg component",1., 1e+6);
    
    RooAddPdf* totalPDF = new RooAddPdf("totalPDF", "totalPDF", RooArgList(sig2CBPdf,bkgPDF), RooArgList(nSig,nBkg));
    
    RooFitResult * r =  totalPDF->fitTo(*data, Extended(kTRUE),Save(true));
    RooPlot* xframe = x.frame(); //definisco frame
    xframe->SetTitle("");
    xframe->SetXTitle("2mu +1trk inv. mass (GeV)");
    //totalPDF->paramOn(xframe, Parameters(RooArgSet(alpha,nSigma,nSig,nSig2,nBkg )), Layout(0.6,0.9,0.9));
    data->plotOn(xframe);
    totalPDF->plotOn(xframe, Components(RooArgSet(sig2CBPdf)), LineColor(kRed));
    totalPDF->plotOn(xframe, Components(RooArgSet(bkgPDF)), LineColor(kGreen), LineStyle(kDashed) );

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
    
    //Integrale
    x.setRange("signal",1.93,2.01);
    RooAbsReal* sig_int = sig2CBPdf.createIntegral(x,NormSet(x),Range("signal"));
    cout<<sig_int->getVal()<<endl;
    float ysig=sig_int->getVal()*nSig.getVal();
    float ysig_e2 = pow(sig_int->getPropagatedError(*r) * nSig.getVal(),2)+pow(sig_int->getVal() * nSig.getError(),2);
    float ysig_e =TMath::Sqrt(ysig_e2);
    TString print= ""; print.Form("_= %.2f +- %.2f",ysig, ysig_e);
    print = "Signal_events_" +print;
    cout<<"Risultati: "<<print<<endl;
    
}
