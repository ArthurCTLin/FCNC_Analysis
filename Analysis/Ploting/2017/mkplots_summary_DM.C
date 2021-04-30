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
#include "THStack.h"
#include "TLegend.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLatex.h"

#include "TH1F.h"
#include "TDirectory.h"
#include "TDirectoryFile.h"
#include "TArrow.h"
#include "TRef.h"
#include "TApplication.h"
#include "TError.h"
#include "TMath.h"
#include "TAxis.h"
#include "TStyle.h"
#include "TLine.h"
#include "TPad.h"
#include "TGraphErrors.h"
#include <vector>

// /* processed events
#define TcZ 1905556
#define TuZ 1754869
#define ttjets 156153276647.36 //13149645235
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

#define INT_LUM  41500 //36773.0

vector<TH1*>Final_mva_eee;
vector<TH1*>Final_mva_eem;
vector<TH1*>Final_mva_emm;
vector<TH1*>Final_mva_mmm;

vector<TH1*>Final_w_mt_eee;
vector<TH1*>Final_w_mt_eem;
vector<TH1*>Final_w_mt_emm;
vector<TH1*>Final_w_mt_mmm;

vector<TH1*>Final_Zmass_eee;
vector<TH1*>Final_Zmass_eem;
vector<TH1*>Final_Zmass_emm;
vector<TH1*>Final_Zmass_mmm;

vector<TH1*>Final_b_no_mmm;
vector<TH1*>Final_b_no_emm;
vector<TH1*>Final_b_no_eem;
vector<TH1*>Final_b_no_eee;

vector<TH1*>Final_evt_weightB;
vector<TH1*>Final_evt_weightA;

const int nFiles=23; //29; //matrix weight but number is 0 to 16

std::string Labels[nFiles]=
  {

                                  "t#rightarrowZq (B=0.12%)",       // T2ZQ
                                  
                                  "t#bar{t}Jets",       //ttjets
                                  "t#bar{t}H",          //tthiggs
                                  "t#bar{t}H",          //tthiggs
                                  "t#bar{t}W / t#bar{t}Z",                // ttwqq
                                  "t#bar{t}W / t#bar{t}Z",                //ttwln
                                  "t#bar{t}W / t#bar{t}Z",            // ttzqq
                                  "t#bar{t}W / t#bar{t}Z",            // ttzll
                                  //"WW/WZ/ZZ",        // wjets
                                  "WW",       //WWTo2L2Nu
                                  "WZ",       //WZTo2L2Q
                                  "WZ",       //WZTo3LNu
                                  "ZZ",       //ZZTo2L2Nu
                                  "ZZ",       //ZZTo2L2Q
                                  "ZZ",       //ZZTo4L
                                  "Single top",       // t_s
                                  "Single top",       // t_t
                                  "Single top",      // t_tw
                                  "Single top",      //tb_t
                                  "Single top",      //tb_tw
                                  "tZq",
                                  "DY/Z",
                                  "DY/Z",

                                  "Data"   // tb_tw
};

std::string histFiles[nFiles]=
  {
    "../Result_run_fcnc_files_total/2017/Zct/Central/sigTT_kappa_zct_combined.root",  //TTbar to bW & cZ kappa_zct (combined top and anti-quark)
    
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_TTJets_powheg.root",        //ttjets
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_ttHTobb.root",         //tthiggs
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_ttHToNonbb.root",         //tthiggs
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_TTWqq.root",      //ttwqq                                                      
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_TTWln.root",      //ttwln
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_TTZqq.root",      //ttzqq
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_TTZll.root",      //ttzll
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_WWTo2L2Nu.root",  //ww2l2n
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_WZTo2L2Q.root",   //wz2l2q
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_WZTo3LNu.root",   //wz3ln
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_ZZTo2L2Nu.root",  //zz2l2n
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_ZZTo2L2Q.root",   //zz2l2q
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_ZZTo4L.root",     //zz4l
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_sT_s.root",       //t_s
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_sT_t_top.root",       //t_t
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_sT_tW_top_TuneCUETP8M1.root",      //t_tw
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_sT_t_antitop.root",   //tb_t
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_sT_tW_antitop_TuneCUETP8M1.root",  //tb_tw
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_tZq.root",
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_DYJets_10to50.root",     //zjets(10-50)
    "../Result_run_fcnc_files_total/2017/Zct/Central/bkg_DYJets_50.root",         //zjets(50)

    "../Result_run_fcnc_files_total/2017/Zct/Central/data_double_mu_combined.root" //data
};

double hist_scale[nFiles-1] = 
  {
    2*0.0012*831.76*0.10099*0.324 *INT_LUM/TcZ,       // T2HC  0.10099 Z->ll; 0.324 W->lepton and tau; FCNC 0.1%
    //2*0.0012*831.76*0.10099*0.324 *INT_LUM/TuZ,       // T2HC  0.10099 Z->ll; 0.324 W->lepton and tau; FCNC 0.1%
    
    831.76          *INT_LUM/ttjets,    //ttjets
    0.2934          *INT_LUM/tthTobb,  //tthiggs
    0.2151          *INT_LUM/tthToNonbb,  //tthiggs
    0.4062          *INT_LUM/ttwqq,      // ttwjets 0.2148
    0.2043          *INT_LUM/ttwln,      // ttwjets 0.2148
    0.5297          *INT_LUM/ttzqq,      // ttzjets 0.172
    0.2529          *INT_LUM/ttzll,      // ttzjets 0.172
    10.48           *INT_LUM/ww2l2n,    //ww2l2n    (X-sec modification : 12.178->10.48)
    5.606           *INT_LUM/wz2l2q,    //wz2l2q    (X-sec modification : 5.595->5.606)
    5.052           *INT_LUM/wz3ln,      //wz3ln    (X-sec modification : 4.42965->4.679)
    0.564           *INT_LUM/zz2l2n,    //zz2l2n
    3.22            *INT_LUM/zz2l2q,    //zz2l2q
    1.325           *INT_LUM/zz4l,        //zz4l
    3.36            *INT_LUM/t_s,          // t_s   
    136.02          *INT_LUM/t_t,          // t_t   (X-sec modification : 44.33->136.02)
    35.85           *INT_LUM/t_tw,        // t_tw   
    80.95           *INT_LUM/tb_t,        //tb_t    (X-sec modification : 26.38->80.95)
    35.85           *INT_LUM/tb_tw,       //tb_tw
    0.0758          *INT_LUM/tZq,         //tZq
    18610           *INT_LUM/DY10to50,    //zjets(10-50)
    6529.0          *INT_LUM/DY50         //zjets(50)  //6025.2
};

double histMax[30];// = {30, };

int histColor[nFiles] = 
  {
    kWhite,     // T2CZ
    kRed+1,     // ttjets  kRed
    kRed-5,      // tthiggs
    kRed-5,      // tthiggs
    kAzure-7,   // ttwqq   kOrange-3
    kAzure-7,   // ttwln   kOrange-3 
    kAzure-7,   // ttzqq   kOrange-3 
    kAzure-7,   // ttzll   kOrange-3 
  //kAzure+8,   // wzjets     //new adding code
    kBlue-4,//kBlue-4,   // ww2l2n  kBlue-10
    kAzure+8,//kAzure+8,//kAzure+8,  //wz2l2q    kBlue-7
    kAzure+8,//kAzure+8, //kAzure+8,  //wz3ln     kBlue-7
    kAzure+4,//kAzure+4,  //zz2l2n    kBlue
    kAzure+4,//kAzure+4,  //zz2l2q    kBlue
    kAzure+4,//kAzure+4,  //zz4l      kBlue
    kMagenta, // t_s
    kMagenta, // t_t
    kMagenta,   // t_tw
    kMagenta, //tb_t
    kMagenta, //tb_tw
    kMagenta+2, //tZq
    kAzure-2,   //zjets(10-50) kGreen+2
    kAzure-2,   //zjets(50)    kGreen+2
    
    kBlack    // data
};

TFile* inFile[nFiles];
double BtagRatio(TH1* Evt_Before, TH1* Evt_After, string histname){
    //Double Muon
    
    double before;
    double after;
    double Ratio;
    if(histname=="hist_w_mt_emm"){
        before = Evt_Before->GetBinContent(20);
        after  = Evt_After->GetBinContent(20);
    }
    if(histname=="hist_w_mt_mmm"){
        before = Evt_Before->GetBinContent(21);
        after  = Evt_After->GetBinContent(21);
    }
    if(histname=="hist_Zmass_mmm"){
        before = Evt_Before->GetBinContent(25);
        after  = Evt_After->GetBinContent(25);
    }
    if(histname=="hist_Zmass_emm"){
        before = Evt_Before->GetBinContent(24);
        after  = Evt_After->GetBinContent(24);
    }
    if(histname=="hist_mva_mmm"){
        before = Evt_Before->GetBinContent(29);
        after  = Evt_After->GetBinContent(29);
    }
    if(histname=="hist_mva_emm"){
        before = Evt_Before->GetBinContent(28);
        after  = Evt_After->GetBinContent(28);
    }
    if(histname=="hist_b_no_mmm" || histname=="hist_b_no_emm"){
        before=1.0;
        after=1.0;
    }

    if(before==0 && after==0) Ratio=1;
    else Ratio = before/after;
    return Ratio;
}

TH1D *AutoRebin(TH1D *hist_in){
    class HIST{
    public:
        vector<double> edges;
        vector<double> data;

         HIST() {};
         HIST(TH1D *hist_in){
              for (int i=1; i<=hist_in->GetNbinsX()+1; i++)
                  edges.push_back(hist_in->GetBinLowEdge(i));
              for (int i=1; i<=hist_in->GetNbinsX(); i++)
                  data.push_back(hist_in->GetBinContent(i));
         }
         HIST(HIST *hist_in){
             data = hist_in->data;
             edges = hist_in->edges;
         }
         void MergeBin(int bin, int direction){
              if (direction<0) { // merge to left
                  if (bin==0) return;
                  data[bin-1] += data[bin];
                  data.erase(data.begin()+bin);
                  edges.erase(edges.begin()+bin);
              }
               if (direction>0) { // merge to right
                  if (bin==(int)data.size()-1) return;
                  data[bin+1] += data[bin];
                  data.erase(data.begin()+bin);
                  edges.erase(edges.begin()+bin+1);
               }
         }
         int Compare(HIST *hist_in){
             if (hist_in->edges.size()!=edges.size()) return -1;
             for (int bin=0; bin<(int)edges.size(); bin++)
                 if (fabs(hist_in->edges[bin]-edges[bin])>1E-5) return -2;
             return 0;
         }

         void Print() {
            cout << "[";
            for (int bin=0; bin<(int)data.size()-1; bin++)
                cout << data[bin] << ", ";
            cout << data.back() << "] in ";
            cout << "[";
            for (int bin=0; bin<(int)edges.size()-1; bin++)
                cout << edges[bin] << ", ";
            cout << edges.back() << "]" << endl;
         }
    };
    
    vector<HIST*> src, dest;
    HIST *clone = new HIST(hist_in);
    src.push_back(clone);
    
    while (1){
        bool w_negative_hist = false;
        for (int idx=0; idx<(int)src.size(); idx++)
            if (src[idx]->data.size()>1) // still can be merged
                  for (int bin=0; bin<(int)src[idx]->data.size(); bin++)
                      if (src[idx]->data[bin]<0.0) w_negative_hist = true;
        if (!w_negative_hist) break;

        //cout << ">>> Rebinning histograms: " << src.size() << endl;

        for (int idx=0; idx<(int)src.size(); idx++){
             bool w_negative_bin = false;
             for (int bin=0; bin<(int)src[idx]->data.size(); bin++){
                  if (src[idx]->data[bin]<0.0) {
                      if (bin>0){
                          HIST *merge = new HIST(src[idx]);
                          merge->MergeBin(bin,-1);
                          bool duplicated = false;
                          for (int i=0; i<(int)dest.size(); i++)
                               if (dest[i]->Compare(merge)==0) duplicated = true;
                          if (!duplicated) dest.push_back(merge);
                      }
                      if (bin<(int)src[idx]->data.size()-1) {
                          HIST *merge = new HIST(src[idx]);
                          merge->MergeBin(bin,+1);
                          bool duplicated = false;
                          for (int i=0; i<(int)dest.size(); i++)
                              if (dest[i]->Compare(merge)==0) duplicated = true;
                          if (!duplicated) dest.push_back(merge);
                      }
                      w_negative_bin = true;
                  }
             }
             if (!w_negative_bin) {
                 HIST *merge = new HIST(src[idx]);
                 bool duplicated = false;
                 for (int i=0; i<(int)dest.size(); i++)
                     if (dest[i]->Compare(merge)==0) duplicated = true;
                 if (!duplicated) dest.push_back(merge);
             }
        }
        for (int idx=0; idx<(int)src.size(); idx++) delete src[idx];
             src.clear();
             src = dest;
             dest.clear();
    }
    //cout << ">>> Rebinning done, look for the best binning:" << endl;

    int max_nbins = 0;
    for (int idx=0; idx<(int)src.size(); idx++) {
        if ((int)src[idx]->data.size()>max_nbins) max_nbins = src[idx]->data.size();
    }
    double minmax_binwidth = 1E10;
    int best_bin_idx = -1;
    for (int idx=0; idx<(int)src.size(); idx++) {
        if ((int)src[idx]->data.size()!=max_nbins) continue;

        double max_binwidth = 0.;
        for (int bin=0; bin<(int)src[idx]->data.size(); bin++) {
            if (src[idx]->edges[bin+1]-src[idx]->edges[bin]>max_binwidth) max_binwidth = src[idx]->edges[bin+1]-src[idx]->edges[bin];
        }
        if (max_binwidth<minmax_binwidth) {
            minmax_binwidth = max_binwidth;
            best_bin_idx = idx;
        }
    }

    TH1D *rebin = (TH1D*)hist_in->Rebin(src[best_bin_idx]->edges.size()-1,Form("%s_rebin",hist_in->GetName()),src[best_bin_idx]->edges.data());
    for (int idx=0; idx<(int)src.size(); idx++) delete src[idx];
    return rebin;
}

TH1D *ReFill(TH1D *input, TH1D *orignal){
    double binwidth = orignal->GetBinWidth(1);
    int start = 1;
    TH1D *ReFillHist = (TH1D*)orignal->Clone();
    for(int idx=1 ; idx<input->GetNbinsX()+1 ; idx++){
        double MergedBinWidth = input->GetBinWidth(idx)/binwidth;
        for(int idx2=start ; idx2<(start+round(MergedBinWidth)) ; idx2++){
            ReFillHist->SetBinContent(idx2, input->GetBinContent(idx)/round(MergedBinWidth));
            ReFillHist->SetBinError(idx2, input->GetBinError(idx)/round(MergedBinWidth));
            if(ReFillHist->GetBinContent(idx2)<0) {
                ReFillHist->SetBinContent(idx2,0);
                ReFillHist->SetBinError(idx2,0);
            }
        }
        start += round(MergedBinWidth);
    }
    return ReFillHist;
}

TPad* NewTopPad(){
        TPad* pad1 = new TPad( "toppad", "", 0, 0.3, 1., 1.0 );
        pad1->SetTicks( 1, 1 );
        pad1->SetBottomMargin( 0.05 );
        pad1->SetLeftMargin( 0.13 );
        pad1->SetRightMargin( 1 - 0.95 );
        pad1->SetTopMargin( ( 1 - 0.9 ) / ( 1 - 0.3 ) );
        return pad1;
      }

TPad* NewBottomPad(){
        TPad* pad2 = new TPad( "botpad", "", 0, 0.00, 1, 0.3 );
        pad2->SetTicks( 1, 1 );
        pad2->SetTopMargin( 0.025 );
        pad2->SetLeftMargin( 0.13 );
        pad2->SetRightMargin( 1 - 0.95 );
        pad2->SetBottomMargin( ( 0.105 ) / ( 0.2 ) );
        return pad2;
      }

TH1D* DivideHist(
        TH1D*        da,
        TH1D*        mc,
        const double cen)
{
        TH1D* ans = (TH1D*)( da->Clone() );
        ans->Divide( mc );

        for( int i = 0; i < da->GetNcells(); ++i ){
            if( da->GetBinContent( i ) == 0 && mc->GetBinContent( i ) == 0 ){
                ans->SetBinContent( i, cen );
            }
        }

        return ans;
}

void DrawLuminosity( double luminosity ){
        TLatex tl;
        tl.SetNDC( kTRUE );
        tl.SetTextFont( 43 );
        tl.SetTextSize( 22 );
        char buffer[ 1024 ];
        sprintf( buffer, "%.1lf fb^{-1} (%d TeV)", luminosity / 1000., 13 );
        tl.SetTextAlign( 31 );
        tl.DrawLatex( 0.92, 0.88 , buffer );
}

void plot_hist(TCanvas *c1, vector<TH1*> &hists, vector<TH1*> &Evt_Before, vector<TH1*> &Evt_After, //vector<TH1*> &hdata,
	       std::string histName, int nfiles, std::string xlabel="test",int x1=-1000,int x2=1000,int y=500){
  std::string filename = hists[0]->GetName();
  TFile *myFILE = new TFile(("../research_progress/roofit/CR/sample/2017_Zct/Central/"+filename+".root").c_str(), "RECREATE");

  c1->cd();
  c1->SetLeftMargin(0.17);
  c1->SetRightMargin(0.05);
  c1->SetTopMargin(0.06);
  c1->SetBottomMargin(0.13);
  
  TPad *pad1 = NewTopPad();
  TPad *pad2 = NewBottomPad();
  //pad1->SetLogy(); 
  
  pad1->Draw();
  pad2->Draw();
  pad1->cd();

  std::string ylabel="Events";
  std::string ydlabel="Ratio";
  const int size = nfiles;
  TH1* plots[size];
  Float_t tgx[500], tgy[500], tgex[500], tgey[500];
  Float_t tgxe[500], tgye[500], tgexe[500], tgeye[500];

  TH1* sigHist;
  TH1* bkgHist;
  TH1* ttbarHist;
  TH1* TTZHist;
  TH1* WZHist;
  TH1* tZqHist;
  TH1* ZZHist;
  TH1* ZZonlyHist;
  TH1* WZandZZHist;
  TH1* otherHist;
  TH1* TTCR_otherHist;
  TH1* DYHist;
  TH1* TTCR_totalOtherHist;
  TH1D *WZCRratio = new TH1D("WZCRratio", "WZCRratio", 20, 0, 20 );
  
  THStack* allHist=new THStack("all", histName.c_str());
  THStack* testHist = new THStack("ALL", histName.c_str());
  TH1F* deno;//addpa
  TH1F* deno2;//addpa
  TLegend* leg = new TLegend(0.65,0.45,0.92,0.82);
  leg->SetTextFont(42);
  leg->SetBorderSize(0);
  leg->SetLineColor(0);
  leg->SetLineStyle(0);
  leg->SetTextFont(42);
  leg->SetFillStyle(1);

  for(int i = nfiles-2; i >= 0; i--){

    std::string histname = hists[i]->GetName();
    char name[100];
    sprintf(name,"%s_%d.png",histname.c_str(),i);

    plots[i] = (TH1*)hists[i]->Clone(histname.c_str());
    plots[i]->GetXaxis()->SetLabelSize(0.06);
    plots[i]->GetYaxis()->SetLabelSize(0.05);
    plots[i]->GetYaxis()->SetLabelOffset(0.005);

    char label[100];
    char labeld[100];
    sprintf(label, "%s", ylabel.c_str());
    sprintf(labeld, "%s", ydlabel.c_str());
    if(xlabel.find("[") < 80){
      sprintf(label, "%s / %d [%s]", ylabel.c_str(),
              (int)plots[i]->GetBinWidth(1), xlabel.c_str()+xlabel.find("[")+1);
      label[strlen(label)-1]=0;
    }
    
    plots[i]->SetYTitle(label);//ylabel.c_str());
    plots[i]->GetYaxis()->SetTitleOffset(0.8);
    plots[i]->GetYaxis()->SetTitleSize(0.065);
    plots[i]->GetXaxis()->SetLabelSize(0);
    
    plots[i]->SetBinContent(plots[i]->GetNbinsX(),
                            plots[i]->GetBinContent(plots[i]->GetNbinsX())+
                            plots[i]->GetBinContent(plots[i]->GetNbinsX()+1));
    plots[i]->SetBinContent(1, plots[i]->GetBinContent(1)
                              +plots[i]->GetBinContent(0));
    
    cout << histFiles[i].c_str() << endl;
    cout << "scale evt # : " << (plots[i]->Integral())*hist_scale[i]*BtagRatio(Evt_Before[i], Evt_After[i], histname) << endl;
    cout << "scale Error : " << (sqrt(fabs(plots[i]->Integral())))*hist_scale[i]*BtagRatio(Evt_Before[i], Evt_After[i], histname) << endl;
    
    plots[i]->Scale(hist_scale[i]*BtagRatio(Evt_Before[i], Evt_After[i], histname));
    plots[i]->SetFillColor(histColor[i]);

    if(plots[i]->GetNbinsX() > 1000) plots[i]->Rebin(5000);
    else if(plots[i]->GetNbinsX() > 10 && plots[i]->GetNbinsX() == 200) plots[i]->Rebin(20);
    else if(plots[i]->GetNbinsX() > 10 && plots[i]->GetNbinsX() == 60) plots[i]->Rebin(4);
    else if(plots[i]->GetNbinsX() > 10 && plots[i]->GetNbinsX() == 40) plots[i]->Rebin(2);
    if( (histname!="hist_b_no_mmm") && histname!="hist_b_no_emm" ) plots[i] = ReFill(AutoRebin((TH1D*)plots[i]), (TH1D*)plots[i]);

      //set line color
    if(i == 0) plots[i]->SetLineColor(kBlack);
       else plots[i]->SetLineColor(histColor[i]);
    if(i==0){
       sigHist=(TH1*)plots[i]->Clone();
    }else if(i==nfiles-2){
       
       allHist->SetHistogram(plots[i]);
       allHist->Add(plots[i]);
       bkgHist=(TH1*)plots[i]->Clone();
       deno=(TH1F*)plots[i]->Clone((histname+"MC").c_str());//addpa
    }else{
       bkgHist->Add(plots[i]);
       allHist->Add(plots[i]);
       deno->Add(plots[i]);//addpa
    }
    
    if(i==1) ttbarHist=(TH1*)plots[i]->Clone();
    if(i==8) TTZHist=(TH1*)plots[i]->Clone();
    if(i==10) WZHist=(TH1*)plots[i]->Clone();
    if(i==19) tZqHist=(TH1*)plots[i]->Clone();
    if(i==13) ZZHist=(TH1*)plots[i]->Clone();
    if(i==21) WZandZZHist=(TH1*)plots[i]->Clone();
    if(i==18) otherHist=(TH1*)plots[i]->Clone();
    if(i==21) DYHist=(TH1*)plots[i]->Clone();
    if(i==19) TTCR_otherHist=(TH1*)plots[i]->Clone();
    if(i==21) TTCR_totalOtherHist=(TH1*)plots[i]->Clone();
    
    if(i==7) TTZHist->Add(plots[i]);
    if(i==9) WZHist->Add(plots[i]);
    if(i==12 || i==11) ZZHist->Add(plots[i]);
    if(i==20 || i==13 || i==12 || i==11 || i==10 || i==9) WZandZZHist->Add(plots[i]);
    if(i==17 || i==16 || i==15 || i==14 || i==6 || i==5 || i==4 || i==3 || i==2) otherHist->Add(plots[i]);
    if(i==20) DYHist->Add(plots[i]);
    if(i!=0 && i!=1 && i!=22 && i!=21 && i!=20) TTCR_otherHist->Add(plots[i]);
    if(i!=0 && i!=1 && i!=22) TTCR_totalOtherHist->Add(plots[i]);
  }

  // Set the data marker
    hists[nfiles-1]->SetMarkerStyle(20);
    hists[nfiles-1]->SetMarkerSize(1.0);
    leg->AddEntry(hists[nfiles-1], "Data", "lp");

  if(hists[nfiles-1]->GetMaximum() > allHist->GetMaximum()){
      allHist->SetMaximum(hists[nfiles-1]->GetMaximum()*2.0);
  }
  else{
      allHist->SetMaximum(allHist->GetMaximum()*2.0);
  }

  allHist->UseCurrentStyle();

  if(allHist->GetXaxis()->GetXmax()==150){
    allHist->GetYaxis()->SetRangeUser(0.0, 300);
  }

  allHist->Draw("HIST");
  
  sigHist->UseCurrentStyle();
  sigHist->SetLineWidth(3);
  sigHist->SetLineColor(kRed+3);
   
  std::string histname = hists[nfiles-1]->GetName();
  cout << histname.c_str() << " signal : " << sigHist->Integral() << endl;
  cout << histname.c_str() << " background : " << bkgHist->Integral() << endl;
 
  //signal_plot
  
  sigHist->Draw("HIST same");
  sigHist->Clone("signal");

  bkgHist->UseCurrentStyle();
  bkgHist->SetLineColor(kBlack);
  bkgHist->SetFillColor(0);
  bkgHist->SetLineWidth(2);
  bkgHist->DrawCopy("HIST same");
  bkgHist->Clone("background");

  ttbarHist->Clone("ttbar");
  TTZHist->Clone("TTZ");
  WZHist->Clone("WZ");
  tZqHist->Clone("tZq");
  ZZHist->Clone("ZZ");
  WZandZZHist->Clone("WZandZZ");
  otherHist->Clone("others");
  DYHist->Clone("DY");
  TTCR_otherHist->Clone("TTCR_other");
  TTCR_totalOtherHist->Clone("TTCR_totalOther");
  
  if( (histname=="hist_b_no_mmm") || histname=="hist_b_no_emm" ){
        //Fix 0 b jets
        double WZ_Onejet = WZHist->GetBinContent(3);
        double WZ_TwoOrThreejet = WZHist->GetBinContent(4);
        WZCRratio->Fill(2, WZ_TwoOrThreejet/WZ_Onejet);
        //Fix 2 or 3 jets
        double WZ_Zerobjet = WZHist->GetBinContent(6);
        double WZ_Onebjet = WZHist->GetBinContent(7);
        WZCRratio->Fill(3, WZ_Onebjet/WZ_Zerobjet);

        //Fix 0 b jets
        double ZZ_Onejet = ZZHist->GetBinContent(3);
        double ZZ_TwoOrThreejet = ZZHist->GetBinContent(4);
        WZCRratio->Fill(5, ZZ_TwoOrThreejet/ZZ_Onejet);
        //Fix 2 or 3 jets
        double ZZ_Zerobjet = ZZHist->GetBinContent(6);
        double ZZ_Onebjet = ZZHist->GetBinContent(7);
        WZCRratio->Fill(6, ZZ_Onebjet/ZZ_Zerobjet);
        
        //Fix 0 b jets
        double DY_Onejet = DYHist->GetBinContent(3);
        double DY_TwoOrThreejet = DYHist->GetBinContent(4);
        WZCRratio->Fill(8, DY_TwoOrThreejet/DY_Onejet);
        //Fix 2 or 3 jets
        double DY_Zerobjet = DYHist->GetBinContent(6);
        double DY_Onebjet = DYHist->GetBinContent(7);
        WZCRratio->Fill(9, DY_Onebjet/DY_Zerobjet);

  }
  
  //for(int ib=1; ib <= 12; ib++){
 for(int ib=1; ib <= bkgHist->GetNbinsX()+1; ib++){
      tgx[ib-1]=bkgHist->GetXaxis()->GetBinCenter(ib);
      tgy[ib-1]=bkgHist->GetBinContent(ib);
      tgex[ib-1]=bkgHist->GetBinWidth(ib)/2;
      tgey[ib-1]=bkgHist->GetBinError(ib);
  }
  TGraphErrors *gr = new TGraphErrors(bkgHist->GetNbinsX(),
          tgx, tgy, tgex, tgey);
  gr->UseCurrentStyle();
  gr->SetLineColor(0);
  gr->SetFillColor(kBlack);
  gr->SetFillStyle(3013);
  gr->Draw("e2same");
  
  plots[nfiles-1] = (TH1*)hists[nfiles-1]->Clone(histname.c_str());
  cout << histname.c_str() << " Data : " << plots[nfiles-1]->Integral() << endl;

  plots[nfiles-1]->SetLineColor(kBlack);
  plots[nfiles-1]->SetMarkerStyle(20);
  plots[nfiles-1]->SetMarkerSize(0.9);
  
  plots[nfiles-1]->SetBinContent(plots[nfiles-1]->GetNbinsX(),
                          plots[nfiles-1]->GetBinContent(plots[nfiles-1]->GetNbinsX())+
                          plots[nfiles-1]->GetBinContent(plots[nfiles-1]->GetNbinsX()+1));
  plots[nfiles-1]->SetBinContent(1, plots[nfiles-1]->GetBinContent(1)
                                   +plots[nfiles-1]->GetBinContent(0));
  
  cout << histFiles[nfiles-1].c_str() << endl;
  cout << "Evt # : " << plots[nfiles-1]->Integral() << endl;
  cout << "Error : " << sqrt(plots[nfiles-1]->Integral()) << endl;
 
  if(plots[nfiles-1]->GetNbinsX() > 1000) plots[nfiles-1]->Rebin(5000);
  else if(plots[nfiles-1]->GetNbinsX() > 10 && plots[nfiles-1]->GetNbinsX() == 200) plots[nfiles-1]->Rebin(20);
  else if(plots[nfiles-1]->GetNbinsX() > 10 && plots[nfiles-1]->GetNbinsX() == 60) plots[nfiles-1]->Rebin(4);
  else if(plots[nfiles-1]->GetNbinsX() > 10 && plots[nfiles-1]->GetNbinsX() == 40) plots[nfiles-1]->Rebin(2);
 
  deno2=(TH1F*)plots[nfiles-1]->Clone((histname+"Data").c_str());
  
  for(int i=0 ; i<plots[nfiles-1]->GetNbinsX() ; i++){
      for(int j=0 ; j<plots[nfiles-1]->GetNbinsY() ; j++){
          if(plots[nfiles-1]->GetBinContent(i+1, j+1) < 0.) plots[nfiles-1]->SetBinContent(i+1, j+1, 0.);
      }
  }

  plots[nfiles-1]->Draw("same");
  plots[nfiles-1]->Clone("data");
  
  leg->AddEntry(sigHist, Labels[0].c_str(), "l");
  for(int i = 1; i < nfiles; i++){
    if(i ==1 || i==2 || i==4 || i==8 || i==9 || i==11 || i==14 || i==19 || i==20)
      leg->AddEntry(plots[i], Labels[i].c_str(), "f");
  }
  
  leg->Draw();

  TLatex tl;
  tl.SetNDC( kTRUE );
  tl.SetTextFont( 43 );
  tl.SetTextSize( 22 );
  tl.SetTextAlign( 13 );
  tl.DrawLatex( 0.13 + 0.04, 0.9 - 0.08, "#bf{CMS}" );

  tl.DrawLatex( 0.13 + 0.04, 0.75, "#it{Preliminary}" );
  DrawLuminosity(INT_LUM); 
  
  Float_t tgx2[500], tgy2[500], tgex2[500], tgey2[500];
  pad2->cd();
  TH1D *divide = DivideHist((TH1D*)plots[nfiles-1], (TH1D*)bkgHist,0);
  divide->GetXaxis()->SetLabelSize(0.12);
  divide->GetXaxis()->SetTitleSize(0.15);
  divide->SetXTitle(xlabel.c_str());
  divide->SetYTitle("Data/MC");
  divide->GetYaxis()->SetTitleOffset(0.3);
  divide->GetYaxis()->SetTitleSize(0.15);
  divide->GetYaxis()->SetLabelSize(0.08);
  divide->GetYaxis()->SetNdivisions(3);
  divide->GetYaxis()->SetRangeUser(0.5,1.5);
  TLine *l1 = new TLine(divide->GetXaxis()->GetXmin(), 1.0,divide->GetXaxis()->GetXmax() , 1.0);
  l1->SetLineColor(kRed);
  for(int ib=1; ib <= bkgHist->GetNbinsX()+1; ib++){
      tgx2[ib-1]=bkgHist->GetXaxis()->GetBinCenter(ib);
      tgy2[ib-1]=1.;
      tgex2[ib-1]=bkgHist->GetBinWidth(ib)/2;
      tgey2[ib-1]=bkgHist->GetBinError(ib)/(bkgHist->GetBinContent(ib));
      if(bkgHist->GetBinContent(ib)==0) divide->SetBinError(ib, 0);
      else divide->SetBinError(ib, sqrt(plots[nFiles-1]->GetBinContent(ib))/bkgHist->GetBinContent(ib));
  }

  TGraphErrors *gr2 = new TGraphErrors(bkgHist->GetNbinsX(),
          tgx2,tgy2, tgex2, tgey2);
  gr2->UseCurrentStyle();
  gr2->SetLineColor(0);
  gr2->SetFillColor(kBlack);
  gr2->SetFillStyle(3013);

  divide->Draw();
  l1->Draw("same");
  gr2->Draw("e2same");
  pad2->cd();
  c1->cd();//addpa
  myFILE->Write();
}


void mkplots_summary_DM(){

  gROOT->Reset();
  gStyle->SetOptFit();

  gROOT->LoadMacro("setTDRStyle.C");

 gStyle->SetOptStat(0);
 gStyle->SetTitleXOffset(0.9);
 gStyle->SetTitleYOffset(1.25);

 gStyle->SetHatchesSpacing(1.0);
 gStyle->SetOptTitle(0);

 double m_over=0., m_max=0.;
 TH1* hist;
 
 cout << "reading histograms...\n";

 for(int if1=0; if1 < nFiles; if1++){ 
   cout << "loading... \n";
   inFile[if1] = TFile::Open(histFiles[if1].c_str());
   cout << histFiles[if1].c_str() << endl;
   gDirectory->cd("");
   hist = (TH1*) gDirectory->Get("hist_evt_weightB");
   Final_evt_weightB.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_evt_weightA");
   Final_evt_weightA.push_back(hist);

//{{{---------------------------------GetHist------------------------------------------
   
   hist = (TH1*) gDirectory->Get("hist_mva_emm");
   Final_mva_emm.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_mva_mmm");
   Final_mva_mmm.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_w_mt_emm");
   Final_w_mt_emm.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_w_mt_mmm");
   Final_w_mt_mmm.push_back(hist);

   hist = (TH1*) gDirectory->Get("hist_Zmass_emm");
   Final_Zmass_emm.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_Zmass_mmm");
   Final_Zmass_mmm.push_back(hist);
   
   hist = (TH1*) gDirectory->Get("hist_b_no_mmm");
   Final_b_no_mmm.push_back(hist);
   hist = (TH1*) gDirectory->Get("hist_b_no_emm");
   Final_b_no_emm.push_back(hist);

//**********************************************************************//
  //}}}
 }
//{{{--- -----------------Plot Histgram---------------------------------------
  TCanvas *c1 = new TCanvas("c1","T2ZQ",10,10,600,550);
  c1->cd();
  c1->cd()->SetRightMargin(0.08);
 
  plot_hist(c1, Final_mva_emm, Final_evt_weightB, Final_evt_weightA, "MVA Response", nFiles, "MVA Response");
  c1->SaveAs("../mkplot_perf_2017/CR/MVA_emm.png");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);
  plot_hist(c1, Final_mva_mmm, Final_evt_weightB, Final_evt_weightA, "MVA Response", nFiles, "MVA Response");
  c1->SaveAs("../mkplot_perf_2017/CR/MVA_mmm.png");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

  plot_hist(c1, Final_w_mt_emm, Final_evt_weightB, Final_evt_weightA, "Transverse Mass of W", nFiles, "Transverse Mass of W[GeV/c^{2}]");
  c1->SaveAs("../mkplot_perf_2017/CR/w_mt_emm.png");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);
  plot_hist(c1, Final_w_mt_mmm, Final_evt_weightB, Final_evt_weightA, "Transverse Mass of W", nFiles, "Transverse Mass of W[GeV/c^{2}]");
  c1->SaveAs("../mkplot_perf_2017/CR/w_mt_mmm.png");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

  plot_hist(c1, Final_Zmass_emm, Final_evt_weightB, Final_evt_weightA, "Invariant Mass of Z", nFiles, "Invariant Mass of Z[GeV/c^{2}]");
  c1->SaveAs("../mkplot_perf_2017/CR/Zmass_emm.png");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);
  plot_hist(c1, Final_Zmass_mmm, Final_evt_weightB, Final_evt_weightA, "Invariant Mass of Z", nFiles, "Invariant Mass of Z[GeV/c^{2}]");
  c1->SaveAs("../mkplot_perf_2017/CR/Zmass_mmm.png");
  c1->cd();
  c1->cd()->SetRightMargin(0.08);

  plot_hist(c1, Final_b_no_mmm, Final_evt_weightB, Final_evt_weightA, "Transfer Ratio", nFiles, "Transfer Ratio");
  plot_hist(c1, Final_b_no_emm, Final_evt_weightB, Final_evt_weightA, "Transfer Ratio", nFiles, "Transfer Ratio");
  //}}}

}
 
