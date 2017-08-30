#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
#include "TROOT.h"
#include "THStack.h"
#include "TPad.h"

#include <vector>
#include <map>
#include <iostream>

#include "plotterUtils.cc"
#include "skimSamples.cc"
#include "definitions.cc"
#include "RA2bTree.cc"
#include "defaultArgs.h"

using namespace std;

int main(int argc, char** argv){

    defaultOptions options(argv[0],"");
    options.opts->parse(argc, argv);

    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
  
    skimSamples skims;
    typedef plot<RA2bTree> plot;

    plot METplot(*fillMET<RA2bTree>,"MET_doubleTag","MET [GeV]",15,300.,1800.);
    plot HTplot(*fillHT<RA2bTree>,"HT_doubleTag","H_{T} [GeV]",15,300,2800.);
    plot NJetsplot(*fillNJets<RA2bTree>,"NJets_doubleTag","n_{j}",14,1.5,15.5);
    plot BTagsplot(*fillBTags<RA2bTree>,"BTags_doubleTag","n_{b}",6,-0.5,5.5);

    plot DeltaPhi1plot(*fillDeltaPhi1<RA2bTree>,"DeltaPhi1_doubleTag","#Delta#Phi_{1}",20,0,3.1415);
    plot DeltaPhi2plot(*fillDeltaPhi2<RA2bTree>,"DeltaPhi2_doubleTag","#Delta#Phi_{2}",20,0,3.1415);
    plot DeltaPhi3plot(*fillDeltaPhi3<RA2bTree>,"DeltaPhi3_doubleTag","#Delta#Phi_{3}",20,0,3.1415);
    plot DeltaPhi4plot(*fillDeltaPhi4<RA2bTree>,"DeltaPhi4_doubleTag","#Delta#Phi_{4}",20,0,3.1415);


    plot J1Mplot(*fillLeadingJetMass<RA2bTree>,"J1M_doubleTag","leading m_{J} [GeV]",40,50.,250.);
    plot J1BBplot(*fillLeadingBBtag<RA2bTree>,"J1BB_doubleTag","leading bb-tag",20,-1.,1.);
    plot J1Tau21plot(*fillLeadingTau21<RA2bTree>,"J1Tau21_doubleTag","leading #tau_{21}",20,0.,1.);
    plot J1Ptplot(*fillLeadingJetPt<RA2bTree>,"J1Pt_doubleTag","leading p_{T,J} [GeV]",40,300.,2300.);
    plot J2Mplot(*fillSubLeadingJetMass<RA2bTree>,"J2M_doubleTag","subleading m_{J} [GeV]",40,50.,250.);
    plot J2BBplot(*fillSubLeadingBBtag<RA2bTree>,"J2BB_doubleTag","subleading bb-tag",20,-1.,1.);
    plot J2Tau21plot(*fillSubLeadingTau21<RA2bTree>,"J2Tau21_doubleTag","subleading #tau_{21}",20,0.,1.);
    plot J2Ptplot(*fillSubLeadingJetPt<RA2bTree>,"J2Pt_doubleTag","subleading p_{T,J} [GeV]",40,300.,2300.);
    plot J1pt_JetFlavorPlot(*fillLeadingJetFlavor<RA2bTree>,"J1pt_JetFlavorPlot_doubleTag","Jet Flavor",22,0.5,21.5);
    plot J2pt_JetFlavorPlot(*fillSubLeadingJetFlavor<RA2bTree>,"J2pt_JetFlavorPlot_doubleTag","Jet Flavor",22,0.5,21.5);


    vector<plot> plots;
    plots.push_back(METplot);
    plots.push_back(HTplot);
    plots.push_back(NJetsplot);
    plots.push_back(BTagsplot);
    plots.push_back(DeltaPhi1plot);
    plots.push_back(DeltaPhi2plot);
    plots.push_back(DeltaPhi3plot);
    plots.push_back(DeltaPhi4plot);
    plots.push_back(J1Mplot);
    plots.push_back(J1BBplot);
    plots.push_back(J1Tau21plot);
    plots.push_back(J1Ptplot);
    plots.push_back(J2Mplot);
    plots.push_back(J2BBplot);
    plots.push_back(J2Tau21plot);
    plots.push_back(J2Ptplot);
    plots.push_back(J2pt_JetFlavorPlot);
    plots.push_back(J1pt_JetFlavorPlot);

    // background MC samples
    for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){

        RA2bTree* ntuple = skims.ntuples[iSample];

        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
            plots[iPlot].setFillColor(ntuple,skims.fillColor[iSample]);
        }

        int numEvents = ntuple->fChain->GetEntries();
        ntupleBranchStatus<RA2bTree>(ntuple);
        TString filename;
        for( int iEvt = 0 ; iEvt < min(options.MAX_EVENTS,numEvents) ; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;

            filename = ntuple->fChain->GetFile()->GetName();
            if( ( filename.Contains("SingleLept") || filename.Contains("DiLept") ) && ntuple->madHT>600. )continue;

            if( !baselineCut(ntuple) ) continue;
            if( !doubletagSRCut(ntuple) ) continue;
            for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++ ){
                plots[iPlot].fill(ntuple);
            }
        }
    }
  
    // Signal samples
    vector<RA2bTree*> sigSamples;
    for( int iSample = 0 ; iSample < skims.signalNtuples.size() ; iSample++){
        if( skims.signalSampleName[iSample] != "T5HH1300" && skims.signalSampleName[iSample] != "T5HH1700" ) continue;
      
        RA2bTree* ntuple = skims.signalNtuples[iSample];
        sigSamples.push_back(ntuple);
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            plots[iPlot].addSignalNtuple(ntuple,skims.signalSampleName[iSample]);
            plots[iPlot].setLineColor(ntuple,skims.sigLineColor[iSample]);
        }
      
        int numEvents = ntuple->fChain->GetEntries();
        ntupleBranchStatus<RA2bTree>(ntuple);
        for( int iEvt = 0 ; iEvt < min(options.MAX_EVENTS,numEvents) ; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 100000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;
            if( !baselineCut(ntuple) ) continue;
            if( !doubletagSRCut(ntuple) ) continue;
            if( !genLevelZZcut(ntuple) ) continue;
            for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
                if( skims.signalSampleName[iSample] == "T5HH1300" )
                    plots[iPlot].fillSignal(ntuple,lumi*0.0460525/102482.);
                if( skims.signalSampleName[iSample] == "T5HH1700" )
                    plots[iPlot].fillSignal(ntuple,lumi*0.00470323/103791.);
            }
        }
    }
  
    // Data tree
    RA2bTree* ntuple = skims.dataNtuple;
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].addDataNtuple(ntuple,"data");
    }

    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    for( int iEvt = 0 ; iEvt < 0/*min(options.MAX_EVENTS,numEvents)*/ ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( !baselineCut(ntuple) ) continue;
        if( !doubletagSRCut(ntuple) ) continue;
        if( !signalTriggerCut(ntuple) ) continue;
        if( iEvt % 100000 == 0 ) cout << "DATA: " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            plots[iPlot].fillSignal(ntuple);
        }
    }

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        TCanvas* can = new TCanvas("can","can",500,500);
        plots[iPlot].dataHist = NULL;
        plots[iPlot].DrawNoRatio(can,skims.ntuples,sigSamples,"../plots/plotObs_doubleTag_plots");
    }
}
