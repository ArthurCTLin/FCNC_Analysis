{
    TFile *fin1 = new TFile("./sample/2016_Zut//hist_w_mt_mmm.root");
    TFile *fin2 = new TFile("./sample/2016_Zut//hist_b_no_mmm.root");
    
    TH1D *WZCR_WZ = (TH1D*)fin1->Get("WZ");
    TH1D *WZCR_ZZ = (TH1D*)fin1->Get("ZZ");
    TH1D *WZCR_DY = (TH1D*)fin1->Get("DY");
    TH1D *WZCR_Data = (TH1D*)fin1->Get("data");

    TH1D *WZCR_Ratio = (TH1D*)fin2->Get("WZCRratio");

    TFile *fin3 = new TFile("./sample/2016_Zut//Zmass_combine.root");
    TFile *fin4 = new TFile("./sample/2016_Zut//hist_Zmass_mmm.root");
    TH1D *TTCR_sig = (TH1D*)fin3->Get("ttbar");
    TH1D *TTCR_sig_mmm = (TH1D*)fin4->Get("ttbar");
    TH1D *TTCR_data = (TH1D*)fin3->Get("data");

    TFile *fin5 = new TFile("./sample/2016_Zut//hist_mva_mmm.root");
    //
    TH1D *Final_sig = (TH1D*)fin5->Get("signal");
    TH1D *Final_bkg_ttbar = (TH1D*)fin5->Get("ttbar");
    TH1D *Final_bkg_TTZ = (TH1D*)fin5->Get("TTZ");
    TH1D *Final_bkg_WZ = (TH1D*)fin5->Get("WZ");
    TH1D *Final_bkg_ZZ = (TH1D*)fin5->Get("ZZ");
    TH1D *Final_bkg_DY = (TH1D*)fin5->Get("DY");
    TH1D *Final_bkg_tZq = (TH1D*)fin5->Get("tZq");
    TH1D *Final_bkg_other = (TH1D*)fin5->Get("others");
    TH1D *Final_data_shape = (TH1D*)fin5->Get("data");


    using namespace RooFit;
//{{{ WZCR   
    RooRealVar N_WZCR_WZ("N_WZCR_WZ", "N_WZCR_WZ", 10, -50, 3000);   
    RooRealVar N_WZCR_ZZ("N_WZCR_ZZ", "N_WZCR_ZZ", 20, -50, 3000);
    RooRealVar N_WZCR_DY("N_WZCR_DY", "N_WZCR_DY", 20, -50, 3000);
    
    double WZ_exp = WZCR_WZ->Integral();
    double ZZ_exp = WZCR_ZZ->Integral();
    double DY_exp = WZCR_DY->Integral();

    RooGaussian constraint_WZ("constraint_WZ","constraint_WZ",N_WZCR_WZ,RooConst(WZ_exp), RooConst(sqrt(WZ_exp))) ;
    RooGaussian constraint_ZZ("constraint_ZZ","constraint_ZZ",N_WZCR_ZZ,RooConst(ZZ_exp), RooConst(sqrt(ZZ_exp))) ;
    RooGaussian constraint_DY("constraint_DY","constraint_DY",N_WZCR_DY,RooConst(DY_exp), RooConst(sqrt(DY_exp))) ;
    RooArgSet gausConstraint(constraint_WZ, constraint_ZZ, constraint_DY);

    RooRealVar WTransmass("WTransmass", "WTransmass", 0., 300.);
    RooDataHist bin_WZCR_WZ("bin_WZCR_WZ", "bin_WZCR_WZ", RooArgList(WTransmass), WZCR_WZ);
    RooDataHist bin_WZCR_ZZ("bin_WZCR_ZZ", "bin_WZCR_ZZ", RooArgList(WTransmass), WZCR_ZZ);
    RooDataHist bin_WZCR_DY("bin_WZCR_DY", "bin_WZCR_DY", RooArgList(WTransmass), WZCR_DY);
    RooDataHist bin_WZCR_Data("bin_WZCR_Data", "bin_WZCR_Data", RooArgList(WTransmass), WZCR_Data);

    RooHistPdf WZCR_WZ_pdf("WZCR_WZ_pdf", "WZCR_WZ_pdf", RooArgList(WTransmass), bin_WZCR_WZ);
    RooHistPdf WZCR_ZZ_pdf("WZCR_ZZ_pdf", "WZCR_ZZ_pdf", RooArgList(WTransmass), bin_WZCR_ZZ);
    RooHistPdf WZCR_DY_pdf("WZCR_DY_pdf", "WZCR_DY_pdf", RooArgList(WTransmass), bin_WZCR_DY);

    RooAddPdf WZCR_total_pdf("WZCR_total_pdf", "WZCR_total_pdf", RooArgList(WZCR_WZ_pdf, WZCR_ZZ_pdf, WZCR_DY_pdf), RooArgList(N_WZCR_WZ, N_WZCR_ZZ, N_WZCR_DY));
    WZCR_total_pdf.fitTo(bin_WZCR_Data, ExternalConstraints(gausConstraint), Extended(true), Minos(true), SumW2Error(kTRUE));//, Extended(true));

    double WZ_no = N_WZCR_WZ.getVal()*(WZCR_Ratio->GetBinContent(4))*(WZCR_Ratio->GetBinContent(3));
    double ZZ_no = N_WZCR_ZZ.getVal()*(WZCR_Ratio->GetBinContent(7))*(WZCR_Ratio->GetBinContent(6));
    double DY_no = N_WZCR_DY.getVal()*(WZCR_Ratio->GetBinContent(10))*(WZCR_Ratio->GetBinContent(9));

    RooPlot *frame = WTransmass.frame();
    bin_WZCR_Data.plotOn(frame);
    WZCR_total_pdf.plotOn(frame);
    WZCR_total_pdf.plotOn(frame, Components(WZCR_WZ_pdf) , LineStyle(2), LineColor(kRed));

    /*
    TCanvas *c1 = new TCanvas("c1", "Transverse Mass of W", 10,10,600,550);
    frame->SetMaximum(frame->GetMaximum()*1.5);
    frame->Draw();
    RooFitResult *result = WZCR_total_pdf.fitTo(bin_WZCR_Data, Save(true), Extended(true), Minos(true), SumW2Error(kTRUE));
    cout << "The Result Value of the fitting : " << result->status() << endl;

    TPaveText* pt = new TPaveText(.50, .75, .90, .90, "NDC" );
    pt->SetTextFont(43);
    pt->SetTextSize(18);
    pt->SetFillColorAlpha( 0, 0 );
    pt->AddText( Form("WZ+jets :  %3.3f #pm %3.3f", N_WZCR_WZ.getVal(), N_WZCR_WZ.getError() ));
    pt->AddText( Form("ZZ :  %4.3f #pm %4.3f",(N_WZCR_ZZ.getVal()), (N_WZCR_ZZ.getError() )));
    pt->AddText( Form("DY :  %4.3f #pm %4.3f",(N_WZCR_DY.getVal()), (N_WZCR_DY.getError() )));
    pt->Draw();
*/
    //c1->SaveAs("./plot/WZCR_mmm.png");
//}}}
    
//{{{TTCR
    RooRealVar TTCR_N_sig("TTCR_N_sig", "TTCR_N_sig", 10, -50, 500);   
    RooRealVar TTCR_N_bkg("TTCR_N_bkg", "TTCR_N_bkg", 20, -50, 1000);
    
    RooRealVar Zmass("Zmass", "Zmass", 30., 150.);
    RooDataHist TTCR_binsig("TTCR_binsig", "TTCR_binsig", RooArgList(Zmass), TTCR_sig);
    RooDataHist TTCR_bindata("TTCR_bindata", "TTCR_bindata", RooArgList(Zmass), TTCR_data);

    RooHistPdf TTCR_sig_pdf("TTCR_sig_pdf", "TTCR_sig_pdf", RooArgList(Zmass), TTCR_binsig);
    RooAddPdf TTCR_total_pdf("TTCR_total_pdf", "TTCR_total_pdf", RooArgList(TTCR_sig_pdf), RooArgList(TTCR_N_sig));

    Zmass.setRange("left",30.,70.);
    Zmass.setRange("right",110.,150.);
    TTCR_total_pdf.fitTo(TTCR_bindata,Range("left,right"), Minos(true), Extended(true));

    RooPlot *frame4 = Zmass.frame();
    TTCR_bindata.plotOn(frame4);
    TTCR_total_pdf.plotOn(frame4);
   
    Zmass.setRange("middle", 82.5, 97.5);
    Zmass.setRange("middle2", 70., 110);
    RooAbsReal* sigregion_sig = TTCR_total_pdf.createIntegral(Zmass, NormSet(Zmass), Range("middle"));
    RooAbsReal* sigregion_sig2 = TTCR_total_pdf.createIntegral(Zmass, NormSet(Zmass), Range("middle2"));

    double Exp_SR = sigregion_sig->getVal()*TTCR_sig->Integral();
    double Exp_SB = TTCR_sig->Integral()-sigregion_sig2->getVal()*TTCR_sig->Integral();
    cout << "Expected in signal region : " << sigregion_sig->getVal()*TTCR_sig->Integral() << endl;
    cout << "Expected outside 70~110 : " << TTCR_sig->Integral()-sigregion_sig2->getVal()*TTCR_sig->Integral() << endl;
    
    RooFitResult *result4 = TTCR_total_pdf.fitTo(TTCR_bindata, Range("left,right"), Save(true), Extended(true), Minos(true));
    cout << "The Result Value of the fitting : " << result4->status() << endl;

    TCanvas *c4 = new TCanvas("c4", "Invariant Mass of Z", 10,10,600,550);
    c4->cd();
    frame4->SetMaximum(frame4->GetMaximum());
    frame4->Draw();

    TPaveText* pt4 = new TPaveText(.50, .75, .90, .90, "NDC" );
    pt4->SetTextFont(43);
    pt4->SetTextSize(18);
    pt4->SetFillColorAlpha( 0, 0 );
    pt4->AddText( Form("ttbar+jets :  %3.2f #pm %3.2f",TTCR_N_sig.getVal()-sigregion_sig2->getVal()*TTCR_N_sig.getVal(), TTCR_N_sig.getError()));
    pt4->Draw();

    double ttbar_No = (TTCR_N_sig.getVal()-sigregion_sig2->getVal()*TTCR_N_sig.getVal())*(TTCR_sig_mmm->Integral()/TTCR_sig->Integral())*(Exp_SR/Exp_SB);
    //c4->SaveAs("Zmass_sideband.png");
//}}}

    double Final_N_ttbar = ttbar_No;
    double Final_N_TTZ = Final_bkg_TTZ->Integral();
    double Final_N_WZ = WZ_no;
    double Final_N_ZZ = ZZ_no;
    double Final_N_tZq = Final_bkg_tZq->Integral();
    double Final_N_DY = DY_no;
    double Final_N_other = Final_bkg_other->Integral();
    RooRealVar Final_N_sig("Final_N_sig", "Final_N_sig", 10, -100., 300);   
    RooRealVar Final_N_bkg_ttbar("Final_N_bkg_ttbar", "Final_N_bkg_ttbar", Final_N_ttbar, -20, 200);
    RooRealVar Final_N_bkg_TTZ("Final_N_bkg_TTZ", "Final_N_bkg_TTZ", Final_N_TTZ, -20, 200);
    RooRealVar Final_N_bkg_WZ("Final_N_bkg_WZ", "Final_N_bkg_WZ", Final_N_WZ, -20, 200);
    RooRealVar Final_N_bkg_ZZ("Final_N_bkg_ZZ", "Final_N_bkg_ZZ", Final_N_ZZ, -20, 200);
    RooRealVar Final_N_bkg_tZq("Final_N_bkg_tZq", "Final_N_bkg_tZq", Final_N_tZq , -20, 200);
    RooRealVar Final_N_bkg_DY("Final_N_bkg_DY", "Final_N_bkg_DY", Final_N_DY, -20, 200);
    RooRealVar Final_N_bkg_other("Final_N_bkg_other", "Final_N_bkg_other", Final_N_other, -20, 200);

    RooGaussian Final_constraint_ttbar("Final_constraint_ttbar","Final_constraint_ttbar",Final_N_bkg_ttbar,RooConst(Final_N_ttbar),RooConst(sqrt(Final_N_ttbar)*5)) ;
    RooGaussian Final_constraint_TTZ("Final_constraint_TTZ","Final_constraint_TTZ",Final_N_bkg_TTZ,RooConst(Final_N_TTZ),RooConst(sqrt(Final_N_TTZ)*5)) ;
    RooGaussian Final_constraint_WZ("Final_constraint_WZ","Final_constraint_WZ",Final_N_bkg_WZ,RooConst(Final_N_WZ),RooConst(sqrt(Final_N_WZ)*5)) ;
    RooGaussian Final_constraint_ZZ("Final_constraint_ZZ","Final_constraint_ZZ",Final_N_bkg_ZZ,RooConst(Final_N_ZZ),RooConst(sqrt(Final_N_ZZ)*5)) ;
    RooGaussian Final_constraint_tZq("Final_constraint_tZq","Final_constraint_tZq",Final_N_bkg_tZq,RooConst(Final_N_tZq),RooConst(sqrt(Final_N_tZq)*5)) ;
    RooGaussian Final_constraint_DY("Final_constraint_DY","Final_constraint_DY",Final_N_bkg_DY,RooConst(Final_N_DY),RooConst(sqrt(Final_N_DY)*5)) ;
    RooGaussian Final_constraint_other("Final_constraint_other","Final_constraint_other",Final_N_bkg_other,RooConst(Final_N_other),RooConst(sqrt(Final_N_other)*5)) ;
    RooArgSet Final_gausConstraint(Final_constraint_ttbar, Final_constraint_TTZ, Final_constraint_WZ, Final_constraint_ZZ, Final_constraint_tZq, Final_constraint_DY, Final_constraint_other);
    
    RooRealVar MVAOutput("MVAOutput", "MVAOutput", -1., 1.);
    RooDataHist Final_binsig("Final_binsig", "Final_binsig", RooArgList(MVAOutput), Final_sig);
    RooDataHist Final_binbkg_ttbar("Final_binbkg_ttbar", "Final_binbkg_ttbar", RooArgList(MVAOutput), Final_bkg_ttbar);
    RooDataHist Final_binbkg_TTZ("Final_binbkg_TTZ", "Final_binbkg_TTZ", RooArgList(MVAOutput), Final_bkg_TTZ);
    RooDataHist Final_binbkg_WZ("Final_binbkg_WZ", "Final_binbkg_WZ", RooArgList(MVAOutput), Final_bkg_WZ);
    RooDataHist Final_binbkg_ZZ("Final_binbkg_ZZ", "Final_binbkg_ZZ", RooArgList(MVAOutput), Final_bkg_ZZ);
    RooDataHist Final_binbkg_tZq("Final_binbkg_tZq", "Final_binbkg_tZq", RooArgList(MVAOutput), Final_bkg_tZq);
    RooDataHist Final_binbkg_DY("Final_binbkg_DY", "Final_binbkg_DY", RooArgList(MVAOutput), Final_bkg_DY);
    RooDataHist Final_binbkg_other("Final_binbkg_other", "Final_binbkg_other", RooArgList(MVAOutput), Final_bkg_other);
    RooDataHist Final_bindata("Final_bindata", "Final_bindata", RooArgList(MVAOutput), Final_data_shape);

    RooHistPdf Final_sig_pdf("Final_sig_pdf", "Final_sig_pdf", RooArgList(MVAOutput), Final_binsig);
    RooHistPdf Final_bkg_pdf_ttbar("Final_bkg_pdf_ttbar", "Final_bkg_pdf_ttbar", RooArgList(MVAOutput), Final_binbkg_ttbar);
    RooHistPdf Final_bkg_pdf_TTZ("Final_bkg_pdf_TTZ", "Final_bkg_pdf_TTZ", RooArgList(MVAOutput), Final_binbkg_TTZ);
    RooHistPdf Final_bkg_pdf_WZ("Final_bkg_pdf_WZ", "Final_bkg_pdf_WZ", RooArgList(MVAOutput), Final_binbkg_WZ);
    RooHistPdf Final_bkg_pdf_ZZ("Final_bkg_pdf_ZZ", "Final_bkg_pdf_ZZ", RooArgList(MVAOutput), Final_binbkg_ZZ);
    RooHistPdf Final_bkg_pdf_tZq("Final_bkg_pdf_tZq", "Final_bkg_pdf_tZq", RooArgList(MVAOutput), Final_binbkg_tZq);
    RooHistPdf Final_bkg_pdf_DY("Final_bkg_pdf_DY", "Final_bkg_pdf_DY", RooArgList(MVAOutput), Final_binbkg_DY);
    RooHistPdf Final_bkg_pdf_other("Final_bkg_pdf_other", "Final_bkg_pdf_other", RooArgList(MVAOutput), Final_binbkg_other);

    RooAddPdf Final_total_pdf("Final_total_pdf", "Final_total_pdf", RooArgList(Final_sig_pdf, Final_bkg_pdf_ttbar, Final_bkg_pdf_TTZ, Final_bkg_pdf_WZ, Final_bkg_pdf_ZZ, Final_bkg_pdf_tZq, Final_bkg_pdf_DY, Final_bkg_pdf_other), RooArgList(Final_N_sig, Final_N_bkg_ttbar, Final_N_bkg_TTZ, Final_N_bkg_WZ, Final_N_bkg_ZZ, Final_N_bkg_tZq, Final_N_bkg_DY, Final_N_bkg_other));
    
    Final_total_pdf.fitTo(Final_bindata, ExternalConstraints(Final_gausConstraint), Extended(true), Minos(true), SumW2Error(kTRUE));//, Extended(true));
    //Final_total_pdf.fitTo(Final_bindata, Extended(true), Minos(true), SumW2Error(kTRUE));//, Extended(true));
    
    RooPlot *Final_frame = MVAOutput.frame();
    Final_bindata.plotOn(Final_frame);
    Final_total_pdf.plotOn(Final_frame);
    Final_total_pdf.plotOn(Final_frame, Components(Final_sig_pdf) , LineStyle(2), LineColor(kRed));

    TCanvas *c1 = new TCanvas("c1", "MVA Response", 10,10,600,550);
    Final_frame->SetMaximum(Final_frame->GetMaximum()*1.5);
    Final_frame->Draw();
    RooFitResult *Final_result = Final_total_pdf.fitTo(Final_bindata, ExternalConstraints(Final_gausConstraint), Save(true), Extended(true), Minos(true), SumW2Error(kTRUE));
    cout << "The Result Value of the fitting : " << Final_result->status() << endl;

    TPaveText* pt3 = new TPaveText(.50, .55, .90, .90, "NDC" );
    pt3->SetTextFont(43);
    pt3->SetTextSize(18);
    pt3->SetFillColorAlpha( 0, 0 );
    pt3->AddText( Form("Signal :  %3.2f #pm %3.2f", Final_N_sig.getVal(), Final_N_sig.getError() ));
    pt3->AddText( Form("ttbar+jets :  %4.2f #pm %4.2f",(Final_N_bkg_ttbar.getVal()), (Final_N_bkg_ttbar.getError() )));
    pt3->AddText( Form("TTZ :  %4.2f #pm %4.2f",(Final_N_bkg_TTZ.getVal()), (Final_N_bkg_TTZ.getError() )));
    pt3->AddText( Form("WZ+jets :  %4.2f #pm %4.2f",(Final_N_bkg_WZ.getVal()), (Final_N_bkg_WZ.getError() )));
    pt3->AddText( Form("ZZ :  %4.2f #pm %4.2f",(Final_N_bkg_ZZ.getVal()), (Final_N_bkg_ZZ.getError() )));
    pt3->AddText( Form("tZq :  %4.2f #pm %4.2f",(Final_N_bkg_tZq.getVal()), (Final_N_bkg_tZq.getError() )));
    pt3->AddText( Form("Z+jets :  %4.2f #pm %4.2f",(Final_N_bkg_DY.getVal()), (Final_N_bkg_DY.getError() )));
    pt3->AddText( Form("other bkgs:  %4.2f #pm %4.2f",(Final_N_bkg_other.getVal()), (Final_N_bkg_other.getError() )));
    pt3->Draw();

    c1->SaveAs("MVA_mmm.png");

    cout << "Exp_Signal : " << Final_sig->Integral() << endl;
    cout << "Signal_no : " << Final_N_sig.getVal() << endl;
    cout << "Fit_WZ : " << Final_N_bkg_WZ.getVal() << endl;
    cout << "Fit_ZZ : " << Final_N_bkg_ZZ.getVal() << endl;
    cout << "Fit_DY : " << Final_N_bkg_DY.getVal() << endl;
    cout << "Fit_ttbar : " << Final_N_bkg_ttbar.getVal() << endl;
    cout << "WZ_no : " << WZ_no << endl;
    cout << "ZZ_no : " << ZZ_no << endl;
    cout << "DY_no : " << DY_no << endl;
    cout << "ttbar+jets : " << ttbar_No << endl;
    cout << "Exp_WZ : " << Final_bkg_WZ->Integral() << endl;
    cout << "Exp_ZZ : " << Final_bkg_ZZ->Integral() << endl;
    cout << "Exp_DY : " << Final_bkg_DY->Integral() << endl;
    cout << "Exp_ttbar : " << Final_bkg_ttbar->Integral() << endl;
    cout << "Exp_TTZ : " << Final_N_TTZ << endl;
    cout << "Exp_tZq : " << Final_N_tZq << endl;
    cout << "Exp_other : " << Final_N_other << endl;
  
    cout << "Fit_TTZ : " << Final_N_bkg_TTZ.getVal() << endl; 
    cout << "Fit_tZq : " << Final_N_bkg_tZq.getVal() << endl; 
    cout << "Fit_Other : " << Final_N_bkg_other.getVal() << endl; 
    cout << "Data : " << Final_data_shape->Integral() << endl; 
}
