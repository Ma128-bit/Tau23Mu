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
parser.add_argument("--run", type=str, default='', choices=['Minbias', '2018D', '2022B', '2022C_0', '2022C_1', '2022C_2', '2022C_3', '2022C_4', '2022C_5', '2022C_6', '2022C_7', '2022D-v1_0', '2022D-v1_1', '2022D-v1_2', '2022D-v1_3', '2022D-v1_4', '2022D-v1_5', '2022D-v1_6', '2022D-v1_7', '2022D-v2_0', '2022D-v2_1', '2022D-v2_2', '2022D-v2_3', '2022D-v2_4', '2022D-v2_5', '2022D-v2_6', '2022D-v2_7', '2022E_0', '2022E_1', '2022E_2', '2022E_3', '2022E_4', '2022E_5', '2022E_6', '2022E_7', '2022F_0', '2022F_1', '2022F_2', '2022F_3', '2022F_4', '2022F_5', '2022F_6', '2022F_7', '2022G_0', '2022G_1', '2022G_2', '2022G_3', '2022G_4', '2022G_5', '2022G_6', '2022G_7','2023B_0', '2023B_1', '2023B_2', '2023B_3', '2023B_4', '2023B_5', '2023B_6', '2023B_7', '2023C-v1_0', '2023C-v1_1', '2023C-v1_2',  '2023C-v1_3',  '2023C-v1_4', '2023C-v1_5', '2023C-v1_6', '2023C-v1_7', '2023C-v2_0', '2023C-v2_1', '2023C-v2_2', '2023C-v2_3', '2023C-v2_4', '2023C-v2_5', '2023C-v2_6', '2023C-v2_7', '2023C-v3_0', '2023C-v3_1', '2023C-v3_2', '2023C-v3_3', '2023C-v3_4', '2023C-v3_5', '2023C-v3_6', '2023C-v3_7', '2023C-v4_0', '2023C-v4_1', '2023C-v4_2', '2023C-v4_3', '2023C-v4_4', '2023C-v4_5', '2023C-v4_6', '2023C-v4_7', '2023D-v1_0', '2023D-v1_1', '2023D-v1_2', '2023D-v1_3', '2023D-v1_4', '2023D-v1_5', '2023D-v1_6', '2023D-v1_7', '2023D-v2_0', '2023D-v2_1', '2023D-v2_2', '2023D-v2_3', '2023D-v2_4', '2023D-v2_5', '2023D-v2_6', '2023D-v2_7'], help="run in data")

# Optional Arguments
parser.add_argument("--outName", type=str, default="test", help="Specify name for output files")
parser.add_argument("--n", type=int, default=255, help="number of .root files per job")
parser.add_argument("--MCprocess", type=str, default='', choices=['Ds_2018', 'Ds_preE', 'Ds_postE', 'B0_preE', 'B0_postE', 'Bp_preE', 'Bp_postE', 'DsPhiPi_preE', 'DsPhiPi_postE', 'DsPhiMuNu', 'Ds_preBPix', 'Ds_postBPix', 'B0_preBPix', 'B0_postBPix', 'Bp_preBPix', 'Bp_postBPix', 'DsPhiPi_preBPix', 'DsPhiPi_postBPix'], help="process in Monte Carlo")
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
   if args.dataset == 'data' and args.run == 'Minbias':
      path = '/lustre/cms/store/user/mbuonsan/InclusiveDileptonMinBias_TuneCP5Plus_13p6TeV_pythia8/SkimTau3mu_MCMinBias_Mini/240206_113714'
   #### 2018
   if args.dataset == 'data' and args.run == '2018D':
      path = '/lustre/cms/store/user/fsimone/DoubleMuonLowMass/SkimTau3Mu_UL2018_Run2018D_Mini_yesHLT/240202_184932' 
   #### 2022
   if args.dataset == 'data' and args.run == '2022B':
      path = '' 
   if args.dataset == 'data' and args.run == '2022C_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraC_stream0_Mini_v3/240401_201452'
   if args.dataset == 'data' and args.run == '2022C_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraC_stream1_Mini_v3/240401_201511'
   if args.dataset == 'data' and args.run == '2022C_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraC_stream2_Mini_v3/240401_201533'
   if args.dataset == 'data' and args.run == '2022C_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraC_stream3_Mini_v3/240401_201555'
   if args.dataset == 'data' and args.run == '2022C_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraC_stream4_Mini_v3/240401_201614'
   if args.dataset == 'data' and args.run == '2022C_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraC_stream5_Mini_v3/240401_201634'
   if args.dataset == 'data' and args.run == '2022C_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraC_stream6_Mini_v3/240401_201658'
   if args.dataset == 'data' and args.run == '2022C_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraC_stream7_Mini_v3/240401_201718'
     
   '''
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
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraD-v1_stream0_Mini_v3/240401_201734'
   if args.dataset == 'data' and args.run == '2022D-v1_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraD-v1_stream1_Mini_v3/240401_201753'
   if args.dataset == 'data' and args.run == '2022D-v1_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraD-v1_stream2_Mini_v3/240401_201813'
   if args.dataset == 'data' and args.run == '2022D-v1_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraD-v1_stream3_Mini_v3/240401_201833'
   if args.dataset == 'data' and args.run == '2022D-v1_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraD-v1_stream4_Mini_v3/240401_201853'
   if args.dataset == 'data' and args.run == '2022D-v1_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraD-v1_stream5_Mini_v3/240401_201915'
   if args.dataset == 'data' and args.run == '2022D-v1_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraD-v1_stream6_Mini_v3/240401_201934'
   if args.dataset == 'data' and args.run == '2022D-v1_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraD-v1_stream7_Mini_v3/240401_201953'
      
   if args.dataset == 'data' and args.run == '2022D-v2_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraD-v2_stream0_Mini_v3/240401_205035'
   if args.dataset == 'data' and args.run == '2022D-v2_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraD-v2_stream1_Mini_v3/240401_202028'
   if args.dataset == 'data' and args.run == '2022D-v2_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraD-v2_stream2_Mini_v3/240401_202048'
   if args.dataset == 'data' and args.run == '2022D-v2_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraD-v2_stream3_Mini_v3/240401_202107'
   if args.dataset == 'data' and args.run == '2022D-v2_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraD-v2_stream4_Mini_v3/240401_202127'
   if args.dataset == 'data' and args.run == '2022D-v2_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraD-v2_stream5_Mini_v3/240401_202147'
   if args.dataset == 'data' and args.run == '2022D-v2_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraD-v2_stream6_Mini_v3/240401_202206'
   if args.dataset == 'data' and args.run == '2022D-v2_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraD-v2_stream7_Mini_v3/240401_202226'
   
   if args.dataset == 'data' and args.run == '2022E_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraE_stream0_Mini_v3/240401_202241'
   if args.dataset == 'data' and args.run == '2022E_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraE_stream1_Mini_v3/240401_202301'
   if args.dataset == 'data' and args.run == '2022E_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraE_stream2_Mini_v3/240401_202322'
   if args.dataset == 'data' and args.run == '2022E_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraE_stream3_Mini_v3/240401_202342'
   if args.dataset == 'data' and args.run == '2022E_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraE_stream4_Mini_v3/240401_202401'
   if args.dataset == 'data' and args.run == '2022E_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraE_stream5_Mini_v3/240401_202420'
   if args.dataset == 'data' and args.run == '2022E_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraE_stream6_Mini_v3/240401_202441'
   if args.dataset == 'data' and args.run == '2022E_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraE_stream7_Mini_v3/240401_202501'
      
   if args.dataset == 'data' and args.run == '2022F_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraF_stream0_Mini_v3/240401_193056'
   if args.dataset == 'data' and args.run == '2022F_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraF_stream1_Mini_v3/240401_193116'
   if args.dataset == 'data' and args.run == '2022F_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraF_stream2_Mini_v3/240401_193136'
   if args.dataset == 'data' and args.run == '2022F_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraF_stream3_Mini_v3/240401_193155'
   if args.dataset == 'data' and args.run == '2022F_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraF_stream4_Mini_v3/240401_193214'
   if args.dataset == 'data' and args.run == '2022F_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraF_stream5_Mini_v3/240401_193235'
   if args.dataset == 'data' and args.run == '2022F_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraF_stream6_Mini_v3/240401_204543'
   if args.dataset == 'data' and args.run == '2022F_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraF_stream7_Mini_v3/240401_193316'
      
   if args.dataset == 'data' and args.run == '2022G_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2022eraG_stream0_Mini_v3/240401_193544'
   if args.dataset == 'data' and args.run == '2022G_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2022eraG_stream1_Mini_v3/240401_193606'
   if args.dataset == 'data' and args.run == '2022G_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2022eraG_stream2_Mini_v3/240401_193627'
   if args.dataset == 'data' and args.run == '2022G_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2022eraG_stream3_Mini_v3/240401_193648'
   if args.dataset == 'data' and args.run == '2022G_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2022eraG_stream4_Mini_v3/240401_193710'
   if args.dataset == 'data' and args.run == '2022G_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2022eraG_stream5_Mini_v3/240401_193730'
   if args.dataset == 'data' and args.run == '2022G_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2022eraG_stream6_Mini_v3/240401_193751'
   if args.dataset == 'data' and args.run == '2022G_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2022eraG_stream7_Mini_v3/240401_193813'

   ##### 2023
   if args.dataset == 'data' and args.run == '2023B_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2023eraB_stream0_Mini_v3/240401_194112'
   if args.dataset == 'data' and args.run == '2023B_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2023eraB_stream1_Mini_v3/240401_194129'
   if args.dataset == 'data' and args.run == '2023B_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2023eraB_stream2_Mini_v3/240401_194146'
   if args.dataset == 'data' and args.run == '2023B_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2023eraB_stream3_Mini_v3/240401_194204'
   if args.dataset == 'data' and args.run == '2023B_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2023eraB_stream4_Mini_v3/240401_194220'
   if args.dataset == 'data' and args.run == '2023B_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2023eraB_stream5_Mini_v3/240401_194237'
   if args.dataset == 'data' and args.run == '2023B_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2023eraB_stream6_Mini_v3/240401_194252'
   if args.dataset == 'data' and args.run == '2023B_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2023eraB_stream7_Mini_v3/240401_194309'

   if args.dataset == 'data' and args.run == '2023C-v1_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2023eraC-v1_stream0_Mini_v3/240401_194322'
   if args.dataset == 'data' and args.run == '2023C-v1_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2023eraC-v1_stream1_Mini_v3/240401_194339'
   if args.dataset == 'data' and args.run == '2023C-v1_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2023eraC-v1_stream2_Mini_v3/240401_194355'
   if args.dataset == 'data' and args.run == '2023C-v1_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2023eraC-v1_stream3_Mini_v3/240401_194410'
   if args.dataset == 'data' and args.run == '2023C-v1_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2023eraC-v1_stream4_Mini_v3/240401_194427'
   if args.dataset == 'data' and args.run == '2023C-v1_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2023eraC-v1_stream5_Mini_v3/240401_194446'
   if args.dataset == 'data' and args.run == '2023C-v1_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2023eraC-v1_stream6_Mini_v3/240401_194501'
   if args.dataset == 'data' and args.run == '2023C-v1_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2023eraC-v1_stream7_Mini_v3/240401_194517'
   
   if args.dataset == 'data' and args.run == '2023C-v2_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2023eraC-v2_stream0_Mini_v3/240401_194530'
   if args.dataset == 'data' and args.run == '2023C-v2_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2023eraC-v2_stream1_Mini_v3/240401_194546'
   if args.dataset == 'data' and args.run == '2023C-v2_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2023eraC-v2_stream2_Mini_v3/240401_194602'
   if args.dataset == 'data' and args.run == '2023C-v2_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2023eraC-v2_stream3_Mini_v3/240401_194618'
   if args.dataset == 'data' and args.run == '2023C-v2_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2023eraC-v2_stream4_Mini_v3/240401_194636'
   if args.dataset == 'data' and args.run == '2023C-v2_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2023eraC-v2_stream5_Mini_v3/240401_194651'
   if args.dataset == 'data' and args.run == '2023C-v2_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2023eraC-v2_stream6_Mini_v3/240401_194707'
   if args.dataset == 'data' and args.run == '2023C-v2_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2023eraC-v2_stream7_Mini_v3/240401_194723'

   if args.dataset == 'data' and args.run == '2023C-v3_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2023eraC-v3_stream0_Mini_v3/240401_194734'
   if args.dataset == 'data' and args.run == '2023C-v3_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2023eraC-v3_stream1_Mini_v3/240401_194750'
   if args.dataset == 'data' and args.run == '2023C-v3_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2023eraC-v3_stream2_Mini_v3/240401_194807'
   if args.dataset == 'data' and args.run == '2023C-v3_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2023eraC-v3_stream3_Mini_v3/240401_194823'
   if args.dataset == 'data' and args.run == '2023C-v3_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2023eraC-v3_stream4_Mini_v3/240401_194839'
   if args.dataset == 'data' and args.run == '2023C-v3_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2023eraC-v3_stream5_Mini_v3/240401_194856'
   if args.dataset == 'data' and args.run == '2023C-v3_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2023eraC-v3_stream6_Mini_v3/240401_194914'
   if args.dataset == 'data' and args.run == '2023C-v3_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2023eraC-v3_stream7_Mini_v3/240401_194929'

   if args.dataset == 'data' and args.run == '2023C-v4_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2023eraC-v4_stream0_Mini_v3/240401_194941'
   if args.dataset == 'data' and args.run == '2023C-v4_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2023eraC-v4_stream1_Mini_v3/240401_194956'
   if args.dataset == 'data' and args.run == '2023C-v4_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2023eraC-v4_stream2_Mini_v3/240401_195012'
   if args.dataset == 'data' and args.run == '2023C-v4_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2023eraC-v4_stream3_Mini_v3/240401_195027'
   if args.dataset == 'data' and args.run == '2023C-v4_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2023eraC-v4_stream4_Mini_v3/240401_210225'
   if args.dataset == 'data' and args.run == '2023C-v4_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2023eraC-v4_stream5_Mini_v3/240401_195059'
   if args.dataset == 'data' and args.run == '2023C-v4_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2023eraC-v4_stream6_Mini_v3/240401_195115'
   if args.dataset == 'data' and args.run == '2023C-v4_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2023eraC-v4_stream7_Mini_v3/240401_195130'

   if args.dataset == 'data' and args.run == '2023D-v1_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2023eraD-v1_stream0_Mini_v3/240401_195143'
   if args.dataset == 'data' and args.run == '2023D-v1_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2023eraD-v1_stream1_Mini_v3/240401_195158'
   if args.dataset == 'data' and args.run == '2023D-v1_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2023eraD-v1_stream2_Mini_v3/240401_195220'
   if args.dataset == 'data' and args.run == '2023D-v1_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2023eraD-v1_stream3_Mini_v3/240401_195236'
   if args.dataset == 'data' and args.run == '2023D-v1_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2023eraD-v1_stream4_Mini_v3/240401_195252'
   if args.dataset == 'data' and args.run == '2023D-v1_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2023eraD-v1_stream5_Mini_v3/240401_195308'
   if args.dataset == 'data' and args.run == '2023D-v1_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2023eraD-v1_stream6_Mini_v3/240401_195325'
   if args.dataset == 'data' and args.run == '2023D-v1_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2023eraD-v1_stream7_Mini_v3/240401_195340'

   if args.dataset == 'data' and args.run == '2023D-v2_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimTau3mu_2023eraD-v2_stream0_Mini_v3/240401_195355'
   if args.dataset == 'data' and args.run == '2023D-v2_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimTau3mu_2023eraD-v2_stream1_Mini_v3/240401_195410'
   if args.dataset == 'data' and args.run == '2023D-v2_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimTau3mu_2023eraD-v2_stream2_Mini_v3/240401_195425'
   if args.dataset == 'data' and args.run == '2023D-v2_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimTau3mu_2023eraD-v2_stream3_Mini_v3/240401_195441'
   if args.dataset == 'data' and args.run == '2023D-v2_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimTau3mu_2023eraD-v2_stream4_Mini_v3/240401_195459'
   if args.dataset == 'data' and args.run == '2023D-v2_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimTau3mu_2023eraD-v2_stream5_Mini_v3/240401_195514'
   if args.dataset == 'data' and args.run == '2023D-v2_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimTau3mu_2023eraD-v2_stream6_Mini_v3/240401_195531'
   if args.dataset == 'data' and args.run == '2023D-v2_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimTau3mu_2023eraD-v2_stream7_Mini_v3/240401_195546'


if args.anatype == 'control':
   if args.dataset == 'data_control' and args.run == '2022B':
      path = ''
   if args.dataset == 'data_control' and args.run == '2022C_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraC_stream0_Mini_v3/240204_002947'
   if args.dataset == 'data_control' and args.run == '2022C_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraC_stream1_Mini_v3/240204_003014'
   if args.dataset == 'data_control' and args.run == '2022C_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraC_stream2_Mini_v3/240204_003033'
   if args.dataset == 'data_control' and args.run == '2022C_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraC_stream3_Mini_v3/240204_003053'
   if args.dataset == 'data_control' and args.run == '2022C_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraC_stream4_Mini_v3/240204_003121'
   if args.dataset == 'data_control' and args.run == '2022C_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraC_stream5_Mini_v3/240204_003141'
   if args.dataset == 'data_control' and args.run == '2022C_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraC_stream6_Mini_v3/240204_003202'
   if args.dataset == 'data_control' and args.run == '2022C_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraC_stream7_Mini_v3/240204_003223'

   '''
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
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraD-v1_stream0_Mini_v3/240204_003244'
   if args.dataset == 'data_control' and args.run == '2022D-v1_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraD-v1_stream1_Mini_v3/240204_003307'
   if args.dataset == 'data_control' and args.run == '2022D-v1_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraD-v1_stream2_Mini_v3/240204_003331'
   if args.dataset == 'data_control' and args.run == '2022D-v1_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraD-v1_stream3_Mini_v3/240204_003358'
   if args.dataset == 'data_control' and args.run == '2022D-v1_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraD-v1_stream4_Mini_v3/240204_003419'
   if args.dataset == 'data_control' and args.run == '2022D-v1_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraD-v1_stream5_Mini_v3/240204_003441'
   if args.dataset == 'data_control' and args.run == '2022D-v1_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraD-v1_stream6_Mini_v3/240204_003506'
   if args.dataset == 'data_control' and args.run == '2022D-v1_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraD-v1_stream7_Mini_v3/240204_003532'
      
   if args.dataset == 'data_control' and args.run == '2022D-v2_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraD-v2_stream0_Mini_v3/240204_003554'
   if args.dataset == 'data_control' and args.run == '2022D-v2_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraD-v2_stream1_Mini_v3/240204_003617'
   if args.dataset == 'data_control' and args.run == '2022D-v2_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraD-v2_stream2_Mini_v3/240204_003641'
   if args.dataset == 'data_control' and args.run == '2022D-v2_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraD-v2_stream3_Mini_v3/240204_003713'
   if args.dataset == 'data_control' and args.run == '2022D-v2_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraD-v2_stream4_Mini_v3/240204_003741'
   if args.dataset == 'data_control' and args.run == '2022D-v2_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraD-v2_stream5_Mini_v3/240204_003803'
   if args.dataset == 'data_control' and args.run == '2022D-v2_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraD-v2_stream6_Mini_v3/240204_003826'
   if args.dataset == 'data_control' and args.run == '2022D-v2_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraD-v2_stream7_Mini_v3/240204_003849'
   
   if args.dataset == 'data_control' and args.run == '2022E_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraE_stream0_Mini_v3/240204_003910'
   if args.dataset == 'data_control' and args.run == '2022E_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraE_stream1_Mini_v3/240204_003934'
   if args.dataset == 'data_control' and args.run == '2022E_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraE_stream2_Mini_v3/240204_003956'
   if args.dataset == 'data_control' and args.run == '2022E_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraE_stream3_Mini_v3/240204_004018'
   if args.dataset == 'data_control' and args.run == '2022E_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraE_stream4_Mini_v3/240204_004043'
   if args.dataset == 'data_control' and args.run == '2022E_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraE_stream5_Mini_v3/240204_004110'
   if args.dataset == 'data_control' and args.run == '2022E_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraE_stream6_Mini_v3/240204_004134'
   if args.dataset == 'data_control' and args.run == '2022E_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraE_stream7_Mini_v3/240204_004156'
      
   if args.dataset == 'data_control' and args.run == '2022F_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraF_stream0_Mini_v3/240203_235432'
   if args.dataset == 'data_control' and args.run == '2022F_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraF_stream1_Mini_v3/240203_235455'
   if args.dataset == 'data_control' and args.run == '2022F_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraF_stream2_Mini_v3/240203_235519'
   if args.dataset == 'data_control' and args.run == '2022F_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraF_stream3_Mini_v3/240203_235539'
   if args.dataset == 'data_control' and args.run == '2022F_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraF_stream4_Mini_v3/240203_235559'
   if args.dataset == 'data_control' and args.run == '2022F_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraF_stream5_Mini_v3/240203_235620'
   if args.dataset == 'data_control' and args.run == '2022F_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraF_stream6_Mini_v3/240203_235643'
   if args.dataset == 'data_control' and args.run == '2022F_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraF_stream7_Mini_v3/240203_235704'
      
   if args.dataset == 'data_control' and args.run == '2022G_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2022eraG_stream0_Mini_v3/240203_235721'
   if args.dataset == 'data_control' and args.run == '2022G_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2022eraG_stream1_Mini_v3/240203_235740'
   if args.dataset == 'data_control' and args.run == '2022G_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2022eraG_stream2_Mini_v3/240203_235800'
   if args.dataset == 'data_control' and args.run == '2022G_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2022eraG_stream3_Mini_v3/240203_235821'
   if args.dataset == 'data_control' and args.run == '2022G_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2022eraG_stream4_Mini_v3/240203_235847'
   if args.dataset == 'data_control' and args.run == '2022G_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2022eraG_stream5_Mini_v3/240203_235906'
   if args.dataset == 'data_control' and args.run == '2022G_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2022eraG_stream6_Mini_v3/240203_235926'
   if args.dataset == 'data_control' and args.run == '2022G_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2022eraG_stream7_Mini_v3/240203_235946'

   if args.dataset == 'data_control' and args.run == '2023B_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraB_stream0_Mini_v3/240313_095027'
   if args.dataset == 'data_control' and args.run == '2023B_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraB_stream1_Mini_v3/240313_095042'
   if args.dataset == 'data_control' and args.run == '2023B_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraB_stream2_Mini_v3/240313_095057'
   if args.dataset == 'data_control' and args.run == '2023B_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraB_stream3_Mini_v3/240313_095112'
   if args.dataset == 'data_control' and args.run == '2023B_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraB_stream4_Mini_v3/240313_095128'
   if args.dataset == 'data_control' and args.run == '2023B_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraB_stream5_Mini_v3/240313_095143'
   if args.dataset == 'data_control' and args.run == '2023B_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraB_stream6_Mini_v3/240313_095157'
   if args.dataset == 'data_control' and args.run == '2023B_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraB_stream7_Mini_v3/240313_095212'

   if args.dataset == 'data_control' and args.run == '2023C-v1_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraC-v1_stream0_Mini_v3/240313_095224'
   if args.dataset == 'data_control' and args.run == '2023C-v1_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraC-v1_stream1_Mini_v3/240313_095239'
   if args.dataset == 'data_control' and args.run == '2023C-v1_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraC-v1_stream2_Mini_v3/240313_095253'
   if args.dataset == 'data_control' and args.run == '2023C-v1_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraC-v1_stream3_Mini_v3/240313_095308'
   if args.dataset == 'data_control' and args.run == '2023C-v1_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraC-v1_stream4_Mini_v3/240313_095322'
   if args.dataset == 'data_control' and args.run == '2023C-v1_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraC-v1_stream5_Mini_v3/240313_095337'
   if args.dataset == 'data_control' and args.run == '2023C-v1_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraC-v1_stream6_Mini_v3/240313_095351'
   if args.dataset == 'data_control' and args.run == '2023C-v1_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraC-v1_stream7_Mini_v3/240313_095405'
   
   if args.dataset == 'data_control' and args.run == '2023C-v2_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraC-v2_stream0_Mini_v3/240313_095416'
   if args.dataset == 'data_control' and args.run == '2023C-v2_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraC-v2_stream1_Mini_v3/240313_095430'
   if args.dataset == 'data_control' and args.run == '2023C-v2_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraC-v2_stream2_Mini_v3/240313_095444'
   if args.dataset == 'data_control' and args.run == '2023C-v2_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraC-v2_stream3_Mini_v3/240313_095458'
   if args.dataset == 'data_control' and args.run == '2023C-v2_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraC-v2_stream4_Mini_v3/240313_095513'
   if args.dataset == 'data_control' and args.run == '2023C-v2_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraC-v2_stream5_Mini_v3/240313_095527'
   if args.dataset == 'data_control' and args.run == '2023C-v2_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraC-v2_stream6_Mini_v3/240313_095541'
   if args.dataset == 'data_control' and args.run == '2023C-v2_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraC-v2_stream7_Mini_v3/240313_095556'

   if args.dataset == 'data_control' and args.run == '2023C-v3_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraC-v3_stream0_Mini_v3/240313_095606'
   if args.dataset == 'data_control' and args.run == '2023C-v3_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraC-v3_stream1_Mini_v3/240313_095621'
   if args.dataset == 'data_control' and args.run == '2023C-v3_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraC-v3_stream2_Mini_v3/240313_095635'
   if args.dataset == 'data_control' and args.run == '2023C-v3_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraC-v3_stream3_Mini_v3/240313_095650'
   if args.dataset == 'data_control' and args.run == '2023C-v3_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraC-v3_stream4_Mini_v3/240313_095705'
   if args.dataset == 'data_control' and args.run == '2023C-v3_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraC-v3_stream5_Mini_v3/240313_095720'
   if args.dataset == 'data_control' and args.run == '2023C-v3_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraC-v3_stream6_Mini_v3/240313_095735'
   if args.dataset == 'data_control' and args.run == '2023C-v3_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraC-v3_stream7_Mini_v3/240313_095750'

   if args.dataset == 'data_control' and args.run == '2023C-v4_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraC-v4_stream0_Mini_v3/240313_095800'
   if args.dataset == 'data_control' and args.run == '2023C-v4_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraC-v4_stream1_Mini_v3/240313_095816'
   if args.dataset == 'data_control' and args.run == '2023C-v4_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraC-v4_stream2_Mini_v3/240313_095830'
   if args.dataset == 'data_control' and args.run == '2023C-v4_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraC-v4_stream3_Mini_v3/240313_095845'
   if args.dataset == 'data_control' and args.run == '2023C-v4_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraC-v4_stream4_Mini_v3/240313_095900'
   if args.dataset == 'data_control' and args.run == '2023C-v4_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraC-v4_stream5_Mini_v3/240313_095914'
   if args.dataset == 'data_control' and args.run == '2023C-v4_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraC-v4_stream6_Mini_v3/240313_095929'
   if args.dataset == 'data_control' and args.run == '2023C-v4_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraC-v4_stream7_Mini_v3/240313_095944'

   if args.dataset == 'data_control' and args.run == '2023D-v1_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraD-v1_stream0_Mini_v3/240313_095956'
   if args.dataset == 'data_control' and args.run == '2023D-v1_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraD-v1_stream1_Mini_v3/240313_100012'
   if args.dataset == 'data_control' and args.run == '2023D-v1_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraD-v1_stream2_Mini_v3/240313_100028'
   if args.dataset == 'data_control' and args.run == '2023D-v1_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraD-v1_stream3_Mini_v3/240313_100043'
   if args.dataset == 'data_control' and args.run == '2023D-v1_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraD-v1_stream4_Mini_v3/240313_100059'
   if args.dataset == 'data_control' and args.run == '2023D-v1_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraD-v1_stream5_Mini_v3/240313_100115'
   if args.dataset == 'data_control' and args.run == '2023D-v1_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraD-v1_stream6_Mini_v3/240313_100130'
   if args.dataset == 'data_control' and args.run == '2023D-v1_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraD-v1_stream7_Mini_v3/240313_100153'

   if args.dataset == 'data_control' and args.run == '2023D-v2_0':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass0/SkimDsPhiPi_2023eraD-v2_stream0_Mini_v3/240313_100205'
   if args.dataset == 'data_control' and args.run == '2023D-v2_1':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass1/SkimDsPhiPi_2023eraD-v2_stream1_Mini_v3/240313_100222'
   if args.dataset == 'data_control' and args.run == '2023D-v2_2':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass2/SkimDsPhiPi_2023eraD-v2_stream2_Mini_v3/240313_100237'
   if args.dataset == 'data_control' and args.run == '2023D-v2_3':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass3/SkimDsPhiPi_2023eraD-v2_stream3_Mini_v3/240313_100252'
   if args.dataset == 'data_control' and args.run == '2023D-v2_4':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass4/SkimDsPhiPi_2023eraD-v2_stream4_Mini_v3/240313_100309'
   if args.dataset == 'data_control' and args.run == '2023D-v2_5':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass5/SkimDsPhiPi_2023eraD-v2_stream5_Mini_v3/240313_100324'
   if args.dataset == 'data_control' and args.run == '2023D-v2_6':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass6/SkimDsPhiPi_2023eraD-v2_stream6_Mini_v3/240313_100339'
   if args.dataset == 'data_control' and args.run == '2023D-v2_7':
      path = '/lustre/cms/store/user/mbuonsan/ParkingDoubleMuonLowMass7/SkimDsPhiPi_2023eraD-v2_stream7_Mini_v3/240313_100354'

if args.dataset == 'MC' and args.MCprocess == 'Ds_preE':
   path = '/lustre/cms/store/user/mbuonsan/DstoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Ds_new_Mini_preE/240401_200539'
if args.dataset == 'MC' and args.MCprocess == 'Ds_postE':
   path = '/lustre/cms/store/user/mbuonsan/DstoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Ds_new_Mini_postE/240401_200612'
if args.dataset == 'MC' and args.MCprocess == 'Bp_preE':
   path = '/lustre/cms/store/user/mbuonsan/ButoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bu_Mini_preE/240401_200522'
if args.dataset == 'MC' and args.MCprocess == 'Bp_postE':
   path = '/lustre/cms/store/user/mbuonsan/ButoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bu_Mini_postE/240401_200556'
if args.dataset == 'MC' and args.MCprocess == 'B0_preE':
   path = '/lustre/cms/store/user/mbuonsan/BdtoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bd_Mini_preE/240401_200505'
if args.dataset == 'MC' and args.MCprocess == 'B0_postE':
   path = '/lustre/cms/store/user/mbuonsan/BdtoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MCRun3_Bd_Mini_postE/240401_200447'
if args.dataset == 'MC' and args.MCprocess == 'DsPhiMuNu':
   path = '/lustre/cms/store/user/caruta/Pythia8_DsPhiMuNu_Run3_2022/SkimTau3mu_MCRun3_DsPhiMuNu_Mini_v4/230114_172745'
if args.dataset == 'MC' and args.MCprocess == 'DsPhiPi_preE':
   path = '/lustre/cms/store/user/mbuonsan/DstoPhiPi_Phito2Mu_MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimPhiPi_MCRun3_Mini_preE/231128_103303'
if args.dataset == 'MC' and args.MCprocess == 'DsPhiPi_postE':
   path = '/lustre/cms/store/user/mbuonsan/DstoPhiPi_Phito2Mu_MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimPhiPi_MCRun3_Mini_postE/231128_103225'
if args.dataset == 'MC' and args.MCprocess == 'Ds_2018':
   path = '/lustre/cms/store/user/fsimone/DsToTau_To3Mu_MuFilter_TuneCP5_13TeV-pythia8-evtgen/SkimTau3Mu_Summer20UL18_DsTau3Muv2_yesHLT_forSynch/240202_190214'

if args.dataset == 'MC' and args.MCprocess == 'Ds_preBPix':
   path = '/lustre/cms/store/user/mbuonsan/DstoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MC_23_Run3_Ds_new_Mini_preBPix/240401_200756'
if args.dataset == 'MC' and args.MCprocess == 'Ds_postBPix':
   path = '/lustre/cms/store/user/mbuonsan/DstoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MC_23_Run3_Ds_new_Mini_postBPix/240401_200828'
if args.dataset == 'MC' and args.MCprocess == 'Bp_preBPix':
   path = '/lustre/cms/store/user/mbuonsan/ButoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MC_23_Run3_Bu_Mini_preBPix/240401_200740'
if args.dataset == 'MC' and args.MCprocess == 'Bp_postBPix':
   path = '/lustre/cms/store/user/mbuonsan/ButoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MC_23_Run3_Bu_Mini_postBPix/240401_204434'
if args.dataset == 'MC' and args.MCprocess == 'B0_preBPix':
   path = '/lustre/cms/store/user/mbuonsan/BdtoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MC_23_Run3_Bd_Mini_preBPix/240401_200723'
if args.dataset == 'MC' and args.MCprocess == 'B0_postBPix':
   path = '/lustre/cms/store/user/mbuonsan/BdtoTau_Tauto3Mu_3MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimTau3mu_MC_23_Run3_Bd_Mini_postBPix/240401_200705'
if args.dataset == 'MC' and args.MCprocess == 'DsPhiPi_preBPix':
   path = '/lustre/cms/store/user/mbuonsan/DstoPhiPi_Phito2Mu_MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimPhiPi_MC_23_Run3_Mini_preBPix/240313_093123'
if args.dataset == 'MC' and args.MCprocess == 'DsPhiPi_postBPix':
   path = '/lustre/cms/store/user/mbuonsan/DstoPhiPi_Phito2Mu_MuFilter_TuneCP5_13p6TeV_pythia8-evtgen/SkimPhiPi_MC_23_Run3_Mini_postBPix/240313_092943'



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
