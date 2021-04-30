#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#define TcZ 1905556
#define ttjets 156153276647.36 
#define t_s  36752348.43
#define t_t  5948313
#define t_tw  271208925.03 
#define tb_t 3675910
#define tb_tw 264516790.6
#define DY10to50  39481546
#define DY50  3684977929303.02  

#define ttwqq   560315.1342
#define ttwln   1711122.764
#define ttzqq   383062.0867
#define ttzll   1928279.476
#define wz2l2q  268351428.7
#define wz3ln   94563224.93
#define tZq     987413.0371
#define zz2l2n  5221275.944
#define zz2l2q  156516052.8
#define zz4l    9226778.404
#define ww2l2n  22155848.7
#define tthTobb 4189933.39
#define tthToNonbb 4464344.111

#define INT_LUM  41500 

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

void myTMVAClass( TString myMethodList = "" )
{
   // This loads the library
   TMVA::Tools::Instance();

   // to get access to the GUI and all tmva macros
   TString thisdir = gSystem->DirName(gInterpreter->GetCurrentMacroName());
   gROOT->SetMacroPath(thisdir + ":" + gROOT->GetMacroPath());
   gROOT->ProcessLine(".L TMVAGui.C");

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Cut optimisation
   Use["Cuts"]            = 0;
   Use["CutsD"]           = 0;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   // 
   // --- 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 1;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 0; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 0;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 0; // k-nearest neighbour method
   //
   // --- Linear Discriminant Analysis
   Use["LD"]              = 1; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 0; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
   //
   // --- Support Vector Machine 
   Use["SVM"]             = 0;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 1; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting 
   // 
   // --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 0;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;

   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "myTMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

    
    dataloader->AddVariable( "CJetBoost_E", 'F' );
    dataloader->AddVariable( "BJetBoost_E", 'F' );
    dataloader->AddVariable( "TopTop_dphi", 'F' );
    dataloader->AddVariable( "Z_cjet_dphi", 'F' );
    //dataloader->AddVariable( "Z_bjet_dphi", 'F' );
    //dataloader->AddVariable( "W_cjet_dphi", 'F' );
    dataloader->AddVariable( "W_bjet_dphi", 'F' );
   dataloader->AddVariable( "ZLLpair_dphi", 'F' );
   dataloader->AddVariable( "WLZL1_dphi", 'F' );
    dataloader->AddVariable( "WLZL2_dphi", 'F' );
    //dataloader->AddVariable( "WLep_bjet_dphi", 'F' );
    //dataloader->AddVariable( "ZLep1_bjet_dphi", 'F' );
    dataloader->AddVariable( "ZLep2_bjet_dphi", 'F' );
    dataloader->AddVariable( "WLep_cjet_dphi", 'F' );
    //dataloader->AddVariable( "ZLep1_cjet_dphi", 'F' );
    //dataloader->AddVariable( "ZLep2_cjet_dphi", 'F' );

    dataloader->AddVariable( "BJet_btag", 'F' );
    //dataloader->AddVariable( "BJet_ctag", 'F' );
    dataloader->AddVariable( "CJet_btag", 'F' );
    //dataloader->AddVariable( "CJet_ctag", 'F' );
    //dataloader->AddVariable( "TopTop_deta", 'F' );
    //dataloader->AddVariable( "Z_cjet_deta", 'F' );
    //dataloader->AddVariable( "Z_bjet_deta", 'F' );
    dataloader->AddVariable( "W_bjet_deta", 'F' );
    //dataloader->AddVariable( "W_cjet_deta", 'F' );
    dataloader->AddVariable( "ZLLpair_deta", 'F' );
    dataloader->AddVariable( "WLZL1_deta", 'F' );
    //dataloader->AddVariable( "WLZL2_deta", 'F' );
    //dataloader->AddVariable( "WLep_bjet_deta", 'F' );
    //dataloader->AddVariable( "ZLep1_bjet_deta", 'F' );
    //dataloader->AddVariable( "ZLep2_bjet_deta", 'F' );
    //dataloader->AddVariable( "WLep_cjet_deta", 'F' );
    dataloader->AddVariable( "ZLep1_cjet_deta", 'F' );
    //dataloader->AddVariable( "ZLep2_cjet_deta", 'F' );
   
    // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables
    //factory->AddSpectator( "spec1 := var1*2",  "Spectator 1", "units", 'F' );
    //factory->AddSpectator( "spec2 := var1*3",  "Spectator 2", "units", 'F' );
   dataloader->AddSpectator( "TopInfo_M_bw", "Spectator 1", "units", 'F' );
   dataloader->AddSpectator( "TopInfo_M_cz", "Spectator 2", "units", 'F' );

   // Read training and test data
   const int nfiles = 21;
   TFile *input_bkg[nfiles];
   TTree *backgroundT[nfiles];

   TString file_sig = "./sample/sigTT_kappa_zct_combined.root";
   TFile *input_sig = TFile::Open( file_sig );

   TString file_bkg[nfiles] = 
   {
       "./sample/bkg_TTJets_powheg.root",
       "./sample/bkg_ttHTobb.root",
       "./sample/bkg_ttHToNonbb.root",
       "./sample/bkg_TTWqq.root",
       "./sample/bkg_TTWln.root",
       "./sample/bkg_TTZqq.root",
       "./sample/bkg_TTZll.root",
       "./sample/bkg_WWTo2L2Nu.root",
       "./sample/bkg_WZTo2L2Q.root",
       "./sample/bkg_WZTo3LNu.root",
       "./sample/bkg_ZZTo2L2Nu.root",
       "./sample/bkg_ZZTo2L2Q.root",
       "./sample/bkg_ZZTo4L.root",
       "./sample/bkg_sT_s.root",
       "./sample/bkg_sT_t_top.root",
       "./sample/bkg_sT_tW_top_TuneCUETP8M1.root",
       "./sample/bkg_sT_t_antitop.root",
       "./sample/bkg_sT_tW_antitop_TuneCUETP8M1.root",
       "./sample/bkg_tZq.root",
       "./sample/bkg_DYJets_10to50.root",
       "./sample/bkg_DYJets_50.root"
   };

    for(int i=0 ; i<nfiles ; i++){
       input_bkg[i] = TFile::Open(file_bkg[i]);
       std::cout << "--- TMVAClassification       : Using input file: " << input_bkg[i]->GetName() << std::endl;
    }
   
    std::cout << "--- TMVAClassification       : Using input file: " << input_sig->GetName() << std::endl;
  
   
   TTree *signalT     = (TTree*)input_sig->Get("mvaTree;1");
   for(int i=0 ; i<nfiles ; i++){
        backgroundT[i] = (TTree*)input_bkg[i]->Get("mvaTree;1");
   }

   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 2*0.0005*831.76*0.10099*0.324 *INT_LUM/TcZ;
   Double_t backgroundWeight[nfiles] =
   {
    831.76  *INT_LUM/ttjets,  //ttjets
    0.2934  *INT_LUM/tthTobb,
    0.2151  *INT_LUM/tthToNonbb,
    0.4062  *INT_LUM/ttwqq,
    0.2043  *INT_LUM/ttwln,
    0.5297  *INT_LUM/ttzqq,
    0.2529  *INT_LUM/ttzll,
    10.48   *INT_LUM/ww2l2n,
    5.606   *INT_LUM/wz2l2q,
    5.052   *INT_LUM/wz3ln,
    0.564   *INT_LUM/zz2l2n,
    3.22    *INT_LUM/zz2l2q,
    1.325   *INT_LUM/zz4l,
    3.36    *INT_LUM/t_s,
    136.02  *INT_LUM/t_t,
    35.85   *INT_LUM/t_tw,
    80.95   *INT_LUM/tb_t,
    35.85   *INT_LUM/tb_tw,
    0.0758  *INT_LUM/tZq,
    18610   *INT_LUM/DY10to50,
    6529.0  *INT_LUM/DY50      
   };
   
   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree    ( signalT,     signalWeight     );
   for(int i=0 ; i<nfiles ; i++){
       if ( backgroundT[i]->GetEntries() == 0 ){
           cout << "File name: " << input_bkg[i]->GetName() << endl;
           continue;
       }
       dataloader->AddBackgroundTree( backgroundT[i], backgroundWeight[i] );
   }
   
   dataloader->SetSignalWeightExpression( "MVAweight" );
   dataloader->SetBackgroundWeightExpression( "MVAweight" );

   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycuts = "TopInfo_MCTruth==1"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = "MVAweight>0"; // for example: TCut mycutb = "abs(var1)<0.5";

   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

   // Cut optimisation
   if (Use["Cuts"])
      factory->BookMethod(dataloader, TMVA::Types::kCuts, "Cuts",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

   if (Use["CutsD"])
      factory->BookMethod(dataloader, TMVA::Types::kCuts, "CutsD",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

   if (Use["CutsPCA"])
      factory->BookMethod(dataloader, TMVA::Types::kCuts, "CutsPCA",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

   if (Use["CutsGA"])
      factory->BookMethod(dataloader, TMVA::Types::kCuts, "CutsGA",
                           "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   if (Use["CutsSA"])
      factory->BookMethod(dataloader, TMVA::Types::kCuts, "CutsSA",
                           "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   // Likelihood ("naive Bayes estimator")
   if (Use["Likelihood"])
      factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

   // Decorrelated likelihood
   if (Use["LikelihoodD"])
      factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "LikelihoodD",
                           "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );

   // PCA-transformed likelihood
   if (Use["LikelihoodPCA"])
      factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "LikelihoodPCA",
                           "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" ); 

   // Use a kernel density estimator to approximate the PDFs
   if (Use["LikelihoodKDE"])
      factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "LikelihoodKDE",
                           "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" ); 

   // Use a variable-dependent mix of splines and kernel density estimator
   if (Use["LikelihoodMIX"])
      factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "LikelihoodMIX",
                           "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" ); 

   // Test the multi-dimensional probability density estimator
   // here are the options strings for the MinMax and RMS methods, respectively:
   //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
   //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
   if (Use["PDERS"])
      factory->BookMethod(dataloader, TMVA::Types::kPDERS, "PDERS",
                           "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );

   if (Use["PDERSD"])
      factory->BookMethod(dataloader, TMVA::Types::kPDERS, "PDERSD",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );

   if (Use["PDERSPCA"])
      factory->BookMethod(dataloader, TMVA::Types::kPDERS, "PDERSPCA",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );

   // Multi-dimensional likelihood estimator using self-adapting phase-space binning
   if (Use["PDEFoam"])
      factory->BookMethod(dataloader, TMVA::Types::kPDEFoam, "PDEFoam",
                           "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );

   if (Use["PDEFoamBoost"])
      factory->BookMethod(dataloader, TMVA::Types::kPDEFoam, "PDEFoamBoost",
                           "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );

   // K-Nearest Neighbour classifier (KNN)
   if (Use["KNN"])
      factory->BookMethod(dataloader, TMVA::Types::kKNN, "KNN",
                           "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );

   // H-Matrix (chi2-squared) method
   if (Use["HMatrix"])
      factory->BookMethod(dataloader, TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );

   // Linear discriminant (same as Fisher discriminant)
   if (Use["LD"])
      factory->BookMethod(dataloader, TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher discriminant (same as LD)
   if (Use["Fisher"])
      factory->BookMethod(dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher with Gauss-transformed input variables
   if (Use["FisherG"])
      factory->BookMethod(dataloader, TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );

   // Composite classifier: ensemble (tree) of boosted Fisher classifiers
   if (Use["BoostedFisher"])
      factory->BookMethod(dataloader, TMVA::Types::kFisher, "BoostedFisher", 
                           "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );

   // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
   if (Use["FDA_MC"])
      factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_MC",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );

   if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_GA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" );

   if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_SA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   if (Use["FDA_MT"])
      factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_MT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );

   if (Use["FDA_GAMT"])
      factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_GAMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );

   if (Use["FDA_MCMT"])
      factory->BookMethod(dataloader, TMVA::Types::kFDA, "FDA_MCMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );

   // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
   if (Use["MLP"])
      factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

   if (Use["MLPBFGS"])
      factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );

   if (Use["MLPBNN"])
      factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=3000:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator:CreateMVAPdfs" ); // BFGS training with bayesian regulators

   // CF(Clermont-Ferrand)ANN
   if (Use["CFMlpANN"])
      factory->BookMethod(dataloader, TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...  

   // Tmlp(Root)ANN
   if (Use["TMlpANN"])
      factory->BookMethod(dataloader, TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...

   // Support Vector Machine
   if (Use["SVM"])
      factory->BookMethod(dataloader, TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );

   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=400:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=3:NegWeightTreatment=Pray" );

   if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=400:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20:CreateMVAPdfs:NegWeightTreatment=Pray" );

   if (Use["BDTB"]) // Bagging
      factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTB",
                           "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
      factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTD",
                           "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );

   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
      factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTMitFisher",
                           "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );

   // RuleFit -- TMVA implementation of Friedman's method
   if (Use["RuleFit"])
      factory->BookMethod(dataloader, TMVA::Types::kRuleFit, "RuleFit",
                           "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );

   // For an example of the category classifier usage, see: TMVAClassificationCategory

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events

   // ---- STILL EXPERIMENTAL and only implemented for BDT's ! 
   // factory->OptimizeAllMethods("SigEffAt001","Scan");
   // factory->OptimizeAllMethods("ROCIntegral","FitGA");

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can tell the factory to train, test, and evaluate the MVAs

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;

   // Launch the GUI for the root macros
   //if (!gROOT->IsBatch()) TMVAGui( outfileName );
   if (!gROOT->IsBatch())  gROOT->ProcessLine(".x TMVAGui.C(\"myTMVA.root\")");

}
