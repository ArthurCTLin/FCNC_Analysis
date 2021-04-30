//
// Package:    MyFCNCkit
// Class:      MyFCNCkit
// 


// system include files
#include <memory>

#include <TROOT.h>
#include <TSystem.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>

#include "TH2F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TRandom.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Particle.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"

#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "DataFormats/Math/interface/angle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"


#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"


#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h" 

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Run.h"
// For JER
#include "FWCore/Framework/interface/ESHandle.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"

// For JEC
#include "JetMETCorrections/JetCorrector/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

//LHERunInfoProduct
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"

// PileupSummaryInfo
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"


//YH 2012-08-15
#include "DataFormats/EgammaReco/interface/SuperCluster.h"

#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"
//
// class declaration
//

#include "TopQuarkAnalysis/MyFCNCkit/interface/MyFCNCkit.h"

//
// constants, enums and typedefs
//

#define W_MASS          80.403
#define Z_MASS          91.1876
#define MUON_MASS       0.105658
#define ELECTRON_MASS   0.0005109989

using namespace edm;
using namespace reco;
using namespace std;
using namespace pat;
using namespace math;
using namespace ROOT;

//
// static data member definitions
//

// #define MAX_LEPTONS     128
// #define MAX_JETS        64
// #define MAX_GENPARTS    512

//
// constructors and destructor
//
MyFCNCkit::MyFCNCkit(const edm::ParameterSet& iConfig){

   edm::Service<TFileService> fs;
   TFileDirectory results = TFileDirectory( fs->mkdir("results") );

   MCflag               = iConfig.getUntrackedParameter<bool>("MCflag",true);
   muonlabel_           = iConfig.getParameter<InputTag>("muonlabel");  //"cleanPatMuons"
   eleclabel_           = iConfig.getParameter<InputTag>("eleclabel");  // "cleanPatElectrons"
   convlabel_           = iConfig.getParameter<InputTag>("convlabel");  // "Electron conversions"

   // 2016 EID by YC
   eleidvetolabel_      = iConfig.getParameter<string>("eleidveto");
   eleidlooselabel_     = iConfig.getParameter<string>("eleidloose"); // "Electron ID Map"
   eleidmediumlabel_    = iConfig.getParameter<string>("eleidmedium"); // "Electron ID Map"
   eleidtightlabel_     = iConfig.getParameter<string>("eleidtight"); // "Electron ID Map"

   pfjetlabel_          = iConfig.getParameter<InputTag>("pfjetlabel"); // "cleanPatJets"
   metlabel_            = iConfig.getParameter<InputTag>("metlabel");   //"patMETs"
   genlabel_            = iConfig.getParameter<InputTag>("genlabel");   // "genParticles"
   hltlabel_            = iConfig.getParameter<InputTag>("hltlabel");   // "TriggerResults::HLT"
   pathltlabel_         = iConfig.getParameter<InputTag>("pathltlabel"); // patTriggerEvent
   offlinePVlabel_      = iConfig.getParameter<InputTag>("offlinePVlabel"); //offlinePrimaryVertices
   offlineBSlabel_      = iConfig.getParameter<InputTag>("offlineBSlabel"); //offlineBeamSpot
   genevtlabel_         = iConfig.getParameter<InputTag>("genevtlabel"); //generator
   gtdigilabel_         = iConfig.getParameter<InputTag>("gtdigilabel"); //gtDigis
   puInfoLabel_         = iConfig.getParameter<InputTag>("puInfoLabel");
   rhoIsoLabel_         = iConfig.getParameter<InputTag>("rhoIsoInputLabel");
   
   mettriggersrc_       = iConfig.getParameter<InputTag>("mettriggersrc");
   lhelabel_            = iConfig.getParameter<InputTag>("lhesrc");
   lherunlabel_         = iConfig.getParameter<InputTag>("lherunsrc");
   prefwgtsrc_          = iConfig.getParameter<InputTag>("prefwgtsrc");
   prefwgtupsrc_        = iConfig.getParameter<InputTag>("prefwgtupsrc");
   prefwgtdownsrc_      = iConfig.getParameter<InputTag>("prefwgtdownsrc");
    


   VertexToken = consumes<reco::VertexCollection>(offlinePVlabel_);
   BeamSpotToken = consumes<reco::BeamSpot>(offlineBSlabel_);
   RhoIsoToken = consumes<double>(rhoIsoLabel_);
   PileupToken = consumes< std::vector< PileupSummaryInfo > >(puInfoLabel_);
   TigResultsToken = consumes<edm::TriggerResults>(hltlabel_);
   gtToken = consumes<L1GlobalTriggerReadoutRecord>(gtdigilabel_);

   GenEventInfoToken = consumes<GenEventInfoProduct>(genevtlabel_);
   GenToken = consumes<reco::GenParticleCollection>(genlabel_);

   JetToken = consumes<std::vector<pat::Jet> >(pfjetlabel_);
   METToken = consumes<std::vector<pat::MET> >(metlabel_);
   MuonToken = consumes<std::vector<pat::Muon> >(muonlabel_);
  
   // 2016 Electron by YC
   ElectronToken = mayConsume<edm::View<pat::Electron> >(eleclabel_);
   ConversionToken = mayConsume<reco::ConversionCollection> (convlabel_);
  
   EleId_vetomap =  (eleidvetolabel_);
   EleId_loosemap = (eleidlooselabel_);
   EleId_mediummap = (eleidmediumlabel_);
   EleId_tightmap = (eleidtightlabel_);

   mettriggertoken =  consumes<edm::TriggerResults>( mettriggersrc_ );
   lhetoken        =  consumes<LHEEventProduct>( lhelabel_ );
   lheruntoken     =  consumes<LHERunInfoProduct, edm::InRun>( lherunlabel_ );

   prefweighttoken =  consumes<double>( prefwgtsrc_ );
   prefweightuptoken = consumes<double>( prefwgtupsrc_ );
   prefweightdowntoken = consumes<double>( prefwgtdownsrc_ ); 
   
   m_use_conddb = iConfig.getUntrackedParameter<bool>("useCondDB", false);

   std::cout << "Hello world !\n";
   //now do what ever initialization is needed

}


MyFCNCkit::~MyFCNCkit()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MyFCNCkit::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

  GenParts.Size=0;
  Leptons.Size=0;
  Jets.Size=0;
  VtxInfo.Size=0;
  EvtInfo.nBooking=N_TRIGGER_BOOKINGS;


  bool isData = iEvent.isRealData();   // Add by Jacky
  
  edm::Handle<std::vector<pat::Muon> >         MuonHandle;
 
  // 2016 Electron by YC

  edm::Handle<edm::View<pat::Electron> >     ElectronHandle;
  edm::Handle<reco::ConversionCollection>      ConversionHandle;

  edm::Handle<std::vector<pat::MET> >          METHandle;
  //edm::Handle<std::vector<reco::PFMET> >          METHandle;
  edm::Handle<std::vector<pat::Jet> >          JetHandle;  //PFJets

  edm::Handle<reco::GenParticleCollection>     GenHandle;  
  edm::Handle<reco::VertexCollection>          VertexHandle;
  edm::Handle<reco::VertexCollection>          VertexHandleBS; //Dmitry
  edm::Handle<reco::VertexCollection>          VertexHandlePixel; //Dmitry

  edm::Handle<edm::TriggerResults>             _mettriggerhandle;

  edm::Handle<double> rhoIsoHandle;
  edm::Handle<LHEEventProduct> _lhehandle;
  edm::Handle<LHERunInfoProduct> _runinfohandle;

  edm::Handle<double> _prefweighthandle;
  edm::Handle<double> _prefweightuphandle;
  edm::Handle<double> _prefweightdownhandle;
  
  iEvent.getByLabel( muonlabel_,   MuonHandle);
  iEvent.getByLabel( eleclabel_,   ElectronHandle);

  iEvent.getByToken(ConversionToken, ConversionHandle);

  iEvent.getByLabel( pfjetlabel_,  JetHandle);  //PFJets
  iEvent.getByLabel( metlabel_,    METHandle);
  
  iEvent.getByLabel( rhoIsoLabel_, rhoIsoHandle); // for Iso PU corr

  iEvent.getByToken( mettriggertoken,  _mettriggerhandle );
  iEvent.getByToken( lhetoken,      _lhehandle        );
  
  iEvent.getByToken( prefweighttoken, _prefweighthandle );
  iEvent.getByToken( prefweightuptoken, _prefweightuphandle );
  iEvent.getByToken( prefweightdowntoken, _prefweightdownhandle );
  

  
  if(!isData) iEvent.getByLabel( genlabel_, GenHandle);

  iEvent.getByLabel( offlinePVlabel_, VertexHandle); 

  edm::Handle< pat::TriggerEvent > triggerEvent;
  iEvent.getByLabel( pathltlabel_, triggerEvent );
  const pat::helper::TriggerMatchHelper matchHelper;
  
  // Prim. vertex
  memset(&VtxInfo,0x00,sizeof(VtxInfo));
  
  const vector<reco::Vertex> Vertices = *VertexHandle;
  double PV_Pt_Max = -100.;
  double Signal_Vz = 0.;
  
  reco::Vertex PrimVtx;
  if( !VertexHandle.failedToGet() && VertexHandle->size() > 0 ) {
    for(vector<reco::Vertex>::const_iterator it_vtx = Vertices.begin();
        it_vtx != Vertices.end(); it_vtx++ ) {
      if (VtxInfo.Size>=MAX_VERTEX) {
        cout << "PV " << VtxInfo.Size << endl;
        fprintf(stderr,"ERROR: number of  Tracks exceeds the size of array.\n");
        break;//exit(0);
      }
      VtxInfo.Type[VtxInfo.Size] = 0; //Vertices WITHOUT the Beam Spot constraint
      VtxInfo.isValid[VtxInfo.Size] = it_vtx->isValid();
      VtxInfo.isFake[VtxInfo.Size] = it_vtx->isFake(); 
      VtxInfo.Ndof[VtxInfo.Size] = it_vtx->ndof();
      VtxInfo.NormalizedChi2[VtxInfo.Size] = it_vtx->normalizedChi2();
      VtxInfo.vx[VtxInfo.Size] = it_vtx->x();
      VtxInfo.vy[VtxInfo.Size] = it_vtx->y();
      VtxInfo.vz[VtxInfo.Size] = it_vtx->z();
      VtxInfo.Rho[VtxInfo.Size] = it_vtx->position().Rho();
      VtxInfo.Pt_Sum[VtxInfo.Size] = 0.;
      VtxInfo.Pt_Sum2[VtxInfo.Size] = 0.;

      for(reco::Vertex::trackRef_iterator it = it_vtx->tracks_begin();
          it != it_vtx->tracks_end(); it++){
        VtxInfo.Pt_Sum[VtxInfo.Size] += (*it)->pt();
        VtxInfo.Pt_Sum2[VtxInfo.Size] += ( ( *it )->pt() * ( *it )->pt() );
      }
      if( VtxInfo.Pt_Sum[VtxInfo.Size] > PV_Pt_Max ){
        PV_Pt_Max = VtxInfo.Pt_Sum[VtxInfo.Size];
        PrimVtx = *it_vtx;
        VtxInfo.Index[VtxInfo.Size] = VtxInfo.Size;
      }
      
      VtxInfo.Size++;
    }
  }
  
  Signal_Vz=PrimVtx.z();
   

  // Get Beam Spot 
  reco::BeamSpot beamSpot;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByLabel( offlineBSlabel_, beamSpotHandle);
  
  if ( beamSpotHandle.isValid() )
    {
      beamSpot = *beamSpotHandle;
      
    } else
    {
      edm::LogInfo("MyAnalyzer")
        << "No beam spot available from EventSetup \n";
    }
  
  
  //Leptons
  
  memset(&Leptons,0x00,sizeof(Leptons));
  //Muons
  for(std::vector<pat::Muon>::const_iterator it_mu = MuonHandle->begin(); 
      it_mu != MuonHandle->end(); it_mu++ ) {
    
    if(Leptons.Size>=MAX_LEPTONS) {
      std::cerr <<"ERROR: number of leptons exceeds the size of array.\n";
      break;//exit(0);
    }
    
    Leptons.Index   [Leptons.Size] = Leptons.Size;
    Leptons.Type    [Leptons.Size] = 13;
    Leptons.Charge  [Leptons.Size] = it_mu->charge();
    Leptons.Pt      [Leptons.Size] = it_mu->pt();
    Leptons.Eta     [Leptons.Size] = it_mu->eta();
    Leptons.Phi     [Leptons.Size] = it_mu->phi();

    
    Leptons.Px      [Leptons.Size] = it_mu->px(); //Uly 2011-04-04
    Leptons.Py      [Leptons.Size] = it_mu->py(); //Uly 2011-04-04
    Leptons.Pz      [Leptons.Size] = it_mu->pz(); //Uly 2011-04-04
    Leptons.Energy  [Leptons.Size] = it_mu->energy(); //Uly 2011-04-04
    Leptons.isPFMuon[Leptons.Size] = it_mu->isPFMuon(); //CT 2018-08-09

    Leptons.MuIDGlobalMuonPromptTight[Leptons.Size] = it_mu->muonID("GlobalMuonPromptTight");

    if ((it_mu->type() & 0x02) || (it_mu->type() & 0x04)){ 
      Leptons.MuInnerTrackDz      [Leptons.Size] = it_mu->innerTrack()->dz(); 
      Leptons.MuInnerTrackDz_PV   [Leptons.Size] = it_mu->innerTrack()->dz(PrimVtx.position()); 
      Leptons.MuInnerTrackD0      [Leptons.Size] = it_mu->innerTrack()->d0(); 
      Leptons.MuInnerTrackDxy_BS  [Leptons.Size] = it_mu->innerTrack()->dxy(beamSpot.position()); 
      Leptons.MuInnerTrackDxy_PV  [Leptons.Size] = it_mu->innerTrack()->dxy(PrimVtx.position()); 

      bool hasPV = !VertexHandle->empty();
      float max_value = numeric_limits<float>::max();

      Leptons.MuInnerTrackDxy_PV_bpk  [Leptons.Size] = hasPV ? it_mu->innerTrack()->dxy( VertexHandle->front().position() ) : max_value;  //The way bprimeKit call Dz , CT2018-08-16
      Leptons.MuInnerTrackDz_PV_bpk   [Leptons.Size] = hasPV ? it_mu->innerTrack()->dz( VertexHandle->front().position() ) : max_value;   //The way bprimeKit call Dxy, CT2018-08-16
       
      Leptons.MuInnerTrackNHits   [Leptons.Size] = it_mu->innerTrack()->numberOfValidHits(); 
      Leptons.MuNTrackerHits      [Leptons.Size] = it_mu->innerTrack()->hitPattern().numberOfValidTrackerHits(); 
      Leptons.MuNPixelLayers      [Leptons.Size] = it_mu->innerTrack()->hitPattern().numberOfValidPixelHits();
      Leptons.vertexZ             [Leptons.Size] = it_mu->vertex().z(); //Uly 2011-04-04
      Leptons.MuNPixelLayersWMeasurement[Leptons.Size] = it_mu->innerTrack()->hitPattern().pixelLayersWithMeasurement(); //Uly 2011-04-04
    }
    
    if (it_mu->type() & 0x02){
      Leptons.MuGlobalNormalizedChi2 [Leptons.Size] = it_mu->globalTrack()->normalizedChi2();
      Leptons.MuNMuonhits            [Leptons.Size] = it_mu->globalTrack()->hitPattern().numberOfValidMuonHits();
    }

      Leptons.MunumberOfMatchedStations[Leptons.Size]=it_mu->numberOfMatchedStations();//YH 2012-08-15 

    if ((it_mu->type() & 0x02) || (it_mu->type() & 0x04)){
      Leptons.MuTrackerLayersWithMeasurement[Leptons.Size]=it_mu->track()->hitPattern().trackerLayersWithMeasurement();//YH2012-08-15
    }
    
    
    Leptons.MuNChambers               [Leptons.Size] = it_mu->numberOfChambers(); 
    Leptons.MuNChambersMatchesSegment [Leptons.Size] = it_mu->numberOfMatches();  // At least 2 Chambers matched with segments

    //C.T. Lin 2019-05-02
    Leptons.MuonCutBasedMuIdLOOSE     [Leptons.Size] = it_mu->passed(reco::Muon::CutBasedIdLoose);
    Leptons.MuonCutBasedMuIdMEDIUM    [Leptons.Size] = it_mu->passed(reco::Muon::CutBasedIdMedium);
    Leptons.MuonCutBasedMuIdTIGHT     [Leptons.Size] = it_mu->passed(reco::Muon::CutBasedIdTight);
    Leptons.MuonCutBasedIdGlobalHighPt [Leptons.Size] = it_mu->passed(reco::Muon::CutBasedIdGlobalHighPt);
    Leptons.MuonCutBasedIdTrkHighPt    [Leptons.Size] = it_mu->passed(reco::Muon::CutBasedIdTrkHighPt);
    Leptons.isGoodMuonTMOneStationTight [Leptons.Size] = muon::isGoodMuon( *it_mu, muon::TMOneStationTight );
    Leptons.isGoodMuonGlobalMuonPromptTight [Leptons.Size] = muon::isGoodMuon( *it_mu, muon::GlobalMuonPromptTight );
    Leptons.MuType[Leptons.Size] = it_mu->type();
    
    // PF lepton isolation
    Leptons.chargedIso   [Leptons.Size] = it_mu->chargedHadronIso();
    Leptons.neutralIso   [Leptons.Size] = it_mu->neutralHadronIso();
    Leptons.photonIso    [Leptons.Size] = it_mu->photonIso();
    if (it_mu->isPFMuon() && it_mu->isPFIsolationValid()){
      Leptons.ChargedHadronIsoR04  [Leptons.Size] = it_mu->pfIsolationR04().sumChargedHadronPt;
      Leptons.NeutralHadronIsoR04  [Leptons.Size] = it_mu->pfIsolationR04().sumNeutralHadronEt;
      Leptons.PhotonIsoR04         [Leptons.Size] = it_mu->pfIsolationR04().sumPhotonEt;
      Leptons.sumPUPtR04           [Leptons.Size] = it_mu->pfIsolationR04().sumPUPt;
    } 
    
    Leptons.Size++;
    
  }
  
  //C.T. Lin 2019-05-02
  float AEff03 = 0.0;

  for (size_t it = 0; it < ElectronHandle->size(); ++it){
    const auto it_el = ElectronHandle->ptrAt(it);

    if (Leptons.Size>=MAX_LEPTONS){
      std::cerr << "ERROR: number of leptons exceeds the size of array.\n";
      break;//exit(0);
    }
    
    if(iEvent.isRealData()){
      AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, fabs(it_el->superCluster()->eta()), ElectronEffectiveArea::kEleEAData2012);
    }else{
      AEff03 = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, fabs(it_el->superCluster()->eta()), ElectronEffectiveArea::kEleEAFall11MC);
    }
    
    //std::cout << "AEff03: " << AEff03 << endl;     
    
    Leptons.Index          [Leptons.Size] = Leptons.Size;
    Leptons.isEcalDriven   [Leptons.Size] = it_el->ecalDrivenSeed();
    Leptons.isTrackerDriven[Leptons.Size] = it_el->trackerDrivenSeed();
    Leptons.Type           [Leptons.Size] = 11;
    Leptons.Charge         [Leptons.Size] = it_el->charge();
    Leptons.Pt             [Leptons.Size] = it_el->pt();
    Leptons.Et             [Leptons.Size] = it_el->et(); //Uly 2011-04-04

    Leptons.Eta            [Leptons.Size] = it_el->superCluster()->eta(); //Uly 2011-04-04
    //Leptons.Eta          [Leptons.Size] = it_el->eta();
    Leptons.caloEta        [Leptons.Size] = it_el->caloPosition().eta();
    Leptons.Phi            [Leptons.Size] = it_el->superCluster()->phi(); //Uly 2011-04-04
    
    Leptons.Px         [Leptons.Size] = it_el->px(); //Uly 2011-04-04
    Leptons.Py         [Leptons.Size] = it_el->py(); //Uly 2011-04-04
    Leptons.Pz         [Leptons.Size] = it_el->pz(); //Uly 2011-04-04
    Leptons.Energy     [Leptons.Size] = it_el->energy(); //Uly 2011-04-04
    
    Leptons.ElTrackD0      [Leptons.Size] = it_el->gsfTrack()->d0();
    Leptons.ElTrackDz_PV   [Leptons.Size] = it_el->gsfTrack()->dz(PrimVtx.position());
    Leptons.ElTrackDxy_BS  [Leptons.Size] = it_el->gsfTrack()->dxy(beamSpot.position());
    Leptons.ElTrackDxy_PV  [Leptons.Size] = it_el->gsfTrack()->dxy(PrimVtx.position());
     //     Leptons.ElTrackDxy_PVBS[Leptons.Size] = it_el->gsfTrack()->dxy(PrimVtx_BS.position());
    Leptons.vertexZ        [Leptons.Size] = it_el->vertex().z();//Uly 2011-04-04

    Leptons.TrackIso     [Leptons.Size] = it_el->dr03TkSumPt();
    Leptons.EcalIso      [Leptons.Size] = it_el->dr03EcalRecHitSumEt();
    Leptons.HcalIso      [Leptons.Size] = it_el->dr03HcalTowerSumEt();


    // // PF lepton isolation
    Leptons.chargedIso   [Leptons.Size] = it_el->chargedHadronIso();
    Leptons.neutralIso   [Leptons.Size] = it_el->neutralHadronIso();
    Leptons.photonIso    [Leptons.Size] = it_el->photonIso();

    // The actual cone size used for electron is R < 0.3, here is to save space
    Leptons.ChargedHadronIsoR04  [Leptons.Size] = it_el->pfIsolationVariables().sumChargedHadronPt;
    Leptons.NeutralHadronIsoR04  [Leptons.Size] = it_el->pfIsolationVariables().sumNeutralHadronEt;
    Leptons.PhotonIsoR04         [Leptons.Size] = it_el->pfIsolationVariables().sumPhotonEt;
    Leptons.sumPUPtR04           [Leptons.Size] = it_el->pfIsolationVariables().sumPUPt;

    Leptons.puChIso[Leptons.Size] = it_el->puChargedHadronIso();
    Leptons.AllIso[Leptons.Size] = it_el->particleIso();

    Leptons.AEff03[Leptons.Size] = AEff03;

  
    Leptons.eidVetoMC[Leptons.Size] = (int) it_el->electronID( EleId_vetomap );
    Leptons.eidLooseMC[Leptons.Size] = (int) it_el->electronID( EleId_loosemap );
    Leptons.eidMediumMC[Leptons.Size] = (int) it_el->electronID( EleId_mediummap );
    Leptons.eidTightMC[Leptons.Size] = (int) it_el->electronID( EleId_tightmap );


    if ( it_el->hasUserFloat("ecalTrkEnergyPostCorr") ){
        Leptons.ElEnergyCorrFactor          [Leptons.Size] = it_el->userFloat("ecalTrkEnergyPostCorr") / it_el->energy();
        Leptons.ElEnergyPreCorrErr          [Leptons.Size] = it_el->userFloat("ecalTrkEnergyErrPreCorr");
        Leptons.ElEnergyPostCorrErr         [Leptons.Size] = it_el->userFloat("ecalTrkEnergyErrPostCorr"); 
        Leptons.ElEnergyPostCorrScaleUp     [Leptons.Size] = it_el->userFloat("energyScaleUp");
        Leptons.ElEnergyPostCorrScaleDown   [Leptons.Size] = it_el->userFloat("energyScaleDown");
        Leptons.ElEnergyPostCorrSmearUp     [Leptons.Size] = it_el->userFloat("energySigmaUp");
        Leptons.ElEnergyPostCorrSmearDown   [Leptons.Size] = it_el->userFloat("energySigmaDown");
    }
 
    float dist_ = (it_el->convDist() == -9999.? 9999:it_el->convDist());
    float dcot_ = (it_el->convDcot() == -9999.? 9999:it_el->convDcot());
    Leptons.dcotdist[Leptons.Size] =((0.04 - std::max(fabs(dist_), fabs(dcot_))) > 0?(0.04 - std::max(fabs(dist_), fabs(dcot_))):0);
    Leptons.ElseedEoverP[Leptons.Size] = it_el->eSeedClusterOverP();
    Leptons.ElHcalIso04[Leptons.Size]  = it_el->dr04HcalTowerSumEt();
    Leptons.ElEcalIso04[Leptons.Size]  = it_el->dr04EcalRecHitSumEt();
    
    Leptons.ElepassConversionVeto  [Leptons.Size]  = !ConversionTools::hasMatchedConversion(*it_el, 
                                                                                            ConversionHandle,
                                                                                            beamSpot.position());
    Leptons.ElesuperClusterEta     [Leptons.Size]  = it_el->superCluster()->eta();
    
    Leptons.full5x5_sigmaIetaIeta  [Leptons.Size]  = it_el->full5x5_sigmaIetaIeta();
    Leptons.dEtaInSeed             [Leptons.Size]  = it_el->deltaEtaSeedClusterTrackAtVtx();
    Leptons.NumberOfExpectedInnerHits [Leptons.Size]  = it_el->gsfTrack()->hitPattern().numberOfAllHits(reco::HitPattern::MISSING_INNER_HITS);
    
    const ElectronEffectiveArea::ElectronEffectiveAreaTarget EATarget = iEvent.isRealData() ?  ElectronEffectiveArea::kEleEAData2012 : ElectronEffectiveArea::kEleEAFall11MC;
    const double rhoPrime = max( *rhoIsoHandle, 0.0 );
    const double AEffR03  = ElectronEffectiveArea::GetElectronEffectiveArea(ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03, Leptons.Eta[Leptons.Size], EATarget );
    Leptons.IsoRhoCorrR03[Leptons.Size] = Leptons.ChargedHadronIsoR04[Leptons.Size] + max( (double)( Leptons.NeutralHadronIsoR04[Leptons.Size] + Leptons.PhotonIsoR04[Leptons.Size] - rhoPrime * AEffR03 ), 0.0 );
    
    Leptons.EletrackMomentumAtVtxp [Leptons.Size]  = it_el->trackMomentumAtVtx().R();
    Leptons.EleecalEnergy          [Leptons.Size]  = it_el->ecalEnergy();
    Leptons.EleeSuperClusterOverP  [Leptons.Size]  = it_el->eSuperClusterOverP();
    Leptons.Elefbrem               [Leptons.Size]  = it_el->fbrem();
    Leptons.EleHoverE              [Leptons.Size]  = it_el->hadronicOverEm();
    Leptons.ElesigmaIetaIeta       [Leptons.Size]  = it_el->sigmaIetaIeta();
    Leptons.EledeltaPhiVtx         [Leptons.Size]  = it_el->deltaPhiSuperClusterTrackAtVtx();
    Leptons.EledeltaEtaVtx         [Leptons.Size]  = it_el->deltaEtaSuperClusterTrackAtVtx();

    Leptons.Size++;
  }

   // *********************************************************************************
   // PFJets
   // *********************************************************************************

   memset(&Jets,0x00,sizeof(Jets));

   //Jet ID for PFJet
   edm::ParameterSet PS_pf;
   PS_pf.addParameter<std::string>("version", "FIRSTDATA");
   PS_pf.addParameter<std::string>("quality", "LOOSE");
   PFJetIDSelectionFunctor pfjetIDLOOSE(PS_pf);
   strbitset pfret = pfjetIDLOOSE.getBitTemplate();
    
   edm::ParameterSet PS_pf_tightID;
   PS_pf_tightID.addParameter<std::string>("version", "WINTER17");
   PS_pf_tightID.addParameter<std::string>("quality", "TIGHT");
   PFJetIDSelectionFunctor pfjetIDTIGHT(PS_pf_tightID);
   strbitset pfret_tight = pfjetIDTIGHT.getBitTemplate();
  
   edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
   iSetup.get<JetCorrectionsRecord>().get("AK4PFchs",JetCorParColl); 
   JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
   JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(JetCorPar);

   //20190214 add by C.T.
   const JME::JetResolution jetptres( JME::JetResolution::get(iSetup, "AK4PFchs_pt"));                        
   const JME::JetResolution jetphires( JME::JetResolution::get(iSetup, "AK4PFchs_phi"));
   const JME::JetResolutionScaleFactor jetressf( JME::JetResolutionScaleFactor::get( iSetup, "AK4PFchs" ) );

   for(std::vector<pat::Jet>::const_iterator it_jet = JetHandle->begin();
       it_jet != JetHandle->end(); it_jet++ ){ 
     if (Jets.Size>=MAX_JETS) {
       fprintf(stderr,"ERROR: number of jets exceeds the size of array.\n");
       break;//exit(0);
     }

     if (it_jet->pt()<=15.) continue; // IMPORTANT: Only book jet with pt>15 GeV. 

     Jets.Index       [Jets.Size] = Jets.Size;
     Jets.NTracks     [Jets.Size] = it_jet->associatedTracks().size();
     Jets.Eta         [Jets.Size] = it_jet->eta();
     
     Jets.Pt          [Jets.Size] = it_jet->pt();
     Jets.Et          [Jets.Size] = it_jet->et();
     

     jecUnc->setJetEta(it_jet->eta());
     jecUnc->setJetPt(it_jet->pt()); // here you must use the CORRECTED jet pt

     Jets.Unc[Jets.Size] = jecUnc->getUncertainty(true); //20190214 C.T.     
    
     JME::JetParameters jetparm;
     jetparm.setJetPt( it_jet->pt() ).setJetEta( it_jet->eta() ).setRho( *rhoIsoHandle );
     Jets.JERPt       [Jets.Size]   = jetptres.getResolution( jetparm );
     Jets.JERPhi      [Jets.Size]   = jetphires.getResolution( jetparm );
     Jets.JERScale    [Jets.Size]   = jetressf.getScaleFactor( jetparm );
     Jets.JERScaleUp  [Jets.Size]   = jetressf.getScaleFactor( jetparm, Variation::UP );
     Jets.JERScaleDown[Jets.Size]   = jetressf.getScaleFactor( jetparm, Variation::DOWN );

     Jets.Phi         [Jets.Size] = it_jet->phi();
     Jets.JetCharge   [Jets.Size] = it_jet->jetCharge();
     Jets.NConstituents[Jets.Size] = it_jet->numberOfDaughters();
     
     Jets.Px          [Jets.Size] = it_jet->px(); //Uly 2011-04-04
     Jets.Py          [Jets.Size] = it_jet->py(); //Uly 2011-04-04
     Jets.Pz          [Jets.Size] = it_jet->pz(); //Uly 2011-04-04
     Jets.Energy      [Jets.Size] = it_jet->energy(); //Uly 2011-04-04

     pfret.set(false);
     bool JetID = pfjetIDLOOSE(*it_jet, pfret);
     Jets.JetIDLOOSE[Jets.Size] = (JetID) ?  1 : 0;
     
     pfret_tight.set(false);
     bool JetID_tight = pfjetIDTIGHT(*it_jet, pfret_tight);
     Jets.JetIDTIGHT[Jets.Size] = (JetID_tight) ?  1 : 0;

     double tracks_x = 0.;
     double tracks_y = 0.;
     double tracks_x_tot = 0.;
     double tracks_y_tot = 0.;
          
     const reco::TrackRefVector& TrackCol = it_jet->associatedTracks();
     for (reco::TrackRefVector::const_iterator it = TrackCol.begin();
	  it != TrackCol.end (); it++){      
       tracks_x_tot += (*it)->px();
       tracks_y_tot += (*it)->py();     
       if (fabs((*it)->vz()-Signal_Vz) < 0.1){                
	 tracks_x += (*it)->px();
	 tracks_y += (*it)->py();            
       }
     }

      Jets.JVAlpha[Jets.Size] = sqrt(tracks_x*tracks_x+tracks_y*tracks_y)/it_jet->pt();
      if (tracks_x_tot!=0. || tracks_y_tot!=0.) 
      {
         Jets.JVBeta[Jets.Size] = sqrt(tracks_x*tracks_x+tracks_y*tracks_y)/sqrt(tracks_x_tot*tracks_x_tot+tracks_y_tot*tracks_y_tot);
      } else {
         Jets.JVBeta[Jets.Size] = -1.;
      }

      // Jet corrections, B-tagging, and Jet ID information
      // now we just fill everything (regardless of availability)
      Jets.PtCorrRaw   [Jets.Size] = it_jet->correctedJet("Uncorrected"       ).pt();
      Jets.PtCorrL2    [Jets.Size] = it_jet->correctedJet("L2Relative"        ).pt(); // L2(rel) 
      Jets.PtCorrL3    [Jets.Size] = it_jet->correctedJet("L3Absolute"        ).pt(); // L3(abs) 
      Jets.NCH         [Jets.Size] = it_jet->chargedMultiplicity();
      Jets.CEF         [Jets.Size] = it_jet->chargedEmEnergyFraction();
      Jets.NHF         [Jets.Size] = it_jet->neutralHadronEnergyFraction();
      Jets.NEF         [Jets.Size] = it_jet->neutralEmEnergyFraction();
      Jets.CHF         [Jets.Size] = it_jet->chargedHadronEnergyFraction();
      Jets.JM          [Jets.Size] = it_jet->chargedMultiplicity() + it_jet->neutralMultiplicity();
      Jets.NNH         [Jets.Size] = it_jet->neutralMultiplicity();
      Jets.MUF         [Jets.Size] = it_jet->muonEnergyFraction();

      Jets.CombinedIncSVBJetTags   [Jets.Size] = it_jet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
      Jets.CombinedSVMVAV2BJetTags [Jets.Size] = it_jet->bDiscriminator("pfCombinedMVAV2BJetTags");
      //Jets.CombinedSVSoftLBJetTags [Jets.Size] = it_jet->bDiscriminator("pfCombinedSecondaryVertexSoftLeptonBJetTags");
      //Jets.CombinedCvsLJetTags     [Jets.Size] = it_jet->bDiscriminator("pfCombinedCvsLJetTags");
      //Jets.CombinedCvsBJetTags     [Jets.Size] = it_jet->bDiscriminator("pfCombinedCvsBJetTags");
      Jets.DeepCSVJetTags_probb      [Jets.Size] = it_jet->bDiscriminator("pfDeepCSVJetTags:probb");
      Jets.DeepCSVJetTags_probbb     [Jets.Size] = it_jet->bDiscriminator("pfDeepCSVJetTags:probbb");
      Jets.DeepCSVJetTags_probc      [Jets.Size] = it_jet->bDiscriminator("pfDeepCSVJetTags:probc");
      Jets.DeepCSVJetTags_probudsg   [Jets.Size] = it_jet->bDiscriminator("pfDeepCSVJetTags:probudsg");
      Jets.DeepFlavourJetTags_probb  [Jets.Size] = it_jet->bDiscriminator("pfDeepFlavourJetTags:probb");
      Jets.DeepFlavourJetTags_probbb [Jets.Size] = it_jet->bDiscriminator("pfDeepFlavourJetTags:probbb");
      Jets.DeepFlavourJetTags_problepb [Jets.Size] = it_jet->bDiscriminator("pfDeepFlavourJetTags:problepb");
      Jets.DeepFlavourJetTags_probc  [Jets.Size] = it_jet->bDiscriminator("pfDeepFlavourJetTags:probc");
      Jets.DeepFlavourJetTags_probuds [Jets.Size] = it_jet->bDiscriminator("pfDeepFlavourJetTags:probuds");
      Jets.DeepFlavourJetTags_probg  [Jets.Size] = it_jet->bDiscriminator("pfDeepFlavourJetTags:probg");
      Jets.summaryDeepCSVJetTags_BvsAll [Jets.Size] = it_jet->bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll");
      Jets.summaryDeepCSVJetTags_CvsB   [Jets.Size] = it_jet->bDiscriminator("pfDeepCSVDiscriminatorsJetTags:CvsB");
      Jets.summaryDeepCSVJetTags_CvsL   [Jets.Size] = it_jet->bDiscriminator("pfDeepCSVDiscriminatorsJetTags:CvsL");

      if(!isData){
	const reco::GenJet * genjet = it_jet->genJet();
	if(genjet!=NULL) {
	  Jets.GenJetPt  [Jets.Size] = genjet->pt();
	  Jets.GenJetEta [Jets.Size] = genjet->eta();
	  Jets.GenJetPhi [Jets.Size] = genjet->phi();
	} 

	const reco::GenParticle* parton = it_jet->genParton();
	if(parton!=NULL){
	  Jets.GenPt     [Jets.Size] = parton->pt();
	  Jets.GenEta    [Jets.Size] = parton->eta();
	  Jets.GenPhi    [Jets.Size] = parton->phi();
	  Jets.GenPdgID  [Jets.Size] = parton->pdgId();
	  Jets.GenFlavor [Jets.Size] = it_jet->partonFlavour();
	  
	  //const reco::Candidate* genCand = parton;
	}
      } // no data

      //Jets.CandRef [Jets.Size] = (reco::Candidate*)&(*it_jet);
      Jets.Size++;
   }

   memset(&GenParts,0x00,sizeof(GenParts));
   memset(&EvtInfo,0x00,sizeof(EvtInfo));
      
   EvtInfo.RunNo  = iEvent.id().run();
   EvtInfo.EvtNo  = iEvent.id().event();
   EvtInfo.McFlag = iEvent.isRealData()? 0: 1;  
   EvtInfo.BxNo   = iEvent.bunchCrossing();
   EvtInfo.LumiNo = iEvent.luminosityBlock();

   EvtInfo.Orbit  = iEvent.orbitNumber();
   
   EvtInfo.rhoIso = *(rhoIsoHandle.product());

   EvtInfo.PrefiringWeight = (*_prefweighthandle);
   EvtInfo.PrefiringWeightUp = (*_prefweightuphandle);
   EvtInfo.PrefiringWeightDown = (*_prefweightdownhandle);

   // MC daughters: 0-1: hard jet from b'bar/t'bar, 2-9: W daughters, 10-13: Z daughters

   vector<const reco::Candidate *> cands;
   vector<const Candidate *>::const_iterator found = cands.begin();
   
   if(!isData){
     GenParts.Size=0;
     for( std::vector<reco::GenParticle>::const_iterator it_gen =
	    GenHandle->begin(); it_gen != GenHandle->end(); it_gen++ ){
       cands.push_back(&*it_gen);
     }

     // PileupSummaryInfo
     Handle<std::vector< PileupSummaryInfo > >  PUInfo;
     iEvent.getByLabel(puInfoLabel_, PUInfo);
     std::vector<PileupSummaryInfo>::const_iterator PVI;
     
     for(PVI = PUInfo->begin(); PVI != PUInfo->end(); ++PVI) {
       EvtInfo.nPU[EvtInfo.nBX] = PVI->getPU_NumInteractions();
       EvtInfo.nTPU[EvtInfo.nBX] = PVI->getTrueNumInteractions();
       EvtInfo.BXPU[EvtInfo.nBX] = PVI->getBunchCrossing();
       EvtInfo.nBX += 1;
     }
     
     for( std::vector<reco::GenParticle>::const_iterator it_gen =
            GenHandle->begin(); it_gen != GenHandle->end() &&
            GenParts.Size < MAX_GENPARTS; it_gen++ ){

	  if(GenParts.Size<60){
       // Particles Mothers and Daighters
       int iMo1 = -1;
       int iMo2 = -1;
       int iDa1 = -1;
       int iDa2 = -1;
       int NMo = it_gen->numberOfMothers();
       int NDa = it_gen->numberOfDaughters();
	 
       // if(it_gen->status() == 3){     //Book GenParts for DC table
         found = find(cands.begin(), cands.end(), it_gen->mother(0));
         if(found != cands.end()) iMo1 = found - cands.begin() ;
         if(iMo1>GenParts.Size) iMo1 = 0;
         
         found = find(cands.begin(), cands.end(), it_gen->mother(1));
         if(found != cands.end()) iMo2 = found - cands.begin() ;
	 
         found = find(cands.begin(), cands.end(), it_gen->daughter(0));
         if(found != cands.end()) iDa1 = found - cands.begin() ;
         
         found = find(cands.begin(), cands.end(), it_gen->daughter(1));
         if(found != cands.end()) iDa2 = found - cands.begin() ;
       // }
       //if((it_gen-GenHandle->begin())>=128 && it_gen->status()>=30)
       //  continue;

       GenParts.Index[GenParts.Size]         = it_gen - GenHandle->begin();
       GenParts.Pt[GenParts.Size]            = it_gen->pt();
       GenParts.Eta[GenParts.Size]           = it_gen->eta();
       GenParts.Phi[GenParts.Size]           = it_gen->phi();
       GenParts.Mass[GenParts.Size]          = it_gen->mass();
       GenParts.PdgID[GenParts.Size]         = it_gen->pdgId();
       GenParts.Status[GenParts.Size]        = it_gen->status();
       GenParts.Mo1[GenParts.Size]           = iMo1; 
       GenParts.Mo2[GenParts.Size]           = iMo2; 
       GenParts.Da1[GenParts.Size]           = iDa1; 
       GenParts.Da2[GenParts.Size]           = iDa2; 
       GenParts.nMo[GenParts.Size]           = NMo;
       GenParts.nDa[GenParts.Size]           = NDa; 
      
       GenParts.Size++;
     }
     }
     //std::cout << "Processing MC... " << GenParts.Size << std::endl;
   }  //not data

   for(std::vector<pat::MET>::const_iterator it_patmet =METHandle->begin();
   //for(std::vector<reco::PFMET>::const_iterator it_patmet =METHandle->begin();
       it_patmet != METHandle->end(); it_patmet++ ){
     
     EvtInfo.MET           = it_patmet->pt();
     EvtInfo.METPhi        = it_patmet->phi();
     // EvtInfo.RawMET        = it_patmet->uncorPt();
     // EvtInfo.RawMETPhi     = it_patmet->uncorPhi();
     
     EvtInfo.METx          = it_patmet->px(); //Uly 2011-04-04
     EvtInfo.METy          = it_patmet->py(); //Uly 2011-04-04
     
     EvtInfo.SumEt           = it_patmet->sumEt();
     EvtInfo.METSig        = it_patmet->mEtSig();
     

     // }
   } // MET

   edm::Handle<GenEventInfoProduct> GenEventInfoHandle;  
   bool with_GenEventInfo = iEvent.getByLabel(genevtlabel_,
					      GenEventInfoHandle);

   if(with_GenEventInfo && GenEventInfoHandle->hasPDF()) {
     EvtInfo.PDFid1   = GenEventInfoHandle->pdf()->id.first;
     EvtInfo.PDFid2   = GenEventInfoHandle->pdf()->id.second;
     EvtInfo.PDFx1    = GenEventInfoHandle->pdf()->x.first;
     EvtInfo.PDFx2    = GenEventInfoHandle->pdf()->x.second;
     EvtInfo.PDFscale = GenEventInfoHandle->pdf()->scalePDF;
     EvtInfo.PDFv1    = GenEventInfoHandle->pdf()->xPDF.first;
     EvtInfo.PDFv2    = GenEventInfoHandle->pdf()->xPDF.second;

   }

   //Add by C.T. 2019-02-15
   if(!isData){
     EvtInfo.Weight            = GenEventInfoHandle->weight();
     EvtInfo.ptHat             = GenEventInfoHandle->qScale();
     EvtInfo.LHENominalWeight  = _lhehandle->hepeup().XWGTUP;
     EvtInfo.LHEOriginalWeight = _lhehandle->originalXWGTUP();
     EvtInfo.LHESize           = std::min( MAX_LHE, (int)( _lhehandle->weights().size() ) );
     for( int i = 0; i < EvtInfo.LHESize; ++i ){
         EvtInfo.LHESystematicWeights[i] = _lhehandle->weights().at( i ).wgt;
         EvtInfo.LHESystematicId[i]      = std::stoi( _lhehandle->weights().at( i ).id.data() );
     }
   }


   // HLT: Booking trigger bits  
   edm::Handle<TriggerResults> TrgResultsHandle;
   bool with_TriggerResults = iEvent.getByLabel(hltlabel_,TrgResultsHandle);
   if (with_TriggerResults){
     const edm::TriggerNames & TrgNames =
       iEvent.triggerNames(*TrgResultsHandle);
     EvtInfo.TrgCount = 0;
     
     EvtInfo.nBooking=N_TRIGGER_BOOKINGS;
     EvtInfo.nHLT = TrgNames.size();
     for(int i=0; i<N_TRIGGER_BOOKINGS; i++) {
       unsigned int TrgIndex = TrgNames.triggerIndex( TriggerBooking[i] );
       
       if (TrgIndex == TrgNames.size()) {
	 EvtInfo.TrgBook[i] = -4; // The trigger path is not known in this event.
       }else if ( !TrgResultsHandle->wasrun( TrgIndex ) ) {
	 EvtInfo.TrgBook[i] = -3; // The trigger path was not included in this event.
       }else if ( !TrgResultsHandle->accept( TrgIndex ) ) {
	 EvtInfo.TrgBook[i] = -2; // The trigger path was not accepted in this event.
       }else if (  TrgResultsHandle->error ( TrgIndex ) ) {
	 EvtInfo.TrgBook[i] = -1; // The trigger path has an error in this event.
       }else {
	 EvtInfo.TrgBook[i] = +1; // It's triggered.
	 EvtInfo.TrgCount++; 
       }
     }  

     for(unsigned int i=0; i<TrgNames.size();i++){
       EvtInfo.HLTbits[i] = (TrgResultsHandle->accept(i) == true) ? 1:0;
       // Print out Trigger table
       //std::cout << "trigger path= " << TrgNames.triggerName(i) << std::endl;
     }
   }


   const edm::TriggerNames& mettriggername = iEvent.triggerNames( *_mettriggerhandle );
   auto checkMETfilter = [_mettriggerhandle ,mettriggername]( const std::string& triggername ){
        const unsigned index = mettriggername.triggerIndex( triggername );
        return _mettriggerhandle->accept( index ) && _mettriggerhandle->wasrun( index ) && !_mettriggerhandle->error( index );
   };
   
   EvtInfo.Flag_METFilter = ( 
                             checkMETfilter( "Flag_BadPFMuonFilter" ) &&
                             checkMETfilter( "Flag_HBHENoiseFilter" ) &&
                             checkMETfilter( "Flag_HBHENoiseIsoFilter" ) &&
                             checkMETfilter( "Flag_EcalDeadCellTriggerPrimitiveFilter" ) &&
                             checkMETfilter( "Flag_goodVertices" ) &&
                             checkMETfilter( "Flag_globalSuperTightHalo2016Filter" ) 
                            );
   if ( iEvent.isRealData() ) EvtInfo.Flag_METFilter = EvtInfo.Flag_METFilter && checkMETfilter( "Flag_eeBadScFilter" );

   myTree->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
MyFCNCkit::beginJob(){
  myTree = new TTree("root","My FCNC Top Tree");
  EvtInfo.setBranch(myTree);  
  GenParts.setBranch(myTree);  
  Leptons.setBranch(myTree);
  VtxInfo.setBranch(myTree);
  Jets.setBranch(myTree);

  RunTree = new TTree("run", "run");
  RunInfo.setBranch(RunTree);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyFCNCkit::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
MyFCNCkit::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
MyFCNCkit::endRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
  edm::Handle<LHERunInfoProduct> _runinfohandle;
  iRun.getByToken( lheruntoken, _runinfohandle );
  if(_runinfohandle.isValid() ){
      RunInfo.PdfID = _runinfohandle->heprup().PDFSUP.first;
  }
  else{
      cerr << "Invalid handle!" << endl;
  }
  RunTree->Fill();
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MyFCNCkit::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MyFCNCkit::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyFCNCkit::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
