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
#include "RA2bTree.cc"
#include "TriggerEfficiencySextet.cc"
#include "defaultArgs.h"

using namespace std;

int main(int argc, char** argv){

    skimSamples::region reg;
    int reg_(1);
    bool looseCuts(false);
    defaultOptions options(argv[0],"");
    options.opts->add_options()("l,loose_cuts","apply loose jet pt cuts",cxxopts::value<bool>(looseCuts))("r,region","region to analyze",cxxopts::value<int>(reg_));
    options.opts->parse(argc, argv);

    reg = static_cast<skimSamples::region>(reg_);
    
    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
    
    skimSamples* skims_ = new skimSamples(reg);

    typedef bool(*cuts)(RA2bTree*);
    vector<cuts> baselineCuts;

    if( looseCuts ){
        baselineCuts.push_back(*FiltersCut<RA2bTree>);
        if( reg == skimSamples::kLowDphi ){ 
            baselineCuts.push_back(*lowDPhiCuts<RA2bTree>);
        }else{
            baselineCuts.push_back(*DeltaPhiCuts<RA2bTree>);
        }
        if( reg == skimSamples::kSLm ){
            baselineCuts.push_back(*singleMuCut<RA2bTree>);
        }
        if( reg == skimSamples::kSLe ){
            baselineCuts.push_back(*singleEleCut<RA2bTree>);
        }
        baselineCuts.push_back(*METHTlooseCut<RA2bTree>);
        baselineCuts.push_back(*AK8MultCut<RA2bTree>);
    }else{
        if( reg == skimSamples::kSignal ){
            baselineCuts.push_back(*baselineCut<RA2bTree>);
        }else if( reg == skimSamples::kSLm ){
            baselineCuts.push_back(*singleMuBaselineCut<RA2bTree>);
        }else if( reg == skimSamples::kSLe ){
            baselineCuts.push_back(*singleEleBaselineCut<RA2bTree>);
        }else if( reg == skimSamples::kLowDphi ){ 
            baselineCuts.push_back(*lowDphiBaselineCut<RA2bTree>);
        }
	else if(reg==skimSamples::kPhoton){
            baselineCuts.push_back(*photonBaselineCut<RA2bTree>);
		//std::cout<<"Single Photon "<<std::endl;
	}
	else
            assert(1);
    }

    skimSamples skims = *skims_;
    TFile* outputFile;
    TString regionName;
    TString cutName="";
    if( looseCuts )
        cutName="_looseCuts";
    if( reg == skimSamples::kSignal )
        regionName="";
    if( reg == skimSamples::kSLm )
        regionName="_singleMu";
    if( reg == skimSamples::kSLe )
        regionName="_singleEle";
    if( reg == skimSamples::kLowDphi )
        regionName="_lowDphi";
    outputFile = new TFile("SkimFileMass"+cutName+regionName+".root","RECREATE");
    // background MC samples - 0 lepton regions
   for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){
   ///for( int iSample = 0 ; iSample < 0 ; iSample++){
        RA2bTree* ntuple = skims.ntuples[iSample];
 	//TTree*newtree=(TTree*)ntuple->fChain->CloneTree(0);
 	TTree*newtree=new TTree("newtree","");//(TTree*)ntuple->fChain->CloneTree(0);
	/*
	newtree->SetBranchStatus("*",0);
	newtree->SetBranchStatus("HT",1);
        newtree->SetBranchStatus("BTags",1);
        newtree->SetBranchStatus("MET",1);
        newtree->SetBranchStatus("JetsAK8*",1);
        newtree->SetBranchStatus("Jets",1);
        newtree->SetBranchStatus("Jets_bDiscriminatorCSV",1);
	newtree->SetBranchStatus("Jets_partonFlavor",1);
	*/
	int BTags;	
        double MET,HT,Weight,JetPt1, JetPt2,PrunedMass1, PrunedMass2, Jet1_tau2overtau1, Jet2_tau2overtau1;
        //TBranch*b_BTags, *b_Weight,*b_MET,*b_HT,*b_JetPt1, *b_JetPt2,*b_PrunedMass1, *b_PrunedMass2, *b_Jet1_tau2overtau1, *b_Jet2_tau2overtau1, *b_GenHadTau;
    	int WMatchedJet1, WMatchedJet2;
	int GenHadTau=0;
	int nAK8=0;
        newtree->Branch("WMatchedJet1", &WMatchedJet1, "WMatchedJet1/I");	
        newtree->Branch("WMatchedJet2", &WMatchedJet2, "WMatchedJet2/I");	
        newtree->Branch("JetPt1", &JetPt1, "JetPt1/D");	
        newtree->Branch("JetPt2", &JetPt2, "JetPt2/D");	
        newtree->Branch("PrunedMass1", &PrunedMass1, "PrunedMass1/D");	
        newtree->Branch("PrunedMass2", &PrunedMass2, "PrunedMass2/D");	
        newtree->Branch("Jet1_tau2overtau1", &Jet1_tau2overtau1, "Jet1_tau2overtau1/D");	
        newtree->Branch("Jet2_tau2overtau2", &Jet2_tau2overtau1, "Jet2_tau2overtau1/D");	
        newtree->Branch("Evtweight",&Weight, "Evtweight/D");  
        newtree->Branch("GenHadTau", &GenHadTau, "GenHadTau/I");
        newtree->Branch("nAK8", &nAK8, "nAK8/I");
	newtree->Branch("HT", &HT, "HT/D");
        //newtree->SetBranchAddress("BTags",&BTags,&b_BTags);
        newtree->Branch("MET",&MET, "MET/D");
        int numEvents = ntuple->fChain->GetEntries();
        ntupleBranchStatus<RA2bTree>(ntuple);
        int bin = -1;
        double weight=0.;
        float trigWeight=1.0;
        bool passBaseline;
        double jetMass1,jetMass2;
        TString filename;
        cout << skims.sampleName[iSample]<<numEvents <<endl;
    for( int iEvt = 0 ; iEvt < min(options.MAX_EVENTS,numEvents) ; iEvt++ ){
    //for( int iEvt = 0 ; iEvt < min(10,numEvents) ; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;
             passBaseline=true;
             for( auto baselineCut : baselineCuts ){
             passBaseline&=baselineCut(ntuple);
             }
            if( ! passBaseline ) continue;
	    //std::cout<<"Pass Baseline "<<std::endl; 	    
            filename = ntuple->fChain->GetFile()->GetName();
            if( ( filename.Contains("SingleLept") || filename.Contains("DiLept") ) && ntuple->madHT>600. )continue;
            bin = -1;
            if(reg == skimSamples::kSignal ){
                std::vector<double> EfficiencyCenterUpDown = Eff_MetMhtSextetReal_CenterUpDown(ntuple->HT, ntuple->MHT, ntuple->NJets);
                trigWeight=EfficiencyCenterUpDown[0];
            }else if( reg == skimSamples::kSLm ){
                trigWeight=singleMuonTrigWeights(ntuple);
            }else if( reg == skimSamples::kSLe ){
                trigWeight=singleElectronTrigWeights(ntuple);
            }else if( reg == skimSamples::kLowDphi ){
                trigWeight=lowDphiTrigWeights(ntuple);
	    }
	    weight = ntuple->Weight*lumi*trigWeight;//*customPUweights(ntuple)*trigWeight;
	    //weight = ntuple->Weight *lumi*trigWeight*customPUweights(ntuple);    
	    //std::cout<<"Weight "<<ntuple->Weight<<std::endl;
            Weight=weight;
	    MET=ntuple->MET;
	    HT=ntuple->HT;
	    BTags=ntuple->BTags;
	    nAK8=ntuple->JetsAK8->size();
	    if(nAK8>0){
            JetPt1=ntuple->JetsAK8->at(0).Pt();  
	    PrunedMass1=ntuple->JetsAK8_prunedMass->at(0);
	   Jet1_tau2overtau1=ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0);
	   }
	    if(nAK8>1){
            JetPt2=ntuple->JetsAK8->at(1).Pt();
	    PrunedMass2=ntuple->JetsAK8_prunedMass->at(1);
	    Jet2_tau2overtau1=ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1);
	    }
	    //std::cout<<"MET"<<MET<<std::endl;
	WMatchedJet1=0;
	WMatchedJet2=0;
	if(skims.sampleName[iSample]!="data" && skims.sampleName[iSample]!="data2017" && skims.sampleName[iSample]!="data2018"){
	for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        	if( abs(ntuple->GenParticles_PdgId->at(i)) == 24){ //&& ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<0.4){
			if(nAK8<1)continue;
			float deta=ntuple->JetsAK8->at(0).Eta()-ntuple->GenParticles->at(i).Eta();
			float dphi=ntuple->JetsAK8->at(0).Phi()-ntuple->GenParticles->at(i).Phi();
			if(sqrt((deta*deta)+(dphi*dphi))<0.4)WMatchedJet1=1;
	    		if(nAK8<2)continue;
			deta=ntuple->JetsAK8->at(1).Eta()-ntuple->GenParticles->at(i).Eta();
			dphi=ntuple->JetsAK8->at(1).Phi()-ntuple->GenParticles->at(i).Phi();
			if(sqrt((deta*deta)+(dphi*dphi))<0.4)WMatchedJet2=1;
		}
    	     }
	}
	   if(skims.sampleName[iSample]!="data" && skims.sampleName[iSample]!="data2017" && skims.sampleName[iSample]!="data2018"){
		bool HadTau=false;
		GenHadTau=0;
	   	for(unsigned int t=0; t<ntuple->GenTaus_had->size(); ++t) if(ntuple->GenTaus_had->at(t))++GenHadTau ;
	   } 
		newtree->Fill();
        }// end event loop
	//newtree->SetName(filename);
	outputFile->cd();
	newtree->Write(skims.sampleName[iSample]);
	  
  }// end sample loop
if(reg == skimSamples::kSignal ){
    for( int iSample = 0 ; iSample < skims.signalNtuples.size() ; iSample++){

        RA2bTree* ntuple = skims.signalNtuples[iSample];
 	TTree*newtree=new TTree("newtree", "");//ntuple->fChain->CloneTree(0);
	int BTags;	
        double MET,HT,Weight,JetPt1, JetPt2,PrunedMass1, PrunedMass2, Jet1_tau2overtau1, Jet2_tau2overtau1;
        //TBranch*b_BTags, *b_Weight,*b_MET,*b_JetPt1, *b_JetPt2,*b_PrunedMass1, *b_PrunedMass2, *b_Jet1_tau2overtau1, *b_Jet2_tau2overtau1, *b_GenHadTau;
    	int WMatchedJet1, WMatchedJet2;
	int GenHadTau=0;
	int nAK8=0;
        newtree->Branch("WMatchedJet1", &WMatchedJet1, "WMatchedJet1/I");	
       newtree->Branch("WMatchedJet2", &WMatchedJet2, "WMatchedJet2/I");	
        newtree->Branch("JetPt1", &JetPt1, "JetPt1/D");	
        newtree->Branch("JetPt2", &JetPt2, "JetPt2/D");	
        newtree->Branch("PrunedMass1", &PrunedMass1, "PrunedMass1/D");	
        newtree->Branch("PrunedMass2", &PrunedMass2, "PrunedMass2/D");	
        newtree->Branch("Jet1_tau2overtau1", &Jet1_tau2overtau1, "Jet1_tau2overtau1/D");	
        newtree->Branch("Jet2_tau2overtau2", &Jet2_tau2overtau1, "Jet2_tau2overtau1/D");	
        newtree->Branch("Evtweight",&Weight, "Evtweight/D");  
        newtree->Branch("GenHadTau", &GenHadTau, "GenHadTau/I");
        newtree->Branch("nAK8", &nAK8, "nAK8/I");
	newtree->Branch("HT", &HT, "HT/D");
        //newtree->SetBranchAddress("BTags",&BTags,&b_BTags);
        newtree->Branch("MET",&MET, "MET/D");

        //newtree->SetBranchAddress("BTags",&BTags,&b_BTags);
        //newtree->SetBranchAddress("MET",&MET, &b_MET);
        int numEvents = ntuple->fChain->GetEntries();
        ntupleBranchStatus<RA2bTree>(ntuple);
        int bin = -1;
        double weight=0.;
        float trigWeight=1.0;
        bool passBaseline;
        double jetMass1,jetMass2;
        TString filename;
    for( int iEvt = 0 ; iEvt < min(options.MAX_EVENTS,numEvents) ; iEvt++ ){
    //  for( int iEvt = 0 ; iEvt <1000; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 100000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;
	                 passBaseline=true;
	    for( auto baselineCut : baselineCuts ){
             passBaseline&=baselineCut(ntuple);
            }
            if( ! passBaseline ) continue;
	    if(getNumGenHiggses(ntuple)>0)continue;
		//std::cout<<"Here ZZ "<<std::endl;	
                std::vector<double> EfficiencyCenterUpDown = Eff_MetMhtSextetReal_CenterUpDown(ntuple->HT, ntuple->MHT, ntuple->NJets);
                trigWeight=EfficiencyCenterUpDown[0];
	   weight=ntuple->Weight*lumi*trigWeight/0.25;
            Weight=weight;
	    HT=ntuple->HT;
	    MET=ntuple->MET;
	    BTags=ntuple->BTags;
	    nAK8=ntuple->JetsAK8->size();
	    if(nAK8>0){
            JetPt1=ntuple->JetsAK8->at(0).Pt();  
	    PrunedMass1=ntuple->JetsAK8_prunedMass->at(0);
	   Jet1_tau2overtau1=ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0);
	   }
	    if(nAK8>1){
            JetPt2=ntuple->JetsAK8->at(1).Pt();
	    PrunedMass2=ntuple->JetsAK8_prunedMass->at(1);
	    Jet2_tau2overtau1=ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1);
	    }
               newtree->Fill();
	}
        outputFile->cd();
        newtree->Write(skims.signalSampleName[iSample]);
   }
}
    outputFile->Close();

}
