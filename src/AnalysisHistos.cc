#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
#include "TROOT.h"
#include "THStack.h"
#include "TPad.h"

#include <vector>
#include <map>
#include <iostream>
#include <assert.h>

#include "plotterUtils.cc"
#include "skimSamples.cc"
#include "definitions.cc"
#include "MassMETPlots.cc"
//#include "RA2bTree.cc"
#include "TriggerEfficiencySextet.cc"
#include "defaultArgs.h"

using namespace std;

int main(int argc, char** argv){

    skimSamples::region reg;
    int reg_(0);
    defaultOptions options(argv[0],"");

    reg = static_cast<skimSamples::region>(reg_);
    
    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
    TFile fin("SkimFileMass.root","READ");
    skimSamples* skims_ = new skimSamples(reg);
    skimSamples skims = *skims_;


    // background MC samples - 0 lepton regions
           double METBins[4]={300., 500.,700., 2100};
           double METBins1AK8[4]={700., 1000.,1300., 2100};
           TH1D*METSignal=new TH1D("METSignal", "; MET [GeV]; 35.9/fb", 3, METBins);
           TH1D*METSignal1AK8=new TH1D("METSignal1AK8", "; MET [GeV]; 35.9/fb", 3, METBins1AK8);
           TH1D*MassPlot=new TH1D("MassPlot", "", 30, 50,200);
           TH1D*MassPlot1AK8=new TH1D("MassPlot1AK8", "", 30, 50,200);
           TH1D*METPlot=new TH1D("METPlot","",24, 300,1500);
           TH1D*METPlot1AK8=new TH1D("METPlot1AK8","",24, 300,1500);
    TFile* outputFile;
    TString regionName;
    TString cutName="";
    if( reg == skimSamples::kSignal )
        regionName="";
    if( reg == skimSamples::kSLm )
        regionName="_singleMu";
    if( reg == skimSamples::kSLe )
        regionName="_singleEle";
    if( reg == skimSamples::kLowDphi )
        regionName="_lowDphi";
    outputFile = new TFile("Analysishistos"+cutName+regionName+".root","RECREATE");
    for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){
        //TTree* ntuple = (TTree*)fin.Get(skims.sampleName[iSample]);
	//cout<<"This Sample "<<skims.sampleName[iSample]<<endl;
        MassPlot->Reset();
           MassPlot1AK8->Reset();
           METPlot->Reset();
           METPlot1AK8->Reset();
           METSignal->Reset();
           METSignal1AK8->Reset();
           MassPlot->Sumw2(kTRUE);
           MassPlot1AK8->Sumw2(kTRUE);
           METPlot->Sumw2(kTRUE);
           METPlot1AK8->Sumw2(kTRUE);
           METSignal->Sumw2(kTRUE);
           METSignal1AK8->Sumw2(kTRUE);
	MassMETPlots* ntuple=new MassMETPlots(skims.sampleName[iSample]); 
	if(reg_==0 &&  skims.sampleName[iSample].Contains("data"))continue; //blind signal region data	
        ntuple->fChain->SetBranchStatus("*", 1);	
        int numEvents = ntuple->fChain->GetEntries();
        float xsec=1.0;
        if(skims.signalSampleName[iSample].Contains("750"))xsec=2.26585;
        if(skims.signalSampleName[iSample].Contains("1000"))xsec=0.325388;
        if(skims.signalSampleName[iSample].Contains("1100"))xsec=0.163491;
        if(skims.signalSampleName[iSample].Contains("1200"))xsec=0.0856418;
        if(skims.signalSampleName[iSample].Contains("1300"))xsec=0.0460525;
        if(skims.signalSampleName[iSample].Contains("1400"))xsec=0.0252977;
        if(skims.signalSampleName[iSample].Contains("1500"))xsec=0.0141903;
        if(skims.signalSampleName[iSample].Contains("1600"))xsec=0.00810078;
        if(skims.signalSampleName[iSample].Contains("1700"))xsec=0.00470323;
        if(skims.signalSampleName[iSample].Contains("1800"))xsec=0.00276133;
        if(skims.signalSampleName[iSample].Contains("1900"))xsec=0.00163547;
        if(skims.signalSampleName[iSample].Contains("2000"))xsec=0.000981077;
        if(skims.signalSampleName[iSample].Contains("2100"))xsec=0.000591918;

        for( int iEvt = 0 ; iEvt < min(options.MAX_EVENTS,numEvents) ; iEvt++ ){
            ntuple->fChain->GetEntry(iEvt);
	    
            if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;
	    int nAK8=ntuple->nAK8;
	    double PrunedMass1=ntuple->PrunedMass1;
	    double PrunedMass2=ntuple->PrunedMass2;
	    double MET=ntuple->MET;
	    double weight=ntuple->Evtweight *xsec;
	    if(ntuple->BTags==0 &&  ntuple->JetPt1>400  && ntuple->JetPt2>300 && ntuple->HT>700){//analysis baseline
                if(nAK8>1 && (PrunedMass1>50 && PrunedMass1<75) && PrunedMass2>50 && PrunedMass2<200)METPlot->Fill(MET, weight);//MET Plot from Mass SB
                if(nAK8==1 && (PrunedMass1>50 && PrunedMass1<75) && MET>700)METPlot1AK8->Fill(MET, weight); //MET Plot from Mass SB for 1AK8
                if(PrunedMass2>75 && PrunedMass2<95 && nAK8>1 )MassPlot->Fill(PrunedMass1,weight); //Mass shape for Lead Jet MET>300
                if(nAK8==1 && MET>700)MassPlot1AK8->Fill(PrunedMass1,weight); // Mass shape for Lead Jet MET>700 for 1AK8 Jet
                if(nAK8>1 && PrunedMass1>75 && PrunedMass1<95 && PrunedMass2>75 && PrunedMass2<95)METSignal->Fill(MET,weight); // SR truth in MET bins 2AK8 Jets
                if(nAK8==1 && PrunedMass1>75 && PrunedMass1<95 && MET>700)METSignal1AK8->Fill(MET, weight); //SR truth in MET bins 2AK8 Jets
		}  
	}
	   outputFile->cd();
           MassPlot->Write(skims.sampleName[iSample]+"LeadJetMass");
           MassPlot1AK8->Write(skims.sampleName[iSample]+"LeadJetMass1AK8");
           METPlot1AK8->Write(skims.sampleName[iSample]+"METSB1AK8");
           METPlot->Write(skims.sampleName[iSample]+"METSB");
           METSignal->Write(skims.sampleName[iSample]+"MCTrueMET");
           METSignal1AK8->Write(skims.sampleName[iSample]+"MCTrueMET1AK8");  
}// end sample loop
    


    outputFile->Close();
}
