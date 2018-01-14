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
    /*

    typedef plot<RA2bTree> plot;
    double mJbins[4]={50.,85.,135.,250.};
    vector<vector<plot> > plots;
    
    for( int i = 0 ; i < numMETbins ; i++ ) {
        TString tag="_";
        tag+=lowestMET+i*binWidth;
        vector<plot> plotsTemp;
        plotsTemp.push_back(plot(*fillLeadingJetMass<RA2bTree>,"mJ_tagSR"+tag,"m_{J} [GeV]",3,mJbins));
        plotsTemp.push_back(plot(*fillLeadingJetMass<RA2bTree>,"mJ_tagSB"+tag,"m_{J} [GeV]",3,mJbins));
    
        plotsTemp.push_back(plot(*fillLeadingJetMass<RA2bTree>,"mJ_antitagSR"+tag,"m_{J} [GeV]",3,mJbins));
        plotsTemp.push_back(plot(*fillLeadingJetMass<RA2bTree>,"mJ_antitagSB"+tag,"m_{J} [GeV]",3,mJbins));
    
        plotsTemp.push_back(plot(*fillLeadingJetMass<RA2bTree>,"mJ_doubletagSR"+tag,"m_{J} [GeV]",3,mJbins));
        plotsTemp.push_back(plot(*fillLeadingJetMass<RA2bTree>,"mJ_doubletagSB"+tag,"m_{J} [GeV]",3,mJbins));

        plots.push_back(plotsTemp);
    }

    //vector<plot> tempPlots;
    double met_bins[9]={100.,150.,200.,250.,300.,400.,500.,600.,700.};
    plot METfine_Plot(*fillMET<RA2bTree>,"METfine","MET [GeV]",8,met_bins);
    plot MET_Plot(*fillMET<RA2bTree>,"MET","MET [GeV]",3,100,700);
    plot J1pt_Ptplot(*fillLeadingJetPt<RA2bTree>,"J1pt_Pt","p_{T,J} [GeV]",50,300.,1300.);
    plot J2pt_Ptplot(*fillSubLeadingJetPt<RA2bTree>,"J2pt_Pt","p_{T,J} [GeV]",50,300.,1300.);
    plot J1pt_Mplot(*fillLeadingJetMass<RA2bTree>,"J1pt_M","m_{J} [GeV]",50,50.,250.);
    plot J2pt_Mplot(*fillSubLeadingJetMass<RA2bTree>,"J2pt_M","m_{J} [GeV]",50,50.,250.);
    plot ClosestMass(*fillClosestJetMass<RA2bTree>,"ClosestMass","m_{J} [GeV]",3,mJbins);
    plot FarthestMass(*fillFarthestJetMass<RA2bTree>,"FarthestMass","m_{J} [GeV]",3,mJbins);

    vector<plot> doubletagSRPlots;
    doubletagSRPlots.push_back(plot(MET_Plot));
    doubletagSRPlots.push_back(plot(METfine_Plot));
    doubletagSRPlots.push_back(plot(J1pt_Ptplot));
    doubletagSRPlots.push_back(plot(J2pt_Ptplot));
    doubletagSRPlots.push_back(plot(J1pt_Mplot));
    doubletagSRPlots.push_back(plot(J2pt_Mplot));
    doubletagSRPlots.push_back(plot(ClosestMass));
    doubletagSRPlots.push_back(plot(FarthestMass));

    vector<plot> doubletagSBPlots;
    doubletagSBPlots.push_back(plot(MET_Plot));
    doubletagSBPlots.push_back(plot(METfine_Plot));
    doubletagSBPlots.push_back(plot(J1pt_Ptplot));
    doubletagSBPlots.push_back(plot(J2pt_Ptplot));
    doubletagSBPlots.push_back(plot(J1pt_Mplot));    
    doubletagSBPlots.push_back(plot(J2pt_Mplot));    
    doubletagSBPlots.push_back(plot(ClosestMass));
    doubletagSBPlots.push_back(plot(FarthestMass));

    vector<plot> tagSRPlots;
    tagSRPlots.push_back(plot(MET_Plot));
    tagSRPlots.push_back(plot(METfine_Plot));
    tagSRPlots.push_back(plot(J1pt_Ptplot));
    tagSRPlots.push_back(plot(J2pt_Ptplot));    
    tagSRPlots.push_back(plot(J1pt_Mplot));
    tagSRPlots.push_back(plot(J2pt_Mplot));    
    tagSRPlots.push_back(plot(ClosestMass));
    tagSRPlots.push_back(plot(FarthestMass));

    vector<plot> tagSBPlots;
    tagSBPlots.push_back(plot(MET_Plot));
    tagSBPlots.push_back(plot(METfine_Plot));
    tagSBPlots.push_back(plot(J1pt_Ptplot));
    tagSBPlots.push_back(plot(J2pt_Ptplot));    
    tagSBPlots.push_back(plot(J1pt_Mplot));
    tagSBPlots.push_back(plot(J2pt_Mplot));    
    tagSBPlots.push_back(plot(ClosestMass));
    tagSBPlots.push_back(plot(FarthestMass));

    vector<plot> antitagSRPlots;
    antitagSRPlots.push_back(plot(MET_Plot));
    antitagSRPlots.push_back(plot(METfine_Plot));
    antitagSRPlots.push_back(plot(J1pt_Ptplot));
    antitagSRPlots.push_back(plot(J2pt_Ptplot));    
    antitagSRPlots.push_back(plot(J1pt_Mplot));
    antitagSRPlots.push_back(plot(J2pt_Mplot));    
    antitagSRPlots.push_back(plot(ClosestMass));
    antitagSRPlots.push_back(plot(FarthestMass));

    vector<plot> antitagSBPlots;
    antitagSBPlots.push_back(plot(MET_Plot));
    antitagSBPlots.push_back(plot(METfine_Plot));
    antitagSBPlots.push_back(plot(J1pt_Ptplot));
    antitagSBPlots.push_back(plot(J2pt_Ptplot));    
    antitagSBPlots.push_back(plot(J1pt_Mplot));
    antitagSBPlots.push_back(plot(J2pt_Mplot));    
    antitagSBPlots.push_back(plot(ClosestMass));
    antitagSBPlots.push_back(plot(FarthestMass));
*/
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
       //for( int iEvt = 0 ; iEvt <10; iEvt++ ){
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
	    newtree->Fill(); 
        }// end event loop
	//newtree->SetName(filename);
	outputFile->cd();
	newtree->Write(skims.sampleName[iSample]);
	  
  }// end sample loop
  

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

 /* 
    for( int iBin = 0 ; iBin < numMETbins ; iBin++){
        for( int iPlot = 0 ; iPlot < plots[iBin].size() ; iPlot++){
            plots[iBin][iPlot].addDataNtuple(ntuple,"data");
        }
    }
    for( int i = 0 ; i < doubletagSRPlots.size() ; i++ ){
        doubletagSRPlots[i].addDataNtuple(ntuple,"doubletagSR_data");
    }
    for( int i = 0 ; i < doubletagSBPlots.size() ; i++ ){
        doubletagSBPlots[i].addDataNtuple(ntuple,"doubletagSB_data");
    }
    for( int i = 0 ; i < tagSRPlots.size() ; i++ ){
        tagSRPlots[i].addDataNtuple(ntuple,"tagSR_data");
    }
    for( int i = 0 ; i < tagSBPlots.size() ; i++ ){
        tagSBPlots[i].addDataNtuple(ntuple,"tagSB_data");
    }
    for( int i = 0 ; i < antitagSRPlots.size() ; i++ ){
        antitagSRPlots[i].addDataNtuple(ntuple,"antitagSR_data");
    }
    for( int i = 0 ; i < antitagSBPlots.size() ; i++ ){
        antitagSBPlots[i].addDataNtuple(ntuple,"antitagSB_data");
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
