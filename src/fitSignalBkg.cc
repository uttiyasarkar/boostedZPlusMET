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
//#include "RooPower.h"
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
    
   //TFile* inputFile =new TFile("BkgOutputDistributions.root", "READ");
    //TFile* inputFile =new TFile("OutputSignalCards.root", "READ");
    TFile* inputFile =new TFile("OutputSignalCardsTotalMass.root", "READ");
    //TFile* inputFile =new TFile("BkgOutputDistributionsSubjettinessCut.root", "READ");
    //BKg Shapes:
   // OtherSB=(TH1D*)inputFile->Get("OtherSidebandPlot");
    TH1D*MassShapeSB=(TH1D*)inputFile->Get("MassShapeFromSB");
    TH1D*METShapeFromSB=(TH1D*)inputFile->Get("METShapeFromSB");
     MassShapeSB->Rebin(3);    
   /* 
    TH1D*PrunedMassZBkg=new TH1D("PrunedMassZBkg", "Pruned Mass [GeV]", 60,50,200);
    TH1D*PrunedMassWBkg=new TH1D("PrunedMassWBkg", "Pruned Mass [GeV]", 60,50,200);
    TH1D*PrunedMassTTBarBkg=new TH1D("PrunedMassTTBarBkg", "Pruned Mass [GeV]", 60,50,200);
    TH1D*PrunedMassQCDBkg=new TH1D("PrunedMassQCDBkg", "Pruned Mass [GeV]",60,50,200);
*/
    RooRealVar* METBins = new RooRealVar("METBins","MET [GeV]",700.,300.,2000.);
    RooRealVar* jetMass = new RooRealVar("jetMass","Pruned Jet Mass [GeV]",75.,50.,200.);
    METBins->setRange("METBin1", 300, 500);
    METBins->setRange("METBin2", 500, 700);
    METBins->setRange("METBin3", 700, 1500);
    jetMass->setRange("Signal",70, 100);
    jetMass->setRange("Sideband1",50, 70);
    jetMass->setRange("Sideband2",100, 200);
    //jetMass->setRange("Sideband3",95, 160);
    RooRealVar beta("beta", "powerlaw", 0, -1., 0.5);
    RooRealVar alpha("alpha", "exponential", 0, -1., 0.5);
    RooRealVar alphaMET("alphaMET", "exponentialMET", 0, -1., 1.);
  TCanvas* can = new TCanvas("can","can",500,500);
    int LowSearchBin=MassShapeSB->GetXaxis()->FindBin(70);
    int HighSearchBin=MassShapeSB->GetXaxis()->FindBin(100);
    RooDataHist* MC_bkg = new RooDataHist("MC_bkg","MC_bkg",RooArgList(*jetMass),MassShapeSB);
    RooExponential exp("exp", "", *jetMass, alpha);

   RooRealVar* p1 = new RooRealVar("p1","p1",0.5,0.0,1.0);
    RooRealVar* p2 = new RooRealVar("p2","p2",0.5,0.0,1.0);
    RooRealVar* p3 = new RooRealVar("p3","p3",0.5,0.0,1.0);
    RooBernstein* poly = new RooBernstein("poly","poly",*jetMass,RooArgList(*p1,*p2));
 //   RooFitResult* r=
//	poly->fitTo(*MC_bkg, Range("Sideband1,Sideband2"),Save());
    //RooPower*pow=new RooPower("pow", "pow", *jetMass, RooArgList(beta)); 
    RooExponential expMET("expMET", "", *METBins, alphaMET);
    
    RooFitResult* r=exp.fitTo(*MC_bkg, Range("Sideband1,Sideband2"),Save());
    //RooFitResult* r=exp.fitTo(*MC_bkg);
    RooPlot* frame = jetMass->frame(Title("Imported TH1 with Poisson error bars")) ;
    MC_bkg->plotOn(frame,DataError(RooAbsData::SumW2)) ;
    //poly->plotOn(frame,VisualizeError(*r, RooArgSet(*p1,*p2,*p3),2),FillColor(kYellow),FillStyle(3001));
    exp.plotOn(frame,VisualizeError(*r, RooArgSet(alpha),2),FillColor(kYellow),FillStyle(3001));
    exp.plotOn(frame,LineColor(kBlack));
    //exp.plotOn(frame,LineColor(kRed));
    frame->Draw("");
    //leg->Draw();
    can->Print("MassShapeMC.pdf");
//return;
//  alpha.setVal(alpha.getVal());
  RooAbsReal*BkginSR=exp.createIntegral(*jetMass, NormSet(*jetMass), Range("Signal"));
//  RooAbsReal*BkginSRBias=poly->createIntegral(*jetMass, NormSet(*jetMass), Range("Signal"));
cout << " Bkg Integral "<< BkginSR->getVal()*MassShapeSB->Integral() << endl ; 
//cout << " Bkg Integral Poly "<< BkginSRBias->getVal()*MassShapeSB->Integral() << endl ; 
//cout << "MC  Bkg Integral "<<MassShapeSB->Integral(LowSearchBin,HighSearchBin) << endl ;
return;
    METShapeFromSB->Scale(1.0/METShapeFromSB->Integral());    
    METShapeFromSB->Sumw2(kTRUE);    
    RooDataHist* MC_bkgMETShape = new RooDataHist("MC_bkgMETShape","MC_bkgMETShape",RooArgList(*METBins),METShapeFromSB);
    //RooFitResult*r2=expMET.fitTo(*MC_bkgMETShape, Save());
    RooPlot* frame2 = METBins->frame(Title("Imported TH1 with Poisson error bars")) ;
    //expMET.plotOn(frame2,VisualizeError(*r2, RooArgSet(alphaMET),2),FillColor(kYellow),FillStyle(3001));
    //expMET.plotOn(frame2);
    MC_bkgMETShape->plotOn(frame2) ;
    frame2->Draw("");
    can->Print("TestMET.pdf");
/*    
THStack*hstack2=new THStack("hstack2","");
    
    
    QCDMET->SetFillColor(kGray);
    WJetsMET->SetFillColor(kBlue);
    ZJetsMET->SetFillColor(kGreen+1);
    TTBarMET->SetFillColor(kCyan);
    hstack2->Add(QCDMET);
    hstack2->Add(TTBarMET);
    hstack2->Add(ZJetsMET);
    hstack2->Add(WJetsMET);
 hstack2->Draw("hist"); 
    TH1D*MassShapeSBMETShape=(TH1D*)hstack2->GetStack()->Last();
    RooDataHist* MC_bkgMETShape = new RooDataHist("MC_bkgMETShape","MC_bkgMETShape",RooArgList(*METBins),MassShapeSBMETShape);
    RooFitResult*r2=expMET.fitTo(*MC_bkgMETShape, Save());
    RooPlot* frame2 = METBins->frame(Title("Imported TH1 with Poisson error bars")) ;
    MC_bkgMETShape->plotOn(frame2,DataError(RooAbsData::SumW2)) ;
    expMET.plotOn(frame2,VisualizeError(*r2, RooArgSet(alphaMET),2),FillColor(kYellow),FillStyle(3001));
    expMET.plotOn(frame2);
    frame2->Draw("");
     RooAbsReal*METBin1SR=expMET.createIntegral(*METBins, NormSet(*METBins), Range("METBin1"));
     RooAbsReal*METBin2SR=expMET.createIntegral(*METBins, NormSet(*METBins), Range("METBin2"));
     RooAbsReal*METBin3SR=expMET.createIntegral(*METBins, NormSet(*METBins), Range("METBin3"));
     std::cout<<"MET Bin Fractions "<<METBin1SR->getVal()<<", "<<METBin2SR->getVal()<<", "<<METBin3SR->getVal()<<std::endl;
    can->Print("TestMET.pdf");
    TFile* inputFileB =new TFile("BkgOutputDistributionsBTags.root", "READ");
    //TFile* inputFileB =new TFile("BkgOutputDistributionsBTagsLooseCuts.root", "READ");
    ZJetsSB_b=(TH1D*)inputFileB->Get("ZJetsSidebandPlot");
    WJetsSB_b=(TH1D*)inputFileB->Get("WJetsSidebandPlot");
   // SnglSB=(TH1D*)inputFile->Get("SnglTSidebandPlot");
    TTBarSB_b=(TH1D*)inputFileB->Get("TTSidebandPlot");
    QCDSB_b=(TH1D*)inputFileB->Get("QCDSidebandPlot");
    //OtherSR=(TH1D*)inputFile->Get("OtherSignalRegionMassPlot");
    ZJetsSR_b=(TH1D*)inputFileB->Get("ZJetsSignalRegionMassPlot");
    WJetsSR_b=(TH1D*)inputFileB->Get("WJetsSignalRegionMassPlot");
    //SnglSR=(TH1D*)inputFile->Get("SnglTSignalRegionMassPlot");
    TTBarSR_b=(TH1D*)inputFileB->Get("TTSignalRegionMassPlot");
    QCDSR_b=(TH1D*)inputFileB->Get("QCDSignalRegionMassPlot");
    WJetsSB_b->Add(WJetsSR_b); ZJetsSB_b->Add(ZJetsSR_b);
    QCDSB_b->Add(QCDSR_b); TTBarSB_b->Add(TTBarSR_b);
    THStack*hstack3=new THStack("hstack3","");
    
    
    QCDSB_b->SetFillColor(kGray);
    WJetsSB_b->SetFillColor(kBlue);
    ZJetsSB_b->SetFillColor(kGreen+1);
    TTBarSB_b->SetFillColor(kCyan);
    
    hstack3->Add(QCDSB_b);
    hstack3->Add(TTBarSB_b);
    hstack3->Add(ZJetsSB_b);
    hstack3->Add(WJetsSB_b);
    TCanvas* can2 = new TCanvas("can2","can",500,500);
	hstack3->Draw("hist");
//    can2->Print("TestBtags.pdf");

    TH1D*MassShapeSBB=(TH1D*)hstack3->GetStack()->Last();
    RooDataHist* MC_bkgB = new RooDataHist("MC_bkgB","MC_bkgB",RooArgList(*jetMass),MassShapeSBB);     
    RooRealVar alphaB("alphaB", "exponential", 0, -1., 0.1);
    RooExponential expB("expB", "", *jetMass, alphaB);
  //MEt>300
    RooRealVar* bp1 = new RooRealVar("bp1","p1",0.380,0.0,1.0);
    RooRealVar* bp2 = new RooRealVar("bp2","p2",0.5138,0.0,1.0);
    RooRealVar* bp3 = new RooRealVar("bp3","p3",0.128442,0.0,1.0);
RooRealVar* bp4 = new RooRealVar("bp4","p4", 0.0879432,0.0,1.0);
	//MET>300
    RooRealVar* bp1 = new RooRealVar("bp1","p1",0.736830,0.0,1.0);
    RooRealVar* bp2 = new RooRealVar("bp2","p2",0.995311,0.0,1.0);
    RooRealVar* bp3 = new RooRealVar("bp3","p3",0.248904,0.0,1.0);
RooRealVar* bp4 = new RooRealVar("bp4","p4", 0.170292,0.0,1.0);
  bp1->setConstant(kTRUE);
  bp2->setConstant(kTRUE);
  bp3->setConstant(kTRUE);
  bp4->setConstant(kTRUE);
 RooBernstein* polyB  = new RooBernstein("poly","poly",*jetMass,RooArgList(*bp1,*bp2,*bp3,*bp4));
 //RooBernstein* polyB  = new RooBernstein("poly","poly",*jetMass,RooArgList(*bp1,*bp2,*bp3));
    RooRealVar* meanB = new RooRealVar("meanB","mean",78.17,60.,100.);
    
    RooRealVar* sigmaB = new RooRealVar("sigmaB","sigma",7.2337,0.,20.);
	meanB->setConstant(kTRUE);
RooGaussian* gaussB = new RooGaussian("gaussB","gauss",*jetMass,*meanB,*sigmaB);
	sigmaB->setConstant(kTRUE);
    RooRealVar* WNorm = new RooRealVar("WNorm","sigFrac",0.133,0.,1.);
   RooRealVar* bkgNorm = new RooRealVar("bkgFrac","bkdFrac",100.,0.,10000000.);
 RooAddPdf* model = new RooAddPdf("model","model",RooArgList(*gaussB,*polyB),*WNorm);
 
  WNorm->setConstant(kTRUE);
  RooExtendPdf*modelExt=new RooExtendPdf("modelExt", "", *model, *bkgNorm);
 
modelExt->fitTo(*MC_bkgB,Range("Sideband1,Signal,Sideband3"),Save()); 

    RooPlot* frame3 = jetMass->frame(Title("Imported TH1 with Poisson error bars")) ;
    MC_bkgB->plotOn(frame3,DataError(RooAbsData::SumW2)) ;
    //expB.plotOn(frame2,VisualizeError(*r, RooArgSet(alpha),2),FillColor(kYellow),FillStyle(3001));
    modelExt->plotOn(frame3,LineColor(kBlack));
	WNorm->setVal(WNorm->getVal()+WNorm->getError());
  	RooAbsReal*BkginSRB=modelExt->createIntegral(*jetMass, NormSet(*jetMass),Range("Signal"));
     
     cout << " Bkg Integral Btags"<< BkginSRB->getVal()*MassShapeSBB->Integral() << endl ; 
	cout << "MC  Bkg Integral "<<MassShapeSBB->Integral(LowSearchBin,HighSearchBin) << endl ; 

    leg->Draw();
    //hstack3->Draw("hist");	
    frame3->Draw("");
    can2->Print("TestBtags.pdf");
    ZJetsMETB=(TH1D*)inputFileB->Get("ZJetsMETShape");
    WJetsMETB=(TH1D*)inputFileB->Get("WJetsMETShape");
    TTBarMETB=(TH1D*)inputFileB->Get("TTMETShape");
    QCDMETB=(TH1D*)inputFileB->Get("QCDMETShape");
    //SnglMET=(TH1D*)inputFile->Get("SnglTMETShape");
    THStack*hstack4=new THStack("hstack4","");

    QCDMETB->SetFillColor(kGray);
    WJetsMETB->SetFillColor(kBlue);
    ZJetsMETB->SetFillColor(kGreen+1);
    TTBarMETB->SetFillColor(kCyan);
    hstack4->Add(QCDMETB);
    hstack4->Add(TTBarMETB);
    hstack4->Add(ZJetsMETB);
    hstack4->Add(WJetsMETB);
 hstack4->Draw("hist"); 
    TH1D*MassShapeSBMETShapeB=(TH1D*)hstack4->GetStack()->Last();
    RooDataHist* MC_bkgMETShapeB = new RooDataHist("MC_bkgMETShapeB","MC_bkgMETShape",RooArgList(*METBins),MassShapeSBMETShapeB);
    RooRealVar alphaMETB("alphaMETB", "exponential", 0, -1., 0.1);
    RooExponential expMETB("expMETB", "", *METBins, alphaMETB);
    RooFitResult*r3=expMETB.fitTo(*MC_bkgMETShapeB, Save());
     RooAbsReal*METBin1SRB=expMETB.createIntegral(*METBins, NormSet(*METBins), Range("METBin1"));
     RooAbsReal*METBin2SRB=expMETB.createIntegral(*METBins, NormSet(*METBins), Range("METBin2"));
     RooAbsReal*METBin3SRB=expMETB.createIntegral(*METBins, NormSet(*METBins), Range("METBin3"));
     std::cout<<"MET Bin Fractions "<<METBin1SRB->getVal()<<", "<<METBin2SRB->getVal()<<", "<<METBin3SRB->getVal()<<std::endl;

return;
*/
}

