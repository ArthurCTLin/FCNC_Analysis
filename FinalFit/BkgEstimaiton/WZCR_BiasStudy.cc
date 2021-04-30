void GaussFit( vector<double> pull, string name ){
    using namespace RooFit;
    TCanvas *c3 = new TCanvas("c3", "c3", 800, 800);
    RooRealVar x("x", "Pull Distribution", -3., 3.);
    RooRealVar mu("mu", "Mean Value", 1., -3., 3.);
    RooRealVar sigma("sigma", "width parameter", 1., -3., 3.);
    RooGaussian gfit("gfit", "Gaussian PDF", x, mu, sigma);
    
    RooDataSet dataset("dataset", "dataset", RooArgSet(x));
    for (int i=0 ; i<2000 ; i++){
        x.setVal(pull[i]);
        dataset.add(RooArgSet(x));
    }
    gfit.fitTo(dataset);

    //RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
    //RooMsgService::instance().setSilentMode(true);
    RooFitResult *result = gfit.fitTo(dataset, Save(true));
    cout << "RooFitResult of PullFit : " << result->status() << endl;
   
    TPaveText* pt = new TPaveText(.60, .70, .90, .85, "NDC" );
    pt->SetTextFont(43);
    pt->SetTextSize(18);
    pt->SetFillColorAlpha( 0, 0 );
    pt->AddText( (name+" PDF :").c_str() );
    pt->AddText( "Entries : 2000" );
    pt->AddText( Form("Mean :  %3.2f #pm %3.2f", mu.getVal(), mu.getError() ));
    pt->AddText( Form("Sigma :  %3.2f #pm %3.2f", sigma.getVal(), sigma.getError() ));

    RooPlot *frame = x.frame();
    dataset.plotOn(frame);
    gfit.plotOn(frame);
    frame->Draw();
    
    pt->Draw("same");
    
    c3->SaveAs((name+"_PullFit.png").c_str());
}

void PullDist( TH1D* hist_sig, TH1D* hist_bkg, TH1D* hist_bkg1, string name_WZ, string name_DY, string name_ZZ ){

    using namespace RooFit;
    
    vector<RooDataSet> toymc;
    vector<double> pull_WZ;
    vector<double> pull_DY;
    vector<double> pull_ZZ;
    double mc_no_s = hist_sig->Integral();
    double mc_no_b = hist_bkg->Integral();
    double mc_no_b1 = hist_bkg1->Integral();
    double mc_no_total = mc_no_s + mc_no_b + mc_no_b1;

    RooRealVar N_MC_s("N_MC_s", "N_MC_s", 10., -100., 800.);
    RooRealVar N_MC_b("N_MC_b", "N_MC_b", 50., -100., 800.);
    RooRealVar N_MC_b1("N_MC_b1", "N_MC_b1", 50., -100., 400.);
    RooRealVar WTransmass("WTransmass", "WTransmass", 0., 300.);
    RooDataHist binMC_s("binMC_s", "binMC_s", RooArgList(WTransmass), hist_sig);
    RooDataHist binMC_b("binMC_b", "binMC_b", RooArgList(WTransmass), hist_bkg);
    RooDataHist binMC_b1("binMC_b1", "binMC_b1", RooArgList(WTransmass), hist_bkg1);
    RooHistPdf MC_pdf_s("MC_pdf_s", "MC_pdf_s", RooArgList(WTransmass), binMC_s);
    RooHistPdf MC_pdf_b("MC_pdf_b", "MC_pdf_b", RooArgList(WTransmass), binMC_b);
    RooHistPdf MC_pdf_b1("MC_pdf_b1", "MC_pdf_b1", RooArgList(WTransmass), binMC_b1);
    RooAddPdf final_pdf("final_pdf", "final_pdf", RooArgList(MC_pdf_s, MC_pdf_b, MC_pdf_b1), RooArgList(N_MC_s, N_MC_b, N_MC_b1));
    
    for (int i=0 ; i<2000 ; i++){
        int PoissonEvent_s = RooRandom::randomGenerator()->Poisson(mc_no_s);
        RooDataSet *dataset_s = MC_pdf_s.generate(WTransmass, PoissonEvent_s);
        int PoissonEvent_b = RooRandom::randomGenerator()->Poisson(mc_no_b);
        RooDataSet *dataset_b = MC_pdf_b.generate(WTransmass, PoissonEvent_b);
        int PoissonEvent_b1 = RooRandom::randomGenerator()->Poisson(mc_no_b1);
        RooDataSet *dataset_b1 = MC_pdf_b1.generate(WTransmass, PoissonEvent_b1);

        RooDataSet *total_dataset = new RooDataSet(*dataset_s);
        total_dataset->append(*dataset_b);
        total_dataset->append(*dataset_b1);
       
        toymc.push_back(*total_dataset);

    }
  
    for(int i=0 ; i<2000 ; i++){
        double result_sig = 0.;
        double result_bkg = 0.;
        double result_bkg1 = 0.;
        double floatN_MC_sig = 0.;
        double floatN_MC_bkg = 0.;
        double floatN_MC_bkg1 = 0.;
        double floatErr_MC_sig = 0.;
        double floatErr_MC_bkg = 0.;
        double floatErr_MC_bkg1 = 0.;
        
//        RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
//        RooMsgService::instance().setSilentMode(true);
       
        final_pdf.fitTo(toymc[i], Extended(true));    
        floatN_MC_sig = N_MC_s.getVal();
        floatN_MC_bkg = N_MC_b.getVal();
        floatN_MC_bkg1 = N_MC_b1.getVal();
        floatErr_MC_sig = N_MC_s.getError();
        floatErr_MC_bkg = N_MC_b.getError();
        floatErr_MC_bkg1 = N_MC_b1.getError();

        result_sig = (floatN_MC_sig-mc_no_s)/floatErr_MC_sig;

        result_bkg = (floatN_MC_bkg-mc_no_b)/floatErr_MC_bkg;
        result_bkg1 = (floatN_MC_bkg1-mc_no_b1)/floatErr_MC_bkg1;
        
        pull_WZ.push_back(result_sig);
        pull_DY.push_back(result_bkg);
        pull_ZZ.push_back(result_bkg1);
    }
    GaussFit(pull_WZ, name_WZ);
    GaussFit(pull_DY, name_DY);
    GaussFit(pull_ZZ, name_ZZ);
}

void WZCR(){
    TFile *fin = new TFile("../../sample/2016_Zct/Central/hist_w_mt_emm.root");
    TH1D *sig = (TH1D*)fin->Get("WZ");
    TH1D *bkg = (TH1D*)fin->Get("DY");
    TH1D *bkg1 = (TH1D*)fin->Get("ZZ");
    string name_WZ("WZ");
    string name_DY("DY");
    string name_ZZ("ZZ");
    PullDist( sig, bkg, bkg1, name_WZ, name_DY, name_ZZ );
}


