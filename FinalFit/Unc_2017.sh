
cmsenv
Syst=("Central"
      "ElecID_up" "ElecID_down"
      "ElecReco_up" "ElecReco_down"
      "JEC_up" "JEC_down"
      "JER_up" "JER_down"
      "MuonID_up" "MuonID_down"
      "MuonIso_up" "MuonIso_down"
      "cferr1_up" "cferr1_down"
      "cferr2_up" "cferr2_down"
      "hf_up" "hf_down"
      "hfstats1_up" "hfstats1_down"
      "hfstats2_up" "hfstats2_down"
      "jes_up" "jes_down"
      "lf_up" "lf_down"
      "lfstats1_up" "lfstats1_down"
      "lfstats2_up" "lfstats2_down"
      "pileup_up" "pileup_down")

root -l -q 2017_Summary_mmm.cc > ./Record/2017_Zut/Central/mmm.log
root -l -q 2017_Summary_mme.cc > ./Record/2017_Zut/Central/mme.log
root -l -q 2017_Summary_mee.cc > ./Record/2017_Zut/Central/mee.log
root -l -q 2017_Summary_eee.cc > ./Record/2017_Zut/Central/eee.log

for ((i=0; i<${#Syst[@]}; i++))
do
    sed -i "s/${Syst[$i]}/${Syst[$i+1]}/g" ./2017_Summary_*
    root -l -q 2017_Summary_mmm.cc > ./Record/2017_Zut/${Syst[$i+1]}/mmm.log
    root -l -q 2017_Summary_mme.cc > ./Record/2017_Zut/${Syst[$i+1]}/mme.log
    root -l -q 2017_Summary_mee.cc > ./Record/2017_Zut/${Syst[$i+1]}/mee.log
    root -l -q 2017_Summary_eee.cc > ./Record/2017_Zut/${Syst[$i+1]}/eee.log
done

