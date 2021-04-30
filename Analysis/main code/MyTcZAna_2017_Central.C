#define MyTcZAna_2017_Central_cxx
// The class definition in MyTcZAna_2017_Central.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    p
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("MyTcZAna_2017_Central.C")
// root> T->Process("MyTcZAna_2017_Central.C","some options")
// root> T->Process("MyTcZAna_2017_Central.C+")
//

#include "MyTcZAna_2017_Central.h"
#include <TH2.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TLorentzVector.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <TMath.h>
#include <math.h>
#include "TriggerBooking.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "FWCore/Utilities/interface/thread_safety_macros.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#define N_TRIGGER_BOOKINGS      4086//5148//5792

#define MASS_Z0 91.1870
#define MASS_W 80.33000

#define VTX_NDOF_CUT 4
#define VTX_SUMPT_CUT 0.
#define VTX_ABSZ_CUT 24.
#define VTX_RHO_CUT 2.

#define ELE_PT_CUT  0//35  //20.before 30.group 
#define ELE_PT_CUT_Veto  10
#define ELE_ETA_CUT 2.4//2.5 //2.5.group
#define ELE_ETA_CUT_Veto 2.5 //2.5.group
#define ElTrackDxy 0.04 //Transverse IP of the elecrtron
#define ELE_MVA_CUT 0.9 //MVA : electron.electronID("mvaTrigV0"); > 0.5(or 0.9)
#define ELE_MVA_CUT_Veto_Lcut 0
#define ELE_MVA_CUT_Veto_Tcut 1
#define ELE_Track_CUT 0 // mHits
#define ELE_ISO_LB 0.15 //relIso (r=0.3) with Rho corrections
#define ELE_ISO_LCUT_Veto 0.15

#define MU_PT_CUT   0//30  //20.before 26.group 
#define MU_PT_CUT_Veto   10  //20.before 26.group 
#define MU_ETA_CUT  2.4 //2.4
#define MU_ETA_CUT_Veto  2.5 //2.4
#define MU_ISO_LCUT 0.15
#define MU_ISO_LCUT_Veto 0.2
#define MU_Tracker_CUT 5
#define MU_GlobeTracker_CUT 0
#define MU_InnerTrack_CUT 0
#define MU_MatchedStations_CUT 1
#define MU_VertexZ_CUT 0.5

#define LEP_ISO_LB 0.1 
#define LEP_ISO_LCUT 0.2
#define LEP_ISO_TCUT 0.2

#define Z_MASS_LCUT 82.5 //30.   // 78
#define Z_MASS_HCUT 97.5 //150.   // 102

#define TZ_MASS_LCUT 70.
#define TZ_MASS_HCUT 100.

#define ZZ_MASS_LCUT 30.
#define ZZ_MASS_HCUT 150.

#define W_MT_LCUT 0.   //  65
#define W_MT_HCUT 300//525.   //  290

#define MET_CUT 0.

#define JET_PT_CUT 30 //45. 
#define JET_PT_CUT_1 55.
#define JET_PT_CUT_2 45.
#define JET_PT_CUT_3 35.
#define JET_PT_CUT_4up 30.
#define JET_ETA_CUT 2.4
//#define JET_BTAG_CUT 0.679 //CSVL 0.244 ;CSVM 0.679  ;CSVT 0.898
#define JET_BTAG_CUT 0.1522//0.4941//0.5426 //0.8484  //CSVL 0.5426 ;CSVM 0.8484  ;CSVT 0.9535
#define JET_CBTAG_CUT 0. //c-tag c vs. b
#define JET_NUMBER_CUT 4  //jet number least at 4
#define JET_BJETNO_CUT 3 //bjet number cut

#define HT_S_LCUT 250.
#define HT_S_HCUT 1860.

#define NoRhoCorr 0

#define JES_UNC 0.0
// #define JES_UNC 1.0
// #define JES_UNC -1.0

 #define JER_UNC 0.0
// #define JER_UNC 1.0
// #define JER_UNC -1.0
 
 #define JEM_UNC 0.0
// #define JEM_UNC 1.0
// #define JEM_UNC -1.0

 #define SFM_UNC 0.0
// #define SFM_UNC 1.0
// #define SFM_UNC -1.0

 #define SFE_UNC 0.0
// #define SFE_UNC 1.0
// #define SFE_UNC -1.0

 #define SFM_UNC_I 0.0
// #define SFM_UNC_I 1.0
// #define SFM_UNC_I -1.0

 #define SFE_UNC_I 0.0
// #define SFE_UNC_I 1.0
// #define SFE_UNC_I -1.0

 #define ToppT_UNC 0.0
// #define ToppT_UNC 1.0
// #define ToppT_UNC -1.0

 #define TTbb_UNC 0.0
// #define TTbb_UNC 1.0
// #define TTbb_UNC -1.0

 #define TTcc_UNC 0.0
// #define TTcc_UNC 1.0
// #define TTcc_UNC -1.0
 
 #define METue_UNC 0.0
// #define METue_UNC 1.0
// #define METue_UNC -1.0
std::uint32_t seed              = 37428479;
std::mt19937 m_random_generator = std::mt19937( seed );

void MyTcZAna_2017_Central::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

  //..Histogram definitions
   cout << "MyTcZAna_2017_Central... begin!\n";
   cout << "   options: " << option << endl;

   Event_Weight_Tot=0;
   Event_Tot=0;
   selectionNo=0;
   triggerNo=0;
   postive_number=0;
   negative_number=0;
   test_e_no=0;
   test_mu_no=0;
   FullReco_MCTruth_pre=0;
   FullReco_MCTruth=0;
   FullReco_MCTruth_b_pre=0;
   FullReco_MCTruth_c_pre=0;
   FullReco_MCTruth_b=0;
   FullReco_MCTruth_c=0;
   Topdphi_MCTruth_pre=0;
   Topdphi_MCTruth=0;
   Topdphi_MCTruth_b_pre=0;
   Topdphi_MCTruth_c_pre=0;
   Topdphi_MCTruth_b=0;
   Topdphi_MCTruth_c=0;
   Xsquare_MCTruth_pre=0;
   Xsquare_MCTruth=0;
   Xsquare_MCTruth_b_pre=0;
   Xsquare_MCTruth_c_pre=0;
   Xsquare_MCTruth_b=0;
   Xsquare_MCTruth_c=0;
   BtaggingInit();
}

void MyTcZAna_2017_Central::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   
    // Definition of histograms {{{
   TH1::SetDefaultSumw2();
   hist_evt_cut                   = new TH1D("hist_evt_cut","Event selection cuts", 25, 0, 25);
   hist_evt_cut_e                 = new TH1D("hist_evt_cut_e","Event selection cuts", 25, 0, 25);
   hist_evt_cut_m                 = new TH1D("hist_evt_cut_m","Event selection cuts", 25, 0, 25); 
   hist_evt_cut_eem               = new TH1D("hist_evt_cut_eem","Event selection cuts", 25, 0, 25);
   hist_evt_cut_mme               = new TH1D("hist_evt_cut_mme","Event selection cuts", 25, 0, 25);
   hist_evt_cut_eee               = new TH1D("hist_evt_cut_eee","Event selection cuts", 25, 0, 25);
   hist_evt_cut_mmm               = new TH1D("hist_evt_cut_mmm","Event selection cuts", 25, 0, 25);

   hist_ele_cut                   = new TH1D("hist_ele_cut","Eletron selection cuts", 20, 0, 20);
   hist_mu_cut                    = new TH1D("hist_mu_cut","Muon selection cuts", 20, 0, 20);
   hist_jet_cut                   = new TH1D("hist_jet_cut","Jet selection cuts", 25, 0, 25);


   hist_vtx_no                    = new TH1D("hist_vtx_no","No. of vtx",50,0,50);
   hist_vtx_no_reweight           = new TH1D("hist_vtx_no_reweight", "No. of vtx", 50,0,50);
   
   hist_vtx_no_3leptons           = new TH1D("hist_vtx_no_3leptons", "No. of vtx", 50,0,50);                    //out of DE & DM separation
   hist_vtx_no_3leptons_reweight  = new TH1D("hist_vtx_no_3leptons_reweight", "No. of vtx", 50,0,50);

   hist_vtx_no_3leptons_DE          = new TH1D("hist_vtx_no_3leptons_DE", "No. of vtx", 50,0,50);
   hist_vtx_no_3leptons_reweight_DE = new TH1D("hist_vtx_no_3leptons_reweight_DE", "No. of vtx", 50,0,50);
   hist_vtx_no_3leptons_DM          = new TH1D("hist_vtx_no_3leptons_DM", "No. of vtx", 50,0,50);
   hist_vtx_no_3leptons_reweight_DM = new TH1D("hist_vtx_no_3leptons_reweight_DM", "No. of vtx", 50,0,50);
   //hist_vtx_no_AS                 = new TH1D("hist_vtx_no_AS","No. of vtx",50,0,50);
   //hist_vtx_no_AS_nPU             = new TH1D("hist_vtx_no_AS without PU","No. of vtx",50,0,50);
   hist_vtx_ndof                  = new TH1D("hist_vtx_ndof","No. of vtx DoF",100, 0, 350);
   //hist_vtx_ndof_AS               = new TH1D("hist_vtx_ndof_AS","No. of vtx DoF",100, 0, 350);
   hist_vtx_nx2                   = new TH1D("hist_vtx_nx2","Norm. #chi^2",100, 0, 5);
   hist_vtx_ptsum                 = new TH1D("hist_vtx_ptsum","p_{T} sum of vtx", 100, 0,1000);
   hist_vtx_z                     = new TH1D("hist_vtx_z","Vtx z position",100, -30, 30);
   hist_vtx_rho                   = new TH1D("hist_vtx_rho","Vtx rho position",100, -1, 1);
   hist_vtx_cut                   = new TH1D("hist_vtx_cut","Vtx selection cuts",10, 0, 10);

   hist_npu                       = new TH1D("hist_npu","# of pile-ups",80, 0, 80);
   hist_npu_raw                   = new TH1D("hist_npu_raw","# of pile-ups",80, 0, 80);

   hist_e_AEff                    = new TH1D("hist_e_AEff","e AEff",100,0,1);
   hist_m_AEff                    = new TH1D("hist_m_AEff","m AEff",100,0,1);
   hist_e_rho_AEff                = new TH1D("hist_e_rho_AEff","e rho_AEff",400,0,20);
   hist_m_rho_AEff                = new TH1D("hist_m_rho_AEff","m rho_AEff",400,0,20);
   hist_zee_rho                   = new TH1D("hist_zee_rho","rho",100,0,50);
   hist_zmm_rho                   = new TH1D("hist_zmm_rho","rho",100,0,50);
   hist_zee_rho_raw               = new TH1D("hist_zee_rho_raw","rho",100,0,50);
   hist_zmm_rho_raw               = new TH1D("hist_zmm_rho_raw","rho",100,0,50);

   hist_e_pt                      = new TH1D("hist_e_pt","e p_{T}",100,0,200);
   hist_e_pt_AS                   = new TH1D("hist_e_pt_AS","e p_{T}",50,0,200);
   hist_e_eta                     = new TH1D("hist_e_eta","e #eta",100,-3.0,3.0);
   hist_e_eta_AS                  = new TH1D("hist_e_eta_AS","e #eta",50,-3.0,3.0);
   hist_e_phi                     = new TH1D("hist_e_phi","e #phi",100,-3.14,3.14);
   hist_e_phi_AS                  = new TH1D("hist_e_phi_AS","e #phi",50,-3.14,3.14);
   hist_e_iso                     = new TH1D("hist_e_iso","e Rel. Iso.",100,0.,0.25);
   hist_e_mva                     = new TH1D("hist_e_mva","e MVA",110,0.,1.1);
   hist_e_mva_no                  = new TH1D("hist_e_mva_no","NO. Ele MVA value is 0 or 1",10,0,10);

   hist_m_pt                      = new TH1D("hist_m_pt","#mu p_{T}",100,0,200);
   hist_m_pt_AS                   = new TH1D("hist_m_pt_AS","#mu p_{T}",50,0,200);
   hist_m_eta                     = new TH1D("hist_m_eta","#mu #eta",100,-3.0,3.0);
   hist_m_eta_AS                  = new TH1D("hist_m_eta_AS","#mu #eta",50,-3.0,3.0);
   hist_m_phi                     = new TH1D("hist_m_phi","#mu #phi",100,-3.14,3.14);
   hist_m_phi_AS                  = new TH1D("hist_m_phi_AS","#mu #phi",50,-3.14,3.14);
   hist_m_iso                     = new TH1D("hist_m_iso","#mu Rel. Iso.",100,0.,0.25);
   hist_m_mva                     = new TH1D("hist_m_mva","#mu MVA",110,0.,1.1);

   hist_ge_pt                     = new TH1D("hist_ge_pt","GEN matched e p_{T}",100,0,200);
   hist_ge_eta                    = new TH1D("hist_ge_eta","GEN matched e #eta",100,-3.0,3.0);
   hist_ge_phi                    = new TH1D("hist_ge_phi","GEN matched e #phi",100,-3.14,3.14);

   hist_gm_pt                     = new TH1D("hist_gm_pt","GEN matched #mu p_{T}",100,0,200);
   hist_gm_eta                    = new TH1D("hist_gm_eta","GEN matched #mu #eta",100,-3.0,3.0);
   hist_gm_phi                    = new TH1D("hist_gm_phi","GEN matched #mu #phi",100,-3.14,3.14);

   hist_gel_pt                    = new TH1D("hist_gel_pt","GEN matched e p_{T}",100,0,200);
   hist_gel_eta                   = new TH1D("hist_gel_eta","GEN matched e #eta",100,-3.0,3.0);
   hist_gel_phi                   = new TH1D("hist_gel_phi","GEN matched e #phi",100,-3.14,3.14);

   hist_gml_pt                    = new TH1D("hist_gml_pt","GEN matched #mu p_{T}",100,0,200);
   hist_gml_eta                   = new TH1D("hist_gml_eta","GEN matched #mu #eta",100,-3.0,3.0);
   hist_gml_phi                   = new TH1D("hist_gml_phi","GEN matched #mu #phi",100,-3.14,3.14);
   hist_get_pt                    = new TH1D("hist_get_pt","GEN matched e p_{T}",100,0,200);
   hist_get_eta                   = new TH1D("hist_get_eta","GEN matched e #eta",100,-3.0,3.0);
   hist_get_phi                   = new TH1D("hist_get_phi","GEN matched e #phi",100,-3.14,3.14);

   hist_gmt_pt                    = new TH1D("hist_gmt_pt","GEN matched #mu p_{T}",100,0,200);
   hist_gmt_eta                   = new TH1D("hist_gmt_eta","GEN matched #mu #eta",100,-3.0,3.0);
   hist_gmt_phi                   = new TH1D("hist_gmt_phi","GEN matched #mu #phi",100,-3.14,3.14);

   hist_te_pt                     = new TH1D("hist_te_pt","tight e p_{T}",100,0,200);
   hist_te_eta                    = new TH1D("hist_te_eta","tight e #eta",100,-3.0,3.0);
   hist_te_phi                    = new TH1D("hist_te_phi","tight e #phi",100,-3.14,3.14);

   hist_tm_pt                     = new TH1D("hist_tm_pt","tight #mu p_{T}",100,0,200);
   hist_tm_eta                    = new TH1D("hist_tm_eta","tight #mu #eta",100,-3.0,3.0);
   hist_tm_phi                    = new TH1D("hist_tm_phi","tight #mu #phi",100,-3.14,3.14);

   hist_wen_m                     = new TH1D("hist_wen_m","invariant mass of W(e #nu)",50,0,250);
   hist_wmn_m                     = new TH1D("hist_wmn_m","invariant mass of W(#mu #nu)",50,0,250);
   hist_wen_mt                    = new TH1D("hist_wen_mt","transverse mass of W(e #nu)",50,0,250);
   hist_wmn_mt                    = new TH1D("hist_wmn_mt","transverse mass of W(#mu #nu)",50,0,250);
   hist_wen_gmt                   = new TH1D("hist_wen_gmt","trans. mass of gen W(e #nu)",50,0,250);
   hist_wmn_gmt                   = new TH1D("hist_wmn_gmt","trans. mass of gen W(#mu #nu)",50,0,250);
   hist_wen_pt                    = new TH1D("hist_wen_pt","p_{T} of W(e #nu)",50,0,250);
   hist_wmn_pt                    = new TH1D("hist_wmn_pt","p_{T} of W(#mu #nu)",50,0,250);
   hist_wen_no                    = new TH1D("hist_wen_no", "No. of W candidates (e)",5,0,5.);
   hist_wmn_no                    = new TH1D("hist_wmn_no", "No. of W candidates (#mu)",5,0,5.);
   
   hist_wen_mt_ee                 = new TH1D("hist_wen_mt_ee","transverse mass of W(e #nu)",50,0,250);
   hist_wen_mt_mm                 = new TH1D("hist_wen_mt_mm","transverse mass of W(e #nu)",50,0,250);
   hist_wmn_mt_ee                 = new TH1D("hist_wmn_mt_ee","transverse mass of W(#mu #nu)",50,0,250);
   hist_wmn_mt_mm                 = new TH1D("hist_wmn_mt_mm","transverse mass of W(#mu #nu)",50,0,250);

   hist_zee_no                    = new TH1D("hist_zee_no","# of Z(ee)",10,0,10);
   hist_zmm_no                    = new TH1D("hist_zmm_no","# of Z(#mu#mu)",10,0,10);

   hist_zee_pt                    = new TH1D("hist_zee_pt","pt of Z(ee)",50,0,150);
   hist_zmm_pt                    = new TH1D("hist_zmm_pt","pt of Z(#mu#mu)",50,0,150);

   hist_zee_m                     = new TH1D("hist_zee_m","mass of Z(ee)",60,30,150);
   hist_zmm_m                     = new TH1D("hist_zmm_m","mass of Z(#mu#mu)",60,30,150);

   hist_zee_m_g                   = new TH1D("hist_zee_m_g","mass of Z(ee) GEN",60,30,150);
   hist_zmm_m_g                   = new TH1D("hist_zmm_m_g","mass of Z(#mu#mu) GEN",60,30,150);

   hist_e_no                      = new TH1D("hist_e_no", "No. of electons",10,0,10);
   hist_e_notest                  = new TH1D("hist_e_notest", "No. of electons test",10,0,10);
   hist_m_no                      = new TH1D("hist_m_no", "No. of muons",10,0,10);
   hist_lep_no                    = new TH1D("hist_lep_no", "No. of leptons",10,0,10);
   hist_wz_no                     = new TH1D("hist_wz_no", "No. of W+Z",5,0,5);

   hist_jet_pt                    = new TH1D("hist_jet_pt", "p_{T} of jet",50,0,150);
   hist_jet_pt_AS                 = new TH1D("hist_jet_pt_AS", "p_{T} of jet",50,0,150);
   hist_jet_eta                   = new TH1D("hist_jet_eta", "#eta of jet",100,-3.,3.);
   hist_jet_eta_AS                = new TH1D("hist_jet_eta_AS", "#eta of jet",100,-3.,3.);
   hist_jet_phi                   = new TH1D("hist_jet_phi", "#phi of jet",100,-3.5,3.5);
   hist_jet_phi_AS                = new TH1D("hist_jet_phi_AS", "#phi of jet",100,-3.5,3.5);
   hist_jet_btag                  = new TH1D("hist_jet_btag", "btag of jet",100,-2,2);
   hist_jet_btag_nob              = new TH1D("hist_jet_btag_nob", "btag of jet (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_corr         = new TH1D("hist_jet_btag_nob_corr", "btag of jet (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_b            = new TH1D("hist_jet_btag_nob_b", "btag of b-jet flavor (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_b_corr       = new TH1D("hist_jet_btag_nob_b_corr", "btag of of b-jet flavor (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_l            = new TH1D("hist_jet_btag_nob_l", "btag of of light-jet flavor (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_nob_l_corr       = new TH1D("hist_jet_btag_nob_l_corr", "btag of of light-jet flavor (ttjets) > 4jets",60,-0.1,1.1);
   hist_jet_btag_6                = new TH1D("hist_jet_btag_6", "btag of jet (ttjets) > 6jets + 3 btagged region",60,-0.1,1.1);
   hist_jet_btag_6_corr           = new TH1D("hist_jet_btag_6_corr", "btag of jet (ttjets) > 6jets + 3 btagged region after correction",60,-0.1,1.1);
   hist_jet_btag_6_b              = new TH1D("hist_jet_btag_6_b", "btag of b-jet flavor (ttjets) > 6jets + 3 btagged region ",60,-0.1,1.1);
   hist_jet_btag_6_b_corr         = new TH1D("hist_jet_btag_6_b_corr", "btag of of b-jet flavor (ttjets) > 6jets + 3 btagged region after correction",60,-0.1,1.1);
   hist_jet_btag_6_l              = new TH1D("hist_jet_btag_6_l", "btag of of light-jet flavor (ttjets) > 6jets + 3 btagged region",60,-0.1,1.1);
   hist_jet_btag_6_l_corr         = new TH1D("hist_jet_btag_6_l_corr", "btag of of light-jet flavor (ttjets) > 6jets + 3 btagged region after correction",60,-0.1,1.1);
   hist_jet_btag_4                = new TH1D("hist_jet_btag_4", "btag of jet (ttjets) control region",60,-0.1,1.1);
   hist_jet_btag_4_corr           = new TH1D("hist_jet_btag_4_corr", "btag of jet (ttjets) control region after correction",60,-0.1,1.1);
   hist_jet_btag_4_b              = new TH1D("hist_jet_btag_4_b", "btag of b-jet flavor (ttjets) control region ",60,-0.1,1.1);
   hist_jet_btag_4_b_corr         = new TH1D("hist_jet_btag_4_b_corr", "btag of of b-jet flavor (ttjets) control region after correction",60,-0.1,1.1);
   hist_jet_btag_4_l              = new TH1D("hist_jet_btag_4_l", "btag of of light-jet flavor (ttjets) control region",60,-0.1,1.1);
   hist_jet_btag_4_l_corr         = new TH1D("hist_jet_btag_4_l_corr", "btag of of light-jet flavor (ttjets) control region after correction",60,-0.1,1.1);

   hist_jet_btag_2_ttb            = new TH1D("hist_jet_btag_2_ttb", "btag of jet (tt+b) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_2_ttb_corr       = new TH1D("hist_jet_btag_2_ttb_corr", "btag of jet (tt+b) signal only 3b region after correction",60,-0.1,1.1);
   hist_jet_btag_2_ttc            = new TH1D("hist_jet_btag_2_ttc", "btag of jet (tt+c) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_2_ttc_corr       = new TH1D("hist_jet_btag_2_ttc_corr", "btag of jet (tt+c) signal only 3b region after correction",60,-0.1,1.1);
   hist_jet_btag_2_ttlf           = new TH1D("hist_jet_btag_2_ttlf", "btag of jet (tt+lf) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_2_ttlf_corr      = new TH1D("hist_jet_btag_2_ttlf_corr", "btag of jet (tt+lf) signal only 3b region after correction",60,-0.1,1.1);

   hist_jet_btag_2                = new TH1D("hist_jet_btag_2", "btag of jet (ttjets) 4jet(2b)",60,-0.1,1.1);
   hist_jet_btag_2_corr           = new TH1D("hist_jet_btag_2_corr", "btag of jet (ttjets) 4jet(2b) after correction",60,-0.1,1.1);
   hist_jet_btag_2_b              = new TH1D("hist_jet_btag_2_b", "btag of b-jet flavor (ttjets)4jet(2b) ",60,-0.1,1.1);
   hist_jet_btag_2_b_corr         = new TH1D("hist_jet_btag_2_b_corr", "btag of of b-jet flavor (ttjets) 4jet(2b) after correction",60,-0.1,1.1);
   hist_jet_btag_2_c              = new TH1D("hist_jet_btag_2_c", "btag of charm flavor (ttjets)4jet(2b) ",60,-0.1,1.1);
   hist_jet_btag_2_c_corr         = new TH1D("hist_jet_btag_2_c_corr", "btag of of charm flavor (ttjets) 4jet(2b) after correction",60,-0.1,1.1);
   hist_jet_btag_2_l              = new TH1D("hist_jet_btag_2_l", "btag of of light-jet flavor (ttjets) 4jet(2b)",60,-0.1,1.1);
   hist_jet_btag_2_l_corr         = new TH1D("hist_jet_btag_2_l_corr", "btag of of light-jet flavor (ttjets) 4jet(2b) after correction",60,-0.1,1.1);

   hist_jet_btag_s_2              = new TH1D("hist_jet_btag_s_2", "btag of jet (ttjets) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_s_2_corr         = new TH1D("hist_jet_btag_s_2_corr", "btag of jet (ttjets) signal only 3b region after correction",60,-0.1,1.1);
   hist_jet_btag_s_2_b            = new TH1D("hist_jet_btag_s_2_b", "btag of b-jet flavor (ttjets) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_s_2_b_corr       = new TH1D("hist_jet_btag_s_2_b_corr", "btag of of b-jet flavor (ttjets) signal only 3b region after correction",60,-0.1,1.1);
   hist_jet_btag_s_2_l            = new TH1D("hist_jet_btag_s_2_l", "btag of of light-jet flavor (ttjets) signal only 3b region",60,-0.1,1.1);
   hist_jet_btag_s_2_l_corr       = new TH1D("hist_jet_btag_s_2_l_corr", "btag of of light-jet flavor (ttjets) signal only 3b region after correction",60,-0.1,1.1);

   hist_jet_btag_s_ttb            = new TH1D("hist_jet_btag_s_ttb", "btag of jet (tt+b) signal region",60,-0.1,1.1);
   hist_jet_btag_s_ttb_corr       = new TH1D("hist_jet_btag_s_ttb_corr", "btag of jet (tt+b) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_ttc            = new TH1D("hist_jet_btag_s_ttc", "btag of jet (tt+c) signal region",60,-0.1,1.1);
   hist_jet_btag_s_ttc_corr       = new TH1D("hist_jet_btag_s_ttc_corr", "btag of jet (tt+c) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_ttlf           = new TH1D("hist_jet_btag_s_ttlf", "btag of jet (tt+lf) signal region",60,-0.1,1.1);
   hist_jet_btag_s_ttlf_corr      = new TH1D("hist_jet_btag_s_ttlf_corr", "btag of jet (tt+lf) signal region after correction",60,-0.1,1.1);

   hist_jet_btag_s                = new TH1D("hist_jet_btag_s", "btag of jet (ttjets) signal region",60,-0.1,1.1);
   hist_jet_btag_s_bjet           = new TH1D("hist_jet_btag_s_bjet", "btag of b tagged jet (ttjets) signal region",60,-0.1,1.1);
   hist_jet_btag_s_total_up       = new TH1D("hist_jet_btag_s_total_up", "btag of jet (ttjets) total up signal region",60,-0.1,1.1);
   hist_jet_btag_s_total_down     = new TH1D("hist_jet_btag_s_total_down", "btag of jet (ttjets) total down signal region",60,-0.1,1.1);
   hist_jet_btag_s_jes_up         = new TH1D("hist_jet_btag_s_jes_up", "btag of jet (ttjets) JES up signal region",60,-0.1,1.1);
   hist_jet_btag_s_jes_down       = new TH1D("hist_jet_btag_s_jes_down", "btag of jet (ttjets) JES down signal region",60,-0.1,1.1);
   hist_jet_btag_s_pur_up         = new TH1D("hist_jet_btag_s_pur_up", "btag of jet (ttjets) purity up signal region",60,-0.1,1.1);
   hist_jet_btag_s_pur_down       = new TH1D("hist_jet_btag_s_pur_down", "btag of jet (ttjets) purity down signal region",60,-0.1,1.1);
   hist_jet_btag_s_sta1_up        = new TH1D("hist_jet_btag_s_sta1_up", "btag of jet (ttjets) sta1 up signal region",60,-0.1,1.1);
   hist_jet_btag_s_sta1_down      = new TH1D("hist_jet_btag_s_sta1_down", "btag of jet (ttjets) sta1 down signal region",60,-0.1,1.1);
   hist_jet_btag_s_sta2_up        = new TH1D("hist_jet_btag_s_sta2_up", "btag of jet (ttjets) sta2 up signal region",60,-0.1,1.1);
   hist_jet_btag_s_sta2_down      = new TH1D("hist_jet_btag_s_sta2_down", "btag of jet (ttjets) sta2 down signal region",60,-0.1,1.1);
   hist_jet_btag_s_corr           = new TH1D("hist_jet_btag_s_corr", "btag of jet (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_corr_bjet      = new TH1D("hist_jet_btag_s_corr_bjet", "btag of btagged jet (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_b              = new TH1D("hist_jet_btag_s_b", "btag of b-jet flavor (ttjets) signal regio",60,-0.1,1.1);
   hist_jet_btag_s_b_corr         = new TH1D("hist_jet_btag_s_b_corr", "btag of of b-jet flavor (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_c              = new TH1D("hist_jet_btag_s_c", "btag of charm flavor (ttjets) signal regio",60,-0.1,1.1);
   hist_jet_btag_s_c_corr         = new TH1D("hist_jet_btag_s_c_corr", "btag of of charm flavor (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_s_l              = new TH1D("hist_jet_btag_s_l", "btag of of light-jet flavor (ttjets) signal region",60,-0.1,1.1);
   hist_jet_btag_s_l_Luca         = new TH1D("hist_jet_btag_s_l_Luca", "ttjets light-jet flavor in signal region No b-tagging",60,-0.1,1.1);
   hist_jet_btag_s_l_corr         = new TH1D("hist_jet_btag_s_l_corr", "btag of of light-jet flavor (ttjets) signal region after correction",60,-0.1,1.1);
   hist_jet_btag_AS               = new TH1D("hist_jet_btag_AS", "btag of jet after 4 jets",60,-0.1,1.1);
   hist_jet_btag_AS_corr          = new TH1D("hist_jet_btag_AS_corr", "btag of jet after correction",60,-0.1,1.1);
   hist_jet_btag_Func             = new TH1D("hist_jet_btag_Func", "Correction Function of (lep)b",2200,0,1.1);
   hist_jet_btag_pdgid0           = new TH1D("hist_jet_btag_pdgid0", "btag of jet with pdgID is 0",60,-0.1,1.1);
   hist_jet_SF_pdgid0             = new TH1D("hist_jet_SF_pdgid0", "Scale factor of jet with pdgID is 0",60,0,6);
   hist_gjet_pt                   = new TH1D("hist_gjet_pt", "p_{T} of gjet",100,0,150);
   hist_gjet_eta                  = new TH1D("hist_gjet_eta", "#eta of gjet",100,-3.,3.);
   hist_gjet_phi                  = new TH1D("hist_gjet_phi", "#phi of gjet",100,-3.5,3.5);
   hist_gjetc_pt                  = new TH1D("hist_gjetc_pt", "p_{T} of gjetc",100,0,150);
   hist_gjetc_eta                 = new TH1D("hist_gjetc_eta", "#eta of gjetc",100,-3.,3.);
   hist_gjetc_phi                 = new TH1D("hist_gjetc_phi", "#phi of gjetc",100,-3.5,3.5);
   hist_bjet_no_cut               = new TH1D("hist_bjet_no_cut", "No. of bjets after event selection",10,0,10);
   hist_bjet_no                   = new TH1D("hist_bjet_no", "No. of bjets",10,0,10);
   hist_jet_no                    = new TH1D("hist_jet_no", "No. of jets",10,0,10);
   hist_bjet_no_AS                = new TH1D("hist_bjet_no after selection", "No. of bjets",10,0,10);
   hist_jet_no_AS                 = new TH1D("hist_jet_no after selection", "No. of jets",10,0,10);
   hist_jet_no_c                  = new TH1D("hist_jet_no_c", "No. of jets Cleaned",10,0,10);

   hist_met_sumEt                 = new TH1D("hist_met_sumEt", "Sum E_{T} of MET",50,0,1000);
   hist_met_sumEt_xy              = new TH1D("hist_met_sumEt_xy", "Sum E_{T} of MET",50,0,1000);
   hist_met_UE                    = new TH1D("hist_met_UE", "Unclustered Energy of MET",50,0,1000);
   hist_met_pt                    = new TH1D("hist_met_pt", "p_{T} of MET",100,0,150);
   hist_met_pt_AS                 = new TH1D("hist_met_pt_AS", "p_{T} of MET",100,0,150);
   hist_met_pt_2b                 = new TH1D("hist_met_pt_2b", "p_{T} of MET",100,0,150);
   hist_met_pt_3b                 = new TH1D("hist_met_pt_3b", "p_{T} of MET",100,0,150);
   hist_met_phi                   = new TH1D("hist_met_phi", "#phi of MET",100,-3.5,3.5);

   hist_top_m_bw_DM               = new TH1D("hist_top_m_bw_DM","inv mass of t(bW) all",40,50,350);
   hist_top_m_cz_DM               = new TH1D("hist_top_m_cz_DM","inv mass of t(cZ) all",40,50,350);
   hist_top_m_bw_DE               = new TH1D("hist_top_m_bw_DE","inv mass of t(bW) all",40,50,350);
   hist_top_m_cz_DE               = new TH1D("hist_top_m_cz_DE","inv mass of t(cZ) all",40,50,350);
   hist_top_mt_bw_DM              = new TH1D("hist_top_mt_bw_DM","Transverse mass of t(bW) all",40,50,350);
   hist_top_mt_cz_DM              = new TH1D("hist_top_mt_cz_DM","Transverse mass of t(cZ) all",40,50,350);
   hist_top_mt_bw_DE              = new TH1D("hist_top_mt_bw_DE","Transverse mass of t(bW) all",40,50,350);
   hist_top_mt_cz_DE              = new TH1D("hist_top_mt_cz_DE","Transverse mass of t(cZ) all",40,50,350);
   hist_top_m_bw_DE_csvSF         = new TH1D("hist_top_m_bw_DE_csvSF", "inv mass of t(bW) all",40,50,350);
   hist_top_m_cz_DE_csvSF         = new TH1D("hist_top_m_cz_DE_csvSF", "inv mass of t(cZ) all",40,50,350);
   hist_top_m_bw_DM_csvSF         = new TH1D("hist_top_m_bw_DM_csvSF", "inv mass of t(bW) all",40,50,350);
   hist_top_m_cz_DM_csvSF         = new TH1D("hist_top_m_cz_DM_csvSF", "inv mass of t(cZ) all",40,50,350);


   hist_top_comb                  = new TH1D("hist_top_comb","# of combinations",10,0,10);
   hist_top_corr                  = new TH1D("hist_top_corr","pick correct comb.", 5,0, 5);
   hist_top_corr0                 = new TH1D("hist_top_corr0","pick correct comb. Org", 5,0, 5);

   hist_ERb                       = new TH1D("hist_ERb","energy of b at top rest frame",50,0,200);
   hist_ERc                       = new TH1D("hist_ERc","energy of c at top rest frame",50,0,200);

   hist_fit_m_bw                  = new TH1D("hist_fit_m_bw","inv mass of t(bW)",50,50,350);
   hist_fit_m_cz                  = new TH1D("hist_fit_m_cz","inv mass of t(cZ)",50,50,350);
   hist_fit_m_zee                 = new TH1D("hist_fit_m_zee","inv mass of Z(ee)",60,30,150);
   hist_fit_m_zmm                 = new TH1D("hist_fit_m_zmm","inv mass of Z(#mu#mu)",60,30,150);
   hist_fit_m_wen                 = new TH1D("hist_fit_m_wen","inv mass of W(e#nu)",50,0,250);
   hist_fit_m_wmn                 = new TH1D("hist_fit_m_wmn","inv mass of W(#mu#nu)",50,0,250);
   hist_fit_mt_wen                = new TH1D("hist_fit_mt_wen","trans. mass of W(e#nu)",50,0,250);
   hist_fit_mt_wmn                = new TH1D("hist_fit_mt_wmn","trans mass of W(#mu#nu)",50,0,250);
   hist_fit_ht                    = new TH1D("hist_fit_ht","Daughter p_{T} sum",50,0,1500);
   hist_fit_st                    = new TH1D("hist_fit_st","Total p_{T} sum",50,0,1500);

   hist_fit_ctag_lc1              = new TH1D("hist_fit_ctag_lc1","c-tag l-c 1",50,-2.,2.);
   hist_fit_ctag_lc2              = new TH1D("hist_fit_ctag_lc2","c-tag l-c 2",50,-2.,2.);
   hist_fit_ctag_bc1              = new TH1D("hist_fit_ctag_bc1","c-tag b-c 1",50,-2.,2.);
   hist_fit_ctag_bc2              = new TH1D("hist_fit_ctag_bc2","c-tag b-c 2",50,-2.,2.);

   hist_fit_nbjet                 = new TH1D("hist_fit_nbjet", "No. of bjets",10,0,10);
   hist_fit_ncbjet                = new TH1D("hist_fit_ncbjet", "No. of clean bjets",10,0,10);

   hist_bjet_ordering             = new TH1D("hist_bjet_ordering", "Ordering of the bJets",10,0,10);
   hist_cjet_ordering             = new TH1D("hist_cjet_ordering", "Ordering of the cJets",10,0,10);
   hist_lep_jet_deltaR            = new TH1D("hist_lep_jet_deltaR", "Delta distribution",100,0.,5.);
  
   hist_new_jet_DE_pt             = new TH1D("hist_new_jet_DE_pt", "p_{T} of jet",50,0,150);
   hist_new_jet_DE_eta            = new TH1D("hist_new_jet_DE_eta", "#eta of jet",100,-3.,5.);
   hist_new_jet_DE_phi            = new TH1D("hist_new_jet_DE_phi", "#phi of jet",100,-3.5,3.5);
   hist_new_jet_DE_btag           = new TH1D("hist_new_jet_DE_btag", "CSVv2 discriminant",100,-1,1);
   
   hist_new_jet_DM_pt             = new TH1D("hist_new_jet_DM_pt", "p_{T} of jet",50,0,150);
   hist_new_jet_DM_eta            = new TH1D("hist_new_jet_DM_eta", "#eta of jet",100,-3.,5.);
   hist_new_jet_DM_phi            = new TH1D("hist_new_jet_DM_phi", "#phi of jet",100,-3.5,3.5);
   hist_new_jet_DM_btag           = new TH1D("hist_new_jet_DM_btag", "CSVv2 discriminant",100,-1,1);

   hist_new_ele_DE_pt             = new TH1D("hist_new_ele_DE_pt","new e p_{T}",100,0,200);
   hist_new_ele_DE_eta            = new TH1D("hist_new_ele_DE_eta","new e #eta",100,-3.0,5.0);
   hist_new_ele_DE_phi            = new TH1D("hist_new_ele_DE_phi","new e #phi",100,-3.14,3.14);
   hist_new_mu_DE_pt              = new TH1D("hist_new_mu_DE_pt", "new #mu p_{T}",100,0,200);
   hist_new_mu_DE_eta             = new TH1D("hist_new_mu_DE_eta","new #mu #eta",100,-3.0,5.0);
   hist_new_mu_DE_phi             = new TH1D("hist_new_mu_DE_phi","new #mu #phi",100,-3.14,3.14);
   
   hist_new_ele_DM_pt             = new TH1D("hist_new_ele_DM_pt","new e p_{T}",100,0,200);
   hist_new_ele_DM_eta            = new TH1D("hist_new_ele_DM_eta","new e #eta",100,-3.0,5.0);
   hist_new_ele_DM_phi            = new TH1D("hist_new_ele_DM_phi","new e #phi",100,-3.14,3.14);
   hist_new_mu_DM_pt              = new TH1D("hist_new_mu_DM_pt", "new #mu p_{T}",100,0,200);
   hist_new_mu_DM_eta             = new TH1D("hist_new_mu_DM_eta","new #mu #eta",100,-3.0,5.0);
   hist_new_mu_DM_phi             = new TH1D("hist_new_mu_DM_phi","new #mu #phi",100,-3.14,3.14);
   
   hist_leading_jet_DE_pt         = new TH1D("hist_leading_jet_DE_pt", "p_{T} of leading jet", 50,0,150);
   hist_leading_jet_DE_eta        = new TH1D("hist_leading_jet_DE_eta", "#eta of leading jet", 100, -3., 5.);
   hist_leading_jet_DM_pt         = new TH1D("hist_leading_jet_DM_pt", "p_{T} of leading jet", 50,0,150);
   hist_leading_jet_DM_eta        = new TH1D("hist_leading_jet_DM_eta", "#eta of leading jet", 100, -3., 5.);

   hist_new_ele_3lepton_pt        = new TH1D("hist_new_ele_3lepton_pt", "e p_{T}", 100, 0, 200);
   hist_new_ele_3lepton_eta       = new TH1D("hist_new_ele_3lepton_eta", "e #eta",100,-3.0,5.0);
   hist_new_mu_3lepton_pt         = new TH1D("hist_new_mu_3lepton_pt", "#mu p_{T}", 100, 0, 200);
   hist_new_mu_3lepton_eta        = new TH1D("hist_new_mu_3lepton_eta", "#mu #eta",100,-3.0,5.0);
   hist_new_jet_2leptons_pt       = new TH1D("hist_new_jet_2leptons_pt", "jet p_{T}", 100, 0, 200);
   hist_new_jet_2leptons_eta      = new TH1D("hist_new_jet_2leptons_eta", "jet #eta",100,-3.0,5.0);

   hist_mva_shape_DE_result       = new TH1D("hist_mva_shape_DE_result","MVA Result",200,-1.0,1.0);
   hist_mva_shape_DE_result_count = new TH1D("hist_mva_shape_DE_result_count","MVA Result",100000,-1.0,1.0);
   hist_mva_shape_DM_result       = new TH1D("hist_mva_shape_DM_result","MVA Result",200,-1.0,1.0);
   hist_mva_shape_DM_result_count = new TH1D("hist_mva_shape_DM_result_count","MVA Result",100000,-1.0,1.0);

   hist_CR1_DE_ele_pt             = new TH1D("hist_CR1_DE_ele_pt", "Leading e p_{T}", 100, 0, 200);
   hist_CR1_DE_mu_pt              = new TH1D("hist_CR1_DE_mu_pt", "Leading #mu p_{T}", 100, 0, 200);
   hist_SR_DE_ele_pt              = new TH1D("hist_SR_DE_ele_pt", "Leading e p_{T}", 100, 0, 200);
   hist_SR_DE_mu_pt               = new TH1D("hist_SR_DE_mu_pt", "Leading #mu p_{T}", 100, 0, 200);
   hist_CR2_DE_ele_pt             = new TH1D("hist_CR2_DE_ele_pt", "Leading e p_{T}", 100, 0, 200);
   hist_CR2_DE_mu_pt              = new TH1D("hist_CR2_DE_mu_pt", "Leading #mu p_{T}", 100, 0, 200);
   hist_CR1_DM_ele_pt             = new TH1D("hist_CR1_DM_ele_pt", "Leading e p_{T}", 100, 0, 200);
   hist_CR1_DM_mu_pt              = new TH1D("hist_CR1_DM_mu_pt", "Leading #mu p_{T}", 100, 0, 200);
   hist_SR_DM_ele_pt              = new TH1D("hist_SR_DM_ele_pt", "Leading e p_{T}", 100, 0, 200);
   hist_SR_DM_mu_pt               = new TH1D("hist_SR_DM_mu_pt", "Leading #mu p_{T}", 100, 0, 200);
   hist_CR2_DM_ele_pt             = new TH1D("hist_CR2_DM_ele_pt", "Leading e p_{T}", 100, 0, 200);
   hist_CR2_DM_mu_pt              = new TH1D("hist_CR2_DM_mu_pt", "Leading #mu p_{T}", 100, 0, 200);
   
   hist_zee_m_test                = new TH1D("hist_zee_m_test","mass of Z(ee)",60,30,150);
   hist_zmm_m_test                = new TH1D("hist_zmm_m_test","mass of Z(#mu#mu)",60,30,150);
   hist_zee_m_test2               = new TH1D("hist_zee_m_test2","mass of Z(ee)",60,30,150);
   hist_zmm_m_test2               = new TH1D("hist_zmm_m_test2","mass of Z(#mu#mu)",60,30,150);
   
   hist_zee_vtx_Reweight          = new TH1D("hist_zee_vtx_Reweight", "No. of vtx", 50,0,50);
   hist_zee_vtx                   = new TH1D("hist_zee_vtx", "No. of vtx", 50,0,50);
   hist_zee_e_pt                  = new TH1D("hist_zee_e_pt", "Leading e p_{T}", 100, 0, 200);
   hist_zee_e_eta                 = new TH1D("hist_zee_e_eta", "Leading e #eta", 100,-3.0,5.0);
   hist_zee_HT                    = new TH1D("hist_zee_HT", "Sum pT of Jets", 100, 0, 300);
   hist_zee_m_pt                  = new TH1D("hist_zee_m_pt", "Leading #mu p_{T}", 100, 0, 200);
   hist_zee_m_eta                 = new TH1D("hist_zee_m_eta", "Leading #mu #eta",100,-3.0,5.0);
   hist_zee_jet_pt                = new TH1D("hist_zee_jet_pt", "Jet p_{T}",100, 0, 200);
   hist_zee_jet_eta               = new TH1D("hist_zee_jet_eta", "Jet #eta",100, -3.0, 5.0);
   hist_zee_jet_csv               = new TH1D("hist_zee_jet_csv", "CSVv2 discriminant", 100, 0, 1);
   hist_zee_jet_csvSF             = new TH1D("hist_zee_jet_csvSF", "CSVv2 discriminant", 100, 0, 1);
   hist_zee_bjet_no               = new TH1D("hist_zee_bjet_no", "b-tagged jet #", 10, 0, 10);
   hist_zee_bjet_noSF             = new TH1D("hist_zee_bjet_noSF", "b-tagged jet #", 10, 0, 10);
   
   hist_zmm_vtx_Reweight          = new TH1D("hist_zmm_vtx_Reweight", "No. of vtx", 50,0,50);
   hist_zmm_vtx                   = new TH1D("hist_zmm_vtx", "No. of vtx", 50,0,50);
   hist_zmm_e_pt                  = new TH1D("hist_zmm_e_pt", "Leading e p_{T}", 100, 0, 200);
   hist_zmm_e_eta                 = new TH1D("hist_zmm_e_eta", "Leading e #eta", 100,-3.0,5.0);
   hist_zmm_HT                    = new TH1D("hist_zmm_HT", "Sum pT of Jets", 100, 0, 300);
   hist_zmm_m_pt                  = new TH1D("hist_zmm_m_pt", "Leading #mu p_{T}", 100, 0, 200);
   hist_zmm_m_eta                 = new TH1D("hist_zmm_m_eta", "Leading #mu #eta",100,-3.0,5.0);
   hist_zmm_jet_pt                = new TH1D("hist_zmm_jet_pt", "Jet p_{T}",100, 0, 200);
   hist_zmm_jet_eta               = new TH1D("hist_zmm_jet_eta", "Jet #eta",100, -3.0, 5.0);
   hist_zmm_jet_csv               = new TH1D("hist_zmm_jet_csv", "CSVv2 discriminant", 100, 0, 1);
   hist_zmm_jet_csvSF             = new TH1D("hist_zmm_jet_csvSF", "CSVv2 discriminant", 100, 0, 1);
   hist_zmm_bjet_no               = new TH1D("hist_zmm_bjet_no", "b-tagged jet #", 10, 0, 10);
   hist_zmm_bjet_noSF             = new TH1D("hist_zmm_bjet_noSF", "b-tagged jet #", 10, 0, 10);

   hist_first_pt                  = new TH1D("hist_first_pt", "Leading Lepton p_{T}", 100, 0, 200);
   hist_second_pt                 = new TH1D("hist_second_pt", "Second Lepton p_{T}", 100, 0, 200);
   hist_third_pt                  = new TH1D("hist_third_pt", "Third Lepton p_{T}", 100, 0, 200);
   hist_first_e_pt                = new TH1D("hist_first_e_pt", "Leading Lepton p_{T}", 100, 0, 200);
   hist_second_e_pt               = new TH1D("hist_second_e_pt", "Second Lepton p_{T}", 100, 0, 200);
   hist_third_e_pt                = new TH1D("hist_third_e_pt", "Third Lepton p_{T}", 100, 0, 200);
   hist_first_mu_pt               = new TH1D("hist_first_mu_pt", "Leading Lepton p_{T}", 100, 0, 200);
   hist_second_mu_pt              = new TH1D("hist_second_mu_pt", "Second Lepton p_{T}", 100, 0, 200);
   hist_third_mu_pt               = new TH1D("hist_third_mu_pt", "Third Lepton p_{T}", 100, 0, 200);
   hist_MVA_McZ_DE                = new TH2D("hist_MVA_McZ_DE", "MVA v.s. M(cZ)", 200,-1.0,1.0, 40,50,350); 
   hist_MVA_MbW_DE                = new TH2D("hist_MVA_MbW_DE", "MVA v.s. M(bW)", 200,-1.0,1.0, 40,50,350); 
   hist_MVA_McZ_DM                = new TH2D("hist_MVA_McZ_DM", "MVA v.s. M(cZ)", 200,-1.0,1.0, 40,50,350); 
   hist_MVA_MbW_DM                = new TH2D("hist_MVA_MbW_DM", "MVA v.s. M(bW)", 200,-1.0,1.0, 40,50,350);
   hist_MbW_McZ_DE                = new TH2D("hist_MbW_McZ_DE", "M(bW) v.s. M(cZ)", 40, 50, 350, 40, 50, 350);
   hist_MbW_McZ_DM                = new TH2D("hist_MbW_McZ_DM", "M(bW) v.s. M(cZ)", 40, 50, 350, 40, 50, 350);
   
   hist_e_pt_check1_DE            = new TH1D("hist_e_pt_check1_DE", "Leading e p_{T}", 100, 0, 200);
   hist_mu_pt_check1_DE           = new TH1D("hist_mu_pt_check1_DE", "Leading #mu p_{T}", 100, 0, 200);
   hist_mu_pt_check1_DM           = new TH1D("hist_mu_pt_check1_DM", "Leading #mu p_{T}", 100, 0, 200);
   hist_e_pt_check1_DM            = new TH1D("hist_e_pt_check1_DM", "Leading e p_{T}", 100, 0, 200);
   hist_e_pt_check2_DE            = new TH1D("hist_e_pt_check2_DE", "Leading e p_{T}", 100, 0, 200);
   hist_mu_pt_check2_DE           = new TH1D("hist_mu_pt_check2_DE", "Leading #mu p_{T}", 100, 0, 200);
   hist_mu_pt_check2_DM           = new TH1D("hist_mu_pt_check2_DM", "Leading #mu p_{T}", 100, 0, 200);
   hist_e_pt_check2_DM            = new TH1D("hist_e_pt_check2_DM", "Leading e p_{T}", 100, 0, 200);
  
   hist_top_dphi                  = new TH1D("hist_top_dphi", "top #phi" ,100,0,5);
   hist_top_tree                  = new TH1D("hist_top_tree", "M(cZ)", 40, 50, 350);
   hist_top_fcnc                  = new TH1D("hist_top_fcnc", "M(bW)", 40, 50, 350);

   hist_mva_3D_DE                 = new TH1D("hist_mva_3D_DE", "MVA in signal box", 200, -1.0, 1.0);
   hist_mva_3D_DM                 = new TH1D("hist_mva_3D_DM", "MVA in signal box", 200, -1.0, 1.0);

   hist_total_top_whole_DE        = new TH1D("hist_total_top_whole_DE", "Total Invariant top", 40, 0., 2000.);
   hist_total_top_whole_DM        = new TH1D("hist_total_top_whole_DM", "Total Invariant top", 40, 0., 2000.);
   hist_total_top_DE              = new TH1D("hist_total_top_DE", "Total Invariant top", 40, 0, 2000.);
   hist_fcnc_top_DE               = new TH1D("hist_fcnc_top_DE", "M_{cZ}", 40, 50, 350);
   hist_tree_top_DE               = new TH1D("hist_tree_top_DE", "M_{bW}", 40, 50, 350);
   hist_total_top_DM              = new TH1D("hist_total_top_DM", "Total Invariant top", 40, 0, 2000.);
   hist_fcnc_top_DM               = new TH1D("hist_fcnc_top_DM", "M_{cZ}", 40, 50, 350);
   hist_tree_top_DM               = new TH1D("hist_tree_top_DM", "M_{bW}", 40, 50, 350);
   hist_2D_top_DM                 = new TH2D("hist_2D_top_DM", "M(bW) v.s. M(cZ)", 40, 50, 350, 40, 50, 350);
   hist_2D_top_DE                 = new TH2D("hist_2D_top_DE", "M(bW) v.s. M(cZ)", 40, 50, 350, 40, 50, 350);
   hist_mva_DE                    = new TH1D("hist_mva_DE", "MVA Result", 200, -1.0, 1.0);
   hist_mva_DM                    = new TH1D("hist_mva_DM", "MVA Result", 200, -1.0, 1.0);
   hist_isoflip_DE                = new TH1D("hist_isoflip_DE","mass of Z(ee)",60,30,150);
   hist_isoflip_DM                = new TH1D("hist_isoflip_DM","mass of Z(ee)",60,30,150);
   hist_w_mt_DE                   = new TH1D("hist_w_mt_DE", "Transverse Mass of W", 40, 0, 300);
   hist_w_mt_DM                   = new TH1D("hist_w_mt_DM", "Transverse Mass of W", 40, 0, 300);
   hist_w_mt_DE_test              = new TH1D("hist_w_mt_DE_test", "Transverse Mass of W", 40, 0, 300);
   hist_w_mt_DM_test              = new TH1D("hist_w_mt_DM_test", "Transverse Mass of W", 40, 0, 300);
  
   hist_mva_eee                   = new TH1D("hist_mva_eee", "MVA Response", 200, -1.0, 1.0);
   hist_mva_eem                   = new TH1D("hist_mva_eem", "MVA Response", 200, -1.0, 1.0);
   hist_mva_emm                   = new TH1D("hist_mva_emm", "MVA Response", 200, -1.0, 1.0);
   hist_mva_mmm                   = new TH1D("hist_mva_mmm", "MVA Response", 200, -1.0, 1.0);
   hist_w_mt_eee                  = new TH1D("hist_w_mt_eee", "Transverse Mass of W", 40, 0, 300);   
   hist_w_mt_eem                  = new TH1D("hist_w_mt_eem", "Transverse Mass of W", 40, 0, 300);
   hist_w_mt_emm                  = new TH1D("hist_w_mt_emm", "Transverse Mass of W", 40, 0, 300);
   hist_w_mt_mmm                  = new TH1D("hist_w_mt_mmm", "Transverse Mass of W", 40, 0, 300);
   hist_Zmass_eee                 = new TH1D("hist_Zmass_eee","mass of Z(ee)",60,30,150);
   hist_Zmass_eem                 = new TH1D("hist_Zmass_eem","mass of Z(ee)",60,30,150);
   hist_Zmass_emm                 = new TH1D("hist_Zmass_emm","mass of Z(#mu#mu)",60,30,150);
   hist_Zmass_mmm                 = new TH1D("hist_Zmass_mmm","mass of Z(#mu#mu)",60,30,150);
   
   hist_b_no                      = new TH1D("hist_b_no","WZCR ratio", 25, 0, 25);
   hist_b_no_eee                  = new TH1D("hist_b_no_eee","WZCR ratio", 25, 0, 25);
   hist_b_no_eem                  = new TH1D("hist_b_no_eem","WZCR ratio", 25, 0, 25);
   hist_b_no_emm                  = new TH1D("hist_b_no_emm","WZCR ratio", 25, 0, 25);
   hist_b_no_mmm                  = new TH1D("hist_b_no_mmm","WZCR ratio", 25, 0, 25);

   hist_CJetBoost_E_DE            = new TH1D("hist_CJetBoost_E_DE", "CJetBoost_E", 20, 0, 500);
   hist_BJetBoost_E_DE            = new TH1D("hist_BJetBoost_E_DE", "BJetBoost_E", 20, 0, 500);
   hist_TopTop_dphi_DE            = new TH1D("hist_TopTop_dphi_DE", "TopTop_dphi", 20, 0, 3.14);
   hist_Z_cjet_dphi_DE            = new TH1D("hist_Z_cjet_dphi_DE", "Z_cjet_dphi", 20, 0, 3.14);
   hist_Z_bjet_dphi_DE            = new TH1D("hist_Z_bjet_dphi_DE", "Z_bjet_dphi", 20, 0, 3.14);
   hist_W_cjet_dphi_DE            = new TH1D("hist_W_cjet_dphi_DE", "W_cjet_dphi", 20, 0, 3.14);
   hist_W_bjet_dphi_DE            = new TH1D("hist_W_bjet_dphi_DE", "W_bjet_dphi", 20, 0, 3.14);
   hist_ZLLpair_dphi_DE           = new TH1D("hist_ZLLpair_dphi_DE", "ZLLpair_dphi", 20, 0, 3.14);
   hist_WLZL1_dphi_DE             = new TH1D("hist_WLZL1_dphi_DE", "WLZL1_dphi", 20, 0, 3.14);
   hist_WLZL2_dphi_DE             = new TH1D("hist_WLZL2_dphi_DE", "WLZL2_dphi", 20, 0, 3.14);
   hist_WLep_bjet_dphi_DE         = new TH1D("hist_WLep_bjet_dphi_DE", "WLep_bjet_dphi", 20, 0, 3.14);
   hist_ZLep1_bjet_dphi_DE        = new TH1D("hist_ZLep1_bjet_dphi_DE", "ZLep1_bjet_dphi", 20, 0, 3.14);
   hist_ZLep2_bjet_dphi_DE        = new TH1D("hist_ZLep2_bjet_dphi_DE", "ZLep2_bjet_dphi", 20, 0, 3.14);
   hist_WLep_cjet_dphi_DE         = new TH1D("hist_WLep_cjet_dphi_DE", "WLep_cjet_dphi", 20, 0, 3.14);
   hist_ZLep1_cjet_dphi_DE        = new TH1D("hist_ZLep1_cjet_dphi_DE", "ZLep1_cjet_dphi", 20, 0, 3.14);
   hist_ZLep2_cjet_dphi_DE        = new TH1D("hist_ZLep2_cjet_dphi_DE", "ZLep2_cjet_dphi", 20, 0, 3.14);
   hist_BJet_btag_DE              = new TH1D("hist_BJet_btag_DE", "BJet_btag", 20, 0.5, 1);
   hist_CJet_btag_DE              = new TH1D("hist_CJet_btag_DE", "CJet_btag", 20, 0, 1);
   hist_TopTop_deta_DE            = new TH1D("hist_TopTop_deta_DE", "TopTop_deta", 20, 0., 3.5);
   hist_Z_cjet_deta_DE            = new TH1D("hist_Z_cjet_deta_DE", "Z_cjet_deta", 20, 0., 5);
   hist_Z_bjet_deta_DE            = new TH1D("hist_Z_bjet_deta_DE", "Z_bjet_deta", 20, 0., 5);
   hist_W_bjet_deta_DE            = new TH1D("hist_W_bjet_deta_DE", "W_bjet_deta", 20, 0., 5);
   hist_W_cjet_deta_DE            = new TH1D("hist_W_cjet_deta_DE", "W_cjet_deta", 20, 0., 5);
   hist_ZLLpair_deta_DE           = new TH1D("hist_ZLLpair_deta_DE", "ZLLpair_deta", 20, 0, 3.5);
   hist_WLZL1_deta_DE             = new TH1D("hist_WLZL1_deta_DE", "WLZL1_deta", 20, 0, 5);
   hist_WLZL2_deta_DE             = new TH1D("hist_WLZL2_deta_DE", "WLZL2_deta", 20, 0, 5);
   hist_WLep_bjet_deta_DE         = new TH1D("hist_WLep_bjet_deta_DE", "WLep_bjet_deta", 20, 0., 5);
   hist_ZLep1_bjet_deta_DE        = new TH1D("hist_ZLep1_bjet_deta_DE", "ZLep1_bjet_deta", 20, 0., 5);
   hist_ZLep2_bjet_deta_DE        = new TH1D("hist_ZLep2_bjet_deta_DE", "ZLep2_bjet_deta", 20, 0., 5);
   hist_WLep_cjet_deta_DE         = new TH1D("hist_WLep_cjet_deta_DE", "WLep_cjet_deta", 20, 0., 5);
   hist_ZLep1_cjet_deta_DE        = new TH1D("hist_ZLep1_cjet_deta_DE", "ZLep1_cjet_deta", 20, 0., 5);
   hist_ZLep2_cjet_deta_DE        = new TH1D("hist_ZLep2_cjet_deta_DE", "ZLep2_cjet_deta", 20, 0., 5);
    
   hist_CJetBoost_E_DM            = new TH1D("hist_CJetBoost_E_DM", "CJetBoost_E", 20, 0, 500);
   hist_BJetBoost_E_DM            = new TH1D("hist_BJetBoost_E_DM", "BJetBoost_E", 20, 0, 500);
   hist_TopTop_dphi_DM            = new TH1D("hist_TopTop_dphi_DM", "TopTop_dphi", 20, 0, 3.14);
   hist_Z_cjet_dphi_DM            = new TH1D("hist_Z_cjet_dphi_DM", "Z_cjet_dphi", 20, 0, 3.14);
   hist_Z_bjet_dphi_DM            = new TH1D("hist_Z_bjet_dphi_DM", "Z_bjet_dphi", 20, 0, 3.14);
   hist_W_cjet_dphi_DM            = new TH1D("hist_W_cjet_dphi_DM", "W_cjet_dphi", 20, 0, 3.14);
   hist_W_bjet_dphi_DM            = new TH1D("hist_W_bjet_dphi_DM", "W_bjet_dphi", 20, 0, 3.14);
   hist_ZLLpair_dphi_DM           = new TH1D("hist_ZLLpair_dphi_DM", "ZLLpair_dphi", 20, 0, 3.14);
   hist_WLZL1_dphi_DM             = new TH1D("hist_WLZL1_dphi_DM", "WLZL1_dphi", 20, 0, 3.14);
   hist_WLZL2_dphi_DM             = new TH1D("hist_WLZL2_dphi_DM", "WLZL2_dphi", 20, 0, 3.14);
   hist_WLep_bjet_dphi_DM         = new TH1D("hist_WLep_bjet_dphi_DM", "WLep_bjet_dphi", 20, 0, 3.14);
   hist_ZLep1_bjet_dphi_DM        = new TH1D("hist_ZLep1_bjet_dphi_DM", "ZLep1_bjet_dphi", 20, 0, 3.14);
   hist_ZLep2_bjet_dphi_DM        = new TH1D("hist_ZLep2_bjet_dphi_DM", "ZLep2_bjet_dphi", 20, 0, 3.14);
   hist_WLep_cjet_dphi_DM         = new TH1D("hist_WLep_cjet_dphi_DM", "WLep_cjet_dphi", 20, 0, 3.14);
   hist_ZLep1_cjet_dphi_DM        = new TH1D("hist_ZLep1_cjet_dphi_DM", "ZLep1_cjet_dphi", 20, 0, 3.14);
   hist_ZLep2_cjet_dphi_DM        = new TH1D("hist_ZLep2_cjet_dphi_DM", "ZLep2_cjet_dphi", 20, 0, 3.14);
   hist_BJet_btag_DM              = new TH1D("hist_BJet_btag_DM", "BJet_btag", 20, 0.5, 1);
   hist_CJet_btag_DM              = new TH1D("hist_CJet_btag_DM", "CJet_btag", 20, 0, 1);
   hist_TopTop_deta_DM            = new TH1D("hist_TopTop_deta_DM", "TopTop_deta", 20, 0., 3.5);
   hist_Z_cjet_deta_DM            = new TH1D("hist_Z_cjet_deta_DM", "Z_cjet_deta", 20, 0., 5);
   hist_Z_bjet_deta_DM            = new TH1D("hist_Z_bjet_deta_DM", "Z_bjet_deta", 20, 0., 5);
   hist_W_bjet_deta_DM            = new TH1D("hist_W_bjet_deta_DM", "W_bjet_deta", 20, 0., 5);
   hist_W_cjet_deta_DM            = new TH1D("hist_W_cjet_deta_DM", "W_cjet_deta", 20, 0., 5);
   hist_ZLLpair_deta_DM           = new TH1D("hist_ZLLpair_deta_DM", "ZLLpair_deta", 20, 0, 3.5);
   hist_WLZL1_deta_DM             = new TH1D("hist_WLZL1_deta_DM", "WLZL1_deta", 20, 0, 5);
   hist_WLZL2_deta_DM             = new TH1D("hist_WLZL2_deta_DM", "WLZL2_deta", 20, 0, 5);
   hist_WLep_bjet_deta_DM         = new TH1D("hist_WLep_bjet_deta_DM", "WLep_bjet_deta", 20, 0., 5);
   hist_ZLep1_bjet_deta_DM        = new TH1D("hist_ZLep1_bjet_deta_DM", "ZLep1_bjet_deta", 20, 0., 5);
   hist_ZLep2_bjet_deta_DM        = new TH1D("hist_ZLep2_bjet_deta_DM", "ZLep2_bjet_deta", 20, 0., 5);
   hist_WLep_cjet_deta_DM         = new TH1D("hist_WLep_cjet_deta_DM", "WLep_cjet_deta", 20, 0., 5);
   hist_ZLep1_cjet_deta_DM        = new TH1D("hist_ZLep1_cjet_deta_DM", "ZLep1_cjet_deta", 20, 0., 5);
   hist_ZLep2_cjet_deta_DM        = new TH1D("hist_ZLep2_cjet_deta_DM", "ZLep2_cjet_deta", 20, 0., 5);
 
   hist_pT_optimization           = new TH1D("hist_pT_optimization", "Optimization on Lepton pT", 40, 0, 40);
   hist_trigger_eff_mmm           = new TH1D("hist_trigger_eff_mmm", "trigger_eff_mmm", 20, 0, 500);
   hist_trigger_eff_mme           = new TH1D("hist_trigger_eff_mme", "trigger_eff_mme", 20, 0, 500);
   hist_trigger_eff_mee           = new TH1D("hist_trigger_eff_mee", "trigger_eff_mee", 20, 0, 500);
   hist_trigger_eff_eee           = new TH1D("hist_trigger_eff_eee", "trigger_eff_eee", 20, 0, 500);
   hist_PDF_combined              = new TH1D("hist_PDF_combined", "PDF_Unc", 300, 0, 300); 
   hist_PDFun_eee                 = new TH1D("hist_PDFun_eee", "PDF_Unc", 300, 0, 300); 
   hist_PDFun_eem                 = new TH1D("hist_PDFun_eem", "PDF_Unc", 300, 0, 300); 
   hist_PDFun_emm                 = new TH1D("hist_PDFun_emm", "PDF_Unc", 300, 0, 300); 
   hist_PDFun_mmm                 = new TH1D("hist_PDFun_mmm", "PDF_Unc", 300, 0, 300); 
   hist_evt_weightB               = new TH1D("hist_evt_weightB", "Before_Btagging", 50, 0, 50);
   hist_evt_weightA               = new TH1D("hist_evt_weightA", "Aefore_Btagging", 50, 0, 50);
//}}}
         // mvaTree{{{   
   mvaTree = new TTree("mvaTree", "Tree for MVA studies");

   mvaTree->Branch("TopInfo_Pt_bw", &TopInfo_Pt_bw, "TopInfo_Pt_bw/F");
   mvaTree->Branch("TopInfo_M_bw", &TopInfo_M_bw, "TopInfo_M_bw/F");
   mvaTree->Branch("TopInfo_Mt_bw", &TopInfo_Mt_bw, "TopInfo_Mt_bw/F");
   mvaTree->Branch("TopInfo_Pt_cz", &TopInfo_Pt_cz, "TopInfo_Pt_cz/F");
   mvaTree->Branch("TopInfo_M_cz", &TopInfo_M_cz, "TopInfo_M_cz/F");
   mvaTree->Branch("TopInfo_Mt_cz", &TopInfo_Mt_cz, "TopInfo_Mt_cz/F");
   mvaTree->Branch("TopInfo_MCTruth", &TopInfo_MCTruth, "TopInfo_MCTruth/I");

   mvaTree->Branch("CJetBoost_E", &CJetBoost_E, "CJetBoost_E/F");
   mvaTree->Branch("BJetBoost_E", &BJetBoost_E, "BJetBoost_E/F");
   mvaTree->Branch("WInfo_Pt", &WInfo_Pt, "WInfo_Pt/F");
   mvaTree->Branch("WInfo_Mt", &WInfo_Mt, "WInfo_Mt/F");
   mvaTree->Branch("ZInfo_Pt", &ZInfo_Pt, "ZInfo_Pt/F");
   mvaTree->Branch("ZInfo_M", &ZInfo_M, "ZInfo_M/F");
   
   mvaTree->Branch("TopTop_dphi", &TopTop_dphi, "TopTop_dphi/F");
   mvaTree->Branch("Z_cjet_dphi", &Z_cjet_dphi, "Z_cjet_dphi/F");
   mvaTree->Branch("Z_bjet_dphi", &Z_bjet_dphi, "Z_bjet_dphi/F");
   mvaTree->Branch("W_cjet_dphi", &W_cjet_dphi, "W_cjet_dphi/F");
   mvaTree->Branch("W_bjet_dphi", &W_bjet_dphi, "W_bjet_dphi/F");
   mvaTree->Branch("ZLLpair_dphi", &ZLLpair_dphi, "ZLLpair_dphi/F");
   mvaTree->Branch("WLZL1_dphi", &WLZL1_dphi, "WLZL1_dphi/F");
   mvaTree->Branch("WLZL2_dphi", &WLZL2_dphi, "WLZL2_dphi/F");
   mvaTree->Branch("WLep_bjet_dphi", &WLep_bjet_dphi, "WLep_bjet_dphi/F");
   mvaTree->Branch("ZLep1_bjet_dphi", &ZLep1_bjet_dphi, "ZLep1_bjet_dphi/F");
   mvaTree->Branch("ZLep2_bjet_dphi", &ZLep2_bjet_dphi, "ZLep2_bjet_dphi/F");
   mvaTree->Branch("WLep_cjet_dphi", &WLep_cjet_dphi, "WLep_cjet_dphi/F");
   mvaTree->Branch("ZLep1_cjet_dphi", &ZLep1_cjet_dphi, "ZLep1_cjet_dphi/F");
   mvaTree->Branch("ZLep2_cjet_dphi", &ZLep2_cjet_dphi, "ZLep2_cjet_dphi/F");
   
   mvaTree->Branch("TopTop_dtheta", &TopTop_dtheta, "TopTop_dtheta/F");
   mvaTree->Branch("Z_cjet_dtheta", &Z_cjet_dtheta, "Z_cjet_dtheta/F");
   mvaTree->Branch("Z_bjet_dtheta", &Z_bjet_dtheta, "Z_bjet_dtheta/F");
   mvaTree->Branch("W_cjet_dtheta", &W_cjet_dtheta, "W_cjet_dtheta/F");
   mvaTree->Branch("W_bjet_dtheta", &W_bjet_dtheta, "W_bjet_dtheta/F");
   mvaTree->Branch("ZLLpair_dtheta", &ZLLpair_dtheta, "ZLLpair_dtheta/F");
   mvaTree->Branch("WLZL1_dtheta", &WLZL1_dtheta, "WLZL1_dtheta/F");
   mvaTree->Branch("WLZL2_dtheta", &WLZL2_dtheta, "WLZL2_dtheta/F");
   mvaTree->Branch("WLep_bjet_dtheta", &WLep_bjet_dtheta, "WLep_bjet_dtheta/F");
   mvaTree->Branch("ZLep1_bjet_dtheta", &ZLep1_bjet_dtheta, "ZLep1_bjet_dtheta/F");
   mvaTree->Branch("ZLep2_bjet_dtheta", &ZLep2_bjet_dtheta, "ZLep2_bjet_dtheta/F");
   mvaTree->Branch("WLep_cjet_dtheta", &WLep_cjet_dtheta, "WLep_cjet_dtheta/F");
   mvaTree->Branch("ZLep1_cjet_dtheta", &ZLep1_cjet_dtheta, "ZLep1_cjet_dtheta/F");
   mvaTree->Branch("ZLep2_cjet_dtheta", &ZLep2_cjet_dtheta, "ZLep2_cjet_dtheta/F");

   mvaTree->Branch("BJet_btag", &BJet_btag, "BJet_btag/F");
   mvaTree->Branch("BJet_ctag", &BJet_ctag, "BJet_ctag/F");
   mvaTree->Branch("CJet_btag", &CJet_btag, "CJet_btag/F");
   mvaTree->Branch("CJet_ctag", &CJet_ctag, "CJet_ctag/F");
//--- ---------------------new adding variables------------------------------//{{{
   mvaTree->Branch("TopTop_deta", &TopTop_deta, "TopTop_deta/F");
   mvaTree->Branch("Z_cjet_deta", &Z_cjet_deta, "Z_cjet_deta/F");
   mvaTree->Branch("Z_bjet_deta", &Z_bjet_deta, "Z_bjet_deta/F");
   mvaTree->Branch("W_cjet_deta", &W_cjet_deta, "W_cjet_deta/F");
   mvaTree->Branch("W_bjet_deta", &W_bjet_deta, "W_bjet_deta/F");
   mvaTree->Branch("ZLLpair_deta", &ZLLpair_deta, "ZLLpair_deta/F");
   mvaTree->Branch("WLZL1_deta", &WLZL1_deta, "WLZL1_deta/F");
   mvaTree->Branch("WLZL2_deta", &WLZL2_deta, "WLZL2_deta/F");
   mvaTree->Branch("WLep_bjet_deta", &WLep_bjet_deta, "WLep_bjet_deta/F");
   mvaTree->Branch("ZLep1_bjet_deta", &ZLep1_bjet_deta, "ZLep1_bjet_deta/F");
   mvaTree->Branch("ZLep2_bjet_deta", &ZLep2_bjet_deta, "ZLep2_bjet_deta/F");
   mvaTree->Branch("WLep_cjet_deta", &WLep_cjet_deta, "WLep_cjet_deta/F");
   mvaTree->Branch("ZLep1_cjet_deta", &ZLep1_cjet_deta, "ZLep1_cjet_deta/F");
   mvaTree->Branch("ZLep2_cjet_deta", &ZLep2_cjet_deta, "ZLep2_cjet_deta/F");
   mvaTree->Branch("jet_mva_no", &jet_mva_no, "jet_mva_no/I");
   mvaTree->Branch("lep_mva_no", &lep_mva_no, "lep_mva_no/I");
   mvaTree->Branch("jet_mva_event_orignal_no", &jet_mva_event_orignal_no, "jet_mva_event_orignal_no/I");
   mvaTree->Branch("lep_mva_event_orignal_no", &lep_mva_event_orignal_no, "lep_mva_event_orignal_no/I");
   mvaTree->Branch("MVAweight", &MVAweight, "MVAweight/F");
//------------------------new adding variables------------------------------//}}}
   
   mvaTree->Branch("mvaOCPE", &mvaOCPE, "mvaOCPE/F");
   
   fOutput->Add(mvaTree);

   //MVA for Sorting 
   sorting = new TMVA::Reader( "!Color:!Silent" );
   sorting->AddVariable( "CJetBoost_E", &CJetBoost_E );
   sorting->AddVariable( "BJetBoost_E", &BJetBoost_E );
   sorting->AddVariable( "TopTop_dphi", &TopTop_dphi );
   //sorting->AddVariable( "Z_cjet_dphi", &Z_cjet_dphi );
   sorting->AddVariable( "W_cjet_dphi", &W_cjet_dphi );
   sorting->AddVariable( "W_bjet_dphi", &W_bjet_dphi );
   sorting->AddVariable( "ZLLpair_dphi", &ZLLpair_dphi );
   sorting->AddVariable( "WLZL1_dphi", &WLZL1_dphi );
   sorting->AddVariable( "WLZL2_dphi", &WLZL2_dphi );
   sorting->AddVariable( "ZLep2_bjet_dphi", &ZLep2_bjet_dphi );
   sorting->AddVariable( "ZLep2_cjet_dphi", &ZLep2_cjet_dphi );
   sorting->AddVariable( "BJet_btag", &BJet_btag );
   sorting->AddVariable( "CJet_btag", &CJet_btag );
   //sorting->AddVariable( "TopTop_deta", &TopTop_deta );
   //sorting->AddVariable( "Z_cjet_deta", &Z_cjet_deta );
   //sorting->AddVariable( "Z_bjet_deta", &Z_bjet_deta );
   sorting->AddVariable( "W_bjet_deta", &W_bjet_deta );
   //sorting->AddVariable( "W_cjet_deta", &W_cjet_deta );
   sorting->AddVariable( "ZLLpair_deta", &ZLLpair_deta );
   //sorting->AddVariable( "WLZL1_deta", &WLZL1_deta );
   sorting->AddVariable( "WLZL2_deta", &WLZL2_deta );
   sorting->AddVariable( "WLep_cjet_deta", &WLep_cjet_deta );
   //sorting->AddVariable( "ZLep2_cjet_deta", &ZLep2_cjet_deta );
   
   sorting->AddSpectator( "TopInfo_M_bw", &TopInfo_M_bw );
   sorting->AddSpectator( "TopInfo_M_cz", &TopInfo_M_cz );
   //sorting->BookMVA( "Sorting_Value", "./sorting/Final_MVA/weights/TMVAClassification_BDTG.weights.xml" );  
   //sorting->BookMVA( "Sorting_Value", "./sorting/Final_New/weights/TMVAClassification_BDT.weights.xml" );  
   sorting->BookMVA( "Sorting_Value", "./sorting/94X/2017/zct/dataset/weights/TMVAClassification_BDTG.weights.xml" );  

   //MVA for SignalExtraction
   readerOCPE = new TMVA::Reader( "!Color:!Silent" );

   readerOCPE->AddVariable( "CJetBoost_E", &CJetBoost_E );
   readerOCPE->AddVariable( "BJetBoost_E", &BJetBoost_E );
   readerOCPE->AddVariable( "TopTop_dphi", &TopTop_dphi );
   readerOCPE->AddVariable( "Z_cjet_dphi", &Z_cjet_dphi );
   //readerOCPE->AddVariable( "Z_bjet_dphi", &Z_bjet_dphi );
   //readerOCPE->AddVariable( "W_cjet_dphi", &W_cjet_dphi );
   readerOCPE->AddVariable( "W_bjet_dphi", &W_bjet_dphi );
   readerOCPE->AddVariable( "ZLLpair_dphi", &ZLLpair_dphi );
   readerOCPE->AddVariable( "WLZL1_dphi", &WLZL1_dphi );
   readerOCPE->AddVariable( "WLZL2_dphi", &WLZL2_dphi );
   //readerOCPE->AddVariable( "WLep_bjet_dphi", &WLep_bjet_dphi );
   //readerOCPE->AddVariable( "ZLep1_bjet_dphi", &ZLep1_bjet_dphi );
   readerOCPE->AddVariable( "ZLep2_bjet_dphi", &ZLep2_bjet_dphi );
   readerOCPE->AddVariable( "WLep_cjet_dphi", &WLep_cjet_dphi );
   //readerOCPE->AddVariable( "ZLep1_cjet_dphi", &ZLep1_cjet_dphi );
   //readerOCPE->AddVariable( "ZLep2_cjet_dphi", &ZLep2_cjet_dphi );

   readerOCPE->AddVariable( "BJet_btag", &BJet_btag );
//   readerOCPE->AddVariable( "BJet_ctag", &BJet_ctag );
   readerOCPE->AddVariable( "CJet_btag", &CJet_btag );
//   readerOCPE->AddVariable( "CJet_ctag", &CJet_ctag );

   //readerOCPE->AddVariable( "TopTop_deta", &TopTop_deta );
   //readerOCPE->AddVariable( "Z_cjet_deta", &Z_cjet_deta );
   readerOCPE->AddVariable( "W_bjet_deta", &W_bjet_deta );

   //readerOCPE->AddVariable( "W_bjet_deta", &W_bjet_deta );
   readerOCPE->AddVariable( "ZLLpair_deta", &ZLLpair_deta );
   readerOCPE->AddVariable( "WLZL1_deta", &WLZL1_deta );
   //readerOCPE->AddVariable( "WLZL2_deta", &WLZL2_deta );
   //readerOCPE->AddVariable( "WLep_cjet_deta", &WLep_cjet_deta );
   readerOCPE->AddVariable( "ZLep1_cjet_deta", &ZLep1_cjet_deta );
   //readerOCPE->AddVariable( "ZLep2_cjet_deta", &ZLep2_cjet_deta );

/* For BDT sorting 
   readerOCPE->AddVariable( "CJetBoost_E", &CJetBoost_E );
   readerOCPE->AddVariable( "BJetBoost_E", &BJetBoost_E );
   readerOCPE->AddVariable( "TopTop_dphi", &TopTop_dphi );
   readerOCPE->AddVariable( "Z_cjet_dphi", &Z_cjet_dphi );
   readerOCPE->AddVariable( "W_bjet_dphi", &W_bjet_dphi );
   readerOCPE->AddVariable( "WLep_bjet_dphi", &WLep_bjet_dphi );
   readerOCPE->AddVariable( "ZLep1_cjet_dphi", &ZLep1_cjet_dphi );
*/
   readerOCPE->AddSpectator( "TopInfo_M_bw", &TopInfo_M_bw );
   readerOCPE->AddSpectator( "TopInfo_M_cz", &TopInfo_M_cz );

   //readerOCPE->SetWeightExpression( "Event_Weight" );
   //readerOCPE->BookMVA( "myOCPE", "TMVAClassification_Likelihood.weights.xml" );
   //readerOCPE->BookMVA( "myOCPE", "./TMVAClassification_BDT.weights.xml" );  
   //readerOCPE->BookMVA( "myOCPE", "./SignalExtraction/MET30/weights/TMVAClassification_BDTG.weights.xml" );  
   readerOCPE->BookMVA( "myOCPE", "./SignalExtraction/94X/2017/zct/dataset/weights/TMVAClassification_BDT.weights.xml" );  
   //readerOCPE->BookMVA( "myOCPE", "./sorting/TMVAClassification_BDTG.weights.xml" );  
   //readerOCPE->BookMVA( "myOCPE", "TMVAClassification_MLPBNN.weights.xml" );
   
   
   //FullCut = chain.CloneTree(0);
   //FullCut->SetName("FullCut");
//}}}
   
}

Bool_t MyTcZAna_2017_Central::Process(Long64_t entry)
{
   Long64_t Event_Tot =  fReader.GetEntries(true); 
   printf("[%lld|%lld]\r",Event_Tot,entry);
   fflush(stdout);
   fReader.SetLocalEntry(entry);
   Event_Weight_lep=1.0; //only apply lepton ID SF
   Event_Weight=1.0;

//*********simulated event weight**********//
   if(*EvtInfo_McFlag>0) {
        if(*EvtInfo_Weight>0.0){
            //postive_number++;
            //Event_Weight = 1.0;
            //Event_Weight_lep = 1.0;
            postive_number += *EvtInfo_Weight;
            Event_Weight = *EvtInfo_Weight;
            Event_Weight_lep *= *EvtInfo_Weight;
        }
        else if(*EvtInfo_Weight<0.0){
            //negative_number++;
            //Event_Weight = -1.0;
            //Event_Weight_lep = -1.0;
            negative_number += *EvtInfo_Weight;
            Event_Weight = *EvtInfo_Weight;
            Event_Weight_lep *= *EvtInfo_Weight;
        }   
   }
   else{
       Event_Weight = 1.0;
       Event_Weight_lep = 1.0;
   }
//*****************************************//
//**********METFilter**********************//
   if(*Flag_METFilter<1) return(kFALSE);

   m_gen_zee_idx=-1;
   m_gen_wuu_idx=-1;
   m_gen_top1_idx=-1;
   m_gen_top2_idx=-1;
   m_gen_lep1_idx=-1;
   m_gen_lep2_idx=-1;
   m_gen_lep3_idx=-1;
   m_gen_lep4_idx=-1;
   m_gen_jet1_idx=-1;
   m_gen_jet2_idx=-1;

   m_ht = m_st = 0.;


   if(*EvtInfo_McFlag > 0){ // MC events
     if(*GenParts_Size > 512) cout << "!!!\n\n";
     
     for(int git=0; git < *GenParts_Size && git < MAX_GENS; git++){
      
         if(GenParts_Pt[git] <0.01) continue;
         GenParts_P4[git].SetPtEtaPhiM(GenParts_Pt[git], GenParts_Eta[git],
                                     GenParts_Phi[git], GenParts_Mass[git]);
         if(m_gen_zee_idx==-1 &&
            GenParts_PdgID[git]==23 && GenParts_Status[git]<30){
            m_gen_zee_idx=git;
          }
       
         if(m_gen_wuu_idx==-1 &&
            fabs(GenParts_PdgID[git])==24 && GenParts_Status[git]<30){
            m_gen_wuu_idx=git;
         }
      
         if(m_gen_jet1_idx==-1 &&  // b-jet
            fabs(GenParts_PdgID[git])==5 && GenParts_Status[git]<30){
            m_gen_jet1_idx=git;
         }
       
         if(m_gen_jet2_idx==-1 && m_gen_zee_idx!=-1 && m_gen_zee_idx!=-1 &&
            (fabs(GenParts_PdgID[git])==2 || fabs(GenParts_PdgID[git])==4) &&
            GenParts_Status[git]<30){
            m_gen_jet2_idx=git;  // light jet
          }
         
//         for(int i=m_gen_wuu_idx ; i<*GenParts_Size ; i++){
//             if(abs(GenParts_PdgID[i])==24){
//                m_gen_lep1_idx=GenParts_Da1[i];
//                m_gen_lep2_idx=GenParts_Da2[i];
//             }
//             if(abs(GenParts_PdgID[m_gen_lep1_idx])!=24 && abs(GenParts_PdgID[m_gen_lep2_idx])!=24) break;
//         }
//         for(int j=m_gen_zee_idx ; j<*GenParts_Size ; j++){
//             if(abs(GenParts_PdgID[j])==23){
//                m_gen_lep3_idx=GenParts_Da1[j];
//                m_gen_lep4_idx=GenParts_Da2[j];
//             }
//             if(abs(GenParts_PdgID[m_gen_lep3_idx])!=23 && abs(GenParts_PdgID[m_gen_lep4_idx])!=23) break;
//         }

         if(m_gen_top1_idx==-1 && 
            fabs(GenParts_PdgID[git]) == 6 &&
            fabs(GenParts_PdgID[git+1]) == 6){
            m_gen_top1_idx = git;
            m_gen_top2_idx = git+1;
          }
       
/*       if(m_gen_zee_idx!=-1 && m_gen_top2_idx!=-1 &&
          GenParts_Index[m_gen_top2_idx]==                //had been revised(2018.07.27)(GenParts_Index->GenParts_Size)
          (GenParts_Mo1[m_gen_zee_idx]-1)){
         m_gen_top1_idx=m_gen_top1_idx+1;
         m_gen_top2_idx=m_gen_top2_idx-1;  // swap them
       }
  */     
       if(Event_Weight_Tot < 10 && 
          ( (GenParts_Status[git] >= 3 && (GenParts_Status[git] < 30 )) )){
         if(git == 0) cout << endl;
         cout << "MC evt. " << *EvtInfo_EvtNo << " #" << git << " "
              << GenParts_PdgID[git] << " Mo: " << GenParts_Mo1[git]
              << ","
              << GenParts_Mo2[git] << " Da: " << GenParts_Da1[git]
              << ","
              << GenParts_Da2[git] << " Status: " << GenParts_Status[git] << " pdgID: " << GenParts_PdgID[git];
         
         if(m_gen_top1_idx == git)
           cout << " *\n";
         else if(m_gen_top2_idx == git)
           cout << " &\n";
         else if(m_gen_wuu_idx == git)
           cout << " W\n";
         else if(m_gen_zee_idx == git)
           cout << " Z\n";
         else if(m_gen_jet1_idx == git)
           cout << " b\n";
         else if(m_gen_jet2_idx == git && fabs(GenParts_PdgID[git])==2)
           cout << " u\n";
         else if(m_gen_jet2_idx == git && fabs(GenParts_PdgID[git])==4)
           cout << " c\n";
//         else if(m_gen_lep1_idx == git)
//           cout << " lep1\n";
//         else if(m_gen_lep2_idx == git)
//           cout << " nu\n";
//         else if(m_gen_lep3_idx == git)
//           cout << " lep3\n";
//         else if(m_gen_lep4_idx == git)
//           cout << " lep4\n";
         else
           cout << endl;
       }
     } // GEN loop
   } // MC if

   hist_evt_cut->Fill(0., Event_Weight);
   hist_evt_cut_e->Fill(0., Event_Weight);
   hist_evt_cut_m->Fill(0., Event_Weight);
   
   Event_Weight_Tot += Event_Weight;
   Event_Tot ++;

   //if(Event_Tot%10000 ==0 && Event_Tot>0) cout << "." << std::flush;

//{{{***********************HLT****************************

   if(
        //di-Muon trigger
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v4] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v7] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v8] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v9] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v10] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v11] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v12] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v13] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v14] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v15] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v7] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v2] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v4] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v6] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v7] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v8] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v9] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v10] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v11] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v12] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v13] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v14] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v2] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v5] == 1 ||
      (int)EvtInfo_TrgBook[HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v4] == 1 ||
      (int)EvtInfo_TrgBook[HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v4] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v1] == 1 || 
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v2] == 1 || 
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v3] == 1 || 
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v4] == 1 || 
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v5] == 1 || 
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v7] == 1 || 
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v8] == 1  
        //Single Muon trigger
/*      (int)EvtInfo_TrgBook[HLT_IsoTkMu22_v2] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoTkMu22_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoTkMu22_v4] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoTkMu22_v5] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu22_v1] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu22_v2] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu22_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu22_v5] == 1 ) hist_evt_cut_m->Fill(1., Event_Weight);*/
      
      /*(int)EvtInfo_TrgBook[HLT_IsoMu24_v1] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu24_v2] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoMu24_v4] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoTkMu24_v1] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoTkMu24_v2] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoTkMu24_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_IsoTkMu24_v4] == 1 */ ) hist_evt_cut_m->Fill(1., Event_Weight);
      
      
   if(
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v4] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v5] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v6] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v7] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v8] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v9] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v10] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v11] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v12] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v13] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v14] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v15] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v16] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v17] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v18] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v19] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v11] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v12] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v13] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v14] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v15] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v16] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v17] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v18] == 1 ||
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v19] == 1 ) hist_evt_cut_e->Fill(1., Event_Weight);
   
   if(
           //MET Trigger
      //(int)EvtInfo_TrgBook[HLT_PFHT300_PFMET110_v1] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFHT300_PFMET110_v2] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFHT300_PFMET110_v3] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFHT300_PFMET110_v4] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFHT300_PFMET110_v6] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_MET200_v1] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_MET200_v2] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_MET200_v3] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_MET200_v4] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_MET200_v5] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET300_v1] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET300_v2] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET300_v3] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET300_v4] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET300_v6] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET300_v7] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET120_PFMHT120_IDTight_v1] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET120_PFMHT120_IDTight_v2] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET120_PFMHT120_IDTight_v3] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET120_PFMHT120_IDTight_v4] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET120_PFMHT120_IDTight_v5] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET120_PFMHT120_IDTight_v7] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET120_PFMHT120_IDTight_v8] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET170_HBHECleaned_v1] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET170_HBHECleaned_v2] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET170_HBHECleaned_v3] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET170_HBHECleaned_v4] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET170_HBHECleaned_v5] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET170_HBHECleaned_v6] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET170_HBHECleaned_v8] != 1 &&
      //(int)EvtInfo_TrgBook[HLT_PFMET170_HBHECleaned_v9] != 1 &&


      //di-Muon trigger
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v3] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v4] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v7] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v8] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v9] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v10] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v11] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v12] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v13] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v14] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v15] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v7] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v2] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v3] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v4] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v6] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v7] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v8] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v9] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v10] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v11] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v12] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v13] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v14] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v2] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v3] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v5] != 1 &&
      (int)EvtInfo_TrgBook[HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3] != 1 &&
      (int)EvtInfo_TrgBook[HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v4] != 1 &&
      (int)EvtInfo_TrgBook[HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v3] != 1 &&
      (int)EvtInfo_TrgBook[HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v4] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v1] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v2] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v3] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v4] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v5] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v7] != 1 &&
      (int)EvtInfo_TrgBook[HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v8] != 1 &&
        //Single Muon trigger
    
//      (int)EvtInfo_TrgBook[HLT_IsoMu24_v1] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoMu24_v2] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoMu24_v4] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoTkMu24_v1] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoTkMu24_v2] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoTkMu24_v3] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoTkMu24_v4] != 1 &&
      
//      (int)EvtInfo_TrgBook[HLT_IsoTkMu22_v2] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoTkMu22_v3] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoTkMu22_v4] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoTkMu22_v5] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoMu22_v1] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoMu22_v2] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoMu22_v3] != 1 &&
//      (int)EvtInfo_TrgBook[HLT_IsoMu22_v5] != 1 &&
       
       //di-Electron
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v3] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v4] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v5] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v6] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v7] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v8] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v9] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v10] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v11] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v12] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v13] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v14] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v15] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v16] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v17] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v18] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v19] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v3] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v4] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v5] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v6] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v7] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v8] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v9] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v10] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v11] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v12] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v13] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v14] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v15] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v16] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v17] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v18] != 1 && 
      (int)EvtInfo_TrgBook[HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v19] != 1 ) return(false);


//}}}
   
   hist_evt_cut->Fill(1., Event_Weight);

//*******************Vertex Part********************//
   m_vtx_no=0;
   
   for(int iv=0; iv < *VtxInfo_Size; iv++){
     VtxInfo_Good[iv] = 0;
     hist_vtx_cut->Fill(0., Event_Weight); 
     
     // 0: Vertices WITHOUT the Beam Spot constraint
     // 1: Vertices WITH the Beam Spot constraint
     if(VtxInfo_Type[iv] >= 0){//Type
       hist_vtx_cut->Fill(1, Event_Weight);
       
       if(VtxInfo_isValid[iv] > 0){
         hist_vtx_cut->Fill(2, Event_Weight);
         hist_vtx_ndof->Fill(VtxInfo_Ndof[iv], Event_Weight);
         hist_vtx_nx2->Fill(VtxInfo_NormalizedChi2[iv], Event_Weight);
         
         if(VtxInfo_Ndof[iv] > VTX_NDOF_CUT){//at least 4 degrees of freedom
           hist_vtx_cut->Fill(3, Event_Weight);
           hist_vtx_ptsum->Fill(VtxInfo_Pt_Sum[iv], Event_Weight);
           hist_vtx_z->Fill(VtxInfo_vz[iv], Event_Weight);
           hist_vtx_rho->Fill(VtxInfo_Rho[iv], Event_Weight);
           
           if(VtxInfo_Pt_Sum[iv] >= VTX_SUMPT_CUT){
             hist_vtx_cut->Fill(4, Event_Weight);
             
             if(fabs(VtxInfo_vz[iv]) < VTX_ABSZ_CUT){
               //an impact parameter with respect to the beanspot in z,dz
               hist_vtx_cut->Fill(5, Event_Weight);
               
               if(fabs(VtxInfo_Rho[iv]) < VTX_RHO_CUT){
                 hist_vtx_cut->Fill(6, Event_Weight);
                 VtxInfo_Good[iv] = 1;
                 m_vtx_no++;
               }
             }
           }
         }
       }
     }
   }//END Vertex Loop
   hist_vtx_no->Fill(m_vtx_no, Event_Weight);
//****************************************************//

//*******************Pileup Weight********************//
   nPU=-1;
   for(int i=0 ; i<*EvtInfo_nBX ; i++){
        if( EvtInfo_BXPU[i]==0 ){
            nPU = EvtInfo_nTPU[i];
        }
   }
   if(*EvtInfo_McFlag>0 && nPU<=75 && nPU>0) hist_npu_raw->Fill(nPU, Event_Weight);
   
   if(*EvtInfo_McFlag>0 && nPU<=75 && nPU>0){
       PUweight = SFPileup( h_PU_SF, nPU);
       Event_Weight = Event_Weight*PUweight;
   }
   hist_vtx_no_reweight->Fill(m_vtx_no, Event_Weight);
   
   if(*EvtInfo_McFlag>0 && nPU<=75 && nPU>0) hist_npu->Fill(nPU, Event_Weight);

//******************************************************//
   
   hist_evt_cut->Fill(2., Event_Weight);
   hist_evt_cut_e->Fill(2., Event_Weight);
   hist_evt_cut_m->Fill(2., Event_Weight);


//*******************Lepton Parts********************//
   m_e_notest=0;
   m_e_no=0; m_te_no=0;
   m_m_no=0; m_tm_no=0;

   for(int il1=0; il1 < *Leptons_Size; il1++){
     Leptons_Good[il1]=0;
     Leptons_Index[il1]=il1;
     
     Leptons_P4[il1].SetPxPyPzE(Leptons_Px[il1], Leptons_Py[il1],
                                Leptons_Pz[il1], Leptons_Energy[il1]);
   
     ReconElec(il1);
     ReconMuon(il1);
     m_st += Leptons_P4[il1].Pt();

   }//END lepton Loop
//********************************************************//

//*******************Gen Lepton Parts********************//
   GenLepts_Size=0;
   for(int il1=0; il1 < *GenParts_Size; il1++){
     GenLepts_Index[il1]=GenLepts_Size;
     
     if(GenParts_Status[il1] == 1 &&
        (fabs(GenParts_PdgID[il1])==11 || fabs(GenParts_PdgID[il1])==13) &&
        GenParts_P4[il1].Pt() > 20 && fabs(GenParts_P4[il1].Eta()) < 2.5){
     
       GenLepts_P4[GenLepts_Size]=GenParts_P4[il1];
       GenLepts_Pt[GenLepts_Size]=GenParts_P4[il1].Pt();
       GenLepts_Eta[GenLepts_Size]=GenParts_P4[il1].Eta();
       GenLepts_Phi[GenLepts_Size]=GenParts_P4[il1].Phi();
       GenLepts_Mass[GenLepts_Size]=GenParts_P4[il1].M();

       GenLepts_Charge[GenLepts_Size]=(GenParts_PdgID[il1] > 0 ? 1 : -1);
       GenLepts_Type[GenLepts_Size]=fabs(GenParts_PdgID[il1]);
     
       GenLepts_Size++;
     }
   }//END lepton Loop
//****************************************************//

   hist_lep_no->Fill(m_e_no+m_m_no, Event_Weight);
   hist_e_no->Fill(m_e_no, Event_Weight);
   hist_m_no->Fill(m_m_no, Event_Weight);



   hist_evt_cut->Fill(3., Event_Weight);
//   hist_evt_cut_e->Fill(3., Event_Weight);
//   hist_evt_cut_m->Fill(3., Event_Weight);
   SelectLepton();
   ReconZ();


   if( Zee_No > 0){
     hist_evt_cut->Fill(4., Event_Weight);
//     hist_evt_cut_e->Fill(4., Event_Weight);
//     hist_evt_cut_m->Fill(4., Event_Weight);
   }

   Jets_No=0;
   m_bjet_no=0;
   Jets_new_no=0;
    
   ReconJet();
   ReconBJet();

     //{{{-------------------------------leading leptons-----------------------------------------
   test_e_no = 0;
   test_mu_no = 0;
        if( (test_lep_no)>=3 && Jets_new_no>=2 && Jets_new_no<=3 && Zee_No>0 && m_bjet_no>0 ){
            hist_first_pt->Fill(Leading_test_P4[0].Pt(), Event_Weight);
            hist_second_pt->Fill(Leading_test_P4[1].Pt(), Event_Weight);
            hist_third_pt->Fill(Leading_test_P4[2].Pt(), Event_Weight);
            if(new_e_no>=2){
                hist_first_e_pt->Fill(Leading_test_P4[0].Pt(), Event_Weight);
                hist_second_e_pt->Fill(Leading_test_P4[1].Pt(), Event_Weight);
                hist_third_e_pt->Fill(Leading_test_P4[2].Pt(), Event_Weight);
            }
            if(new_mu_no>=2){
                hist_first_mu_pt->Fill(Leading_test_P4[0].Pt(), Event_Weight);
                hist_second_mu_pt->Fill(Leading_test_P4[1].Pt(), Event_Weight);
                hist_third_mu_pt->Fill(Leading_test_P4[2].Pt(), Event_Weight);
            }
        }
        
/*        
        for(int i=0 ; i<*Leptons_Size ; i++){
            if(Leptons_Type[i]==11 && Leptons_Good[i]==-2){
                Leading_test_ele_P4[test_e_no] = Leptons_P4[i];
                test_e_no++;
            }
            else if(Leptons_Type[i]==13 && Leptons_Good[i]==-2){
                Leading_test_mu_P4[test_mu_no] = Leptons_P4[i];
                test_mu_no++;
            }
        }
        if( test_e_no==3 ){
            hist_first_e_pt->Fill(Leading_test_ele_P4[0].Pt(), Event_Weight);
            hist_second_e_pt->Fill(Leading_test_ele_P4[1].Pt(), Event_Weight);
            hist_third_e_pt->Fill(Leading_test_ele_P4[2].Pt(), Event_Weight);
        }
        if( test_mu_no==3 ){
            hist_first_mu_pt->Fill(Leading_test_mu_P4[0].Pt(), Event_Weight);
            hist_second_mu_pt->Fill(Leading_test_mu_P4[1].Pt(), Event_Weight);
            hist_third_mu_pt->Fill(Leading_test_mu_P4[2].Pt(), Event_Weight);
        }
        //For stupid check (need to be delete after checking
*/
        if( (new_e_no+new_mu_no)==3 && new_e_no >= 2 && Zee_No>0 ){
        //for(int iz=0 ; iz<Zee_No ; iz++){
        //if( (new_e_no+new_mu_no)==3 && new_e_no >= 2 && Zee_P4[iz].Pt()>70 &&Jets_P4[Jets_new_index[0]].Pt()>110.){
            hist_new_ele_DE_pt->Fill(Leading_ele_P4[0].Pt(), Event_Weight);
            hist_new_ele_DE_eta->Fill(Leading_ele_P4[0].Eta(), Event_Weight);
            hist_new_ele_DE_phi->Fill(Leading_ele_P4[0].Phi(), Event_Weight);
            if(new_e_no==2 && new_mu_no==1){
                hist_new_mu_DE_pt->Fill(Leading_mu_P4[0].Pt(), Event_Weight);
                hist_new_mu_DE_eta->Fill(Leading_mu_P4[0].Eta(), Event_Weight);
                hist_new_mu_DE_phi->Fill(Leading_mu_P4[0].Phi(), Event_Weight);
            } //else(no electron->should not have Leading_mu_P4[0])
            
            hist_vtx_no_3leptons_reweight_DE->Fill(m_vtx_no, Event_Weight);
            if(*EvtInfo_McFlag > 0 && m_vtx_no<=75 ){
                hist_vtx_no_3leptons_DE->Fill(m_vtx_no, Event_Weight_lep);
            }
            else hist_vtx_no_3leptons_DE->Fill(m_vtx_no, Event_Weight);
        }
        if( (new_mu_no+new_e_no)==3 && new_mu_no >= 2 && Zee_No>0){
        //if( (new_mu_no+new_e_no)==3 && new_mu_no >= 2 && Zee_P4[iz].Pt()>70 && Jets_P4[Jets_new_index[0]].Pt()>110.){
            hist_new_mu_DM_pt->Fill(Leading_mu_P4[0].Pt(), Event_Weight);
            hist_new_mu_DM_eta->Fill(Leading_mu_P4[0].Eta(), Event_Weight);
            hist_new_mu_DM_phi->Fill(Leading_mu_P4[0].Phi(), Event_Weight);
            if(new_mu_no==2 && new_e_no==1){
                hist_new_ele_DM_pt->Fill(Leading_ele_P4[0].Pt(), Event_Weight);
                hist_new_ele_DM_eta->Fill(Leading_ele_P4[0].Eta(), Event_Weight);
                hist_new_ele_DM_phi->Fill(Leading_ele_P4[0].Phi(), Event_Weight); 
            } //else(no electron->should not have Leading_ele_P4[0])
            
            hist_vtx_no_3leptons_reweight_DM->Fill(m_vtx_no, Event_Weight);
            if(*EvtInfo_McFlag > 0 && m_vtx_no<=75){
                hist_vtx_no_3leptons_DM->Fill(m_vtx_no, Event_Weight_lep);
            }
            else hist_vtx_no_3leptons_DM->Fill(m_vtx_no, Event_Weight);
        }
        //}
   //}}}
  //{{{--------------------------------b and c jets ordering----------------------  
  if((new_e_no+new_mu_no)==3){
    for(int i=0 ; i<Jets_new_no ; i++){
        if(m_gen_jet1_idx > 0 && i < 125 &&
           GenParts_P4[m_gen_jet1_idx].Pt() > 0.1 &&
           fabs(Jets_P4[Jets_new_index[i]].DeltaR(
                GenParts_P4[m_gen_jet1_idx]))<0.4 &&
           fabs(Jets_P4[Jets_new_index[i]].Rho() / 
                GenParts_P4[m_gen_jet1_idx].Rho()) > 0.5 &&
           fabs(Jets_P4[Jets_new_index[i]].Rho() / 
                GenParts_P4[m_gen_jet1_idx].Rho()) < 2.0){ //&&
            hist_bjet_ordering->Fill(i,Event_Weight);
        }
        else if(m_gen_jet2_idx > 0 && i < 125 &&
            GenParts_P4[m_gen_jet2_idx].Pt() > 0.1 &&
            fabs(Jets_P4[Jets_new_index[i]].DeltaR(
                GenParts_P4[m_gen_jet2_idx]))<0.4 &&
            fabs(Jets_P4[Jets_new_index[i]].Rho() /
                GenParts_P4[m_gen_jet2_idx].Rho()) > 0.5 &&
            fabs(Jets_P4[Jets_new_index[i]].Rho() /
                GenParts_P4[m_gen_jet2_idx].Rho()) < 2.0 ){
            hist_cjet_ordering->Fill(i,Event_Weight);
        }
    }
  }
  //}}}     
//{{{--------------------------------jet pt and eta stack----------------------------------------------------------
    for(int i=0 ; i<*Jets_Size ; i++){
        if(Jets_Good[i]>=1 && (new_e_no+new_mu_no)==3 && new_e_no >= 2){
            hist_new_jet_DE_pt->Fill(Jets_P4[i].Pt(), Event_Weight);
            hist_new_jet_DE_eta->Fill(Jets_Eta[i], Event_Weight);
            hist_new_jet_DE_phi->Fill(Jets_Phi[i], Event_Weight);
            hist_new_jet_DE_btag->Fill((Jets_DeepCSVJetTags_probb[i]+Jets_DeepCSVJetTags_probbb[i]), Event_Weight);
            //hist_new_jet_DE_btag->Fill(Jets_CombinedIncSVBJetTags[i], Event_Weight);
        }
        
        if(Jets_Good[i]>=1 && (new_e_no+new_mu_no)==3 && new_mu_no >= 2){
            hist_new_jet_DM_pt->Fill(Jets_P4[i].Pt(), Event_Weight);
            hist_new_jet_DM_eta->Fill(Jets_Eta[i], Event_Weight);
            hist_new_jet_DM_phi->Fill(Jets_Phi[i], Event_Weight);
            hist_new_jet_DM_btag->Fill((Jets_DeepCSVJetTags_probb[i]+Jets_DeepCSVJetTags_probbb[i]), Event_Weight);
            //hist_new_jet_DM_btag->Fill(Jets_CombinedIncSVBJetTags[i], Event_Weight);
        }
    }
    DE_jet = 0;
    DM_jet = 0;
    for(int i=0 ; i<*Jets_Size ;i++){
        if(Jets_Good[i]>=1){
            Leading_DE_Jet_P4[DE_jet] = Jets_P4[i];
            DE_jet++ ;                
        }
    }
    if(Zee_No>0 && Jets_new_no>0){
        if((new_mu_no+new_e_no)==3 && new_e_no >= 2){
            hist_leading_jet_DE_pt->Fill(Leading_DE_Jet_P4[0].Pt(),Event_Weight);
            hist_leading_jet_DE_eta->Fill(Leading_DE_Jet_P4[0].Eta(),Event_Weight);
        }
        if((new_mu_no+new_e_no)==3 && new_mu_no >= 2){
            hist_leading_jet_DM_pt->Fill(Leading_DE_Jet_P4[0].Pt(),Event_Weight);
            hist_leading_jet_DM_eta->Fill(Leading_DE_Jet_P4[0].Eta(),Event_Weight);
        }
    }
//}}}   
//{{{----------------------------------Z window-----------------------------
        for(int iz=0 ; iz<Zee_No ; iz++){
        //if( Z_Good[iz]==1 && new_mu_no==0 && new_e_no==2){
        //if( Z_Good[iz]==1 && new_mu_no==0 && new_e_no==2 && Jets_new_no>=1 && Zee_P4[iz].Pt()>70 && Jets_P4[Jets_new_index[0]].Pt()>110.){
        if( Z_Good[iz]==1 && new_mu_no==0 && new_e_no==2 && Jets_new_no>=1 ){
            hist_zee_m_test2->Fill(Zee_P4[iz].M(), Event_Weight*Btag_weight);
            hist_zee_vtx_Reweight->Fill(m_vtx_no, Event_Weight*Btag_weight);
            hist_zee_HT->Fill(Zee_P4[iz].Pt(), Event_Weight*Btag_weight);
            hist_zee_rho->Fill(*EvtInfo_rhoIso, Event_Weight*Btag_weight);
            if(*EvtInfo_McFlag > 0 && m_vtx_no<=75){
                hist_zee_vtx->Fill(m_vtx_no, Event_Weight_lep*Btag_weight);
                hist_zee_rho_raw->Fill(*EvtInfo_rhoIso, Event_Weight_lep*Btag_weight);
            }
            else hist_zee_vtx->Fill(m_vtx_no, Event_Weight*Btag_weight);
            hist_zee_e_pt->Fill(Leading_ele_P4[0].Pt(), Event_Weight*Btag_weight);
            hist_zee_e_eta->Fill(Leading_ele_P4[0].Eta(), Event_Weight*Btag_weight);
            hist_zee_m_pt->Fill(Leading_mu_P4[0].Pt(), Event_Weight*Btag_weight);
            hist_zee_m_eta->Fill(Leading_mu_P4[0].Eta(), Event_Weight*Btag_weight);
            //if(Zee_P4[iz].Pt()>70. && Jets_Pt[0]>70) hist_zee_HT_HighCut->Fill( ,Event_Weight
            double zee_btagSF=1.0;
            for(int jb=0 ; jb<*Jets_Size ; jb++){
                if(Jets_Good[jb]>=1){
                    if(*EvtInfo_McFlag > 0){
                        zee_btagSF *= BtaggingSF(Jets_P4[jb].Pt(), 
                                                 abs(Jets_Eta[jb]), 
                                                 (Jets_DeepCSVJetTags_probb[jb]+Jets_DeepCSVJetTags_probbb[jb]), 
                                                 //Jets_CombinedIncSVBJetTags[jb], 
                                                 Jets_GenFlavor[jb]);
                    }
                }
            }
            for(int j1=0 ; j1<*Jets_Size ; j1++){
                if(Jets_Good[j1]>=1){
                    hist_zee_jet_pt->Fill(Jets_P4[j1].Pt(), Event_Weight*Btag_weight);
                    hist_zee_jet_eta->Fill(Jets_Eta[j1], Event_Weight*Btag_weight);
                    hist_zee_jet_csv->Fill((Jets_DeepCSVJetTags_probb[j1]+Jets_DeepCSVJetTags_probbb[j1]), Event_Weight*Btag_weight);
                    //hist_zee_jet_csv->Fill(Jets_CombinedIncSVBJetTags[j1], Event_Weight*Btag_weight);
                    hist_zee_jet_csvSF->Fill((Jets_DeepCSVJetTags_probb[j1]+Jets_DeepCSVJetTags_probbb[j1]), Event_Weight*zee_btagSF);
                    //hist_zee_jet_csvSF->Fill(Jets_CombinedIncSVBJetTags[j1], Event_Weight*zee_btagSF);
                    hist_zee_bjet_no->Fill(m_bjet_no, Event_Weight);
                    hist_zee_bjet_noSF->Fill(m_bjet_no, Event_Weight*zee_btagSF);
                }
            }
        }
        //else if( Z_Good[iz]==2 && new_mu_no==2 && new_e_no==0){
        //else if( Z_Good[iz]==2 && new_mu_no==2 && new_e_no==0 && Jets_new_no>=1 && Zee_P4[iz].Pt()>70 && Jets_P4[Jets_new_index[0]].Pt()>110.){
        else if( Z_Good[iz]==2 && new_mu_no==2 && new_e_no==0 && Jets_new_no>=1 ){
            hist_zmm_m_test2->Fill(Zee_P4[iz].M(), Event_Weight*Btag_weight);
            hist_zmm_vtx_Reweight->Fill(m_vtx_no, Event_Weight*Btag_weight);
            hist_zmm_HT->Fill(Zee_P4[iz].Pt(), Event_Weight*Btag_weight);
            hist_zmm_rho->Fill(*EvtInfo_rhoIso, Event_Weight*Btag_weight);
            if(*EvtInfo_McFlag > 0 && m_vtx_no<=75){
                hist_zmm_vtx->Fill(m_vtx_no, Event_Weight_lep*Btag_weight);
                hist_zmm_rho_raw->Fill(*EvtInfo_rhoIso, Event_Weight_lep*Btag_weight);
            }
            else hist_zmm_vtx->Fill(m_vtx_no, Event_Weight*Btag_weight);
            hist_zmm_e_pt->Fill(Leading_ele_P4[0].Pt(), Event_Weight*Btag_weight);
            hist_zmm_e_eta->Fill(Leading_ele_P4[0].Eta(), Event_Weight*Btag_weight);
            hist_zmm_m_pt->Fill(Leading_mu_P4[0].Pt(), Event_Weight*Btag_weight);
            hist_zmm_m_eta->Fill(Leading_mu_P4[0].Eta(), Event_Weight*Btag_weight);
            double zmm_btagSF=1.0;
            for(int jb=0 ; jb<*Jets_Size ; jb++){
                if(Jets_Good[jb]>=1){
                    if(*EvtInfo_McFlag > 0){
                        zmm_btagSF *= BtaggingSF(Jets_P4[jb].Pt(), 
                                                 abs(Jets_Eta[jb]), 
                                                 (Jets_DeepCSVJetTags_probb[jb]+Jets_DeepCSVJetTags_probbb[jb]), 
                                                 //Jets_CombinedIncSVBJetTags[jb], 
                                                 Jets_GenFlavor[jb]);
                    }
                }
            }
            for(int j2=0 ; j2<*Jets_Size ; j2++){
                if(Jets_Good[j2]>=1){
                    hist_zmm_jet_pt->Fill(Jets_P4[j2].Pt(), Event_Weight*Btag_weight);
                    hist_zmm_jet_eta->Fill(Jets_Eta[j2], Event_Weight*Btag_weight);
                    hist_zmm_jet_csv->Fill((Jets_DeepCSVJetTags_probb[j2]+Jets_DeepCSVJetTags_probbb[j2]), Event_Weight*Btag_weight);
                    //hist_zmm_jet_csv->Fill(Jets_CombinedIncSVBJetTags[j2], Event_Weight*Btag_weight);
                    hist_zmm_jet_csvSF->Fill((Jets_DeepCSVJetTags_probb[j2]+Jets_DeepCSVJetTags_probbb[j2]), Event_Weight*zmm_btagSF);
                    //hist_zmm_jet_csvSF->Fill(Jets_CombinedIncSVBJetTags[j2], Event_Weight*zmm_btagSF);
                    hist_zmm_bjet_no->Fill(m_bjet_no, Event_Weight);
                    hist_zmm_bjet_noSF->Fill(m_bjet_no, Event_Weight*zmm_btagSF);
                }
            }
        }
    }
//}}}
  
   if(new_e_no>=2) hist_evt_cut_e->Fill(3., 1.);
   if(new_mu_no>=2) hist_evt_cut_m->Fill(3., 1.);
   if((new_e_no+new_mu_no)>=3 && (new_e_no>=2)) hist_evt_cut_e->Fill(4., 1.);
   if((new_e_no+new_mu_no)>=3 && (new_mu_no>=2)) hist_evt_cut_m->Fill(4., 1.);

//{{{Trigger Test 
   if((new_mu_no+new_e_no)==3 && (new_e_no>=2)) hist_evt_cut_e->Fill(5., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no>=2)) hist_evt_cut_m->Fill(5., 1.);
   
   if((new_mu_no+new_e_no)==3 && (new_e_no>=2) && Zee_No>0) hist_evt_cut_e->Fill(6., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no>=2) && Zee_No>0) hist_evt_cut_m->Fill(6., 1.);

   if((new_mu_no+new_e_no)==3 && (new_e_no>=2) && Zee_No>0 && Jets_new_no>1) hist_evt_cut_e->Fill(7., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no>=2) && Zee_No>0 && Jets_new_no>1) hist_evt_cut_m->Fill(7., 1.);
   
   if((new_mu_no+new_e_no)==3 && (new_e_no>=2) && Zee_No>0 && Jets_new_no>1 && m_bjet_no>0) hist_evt_cut_e->Fill(8., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no>=2) && Zee_No>0 && Jets_new_no>1 && m_bjet_no>0) hist_evt_cut_m->Fill(8., 1.);
   
   if((new_mu_no+new_e_no)==3 && (new_e_no==2)) hist_evt_cut_eem->Fill(1., 1.);
   if((new_mu_no+new_e_no)==3 && (new_e_no==3)) hist_evt_cut_eee->Fill(1., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no==2)) hist_evt_cut_mme->Fill(1., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no==3)) hist_evt_cut_mmm->Fill(1., 1.);
   
   if((new_mu_no+new_e_no)==3 && (new_e_no==2) && Zee_No>0) hist_evt_cut_eem->Fill(2., 1.);
   if((new_mu_no+new_e_no)==3 && (new_e_no==3) && Zee_No>0) hist_evt_cut_eee->Fill(2., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no==2) && Zee_No>0) hist_evt_cut_mme->Fill(2., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no==3) && Zee_No>0) hist_evt_cut_mmm->Fill(2., 1.);

   if((new_mu_no+new_e_no)==3 && (new_e_no==2) && Zee_No>0 && Jets_new_no>1) hist_evt_cut_eem->Fill(3., 1.);
   if((new_mu_no+new_e_no)==3 && (new_e_no==3) && Zee_No>0 && Jets_new_no>1) hist_evt_cut_eee->Fill(3., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no==2) && Zee_No>0 && Jets_new_no>1) hist_evt_cut_mme->Fill(3., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no==3) && Zee_No>0 && Jets_new_no>1) hist_evt_cut_mmm->Fill(3., 1.);
   
   if((new_mu_no+new_e_no)==3 && (new_e_no==2) && Zee_No>0 && Jets_new_no>1 && m_bjet_no>0) hist_evt_cut_eem->Fill(4., 1.);
   if((new_mu_no+new_e_no)==3 && (new_e_no==3) && Zee_No>0 && Jets_new_no>1 && m_bjet_no>0) hist_evt_cut_eee->Fill(4., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no==2) && Zee_No>0 && Jets_new_no>1 && m_bjet_no>0) hist_evt_cut_mme->Fill(4., 1.);
   if((new_mu_no+new_e_no)==3 && (new_mu_no==3) && Zee_No>0 && Jets_new_no>1 && m_bjet_no>0) hist_evt_cut_mmm->Fill(4., 1.);
//}}}
   if( *Jets_Size >= 2){ // two jets
     hist_evt_cut->Fill(5., Event_Weight);
//     hist_evt_cut_e->Fill(5., Event_Weight);
//     hist_evt_cut_m->Fill(5., Event_Weight);
   }

   if( m_bjet_no >= 1){ // one b-jets
     hist_evt_cut->Fill(6., Event_Weight);
//     hist_evt_cut_e->Fill(6., Event_Weight);
//     hist_evt_cut_m->Fill(6., Event_Weight);
   }

   m_te_no=0; m_tm_no=0;
   Wuu_No=0;
   ReconW();

   m_st += *EvtInfo_MET;
   
   if(*EvtInfo_MET < MET_CUT) return(kFALSE);
   hist_evt_cut->Fill(7., Event_Weight);

   //if( (new_e_no+new_mu_no)==3  && Zee_No>0 ) FullCut->Fill();
//   hist_evt_cut_e->Fill(7., Event_Weight);
//   hist_evt_cut_m->Fill(7., Event_Weight);
//   
//   hist_evt_cut->Fill(4, Event_Weight);
//   
//   if((m_e_no > 0) && (m_e_no+m_m_no == 3)){
//     hist_evt_cut_e->Fill(4, Event_Weight);
//   }
//   else if((m_m_no > 0) && (m_e_no+m_m_no == 3)){
//     hist_evt_cut_m->Fill(4, Event_Weight);
//   }

   hist_jet_no->Fill(Jets_No, Event_Weight);
   hist_bjet_no->Fill(m_bjet_no, Event_Weight);
   
   mvaTree = dynamic_cast<TTree *>(fOutput->FindObject(Form("mvaTree")));

   //if( (new_e_no+new_mu_no)==3 ) FullCut->Fill();
   if( (new_e_no+new_mu_no)==3 && Jets_new_no>=2 && Jets_new_no<=3 && Zee_No>0 && m_bjet_no>0) hist_pT_optimization->Fill(20, Event_Weight);
   if( (new_e_no+new_mu_no)==3 && Jets_new_no>0 && Zee_No>0){
        if(new_mu_no==3){
            for(int i=0 ; i<*Leptons_Size ; i++){
                if(Leptons_Good[i]==3) hist_trigger_eff_mmm->Fill(Leptons_P4[i].Pt(), 1.0);
            }
        }
        if(new_mu_no==2 && new_e_no==1){ 
            for(int i=0 ; i<*Leptons_Size ; i++){
                if(Leptons_Good[i]==3) hist_trigger_eff_mme->Fill(Leptons_P4[i].Pt(), 1.0);
            }
        }
        if(new_mu_no==1 && new_e_no==2){
            for(int i=0 ; i<*Leptons_Size ; i++){
                if(Leptons_Good[i]==3) hist_trigger_eff_mee->Fill(Leptons_P4[i].Pt(), 1.0);
            }
        }
        if(new_e_no==3){ 
            for(int i=0 ; i<*Leptons_Size ; i++){
                if(Leptons_Good[i]==3) hist_trigger_eff_eee->Fill(Leptons_P4[i].Pt(), 1.0);
            }
        }
   }
   TopInfo_MCTruth = 0;
 
   //LHE_unc
   if(*EvtInfo_McFlag>0 && *LHENominalWeight!=0){
        //double RenormFact = ((LHESystematicWeights[8]-*LHENominalWeight)/(*LHENominalWeight))+1;
        //Event_Weight = Event_Weight*RenormFact;
        double PDFUnc     = ((LHESystematicWeights[110]-*LHENominalWeight)/(*LHENominalWeight))+1;
        //Event_Weight = Event_Weight*PDFUnc;
   }

   ReconTop();
  
//   }

   if(m_top_comb > 0){ // two tops
     hist_evt_cut->Fill(8., Event_Weight);
//     hist_evt_cut_e->Fill(8., Event_Weight);
//     hist_evt_cut_m->Fill(8., Event_Weight);

     if(m_top_comb>0 && Top_P4[127].M()>50 && Top_P4[127].M()<350){ // mass cz
         hist_evt_cut->Fill(8., Event_Weight);
//       hist_evt_cut_e->Fill(8., Event_Weight);
//       hist_evt_cut_m->Fill(8., Event_Weight);
     }

     if(m_top_comb>0 && Top_P4[126].M()>50 && Top_P4[126].M()<350){ // mass bw
       hist_evt_cut->Fill(8., Event_Weight);
//       hist_evt_cut_e->Fill(8., Event_Weight);
//       hist_evt_cut_m->Fill(8., Event_Weight);
     }

     if(TopInfo_MCTruth > 0){ //gen match
       hist_evt_cut->Fill(9., Event_Weight);
//       hist_evt_cut_e->Fill(9., Event_Weight);
//       hist_evt_cut_m->Fill(9., Event_Weight);
     }

     if(m_bjet_no == 0){ // 0 b-tag
       hist_evt_cut->Fill(10., Event_Weight);
//       hist_evt_cut_e->Fill(10., Event_Weight);
//       hist_evt_cut_m->Fill(10., Event_Weight);
     }

     if(m_bjet_no > 1){ // 2 b-tag
       hist_evt_cut->Fill(11., Event_Weight);
//       hist_evt_cut_e->Fill(11., Event_Weight);
//       hist_evt_cut_m->Fill(11., Event_Weight);
     }

   }
   return kTRUE;
}

void MyTcZAna_2017_Central::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
}

void MyTcZAna_2017_Central::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   fOutput->Write();

  std::cout << "\n\nVoila! C'est fini.\n";

   cout << "\nEvent_selection  \t all \t eee \t eem \t emm \t mmm \n";
   for(int i=0; i < 14; i++){
     cout << evt_cut_label[i] << "   \t\t" << setprecision(9)
          << hist_evt_cut->GetBinContent(i+1) << " \t "
          << endl;
   }
   cout << "Total Number of run event : " << fReader.GetEntries(true) << endl;
   cout << "Postive of run event : " << postive_number << endl;
   cout << "Negative of run event : " << negative_number << endl;
   cout << "Final # of run event : " << postive_number-negative_number << endl;
//   cout << "FullReco_MCTruth_pre : " << FullReco_MCTruth_pre << endl;
//   cout << "# of recorded event : " << FullReco_MCTruth << endl;
//   cout << "Topdphi_MCTruth_pre : " << Topdphi_MCTruth_pre << endl;
//   cout << "Topdphi_MCTruth : " << Topdphi_MCTruth << endl;
//   cout << "Xsquare_MCTruth_pre : " << Xsquare_MCTruth_pre << endl;
//   cout << "Xsquare_MCTruth : " << Xsquare_MCTruth << endl;
}
//Scale Factor{{{
double MyTcZAna_2017_Central::SFElectronID(const TH2D* hist, double LepEta, double LepPt){
    LepEta = min( LepEta, hist->GetXaxis()->GetXmax() - 0.01 );
    LepEta = max( LepEta, hist->GetXaxis()->GetXmin() + 0.01 );
    LepPt = min( LepPt, hist->GetYaxis()->GetXmax() - 0.01 );
    return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) );
    //return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) ) + hist->GetBinError( hist->FindFixBin(LepEta, LepPt) );
    //return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) ) - hist->GetBinError( hist->FindFixBin(LepEta, LepPt) );
}

double MyTcZAna_2017_Central::SFElectronReco(const TH2D* hist, double LepEta, double LepPt){
    LepEta = min( LepEta, hist->GetXaxis()->GetXmax() - 0.01 );
    LepEta = max( LepEta, hist->GetXaxis()->GetXmin() + 0.01 );
    LepPt = min( LepPt, hist->GetYaxis()->GetXmax() - 0.01 );
    return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) );
    //return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) ) + hist->GetBinError( hist->FindFixBin(LepEta, LepPt) );
    //return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) ) - hist->GetBinError( hist->FindFixBin(LepEta, LepPt) );
}

double MyTcZAna_2017_Central::SFMuonID(const TH2D* hist,  double LepEta, double LepPt){
    LepEta = fabs( LepEta );
    LepEta = min( LepEta, hist->GetYaxis()->GetXmax() - 0.01 );
    LepEta = max( LepEta, hist->GetYaxis()->GetXmin() + 0.01 );
    LepPt = min( LepPt, hist->GetXaxis()->GetXmax() - 0.01 );
    return hist->GetBinContent( hist->FindFixBin(LepPt, LepEta) );
    //return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) ) + hist->GetBinError( hist->FindFixBin(LepEta, LepPt) );
    //return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) ) - hist->GetBinError( hist->FindFixBin(LepEta, LepPt) );
}

double MyTcZAna_2017_Central::SFMuonISO(const TH2D* hist,  double LepEta, double LepPt){
    LepEta = fabs( LepEta );
    LepEta = min( LepEta, hist->GetYaxis()->GetXmax() - 0.01 );
    LepEta = max( LepEta, hist->GetYaxis()->GetXmin() + 0.01 );
    LepPt = min( LepPt, hist->GetXaxis()->GetXmax() - 0.01 );
    return hist->GetBinContent( hist->FindFixBin(LepPt, LepEta) );
    //return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) ) + hist->GetBinError( hist->FindFixBin(LepEta, LepPt) );
    //return hist->GetBinContent( hist->FindFixBin(LepEta, LepPt) ) - hist->GetBinError( hist->FindFixBin(LepEta, LepPt) );
}

double MyTcZAna_2017_Central::SFPileup(const TH1D *PU, int vertex_no){
    vertex_no = min( vertex_no, 75);//PU->GetXaxis()->GetXmax() - 0.01 );
    return PU->GetBinContent( PU->FindFixBin(vertex_no) );
}

void MyTcZAna_2017_Central::BtaggingInit(){
    calib = new BTagCalibration("csvv2", "/wk_cms2/arthur6745/env/CMSSW_9_4_13/src/TopQuarkAnalysis/MyFCNCkit/test/ScaleFactor/2017/DeepCSV_94XSF_V5_B_F.csv");
    reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "central"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up_lf"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down_lf"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up_hf"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down_hf"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up_lfstats1"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down_lfstats1"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up_lfstats2"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down_lfstats2"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up_hfstats1"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down_hfstats1"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up_hfstats2"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down_hfstats2"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up_cferr1"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down_cferr1"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up_cferr2"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down_cferr2"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up_jes"); 
    //reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down_jes"); 

    reader->load(*calib, BTagEntry::FLAV_B, "iterativefit");
    reader->load(*calib, BTagEntry::FLAV_C, "iterativefit");
    reader->load(*calib, BTagEntry::FLAV_UDSG, "iterativefit");
}
double MyTcZAna_2017_Central::BtaggingSF(double bjet_pt, double bjet_eta, double csv, int flavor){
  
    double csvWgtHF = 1.0;
    double csvWgtLF = 1.0;
    double csvWgtC = 1.0;
    double csvWgtTotal = 1.0;

    if(abs(flavor)==5){
        double iCSVWgtHF = reader->eval(BTagEntry::FLAV_B, bjet_eta, bjet_pt, csv);
        if( iCSVWgtHF!=0 ) csvWgtHF *= iCSVWgtHF;
    }
    else if(abs(flavor)==4){
        double iCSVWgtC = reader->eval(BTagEntry::FLAV_C, bjet_eta, bjet_pt, csv);
        if( iCSVWgtC!=0 ) csvWgtC *= iCSVWgtC;
    }
    else{
        double iCSVWgtLF = reader->eval(BTagEntry::FLAV_UDSG, bjet_eta, bjet_pt, csv);
        if( iCSVWgtLF!=0 ) csvWgtLF *= iCSVWgtLF;
    }
    return csvWgtTotal = csvWgtHF * csvWgtC * csvWgtLF;
}
//}}}
//ReconElec{{{
void MyTcZAna_2017_Central::ReconElec(int il1){

  if(fabs(Leptons_Type[il1])==11){
    
    //if(*EvtInfo_McFlag!=0) ElecEnergyCorr(il1);
    hist_ele_cut->Fill(0., Event_Weight);

    //Electron real cut         
    if(Leptons_Pt[il1] > ELE_PT_CUT){ // PT > 30
      hist_ele_cut->Fill(2, Event_Weight);
      
      // eta < 2.4 & Excluding EB-EE transition region
      if(fabs(Leptons_Eta[il1]) < ELE_ETA_CUT && 
         (fabs(Leptons_Eta[il1])<1.4442 || fabs(Leptons_Eta[il1])>1.566) ){
            hist_ele_cut->Fill(3, Event_Weight);
            Leptons_Good[il1]=1;

            if(Leptons_eidTightMC[il1] > 0){
                hist_ele_cut->Fill(7, Event_Weight);
              
                hist_e_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
                hist_e_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
                hist_e_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);

                m_e_no++;
                Leptons_Good[il1]=2;
  
            }//eid tight
      }//eta < 2.4
    }//pt > 0
  } // end if il1 electron
}// ReconEle end
//}}}
//ReconMuon{{{
void MyTcZAna_2017_Central::ReconMuon(int il1){

  if(fabs(Leptons_Type[il1])==13){
    hist_mu_cut->Fill(0., Event_Weight);

    if(Leptons_Pt[il1] > MU_PT_CUT){ // PT > 35
        hist_mu_cut->Fill(3, Event_Weight);
          
        if(fabs(Leptons_Eta[il1]) < MU_ETA_CUT){ // eta < 2.4
            hist_mu_cut->Fill(4, Event_Weight);
            double pf_neutral = max(0., Leptons_NeutralHadronIsoR04[il1] +
                                  Leptons_PhotonIsoR04[il1] -
                                  0.5*Leptons_sumPUPtR04[il1]);

            double pf_iso = (Leptons_ChargedHadronIsoR04[il1] + pf_neutral)/Leptons_Pt[il1];
          
            hist_m_iso->Fill( pf_iso, Event_Weight);

            if(pf_iso < MU_ISO_LCUT){ // Tight 0.15
                hist_mu_cut->Fill(5, Event_Weight);
                        
                if(Leptons_MuonCutBasedMuIdTIGHT[il1] > 0){ 
                    hist_m_pt->Fill(Leptons_Pt[il1], Event_Weight);
                    hist_m_eta->Fill(Leptons_Eta[il1], Event_Weight);
                    hist_m_phi->Fill(Leptons_Phi[il1], Event_Weight);
                            
                    m_m_no++;
                    Leptons_Good[il1]=2;
                         
                }
            }//iso < 0.15
        }//Eta < 2.4
    }//pt > 0
  }// end if il1 Muon
}// ReconMu end
//}}}
//SelectLepton{{{
void MyTcZAna_2017_Central::SelectLepton(){
   new_e_no = 0;
   new_mu_no = 0;
   test_lep_no = 0;
   for(int i=0 ; i<*Leptons_Size ; i++){
       if(Leptons_Type[i]==11 || Leptons_Type[i]==13){
           if(Leptons_Good[i]==2){
               Leading_test_P4[test_lep_no] = Leptons_P4[i];
               lepton_index[test_lep_no] = i;
               test_lep_no++;
           }
       }
   }
   //if(test_lep_no<3) return(kFALSE);
   if(test_lep_no>3 && Leading_test_P4[3].Pt()>20) return(kFALSE);
   if(test_lep_no>=3 && Leading_test_P4[0].Pt()>25 && Leading_test_P4[1].Pt()>20 && Leading_test_P4[2].Pt()>20){
       for(int i=0 ; i<*Leptons_Size ; i++){
           if(i==lepton_index[0] || i==lepton_index[1] || i==lepton_index[2]) Leptons_Good[i]=3;
       }
   }

   for(int i=0 ; i<*Leptons_Size ;i++){
       if(Leptons_Type[i]==11 && Leptons_Good[i] == 3){
           Leading_ele_P4[new_e_no] = Leptons_P4[i];
           if(*EvtInfo_McFlag>0){ 
                SF_ele[i] = SFElectronID( h_ele_Eff, Leptons_P4[i].Eta(), Leptons_P4[i].Pt());
                SF_ele_Reco[i] = SFElectronReco( h_ele_Reco, Leptons_P4[i].Eta(), Leptons_P4[i].Pt());
            }
            else{
                SF_ele[i] = 1.0 ;
                SF_ele_Reco[i] = 1.0;
            }
            Event_Weight = Event_Weight*SF_ele[i]*SF_ele_Reco[i];
            Event_Weight_lep = Event_Weight_lep*SF_ele[i]*SF_ele_Reco[i];

           new_e_no++;
           //Leptons_Good[i]=3;
       }
       else if(Leptons_Type[i]==13 && Leptons_Good[i] == 3){
           Leading_mu_P4[new_mu_no] = Leptons_P4[i];
           if( *EvtInfo_McFlag > 0 ){
               SF_MuonISO[i] = SFMuonISO( h_MuonBtoF_Eff_ISO, Leptons_Eta[i], Leptons_Pt[i] );
           }
           else SF_MuonISO[i] = 1.0;
           Event_Weight = Event_Weight*SF_MuonISO[i];
           Event_Weight_lep = Event_Weight_lep*SF_MuonISO[i];
           
           if( *EvtInfo_McFlag > 0 ){
               SF_MuonID[i] = SFMuonID( h_MuonBtoF_Eff, Leptons_Eta[i], Leptons_Pt[i] );
           }
           else SF_MuonID[i] = 1.0;
           Event_Weight = Event_Weight*SF_MuonID[i];
           Event_Weight_lep = Event_Weight_lep*SF_MuonID[i];

           new_mu_no++;
           //Leptons_Good[i]=3;
       }
   }
}
//}}}
//ReconZ{{{
void MyTcZAna_2017_Central::ReconZ(){
  // Z selections
  Zee_No=0;
  Z_No=0;
  m_tz_no=0;
  Z_Good[Zee_No]=0;
  for(int il1=0; il1 < *Leptons_Size; il1++){

//Is good Electron
	if(Leptons_Type[il1]==11 && Leptons_Good[il1]==3){

//Check to see if the electron is faked by a muon
	  int muon_veto = 0;
	  for(int il=0; il < *Leptons_Size; il++){
	    if(Leptons_Type[il]==13 && Leptons_Good[il]==3 &&
	       Leptons_Pt[il] > MU_PT_CUT &&
	       fabs((Leptons_P4[il]).DeltaR(Leptons_P4[il1])) < 0.1){
	      muon_veto=1;
	      break;
	    }
	  }
	  if(muon_veto != 0){
	    Leptons_Good[il1]=-1;
	    continue;
	  }

	  if(Leptons_GenMatch[il1]!=-1){
	    hist_gel_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
	    hist_gel_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
	    hist_gel_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
	    //hist_ele_cut->Fill(5, Event_Weight);
	  }
      
	  for(int il2=il1; il2 < *Leptons_Size; il2++){
	    if(Leptons_Good[il1]==3 &&
	       Leptons_Type[il2]==11 && Leptons_Good[il2]==3 &&
	       Leptons_Charge[il1]*Leptons_Charge[il2]==-1){
          
	      int muon_veto2 = 0;
	      for(int il=0; il < *Leptons_Size; il++){
                if(Leptons_Type[il]==13 && Leptons_Good[il]==3 &&
                   fabs((Leptons_P4[il]).DeltaR(Leptons_P4[il2])) < 0.1){
                  muon_veto2=1;
                  break;
                }
	      }
	      if(muon_veto2==1){
                Leptons_Good[il2]=-1;
                continue;
	      }
	    
          //Side Band
          Z_P4[Z_No]=(Leptons_P4[il1]+Leptons_P4[il2]); 
          if( (Z_P4[Z_No].M() > 30.0) && (Z_P4[Z_No].M()) < 150.0){
	        Z_lid1[Z_No]=Leptons_Index[il1];
            Z_lid2[Z_No]=Leptons_Index[il2];
            Z_No++;
          }
      
	      
          Zee_P4[Zee_No]=(Leptons_P4[il1]+Leptons_P4[il2]);
	      
          if(Zee_P4[Zee_No].M() > Z_MASS_LCUT &&
                 Zee_P4[Zee_No].M() < Z_MASS_HCUT ){
            
                hist_zee_m->Fill(Zee_P4[Zee_No].M(), Event_Weight);
                hist_zee_pt->Fill(Zee_P4[Zee_No].Pt(), Event_Weight);
            
                Zee_lid1[Zee_No]=Leptons_Index[il1];
                Zee_lid2[Zee_No]=Leptons_Index[il2];
                Z_Good[Zee_No]=1;
            
                if(Zee_P4[Zee_No].M() > TZ_MASS_LCUT &&
                   Zee_P4[Zee_No].M() < TZ_MASS_HCUT &&
                   fabs(Leptons_P4[il1].DeltaR(Leptons_P4[il2])) > 0.05 ){
                  //m_tz_no++;
                   Z_tight_P4[m_tz_no]=(Leptons_P4[il1]+Leptons_P4[il2]); // Tight Z mass window
                   Z_tight_lid1[m_tz_no]=Leptons_Index[il1];
                   Z_tight_lid2[m_tz_no]=Leptons_Index[il2];
                   m_tz_no++;
                   m_tz_no_e++;
                }
                //Check on DY-Data matching
                if(new_mu_no==0 && new_e_no==2){
                    hist_zee_m_test->Fill(Zee_P4[Zee_No].M(), Event_Weight);
                }

                Zee_No++;
                m_z_no_e++;
	      }
	    }
	  }
	}

	// now look for muons
	if(Leptons_Type[il1]==13 && Leptons_Good[il1]==3){

	  if(Leptons_GenMatch[il1]!=-1){
	    hist_gml_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
	    hist_gml_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
	    hist_gml_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
	    
	    hist_mu_cut->Fill(17, Event_Weight);
	  }

	  for(int il2=il1+1; il2 < *Leptons_Size; il2++){
	    if(Leptons_Good[il1]==3 &&
	       Leptons_Type[il2]==13 && Leptons_Good[il2]==3 &&
	       Leptons_Charge[il1]*Leptons_Charge[il2]==-1){
           
          //Side Band
          Z_P4[Z_No]=(Leptons_P4[il1]+Leptons_P4[il2]); 
          if( (Z_P4[Z_No].M() > 30.0) && (Z_P4[Z_No].M() < 150.0) ){
	        Z_lid1[Z_No]=Leptons_Index[il1];
            Z_lid2[Z_No]=Leptons_Index[il2];
            Z_No++;
          }
         
	      Zee_P4[Zee_No]=(Leptons_P4[il1]+Leptons_P4[il2]);
          
          if(Zee_P4[Zee_No].M() > Z_MASS_LCUT &&
               Zee_P4[Zee_No].M() < Z_MASS_HCUT ){
            
                hist_zmm_m->Fill(Zee_P4[Zee_No].M(), Event_Weight);
                hist_zmm_pt->Fill(Zee_P4[Zee_No].Pt(), Event_Weight);
            
                Zee_lid1[Zee_No]=Leptons_Index[il1];
                Zee_lid2[Zee_No]=Leptons_Index[il2];
                Z_Good[Zee_No]=2;
            
                if(Zee_P4[Zee_No].M() > TZ_MASS_LCUT &&
                   Zee_P4[Zee_No].M() < TZ_MASS_HCUT &&
                   fabs(Leptons_P4[il1].DeltaR(Leptons_P4[il2])) > 0.05 ){
                  
                    Z_tight_P4[m_tz_no]=(Leptons_P4[il1]+Leptons_P4[il2]); // Tight Z mass window
                    Z_tight_lid1[m_tz_no]=Leptons_Index[il1];
                    Z_tight_lid2[m_tz_no]=Leptons_Index[il2];
                    m_tz_no++;

                  m_tz_no_m++;
                }
                
                // Kinematic in Z mass window
                if(new_mu_no==2 && new_e_no==0){
                    hist_zmm_m_test->Fill(Zee_P4[Zee_No].M(), Event_Weight);
                }

                Zee_No++;
                m_z_no_m++;
            
	      }
	    } // Leptons2 IF
	  } // Leptons2 loop
	} // Leptons1 IF
  } // Leptons loop

  hist_zee_no->Fill(m_z_no_e, Event_Weight);
  hist_zmm_no->Fill(m_z_no_m, Event_Weight);

  if(GenLepts_Size >=2){
    for(int il1=0; il1 < GenLepts_Size; il1++){
      for(int il2=il1+1; il2 < GenLepts_Size; il2++){
        if(GenLepts_Type[il1]==GenLepts_Type[il2] &&
           GenLepts_Charge[il1]*GenLepts_Charge[il2] < 0){
          TLorentzVector GenZee_P4 = GenLepts_P4[il1]+GenLepts_P4[il2];
        
          if(fabs(GenLepts_Type[il1])==11){
            hist_zee_m_g->Fill(GenZee_P4.M(), Event_Weight);
          }else{
            hist_zmm_m_g->Fill(GenZee_P4.M(), Event_Weight);
          }
        }
	  } // GenLept2 loop
    } // GenLept1 loop
  } // size
}
//}}}
//ReconW{{{
void MyTcZAna_2017_Central::ReconW(){
  // W selections
  Wuu_No=0;
  m_w_no_e=m_w_no_m=0;
  hist_met_pt->Fill(*EvtInfo_MET, Event_Weight);
  hist_met_phi->Fill(*EvtInfo_METPhi, Event_Weight);

  int m_lep_idx=-1;


  // loop over leptons for W
  int m_te_no=0; int m_tm_no=0;
  for(int il1=0; il1 < *Leptons_Size; il1++){
	
    if(Leptons_Type[il1]==11 && Leptons_Good[il1] == 3 ){ //&& //#$%^
      m_te_no++;
      
      hist_te_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
      hist_te_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
      hist_te_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
      
      if(Leptons_GenMatch[il1]!=-1){
        hist_get_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
        hist_get_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
        hist_get_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
        //hist_ele_cut->Fill(7, Event_Weight);
      }
    }
    if(Leptons_Type[il1]==13 && Leptons_Good[il1] == 3 ){ 
      m_tm_no++;
      
      hist_tm_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
      hist_tm_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
      hist_tm_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
      
      if(Leptons_GenMatch[il1]!=-1){
        hist_gmt_pt->Fill(Leptons_P4[il1].Pt(), Event_Weight);
        hist_gmt_phi->Fill(Leptons_P4[il1].Phi(), Event_Weight);
        hist_gmt_eta->Fill(Leptons_P4[il1].Eta(), Event_Weight);
        //hist_mu_cut->Fill(15, Event_Weight);
      }
    }
  }

  for(int il1=0; il1 < *Leptons_Size; il1++){

    if(Leptons_Good[il1] != 3) continue;

    TLorentzVector lep;
	  
    lep.SetPxPyPzE(Leptons_P4[il1].Px(), Leptons_P4[il1].Py(),
                   Leptons_P4[il1].Pz(), Leptons_P4[il1].E());
   
    TLorentzVector nu;

    nu.SetPxPyPzE(*EvtInfo_MET * cos(*EvtInfo_METPhi),
		          *EvtInfo_MET * sin(*EvtInfo_METPhi), 0.,
		          *EvtInfo_MET);
   
    double pz=0, b4ac=0, b=0;
    b=lep.Px()*nu.Px()+lep.Py()*nu.Py()+MASS_W*MASS_W/2;
    b4ac=b*b-nu.E()*nu.E()*(lep.E()*lep.E()-lep.Pz()*lep.Pz());
    
    if(b4ac>0){
      if((lep.Pz()*b) * (lep.E()*sqrt(b4ac)) >= 0){
        pz=(lep.Pz()*b - lep.E()*sqrt(b4ac)) /
          (lep.E()*lep.E()-lep.Pz()*lep.Pz());
      }else{
        pz=(lep.Pz()*b + lep.E()*sqrt(b4ac)) /
          (lep.E()*lep.E()-lep.Pz()*lep.Pz());
      }
    }else{
      pz=(lep.Pz()*b) / (lep.E()*lep.E()-lep.Pz()*lep.Pz());
    }
    
    nu.SetPxPyPzE(*EvtInfo_MET *cos(*EvtInfo_METPhi),
                  *EvtInfo_MET *sin(*EvtInfo_METPhi), pz,
                  sqrt((*EvtInfo_MET)*(*EvtInfo_MET)+pz*pz));
    
    Wuu_P4[Wuu_No]=(nu+lep);
  
    Wuu_Mt[Wuu_No] = sqrt(2 * Leptons_P4[il1].Pt() * *EvtInfo_MET *
                          ( 1 - cos(*EvtInfo_METPhi-Leptons_P4[il1].Phi())));

    if(Leptons_Type[il1] == 11){
      hist_wen_m->Fill(Wuu_P4[Wuu_No].M(), Event_Weight);
      hist_wen_mt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      hist_wen_pt->Fill(Wuu_P4[Wuu_No].Pt(), Event_Weight);
      
      if(m_gen_wuu_idx >= 0 && 
         fabs(Wuu_P4[Wuu_No].DeltaR(GenParts_P4[m_gen_wuu_idx])) < 0.4){
        hist_wen_gmt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      }
      if(Wuu_Mt[Wuu_No] > W_MT_LCUT && Wuu_Mt[Wuu_No] < W_MT_HCUT){
        Wuu_lid[Wuu_No]=Leptons_Index[il1];
        m_w_no_e++;
        Wuu_No++;
      }
    }

    if(Leptons_Type[il1] == 13){//The lepton of W is muon
      hist_wmn_m->Fill(Wuu_P4[Wuu_No].M(), Event_Weight);
      hist_wmn_mt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      hist_wmn_pt->Fill(Wuu_P4[Wuu_No].Pt(), Event_Weight);
      
      if(m_gen_wuu_idx >= 0 && 
         fabs(Wuu_P4[Wuu_No].DeltaR(GenParts_P4[m_gen_wuu_idx])) < 0.4){
        hist_wmn_gmt->Fill(Wuu_Mt[Wuu_No], Event_Weight);
      }
      
      if(Wuu_Mt[Wuu_No] > W_MT_LCUT && Wuu_Mt[Wuu_No] < W_MT_HCUT){
        Wuu_lid[Wuu_No]=Leptons_Index[il1];
        m_w_no_m++;
        Wuu_No++;
      }
    }
  }
  hist_wen_no->Fill(m_w_no_e, Event_Weight);
  hist_wmn_no->Fill(m_w_no_m, Event_Weight);
}
//}}} 
//ReconJet{{{
void MyTcZAna_2017_Central::ReconJet(){
  Jets_No = 0;
  Jets_new_no = 0;
  Jets_HT = 0.;
  // Looping over jets
  if(*Jets_Size > 64) cout << "Jet Size > 64!!!!!!\n\n";
  for(int ij1=0; ij1 < *Jets_Size && ij1 < 64; ij1++){
    hist_jet_cut->Fill(0., Event_Weight);
    Jets_Good[ij1]=0;
      
    Jets_P4[ij1].SetPtEtaPhiE(Jets_Pt[ij1], Jets_Eta[ij1],
                              Jets_Phi[ij1], Jets_Energy[ij1]);
    Jets_GenMatch[ij1]=-1;

    InitJES(ij1);
    if(*EvtInfo_McFlag != 0) JERCorr(ij1);
    //if(*EvtInfo_McFlag != 0) JERUp(ij1);
    //if(*EvtInfo_McFlag != 0) JERDn(ij1);
    //if(*EvtInfo_McFlag != 0) JECUp(ij1);
    //if(*EvtInfo_McFlag != 0) JECDn(ij1);

    if(Jets_GenJetPt[ij1]>0){
      hist_gjet_pt->Fill(Jets_Pt[ij1], Event_Weight);
      hist_gjet_eta->Fill(Jets_Eta[ij1], Event_Weight);
      hist_gjet_phi->Fill(Jets_Phi[ij1], Event_Weight);
      
      hist_jet_cut->Fill(1, Event_Weight);
    }
    
    if(Jets_P4[ij1].Pt() > JET_PT_CUT){
      hist_jet_cut->Fill(2, Event_Weight);
      
      if(fabs(Jets_Eta[ij1]) < JET_ETA_CUT){
        hist_jet_cut->Fill(3, Event_Weight);
        
        if(Jets_JetIDLOOSE[ij1] > 0){
          hist_jet_cut->Fill(4, Event_Weight);
        }
        if(Jets_NHF[ij1]<0.90 &&  //Neutral Hadron Fraction
           Jets_NEF[ij1]<0.90 &&  //Neutral EM Fraction
           Jets_NConstituents[ij1]>1 &&  //Number of Constituents
           Jets_CHF[ij1]>0 &&     //Charged Hadron Fraction 
           Jets_NCH[ij1]>0){     //Charged Multiplicity

          bool check = true;                           // judgement of overlap
            for(int i=0 ; i<*Leptons_Size ; i++){
                if(Leptons_Good[i]!=3) continue;
                if(fabs(Jets_P4[ij1].DeltaR(Leptons_P4[i]))< 0.4) check = false;  //if the jet is overlapping then tagging it as overlapping jet
            }
            if(check == true){                         // if the jet isn't tagged as overlapping jet then recording this jet as good jet
                Jets_Good[ij1]=1;
                Jets_No++;
                Jets_new_index[Jets_new_no] = ij1;     // the new index for the new sorted array for Jets ordering check 
                Jets_new_no++;
                Jets_HT += Jets_P4[ij1].Pt();
                hist_jet_cut->Fill(5, Event_Weight);
          
                hist_jet_pt->Fill(Jets_P4[ij1].Pt(), Event_Weight);
                hist_jet_eta->Fill(Jets_Eta[ij1], Event_Weight);
                hist_jet_phi->Fill(Jets_Phi[ij1], Event_Weight);
                //hist_jet_btag->Fill(Jets_CombinedIncSVBJetTags[ij1], Event_Weight);
                hist_jet_btag->Fill((Jets_DeepCSVJetTags_probb[ij1]+Jets_DeepCSVJetTags_probbb[ij1]), Event_Weight);
                
                m_st += Jets_P4[ij1].Pt();
            }//cut jets and leptons overlapping
        }//cut IDloose
      }//cut eta
    }//cut pt
  }//loop jet size
}//for Jet recon
//}}} 
// ReconBJet{{{
void MyTcZAna_2017_Central::ReconBJet(){
  m_bjet_no = 0;
  m_cbjet_no = 0;
  Btag_weight=1.0; //b-tagging SF
  
  for(int ij1=0; ij1 < *Jets_Size && ij1 < 64; ij1++){
    if(Jets_Good[ij1]<1) continue;

    if(*EvtInfo_McFlag > 0){ //apply to each jets
        Btag_weight *= BtaggingSF(Jets_P4[ij1].Pt(), 
                                  abs(Jets_Eta[ij1]), 
                                  //Jets_CombinedIncSVBJetTags[ij1], 
                                  (Jets_DeepCSVJetTags_probb[ij1]+Jets_DeepCSVJetTags_probbb[ij1]),
                                  Jets_GenFlavor[ij1]);
    }
    else Btag_weight=1.0;

  //b-tagging jets 
    double CSV_tag;

    CSV_tag = Jets_CombinedIncSVBJetTags[ij1];
    if(Jets_DeepCSVJetTags_probb[ij1]+Jets_DeepCSVJetTags_probbb[ij1] > JET_BTAG_CUT){
      hist_jet_cut->Fill(6, Event_Weight);
      Jets_Good[ij1]=2;  // medium WP

      m_bjet_no++;

    }//medium bjet
  }//loop jet size
}//Recon B-jet End
//}}}

void MyTcZAna_2017_Central::ReconTop(){

  double ERc_cjet_gm = 0.0;
  double ERc_cjet_choose = 0.0;
  double ERc_bjet_choose = 0.0;

  int m_wuu_idx = -1;
  int m_zee_idx = -1;
  int m_jet1_idx = -1; // b
  int m_jet2_idx = -1; // u,c
  int m_lep1_idx = -1; // Z l1
  int m_lep2_idx = -1; // Z l2
  int m_lep3_idx = -1; // W l

  int GM = 0;
  int flag_CSV = 0;
  double TopDR_gm = 0.0;
  double Topdphi_gm = 0.0;
  double BJetsDR_gm = 0.0;
  double BJetsdphi_gm = 0.0;
  double ZcJetDR_gm = 0.0;  
  double ZcJetdphi_gm = 0.0;
  double WbJetDR_gm = 0.0;
  double WbJetdphi_gm = 0.0; 
  double LepbJetdphi_gm = 0.0; 
  
  double ZbJetDR = 0.0;
  double WcJetDR = 0.0;
  double WLZL1DR = 0.0;
  double WLZL2DR = 0.0;
  double WLep_bjetDR = 0.0;
  double ZLep2_bjetDR = 0.0;
  double ZLep1_bjetDR = 0.0;
  double WLep_cjetDR = 0.0;
  double ZLep2_cjetDR = 0.0;
  double ZLep1_cjetDR = 0.0;
  double WLZL1dphi = 0.0;
  double WLZL2dphi = 0.0;
  double ZLep1_bjetDphi = 0.0;
  double ZLep2_bjetDphi = 0.0;
  double WLep_cjetDphi = 0.0;
  double ZLep1_cjetDphi = 0.0;
  double ZLep2_cjetDphi = 0.0;
  
  double TopDeta = 0.0;
  double Z_cjetDeta = 0.0;
  double Z_bjetDeta = 0.0;
  double W_cjetDeta = 0.0;
  double W_bjetDeta = 0.0;
  double ZLLpairDeta = 0.0;
  double WLZL1Deta = 0.0;
  double WLZL2Deta = 0.0;
  double WLep_bjetDeta = 0.0;
  double ZLep1_bjetDeta = 0.0;
  double ZLep2_bjetDeta = 0.0;
  double WLep_cjetDeta = 0.0;
  double ZLep1_cjetDeta = 0.0;
  double ZLep2_cjetDeta = 0.0;
   
  double TopDR = 0.0;
  double Topdphi = 0.0;
  double LepDR = 0.0;
  double Lepdphi = 0.0;
  double ZcJetDR = 0.0;  
  double ZbJetdphi = 0.0;
  double ZcJetdphi = 0.0;
  double WbJetDR = 0.0;
  double WbJetdphi = 0.0;
  double WcJetdphi = 0.0;
  double LepbJetdphi = 0.0;

  double TopMax = 99999; 
  double TopMassFlag = 0;
  int blep_flag = 99;
  int cjet_flag = 99;
  int woring_flag = 0;

  m_top_comb = 0;

  double SF_leptop = 1;
  double SF_hadtop = 1; 
  double WeightToppT = 1; 
  double CSVweight = 1; 

  int top_test1_P4 = 0;
  int top_test2_P4 = 0;
  
  int iz_Mva = 0;
  int iz_TTCR = 0;
  int ij1=-1;
  int ij2=-1;
  double z_MvaVar_m_diff = 0;
  double z_MvaVar_m_mini=9999;
  double z_TTCR_diff=0;
  double z_TTCR_mini=9999;
  double mvaOutput=0;

  //max deltaPhi of tops
  double top_dphi=0;
  double top_dphimax=-9999;
  int j1_dphi=-1;
  int j2_dphi=-1;
  //minimum Xsquare
  double Xsquare=0;
  double Xsquaremin=9999;
  int j1_Xsqu=-1;
  int j2_Xsqu=-1;
  //Isis method
  int idx1=-1;
  int idx2=-1;
  double csv_value=0.;
  double csv_max=-9999;
  double top_mass=0.;
  double top_mass_mini=9999;
  double sorting_output=0;
  double sorting_max=-9999;

  mvaOCPE=mvaOCPEt=mvaOCPEmax=-9999.;
  mvaOCPE0=mvaOCPE0t=mvaOCPE0max=-9999.;

  Top_P4[126]=TLorentzVector(0,0,0,0);
  Top_P4[127]=TLorentzVector(0,0,0,0);
  
// ***********  RealRun ************* //
//    /*FOR Signal matching method
  //WZCR Transfer Ratio
 
  if( (new_e_no+new_mu_no)==3 && Jets_new_no>=1 && Zee_No>0 && m_bjet_no>=0){
        //Fix the # of b==0
        if(m_bjet_no==0){
            if(Jets_new_no>=1){
                hist_b_no->Fill(2, Event_Weight);
                if(new_mu_no==3) hist_b_no_mmm->Fill(2, Event_Weight);
                if(new_mu_no==2 && new_e_no==1) hist_b_no_emm->Fill(2, Event_Weight);
                if(new_e_no==2 && new_mu_no==1) hist_b_no_eem->Fill(2, Event_Weight);
                if(new_e_no==3) hist_b_no_eee->Fill(2, Event_Weight);
            }
            if(Jets_new_no==2 || Jets_new_no==3){
                hist_b_no->Fill(3, Event_Weight);
                if(new_mu_no==3) hist_b_no_mmm->Fill(3, Event_Weight);
                if(new_mu_no==2 && new_e_no==1) hist_b_no_emm->Fill(3, Event_Weight);
                if(new_e_no==2 && new_mu_no==1) hist_b_no_eem->Fill(3, Event_Weight);
                if(new_e_no==3) hist_b_no_eee->Fill(3, Event_Weight);
            }
        }
        //Fix # of jet = 2 or 3
        if(Jets_new_no==2 || Jets_new_no==3){
            if(m_bjet_no==0){
                hist_b_no->Fill(5, Event_Weight);
                if(new_mu_no==3) hist_b_no_mmm->Fill(5, Event_Weight);
                if(new_mu_no==2 && new_e_no==1) hist_b_no_emm->Fill(5, Event_Weight);
                if(new_e_no==2 && new_mu_no==1) hist_b_no_eem->Fill(5, Event_Weight);
                if(new_e_no==3) hist_b_no_eee->Fill(5, Event_Weight);
            }
            if(m_bjet_no>0){
                hist_b_no->Fill(6, Event_Weight);
                if(new_mu_no==3) hist_b_no_mmm->Fill(6, Event_Weight);
                if(new_mu_no==2 && new_e_no==1) hist_b_no_emm->Fill(6, Event_Weight);
                if(new_e_no==2 && new_mu_no==1) hist_b_no_eem->Fill(6, Event_Weight);
                if(new_e_no==3) hist_b_no_eee->Fill(6, Event_Weight);
            }
        }
        
        //Fix the # of b>0
        if(m_bjet_no>0){
            if(Jets_new_no>=1){
                hist_b_no->Fill(8, Event_Weight);
                if(new_mu_no==3) hist_b_no_mmm->Fill(8, Event_Weight);
                if(new_mu_no==2 && new_e_no==1) hist_b_no_emm->Fill(8, Event_Weight);
                if(new_e_no==2 && new_mu_no==1) hist_b_no_eem->Fill(8, Event_Weight);
                if(new_e_no==3) hist_b_no_eee->Fill(8, Event_Weight);
            }
            if(Jets_new_no==2 || Jets_new_no==3){
                hist_b_no->Fill(9, Event_Weight);
                if(new_mu_no==3) hist_b_no_mmm->Fill(9, Event_Weight);
                if(new_mu_no==2 && new_e_no==1) hist_b_no_emm->Fill(9, Event_Weight);
                if(new_e_no==2 && new_mu_no==1) hist_b_no_eem->Fill(9, Event_Weight);
                if(new_e_no==3) hist_b_no_eee->Fill(9, Event_Weight);
            }
        }
        //Fix # of jet >= 1
        if(Jets_new_no>0){
            if(m_bjet_no==0){
                hist_b_no->Fill(11, Event_Weight);
                if(new_mu_no==3) hist_b_no_mmm->Fill(11, Event_Weight);
                if(new_mu_no==2 && new_e_no==1) hist_b_no_emm->Fill(11, Event_Weight);
                if(new_e_no==2 && new_mu_no==1) hist_b_no_eem->Fill(11, Event_Weight);
                if(new_e_no==3) hist_b_no_eee->Fill(11, Event_Weight);
            }
            if(m_bjet_no>0){
                hist_b_no->Fill(12, Event_Weight);
                if(new_mu_no==3) hist_b_no_mmm->Fill(12, Event_Weight);
                if(new_mu_no==2 && new_e_no==1) hist_b_no_emm->Fill(12, Event_Weight);
                if(new_e_no==2 && new_mu_no==1) hist_b_no_eem->Fill(12, Event_Weight);
                if(new_e_no==3) hist_b_no_eee->Fill(12, Event_Weight);
            }
        }
  }
  // WZCR only need Transverse Mass of W
  if( (new_e_no+new_mu_no)==3 && Jets_new_no>=1 && Zee_No>0 && m_bjet_no==0){
    for(int iz=0 ; iz < Zee_No ; iz++){
        z_MvaVar_m_diff = abs(MASS_Z0- Zee_P4[iz].M());
        if( z_MvaVar_m_diff<z_MvaVar_m_mini){
            z_MvaVar_m_mini=z_MvaVar_m_diff;
            iz_Mva = iz;
        }
    }
    for(int iw=0 ; iw< Wuu_No ; iw++){
        if(Zee_lid1[iz_Mva] == Wuu_lid[iw] ||
           Zee_lid2[iz_Mva] == Wuu_lid[iw]) continue;  //no lepton overlap
        
        if(new_e_no==3){
            hist_w_mt_eee->Fill(Wuu_Mt[iw], Event_Weight*Btag_weight);
            hist_evt_weightB->Fill(17, Event_Weight);
            hist_evt_weightA->Fill(17, Event_Weight*Btag_weight);
        }
        if((new_e_no==2) && new_mu_no==1){
            hist_w_mt_eem->Fill(Wuu_Mt[iw], Event_Weight*Btag_weight);
            hist_evt_weightB->Fill(18, Event_Weight);
            hist_evt_weightA->Fill(18, Event_Weight*Btag_weight);
        }
        if((new_mu_no==2) && new_e_no==1){ 
            hist_w_mt_emm->Fill(Wuu_Mt[iw], Event_Weight*Btag_weight);
            hist_evt_weightB->Fill(19, Event_Weight);
            hist_evt_weightA->Fill(19, Event_Weight*Btag_weight);
        }
        if(new_mu_no==3){
            hist_w_mt_mmm->Fill(Wuu_Mt[iw], Event_Weight*Btag_weight);
            hist_evt_weightB->Fill(20, Event_Weight);
            hist_evt_weightA->Fill(20, Event_Weight*Btag_weight);
        }

    }
  }
  
  // TTCR only need Invariant Mass of Z
  if( (new_e_no+new_mu_no)==3 && Jets_new_no>=2 && Jets_new_no<=3 && Z_No>0 && m_bjet_no>0){
    for(int iz=0 ; iz < Z_No ; iz++){
        z_TTCR_diff = abs(MASS_Z0- Z_P4[iz].M());
        if( z_TTCR_diff<z_TTCR_mini){
            z_TTCR_mini=z_TTCR_diff;
            iz_TTCR = iz;
        }
    }
    for(int iw=0 ; iw< Wuu_No ; iw++){
        if(Z_lid1[iz_TTCR] == Wuu_lid[iw] ||
           Z_lid2[iz_TTCR] == Wuu_lid[iw]) continue;  //no lepton overlap
        
        if(new_e_no==3){
            hist_Zmass_eee->Fill(Z_P4[iz_TTCR].M(), Event_Weight*Btag_weight);
            hist_evt_weightB->Fill(21, Event_Weight);
            hist_evt_weightA->Fill(21, Event_Weight*Btag_weight);
        }
        if((new_e_no==2) && new_mu_no==1){
            hist_Zmass_eem->Fill(Z_P4[iz_TTCR].M(), Event_Weight*Btag_weight);
            hist_evt_weightB->Fill(22, Event_Weight);
            hist_evt_weightA->Fill(22, Event_Weight*Btag_weight);
        }
        if((new_mu_no==2) && new_e_no==1){
            hist_Zmass_emm->Fill(Z_P4[iz_TTCR].M(), Event_Weight*Btag_weight);
            hist_evt_weightB->Fill(23, Event_Weight);
            hist_evt_weightA->Fill(23, Event_Weight*Btag_weight);
        }
        if(new_mu_no==3){
            hist_Zmass_mmm->Fill(Z_P4[iz_TTCR].M(), Event_Weight*Btag_weight);
            hist_evt_weightB->Fill(24, Event_Weight);
            hist_evt_weightA->Fill(24, Event_Weight*Btag_weight);
        }

    }
  }
  
  // TT FCNC SR
  if( (new_e_no+new_mu_no)==3 && Jets_new_no>=2 && Jets_new_no<=3 && Zee_No>0 && m_bjet_no>0){
    for(int iz=0 ; iz < Zee_No ; iz++){
        z_MvaVar_m_diff = abs(MASS_Z0- Zee_P4[iz].M());
        if( z_MvaVar_m_diff<z_MvaVar_m_mini){
            z_MvaVar_m_mini=z_MvaVar_m_diff;
            iz_Mva = iz;
        }
    }
    for(int iw=0 ; iw< Wuu_No ; iw++){
        if(Zee_lid1[iz_Mva] == Wuu_lid[iw] ||
           Zee_lid2[iz_Mva] == Wuu_lid[iw]) continue;  //no lepton overlap
    
        if((new_mu_no+new_e_no)==3 && (new_e_no>=2)) hist_w_mt_DE_test->Fill(Wuu_Mt[iw], Event_Weight*Btag_weight);
        if((new_mu_no+new_e_no)==3 && (new_mu_no>=2)) hist_w_mt_DM_test->Fill(Wuu_Mt[iw], Event_Weight*Btag_weight);
     

//{{{        //Isis methods 
/*        if(Jets_new_no<=3 && m_bjet_no>0){
            for(int ji1=0 ; ji1<*Jets_Size ; ji1++){
                if(Jets_Good[ji1]<1) continue;
                csv_value=Jets_CombinedIncSVBJetTags[ji1];
                if(csv_value>csv_max){
                   csv_max=csv_value;
                   idx1=ji1;
                }
            }
            for(int ji2=0 ; ji2<*Jets_Size ; ji2++){
                if(Jets_Good[ji2]<1) continue;
                if(ji2==idx1) continue;
                top_mass=(Jets_P4[ji2]+Zee_P4[iz_Mva]).M();
                if(abs(top_mass-172.44)<top_mass_mini){
                    top_mass_mini=abs(top_mass-172.44);
                    idx2=ji2;
                }
            }
        }
        if(idx1>-1 && idx2>-1){
            if((new_mu_no+new_e_no)==3 && (new_e_no>=2)){
                hist_total_top_whole_DE->Fill((Jets_P4[idx2]+Jets_P4[idx1]+Zee_P4[iz_Mva]+Wuu_P4[iw]).M(), Event_Weight);
                selectionNo++;
            }
            if((new_mu_no+new_e_no)==3 && (new_mu_no>=2)){
                hist_total_top_whole_DM->Fill((Jets_P4[idx2]+Jets_P4[idx1]+Zee_P4[iz_Mva]+Wuu_P4[iw]).M(), Event_Weight);
            }
            if((Jets_P4[idx1]+Wuu_P4[iw]).M()>=0. && (Jets_P4[idx1]+Wuu_P4[iw]).M()<=350. &&
               (Jets_P4[idx2]+Zee_P4[iz_Mva]).M()>=0. && (Jets_P4[idx2]+Zee_P4[iz_Mva]).M()<=350.){
                if((new_mu_no+new_e_no)==3 && (new_e_no>=2)){
                    hist_total_top_DE->Fill((Jets_P4[idx2]+Jets_P4[idx1]+Zee_P4[iz_Mva]+Wuu_P4[iw]).M(), Event_Weight);
                    hist_tree_top_DE->Fill((Jets_P4[idx1]+Wuu_P4[iw]).M(), Event_Weight);
                    hist_fcnc_top_DE->Fill((Jets_P4[idx2]+Zee_P4[iz_Mva]).M(), Event_Weight);
                    hist_2D_top_DE->Fill((Jets_P4[idx1]+Wuu_P4[iw]).M(), (Jets_P4[idx2]+Zee_P4[iz_Mva]).M(), Event_Weight);
                }
                if((new_mu_no+new_e_no)==3 && (new_mu_no>=2)){
                    hist_total_top_DM->Fill((Jets_P4[idx2]+Jets_P4[idx1]+Zee_P4[iz_Mva]+Wuu_P4[iw]).M(), Event_Weight);
                    hist_tree_top_DM->Fill((Jets_P4[idx1]+Wuu_P4[iw]).M(), Event_Weight);
                    hist_fcnc_top_DM->Fill((Jets_P4[idx2]+Zee_P4[iz_Mva]).M(), Event_Weight);
                    hist_2D_top_DM->Fill((Jets_P4[idx1]+Wuu_P4[iw]).M(), (Jets_P4[idx2]+Zee_P4[iz_Mva]).M(), Event_Weight);
                }
            }
        }*/
//}}}
//{{{ For Sorting comparison & Truth matching (Status : comment out)
    /*
       //Expansion of every combinations (For sorting)
        for(int j3=0 ; j3<*Jets_Size ; j3++){
            if(Jets_Good[j3]<2) continue; //bjet
            if(fabs(Jets_P4[j3].DeltaR(Leptons_P4[Wuu_lid[iw]])) < 0.4) continue;
            if(fabs(Jets_P4[j3].DeltaR(Leptons_P4[Zee_lid1[iz_Mva]])) < 0.4) continue;
            if(fabs(Jets_P4[j3].DeltaR(Leptons_P4[Zee_lid2[iz_Mva]])) < 0.4) continue;
            for(int j4=0 ; j4<*Jets_Size ; j4++){
                if(Jets_Good[j4]<1) continue;
                if(j4==j3) continue;
                if(fabs(Jets_P4[j4].DeltaR(Leptons_P4[Wuu_lid[iw]])) < 0.4) continue;
                if(fabs(Jets_P4[j4].DeltaR(Leptons_P4[Zee_lid1[iz_Mva]])) < 0.4) continue;
                if(fabs(Jets_P4[j4].DeltaR(Leptons_P4[Zee_lid2[iz_Mva]])) < 0.4) continue;
               
                Top_P4[5] = Wuu_P4[iw] + Jets_P4[j3];
                Top_P4[6] = Zee_P4[iz_Mva] + Jets_P4[j4];
                top_dphi = fabs(Top_P4[5].DeltaPhi(Top_P4[6]));
                Xsquare = (top_dphi-2.469)*(top_dphi-2.469)/(0.7349*0.7349)+
                          (Top_P4[5].M()-179.6)*(Top_P4[5].M()-179.6)/(55.82*55.82) +
                          (Top_P4[6].M()-200)*(Top_P4[6].M()-200)/(52.8*52.8);
                hist_top_dphi->Fill(top_dphi, Event_Weight);
                hist_top_tree->Fill(Top_P4[5].M(), Event_Weight);
                hist_top_fcnc->Fill(Top_P4[6].M(), Event_Weight);
                
                if( top_dphi>top_dphimax ){
                    top_dphimax=top_dphi;
                    j1_dphi=j3;
                    j2_dphi=j4;
                }
                if( Xsquare<Xsquaremin ){
                    Xsquaremin = Xsquare;
                    j1_Xsqu=j3;
                    j2_Xsqu=j4;
                }
            }
        }
        if(*EvtInfo_McFlag > 0){ // MC events
      
            if(m_gen_top1_idx > 0 && m_gen_top2_idx > 0 &&
               m_gen_zee_idx > 0 && m_gen_wuu_idx > 0 ){//&&
              
              if(j1_dphi>=0 && j2_dphi>=0){
                Topdphi_MCTruth_pre++;
                if(m_gen_jet1_idx > 0 && m_gen_jet2_idx>0 &&
                   GenParts_P4[m_gen_jet1_idx].Pt() > 0.1 &&
                   GenParts_P4[m_gen_jet2_idx].Pt() > 0.1 &&
                   fabs(Jets_P4[j1_dphi].DeltaR(GenParts_P4[m_gen_jet1_idx]))<0.4 &&
                   fabs(Jets_P4[j2_dphi].DeltaR(GenParts_P4[m_gen_jet2_idx]))<0.4) Topdphi_MCTruth++;
              }

              if(j1_Xsqu>=0 && j2_Xsqu>=0){
                Xsquare_MCTruth_pre++;
                if(m_gen_jet1_idx > 0 && m_gen_jet2_idx>0 &&
                   GenParts_P4[m_gen_jet1_idx].Pt() > 0.1 &&
                   GenParts_P4[m_gen_jet2_idx].Pt() > 0.1 &&
                   fabs(Jets_P4[j1_Xsqu].DeltaR(GenParts_P4[m_gen_jet1_idx]))<0.4 &&
                   fabs(Jets_P4[j2_Xsqu].DeltaR(GenParts_P4[m_gen_jet2_idx]))<0.4) Xsquare_MCTruth++;
              }
            }
        }
*/        
//}}}      
        //For BDT all combinations
         for(int ij1=0 ; ij1<*Jets_Size ; ij1++){
            if(Jets_Good[ij1]<2) continue; //bjet
            if(fabs(Jets_P4[ij1].DeltaR(Leptons_P4[Wuu_lid[iw]])) < 0.4) continue;
            if(fabs(Jets_P4[ij1].DeltaR(Leptons_P4[Zee_lid1[iz_Mva]])) < 0.4) continue;
            if(fabs(Jets_P4[ij1].DeltaR(Leptons_P4[Zee_lid2[iz_Mva]])) < 0.4) continue;
            for(int ij2=0 ; ij2<*Jets_Size ; ij2++){
                if(Jets_Good[ij2]<1) continue;
                if(ij2==ij1) continue;
                if(fabs(Jets_P4[ij2].DeltaR(Leptons_P4[Wuu_lid[iw]])) < 0.4) continue;
                if(fabs(Jets_P4[ij2].DeltaR(Leptons_P4[Zee_lid1[iz_Mva]])) < 0.4) continue;
                if(fabs(Jets_P4[ij2].DeltaR(Leptons_P4[Zee_lid2[iz_Mva]])) < 0.4) continue;
  
    
//{{{ MVA variables
        Top_P4[0] = Wuu_P4[iw] + Jets_P4[ij1];
        Top_P4[1] = Zee_P4[iz_Mva] + Jets_P4[ij2];

        ZcJetDR   = Zee_P4[iz_Mva].DeltaR(Jets_P4[ij2]); //c Z DR
        LepDR     = Leptons_P4[Zee_lid1[iz_Mva]].DeltaR(
                               Leptons_P4[Zee_lid2[iz_Mva]]);// 2 lep DR
        WbJetDR   = Jets_P4[ij1].DeltaR(Wuu_P4[iw]);//W b DR
        TopDR     = Top_P4[0].DeltaR(Top_P4[1]); //two top DR
            
        ZbJetdphi = Zee_P4[iz_Mva].DeltaPhi(Jets_P4[ij1]); //b Z Dphi
        ZcJetdphi = Zee_P4[iz_Mva].DeltaPhi(Jets_P4[ij2]); //c Z Dphi
        Lepdphi   = Leptons_P4[Zee_lid1[iz_Mva]].DeltaPhi(
                                 Leptons_P4[Zee_lid2[iz_Mva]]);// 2 lep Dphi
        WbJetdphi = Wuu_P4[iw].DeltaPhi(Jets_P4[ij1]); // W b Dphi
        WcJetdphi = Wuu_P4[iw].DeltaPhi(Jets_P4[ij2]); // W b Dphi
        LepbJetdphi = Jets_P4[ij1].DeltaPhi(Leptons_P4[Wuu_lid[iw]]);
                                                      //W_l b Dphi
        Topdphi   = Top_P4[0].DeltaPhi(Top_P4[1]);//two top Dphi
            
        // Boost
        Jets_P4[127] = Jets_P4[ij2];
        //ERc_topCoor[3] = Top_P4[0].BoostVector();
        //ERc_topCoor[4] = -ERc_topCoor[3];
        Jets_P4[127].Boost(-Top_P4[1].BoostVector());
        ERc_cjet_choose = Jets_P4[127].E();
      
        Jets_P4[126] = Jets_P4[ij1];
        Jets_P4[126].Boost(-Top_P4[0].BoostVector());
        ERc_bjet_choose = Jets_P4[126].E();
        
        // mvaTree 
        TopInfo_Pt_bw = Top_P4[0].Pt();
        TopInfo_M_bw = Top_P4[0].M();
        TopInfo_Mt_bw = Top_P4[0].Mt();
        TopInfo_Pt_cz = Top_P4[1].Pt();
        TopInfo_M_cz = Top_P4[1].M();
        TopInfo_Mt_cz = Top_P4[1].Mt();
        WInfo_Pt = Wuu_P4[0].Pt();
        WInfo_Mt = Wuu_Mt[0];
        ZInfo_Pt = Zee_P4[0].Pt();
        ZInfo_M  = Zee_P4[0].M();
        
        //if(TMath::IsNaN(Jets_P4[126].E())) continue;
        //cout << "BJetBoost_E : " << Jets_P4[126].E()<< endl;

        CJetBoost_E = ERc_cjet_choose;
        BJetBoost_E = ERc_bjet_choose;

        TopTop_dphi = fabs(Topdphi);
        W_bjet_dphi = fabs(WbJetdphi);
        W_cjet_dphi = fabs(WcJetdphi);
        WLep_bjet_dphi = fabs(LepbJetdphi);
        WLep_bjet_dphi = fabs(Jets_P4[ij1].DeltaPhi(Leptons_P4[Wuu_lid[iw]]));
        WLep_cjet_dphi = fabs(Jets_P4[ij2].DeltaPhi(Leptons_P4[Wuu_lid[iw]]));
        Z_bjet_dphi = fabs(ZbJetdphi);
        Z_cjet_dphi = fabs(ZcJetdphi);
        ZLLpair_dphi = fabs(Lepdphi);
        ZLep1_bjet_dphi =fabs(Jets_P4[ij1].DeltaPhi(Leptons_P4[Zee_lid1[iz_Mva]]));
        ZLep2_bjet_dphi =fabs(Jets_P4[ij1].DeltaPhi(Leptons_P4[Zee_lid2[iz_Mva]]));
        ZLep1_cjet_dphi =fabs(Jets_P4[ij2].DeltaPhi(Leptons_P4[Zee_lid1[iz_Mva]]));
        ZLep2_cjet_dphi =fabs(Jets_P4[ij2].DeltaPhi(Leptons_P4[Zee_lid2[iz_Mva]]));
        WLZL1_dphi = fabs(Leptons_P4[Wuu_lid[iw]].DeltaPhi(
                                               Leptons_P4[Zee_lid1[iz_Mva]]));
        WLZL2_dphi = fabs(Leptons_P4[Wuu_lid[iw]].DeltaPhi(
                                               Leptons_P4[Zee_lid2[iz_Mva]]));
      
        TopTop_DR = TopDR;
        W_bjet_DR = WbJetDR;
        Z_cjet_DR = ZcJetDR;
        ZLLpair_DR = LepDR;
      
        BJet_btag = (Jets_DeepCSVJetTags_probb[ij1]+Jets_DeepCSVJetTags_probbb[ij1]);
        //BJet_btag = Jets_CombinedIncSVBJetTags[ij1];
        //BJet_ctag = Jets_CombinedCvsBJetTags[ij1];
        CJet_btag = (Jets_DeepCSVJetTags_probb[ij2]+Jets_DeepCSVJetTags_probbb[ij2]);
        //CJet_btag = Jets_CombinedIncSVBJetTags[ij2];
        //CJet_ctag = Jets_CombinedCvsBJetTags[ij2];

       
        ZbJetDR = Zee_P4[iz_Mva].DeltaR(Jets_P4[ij1]);
        WcJetDR = Wuu_P4[iw].DeltaR(Jets_P4[ij2]);
        WLZL1DR = Leptons_P4[Wuu_lid[iw]].DeltaR(Leptons_P4[Zee_lid1[iz_Mva]]);
        WLZL2DR = Leptons_P4[Wuu_lid[iw]].DeltaR(Leptons_P4[Zee_lid2[iz_Mva]]);
        WLep_bjetDR = Leptons_P4[Wuu_lid[iw]].DeltaR(Jets_P4[ij1]);
        ZLep1_bjetDR = Leptons_P4[Zee_lid1[iz_Mva]].DeltaR(Jets_P4[ij1]);
        ZLep2_bjetDR = Leptons_P4[Zee_lid2[iz_Mva]].DeltaR(Jets_P4[ij1]);
        WLep_cjetDR = Leptons_P4[Wuu_lid[iw]].DeltaR(Jets_P4[ij2]);
        ZLep1_cjetDR = Leptons_P4[Zee_lid1[iz_Mva]].DeltaR(Jets_P4[ij2]);
        ZLep2_cjetDR = Leptons_P4[Zee_lid2[iz_Mva]].DeltaR(Jets_P4[ij2]);
        WLZL1dphi = fabs(Leptons_P4[Wuu_lid[iw]].DeltaPhi(
                                                Leptons_P4[Zee_lid1[iz_Mva]]));
        WLZL2dphi = fabs(Leptons_P4[Wuu_lid[iw]].DeltaPhi(
                                                Leptons_P4[Zee_lid2[iz_Mva]]));
        ZLep1_bjetDphi = fabs(Jets_P4[ij1].DeltaPhi(Leptons_P4[Zee_lid1[iz_Mva]]));
        ZLep2_bjetDphi = fabs(Jets_P4[ij1].DeltaPhi(Leptons_P4[Zee_lid2[iz_Mva]]));
        WLep_cjetDphi = fabs(Jets_P4[ij2].DeltaPhi(Leptons_P4[Wuu_lid[iw]]));
        ZLep1_cjetDphi = fabs(Jets_P4[ij2].DeltaPhi(Leptons_P4[Zee_lid1[iz_Mva]]));
        ZLep2_cjetDphi = fabs(Jets_P4[ij2].DeltaPhi(Leptons_P4[Zee_lid2[iz_Mva]]));
       
       
        TopDeta =         TMath::Sqrt((TopDR*TopDR - Topdphi*Topdphi));
        Z_cjetDeta =      TMath::Sqrt((ZcJetDR*ZcJetDR - ZcJetdphi*ZcJetdphi));
        Z_bjetDeta =      TMath::Sqrt((ZbJetDR*ZbJetDR - ZbJetdphi*ZbJetdphi));
        W_cjetDeta =      TMath::Sqrt((WcJetDR*WcJetDR - WcJetdphi*WcJetdphi));
        W_bjetDeta =      TMath::Sqrt((WbJetDR*WbJetDR - WbJetdphi*WbJetdphi));  
        ZLLpairDeta =     TMath::Sqrt((LepDR*LepDR - Lepdphi*Lepdphi));
        WLZL1Deta =       TMath::Sqrt((WLZL1DR*WLZL1DR - WLZL1dphi*WLZL1dphi));
        WLZL2Deta =       TMath::Sqrt((WLZL2DR*WLZL2DR - WLZL2dphi*WLZL2dphi));
        WLep_bjetDeta =   TMath::Sqrt((WLep_bjetDR*WLep_bjetDR - LepbJetdphi*LepbJetdphi));
        ZLep1_bjetDeta =  TMath::Sqrt((ZLep1_bjetDR*ZLep1_bjetDR - ZLep1_bjetDphi*ZLep1_bjetDphi));
        ZLep2_bjetDeta =  TMath::Sqrt((ZLep2_bjetDR*ZLep2_bjetDR - ZLep2_bjetDphi*ZLep2_bjetDphi));
        WLep_cjetDeta =   TMath::Sqrt((WLep_cjetDR*WLep_cjetDR - WLep_cjetDphi*WLep_cjetDphi));
        ZLep1_cjetDeta =  TMath::Sqrt((ZLep1_cjetDR*ZLep1_cjetDR - ZLep1_cjetDphi*ZLep1_cjetDphi));
        ZLep2_cjetDeta =  TMath::Sqrt((ZLep2_cjetDR*ZLep2_cjetDR - ZLep2_cjetDphi*ZLep2_cjetDphi));

        TopTop_deta =      TopDeta;
        Z_cjet_deta =      Z_cjetDeta;
        Z_bjet_deta =      Z_bjetDeta;
        W_cjet_deta =      W_cjetDeta;
        W_bjet_deta =      W_bjetDeta;
        ZLLpair_deta =     ZLLpairDeta;
        WLZL1_deta =       WLZL1Deta;
        WLZL2_deta =       WLZL2Deta;
        WLep_bjet_deta =   WLep_bjetDeta;
        ZLep1_bjet_deta =  ZLep1_bjetDeta;
        ZLep2_bjet_deta =  ZLep2_bjetDeta;
        WLep_cjet_deta =   WLep_cjetDeta;
        ZLep1_cjet_deta =  ZLep1_cjetDeta;
        ZLep2_cjet_deta =  ZLep2_cjetDeta;
        
        jet_mva_no = Jets_new_no;
        lep_mva_no = (new_e_no+new_mu_no);
        jet_mva_event_orignal_no = *Jets_Size;
        lep_mva_event_orignal_no = *Leptons_Size;
        MVAweight = Event_Weight*Btag_weight;
//}}}

        sorting_output = sorting->EvaluateMVA("Sorting_Value");
        if(sorting_output > sorting_max){
          sorting_max = sorting_output;
          m_wuu_idx = iw;
          m_zee_idx = iz_Mva;
          m_jet1_idx = ij1;
          m_jet2_idx = ij2;
        }
      }//light jet
     }// b jet
    }// lepton
    
    if(m_wuu_idx>-1 && m_zee_idx>-1 && m_jet1_idx>-1 && m_jet2_idx>-1){ 
        //{{{MVA variables for SignalExtraction
        Top_P4[0] = Wuu_P4[m_wuu_idx] + Jets_P4[m_jet1_idx];
        Top_P4[1] = Zee_P4[m_zee_idx] + Jets_P4[m_jet2_idx];

        ZcJetDR   = Zee_P4[m_zee_idx].DeltaR(Jets_P4[m_jet2_idx]); //c Z DR
        LepDR     = Leptons_P4[Zee_lid1[m_zee_idx]].DeltaR(
                               Leptons_P4[Zee_lid2[m_zee_idx]]);// 2 lep DR
        WbJetDR   = Jets_P4[m_jet1_idx].DeltaR(Wuu_P4[m_wuu_idx]);//W b DR
        TopDR     = Top_P4[0].DeltaR(Top_P4[1]); //two top DR
            
        ZbJetdphi = Zee_P4[m_zee_idx].DeltaPhi(Jets_P4[m_jet1_idx]); //b Z Dphi
        ZcJetdphi = Zee_P4[m_zee_idx].DeltaPhi(Jets_P4[m_jet2_idx]); //c Z Dphi
        Lepdphi   = Leptons_P4[Zee_lid1[m_zee_idx]].DeltaPhi(
                                 Leptons_P4[Zee_lid2[m_zee_idx]]);// 2 lep Dphi
        WbJetdphi = Wuu_P4[m_wuu_idx].DeltaPhi(Jets_P4[m_jet1_idx]); // W b Dphi
        WcJetdphi = Wuu_P4[m_wuu_idx].DeltaPhi(Jets_P4[m_jet2_idx]); // W b Dphi
        LepbJetdphi = Jets_P4[m_jet1_idx].DeltaPhi(Leptons_P4[Wuu_lid[m_wuu_idx]]);
                                                      //W_l b Dphi
        Topdphi   = Top_P4[0].DeltaPhi(Top_P4[1]);//two top Dphi
            
        // Boost
        Jets_P4[127] = Jets_P4[m_jet2_idx];
        //ERc_topCoor[3] = Top_P4[0].BoostVector();
        //ERc_topCoor[4] = -ERc_topCoor[3];
        Jets_P4[127].Boost(-Top_P4[1].BoostVector());
        ERc_cjet_choose = Jets_P4[127].E();
      
        Jets_P4[126] = Jets_P4[m_jet1_idx];
        Jets_P4[126].Boost(-Top_P4[0].BoostVector());
        ERc_bjet_choose = Jets_P4[126].E();
        
        // mvaTree 
        TopInfo_Pt_bw = Top_P4[0].Pt();
        TopInfo_M_bw = Top_P4[0].M();
        TopInfo_Mt_bw = Top_P4[0].Mt();
        TopInfo_Pt_cz = Top_P4[1].Pt();
        TopInfo_M_cz = Top_P4[1].M();
        TopInfo_Mt_cz = Top_P4[1].Mt();
        WInfo_Pt = Wuu_P4[0].Pt();
        WInfo_Mt = Wuu_Mt[0];
        ZInfo_Pt = Zee_P4[0].Pt();
        ZInfo_M  = Zee_P4[0].M();
        
        //cout << "BJetBoost_E : " << Jets_P4[126].E()<< endl;

        CJetBoost_E = ERc_cjet_choose;
        BJetBoost_E = ERc_bjet_choose;

        TopTop_dphi = fabs(Topdphi);
        W_bjet_dphi = fabs(WbJetdphi);
        W_cjet_dphi = fabs(WcJetdphi);
        WLep_bjet_dphi = fabs(LepbJetdphi);
        WLep_bjet_dphi = fabs(Jets_P4[m_jet1_idx].DeltaPhi(Leptons_P4[Wuu_lid[m_wuu_idx]]));
        WLep_cjet_dphi = fabs(Jets_P4[m_jet2_idx].DeltaPhi(Leptons_P4[Wuu_lid[m_wuu_idx]]));
        Z_bjet_dphi = fabs(ZbJetdphi);
        Z_cjet_dphi = fabs(ZcJetdphi);
        ZLLpair_dphi = fabs(Lepdphi);
        ZLep1_bjet_dphi =fabs(Jets_P4[m_jet1_idx].DeltaPhi(Leptons_P4[Zee_lid1[m_zee_idx]]));
        ZLep2_bjet_dphi =fabs(Jets_P4[m_jet1_idx].DeltaPhi(Leptons_P4[Zee_lid2[m_zee_idx]]));
        ZLep1_cjet_dphi =fabs(Jets_P4[m_jet2_idx].DeltaPhi(Leptons_P4[Zee_lid1[m_zee_idx]]));
        ZLep2_cjet_dphi =fabs(Jets_P4[m_jet2_idx].DeltaPhi(Leptons_P4[Zee_lid2[m_zee_idx]]));
        WLZL1_dphi = fabs(Leptons_P4[Wuu_lid[m_wuu_idx]].DeltaPhi(
                                               Leptons_P4[Zee_lid1[m_zee_idx]]));
        WLZL2_dphi = fabs(Leptons_P4[Wuu_lid[m_wuu_idx]].DeltaPhi(
                                               Leptons_P4[Zee_lid2[m_zee_idx]]));
      
        TopTop_DR = TopDR;
        W_bjet_DR = WbJetDR;
        Z_cjet_DR = ZcJetDR;
        ZLLpair_DR = LepDR;
      
        BJet_btag = (Jets_DeepCSVJetTags_probb[m_jet1_idx]+Jets_DeepCSVJetTags_probbb[m_jet1_idx]);
        //BJet_btag = Jets_CombinedIncSVBJetTags[m_jet1_idx];
        //BJet_ctag = Jets_CombinedCvsBJetTags[m_jet1_idx];
        CJet_btag = (Jets_DeepCSVJetTags_probb[m_jet2_idx]+Jets_DeepCSVJetTags_probbb[m_jet2_idx]);
        //CJet_btag = Jets_CombinedIncSVBJetTags[m_jet2_idx];
        //CJet_ctag = Jets_CombinedCvsBJetTags[m_jet2_idx];
       
        ZbJetDR = Zee_P4[m_zee_idx].DeltaR(Jets_P4[m_jet1_idx]);
        WcJetDR = Wuu_P4[m_wuu_idx].DeltaR(Jets_P4[m_jet2_idx]);
        WLZL1DR = Leptons_P4[Wuu_lid[m_wuu_idx]].DeltaR(Leptons_P4[Zee_lid1[m_zee_idx]]);
        WLZL2DR = Leptons_P4[Wuu_lid[m_wuu_idx]].DeltaR(Leptons_P4[Zee_lid2[m_zee_idx]]);
        WLep_bjetDR = Leptons_P4[Wuu_lid[m_wuu_idx]].DeltaR(Jets_P4[m_jet1_idx]);
        ZLep1_bjetDR = Leptons_P4[Zee_lid1[m_zee_idx]].DeltaR(Jets_P4[m_jet1_idx]);
        ZLep2_bjetDR = Leptons_P4[Zee_lid2[m_zee_idx]].DeltaR(Jets_P4[m_jet1_idx]);
        WLep_cjetDR = Leptons_P4[Wuu_lid[m_wuu_idx]].DeltaR(Jets_P4[m_jet2_idx]);
        ZLep1_cjetDR = Leptons_P4[Zee_lid1[m_zee_idx]].DeltaR(Jets_P4[m_jet2_idx]);
        ZLep2_cjetDR = Leptons_P4[Zee_lid2[m_zee_idx]].DeltaR(Jets_P4[m_jet2_idx]);
        WLZL1dphi = fabs(Leptons_P4[Wuu_lid[m_wuu_idx]].DeltaPhi(
                                                Leptons_P4[Zee_lid1[m_zee_idx]]));
        WLZL2dphi = fabs(Leptons_P4[Wuu_lid[m_wuu_idx]].DeltaPhi(
                                                Leptons_P4[Zee_lid2[m_zee_idx]]));
        ZLep1_bjetDphi = fabs(Jets_P4[m_jet1_idx].DeltaPhi(Leptons_P4[Zee_lid1[m_zee_idx]]));
        ZLep2_bjetDphi = fabs(Jets_P4[m_jet1_idx].DeltaPhi(Leptons_P4[Zee_lid2[m_zee_idx]]));
        WLep_cjetDphi = fabs(Jets_P4[m_jet2_idx].DeltaPhi(Leptons_P4[Wuu_lid[m_wuu_idx]]));
        ZLep1_cjetDphi = fabs(Jets_P4[m_jet2_idx].DeltaPhi(Leptons_P4[Zee_lid1[m_zee_idx]]));
        ZLep2_cjetDphi = fabs(Jets_P4[m_jet2_idx].DeltaPhi(Leptons_P4[Zee_lid2[m_zee_idx]]));
       
       
        TopDeta =         TMath::Sqrt((TopDR*TopDR - Topdphi*Topdphi));
        Z_cjetDeta =      TMath::Sqrt((ZcJetDR*ZcJetDR - ZcJetdphi*ZcJetdphi));
        Z_bjetDeta =      TMath::Sqrt((ZbJetDR*ZbJetDR - ZbJetdphi*ZbJetdphi));
        W_cjetDeta =      TMath::Sqrt((WcJetDR*WcJetDR - WcJetdphi*WcJetdphi));
        W_bjetDeta =      TMath::Sqrt((WbJetDR*WbJetDR - WbJetdphi*WbJetdphi));  
        ZLLpairDeta =     TMath::Sqrt((LepDR*LepDR - Lepdphi*Lepdphi));
        WLZL1Deta =       TMath::Sqrt((WLZL1DR*WLZL1DR - WLZL1dphi*WLZL1dphi));
        WLZL2Deta =       TMath::Sqrt((WLZL2DR*WLZL2DR - WLZL2dphi*WLZL2dphi));
        WLep_bjetDeta =   TMath::Sqrt((WLep_bjetDR*WLep_bjetDR - LepbJetdphi*LepbJetdphi));
        ZLep1_bjetDeta =  TMath::Sqrt((ZLep1_bjetDR*ZLep1_bjetDR - ZLep1_bjetDphi*ZLep1_bjetDphi));
        ZLep2_bjetDeta =  TMath::Sqrt((ZLep2_bjetDR*ZLep2_bjetDR - ZLep2_bjetDphi*ZLep2_bjetDphi));
        WLep_cjetDeta =   TMath::Sqrt((WLep_cjetDR*WLep_cjetDR - WLep_cjetDphi*WLep_cjetDphi));
        ZLep1_cjetDeta =  TMath::Sqrt((ZLep1_cjetDR*ZLep1_cjetDR - ZLep1_cjetDphi*ZLep1_cjetDphi));
        ZLep2_cjetDeta =  TMath::Sqrt((ZLep2_cjetDR*ZLep2_cjetDR - ZLep2_cjetDphi*ZLep2_cjetDphi));

        TopTop_deta =      TopDeta;
        Z_cjet_deta =      Z_cjetDeta;
        Z_bjet_deta =      Z_bjetDeta;
        W_cjet_deta =      W_cjetDeta;
        W_bjet_deta =      W_bjetDeta;
        ZLLpair_deta =     ZLLpairDeta;
        WLZL1_deta =       WLZL1Deta;
        WLZL2_deta =       WLZL2Deta;
        WLep_bjet_deta =   WLep_bjetDeta;
        ZLep1_bjet_deta =  ZLep1_bjetDeta;
        ZLep2_bjet_deta =  ZLep2_bjetDeta;
        WLep_cjet_deta =   WLep_cjetDeta;
        ZLep1_cjet_deta =  ZLep1_cjetDeta;
        ZLep2_cjet_deta =  ZLep2_cjetDeta;
        
        jet_mva_no = Jets_new_no;
        lep_mva_no = (new_e_no+new_mu_no);
        jet_mva_event_orignal_no = *Jets_Size;
        lep_mva_event_orignal_no = *Leptons_Size;
        MVAweight = Event_Weight*Btag_weight;
    //}}}

        mvaOutput = readerOCPE->EvaluateMVA("myOCPE");

         if((new_mu_no+new_e_no)==3){
            if(new_e_no==3){
                hist_mva_eee->Fill(mvaOutput, Event_Weight*Btag_weight);
                hist_evt_weightB->Fill(25, Event_Weight);
                hist_evt_weightA->Fill(25, Event_Weight*Btag_weight);
            }
            if((new_e_no==2) && new_mu_no==1){
                hist_mva_eem->Fill(mvaOutput, Event_Weight*Btag_weight);
                hist_evt_weightB->Fill(26, Event_Weight);
                hist_evt_weightA->Fill(26, Event_Weight*Btag_weight);
            }
            if((new_mu_no==2) && new_e_no==1){ 
                hist_mva_emm->Fill(mvaOutput, Event_Weight*Btag_weight);
                hist_evt_weightB->Fill(27, Event_Weight);
                hist_evt_weightA->Fill(27, Event_Weight*Btag_weight);
            }
            if(new_mu_no==3){
                hist_mva_mmm->Fill(mvaOutput, Event_Weight*Btag_weight);
                hist_evt_weightB->Fill(28, Event_Weight);
                hist_evt_weightA->Fill(28, Event_Weight*Btag_weight);
            }
        }
        
         for(int PDFid=0 ; PDFid<*LHESize ; PDFid++){
            double PDF_Unc = ((LHESystematicWeights[PDFid]-*LHENominalWeight)/(*LHENominalWeight))+1;
            hist_PDF_combined->Fill(PDFid, Event_Weight*PDF_Unc);
            if(new_e_no==3) hist_PDFun_eee->Fill(PDFid, Event_Weight*PDF_Unc);
            if((new_e_no==2) && (new_mu_no==1)) hist_PDFun_eem->Fill(PDFid, Event_Weight*PDF_Unc);
            if((new_e_no==1) && (new_mu_no==2)) hist_PDFun_emm->Fill(PDFid, Event_Weight*PDF_Unc);
            if(new_mu_no==3) hist_PDFun_mmm->Fill(PDFid, Event_Weight*PDF_Unc);
         }
         
         if((new_mu_no+new_e_no)==3 && (new_e_no>=2)){
            hist_evt_weightB->Fill(29, Event_Weight);
            hist_evt_weightA->Fill(29, Event_Weight*Btag_weight);
            hist_CJetBoost_E_DE->Fill(CJetBoost_E, Event_Weight*Btag_weight);
            hist_BJetBoost_E_DE->Fill(BJetBoost_E, Event_Weight*Btag_weight);
            hist_TopTop_dphi_DE->Fill(TopTop_dphi, Event_Weight*Btag_weight);
            hist_Z_cjet_dphi_DE->Fill(Z_cjet_dphi, Event_Weight*Btag_weight);
            hist_Z_bjet_dphi_DE->Fill(Z_bjet_dphi, Event_Weight*Btag_weight);
            hist_W_cjet_dphi_DE->Fill(W_cjet_dphi, Event_Weight*Btag_weight);
            hist_W_bjet_dphi_DE->Fill(W_bjet_dphi, Event_Weight*Btag_weight);
            hist_ZLLpair_dphi_DE->Fill(ZLLpair_dphi, Event_Weight*Btag_weight);
            hist_WLZL1_dphi_DE->Fill(WLZL1_dphi, Event_Weight*Btag_weight);
            hist_WLZL2_dphi_DE->Fill(WLZL2_dphi, Event_Weight*Btag_weight);
            hist_WLep_bjet_dphi_DE->Fill(WLep_bjet_dphi, Event_Weight*Btag_weight);
            hist_ZLep1_bjet_dphi_DE->Fill(ZLep1_bjet_dphi, Event_Weight*Btag_weight);
            hist_ZLep2_bjet_dphi_DE->Fill(ZLep2_bjet_dphi, Event_Weight*Btag_weight);
            hist_WLep_cjet_dphi_DE->Fill(WLep_cjet_dphi, Event_Weight*Btag_weight);
            hist_ZLep1_cjet_dphi_DE->Fill(ZLep1_cjet_dphi, Event_Weight*Btag_weight);
            hist_ZLep2_cjet_dphi_DE->Fill(ZLep2_cjet_dphi, Event_Weight*Btag_weight);
            hist_BJet_btag_DE->Fill(BJet_btag, Event_Weight*Btag_weight);
            hist_CJet_btag_DE->Fill(CJet_btag, Event_Weight*Btag_weight);
            hist_TopTop_deta_DE->Fill(TopTop_deta, Event_Weight*Btag_weight);
            hist_Z_cjet_deta_DE->Fill(Z_cjet_deta, Event_Weight*Btag_weight);
            hist_Z_bjet_deta_DE->Fill(Z_bjet_deta, Event_Weight*Btag_weight);
            hist_W_bjet_deta_DE->Fill(W_bjet_deta, Event_Weight*Btag_weight);
            hist_W_cjet_deta_DE->Fill(W_cjet_deta, Event_Weight*Btag_weight);
            hist_ZLLpair_deta_DE->Fill(ZLLpair_deta, Event_Weight*Btag_weight);
            hist_WLZL1_deta_DE->Fill(WLZL1_deta, Event_Weight*Btag_weight);
            hist_WLZL2_deta_DE->Fill(WLZL2_deta, Event_Weight*Btag_weight);
            hist_WLep_bjet_deta_DE->Fill(WLep_bjet_deta, Event_Weight*Btag_weight);
            hist_ZLep1_bjet_deta_DE->Fill(ZLep1_bjet_deta, Event_Weight*Btag_weight);
            hist_ZLep2_bjet_deta_DE->Fill(ZLep2_bjet_deta, Event_Weight*Btag_weight);
            hist_WLep_cjet_deta_DE->Fill(WLep_cjet_deta, Event_Weight*Btag_weight);
            hist_ZLep1_cjet_deta_DE->Fill(ZLep2_cjet_deta, Event_Weight*Btag_weight);
            hist_ZLep2_cjet_deta_DE->Fill(ZLep2_cjet_deta, Event_Weight*Btag_weight);
        }
        if((new_mu_no+new_e_no)==3 && (new_mu_no>=2)){
            hist_evt_weightB->Fill(30, Event_Weight);
            hist_evt_weightA->Fill(30, Event_Weight*Btag_weight);
            hist_CJetBoost_E_DM->Fill(CJetBoost_E, Event_Weight*Btag_weight);
            hist_BJetBoost_E_DM->Fill(BJetBoost_E, Event_Weight*Btag_weight);
            hist_TopTop_dphi_DM->Fill(TopTop_dphi, Event_Weight*Btag_weight);
            hist_Z_cjet_dphi_DM->Fill(Z_cjet_dphi, Event_Weight*Btag_weight);
            hist_Z_bjet_dphi_DM->Fill(Z_bjet_dphi, Event_Weight*Btag_weight);
            hist_W_cjet_dphi_DM->Fill(W_cjet_dphi, Event_Weight*Btag_weight);
            hist_W_bjet_dphi_DM->Fill(W_bjet_dphi, Event_Weight*Btag_weight);
            hist_ZLLpair_dphi_DM->Fill(ZLLpair_dphi, Event_Weight*Btag_weight);
            hist_WLZL1_dphi_DM->Fill(WLZL1_dphi, Event_Weight*Btag_weight);
            hist_WLZL2_dphi_DM->Fill(WLZL2_dphi, Event_Weight*Btag_weight);
            hist_WLep_bjet_dphi_DM->Fill(WLep_bjet_dphi, Event_Weight*Btag_weight);
            hist_ZLep1_bjet_dphi_DM->Fill(ZLep1_bjet_dphi, Event_Weight*Btag_weight);
            hist_ZLep2_bjet_dphi_DM->Fill(ZLep2_bjet_dphi, Event_Weight*Btag_weight);
            hist_WLep_cjet_dphi_DM->Fill(WLep_cjet_dphi, Event_Weight*Btag_weight);
            hist_ZLep1_cjet_dphi_DM->Fill(ZLep1_cjet_dphi, Event_Weight*Btag_weight);
            hist_ZLep2_cjet_dphi_DM->Fill(ZLep2_cjet_dphi, Event_Weight*Btag_weight);
            hist_BJet_btag_DM->Fill(BJet_btag, Event_Weight*Btag_weight);
            hist_CJet_btag_DM->Fill(CJet_btag, Event_Weight*Btag_weight);
            hist_TopTop_deta_DM->Fill(TopTop_deta, Event_Weight*Btag_weight);
            hist_Z_cjet_deta_DM->Fill(Z_cjet_deta, Event_Weight*Btag_weight);
            hist_Z_bjet_deta_DM->Fill(Z_bjet_deta, Event_Weight*Btag_weight);
            hist_W_bjet_deta_DM->Fill(W_bjet_deta, Event_Weight*Btag_weight);
            hist_W_cjet_deta_DM->Fill(W_cjet_deta, Event_Weight*Btag_weight);
            hist_ZLLpair_deta_DM->Fill(ZLLpair_deta, Event_Weight*Btag_weight);
            hist_WLZL1_deta_DM->Fill(WLZL1_deta, Event_Weight*Btag_weight);
            hist_WLZL2_deta_DM->Fill(WLZL2_deta, Event_Weight*Btag_weight);
            hist_WLep_bjet_deta_DM->Fill(WLep_bjet_deta, Event_Weight*Btag_weight);
            hist_ZLep1_bjet_deta_DM->Fill(ZLep1_bjet_deta, Event_Weight*Btag_weight);
            hist_ZLep2_bjet_deta_DM->Fill(ZLep2_bjet_deta, Event_Weight*Btag_weight);
            hist_WLep_cjet_deta_DM->Fill(WLep_cjet_deta, Event_Weight*Btag_weight);
            hist_ZLep1_cjet_deta_DM->Fill(ZLep2_cjet_deta, Event_Weight*Btag_weight);
            hist_ZLep2_cjet_deta_DM->Fill(ZLep2_cjet_deta, Event_Weight*Btag_weight);
        }
        
        if(TopInfo_M_bw >= 50 && TopInfo_M_bw <= 350 && 
           TopInfo_M_cz >= 50 && TopInfo_M_cz <= 350 ){//||
           //mvaOutput < -1    || mvaOutput > 1   ) continue;//|| 
           //CJetBoost_E < 0 || CJetBoost_E > 300) continue;
        
        if((new_mu_no+new_e_no)==3 && (new_e_no>=2)){
            hist_top_mt_bw_DE->Fill(TopInfo_Mt_bw, Event_Weight);
            hist_top_mt_cz_DE->Fill(TopInfo_Mt_cz, Event_Weight);
            hist_top_m_bw_DE->Fill(TopInfo_M_bw, Event_Weight);
            hist_top_m_cz_DE->Fill(TopInfo_M_cz, Event_Weight);
            hist_MVA_McZ_DE->Fill(mvaOutput, TopInfo_M_cz, Event_Weight);
            hist_MVA_MbW_DE->Fill(mvaOutput, TopInfo_M_bw, Event_Weight);
            hist_MbW_McZ_DE->Fill(TopInfo_M_bw, TopInfo_M_cz, Event_Weight);
            hist_mva_shape_DE_result->Fill(mvaOutput, Event_Weight);
            hist_mva_shape_DE_result_count->Fill(mvaOutput, Event_Weight);
            hist_top_m_bw_DE_csvSF->Fill(TopInfo_M_bw, Event_Weight*Btag_weight);
            hist_top_m_cz_DE_csvSF->Fill(TopInfo_M_cz, Event_Weight*Btag_weight);
            //3 dimension & look at BDT 
            if(TopInfo_M_bw>=125 && TopInfo_M_bw<=240 && TopInfo_M_cz>=140 && TopInfo_M_cz<=240){
                hist_mva_3D_DE->Fill(mvaOutput, Event_Weight);
            }
        }
        if((new_mu_no+new_e_no)==3 && (new_mu_no>=2)){
            hist_top_mt_bw_DM->Fill(TopInfo_Mt_bw, Event_Weight);
            hist_top_mt_cz_DM->Fill(TopInfo_Mt_cz, Event_Weight);
            hist_top_m_bw_DM->Fill(TopInfo_M_bw, Event_Weight);
            hist_top_m_cz_DM->Fill(TopInfo_M_cz, Event_Weight);
            hist_MVA_McZ_DM->Fill(mvaOutput, TopInfo_M_cz, Event_Weight);
            hist_MVA_MbW_DM->Fill(mvaOutput, TopInfo_M_bw, Event_Weight);
            hist_MbW_McZ_DM->Fill(TopInfo_M_bw, TopInfo_M_cz, Event_Weight);
            hist_mva_shape_DM_result->Fill(mvaOutput, Event_Weight);
            hist_mva_shape_DM_result_count->Fill(mvaOutput, Event_Weight); 
            hist_top_m_bw_DM_csvSF->Fill(TopInfo_M_bw, Event_Weight*Btag_weight);
            hist_top_m_cz_DM_csvSF->Fill(TopInfo_M_cz, Event_Weight*Btag_weight);
            //3 dimension & look at BDT
            if(TopInfo_M_bw>=125 && TopInfo_M_bw<=240 && TopInfo_M_cz>=140 && TopInfo_M_cz<=240){
                hist_mva_3D_DM->Fill(mvaOutput, Event_Weight);
            }
        }
        }
        hist_ERb->Fill(BJetBoost_E, Event_Weight);
        hist_ERc->Fill(CJetBoost_E, Event_Weight);
        
      
        m_top_comb++;
        if(*EvtInfo_McFlag > 0){ // MC events
      
          if(m_gen_top1_idx > 0 && m_gen_top2_idx > 0 &&
             m_gen_zee_idx > 0 && m_gen_wuu_idx > 0){
            
            if((fabs(Top_P4[0].DeltaR(GenParts_P4[m_gen_top1_idx])) < 0.4 &&
                fabs(Top_P4[1].DeltaR(GenParts_P4[m_gen_top2_idx])) < 0.4) ||
               (fabs(Top_P4[0].DeltaR(GenParts_P4[m_gen_top2_idx])) < 0.4 &&
                fabs(Top_P4[1].DeltaR(GenParts_P4[m_gen_top1_idx])) < 0.4)){
            if(fabs(Zee_P4[m_zee_idx].DeltaR(GenParts_P4[m_gen_zee_idx])) < 0.4 &&
                 fabs(Wuu_P4[m_wuu_idx].DeltaR(GenParts_P4[m_gen_wuu_idx])) < 0.4){
            //if(fabs(Zee_P4[iz_Mva].DeltaR(GenParts_P4[m_gen_zee_idx])) < 0.4 &&
                 //fabs(Wuu_P4[iw].DeltaR(GenParts_P4[m_gen_wuu_idx])) < 0.4){

      
                if(m_gen_jet1_idx > 0 && m_jet1_idx < 125 &&
                   m_gen_jet2_idx > 0 && m_jet2_idx < 125 &&
                   GenParts_P4[m_gen_jet1_idx].Pt() > 0.1 &&
                   GenParts_P4[m_gen_jet2_idx].Pt() > 0.1 &&
                   fabs(Jets_P4[m_jet1_idx].DeltaR(
                   //fabs(Jets_P4[ij1].DeltaR(
                                       GenParts_P4[m_gen_jet1_idx]))<0.5 &&
                   fabs(Jets_P4[m_jet2_idx].DeltaR(
                   //fabs(Jets_P4[ij2].DeltaR(
                                       GenParts_P4[m_gen_jet2_idx]))<0.5 &&
                   fabs(Jets_P4[m_jet1_idx].Rho() / 
                   //fabs(Jets_P4[ij1].Rho() / 
                        GenParts_P4[m_gen_jet1_idx].Rho()) > 0.5 &&
                   fabs(Jets_P4[m_jet1_idx].Rho() / 
                   //fabs(Jets_P4[ij1].Rho() / 
                        GenParts_P4[m_gen_jet1_idx].Rho()) < 2.0 &&
                   fabs(Jets_P4[m_jet2_idx].Rho() / 
                   //fabs(Jets_P4[ij2].Rho() / 
                        GenParts_P4[m_gen_jet2_idx].Rho()) > 0.5 &&
                   fabs(Jets_P4[m_jet2_idx].Rho() / 
                   //fabs(Jets_P4[ij2].Rho() / 
                        GenParts_P4[m_gen_jet2_idx].Rho()) < 2.0 ){
                  TopInfo_MCTruth += 1;
                  
                  mvaOCPEt = readerOCPE->EvaluateMVA("myOCPE");
                  mvaOCPE0t = fabs(TopTop_dphi);
                }
              }
            }
          }
        }
        if(mvaTree){
          mvaTree->Fill();
        }            
       //}//light jet for sorting
      //}// b jet for sorting
     //}// lepton for Sorting
     }// signal extraction 
    }// basic event selection

  hist_top_comb->Fill(m_top_comb, Event_Weight);

  if(m_top_comb > 0 ){
    if(*EvtInfo_McFlag > 0 && mvaOCPEt != -9999. &&
       m_gen_top1_idx > 0 && m_gen_top2_idx > 0 &&
       m_gen_zee_idx > 0 && m_gen_wuu_idx > 0 &&
       m_gen_jet1_idx > 0 && m_gen_jet2_idx > 0){
      if(mvaOCPEt == mvaOCPEmax){
        hist_top_corr->Fill(1., Event_Weight);
      }else{
        hist_top_corr->Fill(0., Event_Weight);
      }

      if(mvaOCPE0t == mvaOCPE0max){
        hist_top_corr0->Fill(1., Event_Weight);
      }else{
        hist_top_corr0->Fill(0., Event_Weight);
      }
    }

    if( m_wuu_idx >= 0 && m_zee_idx >= 0 && m_jet1_idx >= 0 && m_jet2_idx >= 0){
      Top_P4[126] = Wuu_P4[m_wuu_idx] + Jets_P4[m_jet1_idx]; // tree top side
      Top_P4[127] = Zee_P4[m_zee_idx] + Jets_P4[m_jet2_idx]; // fcnc top side
      
      hist_fit_m_bw->Fill(Top_P4[126].M(), Event_Weight);
      hist_fit_m_cz->Fill(Top_P4[127].M(), Event_Weight);
      
      hist_fit_nbjet->Fill(m_bjet_no, Event_Weight);
      hist_fit_ncbjet->Fill(m_cbjet_no, Event_Weight);

      if(fabs(Leptons_Type[Zee_lid1[m_zee_idx]]) == 11){
        hist_fit_m_zee->Fill(Zee_P4[m_zee_idx].M(), Event_Weight);
      }else{
        hist_fit_m_zmm->Fill(Zee_P4[m_zee_idx].M(), Event_Weight);
      }
      
      if(fabs(Leptons_Type[Wuu_lid[m_wuu_idx]]) == 11){
        hist_fit_m_wen->Fill(Wuu_P4[m_wuu_idx].M(), Event_Weight);
        hist_fit_mt_wen->Fill(Wuu_Mt[m_wuu_idx], Event_Weight);
      }else{
        hist_fit_m_wmn->Fill(Wuu_P4[m_wuu_idx].M(), Event_Weight);
        hist_fit_mt_wmn->Fill(Wuu_Mt[m_wuu_idx], Event_Weight);
      }
      
      m_ht = Leptons_P4[Zee_lid1[m_zee_idx]].Pt() +
        Leptons_P4[Zee_lid2[m_zee_idx]].Pt() +
        Leptons_P4[Wuu_lid[m_wuu_idx]].Pt() +
        Jets_P4[m_jet1_idx].Pt() + Jets_P4[m_jet2_idx].Pt() + *EvtInfo_MET;
    
    }

    hist_fit_ht->Fill(m_ht, Event_Weight);
    hist_fit_st->Fill(m_st, Event_Weight);
  }

}//for ReconTop7()

// Jet Energy Resolution
void MyTcZAna_2017_Central::InitJES(int i){
    double GenJetsEta = Jets_GenJetEta[i];
    double GenJetsPhi = Jets_GenJetPhi[i];
    double GenJetsPt  = Jets_GenJetPt[i];
    double JERScale   = Jets_JERScale[i];
    double JERPt      = Jets_JERPt[i];
    double JERScaleUp = Jets_JERScaleUp[i];
    double JERScaleDown = Jets_JERScaleDown[i];
    double JEC_Unc      = Jets_Unc[i];
    int    NCH          = Jets_NCH[i];
    double CEF          = Jets_CEF[i];
    double NHF          = Jets_NHF[i];
    double NEF          = Jets_NEF[i];
    double CHF          = Jets_CHF[i];
    int    JM           = Jets_JM[i];
    int    NNH          = Jets_NNH[i];
    double MUF          = Jets_MUF[i];
}
unsigned MyTcZAna_2017_Central::bitconv( const float &x ){
    const void* temp = &x;
    return *((const unsigned*)( temp ));
}

bool MyTcZAna_2017_Central::IsMathched( int i, double ptres ){
    double deta = Jets_Eta[i] - Jets_GenJetEta[i];
    double dphi = Phi_mpi_pi((double)(Jets_Phi[i] - Jets_GenJetPhi[i]));
    double delR = TMath::Sqrt( deta * deta + dphi * dphi );

    if( delR >= 0.4/2. ){
        return false;
    }
    if( fabs(Jets_Pt[i] - Jets_GenJetPt[i]) >= 3*ptres*Jets_Pt[i] ){
        return false;
    }
    return true;
}

double MyTcZAna_2017_Central::Phi_mpi_pi( double x ){
    double const kPI    = TMath::Pi();
    double const kTWOPI = 2. * kPI;
    while( x >= kPI ) x -= kTWOPI;
    while( x < -kPI ) x += kTWOPI;
    return x;
}

double MyTcZAna_2017_Central::MakeScaled( int i, double ressf ){
    const double newpt = std::max(0.0, Jets_GenJetPt[i]+ressf*(Jets_Pt[i]-Jets_GenJetPt[i]));
    const double scale = newpt/Jets_Pt[i];
    return scale;
}

double MyTcZAna_2017_Central::MakeSmeared( int i, double ressf , double ptres){
    const double width = ressf > 1 ? sqrt( ressf * ressf - 1 ) * ptres : 0;
    //std::default_random_engine gen( m_random_generator );
    std::normal_distribution<double> myrand( 0, width );
    //cout << "seed : " << myrand(m_random_generator) << endl;
    double scale =  1. + myrand( m_random_generator );
    if( scale <= 0 || ::isnan( scale ) ){
        return 1;
    }
    else {
        return scale;
    }
}

void MyTcZAna_2017_Central::JERCorr(int i){
    //JME::JetParameters jetparm;
    //jetparm.setJetPt( Jets_Pt[i] ).setJetEta( Jets_Eta[i] ).setRho( *EvtInfo_rhoIso );
    double scale = 1.0;
    double ressf = Jets_JERScale[i];
    double ptres = Jets_JERPt[i];
    //double ressf = (double)resolution->getScaleFactor(jetparm);
    //double ptres = (double)jetptres->getResolution(jetparm);
    if(IsMathched(i, ptres)){
        scale = MakeScaled(i, ressf);
    }
    else{
        scale = MakeSmeared(i, ressf, ptres);
    }
    
    Jets_P4[i]  *= scale;
    Jets_Pt[i]   = Jets_P4[i].Pt();
    Jets_Eta[i]  = Jets_P4[i].Eta();
    Jets_Phi[i]  = Jets_P4[i].Phi();
    Jets_Energy[i] = Jets_P4[i].E();
}

void MyTcZAna_2017_Central::JERUp(int i){
   //JME::JetParameters jetparm;
   //jetparm.setJetPt( Jets_Pt[i] ).setJetEta( Jets_Eta[i] ).setRho( *EvtInfo_rhoIso );
   double scale = 1.0;
    double ressf = Jets_JERScaleUp[i];
    double ptres = Jets_JERPt[i];
    //double ressf = (double)resolution->getScaleFactor(jetparm, Variation::UP);
    //double ptres = (double)jetptres->getResolution(jetparm);
    if(IsMathched(i, ptres)){
        scale = MakeScaled(i, ressf);
    }
    else{
        scale = MakeSmeared(i, ressf, ptres);
    }
    
    Jets_P4[i]  *= scale;
    Jets_Pt[i]   = Jets_P4[i].Pt();
    Jets_Eta[i]  = Jets_P4[i].Eta();
    Jets_Phi[i]  = Jets_P4[i].Phi();
    Jets_Energy[i] = Jets_P4[i].E();

}

void MyTcZAna_2017_Central::JERDn(int i){
   //JME::JetParameters jetparm;
   //jetparm.setJetPt( Jets_Pt[i] ).setJetEta( Jets_Eta[i] ).setRho( *EvtInfo_rhoIso );
   double scale = 1.0;
    double ressf = Jets_JERScaleDown[i];
    double ptres = Jets_JERPt[i];
    //double ressf = (double)resolution->getScaleFactor(jetparm, Variation::DOWN);
    //double ptres = (double)jetptres->getResolution(jetparm);
    if(IsMathched(i, ptres)){
        scale = MakeScaled(i, ressf);
    }
    else{
       scale = MakeSmeared(i, ressf, ptres);
    }
    
    Jets_P4[i]  *= scale;
    Jets_Pt[i]   = Jets_P4[i].Pt();
    Jets_Eta[i]  = Jets_P4[i].Eta();
    Jets_Phi[i]  = Jets_P4[i].Phi();
    Jets_Energy[i] = Jets_P4[i].E();
}

void MyTcZAna_2017_Central::JECDn(int i){
    Jets_P4[i]  *= (1-Jets_Unc[i]);
    Jets_Pt[i]   = Jets_P4[i].Pt();
    Jets_Eta[i]  = Jets_P4[i].Eta();
    Jets_Phi[i]  = Jets_P4[i].Phi();
    Jets_Energy[i] = Jets_P4[i].E();
}
void MyTcZAna_2017_Central::JECUp(int i){
    Jets_P4[i]  *= (1+Jets_Unc[i]);
    Jets_Pt[i]   = Jets_P4[i].Pt();
    Jets_Eta[i]  = Jets_P4[i].Eta();
    Jets_Phi[i]  = Jets_P4[i].Phi();
    Jets_Energy[i] = Jets_P4[i].E();
}

void MyTcZAna_2017_Central::ElecEnergyCorr(int i){
    Leptons_P4[i] *= Leptons_ElEnergyCorrFactor[i];
    Leptons_Energy[i] = Leptons_P4[i].Energy();
    Leptons_Pt[i] = Leptons_P4[i].Pt();
    Leptons_Eta[i] = Leptons_P4[i].Eta();
    Leptons_Phi[i] = Leptons_P4[i].Phi();
    Leptons_Px[i] = Leptons_P4[i].Px();
    Leptons_Py[i] = Leptons_P4[i].Py();
    Leptons_Pz[i] = Leptons_P4[i].Pz();
}

