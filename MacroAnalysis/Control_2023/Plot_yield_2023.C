
void Plot_yield_2023(){
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(1);

    cout<<"Inizio"<<endl;
    TString name[7] = {"B", "C-v1", "C-v2", "C-v3", "C-v4", "D-v1", "D-v2"};
    double lumi[7] = {0.030, 0.215, 0.063, 0.078, 0.486, 0.381, 0.081};
    TString lumi_tot = "1.333";

    std::ifstream inputFile("Inv_mass_plot/yield.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Impossibile aprire il file." << std::endl;
    }

    // Ignora le prime due righe
    std::string line;
    std::getline(inputFile, line);
    std::getline(inputFile, line);
    cout<<"Inizo loop...";
    TH1F *g= new TH1F("Yield per era","Yield per era",7, 0, 7);
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
    g->GetXaxis()->SetRangeUser(-1, 6);
    g->GetXaxis()->SetNdivisions(15);
    g->GetYaxis()->SetRangeUser(0, 10000);
    g->GetXaxis()->SetTitle("2023 Era");
    g->GetYaxis()->SetTitle("Ds Yield/fb^{-1}");
    g->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"B");
    g->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"C-v1");
    g->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"C-v2");
    g->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(8,-1,-1,-1,-1,-1,"C-v3");
    g->GetXaxis()->ChangeLabel(9,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(10,-1,-1,-1,-1,-1,"C-v4");
    g->GetXaxis()->ChangeLabel(11,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(12,-1,-1,-1,-1,-1,"D-v1");
    g->GetXaxis()->ChangeLabel(13,-1,-1,-1,-1,-1," ");
    g->GetXaxis()->ChangeLabel(14,-1,-1,-1,-1,-1,"D-v2");
    g->GetXaxis()->ChangeLabel(15,-1,-1,-1,-1,-1," ");

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

