{    
  //Reset ROOT    
  gROOT->Reset();    

  gSystem->Load("libJetMETCorrectionsJetCorrector.so");
  gSystem->Load("libJetMETCorrectionsAlgorithms.so");
  gSystem->Load("libJetMETCorrectionsObjects.so");
  gSystem->Load("libJetMETCorrectionsModules.so");
  gSystem->Load("libCondFormatsBTauObjects.so");
  //gROOT->LoadMacro("MyTcZAna.C+");    
 
  // Create a chain of files. The parameter to the TChain constructor    
  // is the name of the Tree to be processed in each file of the chain.    
  TChain chain("fcncKit/root");    

  chain.Add("/wk_cms/arthur6745/Data/CRABdata/Data_File_2016/Double_mu_2016B/*");

  TFile *EG_SF = TFile::Open("./ScaleFactor/2016/2016LegacyReReco_ElectronTight_Fall17V2.root");
  TH2D *h_ele_Eff = (TH2D*)EG_SF->Get("EGamma_SF2D");
  TFile *EG_Reco_SF = TFile::Open("./ScaleFactor/2016/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root");
  TH2D *h_ele_Reco = (TH2D*)EG_Reco_SF->Get("EGamma_SF2D");
  
  TFile *Muon_SF_BToF = TFile::Open("./ScaleFactor/2016/RunBCDEF_SF_ID.root");
  TH2D *h_MuonBtoF_Eff = (TH2D*)Muon_SF_BToF->Get("NUM_TightID_DEN_genTracks_eta_pt");
  TFile *Muon_SF_GH = TFile::Open("./ScaleFactor/2016/RunGH_SF_ID.root");
  TH2D *h_MuonGH_Eff = (TH2D*)Muon_SF_GH->Get("NUM_TightID_DEN_genTracks_eta_pt");

  TFile *Muon_SF_BToF_ISO = TFile::Open("./ScaleFactor/2016/RunBCDEF_SF_ISO.root");
  TH2D *h_MuonBtoF_Eff_ISO = (TH2D*)Muon_SF_BToF_ISO->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");
  TFile *Muon_SF_GH_ISO = TFile::Open("./ScaleFactor/2016/RunGH_SF_ISO.root");
  TH2D *h_MuonGH_Eff_ISO = (TH2D*)Muon_SF_GH_ISO->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");

  TFile *PU_SF = TFile::Open("./ScaleFactor/2016/PileupSF.root");
  TH1D *h_PU_SF = (TH1D*)PU_SF->Get("Scale_Factor");

  TFile *hfile = new TFile("./Result_run_fcnc_files_2016/data_double_mu_RunB.root","RECREATE","Ttbar-fcnc-Signal");

  chain.Process("./MyTcZAna_2016.C", "a=b,test;test2");
  hfile->Write();    
}    
