#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
#include "TFile.h"
using namespace RooFit;
void omega_cuts() {
  // Open the file containing the histogram
  TFile *file = new TFile("/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/MacroAnalysis/New_Ntuple/All_Data.root");
  
  // Retrieve the histogram from the file
  TTree *t = (TTree*)file->Get("FinalTree");
  t->Draw("dimu_OS1>>histo(50,0.72,0.84)","isMC==0 && category==2");
  
  TH1F *histo;
  histo = (TH1F *)gDirectory->Get("histo");

  // Create a RooRealVar for the observable
  RooRealVar x("x", "x", histo->GetXaxis()->GetXmin(), histo->GetXaxis()->GetXmax());
  
  // Create a RooDataHist from the histogram
  RooDataHist data("data", "data2", x, Import(*histo));
  
  // Create the Gaussian PDF
  RooRealVar mean("mean", "mean", 0.782);
  RooRealVar sigma("sigma", "sigma", 0.02, 0.001, 0.1);
  RooGaussian gauss("gauss", "gauss", x, mean, sigma);
  
  // Create the exponential PDF
  RooRealVar lambda2("lambda2", "lambda2", -0.1, -5., 0.);
  RooExponential expo("expo", "expo", x, lambda2);
  
  // Create the composite model
  RooRealVar frac("frac", "frac", 0.5, 0.0, 1.0);
  RooAddPdf model("model", "model", RooArgList(gauss, expo), frac);
  
  // Fit the model to the data
  model.fitTo(data);
  TCanvas *c = new TCanvas();
  
  RooPlot *frame = x.frame();
  data.plotOn(frame);
  model.plotOn(frame);
  model.paramOn(frame, Parameters(RooArgSet(mean,sigma)), Layout(0.52,0.99,0.9));
  frame->Draw();
}
