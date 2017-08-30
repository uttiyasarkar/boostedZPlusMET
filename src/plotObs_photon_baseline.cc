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

    bool looseCuts(false);
    defaultOptions options(argv[0],"");
    options.opts->add_options()("l,loose_cuts","apply loose jet pt cuts",cxxopts::value<bool>(looseCuts));
    options.opts->parse(argc, argv);

    gROOT->ProcessLine(".L tdrstyle.C");
    gROOT->ProcessLine("setTDRStyle()");
  
    skimSamples skims(skimSamples::kPhoton);
    typedef plot<RA2bTree> plot;

    plot METplot(*fillMETclean<RA2bTree>,"MET_photon_baseline","MET [GeV]",52,100.,800.);
    plot HTplot(*fillHTclean<RA2bTree>,"HT_photon_baseline","H_{T} [GeV]",17,300,2000.);
    plot NJetsplot(*fillNJetsclean<RA2bTree>,"NJets_photon_baseline","n_{j}",14,1.5,15.5);
    plot BTagsplot(*fillBTags<RA2bTree>,"BTags_photon_baseline","n_{b}",6,-0.5,5.5);
    plot PhotonPtplot(*fillPhotonPt<RA2bTree>,"PhotonPt_photon_baseline","p_{T,#gamma} [GeV]",50,100.,1100.);

    plot Ak4JetPt1(*fillJetPt1<RA2bTree>,"Ak4JetPt1_photon_baseline","p_{T,j1} [GeV]",40,0,600);
    plot Ak4JetPt2(*fillJetPt2<RA2bTree>,"Ak4JetPt2_photon_baseline","p_{T,j2} [GeV]",40,0,600);
    plot Ak4JetPt3(*fillJetPt3<RA2bTree>,"Ak4JetPt3_photon_baseline","p_{T,j3} [GeV]",40,0,600);
    plot Ak4JetPt4(*fillJetPt4<RA2bTree>,"Ak4JetPt4_photon_baseline","p_{T,j4} [GeV]",40,0,600);

    plot J2NbhadronPlot(*fillLeadingNbHadrons<RA2bTree>,"J1pt_numBhadrons_baseline","n_{b-had}",5,-0.5,4.5);
    plot J1NbhadronPlot(*fillSubLeadingNbHadrons<RA2bTree>,"J2pt_numBhadrons_baseline","n_{b-had}",5,-0.5,4.5);

    plot J1pt_Massplot(*fillLeadingJetMass_photon<RA2bTree>,"J1pt_Mass_photon_baseline","m_{J} [GeV]",20,50.,250.);
    plot J2pt_Massplot(*fillSubLeadingJetMass_photon<RA2bTree>,"J2pt_Mass_photon_baseline","m_{J} [GeV]",20,50.,250.);
    plot J1pt_MassWideplot(*fillLeadingJetMass_photon<RA2bTree>,"J1pt_MassWide_photon_baseline","m_{J} [GeV]",50,0.,250.);
    plot J2pt_MassWideplot(*fillSubLeadingJetMass_photon<RA2bTree>,"J2pt_MassWide_photon_baseline","m_{J} [GeV]",50,0.,250.);

    plot J1pt_BBplot(*fillLeadingBBtag_photon<RA2bTree>,"J1pt_BBtag_photon_baseline","bb-disc",20,-1.,1.);
    plot J2pt_BBplot(*fillSubLeadingBBtag_photon<RA2bTree>,"J2pt_BBtag_photon_baseline","bb-disc",20,-1.,1.);

    plot J1pt_Ptplot(*fillLeadingJetPt_photon<RA2bTree>,"J1pt_Pt_photon_baseline","p_{T,J} [GeV]",40,300.,2300.);
    plot J2pt_Ptplot(*fillSubLeadingJetPt_photon<RA2bTree>,"J2pt_Pt_photon_baseline","p_{T,J} [GeV]",40,300.,2300.);
    plot J1pt_PtWideplot(*fillLeadingJetPt_photon<RA2bTree>,"J1pt_PtWide_photon_baseline","p_{T,J} [GeV]",50,100.,2100.);
    plot J2pt_PtWideplot(*fillSubLeadingJetPt_photon<RA2bTree>,"J2pt_PtWide_photon_baseline","p_{T,J} [GeV]",50,100.,2100.);

    plot J1pt_JetFlavorPlot(*fillLeadingJetFlavor_photon<RA2bTree>,"J1pt_JetFlavorPlot","Jet Flavor",22,0.5,21.5);
    plot J2pt_JetFlavorPlot(*fillSubLeadingJetFlavor_photon<RA2bTree>,"J2pt_JetFlavorPlot","Jet Flavor",22,0.5,21.5);

    plot J1pt_Tau21plot(*fillLeadingTau21<RA2bTree>,"J1pt_Tau21_photon_baseline","#tau_{21}",20,0.,1.);
    plot J2pt_Tau21plot(*fillSubLeadingTau21<RA2bTree>,"J2pt_Tau21_photon_baseline","#tau_{21}",20,0.,1.);

    vector<plot> plots;
    plots.push_back(J1NbhadronPlot);
    plots.push_back(J2NbhadronPlot);
    plots.push_back(METplot);
    plots.push_back(HTplot);
    plots.push_back(NJetsplot);
    plots.push_back(BTagsplot);
    plots.push_back(PhotonPtplot);
    plots.push_back(J1pt_Massplot);
    plots.push_back(J2pt_Massplot);
    plots.push_back(J1pt_MassWideplot);
    plots.push_back(J2pt_MassWideplot);
    plots.push_back(J1pt_BBplot);
    plots.push_back(J2pt_BBplot);
    plots.push_back(J1pt_Ptplot);
    plots.push_back(J2pt_Ptplot);
    plots.push_back(J1pt_PtWideplot);
    plots.push_back(J2pt_PtWideplot);
    plots.push_back(J1pt_JetFlavorPlot);
    plots.push_back(J2pt_JetFlavorPlot);
    plots.push_back(J1pt_Tau21plot);
    plots.push_back(J2pt_Tau21plot);

    // background MC samples
    for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){

        RA2bTree* ntuple = skims.ntuples[iSample];

        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
            plots[iPlot].setFillColor(ntuple,skims.fillColor[iSample]);
        }

        int numEvents = ntuple->fChain->GetEntries();
        ntupleBranchStatus<RA2bTree>(ntuple);
        int iBin=0;
        double weight=0.;
        for( int iEvt = 0 ; iEvt < min(options.MAX_EVENTS,numEvents) ; iEvt++ ){
            ntuple->GetEntry(iEvt);
            if( iEvt % 100000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;

            if( looseCuts ){
                if( !photonBaselineCut_loose(ntuple) ) continue;
            }else{
                if( !photonBaselineCut(ntuple) ) continue;
            }

            if( skims.sampleName[iSample] == "QCD" && ntuple->Photons_nonPrompt->at(0) == 0 && ntuple->madMinPhotonDeltaR>0.4 && ntuple->madMinDeltaRStatus==1 ) continue;
            if( skims.sampleName[iSample] == "GJets" && ntuple->Photons_nonPrompt->at(0) == 1 ) continue;

            weight = ntuple->Weight*lumi*customPUweights(ntuple);
            if( skims.sampleName[iSample] == "GJets" ){
                //cout << "GJets NLO correction: " << GJetsNLOWeights(ntuple) << endl;
                //weight*=GJetsNLOWeights(ntuple);
            }
            for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++ ){
                iBin=plots[iPlot].fill(ntuple,weight);
            }
        }
    }


    // Data samples
    RA2bTree* ntuple = skims.dataNtuple;
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].addDataNtuple(ntuple,"data");
    }

    int numEvents = ntuple->fChain->GetEntries();
    ntupleBranchStatus<RA2bTree>(ntuple);
    int iBin=0;
    for( int iEvt = 0 ; iEvt < min(options.MAX_EVENTS,numEvents) ; iEvt++ ){
        ntuple->GetEntry(iEvt);
        if( iEvt % 1000000 == 0 ) cout << "data: " << iEvt << "/" << min(options.MAX_EVENTS,numEvents) << endl;
      
        if( looseCuts ){
            if( !photonBaselineCut_loose(ntuple) ) continue;
        }else{
            if( !photonBaselineCut(ntuple) ) continue;
        }
        if( !photonTriggerCut(ntuple) ) continue;
        for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
            iBin=plots[iPlot].fillData(ntuple);
        }
    }
  
    TString outputTag = (looseCuts?"looseCuts_":"");
    TFile* outputFile = new TFile("plotObs_photon_"+outputTag+"baseline.root","RECREATE");

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
        plots[iPlot].Write();
        TCanvas* can = new TCanvas("can","can",500,500);
        can->SetTopMargin(0.05);
        plots[iPlot].Draw(can,skims.ntuples,skims.signalNtuples,"../plots/plotObs_photon_"+outputTag+"baseline_plots",0.,2.,true);
    }
}
