#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "TMath.h"
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
#include "TLegend.h"
#include "TCanvas.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooLandau.h"
#include "RooFFTConvPdf.h"
// STL libraries
#include <iostream>
#include <cassert>
#include "TLinearFitter.h"
using namespace RooFit;
using namespace std;

void fitSignalBkg(){
    
    TFile* inputFile =new TFile("SkimFileMass.root", "READ");
    OtherTree=(TTree*)inputFile->Get("Other");
    ZJetsTree=(TTree*)inputFile->Get("ZJets");
    WJetsTree=(TTree*)inputFile->Get("WJets");
    SnglTTree=(TTree*)inputFile->Get("SnglT");
    TTBarTTree=(TTree*)inputFile->Get("TT");
    QCDTree=(TTree*)inputFile->Get("QCD");
    T5HH1300Tree=(TTree*)inputFile->Get("T5HH1300");
    T5HH1700Tree=(TTree*)inputFile->Get("T5HH1700");
    
    TH1D*PrunedMassZBkg=new TH1D("PrunedMassZBkg", "Pruned Mass [GeV]", 30,50,200);
    TH1D*PrunedMassWBkg=new TH1D("PrunedMassWBkg", "Pruned Mass [GeV]", 30,50,200);
    TH1D*PrunedMassTTBarBkg=new TH1D("PrunedMassTTBarBkg", "Pruned Mass [GeV]", 30,50,200);
    TH1D*PrunedMassQCDBkg=new TH1D("PrunedMassQCDBkg", "Pruned Mass [GeV]", 30,50,200);
    TH1D*PrunedMassT5HH1300Sig=new TH1D("PrunedMassT5HH1300Sig", "Pruned Mass [GeV]", 30,50,200);
    TH1D*PrunedMassT5HH1700Sig=new TH1D("PrunedMassT5HH1700Sig", "Pruned Mass [GeV]", 30,50,200);

    PrunedMassZBkg->Sumw2(kTRUE);
    PrunedMassTTBarBkg->Sumw2(kTRUE);
    PrunedMassT5HH1300Sig->Sumw2(kTRUE);
    PrunedMassT5HH1700Sig->Sumw2(kTRUE);

    ZJetsTree->Draw("PrunedMass1>>PrunedMassZBkg", "(MET>300)*Evtweight");
    WJetsTree->Draw("PrunedMass1>>PrunedMassWBkg", "(MET>300)*Evtweight");
    TTBarTTree->Draw("PrunedMass1>>PrunedMassTTBarBkg","(MET>300)*Evtweight");
    QCDTree->Draw("PrunedMass1>>PrunedMassQCDBkg", "(MET>300)*Evtweight");
    T5HH1300Tree->Draw("PrunedMass1>>PrunedMassT5HH1300Sig", "(MET>300)*Evtweight");
    T5HH1700Tree->Draw("PrunedMass1>>PrunedMassT5HH1700Sig", "(MET>300)*Evtweight");
    
    
    cout<<"T5/hh1300------------------"<<PrunedMassT5HH1300Sig->Integral()<<endl;
    cout<<"T5/hh1700------------------"<<PrunedMassT5HH1700Sig->Integral()<<endl;
    cout<<"T5/QCD------------------"<<PrunedMassQCDBkg->Integral()<<endl;
    cout<<"T5/TTBar------------------"<<PrunedMassTTBarBkg->Integral()<<endl;
    cout<<"T5/WBkg------------------"<<PrunedMassWBkg->Integral()<<endl;
    cout<<"T5/ZBkg------------------"<<PrunedMassZBkg->Integral()<<endl;



}
