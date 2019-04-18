//#include "tdrstyle.C"
#include "CMS_lumi.C"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooMCStudy.h"
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

using namespace RooFit;
using namespace std;

//int main( int argc , char** argv ){
void PullSig1300Cheby2()
{
//gROOT->LoadMacro("tdrstyle.C");
gROOT->LoadMacro("CMS_lumi.C");
//  setTDRStyle();
gStyle->SetOptTitle(0);  
  TFile* inputFile =new TFile("SkimFileMass.root", "READ");
    //BKg Shapes:
  OtherTree=(TTree*)inputFile->Get("Other");
  ZJetsTree=(TTree*)inputFile->Get("ZJets");
  WJetsTree=(TTree*)inputFile->Get("WJets");
  SnglTTree=(TTree*)inputFile->Get("SnglT");
  TTBarTTree=(TTree*)inputFile->Get("TT");
  QCDTree=(TTree*)inputFile->Get("QCD");
  T5HH1300Tree=(TTree*)inputFile->Get("T5HH1300");
  T5HH1700Tree=(TTree*)inputFile->Get("T5HH1700");
  T5HH1100Tree=(TTree*)inputFile->Get("T5HH1100");
  T5HH1200Tree=(TTree*)inputFile->Get("T5HH1200");
  T5HH1400Tree=(TTree*)inputFile->Get("T5HH1400");
  T5HH1500Tree=(TTree*)inputFile->Get("T5HH1500");
  T5HH1600Tree=(TTree*)inputFile->Get("T5HH1600");
  T5HH1800Tree=(TTree*)inputFile->Get("T5HH1800");
  T5HH1900Tree=(TTree*)inputFile->Get("T5HH1900");
  T5HH2000Tree=(TTree*)inputFile->Get("T5HH2000");
  T5HH2100Tree=(TTree*)inputFile->Get("T5HH2100");
  T5HH1000Tree=(TTree*)inputFile->Get("T5HH1000");
////////TH1 candidates 
  TH1D*PrunedMassSnglT=new TH1D("PrunedMassSnglT", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassOther=new TH1D("PrunedMassOther", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassZBkg=new TH1D("PrunedMassZBkg", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassWBkg=new TH1D("PrunedMassWBkg", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassTTBarBkg=new TH1D("PrunedMassTTBarBkg", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassQCDBkg=new TH1D("PrunedMassQCDBkg", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1300Sig=new TH1D("PrunedMassT5HH1300Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1700Sig=new TH1D("PrunedMassT5HH1700Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1000Sig=new TH1D("PrunedMassT5HH1000Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1100Sig=new TH1D("PrunedMassT5HH1100Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1200Sig=new TH1D("PrunedMassT5HH1200Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1400Sig=new TH1D("PrunedMassT5HH1400Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1500Sig=new TH1D("PrunedMassT5HH1500Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1600Sig=new TH1D("PrunedMassT5HH1600Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1800Sig=new TH1D("PrunedMassT5HH1800Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH1900Sig=new TH1D("PrunedMassT5HH1900Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH2000Sig=new TH1D("PrunedMassT5HH2000Sig", "Pruned Mass [GeV]", 50.,50.,200.);
  TH1D*PrunedMassT5HH2100Sig=new TH1D("PrunedMassT5HH2100Sig", "Pruned Mass [GeV]", 50.,50.,200.);

  PrunedMassSnglT->Sumw2(kTRUE);
  PrunedMassOther->Sumw2(kTRUE);
  PrunedMassQCDBkg->Sumw2(kTRUE);
  PrunedMassWBkg->Sumw2(kTRUE);
  PrunedMassZBkg->Sumw2(kTRUE);
  PrunedMassTTBarBkg->Sumw2(kTRUE);
  PrunedMassT5HH1000Sig->Sumw2(kTRUE);
  PrunedMassT5HH1100Sig->Sumw2(kTRUE);
  PrunedMassT5HH1200Sig->Sumw2(kTRUE);
  PrunedMassT5HH1300Sig->Sumw2(kTRUE);
  PrunedMassT5HH1400Sig->Sumw2(kTRUE);
  PrunedMassT5HH1500Sig->Sumw2(kTRUE);
  PrunedMassT5HH1600Sig->Sumw2(kTRUE);
  PrunedMassT5HH1700Sig->Sumw2(kTRUE);
  PrunedMassT5HH1800Sig->Sumw2(kTRUE);
  PrunedMassT5HH1900Sig->Sumw2(kTRUE);
  PrunedMassT5HH2000Sig->Sumw2(kTRUE);
  PrunedMassT5HH2100Sig->Sumw2(kTRUE);

  OtherTree->Draw("PrunedMass1>>PrunedMassOther", "(HT>500 && MET>300 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
    SnglTTree->Draw("PrunedMass1>>PrunedMassSnglT", "(HT>500 && MET>300 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  ZJetsTree->Draw("PrunedMass1>>PrunedMassZBkg", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  WJetsTree->Draw("PrunedMass1>>PrunedMassWBkg", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  TTBarTTree->Draw("PrunedMass1>>PrunedMassTTBarBkg","(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  QCDTree->Draw("PrunedMass1>>PrunedMassQCDBkg", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1300Tree->Draw("PrunedMass1>>PrunedMassT5HH1300Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1700Tree->Draw("PrunedMass1>>PrunedMassT5HH1700Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1000Tree->Draw("PrunedMass1>>PrunedMassT5HH1000Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1100Tree->Draw("PrunedMass1>>PrunedMassT5HH1100Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1200Tree->Draw("PrunedMass1>>PrunedMassT5HH1200Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1400Tree->Draw("PrunedMass1>>PrunedMassT5HH1400Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1500Tree->Draw("PrunedMass1>>PrunedMassT5HH1500Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1600Tree->Draw("PrunedMass1>>PrunedMassT5HH1600Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1800Tree->Draw("PrunedMass1>>PrunedMassT5HH1800Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH1900Tree->Draw("PrunedMass1>>PrunedMassT5HH1900Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH2000Tree->Draw("PrunedMass1>>PrunedMassT5HH2000Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  T5HH2100Tree->Draw("PrunedMass1>>PrunedMassT5HH2100Sig", "(MET>300 && HT>500 && JetPt1>300 && JetPt2>200 && PrunedMass1>50 && PrunedMass1<200 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");
  
  THStack*hstack=new THStack("hstack","");
  PrunedMassQCDBkg->SetFillColor(kGray+1);
  PrunedMassOther->SetFillColor(kRed+2);
  PrunedMassSnglT->SetFillColor(kYellow-3);
  PrunedMassWBkg->SetFillColor(kBlue+1);
  PrunedMassZBkg->SetFillColor(kGreen+1);
  PrunedMassTTBarBkg->SetFillColor(kCyan+1);
  PrunedMassT5HH1300Sig->SetLineColor(kRed+1);
  PrunedMassT5HH1700Sig->SetLineColor(kBlue+1);

  int W = 600;
  int H = 600;
  int H_ref = 600;
  int W_ref = 600;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;
  TLegend *leg=new TLegend(0.5488722,0.5825806,0.814787,0.7748387,NULL,"brNDC");
    leg->AddEntry(PrunedMassTTBarBkg, "TTJets ","F");
    leg->AddEntry(PrunedMassWBkg, "W+Jets ","F");
    leg->AddEntry(PrunedMassZBkg, "Z+Jets ","F");
    leg->AddEntry(PrunedMassT5HH1300Sig, "Sig.+Bkg. Fit ","L");
    leg->AddEntry(PrunedMassT5HH1700Sig, "Bkg. Fit ","L");
    
    gStyle->SetLegendBorderSize(0);
    gStyle->SetLegendFillColor(0);
    gStyle->SetLegendFont(10);
  
  //hstack->Add(PrunedMassOther);
  //hstack->Add(PrunedMassSnglT);
  hstack->Add(PrunedMassTTBarBkg);
  hstack->Add(PrunedMassWBkg);
  hstack->Add(PrunedMassZBkg);
  TH1D*TotalBkg=(TH1D*)hstack->GetStack()->Last();
  
  RooRealVar jetMass("jetMass","Jet Mass [GeV]",50.,200.);
  jetMass.setRange("Signal",70., 100.);
  jetMass.setRange("Sideband1",50., 70.);
  jetMass.setRange("Sideband2",100., 200.);
  
  RooDataHist MC_bkg("MC_bkg","MC_bkg",jetMass,Import(*TotalBkg));
  RooDataHist MC_sig("MC_sig","MC_sig",jetMass,Import(*PrunedMassT5HH1700Sig));
  RooRealVar a1("a1","a1",-0.8591);
  RooRealVar a2("a2","a2",0.023);
  //RooRealVar a1("a1","a1",-0.8,-10.,10.);
  //RooRealVar a2("a2","a2",-0.01,-10.,10.);
 RooChebychev bkg("bkg", "", jetMass, RooArgList(a1,a2));
 RooFitResult *r =  bkg.fitTo(MC_bkg,Range("Sideband1,Sideband2"),Save());
  //integral of mass in signal region:
  RooAbsReal*BkginSR=bkg.createIntegral(jetMass, NormSet(jetMass), Range("Signal"));

//-------------fixing parameters of Signal shape----------------------//  
  RooRealVar mean("mean","mean",83.6);
  RooRealVar sigma("sigma","sigma",5.1);
  RooRealVar width("width","width",9.2);
  RooVoigtian voigt("voigt","voigt",jetMass,mean,width,sigma);
//RooVoigtian sig("sig","sig",jetMass,mean,width,sigma);
//  RooRealVar s1("s1","a1",0.,-50.,50.);
  RooRealVar s1("s1","s1",-0.41);
  RooChebychev cheby1sig("cheby1sig","Polynomial part", jetMass, RooArgList(s1));
  RooRealVar cheby1sigfrac("polyfrac","fraction of chebhchev",0.05);
//  RooRealVar cheby1sigfrac("polyfrac","fraction of chebhchev",0.5,0.,1.0);
  RooAddPdf sig ("sig","signal",RooArgList(cheby1sig,voigt),cheby1sigfrac);
  bkg.fitTo(MC_bkg);
  //sig.fitTo(MC_sig);

  //integral of mass in signal region:
  RooPlot* frame = jetMass.frame();
  //MC_bkg.plotOn(frame,DataError(RooAbsData::SumW2)) ;
  //bkg.plotOn(frame,VisualizeError(*r, RooArgSet(a1,a2),2),FillColor(kYellow),FillStyle(3001));
  bkg.plotOn(frame,LineColor(kBlack));
  bkg.plotOn(frame) ;
  bkg.paramOn(frame,Layout(0.9, 0.4, 0.9));
  //MC_sig.plotOn(frame);
  //sig.plotOn(frame,LineColor(kYellow));
  //sig.plotOn(frame,Components(voigt),LineColor(kRed));
  //sig.plotOn(frame,Components(cheby1sig),LineColor(kOrange));
  //sig.paramOn(frame,LineColor(kBlue),Layout(0.9, 0.4, 0.9));

  cout << "***************************************************************************************************************************************************************************************************************************8 Bkg Integral "<< BkginSR->getVal()*TotalBkg->Integral() << endl ; 

  TCanvas *c1=new TCanvas("c1","",600,600) ;
  c1->SetFillColor(0);c1->SetBorderMode(0);c1->SetFrameFillStyle(0);c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L/W );c1->SetRightMargin( R/W );c1->SetTopMargin( T/H );
  c1->SetBottomMargin( B/H );c1->SetTickx(0);c1->SetTicky(0);c1->Draw();
  c1->Update();  
  hstack->Draw("hist");
  frame->Draw("hist same");

  hstack->GetXaxis()->SetTitle("Lead m_{J} [GeV]");
  hstack->GetYaxis()->SetLabelSize(0.023);
  hstack->GetYaxis()->SetTitleSize(0.04);
  hstack->GetXaxis()->SetTitleSize(0.04);
  hstack->GetYaxis()->SetTitle("Events");
  hstack->GetXaxis()->SetLabelSize(0.023);
  c1->Modified();
  writeExtraText = true;extraText  = "      preliminary";lumi_sqrtS = "137.1 fb^{-1}(13 TeV)";   
  leg->Draw();
  CMS_lumi( c1,0,0 );
  c1->Update();
  c1->RedrawAxis();
  c1->GetFrame()->Draw();
  c1->Print("PrunedMass1data_fullmodel_fitted.pdf",".pdf");

  MC_bkg.add(MC_sig);
  RooPlot *xframe = jetMass.frame();
  MC_bkg.plotOn(xframe,LineColor(kOrange+4)) ; 

  RooRealVar nsig("nsig","number of signal events",300.,0.,10000.) ;
  RooRealVar nbkg("nbkg","number of background events",1000.,0.,10000.) ;
  //RooExtendPdf esig("esig","extended signal p.d.f",sig,nsig) ;
  //RooExtendPdf ebkg("ebkg","extended background p.d.f",bkg,nbkg) ;
  // Construct sum of two extended p.d.f. (no coefficients required)
  RooAddPdf  model("model","(g1+g2)+a",RooArgList(bkg,sig),RooArgList(nbkg,nsig)) ;
  RooFitResult* r1 = model.fitTo(MC_bkg,Extended(kTRUE),Save());
  model.plotOn(xframe,LineColor(kRed));   
  model.plotOn(xframe,Components(bkg));
  model.paramOn(xframe,LineColor(kRed),Layout(0.9, 0.55, 0.9));
  
  //bkg.plotOn(xframe,DataError(RooAbsData::SumW2));
  //bkg.plotOn(frame,VisualizeError(*r, RooArgSet(a1,a2),2),FillColor(kYellow),FillStyle(3001));
  bkg.plotOn(frame,LineColor(kBlack));
  bkg.paramOn(xframe);
   //sig.plotOn(xframe);
  sig.paramOn(xframe);

  TCanvas *c2=new TCanvas("c2","",600,600) ;
  c2->SetFillColor(0);c2->SetBorderMode(0);c2->SetFrameFillStyle(0);c2->SetFrameBorderMode(0);
  c2->SetLeftMargin( L/W );c2->SetRightMargin( R/W );c2->SetTopMargin( T/H );
  c2->SetBottomMargin( B/H );c2->SetTickx(0);c2->SetTicky(0);c2->Draw();
  c2->Update();
  hstack->Draw("hist");
  //xframe->Draw("hist same");
  hstack->GetXaxis()->SetTitle("Lead m_{J} [GeV]");
  hstack->GetYaxis()->SetLabelSize(0.023);
  hstack->GetYaxis()->SetTitleSize(0.04);
  hstack->GetXaxis()->SetTitleSize(0.04);
  hstack->GetYaxis()->SetTitle("Events");
  hstack->GetYaxis()->SetRangeUser(0.,200.);
  hstack->GetXaxis()->SetLabelSize(0.023);
  c2->Modified();
  writeExtraText = true;extraText  = "      preliminary";lumi_sqrtS = "137.1 fb^{-1}(13 TeV)";
  leg->Draw();
  //hstack->Draw("hist");
  xframe->Draw("hist same");
  CMS_lumi( c2,0,0 );
  c2->Update();
  c2->RedrawAxis();
  c2->GetFrame()->Draw();
  c2->Print("PrunedMass1scaled137_sigplusbkg_fitted.pdf",".pdf");  

//  for(int i=0;i<1000;i++){
  //RooDataSet* toySample = (RooDataSet*)mcs->genData(600);
  
  RooRealVar Mmean("Mmean","mean",90.,50.,200.);
  RooRealVar Msigma("Msigma","sigma",5.,0.,50.);
  RooRealVar Mwidth("Mwidth","width",15.,0.,50.);
  RooVoigtian Mvoigt("Mvoigt","voigt",jetMass,Mmean,Mwidth,Msigma);
  RooRealVar lambda("lambda", "slope", -0.1,-10.,10.);
  RooExponential expo("expo", "exponential PDF", jetMass, lambda);
  RooRealVar expofrac("expofrac","fraction of expo",0.5,0.,1.);

  RooRealVar ms1("ms1","ms1",0.5,0.,1.);
  RooChebychev mcheby1sig("mcheby1sig","Polynomial part", jetMass, RooArgList(ms1));
  RooRealVar mchebyfrac("mchebyfrac","fraction of cheby",0.5,0.,1.);
  RooAddPdf Msig("Msig","Msig",RooArgList(Mvoigt,mcheby1sig),mchebyfrac);
//  RooRealVar b1("b1","a1",0.0,-100.,100.);
//  RooRealVar b2("b2","a2",0.0,-100.,100.);
//  RooChebychev cheby("cheby", "", jetMass, RooArgList(b1,b2));
  
   RooAddPdf Mfinal1 ("Mfinal1","toy fitting",RooArgList(expo,sig),RooArgList(nbkg,nsig));
//  RooAddPdf Mfinal ("Mfinal","toy fitting",RooArgList(expo,Mvoigt),RooArgList(nbkg,nsig));

//RooMCStudy* mcs = new RooMCStudy(model,jetMass,Binned(kTRUE),Silence(),Extended(),FitModel(model),FitOptions(Save(kTRUE),PrintEvalErrors(0)));
RooMCStudy* mcs = new RooMCStudy(model,jetMass,Silence(),Extended(),FitModel(Mfinal1),FitOptions(Save(kTRUE),PrintEvalErrors(0)));

   mcs->generateAndFit(10000,0,kTRUE);

   RooDataSet* toySample = (RooDataSet*)mcs->genData(5693);
   //Mfinal1.fitTo(*toySample);
   RooFitResult *r5 =  Mfinal1.fitTo(*toySample,Save());
   RooPlot* frame0 = jetMass.frame();
   toySample->plotOn(frame0);

   //Mfinal.plotOn(frame0,LineColor(kRed),);
   Mfinal1.plotOn(frame0,LineColor(kBlue),VisualizeError(*r5, RooArgSet(lambda),1),FillColor(kYellow),FillStyle(3001));
  // Mfinal1.plotOn(frame0,Components(cheby),LineColor(kYellow),LineStyle(kDashed));
  // Mfinal.plotOn(frame0,Components(expo),LineColor(kRed),LineStyle(kDashed));
  // sig.plotOn(frame,Components(cheby1sig),LineColor(kOrange));
  // Mfinal.paramOn(frame0,LineColor(kRed));
   Mfinal1.paramOn(frame0,LineColor(kBlue),Layout(0.95, 0.4, 0.9));
   //model.plotOn(frame0,LineColor(kRed));
   // RooNLLVar nll("nll","nll",Mfinal,*toySample) ;

  TH1* h_nsig = mcs->fitParDataSet().createHistogram("nsig") ;
  TH1* h_nbkg = mcs->fitParDataSet().createHistogram("nbkg") ;
  RooPlot* frame1  = mcs->plotParam(nsig) ;
  frame1->SetTitle("Distribution of fitted nsig values") ;
  RooPlot* frame2 = mcs->plotPull(nsig,FitGauss(),Layout(0.9, 0.4, 0.9)) ;
  RooPlot* frame3  = mcs->plotParam(nbkg);
  frame3->SetTitle("Distribution of fitted nbkg values") ;
  RooPlot* frame4 = mcs->plotPull(nbkg,FitGauss(),Layout(0.9, 0.4, 0.9)) ;

//  TH1* h_total = Add(h_nsig);
//  h_total = Add(h_nbkg);
//  RooPlot* frame5  = mcs->plotParam(h_total);
//  frame3->SetTitle("Distribution of fitted nTotal values") ;
//  RooPlot* frame6 = mcs->plotPull(h_total,FitGauss()) ;
  
  TCanvas *c3=new TCanvas("c3","",600,600) ;
  c3->SetFillColor(0);c3->SetBorderMode(0);c3->SetFrameFillStyle(0);c3->SetFrameBorderMode(0);
  c3->SetLeftMargin( L/W );c3->SetRightMargin( R/W );c3->SetTopMargin( T/H );
  c3->SetBottomMargin( B/H );c3->SetTickx(0);c3->SetTicky(0);c3->Draw();
  c3->Update();
  frame0->Draw("hist");
  frame0->GetXaxis()->SetTitle("Lead m_{J} [GeV]");
  frame0->GetYaxis()->SetLabelSize(0.023);
  frame0->GetYaxis()->SetTitleSize(0.04);
  frame0->GetXaxis()->SetTitleSize(0.04);
  frame0->GetYaxis()->SetTitle("Events");
 // frame0->GetYaxis()->SetRangeUser(0.,50.);
  frame0->GetXaxis()->SetLabelSize(0.023);
  c3->Modified();
  writeExtraText = true;extraText  = "     Generated for 10000 toy MC";lumi_sqrtS = "";
  //TLegend *leg1=new TLegend(0.5488722,0.5825806,0.814787,0.7748387,NULL,"brNDC");
  //leg1->AddEntry(PrunedMassT5HH1700Sig ,"Generated toy fitted to expo + fixed signal ","L");
  //leg1->AddEntry(PrunedMassT5HH1300Sig, "Sig.+Bkg. Fit from model","L");
  //leg1->Draw();
  CMS_lumi( c3,0,0 );
  c3->Update();
  c3->RedrawAxis();
  c3->GetFrame()->Draw();
  c3->Print("PrunedMass1scaled137_toywithexpo_sigplusbkg_fitted.pdf",".pdf");

  TCanvas *c5=new TCanvas("c5","",600,600) ;
  c5->SetFillColor(0);c5->SetBorderMode(0);c5->SetFrameFillStyle(0);c5->SetFrameBorderMode(0);
  c5->SetLeftMargin( L/W );c5->SetRightMargin( R/W );c5->SetTopMargin( T/H );
  c5->SetBottomMargin( B/H );c5->SetTickx(0);c5->SetTicky(0);c5->Draw();
  c5->Update();
  frame4->Draw("hist");
  frame4->GetXaxis()->SetTitle("Background Pull");
  frame4->GetYaxis()->SetLabelSize(0.023);
  frame4->GetYaxis()->SetTitleSize(0.04);
  frame4->GetXaxis()->SetTitleSize(0.04);
  frame4->GetYaxis()->SetTitle("Events");
//  frame4->GetYaxis()->SetRangeUser(0.,50.);
  frame4->GetXaxis()->SetLabelSize(0.023);
  c5->Modified();
  writeExtraText = true;extraText  = "    Generated for 10000 toy MC";lumi_sqrtS = "";
  CMS_lumi( c5,0,0 );
  c5->Update();
  c5->RedrawAxis();
  c5->GetFrame()->Draw();
  c5->Print("PrunedMass1scaled137_bkgpull_fitted.pdf",".pdf");

  TCanvas *c4=new TCanvas("c4","",600,600) ;
  c4->SetFillColor(0);c4->SetBorderMode(0);c4->SetFrameFillStyle(0);c4->SetFrameBorderMode(0);
  c4->SetLeftMargin( L/W );c4->SetRightMargin( R/W );c4->SetTopMargin( T/H );
  c4->SetBottomMargin( B/H );c4->SetTickx(0);c4->SetTicky(0);c4->Draw();
  c4->Update();
  frame2->Draw("hist");
  frame2->GetXaxis()->SetTitle("Signal Pull");
  frame2->GetYaxis()->SetLabelSize(0.023);
  frame2->GetYaxis()->SetTitleSize(0.04);
  frame2->GetXaxis()->SetTitleSize(0.04);
  frame2->GetYaxis()->SetTitle("Events");
//  frame2->GetYaxis()->SetRangeUser(0.,50.);
  frame2->GetXaxis()->SetLabelSize(0.023);
  c4->Modified();
  writeExtraText = true;extraText  = "     Generated for 10000 toy MC";lumi_sqrtS = "";
  CMS_lumi( c4,0,0 );
  c4->Update();
  c4->RedrawAxis();
  c4->GetFrame()->Draw();
  c4->Print("PrunedMass1scaled137_sigpull_fitted.pdf",".pdf");

/*  

  TCanvas* c3 = new TCanvas("SignalPull","Pull distribution of nsig",1200,400);
  c3->Divide(3) ;
  c3->cd(1) ; gPad->SetLeftMargin(0.15) ; h_nsig->GetYaxis()->SetTitleOffset(1.6) ; h_nsig->Draw() ;
  c3->cd(2) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
  c3->cd(3) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
  
  TCanvas* c4 = new TCanvas("BkgPull","Pull distribution of nbkg",1200,400);
  c4->Divide(3) ;
  c4->cd(1) ; gPad->SetLeftMargin(0.15) ; h_nbkg->GetYaxis()->SetTitleOffset(1.6) ; h_nbkg->Draw() ;
  c4->cd(2) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
  c4->cd(3) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
*/
  
}
