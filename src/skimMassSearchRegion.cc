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
    int reg_(0);
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
        }else
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

        RA2bTree* ntuple = skims.ntuples[iSample];
 	TTree*newtree=(TTree*)ntuple->fChain->CloneTree(0);
	newtree->SetBranchStatus("*",0);
        newtree->SetBranchStatus("BTags",1);
        newtree->SetBranchStatus("MET",1);
	int BTags;	
        double MET,Weight,JetPt1, JetPt2,PrunedMass1, PrunedMass2, Jet1_tau2overtau1, Jet2_tau2overtau1;
        TBranch*b_BTags, *b_Weight,*b_MET,*b_JetPt1, *b_JetPt2,*b_PrunedMass1, *b_PrunedMass2, *b_Jet1_tau2overtau1, *b_Jet2_tau2overtau1;
    	int WMatchedJet1, WMatchedJet2;

        newtree->Branch("WMatchedJet1", &WMatchedJet1, "WMatchedJet1/I");	
        newtree->Branch("WMatchedJet2", &WMatchedJet2, "WMatchedJet2/I");	
	
        newtree->Branch("JetPt1", &JetPt1, "JetPt1/D");	
        newtree->Branch("JetPt2", &JetPt2, "JetPt/D");	
        newtree->Branch("PrunedMass1", &PrunedMass1, "PrunedMass1/D");	
        newtree->Branch("PrunedMass2", &PrunedMass2, "PrunedMass/D");	
        newtree->Branch("Jet1_tau2overtau1", &Jet1_tau2overtau1, "Jet1_tau2overtau1/D");	
        newtree->Branch("Jet2_tau2overtau2", &Jet2_tau2overtau1, "Jet2_tau2overtau1/D");	
        newtree->Branch("Evtweight",&Weight, "Evtweight/D");  

        newtree->SetBranchAddress("BTags",&BTags,&b_BTags);
        newtree->SetBranchAddress("MET",&MET, &b_MET);
         	
        int numEvents = ntuple->fChain->GetEntries();
        ntupleBranchStatus<RA2bTree>(ntuple);
        int bin = -1;
        double weight=0.;
        float trigWeight=1.0;
        bool passBaseline;
        double jetMass1,jetMass2;
        TString filename;
    for( int iEvt = 0 ; iEvt < min(options.MAX_EVENTS,numEvents) ; iEvt++ ){
      // for( int iEvt = 0 ; iEvt <1000; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;
             passBaseline=true;
             for( auto baselineCut : baselineCuts ){
             passBaseline&=baselineCut(ntuple);
             }
            if( ! passBaseline ) continue;
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
	    weight = ntuple->Weight*lumi*customPUweights(ntuple)*trigWeight;
	    //weight = ntuple->Weight *lumi*trigWeight*customPUweights(ntuple);    
	    //std::cout<<"Weight "<<ntuple->Weight<<std::endl;
            Weight=weight;
	    MET=ntuple->MET;
	    BTags=ntuple->BTags;
            JetPt1=ntuple->JetsAK8->at(0).Pt();  
            JetPt2=ntuple->JetsAK8->at(1).Pt();
	    PrunedMass1=ntuple->JetsAK8_prunedMass->at(0);
	    PrunedMass2=ntuple->JetsAK8_prunedMass->at(1);
	    Jet1_tau2overtau1=ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0);
	    Jet2_tau2overtau1=ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1);
	    //std::cout<<"MET"<<MET<<std::endl;
	WMatchedJet1=0;
	WMatchedJet2=0;
	if(skims.sampleName[iSample]!="data"){
	for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        	if( abs(ntuple->GenParticles_PdgId->at(i)) == 24){ //&& ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<0.4){
			float deta=ntuple->JetsAK8->at(0).Eta()-ntuple->GenParticles->at(i).Eta();
			float dphi=ntuple->JetsAK8->at(0).Phi()-ntuple->GenParticles->at(i).Phi();
			if(sqrt((deta*deta)+(dphi*dphi))<0.4)WMatchedJet1=1;
			deta=ntuple->JetsAK8->at(1).Eta()-ntuple->GenParticles->at(i).Eta();
			dphi=ntuple->JetsAK8->at(1).Phi()-ntuple->GenParticles->at(i).Phi();
			if(sqrt((deta*deta)+(dphi*dphi))<0.4)WMatchedJet2=1;
		}
    	     }
	}
	    newtree->Fill(); 
        }// end event loop
	//newtree->SetName(filename);
	outputFile->cd();
	newtree->Write(skims.sampleName[iSample]);
	  
  }// end sample loop
  
/*
    for( int iSample = 0 ; iSample < skims.signalNtuples.size() ; iSample++){
        RA2bTree* ntuple = skims.signalNtuples[iSample];

        ntupleBranchStatus<RA2bTree>(ntuple);
 	TTree*newtree=(TTree*)ntuple->fChain->CloneTree(0);
	newtree->SetBranchStatus("*",0);
        newtree->SetBranchStatus("BTags",1);
        newtree->SetBranchStatus("MET",1);
	int BTags;	
        double MET,Weight,JetPt1, JetPt2,PrunedMass1, PrunedMass2, Jet1_tau2overtau1, Jet2_tau2overtau1;
        TBranch*b_BTags, *b_Weight,*b_MET,*b_JetPt1, *b_JetPt2,*b_PrunedMass1, *b_PrunedMass2, *b_Jet1_tau2overtau1, *b_Jet2_tau2overtau1;
		
        newtree->Branch("JetPt1", &JetPt1, "JetPt1/D");	
        newtree->Branch("JetPt2", &JetPt2, "JetPt/D");	
        newtree->Branch("PrunedMass1", &PrunedMass1, "PrunedMass1/D");	
        newtree->Branch("PrunedMass2", &PrunedMass2, "PrunedMass/D");	
        newtree->Branch("Jet1_tau2overtau1", &Jet1_tau2overtau1, "Jet1_tau2overtau1/D");	
        newtree->Branch("Jet2_tau2overtau2", &Jet2_tau2overtau1, "Jet2_tau2overtau1/D");	
        newtree->Branch("Evtweight",&Weight, "Evtweight/D");  

        newtree->SetBranchAddress("BTags",&BTags,&b_BTags);
        newtree->SetBranchAddress("MET",&MET, &b_MET);

        int numEvents = ntuple->fChain->GetEntries();
        float trigWeight,weight;
        double jetMass1,jetMass2;
        vector<double> EfficiencyCenterUpDown;
      // for( int iEvt = 0 ; iEvt <10; iEvt++ ){

        for( int iEvt = 0 ; iEvt < numEvents ; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 10000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
            if(!baselineCut(ntuple) ) continue;
            //                        //std::cout<<"Gen Higgs Content "<<getNumGenHiggses(ntuple)<<std::endl;
            if(getNumGenZs(ntuple)!=2) continue;
            EfficiencyCenterUpDown = Eff_MetMhtSextetReal_CenterUpDown(ntuple->HT, ntuple->MHT, ntuple->NJets);
            trigWeight=EfficiencyCenterUpDown[0];
            weight = trigWeight;
            weight*=SignalISRCorrection(ntuple);
            Weight=weight;
	    MET=ntuple->MET;
	    BTags=ntuple->BTags;
            JetPt1=ntuple->JetsAK8->at(0).Pt();  
            JetPt2=ntuple->JetsAK8->at(1).Pt();
	    PrunedMass1=ntuple->JetsAK8_prunedMass->at(0);
	    PrunedMass2=ntuple->JetsAK8_prunedMass->at(1);
	    Jet1_tau2overtau1=ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0);
	    Jet2_tau2overtau1=ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1);
	    newtree->Fill(); 
      }
	//newtree->SetName(filename);
	outputFile->cd();
	newtree->Write(skims.signalSampleName[iSample]);
   }
*/ 
    // data 
/*
    RA2bTree* ntuple = skims.dataNtuple;
    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    bool passBaseline;
    for( int iEvt = 0 ; iEvt < min(options.MAX_EVENTS,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( iEvt % 100000 == 0 ) cout << "data: " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;

        passBaseline=true;
        for( auto baselineCut : baselineCuts ){
            passBaseline&=baselineCut(ntuple);
        }
        if( ! passBaseline ) continue;

        if( reg == skimSamples::kSignal ){
            if( !signalTriggerCut(ntuple) ) continue;
        }else if( reg == skimSamples::kSLm ){
            if( !singleMuTriggerCut(ntuple) ) continue;
        }else if( reg == skimSamples::kSLe ){
            if( !singleEleTriggerCut(ntuple) ) continue;
        }else if( reg == skimSamples::kLowDphi ){ 
            if( !lowDphiTriggerCut(ntuple) ) continue;
        }
    }// end event loop 
*/
            

    outputFile->Close();

}
