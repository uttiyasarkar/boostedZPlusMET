#This code is for producing variable plots with CMS standards. Instructions to run: 1. Specify your cut selection from L#28. 2. draw from L#28 onwards.in L#2 choose which plots do you want to make, finally run script plotmaker.sh to produce .pdf and .png files
data = ["HT","MET","JetPt1","JetPt2","PrunedMass1","PrunedMass2"]
import os
import sys
for ivar in range(0, len(data)):
   sys.stdout = open('anplotter{}.C'.format(data[ivar]),'w')
   print ' #include "string.h"\n#include "tdrstyle.C"\n#include "CMS_lumi.C"\n#include "TH1.h"\n#include "TH1F.h"\n#include "THStack.h"\n#include "hist.C"'
   print 'void anplotter%s(){'%(data[ivar])
   print 'gROOT->LoadMacro("tdrstyle.C");'
   print '//setTDRStyle();'
   print ' TFile* inputFile =new TFile("SkimFileMass.root", "READ");'
   print ' OtherTree=(TTree*)inputFile->Get("Other");'
   print ' ZJetsTree=(TTree*)inputFile->Get("ZJets");'
   print ' WJetsTree=(TTree*)inputFile->Get("WJets");' 
   print ' SnglTTree=(TTree*)inputFile->Get("SnglT");'
   print ' TTBarTTree=(TTree*)inputFile->Get("TT");'
   print ' QCDTree=(TTree*)inputFile->Get("QCD");'
   print ' T5HH1300Tree=(TTree*)inputFile->Get("T5HH1300");'
   print ' T5HH1700Tree=(TTree*)inputFile->Get("T5HH1700");'
   print 'hist h;'
   print 'TH1D *%sOther = h.%sOther;'%(data[ivar],data[ivar])
   print 'TH1D *%sSnglT = h.%sSnglT;'%(data[ivar],data[ivar])
   print 'TH1D *%sZBkg = h.%sZBkg;'%(data[ivar],data[ivar])
   print 'TH1D *%sWBkg = h.%sWBkg;'%(data[ivar],data[ivar])
   print 'TH1D *%sTTBarBkg = h.%sTTBarBkg;'%(data[ivar],data[ivar])   
   print 'TH1D *%sQCDBkg = h.%sQCDBkg;'%(data[ivar],data[ivar])
   print 'TH1D *%sT5HH1300Sig = h.%sT5HH1300Sig;'%(data[ivar],data[ivar])
   print 'TH1D *%sT5HH1700Sig = h.%sT5HH1700Sig;'%(data[ivar],data[ivar])
   print 'OtherTree->Draw("%s>>%sOther", "(HT>500 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");'%(data[ivar],data[ivar])
   print 'SnglTTree->Draw("%s>>%sSnglT", "(HT>500 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");'%(data[ivar],data[ivar])
   print 'ZJetsTree->Draw("%s>>%sZBkg", "(HT>500 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");'%(data[ivar],data[ivar])
   print 'WJetsTree->Draw("%s>>%sWBkg", "(HT>500 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");'%(data[ivar],data[ivar])
   print 'TTBarTTree->Draw("%s>>%sTTBarBkg","(HT>500 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");'%(data[ivar],data[ivar])
   print 'QCDTree->Draw("%s>>%sQCDBkg", "(HT>500 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");'%(data[ivar],data[ivar])
   print 'T5HH1300Tree->Draw("%s>>%sT5HH1300Sig", "(HT>500 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");'%(data[ivar],data[ivar])
   print 'T5HH1700Tree->Draw("%s>>%sT5HH1700Sig", "(HT>500 && MET>300 && PrunedMass1>70 && PrunedMass1<100 && PrunedMass2>70 && PrunedMass2<100)*Evtweight*(137/35.9)");'%(data[ivar],data[ivar])
   print ' hist *h1;'
   print ' %sSnglT->Sumw2(kTRUE);'%(data[ivar])
   print ' %sOther->Sumw2(kTRUE);'%(data[ivar])
   print ' %sQCDBkg->Sumw2(kTRUE);'%(data[ivar])
   print ' %sWBkg->Sumw2(kTRUE);'%(data[ivar])
   print ' %sZBkg->Sumw2(kTRUE);'%(data[ivar])
   print ' %sTTBarBkg->Sumw2(kTRUE);'%(data[ivar])
   print ' %sT5HH1300Sig->Sumw2(kTRUE);'%(data[ivar])
   print ' %sT5HH1700Sig->Sumw2(kTRUE);'%(data[ivar])

   print ' THStack*hstack=new THStack("hstack","");'
   print ' %sQCDBkg->SetFillColor(kGray+1);'%(data[ivar])
   print ' %sOther->SetFillColor(kRed+2);'%(data[ivar])
   print ' %sSnglT->SetFillColor(kYellow-3);'%(data[ivar])
   print ' %sWBkg->SetFillColor(kBlue+1);'%(data[ivar])
   print ' %sZBkg->SetFillColor(kGreen+1);'%(data[ivar])
   print ' %sTTBarBkg->SetFillColor(kCyan+1);'%(data[ivar])
   print ' %sT5HH1300Sig->SetLineColor(kRed+1);'%(data[ivar])
   print ' %sT5HH1700Sig->SetLineColor(kBlack);'%(data[ivar])

   print ' hstack->Add(%sOther);'%(data[ivar])
   print ' hstack->Add(%sSnglT);'%(data[ivar])
   print ' hstack->Add(%sTTBarBkg);'%(data[ivar])
   print ' hstack->Add(%sWBkg);'%(data[ivar])
   print ' hstack->Add(%sZBkg);'%(data[ivar])
   print ' TH1D*TotalBkg=(TH1D*)hstack->GetStack()->Last();'
   print ' TCanvas*c1=new TCanvas("c1", "", 600, 600);'
   print ' int W = 600;\nint H = 600;\nint H_ref = 600;\nint W_ref = 600;\nfloat T = 0.08*H_ref;\nfloat B = 0.12*H_ref;\nfloat L = 0.12*W_ref;\nfloat R = 0.04*W_ref;'
   print ' c1->SetFillColor(0);c1->SetBorderMode(0);c1->SetFrameFillStyle(0);c1->SetFrameBorderMode(0);c1->SetLeftMargin( L/W );c1->SetRightMargin( R/W );c1->SetTopMargin( T/H );c1->SetBottomMargin( B/H );c1->SetTickx(0);c1->SetTicky(0);'
   print ' c1->Draw();'
   print 'c1->Update();'

   print ' hstack->Draw("hist");'
   print ' %sT5HH1300Sig->Draw("hist same");'%(data[ivar])
   print ' %sT5HH1700Sig->Draw("hist same");'%(data[ivar])
   print ' hstack->GetXaxis()->SetTitle("%s [GeV]");'%(data[ivar])
   print ' hstack->GetYaxis()->SetLabelSize(0.023);'
   print ' hstack->GetYaxis()->SetTitleSize(0.04);'
   print ' hstack->GetXaxis()->SetTitleSize(0.04);'
   print ' hstack->GetYaxis()->SetTitle("Events");'
   print ' hstack->GetXaxis()->SetLabelSize(0.023);'
   print ' c1->Modified();'
   print ' writeExtraText = true;'
   print ' extraText  = "     preliminary Simulation";'
   print ' lumi_sqrtS = "137.1 fb^{-1}(13 TeV)";'
   print ' TLegend *leg=new TLegend(0.5488722,0.6825806,0.914787,0.8748387,NULL,"brNDC");'
   print ' leg->AddEntry(%sQCDBkg, "QCD ","F");'%(data[ivar])
   print ' leg->AddEntry(%sOther, "Other","F");'%(data[ivar])
   print ' leg->AddEntry(%sSnglT, "SnglT ","F");'%(data[ivar])
   print ' leg->AddEntry(%sTTBarBkg, "TTJets ","F");'%(data[ivar])
   print ' leg->AddEntry(%sWBkg, "W+Jets ","F");'%(data[ivar])
   print ' leg->AddEntry(%sZBkg, "Z+Jets ","F");'%(data[ivar])
   print ' leg->AddEntry(%sT5HH1300Sig, "T5ZZ1300 ","L");'%(data[ivar])
   print ' leg->AddEntry(%sT5HH1700Sig, "T5ZZ1700 ","L");'%(data[ivar])
   print ' gStyle->SetLegendBorderSize(0);'
   print ' gStyle->SetLegendFillColor(0);'
   print ' gStyle->SetLegendFont(10);'
   print ' leg->Draw();'
   print ' CMS_lumi( c1,0,0 );'
   print ' //c1->SetLogy();'
   print ' c1->Update();'
   print ' c1->RedrawAxis();'
   print ' c1->GetFrame()->Draw();'
   print ' c1->Print("%sscaled137_fitting.pdf",".pdf");'%(data[ivar])
   print ' c1->Print("%sscaled137_fitting.png",".png");'%(data[ivar])
   print '}'


