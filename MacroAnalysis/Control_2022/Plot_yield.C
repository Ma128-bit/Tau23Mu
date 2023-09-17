
void Plot_yield(){
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(1);

    cout<<"Inizio"<<endl;
    TString name[5]={"C","D","E","F", "G"};
    double lumi[5]={0.25, 0.147, 0.29, 0.887, 0.153};
    //double lumi[5]={0.22, 0.14, 0.29, 0.8", 0.13};

    std::ifstream inputFile("Inv_mass_plot/yield.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Impossibile aprire il file." << std::endl;
    }

    // Ignora le prime due righe
    std::string line;
    std::getline(inputFile, line);
    std::getline(inputFile, line);
    cout<<"Inizo loop...";

    TH1F *g= new TH1F("","",5, 0, 5);
    int i=0;    
    while (std::getline(inputFile, line)) {
        char c1,c2;
        std::string identifier;
        double value;
        double error;
        std::istringstream iss(line);
        iss >> identifier  >> value >> c1 >> c2 >> error;
        cout<<identifier<<value<<c1<<c2<<error<<endl;
	cout<<value<<" "<<error<<endl;
	//cout<<".."<<i<<"..";
        g->SetBinContent(i, value/lumi[i]);
        double error2 = error/lumi[i];
	//double error2 = sqrt(pow(error/lumi[i],2)+pow(value*lumi[i]*10/(lumi[i]*lumi[i]*100),2));
        g->SetBinError(i, error2);
	i++;
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
    g->Fit("pol0");    
    g->Draw();
    c->SaveAs("Inv_mass_plot/plot_yield.png");
    inputFile.close();
}

