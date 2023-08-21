import sys
import os
import csv
import string
import datetime

# Define the parser
import argparse
parser = argparse.ArgumentParser(description="Options to give to the script")
# Positional arguments
parser.add_argument("dataset", type=str, choices=['data', 'data_control', 'MC'], help="Specify if data or Monte Carlo")
parser.add_argument("anatype", type=str, choices=['tau3mu', 'control'], help="Specify analysis type")
# parser.add_argument("--run", type=str, default='', choices=['2022B', '2022C_0', '2022C_1', '2022C_2', '2022C_3', '2022C_4', '2022C_5', '2022C_6', '2022C_7', '2022D-v1_0', '2022D-v1_1', '2022D-v1_2', '2022D-v1_3', '2022D-v1_4', '2022D-v1_5', '2022D-v1_6', '2022D-v1_7', '2022D-v2_0', '2022D-v2_1', '2022D-v2_2', '2022D-v2_3', '2022D-v2_4', '2022D-v2_5', '2022D-v2_6', '2022D-v2_7', '2022E_0', '2022E_1', '2022E_2', '2022E_3', '2022E_4', '2022E_5', '2022E_6', '2022E_7', '2022F_0', '2022F_1', '2022F_2', '2022F_3', '2022F_4', '2022F_5', '2022F_6', '2022F_7', '2022G_0', '2022G_1', '2022G_2', '2022G_3', '2022G_4', '2022G_5', '2022G_6', '2022G_7'], help="run in data")
parser.add_argument("--run", type=str, default='', choices=['2022B', '2022C_0', '2022C_1', '2022C_2', '2022C_3', '2022C_4', '2022C_5', '2022C_6', '2022C_7', '2022D_0', '2022D_1', '2022D_2', '2022D_3', '2022D_4', '2022D_5', '2022D_6', '2022D_7', '2022E_0', '2022E_1', '2022E_2', '2022E_3', '2022E_4', '2022E_5', '2022E_6', '2022E_7', '2022F_0', '2022F_1', '2022F_2', '2022F_3', '2022F_4', '2022F_5', '2022F_6', '2022F_7', '2022G_0', '2022G_1', '2022G_2', '2022G_3', '2022G_4', '2022G_5', '2022G_6', '2022G_7','2023B_0', '2023B_1', '2023B_2', '2023B_3', '2023B_4', '2023B_5', '2023B_6', '2023B_7', '2023C-v1_0', '2023C-v1_1', '2023C-v1_2',  '2023C-v1_3',  '2023C-v1_4', '2023C-v1_5', '2023C-v1_6', '2023C-v1_7', '2023C-v2_0', '2023C-v2_1', '2023C-v2_2', '2023C-v2_3', '2023C-v2_4', '2023C-v2_5', '2023C-v2_6', '2023C-v2_7', '2023C-v3_0', '2023C-v3_1', '2023C-v3_2', '2023C-v3_3', '2023C-v3_4', '2023C-v3_5', '2023C-v3_6', '2023C-v3_7', '2023C-v4_0', '2023C-v4_1', '2023C-v4_2', '2023C-v4_3', '2023C-v4_4', '2023C-v4_5', '2023C-v4_6', '2023C-v4_7', '2023D-v1_0', '2023D-v1_1', '2023D-v1_2', '2023D-v1_3', '2023D-v1_4', '2023D-v1_5', '2023D-v1_6', '2023D-v1_7', '2023D-v2_0', '2023D-v2_1', '2023D-v2_2', '2023D-v2_3', '2023D-v2_4', '2023D-v2_5', '2023D-v2_6', '2023D-v2_7'], help="run in data")

# Optional Arguments
parser.add_argument("--outName", type=str, default="test", help="Specify name for output files")
parser.add_argument("--n", type=int, default=255, help="number of .root files per job")
parser.add_argument("--MCprocess", type=str, default='', choices=['Ds_preE', 'Ds_postE', 'B0_preE', 'B0_postE', 'Bp_preE', 'Bp_postE', 'DsPhiPi_preE', 'DsPhiPi_postE', 'DsPhiMuNu'], help="process in Monte Carlo")
args = parser.parse_args()

#prepare output filename  and option string
if args.dataset == 'data':
   out_filename = 'AnalysedTree_'+args.dataset+'_'+args.run+'_'+args.anatype
   temp = '_'+args.anatype
   option_string = ' "'+args.dataset+temp.replace("_tau3mu","")+'" "'+args.run+'"'
elif args.dataset == 'data_control':
   out_filename = 'AnalysedTree_'+args.dataset+'_'+args.run+'_'+args.anatype
   temp = '_'+args.anatype
   option_string = ' "'+args.dataset+temp.replace("_control","")+'" "'+args.run+'"'
elif args.dataset == 'MC':
   out_filename = 'AnalysedTree_'+args.dataset+'_'+args.MCprocess+'_'+args.anatype
   temp = '_'+args.anatype
   option_string = ' "'+args.dataset+temp.replace("_tau3mu","")+'" "'+args.MCprocess+'"'

#startTime = datetime.datetime.now().strftime("%Y%m%d_%H%M")

# Create target Directory if don't exist
if args.dataset == 'MC':
   output_name = args.MCprocess+"_"+args.anatype+"_"+args.outName
else: 
   output_name = args.run+"_"+args.anatype+"_"+args.outName

if not os.path.exists(output_name):
    os.mkdir(output_name)
    print('Directory '+output_name+' created\n')
else:    
    print('Directory '+output_name+' already exists\n')

if args.anatype == 'tau3mu':
   #### 2022
   if args.dataset == 'data' and args.run == '2022B':
      path = '' 
   if args.dataset == 'data' and args.run == '2022C_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsTau3mu_2022eraC_stream0_Mini_v3/230504_135403'
   if args.dataset == 'data' and args.run == '2022C_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsTau3mu_2022eraC_stream1_Mini_v3/230504_135433'
   if args.dataset == 'data' and args.run == '2022C_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsTau3mu_2022eraC_stream2_Mini_v3/230504_135502'
   if args.dataset == 'data' and args.run == '2022C_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsTau3mu_2022eraC_stream3_Mini_v3/230504_135532'
   if args.dataset == 'data' and args.run == '2022C_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsTau3mu_2022eraC_stream4_Mini_v3/230504_135604'
   if args.dataset == 'data' and args.run == '2022C_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsTau3mu_2022eraC_stream5_Mini_v3/230504_135636'
   if args.dataset == 'data' and args.run == '2022C_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsTau3mu_2022eraC_stream6_Mini_v3/230504_135709'
   if args.dataset == 'data' and args.run == '2022C_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsTau3mu_2022eraC_stream7_Mini_v3/230504_135740'
      
   if args.dataset == 'data' and args.run == '2022D_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraD_stream0_Mini_v3/230504_151331'
   if args.dataset == 'data' and args.run == '2022D_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraD_stream1_Mini_v3/230504_151401'
   if args.dataset == 'data' and args.run == '2022D_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraD_stream2_Mini_v3/230504_151432'
   if args.dataset == 'data' and args.run == '2022D_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraD_stream3_Mini_v3/230504_151502'
   if args.dataset == 'data' and args.run == '2022D_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraD_stream4_Mini_v3/230504_151531'
   if args.dataset == 'data' and args.run == '2022D_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraD_stream5_Mini_v3/230504_151602'
   if args.dataset == 'data' and args.run == '2022D_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraD_stream6_Mini_v3/230504_151632'
   if args.dataset == 'data' and args.run == '2022D_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraD_stream7_Mini_v3/230504_151704'
      
   '''
   if args.dataset == 'data' and args.run == '2022D-v1_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraD-v1_stream0_Mini_v6/221215_125019'
   if args.dataset == 'data' and args.run == '2022D-v1_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraD-v1_stream1_Mini_v6/221215_151532'
   if args.dataset == 'data' and args.run == '2022D-v1_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraD-v1_stream2_Mini_v6/221215_151601'
   if args.dataset == 'data' and args.run == '2022D-v1_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraD-v1_stream3_Mini_v6/221215_151631'
   if args.dataset == 'data' and args.run == '2022D-v1_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraD-v1_stream4_Mini_v6/221215_151701'
   if args.dataset == 'data' and args.run == '2022D-v1_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraD-v1_stream5_Mini_v6/221215_151729'
   if args.dataset == 'data' and args.run == '2022D-v1_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraD-v1_stream6_Mini_v6/221215_151758'
   if args.dataset == 'data' and args.run == '2022D-v1_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraD-v1_stream7_Mini_v6/221215_151827'
   if args.dataset == 'data' and args.run == '2022D-v2_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraD-v2_stream0_Mini_v6/221215_145359'
   if args.dataset == 'data' and args.run == '2022D-v2_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraD-v2_stream1_Mini_v6/221215_170419'
   if args.dataset == 'data' and args.run == '2022D-v2_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraD-v2_stream2_Mini_v6/221215_170453'
   if args.dataset == 'data' and args.run == '2022D-v2_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraD-v2_stream3_Mini_v6/221215_170528'
   if args.dataset == 'data' and args.run == '2022D-v2_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraD-v2_stream4_Mini_v6/221215_170603'
   if args.dataset == 'data' and args.run == '2022D-v2_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraD-v2_stream5_Mini_v6/221215_170636'
   if args.dataset == 'data' and args.run == '2022D-v2_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraD-v2_stream6_Mini_v6/221215_170709'
   if args.dataset == 'data' and args.run == '2022D-v2_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraD-v2_stream7_Mini_v6/221215_170744'
   '''
   if args.dataset == 'data' and args.run == '2022E_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraE_stream0_Mini_v3/230504_151737'
   if args.dataset == 'data' and args.run == '2022E_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraE_stream1_Mini_v3/230504_151808'
   if args.dataset == 'data' and args.run == '2022E_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraE_stream2_Mini_v3/230504_151840'
   if args.dataset == 'data' and args.run == '2022E_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraE_stream3_Mini_v3/230504_151911'
   if args.dataset == 'data' and args.run == '2022E_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraE_stream4_Mini_v3/230504_151942'
   if args.dataset == 'data' and args.run == '2022E_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraE_stream5_Mini_v3/230504_152013'
   if args.dataset == 'data' and args.run == '2022E_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraE_stream6_Mini_v3/230504_152044'
   if args.dataset == 'data' and args.run == '2022E_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraE_stream7_Mini_v3/230504_152114'
      
   if args.dataset == 'data' and args.run == '2022F_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraF_stream0_Mini_v3/230504_152143'
   if args.dataset == 'data' and args.run == '2022F_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraF_stream1_Mini_v3/230504_152215'
   if args.dataset == 'data' and args.run == '2022F_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraF_stream2_Mini_v3/230504_152245'
   if args.dataset == 'data' and args.run == '2022F_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraF_stream3_Mini_v3/230504_152316'
   if args.dataset == 'data' and args.run == '2022F_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraF_stream4_Mini_v3/230504_152345'
   if args.dataset == 'data' and args.run == '2022F_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraF_stream5_Mini_v3/230504_152415'
   if args.dataset == 'data' and args.run == '2022F_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraF_stream6_Mini_v3/230504_152445'
   if args.dataset == 'data' and args.run == '2022F_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraF_stream7_Mini_v3/230504_152514'
      
   if args.dataset == 'data' and args.run == '2022G_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraG_stream0_Mini_v3/230504_152632'
   if args.dataset == 'data' and args.run == '2022G_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraG_stream1_Mini_v3/230504_152651'
   if args.dataset == 'data' and args.run == '2022G_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraG_stream2_Mini_v3/230504_152711'
   if args.dataset == 'data' and args.run == '2022G_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraG_stream3_Mini_v3/230504_152731'
   if args.dataset == 'data' and args.run == '2022G_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraG_stream4_Mini_v3/230504_152751'
   if args.dataset == 'data' and args.run == '2022G_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraG_stream5_Mini_v3/230504_152812'
   if args.dataset == 'data' and args.run == '2022G_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraG_stream6_Mini_v3/230504_152833'
   if args.dataset == 'data' and args.run == '2022G_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraG_stream7_Mini_v3/230504_152853'


if args.anatype == 'control':
   if args.dataset == 'data_control' and args.run == '2022B':
      path = ''
   if args.dataset == 'data_control' and args.run == '2022C_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraC_stream0_Mini_v3/230507_105546'
   if args.dataset == 'data_control' and args.run == '2022C_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraC_stream1_Mini_v3/230507_105617'
   if args.dataset == 'data_control' and args.run == '2022C_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraC_stream2_Mini_v3/230507_105648'
   if args.dataset == 'data_control' and args.run == '2022C_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraC_stream3_Mini_v3/230507_105718'
   if args.dataset == 'data_control' and args.run == '2022C_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraC_stream4_Mini_v3/230507_105748'
   if args.dataset == 'data_control' and args.run == '2022C_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraC_stream5_Mini_v3/230507_105817'
   if args.dataset == 'data_control' and args.run == '2022C_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraC_stream6_Mini_v3/230507_105847'
   if args.dataset == 'data_control' and args.run == '2022C_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraC_stream7_Mini_v3/230507_105917'
      
   if args.dataset == 'data_control' and args.run == '2022D_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraD_stream0_Mini_v3/230507_105929'
   if args.dataset == 'data_control' and args.run == '2022D_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraD_stream1_Mini_v3/230507_105959'
   if args.dataset == 'data_control' and args.run == '2022D_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraD_stream2_Mini_v3/230507_110030'
   if args.dataset == 'data_control' and args.run == '2022D_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraD_stream3_Mini_v3/230507_110101'
   if args.dataset == 'data_control' and args.run == '2022D_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraD_stream4_Mini_v3/230507_110135'
   if args.dataset == 'data_control' and args.run == '2022D_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraD_stream5_Mini_v3/230507_110209'
   if args.dataset == 'data_control' and args.run == '2022D_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraD_stream6_Mini_v3/230507_110239'
   if args.dataset == 'data_control' and args.run == '2022D_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraD_stream7_Mini_v3/230507_110308'
   '''
   if args.dataset == 'data_control' and args.run == '2022D-v1_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraD-v1_stream0_Mini_v6/221216_170014'
   if args.dataset == 'data_control' and args.run == '2022D-v1_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraD-v1_stream1_Mini_v6/221217_081546'
   if args.dataset == 'data_control' and args.run == '2022D-v1_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraD-v1_stream2_Mini_v6/221217_081616'
   if args.dataset == 'data_control' and args.run == '2022D-v1_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraD-v1_stream3_Mini_v6/221217_081648'
   if args.dataset == 'data_control' and args.run == '2022D-v1_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraD-v1_stream4_Mini_v6/221217_081719'
   if args.dataset == 'data_control' and args.run == '2022D-v1_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraD-v1_stream5_Mini_v6/221217_081750'
   if args.dataset == 'data_control' and args.run == '2022D-v1_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraD-v1_stream6_Mini_v6/221217_081822'
   if args.dataset == 'data_control' and args.run == '2022D-v1_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraD-v1_stream7_Mini_v6/221217_081854'
   if args.dataset == 'data_control' and args.run == '2022D-v2_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraD-v2_stream0_Mini_v6/221216_170108'
   if args.dataset == 'data_control' and args.run == '2022D-v2_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraD-v2_stream1_Mini_v6/221217_083112'
   if args.dataset == 'data_control' and args.run == '2022D-v2_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraD-v2_stream2_Mini_v6/221217_083145'
   if args.dataset == 'data_control' and args.run == '2022D-v2_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraD-v2_stream3_Mini_v6/221217_083217'
   if args.dataset == 'data_control' and args.run == '2022D-v2_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraD-v2_stream4_Mini_v6/221217_083249'
   if args.dataset == 'data_control' and args.run == '2022D-v2_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraD-v2_stream5_Mini_v6/221217_083321'
   if args.dataset == 'data_control' and args.run == '2022D-v2_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraD-v2_stream6_Mini_v6/221217_083352'
   if args.dataset == 'data_control' and args.run == '2022D-v2_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraD-v2_stream7_Mini_v6/221217_083425'
   '''
   if args.dataset == 'data_control' and args.run == '2022E_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraE_stream0_Mini_v3/230507_110320'
   if args.dataset == 'data_control' and args.run == '2022E_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraE_stream1_Mini_v3/230507_110348'
   if args.dataset == 'data_control' and args.run == '2022E_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraE_stream2_Mini_v3/230507_110418'
   if args.dataset == 'data_control' and args.run == '2022E_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraE_stream3_Mini_v3/230507_110448'
   if args.dataset == 'data_control' and args.run == '2022E_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraE_stream4_Mini_v3/230507_110518'
   if args.dataset == 'data_control' and args.run == '2022E_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraE_stream5_Mini_v3/230507_110549'
   if args.dataset == 'data_control' and args.run == '2022E_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraE_stream6_Mini_v3/230507_110619'
   if args.dataset == 'data_control' and args.run == '2022E_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraE_stream7_Mini_v3/230507_110649'
      
   if args.dataset == 'data_control' and args.run == '2022F_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraF_stream0_Mini_v3/230507_110700'
   if args.dataset == 'data_control' and args.run == '2022F_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraF_stream1_Mini_v3/230507_110734'
   if args.dataset == 'data_control' and args.run == '2022F_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraF_stream2_Mini_v3/230507_110806'
   if args.dataset == 'data_control' and args.run == '2022F_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraF_stream3_Mini_v3/230507_110838'
   if args.dataset == 'data_control' and args.run == '2022F_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraF_stream4_Mini_v3/230507_110908'
   if args.dataset == 'data_control' and args.run == '2022F_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraF_stream5_Mini_v3/230507_110939'
   if args.dataset == 'data_control' and args.run == '2022F_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraF_stream6_Mini_v3/230507_111009'
   if args.dataset == 'data_control' and args.run == '2022F_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraF_stream7_Mini_v3/230507_111039'
      
   if args.dataset == 'data_control' and args.run == '2022G_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraG_stream0_Mini_v3/230507_111050'
   if args.dataset == 'data_control' and args.run == '2022G_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraG_stream1_Mini_v3/230507_111120'
   if args.dataset == 'data_control' and args.run == '2022G_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraG_stream2_Mini_v3/230507_111149'
   if args.dataset == 'data_control' and args.run == '2022G_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraG_stream3_Mini_v3/230507_111218'
   if args.dataset == 'data_control' and args.run == '2022G_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraG_stream4_Mini_v3/230507_111248'
   if args.dataset == 'data_control' and args.run == '2022G_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraG_stream5_Mini_v3/230507_111319'
   if args.dataset == 'data_control' and args.run == '2022G_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraG_stream6_Mini_v3/230507_111352'
   if args.dataset == 'data_control' and args.run == '2022G_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraG_stream7_Mini_v3/230507_111424'

   if args.dataset == 'data_control' and args.run == '2023B_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraB_stream0_Mini_v3/230608_165126'
   if args.dataset == 'data_control' and args.run == '2023B_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraB_stream1_Mini_v3/230608_165340'
   if args.dataset == 'data_control' and args.run == '2023B_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraB_stream2_Mini_v3/230608_165516'
   if args.dataset == 'data_control' and args.run == '2023B_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraB_stream3_Mini_v3/230608_165646'
   if args.dataset == 'data_control' and args.run == '2023B_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraB_stream4_Mini_v3/230608_165821'
   if args.dataset == 'data_control' and args.run == '2023B_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraB_stream5_Mini_v3/230608_170008'
   if args.dataset == 'data_control' and args.run == '2023B_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraB_stream6_Mini_v3/230608_170147'
   if args.dataset == 'data_control' and args.run == '2023B_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraB_stream7_Mini_v3/230608_170353'

   if args.dataset == 'data_control' and args.run == '2023C-v1_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraC-v1_stream0_Mini_v3/230608_205030'
   if args.dataset == 'data_control' and args.run == '2023C-v1_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraC-v1_stream1_Mini_v3/230608_205042'
   if args.dataset == 'data_control' and args.run == '2023C-v1_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraC-v1_stream2_Mini_v3/230608_205054'
   if args.dataset == 'data_control' and args.run == '2023C-v1_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraC-v1_stream3_Mini_v3/230608_205106'
   if args.dataset == 'data_control' and args.run == '2023C-v1_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraC-v1_stream4_Mini_v3/230608_205118'
   if args.dataset == 'data_control' and args.run == '2023C-v1_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraC-v1_stream5_Mini_v3/230609_130551'
   if args.dataset == 'data_control' and args.run == '2023C-v1_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraC-v1_stream6_Mini_v3/230608_205136'
   if args.dataset == 'data_control' and args.run == '2023C-v1_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraC-v1_stream7_Mini_v3/230608_205148'
   
   if args.dataset == 'data_control' and args.run == '2023C-v2_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraC-v2_stream0_Mini_v3/230608_205259'
   if args.dataset == 'data_control' and args.run == '2023C-v2_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraC-v2_stream1_Mini_v3/230608_205311'
   if args.dataset == 'data_control' and args.run == '2023C-v2_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraC-v2_stream2_Mini_v3/230608_205323'
   if args.dataset == 'data_control' and args.run == '2023C-v2_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraC-v2_stream3_Mini_v3/230608_205334'
   if args.dataset == 'data_control' and args.run == '2023C-v2_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraC-v2_stream4_Mini_v3/230608_205347'
   if args.dataset == 'data_control' and args.run == '2023C-v2_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraC-v2_stream5_Mini_v3/230608_205359'
   if args.dataset == 'data_control' and args.run == '2023C-v2_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraC-v2_stream6_Mini_v3/230608_205411'
   if args.dataset == 'data_control' and args.run == '2023C-v2_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraC-v2_stream7_Mini_v3/230608_205424'

   if args.dataset == 'data_control' and args.run == '2023C-v3_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraC-v3_stream0_Mini_v3/230608_205520'
   if args.dataset == 'data_control' and args.run == '2023C-v3_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraC-v3_stream1_Mini_v3/230608_205532'
   if args.dataset == 'data_control' and args.run == '2023C-v3_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraC-v3_stream2_Mini_v3/230608_205544'
   if args.dataset == 'data_control' and args.run == '2023C-v3_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraC-v3_stream3_Mini_v3/230608_205556'
   if args.dataset == 'data_control' and args.run == '2023C-v3_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraC-v3_stream4_Mini_v3/230608_205608'
   if args.dataset == 'data_control' and args.run == '2023C-v3_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraC-v3_stream5_Mini_v3/230608_205620'
   if args.dataset == 'data_control' and args.run == '2023C-v3_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraC-v3_stream6_Mini_v3/230608_205632'
   if args.dataset == 'data_control' and args.run == '2023C-v3_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraC-v3_stream7_Mini_v3/230608_205644'

   if args.dataset == 'data_control' and args.run == '2023C-v4_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraC-v4_stream0_Mini_v3/230608_205851'
   if args.dataset == 'data_control' and args.run == '2023C-v4_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraC-v4_stream1_Mini_v3/230608_205919'
   if args.dataset == 'data_control' and args.run == '2023C-v4_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraC-v4_stream2_Mini_v3/230608_205947'
   if args.dataset == 'data_control' and args.run == '2023C-v4_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraC-v4_stream3_Mini_v3/230608_210014'
   if args.dataset == 'data_control' and args.run == '2023C-v4_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraC-v4_stream4_Mini_v3/230608_210041'
   if args.dataset == 'data_control' and args.run == '2023C-v4_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraC-v4_stream5_Mini_v3/230608_210108'
   if args.dataset == 'data_control' and args.run == '2023C-v4_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraC-v4_stream6_Mini_v3/230608_210135'
   if args.dataset == 'data_control' and args.run == '2023C-v4_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraC-v4_stream7_Mini_v3/230608_210202'

if args.dataset == 'MC' and args.MCprocess == 'Ds_preE':
   path = '/lustre/cms/store/user/mbuonsan/DstoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Ds_new_Mini_preE/230504_170059'
if args.dataset == 'MC' and args.MCprocess == 'Ds_postE':
   path = '/lustre/cms/store/user/mbuonsan/DstoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Ds_new_Mini_postE/230504_170127'
if args.dataset == 'MC' and args.MCprocess == 'Bp_preE':
   path = '/lustre/cms/store/user/mbuonsan/ButoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bu_Mini_preE/230504_170043'
if args.dataset == 'MC' and args.MCprocess == 'Bp_postE':
   path = '/lustre/cms/store/user/mbuonsan/ButoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bu_Mini_postE/230504_170114'
if args.dataset == 'MC' and args.MCprocess == 'B0_preE':
   path = '/lustre/cms/store/user/mbuonsan/BdtoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bd_Mini_preE/230504_170029'
if args.dataset == 'MC' and args.MCprocess == 'B0_postE':
   path = '/lustre/cms/store/user/mbuonsan/BdtoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bd_Mini_postE/230504_170014'
if args.dataset == 'MC' and args.MCprocess == 'DsPhiMuNu':
   path = '/lustre/cms/store/user/caruta/Pythia8_DsPhiMuNu_Run3_2022/SkimTau3mu_MCRun3_DsPhiMuNu_Mini_v4/230114_172745'
if args.dataset == 'MC' and args.MCprocess == 'DsPhiPi_preE':
   path = '/lustre/cms/store/user/mbuonsan/DstoPhiPi_Phito2Mu_MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimPhiPi_MCRun3_Mini_preE/230507_103411'
if args.dataset == 'MC' and args.MCprocess == 'DsPhiPi_postE':
   path = '/lustre/cms/store/user/mbuonsan/DstoPhiPi_Phito2Mu_MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimPhiPi_MCRun3_Mini_postE/230507_103348'

#generating the list of all .root files in given directory and subdirectories
fileList = []
for r, d, f in os.walk(path): # r=root, d=directories, f = files
    for file in f:
        if '.root' in file:
            fileList.append(os.path.join(r, file))
            print file

#prepare final script
#final_script = open("submit_analysis_"+startTime+".sh", "w")
final_script = open("submit_analysis_"+output_name+".sh", "w")
final_script.write("#!/bin/bash\n")
final_script.write("chmod 777 -R *\n")
final_script.write("cd "+output_name+"\n")

#loop to generate one .cpp+executable+batch system conf file for each group of "n" files
n_chunk = len(fileList)//args.n
print('Number of files is {0:2d}'.format(len(fileList)))
print('Number of jobs is {0:2d}'.format(n_chunk+1))
for file_index in range(n_chunk+1):
      chunk = '' 
      for idx, l in enumerate(fileList):
         if idx < args.n*(file_index+1) and idx >= args.n*file_index:
             l = l.rstrip()
             l = '        chain->AddFile("{}");\n'.format(l)
             chunk = chunk + l

      #analysis.cpp template
      with open("templates/Analysis_template.cpp", "r") as in_file:
          buf = in_file.readlines()

      cpp_filename = "Analysis_"+args.dataset+"_"+args.run+args.MCprocess+"_"+args.anatype+"_chunk"+str(file_index)+".cpp"
      with open(cpp_filename, "w") as out_file:
          for lb in buf:
              if lb == '        //AddFile_'+args.dataset+args.MCprocess+'_'+args.anatype+'\n':
                  #write group of files
                  out_file.write(chunk)
              elif lb == '        //OutFile_'+args.dataset+args.MCprocess+'_'+args.anatype+'\n':
                  #write output file name
                  out_file.write('        fileout = "'+out_filename+str(file_index)+'.root";\n')
              else: out_file.write(lb)

              #elif lb == '            TString fileout = "AddOutput_'+args.dataset+args.MCprocess+'_'+args.anatype+'.root";\n':
                  #write output file name
               #   out_file.write('        TString fileout = "'+out_filename+str(file_index)+'.root";\n')
              #else: out_file.write(lb)

      #executable template
      with open("templates/launch_analysis_template.job", "r") as launch_infile:
          buf2 = launch_infile.readlines()

      launch_filename = "launch_analysis_"+args.dataset+"_"+args.run+args.MCprocess+"_"+args.anatype+"_"+str(file_index)+".job"
      with open(output_name+"/"+launch_filename, "w") as launch_outfile:
          for lb2 in buf2:
              if lb2 == "#compile\n":
                  launch_outfile.write("cd "+output_name+"\n")
                  launch_outfile.write("g++ -I $ROOTSYS/include ../"+cpp_filename+" `root-config --glibs` `root-config --libs` `root-config --cflags` -lTMVA -L $ROOTSYS/lib -o executable"+str(file_index)+"\n")
              elif lb2 == "#execute\n":
                  launch_outfile.write('./executable'+str(file_index)+option_string+'\n')
              else: launch_outfile.write(lb2)

      #myCondor template
      with open("templates/my_HTCondor_template.job", "r") as myCondor_infile:
          buf3 = myCondor_infile.readlines()

      condor_filename = "my_HTCondor_"+args.dataset+"_"+args.run+args.MCprocess+"_"+args.anatype+"_"+str(file_index)+".job"
      with open(output_name+"/"+condor_filename, "w") as myCondor_outfile:
          for lb3 in buf3:
              if lb3 == "Executable = launch_analysis_template.job\n":
                  myCondor_outfile.write("Executable = "+launch_filename+"\n")
              else: myCondor_outfile.write(lb3)

      #add lines to final script
      final_script.write("echo condor_submit "+condor_filename+" -name ettore\n")
      final_script.write("condor_submit "+condor_filename+" -name ettore\n")

final_script.close()
#submitName = "submit_analysis_"+startTime+".sh"
#source submitName
