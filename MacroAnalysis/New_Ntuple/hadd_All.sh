echo "Unisco segnale:"
rm All_Data.root
hadd -f All_Data.root *tau3mu.root
echo "Unisco control:"
rm All_Control.root
hadd -f All_Control.root *control.root 
echo "Invio Cern Box:"
scp All_Data.root All_Control.root mbuonsan@lxplus.cern.ch:/eos/user/m/mbuonsan/Tau3mu_2023/File_BDT
