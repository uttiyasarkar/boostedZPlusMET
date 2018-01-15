// ROOT libraries
//#include "CMS_lumi.cc"
#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "THStack.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooBernstein.h"
#include "RooWorkspace.h"

#include "TCanvas.h"

// STL libraries
#include <iostream>
#include <cassert>

using namespace RooFit;
using namespace std;

//int main( int argc , char** argv ){
void fitSignalBkg(){
    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
    
    TFile* inputFile =new TFile("SkimFileMass.root", "READ");
    //BKg Shapes:
    OtherTree=(TTree*)inputFile->Get("Other");
    ZJetsTree=(TTree*)inputFile->Get("ZJets");
    WJetsTree=(TTree*)inputFile->Get("WJets");
    SnglTTree=(TTree*)inputFile->Get("SnglT");
    TTBarTTree=(TTree*)inputFile->Get("TT");
    QCDTree=(TTree*)inputFile->Get("QCD");
    
    TH1D*PrunedMassZBkg=new TH1D("PrunedMassZBkg", "Pruned Mass [GeV]", 20,50,250);
    TH1D*PrunedMassWBkg=new TH1D("PrunedMassWBkg", "Pruned Mass [GeV]", 20,50,250);
    TH1D*PrunedMassTTBarBkg=new TH1D("PrunedMassTTBarBkg", "Pruned Mass [GeV]", 20,50,250);
    TH1D*PrunedMassQCDBkg=new TH1D("PrunedMassQCDBkg", "Pruned Mass [GeV]", 20,50,250);

    RooRealVar* jetMass = new RooRealVar("jetMass","Pruned Jet Mass [GeV]",100.,50.,250.);
    RooRealVar alpha("alpha", "exponential", 0, -0.1, 1);

    ZJetsTree->Draw("PrunedMass1>>PrunedMassZBkg", "(MET>300  && MET<500 && Jet1_tau2overtau1<0.55 && Jet2_tau2overtau1<0.55 && BTags==0)*Evtweight");
    WJetsTree->Draw("PrunedMass1>>PrunedMassWBkg", "(MET>300  && MET<500 && Jet1_tau2overtau1<0.55 && Jet2_tau2overtau1<0.55 && BTags==0)*Evtweight");
    TTBarTTree->Draw("PrunedMass1>>PrunedMassTTBarBkg", "(MET>300  && MET<500 && Jet1_tau2overtau1<0.55 && Jet2_tau2overtau1<0.55 && BTags==0)*Evtweight");
    QCDTree->Draw("PrunedMass1>>PrunedMassQCDBkg", "(MET>300  && MET<500 && Jet1_tau2overtau1<0.55 && Jet2_tau2overtau1<0.55 && BTags==0)*Evtweight");

    THStack*hstack=new THStack("hstack","");
    
    
    PrunedMassQCDBkg->SetFillColor(kGray);
    PrunedMassWBkg->SetFillColor(kBlue);
    PrunedMassZBkg->SetFillColor(kGreen+1);
    PrunedMassTTBarBkg->SetFillColor(kCyan);
    leg=new TLegend(0.5488722,0.6825806,0.914787,0.8748387,NULL,"brNDC");
    leg->AddEntry(PrunedMassQCDBkg, "QCD ","F");
    leg->AddEntry(PrunedMassTTBarBkg, "TTJets ","F");
    leg->AddEntry(PrunedMassWBkg, "W+Jets ","F");
    leg->AddEntry(PrunedMassZBkg, "Z+Jets ","F");
    
    hstack->Add(PrunedMassQCDBkg);
    hstack->Add(PrunedMassWBkg);
    hstack->Add(PrunedMassTTBarBkg);
    hstack->Add(PrunedMassZBkg);
    TH1D*TotalBkg=(TH1D*)hstack->GetStack()->Last();
    hstack->Draw("hist");
    //PrunedMassZBkg->Draw();
    RooDataHist* MC_bkg = new RooDataHist("MC_bkg","MC_bkg",RooArgList(*jetMass),TotalBkg);
    RooExponential exp("exp", "", *jetMass, alpha);
    RooRealVar* p1 = new RooRealVar("p1","p1",0.5,0.0,1.0);
    RooRealVar* p2 = new RooRealVar("p2","p2",0.5,0.0,1.0);
    RooRealVar* p3 = new RooRealVar("p3","p3",0.5,0.0,1.0);
    RooRealVar* p4 = new RooRealVar("p4","p4",0.5,0.0,1.0);
    RooBernstein* poly = new RooBernstein("poly","poly",*jetMass,RooArgList(*p1,*p2,*p3,*p4));
    poly.fitTo(*MC_bkg);
    RooPlot* frame = jetMass->frame(Title("Imported TH1 with Poisson error bars")) ;
    MC_bkg->plotOn(frame, DataError(RooAbsData::SumW2)) ;
    poly->plotOn(frame);
    frame->Draw("same");
    TCanvas* can = new TCanvas("can","can",1000,500);
    can->Divide(2,1);
    can->cd(1);
    hstack->Draw("hist");
    frame->Draw("same");
    leg->Draw();
   // return;
    TH1D*PrunedMassZBkgBtags=new TH1D("PrunedMassZBkgBtags", "Pruned Mass [GeV]", 20,50,250);
    TH1D*PrunedMassWBkgBtags=new TH1D("PrunedMassWBkgBtags", "Pruned Mass [GeV]", 20,50,250);
    TH1D*PrunedMassTTBarBkgBtags=new TH1D("PrunedMassTTBarBkgBtags", "Pruned Mass [GeV]", 20,50,250);
    TH1D*PrunedMassQCDBkgBtags=new TH1D("PrunedMassQCDBkgBtags", "Pruned Mass [GeV]", 20,50,250);
    
    can->cd(2);
    ZJetsTree->Draw("PrunedMass1>>PrunedMassZBkgBtags", "(MET>300  && MET<500 && Jet1_tau2overtau1<0.55 && Jet2_tau2overtau1<0.55 && BTags!=0)*Evtweight");
    WJetsTree->Draw("PrunedMass1>>PrunedMassWBkgBtags", "(MET>300  && MET<500 && Jet1_tau2overtau1<0.55 && Jet2_tau2overtau1<0.55 && BTags!=0)*Evtweight");
    TTBarTTree->Draw("PrunedMass1>>PrunedMassTTBarBkgBtags", "(MET>300  && MET<500 && Jet1_tau2overtau1<0.55 && Jet2_tau2overtau1<0.55 && BTags!=0)*Evtweight");
    QCDTree->Draw("PrunedMass1>>PrunedMassQCDBkgBtags", "(MET>300  && MET<500 && Jet1_tau2overtau1<0.55 && Jet2_tau2overtau1<0.55 && BTags!=0)*Evtweight");
    
    THStack*hstackbtags=new THStack("hstackbtags","");
    
    
    PrunedMassQCDBkgBtags->SetFillColor(kGray);
    PrunedMassWBkgBtags->SetFillColor(kBlue);
    PrunedMassZBkgBtags->SetFillColor(kGreen+1);
    PrunedMassTTBarBkgBtags->SetFillColor(kCyan);
    leg=new TLegend(0.5488722,0.6825806,0.914787,0.8748387,NULL,"brNDC");
    leg->AddEntry(PrunedMassQCDBkgBtags, "QCD ","F");
    leg->AddEntry(PrunedMassTTBarBkgBtags, "TTJets ","F");
    leg->AddEntry(PrunedMassWBkgBtags, "W+Jets ","F");
    leg->AddEntry(PrunedMassZBkgBtags, "Z+Jets ","F");
    
    hstackbtags->Add(PrunedMassQCDBkgBtags);
    hstackbtags->Add(PrunedMassWBkgBtags);
    hstackbtags->Add(PrunedMassTTBarBkgBtags);
    hstackbtags->Add(PrunedMassZBkgBtags);
    can->cd(2);

    hstackbtags->Draw("hist");
    
    RooRealVar* mean = new RooRealVar("mean","mean",80.,60.,100.);
    RooRealVar* sigma = new RooRealVar("sigma","sigma",8.,0.,20.);
    RooGaussian* gauss = new RooGaussian("gauss","gauss",*jetMass,*mean,*sigma);
    
    TCanvas* can2 = new TCanvas("can2","can2",500,500);
    T5HH1500Tree=(TTree*)inputFile->Get("T5HH1500");
    TH1D*PrunedMassT5ZZ1700=new TH1D("PrunedMassT5ZZ1700", "Pruned Mass [GeV]", 15,75,105);

    T5HH1500Tree->Draw("PrunedMass1>>PrunedMassT5ZZ1700", "(PrunedMass1>75 && PrunedMass1<105 && MET>300  && MET<500 && Jet1_tau2overtau1<0.55 && Jet2_tau2overtau1<0.55 && BTags==0)");
    
    RooDataHist* MC_T5ZZ1700 = new RooDataHist("MC_T5ZZ1700","MC_T5ZZ1700",RooArgList(*jetMass),PrunedMassT5ZZ1700);
    MC_T5ZZ1700->Draw();
    gauss->fitTo(*MC_T5ZZ1700);
    RooPlot* frame2 = jetMass->frame(Title("Imported TH1 with Poisson error bars")) ;
    MC_T5ZZ1700->plotOn(frame2, DataError(RooAbsData::SumW2)) ;
    gauss->plotOn(frame2);
    frame2->Draw("same");
}

