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
from multiprocessing import Pool

tname= ["TreeMakerBkg/ntuple", "TreeMakerBkg/ntuple", "Tree3Mu/ntuple", "Tree3Mu/ntuple"]

def fit_era(dataset, era):
    indx = ['_0', '_1', '_2', '_3', '_4', '_5', '_6', '_7']
    if (dataset=='data' or dataset=='dataE' or dataset=='dataE2'):
        nome="TreeMakerBkg/ntuple"
    if (dataset=='data_control' or dataset=='data_controlE'):
        nome="Tree3Mu/ntuple"
    t1 = TChain(nome)
    for ind in indx:
        run = '2022'+era+ind
        path=''
        if dataset == 'data' and run == '2022C_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsTau3mu_2022eraC_stream0_Mini_v3/230504_135403'
        if dataset == 'data' and run == '2022C_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsTau3mu_2022eraC_stream1_Mini_v3/230504_135433'
        if dataset == 'data' and run == '2022C_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsTau3mu_2022eraC_stream2_Mini_v3/230504_135502'
        if dataset == 'data' and run == '2022C_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsTau3mu_2022eraC_stream3_Mini_v3/230504_135532'
        if dataset == 'data' and run == '2022C_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsTau3mu_2022eraC_stream4_Mini_v3/230504_135604'
        if dataset == 'data' and run == '2022C_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsTau3mu_2022eraC_stream5_Mini_v3/230504_135636'
        if dataset == 'data' and run == '2022C_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsTau3mu_2022eraC_stream6_Mini_v3/230504_135709'
        if dataset == 'data' and run == '2022C_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsTau3mu_2022eraC_stream7_Mini_v3/230504_135740'
            
        if dataset == 'data' and run == '2022D_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraD_stream0_Mini_v3/230504_151331'
        if dataset == 'data' and run == '2022D_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraD_stream1_Mini_v3/230504_151401'
        if dataset == 'data' and run == '2022D_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraD_stream2_Mini_v3/230504_151432'
        if dataset == 'data' and run == '2022D_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraD_stream3_Mini_v3/230504_151502'
        if dataset == 'data' and run == '2022D_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraD_stream4_Mini_v3/230504_151531'
        if dataset == 'data' and run == '2022D_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraD_stream5_Mini_v3/230504_151602'
        if dataset == 'data' and run == '2022D_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraD_stream6_Mini_v3/230504_151632'
        if dataset == 'data' and run == '2022D_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraD_stream7_Mini_v3/230504_151704'
    
        if dataset == 'dataE' and run == '2022E_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraE_stream0_Mini_v3/230504_151737'
        if dataset == 'dataE' and run == '2022E_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraE_stream1_Mini_v3/230504_151808'
        if dataset == 'dataE' and run == '2022E_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraE_stream2_Mini_v3/230504_151840'
        if dataset == 'dataE' and run == '2022E_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraE_stream3_Mini_v3/230504_151911'
        if dataset == 'dataE' and run == '2022E_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraE_stream4_Mini_v3/230504_151942'
        if dataset == 'dataE' and run == '2022E_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraE_stream5_Mini_v3/230504_152013'
        if dataset == 'dataE' and run == '2022E_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraE_stream6_Mini_v3/230504_152044'
        if dataset == 'dataE' and run == '2022E_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraE_stream7_Mini_v3/230504_152114'
        
        if dataset == 'dataE' and run == '2022F_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraF_stream0_Mini_v3/230504_152143'
        if dataset == 'dataE' and run == '2022F_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraF_stream1_Mini_v3/230504_152215'
        if dataset == 'dataE' and run == '2022F_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraF_stream2_Mini_v3/230504_152245'
        if dataset == 'dataE' and run == '2022F_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraF_stream3_Mini_v3/230504_152316'
        if dataset == 'dataE2' and run == '2022F_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraF_stream4_Mini_v3/230504_152345'
        if dataset == 'dataE2' and run == '2022F_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraF_stream5_Mini_v3/230504_152415'
        if dataset == 'dataE2' and run == '2022F_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraF_stream6_Mini_v3/230504_152445'
        if dataset == 'dataE2' and run == '2022F_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraF_stream7_Mini_v3/230504_152514'
            
        if dataset == 'dataE' and run == '2022G_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraG_stream0_Mini_v3/230504_152632'
        if dataset == 'dataE' and run == '2022G_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraG_stream1_Mini_v3/230504_152651'
        if dataset == 'dataE' and run == '2022G_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraG_stream2_Mini_v3/230504_152711'
        if dataset == 'dataE' and run == '2022G_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraG_stream3_Mini_v3/230504_152731'
        if dataset == 'dataE' and run == '2022G_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraG_stream4_Mini_v3/230504_152751'
        if dataset == 'dataE' and run == '2022G_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraG_stream5_Mini_v3/230504_152812'
        if dataset == 'dataE' and run == '2022G_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraG_stream6_Mini_v3/230504_152833'
        if dataset == 'dataE' and run == '2022G_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraG_stream7_Mini_v3/230504_152853'

        if dataset == 'data_control' and run == '2022C_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraC_stream0_Mini_v3/230507_105546'
        if dataset == 'data_control' and run == '2022C_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraC_stream1_Mini_v3/230507_105617'
        if dataset == 'data_control' and run == '2022C_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraC_stream2_Mini_v3/230507_105648'
        if dataset == 'data_control' and run == '2022C_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraC_stream3_Mini_v3/230507_105718'
        if dataset == 'data_control' and run == '2022C_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraC_stream4_Mini_v3/230507_105748'
        if dataset == 'data_control' and run == '2022C_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraC_stream5_Mini_v3/230507_105817'
        if dataset == 'data_control' and run == '2022C_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraC_stream6_Mini_v3/230507_105847'
        if dataset == 'data_control' and run == '2022C_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraC_stream7_Mini_v3/230507_105917'
            
        if dataset == 'data_control' and run == '2022D_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraD_stream0_Mini_v3/230507_105929'
        if dataset == 'data_control' and run == '2022D_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraD_stream1_Mini_v3/230507_105959'
        if dataset == 'data_control' and run == '2022D_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraD_stream2_Mini_v3/230507_110030'
        if dataset == 'data_control' and run == '2022D_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraD_stream3_Mini_v3/230507_110101'
        if dataset == 'data_control' and run == '2022D_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraD_stream4_Mini_v3/230507_110135'
        if dataset == 'data_control' and run == '2022D_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraD_stream5_Mini_v3/230507_110209'
        if dataset == 'data_control' and run == '2022D_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraD_stream6_Mini_v3/230507_110239'
        if dataset == 'data_control' and run == '2022D_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraD_stream7_Mini_v3/230507_110308'
        
        if dataset == 'data_controlE' and run == '2022E_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraE_stream0_Mini_v3/230507_110320'
        if dataset == 'data_controlE' and run == '2022E_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraE_stream1_Mini_v3/230507_110348'
        if dataset == 'data_controlE' and run == '2022E_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraE_stream2_Mini_v3/230507_110418'
        if dataset == 'data_controlE' and run == '2022E_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraE_stream3_Mini_v3/230507_110448'
        if dataset == 'data_controlE' and run == '2022E_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraE_stream4_Mini_v3/230507_110518'
        if dataset == 'data_controlE' and run == '2022E_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraE_stream5_Mini_v3/230507_110549'
        if dataset == 'data_controlE' and run == '2022E_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraE_stream6_Mini_v3/230507_110619'
        if dataset == 'data_controlE' and run == '2022E_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraE_stream7_Mini_v3/230507_110649'
            
        if dataset == 'data_controlE' and run == '2022F_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraF_stream0_Mini_v3/230507_110700'
        if dataset == 'data_controlE' and run == '2022F_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraF_stream1_Mini_v3/230507_110734'
        if dataset == 'data_controlE' and run == '2022F_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraF_stream2_Mini_v3/230507_110806'
        if dataset == 'data_controlE' and run == '2022F_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraF_stream3_Mini_v3/230507_110838'
        if dataset == 'data_controlE' and run == '2022F_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraF_stream4_Mini_v3/230507_110908'
        if dataset == 'data_controlE' and run == '2022F_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraF_stream5_Mini_v3/230507_110939'
        if dataset == 'data_controlE' and run == '2022F_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraF_stream6_Mini_v3/230507_111009'
        if dataset == 'data_controlE' and run == '2022F_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraF_stream7_Mini_v3/230507_111039'
            
        if dataset == 'data_controlE' and run == '2022G_0':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraG_stream0_Mini_v3/230507_111050'
        if dataset == 'data_controlE' and run == '2022G_1':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraG_stream1_Mini_v3/230507_111120'
        if dataset == 'data_controlE' and run == '2022G_2':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraG_stream2_Mini_v3/230507_111149'
        if dataset == 'data_controlE' and run == '2022G_3':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraG_stream3_Mini_v3/230507_111218'
        if dataset == 'data_controlE' and run == '2022G_4':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraG_stream4_Mini_v3/230507_111248'
        if dataset == 'data_controlE' and run == '2022G_5':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraG_stream5_Mini_v3/230507_111319'
        if dataset == 'data_controlE' and run == '2022G_6':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraG_stream6_Mini_v3/230507_111352'
        if dataset == 'data_controlE' and run == '2022G_7':
            path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraG_stream7_Mini_v3/230507_111424'
        
        if path!='':
            for r, d, f in os.walk(path):
                for file in f:
                    if '.root' in file:
                        print(os.path.join(r, file))
                        t1.Add(os.path.join(r, file))

    file = open("Number_of_events_ntuple.txt", "a")
    n_entries=0
    n_entries = t1.GetEntries()
    file.write(f"\nNumber of entries era {dataset}-{era}: {n_entries}")
    file.close()
    print(f"Number of entries era {dataset}-{era}: {n_entries}")

if __name__=='__main__':
    file = open("Number_of_events_ntuple.txt", "w")
    file.close()
    #with Pool() as p:
    #    p.starmap(fit_era, [('data','C'), ('data','D'), ('dataE','E'), ('dataE','F'), ('dataE2','F'), ('dataE','G'), ('data_control','C'), ('data_control','D'), ('data_controlE','E'), ('data_controlE','F'), ('data_controlE','G')])
    fit_era('data','C')
    fit_era('dataE','G')
