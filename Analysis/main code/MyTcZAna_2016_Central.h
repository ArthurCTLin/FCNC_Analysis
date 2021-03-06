#ifndef MyTcZAna_2016_Central_h
#define MyTcZAna_2016_Central_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
// Headers needed by this particular selector

#include <TH1.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TLorentzVector.h>

#define MAX_LEPTONS     256
#define MAX_JETS        128
#define MAX_GENS        512
#define MAX_BX          128
#define MAX_Vertices    256

#include "TMVA/TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#endif

#define N_TRIGGER_BOOKINGS      4086//5792

#define MAX_TRACKS      256
#define MAX_PAIRS       512
#define MAX_PHOTONS     64


std::string  vtx_cut_label[] = {"All", "Type", "Valid", "nDoF", "pT_sum",
                                "abs_Z", "Rho"};
std::string  evt_cut_label[] = {"All  ","HLTrig", "Vertex", "3_lep", "one_Z",
                                "2_jet", "1_bjet", "MissET", "one_W_Z",
                                "2_Top", "Mass_cZ", "Mass_bW",
                                "GEN_match", "0_b-tag", "2_b-tag"};
std::string  ele_cut_label[] = {"All", "GEN", "pT", "Eta", "conv", "vLoose",
                                "Medium", "Tight", "GEN"};
std::string  mu_cut_label[] = {"All", "global", "tracker", "pT", "Eta","pf_iso",
                               "track_hits", "track_dxy", "global_chi2",
                               "pixel_layer", "matches", "hits", "trk_iso"
                               "GEN", "rel_iso", "GEN"};
std::string  jet_cut_label[] = {"All", "GEN", "pT", "Eta", "JetID", "LepIso",
                                "GEN", "BTAG", "GEN"};

// Header file for the classes stored in the TTree if any.

class MyTcZAna_2016_Central : public TSelector {
private :
   TTree          *mvaTree;  // pointer to mva tree export
   TTree          *FullCut;

public :

   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   TMVA::Reader *readerOCPE;
   TMVA::Reader *sorting;

   Double_t      Event_Weight;
   Double_t      Btag_weight;
   Double_t      Event_Weight_Tot;
   Int_t      Event_Tot;
   
   int m_vtx_no;
   int m_e_no;
   int m_m_no;
   int m_te_no;
   int m_tm_no;
   int m_z_no;
   int m_tz_no;

   int m_z_no_m;
   int m_z_no_e;
   int m_tz_no_m;
   int m_tz_no_e;
   
   int m_w_no_m;
   int m_w_no_e;

   int m_w_idx=-1;
   int m_z_idx=-1;

   int m_jet_no=0;
   int m_bjet_no=0;
   int m_cbjet_no=0;

   int m_top_comb = 0;

   int m_gen_zee_idx=-1;
   int m_gen_wuu_idx=-1;

   int m_gen_top1_idx=-1;
   int m_gen_top2_idx=-1;
   int m_top1_idx=-1;
   int m_top2_idx=-1;
   int m_top1b_idx=-1;
   int m_top2b_idx=-1;

   int m_gen_lep1_idx=-1;
   int m_gen_lep2_idx=-1;
   int m_gen_lep3_idx=-1;
   int m_gen_lep4_idx=-1;
   int m_gen_jet1_idx=-1;
   int m_gen_jet2_idx=-1;

   int new_e_no;
   int new_mu_no;
   double m_ht;
   double m_st;
   int nPU; 
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Int_t> EvtInfo_RunNo = {fReader, "EvtInfo.RunNo"};
   TTreeReaderValue<Int_t> EvtInfo_EvtNo = {fReader, "EvtInfo.EvtNo"};
   TTreeReaderValue<Int_t> EvtInfo_BxNo = {fReader, "EvtInfo.BxNo"};
   TTreeReaderValue<Int_t> EvtInfo_LumiNo = {fReader, "EvtInfo.LumiNo"};
   TTreeReaderValue<Int_t> EvtInfo_McFlag = {fReader, "EvtInfo.McFlag"};
   TTreeReaderValue<Int_t> EvtInfo_PDFid1 = {fReader, "EvtInfo.PDFid1"};
   TTreeReaderValue<Int_t> EvtInfo_PDFid2 = {fReader, "EvtInfo.PDFid2"};
   TTreeReaderValue<Float_t> EvtInfo_PDFx1 = {fReader, "EvtInfo.PDFx1"};
   TTreeReaderValue<Float_t> EvtInfo_RhoPU = {fReader, "EvtInfo.RhoPU"};
   TTreeReaderValue<Float_t> EvtInfo_SigmaPU = {fReader, "EvtInfo.SigmaPU"};
   TTreeReaderValue<Float_t> EvtInfo_MET = {fReader, "EvtInfo.MET"};
   TTreeReaderValue<Float_t> EvtInfo_METx = {fReader, "EvtInfo.METx"};
   TTreeReaderValue<Float_t> EvtInfo_METy = {fReader, "EvtInfo.METy"};
   TTreeReaderValue<Float_t> EvtInfo_METPhi = {fReader, "EvtInfo.METPhi"};
   TTreeReaderValue<Float_t> EvtInfo_RawMET = {fReader, "EvtInfo.RawMET"};
   TTreeReaderValue<Float_t> EvtInfo_RawMETPhi = {fReader, "EvtInfo.RawMETPhi"};
   TTreeReaderValue<Float_t> EvtInfo_SumEt = {fReader, "EvtInfo.SumEt"};
   TTreeReaderValue<Float_t> EvtInfo_METSig = {fReader, "EvtInfo.METSig"};
   TTreeReaderValue<Float_t> EvtInfo_GenMET = {fReader, "EvtInfo.GenMET"};
   TTreeReaderValue<Float_t> EvtInfo_GenMETPhi = {fReader, "EvtInfo.GenMETPhi"};
   TTreeReaderValue<Float_t> EvtInfo_Weight = {fReader, "EvtInfo.Weight"};
   TTreeReaderValue<Int_t> EvtInfo_TrgCount = {fReader, "EvtInfo.TrgCount"};
   TTreeReaderValue<Int_t> EvtInfo_nBooking = {fReader, "EvtInfo.nBooking"};
   TTreeReaderArray<Char_t> EvtInfo_TrgBook = {fReader, "EvtInfo.TrgBook"};
   TTreeReaderValue<Int_t> EvtInfo_NofTracks = {fReader, "EvtInfo.NofTracks"};
   TTreeReaderValue<Int_t> EvtInfo_nHLT = {fReader, "EvtInfo.nHLT"};
   TTreeReaderArray<Bool_t> EvtInfo_HLTbits = {fReader, "EvtInfo.HLTbits"};
   TTreeReaderValue<Int_t> EvtInfo_nBX = {fReader, "EvtInfo.nBX"};
   TTreeReaderArray<Int_t> EvtInfo_nPU = {fReader, "EvtInfo.nPU"};
   TTreeReaderArray<Int_t> EvtInfo_nTPU = {fReader, "EvtInfo.nTPU"};
   TTreeReaderArray<Int_t> EvtInfo_BXPU = {fReader, "EvtInfo.BXPU"};
   TTreeReaderValue<Float_t> EvtInfo_rhoIso = {fReader, "EvtInfo.rhoIso"};
   TTreeReaderValue<Int_t> GenParts_Size = {fReader, "GenParts.Size"};
   TTreeReaderArray<Int_t> GenParts_Index = {fReader, "GenParts.Index"};
   TTreeReaderArray<Float_t> GenParts_Pt = {fReader, "GenParts.Pt"};
   TTreeReaderArray<Float_t> GenParts_Eta = {fReader, "GenParts.Eta"};
   TTreeReaderArray<Float_t> GenParts_Phi = {fReader, "GenParts.Phi"};
   TTreeReaderArray<Float_t> GenParts_Mass = {fReader, "GenParts.Mass"};
   TTreeReaderArray<Int_t> GenParts_PdgID = {fReader, "GenParts.PdgID"};
   TTreeReaderArray<Int_t> GenParts_Status = {fReader, "GenParts.Status"};
   TTreeReaderArray<Int_t> GenParts_nMo = {fReader, "GenParts.nMo"};
   TTreeReaderArray<Int_t> GenParts_nDa = {fReader, "GenParts.nDa"};
   TTreeReaderArray<Int_t> GenParts_Mo1 = {fReader, "GenParts.Mo1"};
   TTreeReaderArray<Int_t> GenParts_Mo2 = {fReader, "GenParts.Mo2"};
   TTreeReaderArray<Int_t> GenParts_Da1 = {fReader, "GenParts.Da1"};
   TTreeReaderArray<Int_t> GenParts_Da2 = {fReader, "GenParts.Da2"};
   TTreeReaderValue<Int_t> Leptons_Size = {fReader, "Leptons.Size"};
   TTreeReaderArray<Int_t> Leptons_Index = {fReader, "Leptons.Index"};
   TTreeReaderArray<Int_t> Leptons_Type = {fReader, "Leptons.Type"};
   TTreeReaderArray<Int_t> Leptons_Charge = {fReader, "Leptons.Charge"};
   TTreeReaderArray<Float_t> Leptons_Pt = {fReader, "Leptons.Pt"};
   TTreeReaderArray<Float_t> Leptons_Et = {fReader, "Leptons.Et"};
   TTreeReaderArray<Float_t> Leptons_Eta = {fReader, "Leptons.Eta"};
   TTreeReaderArray<Float_t> Leptons_caloEta = {fReader, "Leptons.caloEta"};
   TTreeReaderArray<Float_t> Leptons_Phi = {fReader, "Leptons.Phi"};
   TTreeReaderArray<Float_t> Leptons_TrackIso = {fReader, "Leptons.TrackIso"};
   TTreeReaderArray<Float_t> Leptons_chargedIso = {fReader, "Leptons.chargedIso"};
   TTreeReaderArray<Float_t> Leptons_neutralIso = {fReader, "Leptons.neutralIso"};
   TTreeReaderArray<Float_t> Leptons_photonIso = {fReader, "Leptons.photonIso"};
   TTreeReaderArray<Float_t> Leptons_ChargedHadronIsoR04 = {fReader, "Leptons.ChargedHadronIsoR04"};
   TTreeReaderArray<Float_t> Leptons_NeutralHadronIsoR04 = {fReader, "Leptons.NeutralHadronIsoR04"};
   TTreeReaderArray<Float_t> Leptons_PhotonIsoR04 = {fReader, "Leptons.PhotonIsoR04"};
   TTreeReaderArray<Float_t> Leptons_sumPUPtR04 = {fReader, "Leptons.sumPUPtR04"};
   TTreeReaderArray<Float_t> Leptons_Px = {fReader, "Leptons.Px"};
   TTreeReaderArray<Float_t> Leptons_Py = {fReader, "Leptons.Py"};
   TTreeReaderArray<Float_t> Leptons_Pz = {fReader, "Leptons.Pz"};
   TTreeReaderArray<Float_t> Leptons_Energy = {fReader, "Leptons.Energy"};
   TTreeReaderArray<Float_t> Leptons_vertexZ = {fReader, "Leptons.vertexZ"};
   TTreeReaderArray<Float_t> Leptons_ElTrackD0 = {fReader, "Leptons.ElTrackD0"};
   TTreeReaderArray<Float_t> Leptons_ElTrackDxy_BS = {fReader, "Leptons.ElTrackDxy_BS"};
   TTreeReaderArray<Float_t> Leptons_ElTrackDxy_PV = {fReader, "Leptons.ElTrackDxy_PV"};
   TTreeReaderArray<Float_t> Leptons_ElTrackDxy_PVBS = {fReader, "Leptons.ElTrackDxy_PVBS"};
   TTreeReaderArray<Int_t> Leptons_eidVeryLooseMC = {fReader, "Leptons.eidVeryLooseMC"};
   TTreeReaderArray<Int_t> Leptons_eidLooseMC = {fReader, "Leptons.eidLooseMC"};
   TTreeReaderArray<Int_t> Leptons_eidMediumMC = {fReader, "Leptons.eidMediumMC"};
   TTreeReaderArray<Int_t> Leptons_eidTightMC = {fReader, "Leptons.eidTightMC"};
   TTreeReaderArray<Int_t> Leptons_MuType = {fReader, "Leptons.MuType"};
   TTreeReaderArray<Float_t> Leptons_GenPt = {fReader, "Leptons.GenPt"};
   TTreeReaderArray<Float_t> Leptons_GenEta = {fReader, "Leptons.GenEta"};
   TTreeReaderArray<Float_t> Leptons_GenPhi = {fReader, "Leptons.GenPhi"};
   TTreeReaderArray<Int_t> Leptons_GenPdgID = {fReader, "Leptons.GenPdgID"};
   TTreeReaderArray<Int_t> Leptons_GenMCTag = {fReader, "Leptons.GenMCTag"};
   TTreeReaderArray<Float_t> Leptons_TrgPt = {fReader, "Leptons.TrgPt"};
   TTreeReaderArray<Float_t> Leptons_TrgEta = {fReader, "Leptons.TrgEta"};
   TTreeReaderArray<Float_t> Leptons_TrgPhi = {fReader, "Leptons.TrgPhi"};
   TTreeReaderArray<Int_t> Leptons_TrgID = {fReader, "Leptons.TrgID"};
   TTreeReaderArray<Bool_t> Leptons_ElepassConversionVeto = {fReader, "Leptons.ElepassConversionVeto"};
   TTreeReaderArray<Float_t> Leptons_ElesuperClusterEta = {fReader, "Leptons.ElesuperClusterEta"};
   TTreeReaderArray<Float_t> Leptons_ElemvaTrigV0 = {fReader, "Leptons.ElemvaTrigV0"};
   TTreeReaderArray<Float_t> Leptons_EletrackMomentumAtVtxp = {fReader, "Leptons.EletrackMomentumAtVtxp"};
   TTreeReaderArray<Float_t> Leptons_EleecalEnergy = {fReader, "Leptons.EleecalEnergy"};
   TTreeReaderArray<Float_t> Leptons_EleeSuperClusterOverP = {fReader, "Leptons.EleeSuperClusterOverP"};
   TTreeReaderArray<Float_t> Leptons_Elefbrem = {fReader, "Leptons.Elefbrem"};
   TTreeReaderArray<Float_t> Leptons_EleHoverE = {fReader, "Leptons.EleHoverE"};
   TTreeReaderArray<Float_t> Leptons_ElesigmaIetaIeta = {fReader, "Leptons.ElesigmaIetaIeta"};
   TTreeReaderArray<Float_t> Leptons_EledeltaPhiVtx = {fReader, "Leptons.EledeltaPhiVtx"};
   TTreeReaderArray<Float_t> Leptons_EledeltaEtaVtx = {fReader, "Leptons.EledeltaEtaVtx"};
   TTreeReaderArray<Int_t> Leptons_EleExpnumberOfHits = {fReader, "Leptons.EleExpnumberOfHits"};
   TTreeReaderArray<Int_t> Leptons_MuTrackerLayersWithMeasurement = {fReader, "Leptons.MuTrackerLayersWithMeasurement"};
   TTreeReaderArray<Int_t> Leptons_MunumberOfMatchedStations = {fReader, "Leptons.MunumberOfMatchedStations"};
   TTreeReaderValue<Int_t> VtxInfo_Size = {fReader, "VtxInfo.Size"};
   TTreeReaderArray<Int_t> VtxInfo_isValid = {fReader, "VtxInfo.isValid"};
   TTreeReaderArray<Bool_t> VtxInfo_isFake = {fReader, "VtxInfo.isFake"};
   TTreeReaderArray<Int_t> VtxInfo_Type = {fReader, "VtxInfo.Type"};
   TTreeReaderArray<Int_t> VtxInfo_Ndof = {fReader, "VtxInfo.Ndof"};
   TTreeReaderArray<Float_t> VtxInfo_NormalizedChi2 = {fReader, "VtxInfo.NormalizedChi2"};
   TTreeReaderArray<Float_t> VtxInfo_Pt_Sum = {fReader, "VtxInfo.Pt_Sum"};
   TTreeReaderArray<Float_t> VtxInfo_vx = {fReader, "VtxInfo.vx"};
   TTreeReaderArray<Float_t> VtxInfo_vy = {fReader, "VtxInfo.vy"};
   TTreeReaderArray<Float_t> VtxInfo_vz = {fReader, "VtxInfo.vz"};
   TTreeReaderArray<Float_t> VtxInfo_Rho = {fReader, "VtxInfo.Rho"};
   TTreeReaderValue<Int_t> Jets_Size = {fReader, "Jets.Size"};
   TTreeReaderArray<Int_t> Jets_Index = {fReader, "Jets.Index"};
   TTreeReaderArray<Int_t> Jets_NTracks = {fReader, "Jets.NTracks"};
   TTreeReaderArray<Float_t> Jets_Et = {fReader, "Jets.Et"};
   TTreeReaderArray<Float_t> Jets_Pt = {fReader, "Jets.Pt"};
   TTreeReaderArray<Float_t> Jets_Unc = {fReader, "Jets.Unc"};
   TTreeReaderArray<Float_t> Jets_Eta = {fReader, "Jets.Eta"};
   TTreeReaderArray<Float_t> Jets_Phi = {fReader, "Jets.Phi"};
   TTreeReaderArray<Int_t> Jets_NCH = {fReader, "Jets.NCH"};
   TTreeReaderArray<Float_t> Jets_CEF = {fReader, "Jets.CEF"};
   TTreeReaderArray<Float_t> Jets_NHF = {fReader, "Jets.NHF"};
   TTreeReaderArray<Float_t> Jets_NEF = {fReader, "Jets.NEF"};
   TTreeReaderArray<Float_t> Jets_CHF = {fReader, "Jets.CHF"};
   TTreeReaderArray<Int_t> Jets_JM = {fReader, "Jets.JM"};
   TTreeReaderArray<Int_t> Jets_NNH = {fReader, "Jets.NNH"};
   TTreeReaderArray<Float_t> Jets_MUF = {fReader, "Jets.MUF"};
   TTreeReaderArray<Int_t> Jets_JetIDLOOSE = {fReader, "Jets.JetIDLOOSE"};

   TTreeReaderValue<Int_t> Flag_METFilter = {fReader, "EvtInfo.Flag_METFilter"};
    TTreeReaderArray<Float_t> Jets_CombinedIncSVBJetTags = {fReader, "Jets.CombinedIncSVBJetTags"}; 
    TTreeReaderArray<Float_t> Jets_DeepCSVJetTags_probb = {fReader, "Jets.DeepCSVJetTags_probb"}; 
    TTreeReaderArray<Float_t> Jets_DeepCSVJetTags_probbb = {fReader, "Jets.DeepCSVJetTags_probbb"}; 
   TTreeReaderArray<Float_t> Jets_GenJetPt = {fReader, "Jets.GenJetPt"};
   TTreeReaderArray<Float_t> Jets_GenJetEta = {fReader, "Jets.GenJetEta"}; 
   TTreeReaderArray<Float_t> Jets_GenJetPhi = {fReader, "Jets.GenJetPhi"}; 
   TTreeReaderArray<Float_t> Jets_GenPt = {fReader, "Jets.GenPt"}; 
   TTreeReaderArray<Float_t> Jets_GenEta = {fReader, "Jets.GenEta"};
   TTreeReaderArray<Float_t> Jets_GenPhi = {fReader, "Jets.GenPhi"};
   TTreeReaderArray<Int_t> Jets_GenPdgID = {fReader, "Jets.GenPdgID"};
   TTreeReaderArray<Int_t> Jets_GenFlavor = {fReader, "Jets.GenFlavor"};
   TTreeReaderArray<Int_t> Jets_GenMCTag = {fReader, "Jets.GenMCTag"};
   TTreeReaderArray<Float_t> Jets_Px = {fReader, "Jets.Px"};
   TTreeReaderArray<Float_t> Jets_Py = {fReader, "Jets.Py"};
   TTreeReaderArray<Float_t> Jets_Pz = {fReader, "Jets.Pz"};
   TTreeReaderArray<Float_t> Jets_Energy = {fReader, "Jets.Energy"};
   TTreeReaderArray<Float_t> Jets_JERScale = {fReader, "Jets.JERScale"};
   TTreeReaderArray<Float_t> Jets_JERPt = {fReader, "Jets.JERPt"};
   TTreeReaderArray<Float_t> Jets_JERScaleUp = {fReader, "Jets.JERScaleUp"};
   TTreeReaderArray<Float_t> Jets_JERScaleDown = {fReader, "Jets.JERScaleDown"};
   TTreeReaderValue<Int_t> LHESize = {fReader, "EvtInfo.LHESize"};
   TTreeReaderValue<Float_t> LHENominalWeight = {fReader, "EvtInfo.LHENominalWeight"};
   TTreeReaderArray<Float_t> LHESystematicWeights = {fReader, "EvtInfo.LHESystematicWeights"};
   TTreeReaderArray<Float_t> Leptons_MuonCutBasedMuIdTIGHT = {fReader, "Leptons.MuonCutBasedMuIdTIGHT"};
   TTreeReaderArray<Float_t> Leptons_ElEnergyCorrFactor = {fReader, "Leptons.ElEnergyCorrFactor"};


   // Declaration of leaf types
   TLorentzVector  GenParts_P4[MAX_GENS];

   TLorentzVector  GenLepts_P4[MAX_GENS];
   Int_t           GenLepts_Size;
   Int_t           GenLepts_Index[MAX_GENS];   //[GenLepts.Size]
   Float_t         GenLepts_Pt[MAX_GENS];   //[GenLepts.Size]
   Float_t         GenLepts_Eta[MAX_GENS];   //[GenLepts.Size]
   Float_t         GenLepts_Phi[MAX_GENS];   //[GenLepts.Size]
   Float_t         GenLepts_Mass[MAX_GENS];   //[GenLepts.Size]
   Int_t           GenLepts_Type[MAX_GENS];   //[GenLepts.Size]
   Int_t           GenLepts_Charge[MAX_GENS];   //[Leptons.Size]

   TLorentzVector  Leptons_P4[MAX_LEPTONS];
   Int_t           Leptons_Good[MAX_LEPTONS];   //[Leptons.Size]
   Int_t           Leptons_GenMatch[MAX_LEPTONS];   //[Leptons.Size]
   Int_t           VtxInfo_Good[50];   //[VtxInfo.Size]

   Int_t           Jets_No;
   Double_t        Jets_HT;
   TLorentzVector  Jets_P4[20];
   TLorentzVector  Jets_P4_CSV[20];
   Int_t           Jets_Good[20];   //[Zee.No]
   Int_t           Jets_GenMatch[20];   //[Zee.No]

   Int_t           Zee_No;
   TLorentzVector  Zee_P4[64];
   Double_t        Zee_Pt[64];   //[Zee.No]
   Double_t        Zee_Eta[64];   //[Zee.No]
   Double_t        Zee_Phi[64];   //[Zee.No]
   Double_t        Zee_Px[64];   //[Zee.No]
   Double_t        Zee_Py[64];   //[Zee.No]
   Double_t        Zee_Pz[64];   //[Zee.No]
   Double_t        Zee_E[64];   //[Zee.No]
   Double_t        Zee_Mass[64];   //[Zee.No]
   Int_t           Zee_lid1[64];   //[Zee.No]
   Int_t           Zee_lid2[64];   //[Zee.No]
   Int_t           Zee_GenIdx[64];   //[Zee.No]
   Int_t           Zee_Iso[64];   //[Zee.No]
   Double_t        Zee_lpt1[64];   //[Zee.No]
   Double_t        Zee_lpt2[64];   //[Zee.No]
   Double_t        Zee_leta1[64];   //[Zee.No]
   Double_t        Zee_leta2[64];   //[Zee.No]
   Double_t        Zee_lphi1[64];   //[Zee.No]
   Double_t        Zee_lphi2[64];   //[Zee.No]
   Double_t        Zee_leid1[64];      //[Zee.No]
   Double_t        Zee_leid2[64];      //[Zee.No]
   Int_t           Z_Good[64];      //Add by Chun-Ting 2018-10-07

   Int_t           Wuu_No;
   TLorentzVector  Wuu_P4[64];
   TLorentzVector  Wjj_P4[64];
   Double_t        Wuu_Pt[64];   //[Wuu.No]
   Double_t        Wuu_Px[64];   //[Wuu.No]
   Double_t        Wuu_Py[64];   //[Wuu.No]
   Double_t        Wuu_Pz[64];   //[Wuu.No]
   Double_t        Wuu_Mt[64];   //[Wuu.No]
   Double_t        Wuu_E[64];   //[Wuu.No]
   Int_t           Wuu_lid[64];   //[Wuu.No]
   Int_t           Wuu_GenIdx[64];   //[Wuu.No]
   Int_t           Wuu_Iso[64];   //[Wuu.No]
   Double_t        Wuu_lpt[64];   //[Wuu.No]
   Double_t        Wuu_leta[64];   //[Wuu.No]
   Double_t        Wuu_lphi[64];   //[Wuu.No]
   Double_t        Wuu_ldz[64];   //[Wuu.No]
   Double_t        Wuu_ltrkiso[64];   //[Wuu.No]
   Double_t        Wuu_lecaliso[64];   //[Wuu.No]
   Double_t        Wuu_lhcaliso[64];   //[Wuu.No]
   Double_t        Wuu_lcaloiso[64];   //[Wuu.No]
   Double_t        Wuu_leid[64];   //[Wuu.No]
   Int_t           Wqq_No;
   TLorentzVector  Wqq_P4[64];
   Double_t        Wqq_Pt[64];   //[Wqq.No]
   Double_t        Wqq_Px[64];   //[Wqq.No]
   Double_t        Wqq_Py[64];   //[Wqq.No]
   Double_t        Wqq_Pz[64];   //[Wqq.No]
   Double_t        Wqq_Mt[64];   //[Wqq.No]
   Double_t        Wqq_E[64];   //[Wqq.No]
   Int_t           Wqq_jidx1[64];   //[Wuu.No]
   Int_t           Wqq_jidx2[64];   //[Wuu.No]

   Int_t           Top_No;
   TLorentzVector  Top_P4[128];
   TLorentzVector  Top_Flag_P4[128];
   TLorentzVector  Higgs_P4[128];
   TLorentzVector  Higgs_Flag_P4[128];
   TLorentzVector  LepJet_Sum_P4[64];
   Float_t  LepJet_Sum_Px[64];
   Float_t  LepJet_Sum_Py[64];
   Double_t        Top_Pt[128];   //[Top.No]
   Double_t        Top_Px[128];   //[Top.No]
   Double_t        Top_Py[128];   //[Top.No]
   Double_t        Top_Pz[128];   //[Top.No]
   Double_t        Top_Mt[128];   //[Top.No]
   Double_t        Top_E[128];   //[Top.No]
   Double_t        SF_JM[10];   //[Top.No]
   Double_t        JetEta[10];   //[Top.No]
   Int_t           Top_Type[128];   //[Top.No]
   Int_t           Top_Lidx[128];   //[Top.No]
   Int_t           Top_J1idx[128];   //[Top.No]
   Int_t           Top_J2idx[128];   //[Top.No]
   Int_t           Top_J3idx[128];   //[Top.No]
   Int_t           Top_MCTrue[128];   //[Top.No]

   Float_t         TopInfo_Pt_bw;
   Float_t         TopInfo_Pt_bw_GM;
   Float_t         TopInfo_M_bw;
   Float_t         TopInfo_M_bw_GM;
   Float_t         TopInfo_Mt_bw;
   Float_t         TopInfo_Pt_cz;
   Float_t         TopInfo_Pt_cz_GM;
   Float_t         TopInfo_M_cz;
   Float_t         TopInfo_Mt_cz;
   Float_t         TopTop_DR;
   Float_t         TopTop_dphi;
   Float_t         TopTop_dtheta;
   Int_t           TopInfo_MCTruth;

   Float_t         CJetBoost_E;
   Float_t         BJetBoost_E;
   Float_t         WInfo_Pt;
   Float_t         WInfo_Mt;
   Float_t         ZInfo_Pt;
   Float_t         ZInfo_M;

   Float_t         Z_cjet_dphi;
   Float_t         Z_bjet_dphi;
   Float_t         W_cjet_dphi;
   Float_t         W_bjet_dphi;
   Float_t         ZLLpair_dphi;
   Float_t         WLZL1_dphi;
   Float_t         WLZL2_dphi;
   Float_t         WLep_bjet_dphi;
   Float_t         ZLep1_bjet_dphi;
   Float_t         ZLep2_bjet_dphi;
   Float_t         WLep_cjet_dphi;
   Float_t         ZLep1_cjet_dphi;
   Float_t         ZLep2_cjet_dphi;

   Float_t         Z_cjet_dtheta;
   Float_t         Z_bjet_dtheta;
   Float_t         W_cjet_dtheta;
   Float_t         W_bjet_dtheta;
   Float_t         ZLLpair_dtheta;
   Float_t         WLZL1_dtheta;
   Float_t         WLZL2_dtheta;
   Float_t         WLep_bjet_dtheta;
   Float_t         ZLep1_bjet_dtheta;
   Float_t         ZLep2_bjet_dtheta;
   Float_t         WLep_cjet_dtheta;
   Float_t         ZLep1_cjet_dtheta;
   Float_t         ZLep2_cjet_dtheta;
   Float_t         MVAweight;

   Float_t         ZLLpair_DR;
   Float_t         Z_cjet_DR;
   Float_t         Z_bjet_DR;
   Float_t         W_cjet_DR;
   Float_t         W_bjet_DR;

   Float_t         BJet_btag;
   Float_t         BJet_ctag;
   Float_t         CJet_btag;
   Float_t         CJet_ctag;

   Float_t         TopTop_deta;
   Float_t         Z_cjet_deta;
   Float_t         Z_bjet_deta;
   Float_t         W_cjet_deta;
   Float_t         W_bjet_deta;
   Float_t         ZLLpair_deta;
   Float_t         WLZL1_deta;
   Float_t         WLZL2_deta;
   Float_t         WLep_bjet_deta;
   Float_t         ZLep1_bjet_deta;
   Float_t         ZLep2_bjet_deta;
   Float_t         WLep_cjet_deta;
   Float_t         ZLep1_cjet_deta;
   Float_t         ZLep2_cjet_deta;

   Int_t           jet_mva_no;
   Int_t           lep_mva_no;
   Int_t           jet_mva_event_orignal_no;
   Int_t           lep_mva_event_orignal_no;
   
   //Jets ordering check
   Int_t           jet_ordering[128];
   Int_t           Jets_new_index[128];
   Int_t           Jets_new_no;
   
   Int_t           DE_jet;
   Int_t           DM_jet;
   TLorentzVector  Leading_mu_P4[MAX_LEPTONS];
   TLorentzVector  Leading_ele_P4[MAX_LEPTONS];
   TLorentzVector  Leading_DM_Jet_P4[MAX_JETS];
   TLorentzVector  Leading_DE_Jet_P4[MAX_JETS];

   TLorentzVector Z_P4[64];
   Int_t          Z_lid1[64];
   Int_t          Z_lid2[64];
   Int_t          Z_No;
   TLorentzVector Z_tight_P4[64];
   Int_t          Z_tight_lid1[64];
   Int_t          Z_tight_lid2[64];

   TLorentzVector Leading_test_P4[MAX_LEPTONS];
   Int_t          lepton_index[MAX_LEPTONS];

   int xindex_ele;
   int yindex_ele;
   double SF_ele[MAX_LEPTONS];
   double SF_ele_Reco[MAX_LEPTONS];
   double SF_MuonID_BToF[MAX_LEPTONS];
   double SF_MuonID_GH[MAX_LEPTONS];
   double SF_MuonID[MAX_LEPTONS];
   double PUweight;

   double SF_MuonISO_BToF[MAX_LEPTONS];
   double SF_MuonISO_GH[MAX_LEPTONS];
   double SF_MuonISO[MAX_LEPTONS];
   double SF_Btag[MAX_JETS];
   int leppair;
   int el;
   int mu;
   int triggerNo;
   int postive_number;
   int negative_number;

   BTagCalibration* calib;
   BTagCalibrationReader* reader;
   JME::JetResolution* jetptres;
   JME::JetResolutionScaleFactor* resolution;
//-----------------------------adding TMVA variables---------------------------------//

   Float_t         mvaOCPE;  // check the max MVA
   Float_t         mvaOCPEt;
   Float_t         mvaOCPEmax;
   Float_t         mvaOCPE0;  // check the max top dphi
   Float_t         mvaOCPE0t;
   Float_t         mvaOCPE0max;

   //MyTcZAna_2016_Central(TTree * /*tree*/ =0) : fChain(0) { }
   MyTcZAna_2016_Central(TTree * /*tree*/ =0) { }
   virtual ~MyTcZAna_2016_Central() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();


   void     ReconElec(int);
   void     ReconMuon(int);
   void     ReconW();
   void     ReconZ();
   void     ReconJet();
   void     ReconBJet();
   void     ReconTop();
   double   SFElectronID(const TH2D*, double, double);
   double   SFElectronReco(const TH2D*, double, double);
   double   SFMuonID(const TH2D*, double, double);
   double   SFMuonISO(const TH2D*, double, double);
   double   SFPileup(const TH1D*, int);
   void     MVAFit();
   void     BtaggingInit();
   double   BtaggingSF(double, double, double, int);
   unsigned   bitconv( const float&);
   bool     IsMathched( int, double );
   double   Phi_mpi_pi( double);
   double   MakeScaled( int, double);
   double   MakeSmeared( int, double, double);
   void     InitJES(int);
   void     JERCorr(int);
   void     JERUp(int);
   void     JERDn(int);
   void     JECUp(int);
   void     JECDn(int);
   void     ElecEnergyCorr(int);
   void     SelectLepton();

   // Histograms
   TH1D *hist_evt_cut;
   TH1D *hist_evt_cut_e;
   TH1D *hist_evt_cut_m;
   TH1D *hist_evt_cut_eem;
   TH1D *hist_evt_cut_mme;
   TH1D *hist_evt_cut_eee;
   TH1D *hist_evt_cut_mmm;

   TH1D *hist_ele_cut;
   TH1D *hist_mu_cut;
   TH1D *hist_jet_cut;

   TH1D *hist_vtx_no;
   TH1D *hist_vtx_ndof;
   TH1D *hist_vtx_nx2;
   TH1D *hist_vtx_ptsum;
   TH1D *hist_vtx_z;
   TH1D *hist_vtx_rho;
   TH1D *hist_vtx_cut;

   TH1D *hist_npu;
   TH1D *hist_npu_raw;

   TH1D *hist_wen_m;
   TH1D *hist_wmn_m;
   TH1D *hist_wen_mt;
   TH1D *hist_wmn_mt;
   TH1D *hist_wen_gmt;
   TH1D *hist_wmn_gmt;

   TH1D *hist_wen_pt;
   TH1D *hist_wmn_pt;

   TH1D *hist_wen_no;
   TH1D *hist_wmn_no;

   TH1D *hist_zee_no;
   TH1D *hist_zmm_no;
   TH1D *hist_zee_m;
   TH1D *hist_zmm_m;
   TH1D *hist_zee_pt;
   TH1D *hist_zmm_pt;
   TH1D *hist_zee_m_g;
   TH1D *hist_zmm_m_g;

   TH1D *hist_e_no;
   TH1D *hist_m_no;
   TH1D *hist_lep_no;
   TH1D *hist_wz_no;

   TH1D *hist_e_pt;
   TH1D *hist_e_eta;
   TH1D *hist_e_phi;

   TH1D *hist_m_pt;
   TH1D *hist_m_eta;
   TH1D *hist_m_phi;
   TH1D *hist_m_iso;
   
   TH1D *hist_jet_eta;
   TH1D *hist_jet_phi;
   TH1D *hist_jet_btag;

   TH1D *hist_bjet_no;
   TH1D *hist_jet_no;

   TH1D *hist_met_pt;
   TH1D *hist_met_phi;
   
   TH1D *hist_top_comb;
   TH1D *hist_top_corr;
   TH1D *hist_top_corr0;

   TH1D *hist_fit_m_bw;
   TH1D *hist_fit_m_cz;
   TH1D *hist_fit_m_zee;
   TH1D *hist_fit_m_zmm;
   TH1D *hist_fit_m_wen;
   TH1D *hist_fit_m_wmn;
   TH1D *hist_fit_mt_wen;
   TH1D *hist_fit_mt_wmn;
   TH1D *hist_fit_ht;
   TH1D *hist_fit_st;

   TH1D *hist_ERc;
   TH1D *hist_ERb;

   TH1D *hist_new_jet_DE_pt;
   TH1D *hist_new_jet_DE_eta;
   TH1D *hist_new_jet_DE_phi;
   TH1D *hist_new_jet_DE_btag;
   
   TH1D *hist_new_jet_DM_pt;
   TH1D *hist_new_jet_DM_eta;
   TH1D *hist_new_jet_DM_phi;
   TH1D *hist_new_jet_DM_btag;

   TH1D *hist_new_ele_DE_pt;
   TH1D *hist_new_ele_DE_eta;
   TH1D *hist_new_ele_DE_phi;
   TH1D *hist_new_mu_DE_pt;
   TH1D *hist_new_mu_DE_eta;
   TH1D *hist_new_mu_DE_phi;
   
   TH1D *hist_new_ele_DM_pt;
   TH1D *hist_new_ele_DM_eta;
   TH1D *hist_new_ele_DM_phi;
   TH1D *hist_new_mu_DM_pt;
   TH1D *hist_new_mu_DM_eta;
   TH1D *hist_new_mu_DM_phi;

   TH1D *hist_leading_jet_DE_pt;
   TH1D *hist_leading_jet_DE_eta;
   TH1D *hist_leading_jet_DM_pt;
   TH1D *hist_leading_jet_DM_eta;
   
    TH1D *hist_vtx_no_reweight;

    TH1D *hist_mva_eee;
    TH1D *hist_mva_eem;
    TH1D *hist_mva_emm;
    TH1D *hist_mva_mmm;
    TH1D *hist_w_mt_eee;
    TH1D *hist_w_mt_eem;
    TH1D *hist_w_mt_emm;
    TH1D *hist_w_mt_mmm;
    TH1D *hist_Zmass_eee;
    TH1D *hist_Zmass_eem;
    TH1D *hist_Zmass_emm;
    TH1D *hist_Zmass_mmm;
    
    TH1D *hist_b_no;
    TH1D *hist_b_no_eee;
    TH1D *hist_b_no_eem;
    TH1D *hist_b_no_emm;
    TH1D *hist_b_no_mmm;

    TH1D *hist_pT_optimization;

    TH1D *hist_CJetBoost_E_DM;    
    TH1D *hist_BJetBoost_E_DM;    
    TH1D *hist_TopTop_dphi_DM;    
    TH1D *hist_Z_cjet_dphi_DM;    
    TH1D *hist_Z_bjet_dphi_DM;    
    TH1D *hist_W_cjet_dphi_DM;    
    TH1D *hist_W_bjet_dphi_DM;    
    TH1D *hist_ZLLpair_dphi_DM;   
    TH1D *hist_WLZL1_dphi_DM;     
    TH1D *hist_WLZL2_dphi_DM;     
    TH1D *hist_WLep_bjet_dphi_DM; 
    TH1D *hist_ZLep1_bjet_dphi_DM;
    TH1D *hist_ZLep2_bjet_dphi_DM;
    TH1D *hist_WLep_cjet_dphi_DM; 
    TH1D *hist_ZLep1_cjet_dphi_DM;
    TH1D *hist_ZLep2_cjet_dphi_DM;
    TH1D *hist_BJet_btag_DM;      
    TH1D *hist_CJet_btag_DM;      
    TH1D *hist_TopTop_deta_DM;    
    TH1D *hist_Z_cjet_deta_DM;    
    TH1D *hist_Z_bjet_deta_DM;    
    TH1D *hist_W_bjet_deta_DM;    
    TH1D *hist_W_cjet_deta_DM;    
    TH1D *hist_ZLLpair_deta_DM;   
    TH1D *hist_WLZL1_deta_DM;     
    TH1D *hist_WLZL2_deta_DM;     
    TH1D *hist_WLep_bjet_deta_DM; 
    TH1D *hist_ZLep1_bjet_deta_DM;
    TH1D *hist_ZLep2_bjet_deta_DM;
    TH1D *hist_WLep_cjet_deta_DM;
    TH1D *hist_ZLep1_cjet_deta_DM;
    TH1D *hist_ZLep2_cjet_deta_DM;
 
    TH1D *hist_CJetBoost_E_DE;    
    TH1D *hist_BJetBoost_E_DE;    
    TH1D *hist_TopTop_dphi_DE;    
    TH1D *hist_Z_cjet_dphi_DE;    
    TH1D *hist_Z_bjet_dphi_DE;    
    TH1D *hist_W_cjet_dphi_DE;    
    TH1D *hist_W_bjet_dphi_DE;    
    TH1D *hist_ZLLpair_dphi_DE;   
    TH1D *hist_WLZL1_dphi_DE;     
    TH1D *hist_WLZL2_dphi_DE;     
    TH1D *hist_WLep_bjet_dphi_DE; 
    TH1D *hist_ZLep1_bjet_dphi_DE;
    TH1D *hist_ZLep2_bjet_dphi_DE;
    TH1D *hist_WLep_cjet_dphi_DE; 
    TH1D *hist_ZLep1_cjet_dphi_DE;
    TH1D *hist_ZLep2_cjet_dphi_DE;
    TH1D *hist_BJet_btag_DE;      
    TH1D *hist_CJet_btag_DE;      
    TH1D *hist_TopTop_deta_DE;    
    TH1D *hist_Z_cjet_deta_DE;    
    TH1D *hist_Z_bjet_deta_DE;    
    TH1D *hist_W_bjet_deta_DE;    
    TH1D *hist_W_cjet_deta_DE;    
    TH1D *hist_ZLLpair_deta_DE;   
    TH1D *hist_WLZL1_deta_DE;     
    TH1D *hist_WLZL2_deta_DE;     
    TH1D *hist_WLep_bjet_deta_DE; 
    TH1D *hist_ZLep1_bjet_deta_DE;
    TH1D *hist_ZLep2_bjet_deta_DE;
    TH1D *hist_WLep_cjet_deta_DE;
    TH1D *hist_ZLep1_cjet_deta_DE;
    TH1D *hist_ZLep2_cjet_deta_DE;
   
    TH1D *hist_PDF_combined;
    TH1D *hist_PDFun_eee;
    TH1D *hist_PDFun_eem;
    TH1D *hist_PDFun_emm;
    TH1D *hist_PDFun_mmm;

    TH1D *hist_evt_weightB;
    TH1D *hist_evt_weightA;


   ClassDef(MyTcZAna_2016_Central,0);
};

#endif

#ifdef MyTcZAna_2016_Central_cxx
void MyTcZAna_2016_Central::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
   //cout << "settree done...\n";

}

Bool_t MyTcZAna_2016_Central::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   //mvaTree = new TTree("mvaTree", "Tree for MVA studies");
   //mvaTree2 = new TTree("mvaTree2", "Tree for MVA studies");

   return kTRUE;
}

#endif // #ifdef MyTcZAna_2016_Central_cxx
