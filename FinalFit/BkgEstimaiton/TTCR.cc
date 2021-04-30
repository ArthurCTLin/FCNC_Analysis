{
    //TFile *fin = new TFile("../../get_BDT_shape_DM.root");
    //TFile *fin1 = new TFile("./WZCR/sample/2016/Zmass_combine.root");
    TFile *fin1 = new TFile("./sample/2016_Zct/Central/Zmass_combine.root");
    TH1D *sig = (TH1D*)fin1->Get("ttbar");
    TH1D *data_shape = (TH1D*)fin1->Get("data");

    using namespace RooFit;

    RooRealVar N_sig("N_sig", "N_sig", 10, -50, 5000);   
    RooRealVar N_bkg("N_bkg", "N_bkg", 20, -50, 1000);
    
    RooRealVar Zmass("Zmass", "Zmass", 30., 150.);
    RooDataHist binsig("binsig", "binsig", RooArgList(Zmass), sig);
    RooDataHist bindata("bindata", "bindata", RooArgList(Zmass), data_shape);

    RooHistPdf sig_pdf("sig_pdf", "sig_pdf", RooArgList(Zmass), binsig);
    RooAddPdf total_pdf("total_pdf", "total_pdf", RooArgList(sig_pdf), RooArgList(N_sig));

    //cout << "Side Band : " << sig->Integral(1,4)+ sig->Integral(11,15) << endl;
    //cout << "Signal Region : " << sig->Integral(8,9) << endl;
    Zmass.setRange("left",30.,70.);
    Zmass.setRange("right",110.,150.);
    total_pdf.fitTo(bindata,Range("left,right"), Minos(true), Extended(true));

    RooPlot *frame2 = Zmass.frame();
    bindata.plotOn(frame2);
    total_pdf.plotOn(frame2);
   
    Zmass.setRange("middle", 82.5, 97.5);
    Zmass.setRange("middle2", 70., 110);
    RooAbsReal* sigregion_sig = total_pdf.createIntegral(Zmass, NormSet(Zmass), Range("middle"));
    RooAbsReal* sigregion_sig2 = total_pdf.createIntegral(Zmass, NormSet(Zmass), Range("middle2"));
    cout << "Expected in signal region : " << sigregion_sig->getVal()*sig->Integral() << endl;
    cout << "Expected in outside 70~110 : " << sig->Integral()-sigregion_sig2->getVal()*sig->Integral() << endl;
    cout << "ttbar+jets in signal region(+/-7.5) : " << sigregion_sig->getVal()*N_sig.getVal() << endl;
    cout << "ttbar+jets in sideband region : " << N_sig.getVal()-sigregion_sig->getVal()*N_sig.getVal() << endl;
    cout << "ttbar+jets in sideband region(outside 70~110) : " << N_sig.getVal()-sigregion_sig2->getVal()*N_sig.getVal() << endl;

    RooFitResult *result2 = total_pdf.fitTo(bindata, Range("left,right"), Save(true), Extended(true), Minos(true));
    cout << "The Result Value of the fitting : " << result2->status() << endl;

    TCanvas *c2 = new TCanvas("c2", "Invariant Mass of Z ", 10,10,600,550);

    c2->cd();
    frame2->SetMaximum(data_shape->GetMaximum()*1.5);
    frame2->SetTitle("");
    frame2->GetXaxis()->SetTitle("Invariant Mass of Z [GeV/c^{2}]");
    frame2->Draw();

    TPaveText* pt = new TPaveText(.50, .75, .90, .90, "NDC" );
    pt->SetTextFont(43);
    pt->SetTextSize(18);
    pt->SetFillColorAlpha( 0, 0 );
    //pt->AddText( Form("ttbar+jets :  %3.3f #pm %3.3f", N_sig.getVal(), N_sig.getError() ));
    pt->AddText( Form("ttbar+jets :  %3.2f #pm %3.2f",(N_sig.getVal()-sigregion_sig2->getVal()*N_sig.getVal()), N_sig.getError() ));
    //pt->AddText( Form("other bkgs :  %4.3f #pm %4.3f",(N_bkg.getVal()), (N_bkg.getError() )));
    TLine *L1 = new TLine(70,0,70,data_shape->GetMaximum()*1.5); 
    TLine *L2 = new TLine(110,0,110,data_shape->GetMaximum()*1.5);
    L1->SetLineWidth(3);
    L2->SetLineWidth(3);
    L1->SetLineColor(kRed);
    L2->SetLineColor(kRed);
    L1->Draw("Same");
    L2->Draw("Same");
    pt->Draw();
    
    c2->SaveAs("./plot_94X/2016/Zmass_sideband.png");

}
