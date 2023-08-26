
void Plot_yield_2023(){
    cout<<"Inizio"<<endl;
    ifstream fin("Inv_mass_plot/yield.txt");
    TString name[7] = {"B", "C-v1", "C-v2", "C-v3", "C-v4", "D-v1", "D-v2"};
    TString lumi[7] = {"0.030", "0.215", "0.063", "0.078", "0.486", "0.381", "0.081"};
    TString lumi_tot = "1.333";
    TString s;
    fin>>s;
    cout<<"Inizo loop...";
    TH1F *g= new TH1F("","",7, 0, 7);
    for (int i=0; i<7;i++){
        fin>>s;
        TString val=""; fin>>val;
        float val1 = val.Atof();
        fin>>s;
	cout<<".."<<i<<"..";
        TString err=""; fin>>err;
        float err1 = err.Atof();
        g->SetBinContent(i, val1/lumi[i].Atof());
	double error = sqrt(pow(err1/lumi[i].Atof(),2)+pow(val1*lumi[i].Atof()*10/(lumi[i].Atof()*lumi[i].Atof()*100),2)); 
        g->SetBinError(i, error);
    }
    cout<<"...Fine loop"<<endl;
    g->GetXaxis()->SetRangeUser(-1, 4);
    g->GetXaxis()->SetNdivisions(11);
    g->GetYaxis()->SetRangeUser(0, 11000);
    g->GetXaxis()->SetTitle("2022 Era");
    g->GetYaxis()->SetTitle("Ds Yield/fb^{-1}");
    g->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"C");
    g->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"D");
    g->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"E");
    g->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(8,-1,-1,-1,-1,-1,"F");
    g->GetXaxis()->ChangeLabel(9,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(10,-1,-1,-1,-1,-1,"G");
    g->GetXaxis()->ChangeLabel(11,-1,-1,-1,-1,-1," ");
    TCanvas *c=new TCanvas("c","c",1200,800);
    c->cd();
    g->SetTitle("Yield per Era");
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kBlue);
    g->SetLineColor(kBlue);
    g->SetMarkerSize(1.2);
    
    g->Draw();
    c->SaveAs("Inv_mass_plot/plot_yield.png");
    fin.close();
}

