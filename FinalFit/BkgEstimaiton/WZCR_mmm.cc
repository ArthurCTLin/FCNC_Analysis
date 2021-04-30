{
    //TFile *fin1 = new TFile("./sample/2017/hist_w_mt_mmm.root");
    TFile *fin1 = new TFile("../sample/2017_Zct/Central/hist_w_mt_mmm.root");
    
    TH1D *sig = (TH1D*)fin1->Get("WZ");
    TH1D *bkg1 = (TH1D*)fin1->Get("ZZ");
    TH1D *bkg2 = (TH1D*)fin1->Get("DY");
    TH1D *data_shape = (TH1D*)fin1->Get("data");
    //std::cout << "sig event : " << sig->Integral() << ", bkg event : " << bkg->Integral() << ", data event : " << data_shape->Integral() << "\n";

    using namespace RooFit;
   
//    sig->Rebin(2);
//    bkg1->Rebin(2);
//    //bkg2->Rebin(2);
//    data_shape->Rebin(2);

    RooRealVar N_sig("N_sig", "N_sig", 10, -50, 3000);   
    RooRealVar N_bkg1("N_bkg1", "N_bkg1", 20, -50, 3000);
    RooRealVar N_bkg2("N_bkg2", "N_bkg2", 20, -50, 3000);
     
    double WZ_exp = sig->Integral();
    double ZZ_exp = bkg1->Integral();
    double DY_exp = bkg2->Integral();
    RooGaussian constraint_WZ("constraint_WZ","constraint_WZ",N_sig,RooConst(WZ_exp),RooConst(sqrt(WZ_exp))) ;
    RooGaussian constraint_ZZ("constraint_ZZ","constraint_ZZ",N_bkg1,RooConst(ZZ_exp),RooConst(sqrt(ZZ_exp))) ;
    RooGaussian constraint_DY("constraint_DY","constraint_DY",N_bkg2,RooConst(DY_exp),RooConst(sqrt(DY_exp))) ;
    RooArgSet gausConstraint(constraint_WZ, constraint_ZZ, constraint_DY);
    
    RooRealVar WTransmass("WTransmass", "WTransmass", 0., 300.);
    RooDataHist binsig("binsig", "binsig", RooArgList(WTransmass), sig);
    RooDataHist binbkg1("binbkg1", "binbkg1", RooArgList(WTransmass), bkg1);
    RooDataHist binbkg2("binbkg2", "binbkg2", RooArgList(WTransmass), bkg2);
    RooDataHist bindata("bindata", "bindata", RooArgList(WTransmass), data_shape);

    RooHistPdf sig_pdf("sig_pdf", "sig_pdf", RooArgList(WTransmass), binsig);
    RooHistPdf bkg_pdf1("bkg_pdf1", "bkg_pdf1", RooArgList(WTransmass), binbkg1);
    RooHistPdf bkg_pdf2("bkg_pdf2", "bkg_pdf2", RooArgList(WTransmass), binbkg2);

    RooAddPdf total_pdf("total_pdf", "total_pdf", RooArgList(sig_pdf, bkg_pdf1, bkg_pdf2), RooArgList(N_sig, N_bkg1, N_bkg2));
    total_pdf.fitTo(bindata, ExternalConstraints(gausConstraint), Extended(true), Minos(true), SumW2Error(kTRUE));//, Extended(true));

    RooPlot *frame = WTransmass.frame();
    bindata.plotOn(frame);
    total_pdf.plotOn(frame);
    total_pdf.plotOn(frame, Components(sig_pdf) , LineStyle(2), LineColor(kRed));

    TCanvas *c1 = new TCanvas("c1", "Transverse Mass of W", 10,10,600,550);
    frame->SetMaximum(frame->GetMaximum()*1.5);
    frame->SetTitle("");
    frame->GetXaxis()->SetTitle("Transverse Mass of W [GeV/c^{2}]");
    frame->Draw();
    RooFitResult *result = total_pdf.fitTo(bindata,ExternalConstraints(gausConstraint), Save(true), Extended(true), Minos(true), SumW2Error(kTRUE));
    cout << "The Result Value of the fitting : " << result->status() << endl;

    TPaveText* pt = new TPaveText(.50, .75, .90, .90, "NDC" );
    pt->SetTextFont(43);
    pt->SetTextSize(18);
    pt->SetFillColorAlpha( 0, 0 );
    pt->AddText( Form("WZ+jets :  %3.2f #pm %3.2f", N_sig.getVal(), N_sig.getError() ));
    pt->AddText( Form("ZZ :  %4.2f #pm %4.2f",(N_bkg1.getVal()), (N_bkg1.getError() )));
    pt->AddText( Form("Z+jets :  %4.2f #pm %4.2f",(N_bkg2.getVal()), (N_bkg2.getError() )));
    pt->Draw();

    c1->SaveAs("./plot/2017/WZCR_mmm.png");

}
