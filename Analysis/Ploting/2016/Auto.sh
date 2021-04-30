
cmsenv
target='/wk_cms2/arthur6745/env/CMSSW_9_4_13/src/TopQuarkAnalysis/MyFCNCkit/test/research_progress/roofit/CR/sample/2016_Zut/'

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


root -q -b mkplots_summary_DM.C+
root -q -b mkplots_summary_DE.C+
hadd -f $target${Syst[0]}/Zmass_combine.root $target${Syst[0]}/hist_Zmass_*

for ((i=0; i<${#Syst[@]}; i++)) 
do
    sed -i "s/${Syst[$i]}/${Syst[$i+1]}/g" ./mkplots_summary_DM.C
    sed -i "s/${Syst[$i]}/${Syst[$i+1]}/g" ./mkplots_summary_DE.C 
    root -q -b mkplots_summary_DM.C+
    root -q -b mkplots_summary_DE.C+
    hadd -f $target${Syst[$i+1]}/Zmass_combine.root $target${Syst[$i+1]}/hist_Zmass_*
done

