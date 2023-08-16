import os        
import sys       
import math
import string
import os.path
import array
import glob
import random
import array as ary
import numpy as np
from ROOT import *

if __name__=='__main__':

    # Opzioni di stile
    gStyle.SetOptFit(111)
    gStyle.SetOptStat(0)
    
    print("Opening files ...")
    # Dati pre E
    t1 = TChain("FinalTree")
    for i in ["C","D-v2"]:
        for j in range(8):
            name="/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022"+i+"_"+str(j)+"_tau3mu_test/AnalysedTree_data_2022"+i+"_"+str(j)+"_tau3mu_merged_test.root"
            t1.Add(name)
    # Dati post E
    t2 = TChain("FinalTree")
    for i in ["E","F", "G"]:
        for j in range(8):
            name="/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/2022"+i+"_"+str(j)+"_tau3mu_test/AnalysedTree_data_2022"+i+"_"+str(j)+"_tau3mu_merged_test.root"
            t2.Add(name)
    # MC pre E
    t3 = []
    # MC post E
    t4 = []
    index=0
    for i in ["B0","Bp", "Ds"]:
        t3.append(TChain("FinalTree"))
        name="/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/"+i+"_preE_tau3mu_test/AnalysedTree_MC_"+i+"_preE_tau3mu0.root"
        t3[index].Add(name)
        t4.append(TChain("FinalTree"))
        for j in range(2):
            name="/lustrehome/mbuonsante/Tau_3mu/CMSSW_12_4_11_patch3/src/Analysis/"+i+"_postE_tau3mu_test/AnalysedTree_MC_"+i+"_postE_tau3mu"+str(j)+".root"
            t4[index].Add(name)
        index +=1
    n3 = []
    n4 = []
    n1 = t1.GetEntries()
    n2 = t2.GetEntries()
    for i in range(3):
        n3.append(t3[i].GetEntries())
        n4.append(t4[i].GetEntries())
    
    #Print numero di entries
    print ("Total entries preE data = ", n1)
    print ("Total entries postE data = ", n2)
    index=0
    for i in ["B0","Bp", "Ds"]: #Ricorda B0= Bd e Bp =Bu
        print ("Total entries "+i+"_preE MC = ", n3[index])
        print ("Total entries "+i+"_postE MC = ", n4[index])
        index +=1
    
    # Cross Sections
    cs_preE = np.array([3.520, 3.508, 9.827]) #Ordine B0 Bp Ds
    cs_postE = np.array([3.525, 3.538, 9.815])
    
    #Fattori di scala
    f=1. #Fattore globale MC-Data
    sf_preE = np.ones(3)
    sf_postE = np.ones(3)
    for i in range(3):
        sf_preE[i] = cs_preE[i]/np.sum(cs_preE)
        sf_postE[i] = cs_postE[i]/np.sum(cs_postE)
    
    #Tutti i Tree Dati_preE, Dati_PostE, MC_preE (3) MC_postE
    titles = ["Dati_preE", "B0_preE", "Bp_preE", "Ds_preE","Dati_PostE", "B0_postE", "Bp_postE", "Ds_postE"]
    reso_range = ["reso<0.0065","0.0065<reso<0.0105","0.0105<reso<0.02"]
    mass_raneg = ["(tripletMass<1.753 || tripletMass>1.801)", "(tripletMass<1.739 || tripletMass>1.815)", "(tripletMass<1.727 || tripletMass>1.827)"]
    t = []
    t.append(t1)
    #Pre E
    for i in range(3):
        t.append(t3[i])
    t.append(t2)
    #Post E
    for i in range(3):
        t.append(t4[i])
    
    #Definizione histogrammi
    
    tripletMass1 = []
    tripletMass2 = []
    h0 = []
    h2 = []
    
    name=["fv_nC","fv_dphi3D","fv_d3Dsig","Ptmu3","cLP","tKink","segmComp","d0sig","d0sig_max","mindca_iso","trkRel"]
    #print("scegli fra:/n fv_nC, fv_dphi3D, fv_d3Dsig, Ptmu3, cLP, tKink, segmComp, d0sig, d0sig_max, mindca_iso, trkRel /n")
    #s = input()
    #name=[s]
    down=["0","0","0","1.5","0","2","0","0","0","0","0.00001"]
    up=["10","0.05","100","14","10","40","1","10","50","0.2","1.2"]
    rangelim=["0.07","0.05","0.1","0.075","0.04","0.045","0.06","0.085","0.08","0.08","0.05"]
    #print("Inserisci relativo indice: ")
    #indx=input()
    # Loop su tutti i plot
    ind = 0
    #ind=int(indx)
    for na in name:
        histo = []
        #Ottengo gli histo:
        cont=0
        for i in range(8):
            for j in range(3):
                title="histo"+"["+ str(cont) + "]"
                title1 = na+" "+titles[i]+" "+reso_range[j]
                histo.append(TH1F(title,title1,100,float(down[ind]),float(up[ind])))
                histname = na+">>"+title
                sel = "category=="+str(j)
                if (i==0 or i==4):
                    sel = sel+" && "+mass_raneg[j]
                t[i].Draw(histname, sel, "N")
                cont +=1
                
        #Dati_preE(range1,2,3)+B0_preE(range1,2,3)+ Bp_preE(range1,2,3)+ Ds_preE(range1,2,3)+Dati_postE(range1,2,3)+ B0_postE(range1,2,3) Bp_postE(range1,2,3) Ds_postE(range1,2,3)
        c=TCanvas("c","c",800,600)
        c.cd()
        #Pre E plots
        for i in range(3): #Lopp sui range di massa inv.
            if(ind==9 and i==0): rangelim[9]=0.15
            else: rangelim[9]=0.08
            st=THStack("st","")
            histo[3+i].Scale(sf_preE[0]*f/histo[3+i].Integral())
            histo[3+i].SetFillStyle(3244)
            histo[3+i].SetFillColor(kYellow+1)
            histo[3+i].SetLineColor(kYellow+1)
            #histo[3+i].GetYaxis().SetRangeUser(0,0.5);
            st.Add(histo[3+i])
            histo[6+i].Scale(sf_preE[1]*f/histo[6+i].Integral())
            histo[6+i].SetFillStyle(3244)
            histo[6+i].SetFillColor(kMagenta-4)
            histo[6+i].SetLineColor(kMagenta-4)
            st.Add(histo[6+i])
            histo[9+i].Scale(sf_preE[2]*f/histo[9+i].Integral())
            histo[9+i].SetFillStyle(3244)
            histo[9+i].SetFillColor(kCyan)
            histo[9+i].SetLineColor(kCyan)
            st.Add(histo[9+i])
            
            histo[0+i].SetFillStyle(3244)
            histo[0+i].SetFillColor(kGray)
            histo[0+i].SetLineColor(kGray)
            histo[0+i].Scale(1./histo[0+i].Integral())
            
            #Plot:
            histo[0+i].GetYaxis().SetRangeUser(0,float(rangelim[ind]))
            histo[0+i].SetTitle("Plot "+na+" in "+reso_range[i]+" preE")
            histo[0+i].GetXaxis().SetTitle(na)
            histo[0+i].GetYaxis().SetTitle("Entries")
            histo[0+i].DrawNormalized("histo")
            st.Draw("samehisto")
            #histo[0+i].DrawNormalized("samehisto")
            if(ind ==6):
                leg=TLegend(0.1,0.65,0.45,0.9);
            else:
                leg=TLegend(0.55,0.65,0.9,0.9);
            leg.SetHeader("Legend","C");
            leg.AddEntry(histo[3+i],"B0 MC","f");
            leg.AddEntry(histo[6+i],"Bp MC","f");
            leg.AddEntry(histo[9+i],"Ds MC","f");
            leg.AddEntry(histo[0+i],"Data","f");
            leg.Draw("same")
            c.SaveAs("./Plot_Ana/"+na+"/PreE/"+reso_range[i] + "_preE.png")
            c.Clear()
        #Post E plots
        for i in range(3): #Lopp sui range di massa inv.
            if(ind==9 and i==0): rangelim[9]=0.15
            st2=THStack("st2","")
            histo[15+i].Scale(sf_postE[0]*f/histo[15+i].Integral())
            histo[15+i].SetFillStyle(3244)
            histo[15+i].SetFillColor(kYellow+1)
            histo[15+i].SetLineColor(kYellow+1)
            #histo[3+i].GetYaxis().SetRangeUser(0,0.5);
            st2.Add(histo[15+i])
            histo[18+i].Scale(sf_postE[1]*f/histo[18+i].Integral())
            histo[18+i].SetFillStyle(3244)
            histo[18+i].SetFillColor(kMagenta-4)
            histo[18+i].SetLineColor(kMagenta-4)
            st2.Add(histo[18+i])
            histo[21+i].Scale(sf_postE[2]*f/histo[21+i].Integral())
            histo[21+i].SetFillStyle(3244)
            histo[21+i].SetFillColor(kCyan)
            histo[21+i].SetLineColor(kCyan)
            st2.Add(histo[21+i])
            
            histo[12+i].SetFillStyle(3244)
            histo[12+i].SetFillColor(kGray)
            histo[12+i].SetLineColor(kGray)
            histo[12+i].Scale(1./histo[12+i].Integral())
            
            #Plot:
            histo[12+i].GetYaxis().SetRangeUser(0,float(rangelim[ind]))
            histo[12+i].SetTitle("Plot "+na+" in "+reso_range[i]+" postE")
            histo[12+i].GetXaxis().SetTitle(na)
            histo[12+i].GetYaxis().SetTitle("Entries")
            histo[12+i].DrawNormalized("histo")
            st2.Draw("samehisto")
            #histo[12+i].DrawNormalized("samehisto")
            if(ind ==6):
                leg=TLegend(0.1,0.65,0.45,0.9);
            else:
                leg=TLegend(0.55,0.65,0.9,0.9);
            leg.SetHeader("Legend","C");
            leg.AddEntry(histo[3+i],"B0 MC","f");
            leg.AddEntry(histo[6+i],"Bp MC","f");
            leg.AddEntry(histo[9+i],"Ds MC","f");
            leg.AddEntry(histo[0+i],"Data","f");
            leg.Draw("same")
            c.SaveAs("./Plot_Ana/"+na+"/PostE/"+reso_range[i] + "_postE.png")
            c.Clear()
        ind += 1
        
