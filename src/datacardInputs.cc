#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
#include "TROOT.h"
#include "THStack.h"
#include "TPad.h"

#include <vector>
#include <map>
#include <iostream>
#include "ALPHABET.h"
#include "plotterUtils.cc"
#include "skimSamples.cc"
#include "definitions.cc"
#include "TriggerEfficiencySextet.cc"
#include "RA2bTree.cc"
using namespace std;

int main(int argc, char** argv){

    gROOT->ProcessLine(".L ./tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
  
    skimSamples skims;//signal by default
    typedef plot<RA2bTree> plot;
    double METBins[4] = {300.,500.,700.,2500.};

    TFile*inputFileSR = new TFile("TwoAk8JetSkims/SkimFileMassSR.root","read");  
    TFile*inputFileSL = new TFile("TwoAk8JetSkims/SkimFileMass_singleSL.root","read");
    TFile*output=new TFile("TwoAK8JetDataCards.root", "recreate");
    for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){
        std::cout<<"Sample Name "<<skims.sampleName[iSample]<<std::endl;
 	TTree* ntuple = (TTree*)inputFileSR->Get(skims.sampleName[iSample]);
        TH1D*AnalysisMETBins_2AK8=new TH1D("AnalysisMETBins_2AK8"+skims.sampleName[iSample],";MET [GeV]; Events 35.9/fb", 100, 0, 2000);//3,METBins) ;
	TH1D*AnalysisMassBins=new TH1D("J1_M","m_{J} [GeV]",150,50.,200.);
	AnalysisMETBins_2AK8->Sumw2(kTRUE);
	AnalysisMassBins->Sumw2(kTRUE);
	//ntupleBranchStatus<RA2bTree>(ntuple);
	double PrunedMass1,PrunedMass2, Evtweight,MET,HT;
	TBranch*b_PrunedMass1,*b_PrunedMass2,*b_Evtweight,*b_MET,*b_HT;
 	ntuple->SetBranchAddress("PrunedMass1", &PrunedMass1, &b_PrunedMass1);
 	ntuple->SetBranchAddress("PrunedMass2", &PrunedMass2, &b_PrunedMass2);
 	ntuple->SetBranchAddress("Evtweight", &Evtweight, &b_Evtweight);
	ntuple->SetBranchAddress("MET", &MET, &b_MET);
	ntuple->SetBranchAddress("HT", &HT, &b_HT);
	int numEvents = ntuple->GetEntries();
	for( int iEvt = 0 ; iEvt < numEvents ; iEvt++ ){
            	ntuple->GetEntry(iEvt);
		if( iEvt % 100 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
		if(HT<500)continue;
		AnalysisMassBins->Fill(PrunedMass1,Evtweight);	
		if(PrunedMass1>75 && PrunedMass1<95)AnalysisMETBins_2AK8->Fill(MET, Evtweight);
	}	
     output->cd();
     AnalysisMassBins->Write("LeadJetMass"+skims.sampleName[iSample]);
    AnalysisMETBins_2AK8->Write("METBins"+skims.sampleName[iSample]);
   }

    for( int iSample = 0 ; iSample < skims.signalNtuples.size() ; iSample++){
        std::cout<<"Sample Name "<<skims.signalSampleName[iSample]<<std::endl;
 	TTree* ntuple = (TTree*)inputFileSR->Get(skims.signalSampleName[iSample]);
        TH1D*AnalysisMETBins_2AK8=new TH1D("AnalysisMETBins_2AK8"+skims.signalSampleName[iSample],";MET [GeV]; Events 35.9/fb", 100, 0, 2000);//3,METBins) ;
	TH1D*AnalysisMassBins=new TH1D("J1_M","m_{J} [GeV]",150,50.,200.);
	AnalysisMETBins_2AK8->Sumw2(kTRUE);
	AnalysisMassBins->Sumw2(kTRUE);
	//ntupleBranchStatus<RA2bTree>(ntuple);
	double PrunedMass1,PrunedMass2, Evtweight,MET,HT;
	TBranch*b_PrunedMass1,*b_PrunedMass2,*b_Evtweight,*b_MET,*b_HT;
 	ntuple->SetBranchAddress("PrunedMass1", &PrunedMass1, &b_PrunedMass1);
 	ntuple->SetBranchAddress("PrunedMass2", &PrunedMass2, &b_PrunedMass2);
 	ntuple->SetBranchAddress("Evtweight", &Evtweight, &b_Evtweight);
	ntuple->SetBranchAddress("MET", &MET, &b_MET);
	ntuple->SetBranchAddress("HT", &HT, &b_HT);
	int numEvents = ntuple->GetEntries();
	for( int iEvt = 0 ; iEvt < numEvents ; iEvt++ ){
            	ntuple->GetEntry(iEvt);
		if( iEvt % 100 == 0 ) cout << +skims.signalSampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
		if(HT<500)continue;
		AnalysisMassBins->Fill(PrunedMass1,Evtweight);	
		if(PrunedMass1>75 && PrunedMass1<95)AnalysisMETBins_2AK8->Fill(MET, Evtweight);
	}	
     output->cd();
     AnalysisMassBins->Write("LeadJetMass"+skims.signalSampleName[iSample]);
     AnalysisMETBins_2AK8->Write("MET"+skims.signalSampleName[iSample]);
   }
    skimSamples skimsSL_(skimSamples::kSLm);
    for( int iSample = 0 ; iSample < skimsSL_.ntuples.size() ; iSample++){
        std::cout<<"Sample Name "<<skimsSL_.sampleName[iSample]<<std::endl;
 	TTree* ntuple = (TTree*)inputFileSL->Get(skimsSL_.sampleName[iSample]);
        TH1D*AnalysisMETBins_2AK8SR=new TH1D("AnalysisMETBins_2AK8SR"+skimsSL_.sampleName[iSample],";MET [GeV]; Events 35.9/fb", 100, 0, 2000);//3,METBins) ;
        TH1D*AnalysisMETBins_2AK8SB=new TH1D("AnalysisMETBins_2AK8SB"+skimsSL_.sampleName[iSample],";MET [GeV]; Events 35.9/fb", 100, 0, 2000);//3,METBins) ;
	AnalysisMETBins_2AK8SR->Sumw2(kTRUE);
	AnalysisMETBins_2AK8SB->Sumw2(kTRUE);
	//ntupleBranchStatus<RA2bTree>(ntuple);
	double PrunedMass1,PrunedMass2, Evtweight,MET,HT;
	TBranch*b_PrunedMass1,*b_PrunedMass2,*b_Evtweight,*b_MET,*b_HT;
 	ntuple->SetBranchAddress("PrunedMass1", &PrunedMass1, &b_PrunedMass1);
 	ntuple->SetBranchAddress("PrunedMass2", &PrunedMass2, &b_PrunedMass2);
 	ntuple->SetBranchAddress("Evtweight", &Evtweight, &b_Evtweight);
	ntuple->SetBranchAddress("MET", &MET, &b_MET);
	ntuple->SetBranchAddress("HT", &HT, &b_HT);
	int numEvents = ntuple->GetEntries();
	for( int iEvt = 0 ; iEvt < numEvents ; iEvt++ ){
            	ntuple->GetEntry(iEvt);
		if( iEvt % 100 == 0 ) cout << skimsSL_.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
		if(HT<500)continue;
		if(PrunedMass1>75 && PrunedMass1<95 && PrunedMass2>75 && PrunedMass2<95)AnalysisMETBins_2AK8SR->Fill(MET, Evtweight);
		if(PrunedMass1>50 && PrunedMass1<75 && PrunedMass2>50 && PrunedMass2<200)AnalysisMETBins_2AK8SB->Fill(MET, Evtweight);
	}	
     output->cd();
	AnalysisMETBins_2AK8SR->Write("SLSR"+skimsSL_.sampleName[iSample]);
	AnalysisMETBins_2AK8SB->Write("SLSB"+skimsSL_.sampleName[iSample]);
   }
}
