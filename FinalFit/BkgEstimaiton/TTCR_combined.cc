
void  TTCR_combined(){
    //TFile *fin1 = new TFile("./temp/TTCR_ttbar_total.root");
    TFile *fin1 = new TFile("./WZCR/sample/2017/Zmass_combine.root");
    TH1D *ttbar = (TH1D*)fin1->Get("ttbar");
    TH1D *DY = (TH1D*)fin1->Get("DY");
    TH1D *bkg = (TH1D*)fin1->Get("TTCR_other");

    double n_ttbar = ttbar->Integral();
    double n_DY = DY->Integral();
    double n_bkg = bkg->Integral();

    ttbar->Scale(1./n_ttbar);
    DY->Scale(1./n_DY);
    bkg->Scale(1./n_bkg);
    TCanvas *c1 = new TCanvas("c1","",600,600);
    //ttbar->Rebin(5);
    //DY->Rebin(5);
    //bkg->Rebin(5);
    ttbar->SetFillColor(0);
    DY->SetFillColor(0);
    bkg->SetFillColor(0);
    ttbar->SetStats(false);
    ttbar->SetLineColor(kRed);
    ttbar->SetTitle("");
    ttbar->GetXaxis()->SetTitle("Invariant Mass of Z [GeV/c^{2}]");
    ttbar->GetXaxis()->SetLabelSize(0.035);
    ttbar->GetYaxis()->SetTitle("1/N.");
    ttbar->GetYaxis()->SetTitleSize(0.045);
    ttbar->GetYaxis()->SetTitleOffset(0.95);
    ttbar->GetYaxis()->SetLabelSize(0.035);
    ttbar->SetMaximum(bkg->GetMaximum()*1.5);
    ttbar->Draw("HIST");
    DY->SetLineColor(kAzure+8);
    DY->Draw("same HIST");
    bkg->SetLineColor(kBlack);
    bkg->Draw("same HIST");
    
    TLegend *leg1 = new TLegend(0.65,0.75,0.88,0.88);
    leg1->AddEntry(ttbar,"ttbar+jets","L");
    leg1->AddEntry(DY,"DY", "L");
    leg1->AddEntry(bkg,"other bkg", "L");
    TLine *L1 = new TLine(70,0,70,bkg->GetMaximum()*1.5);
    TLine *L2 = new TLine(110,0,110,bkg->GetMaximum()*1.5);

    L1->SetLineColor(kAzure-2);
    L2->SetLineColor(kAzure-2);
    L1->SetLineWidth(3);
    L2->SetLineWidth(3);
    L1->Draw("Same");
    L2->Draw("Same");

    leg1->Draw();
    c1->SaveAs("./plot_94X/2017/TTCR.png");
}
