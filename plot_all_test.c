// #include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"

{
    // TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
    // canvas->SaveAs("all.root");
    TCanvas *canvas = new TCanvas("c1", "Canvas", 800, 600);
    canvas->cd();
    gStyle->SetOptStat(000000);
    
    TFile *f = new TFile("/user/home/ms23570/work/sim_alpha_project/3OctwithoutDFIceisWater.root");
    TTree *tr = (TTree*)f->Get("Uper&underTissue;1");
    // TTree *tr = (TTree*)f->Get("Ice;1");

    
    tr->Draw("Event>>htemp", "");





    tr->SetLineColor(3);
    TH1F *htemp = (TH1F*)gDirectory->Get("htemp");

    htemp->Scale(7000000/htemp->Integral());

    
    htemp->SetLineColor(1);
  


    htemp->SetTitle("Alpha travel in water");
    htemp->GetXaxis()->SetTitle("prekineticEnergy");
    htemp->GetYaxis()->SetTitle("noumber of alpha step");

    htemp->Draw("hist");
   

    

    TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9); // Adjust position as needed
    leg->AddEntry(htemp, "Ra224", "l");





    
    leg->Draw();
    canvas->SaveAs("./prekineticEnergy.root");
}