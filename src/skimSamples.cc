// ROOT/custom libraries
#include "TChain.h"
#include "RA2bTree.cc"
#include "TString.h"

// STL libraries
#include <iostream>
#include <vector>
static const TString BASE_DIRMC="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/";
static const TString BASE_DIR="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/";

class skimSamples{

public : 

    TChain *WJets,*ZJets,*QCD,*SnglT,*TT,*GJets,*GJets0p4,*Other,*DY,*TTinc;
    TChain *T5HH750, *T5HH1000, *T5HH1100,*T5HH1200,*T5HH1300,*T5HH1400,*T5HH1500,*T5HH1600,*T5HH1700,*T5HH1800,*T5HH1900,*T5HH2000,*T5HH2100;
    TChain *data;
    TChain *data2017;
    TChain *data2018;
    std::vector<RA2bTree*> ntuples,signalNtuples;
    RA2bTree* dataNtuple; RA2bTree* dataNtuple2017; RA2bTree* dataNtuple2018;
    std::vector<TString> sampleName, signalSampleName;
    std::vector<TString> dataSampleName; 
    std::vector<int> fillColor, lineColor, sigLineColor;

    enum region {kSignal,kSLm,kSLe,kLowDphi,kPhoton,kNumRegions};
    TString regionNames[kNumRegions]={"signal","SLm","SLe","kLowDphi","photon"};

    TString skimType;
    TString skimTypeMC;

    skimSamples(region r=kSignal){

        skimType="";

        if( r == kSignal ){
            skimType=BASE_DIR+"tree_signal/";
            skimTypeMC=BASE_DIRMC+"tree_signal/";
        }
        if( r == kPhoton ){
            skimType=BASE_DIR+"tree_GJet_CleanVars/";
            skimTypeMC=BASE_DIRMC+"tree_GJet_CleanVars/";
        }
        if( r == kSLm ){
            skimType=BASE_DIR+"tree_SLm/";
           skimTypeMC=BASE_DIRMC+"tree_SLm/";
        }
        if( r == kSLe ){
            skimType=BASE_DIR+"tree_SLe/";
            skimTypeMC=BASE_DIRMC+"tree_SLe/";
        }
        if(r==kLowDphi){
            skimType=BASE_DIR+"tree_LDP/";
            skimTypeMC=BASE_DIRMC+"tree_LDP/";
        }
        ///////////////////////////////////////////////////////////////////////
        // - - - - - - - - - - BACKGROUND INPUTS - - - - - - - - - - - - - - //
        ///////////////////////////////////////////////////////////////////////
//ONLY DATA IS AVAILABLE FOR NOW!!
        std::vector<TString> OtherFileNames;
        OtherFileNames.push_back("tree_WWTo1L1Nu2Q_MC2017.root");
        OtherFileNames.push_back("tree_WWTo2L2Nu_MC2017.root");
        OtherFileNames.push_back("tree_WWZ_MC2017.root");
        OtherFileNames.push_back("tree_WZTo1L1Nu2Q_MC2017.root");
        OtherFileNames.push_back("tree_WZTo1L3Nu_MC2017.root");
        OtherFileNames.push_back("tree_WZZ_MC2017.root");
        OtherFileNames.push_back("tree_ZZTo2L2Q_MC2017.root");
        OtherFileNames.push_back("tree_ZZTo2Q2Nu_MC2017.root");
        OtherFileNames.push_back("tree_ZZZ_MC2017.root");
        OtherFileNames.push_back("tree_TTTT_MC2017.root");
        OtherFileNames.push_back("tree_TTWJetsToLNu_MC2017.root");
        OtherFileNames.push_back("tree_TTWJetsToQQ_MC2017.root");
        OtherFileNames.push_back("tree_TTGJets_MC2017.root");
        OtherFileNames.push_back("tree_TTZToLLNuNu_MC2017.root");
        OtherFileNames.push_back("tree_TTZToQQ_MC2017.root");
        Other = new TChain("tree");
        for( int i = 0 ; i < OtherFileNames.size() ; i++ ){
            Other->Add(skimTypeMC+"/"+OtherFileNames[i]);
        }
        if( r == kSignal || r == kSLm || r == kSLe || r == kLowDphi || r == kPhoton ){
            ntuples.push_back(new RA2bTree(Other));
            sampleName.push_back("Other");
            fillColor.push_back(kRed+1);
            lineColor.push_back(1);
        }

        std::vector<TString> ZJetsFileNames;
        ZJetsFileNames.push_back("tree_ZJetsToNuNu_HT-100to200_MC2017.root");
        ZJetsFileNames.push_back("tree_ZJetsToNuNu_HT-200to400_MC2017.root");
        ZJetsFileNames.push_back("tree_ZJetsToNuNu_HT-400to600_MC2017.root");
        ZJetsFileNames.push_back("tree_ZJetsToNuNu_HT-600to800_MC2017.root");
        ZJetsFileNames.push_back("tree_ZJetsToNuNu_HT-800to1200_MC2017.root");
        ZJetsFileNames.push_back("tree_ZJetsToNuNu_HT-1200to2500_MC2017.root");
        ZJetsFileNames.push_back("tree_ZJetsToNuNu_HT-2500toInf_MC2017.root");
        ZJets = new TChain("tree");
        for( int i = 0 ; i < ZJetsFileNames.size() ; i++ ){
            ZJets->Add(skimTypeMC+"/"+ZJetsFileNames[i]);
        }
        if( r == kSignal || r == kLowDphi ){ 
            ntuples.push_back(new RA2bTree(ZJets));
            sampleName.push_back("ZJets");
            fillColor.push_back(kGreen+1);
            lineColor.push_back(1);
        }

        std::vector<TString> WJetsFileNames;
        WJetsFileNames.push_back("tree_WJetsToLNu_HT-100to200_MC2017.root");
        WJetsFileNames.push_back("tree_WJetsToLNu_HT-1200to2500_MC2017.root");
        WJetsFileNames.push_back("tree_WJetsToLNu_HT-200to400_MC2017.root");
        WJetsFileNames.push_back("tree_WJetsToLNu_HT-2500toInf_MC2017.root");
        WJetsFileNames.push_back("tree_WJetsToLNu_HT-400to600_MC2017.root");
        WJetsFileNames.push_back("tree_WJetsToLNu_HT-600to800_MC2017.root");
        WJetsFileNames.push_back("tree_WJetsToLNu_HT-800to1200_MC2017.root");
        WJets = new TChain("tree");
        for( int i = 0 ; i < WJetsFileNames.size() ; i++ ){
            WJets->Add(skimTypeMC+"/"+WJetsFileNames[i]);
        }
        if( r == kSignal || r == kSLm || r == kSLe || r == kLowDphi ){
            ntuples.push_back(new RA2bTree(WJets));
            sampleName.push_back("WJets");
            fillColor.push_back(kBlue);
            lineColor.push_back(1);
        }

        std::vector<TString> SnglTFileNames;
        SnglTFileNames.push_back("tree_ST_s-channel_MC2017.root");
        SnglTFileNames.push_back("tree_ST_t-channel_antitop_MC2017.root");
        SnglTFileNames.push_back("tree_ST_t-channel_top_MC2017.root");
        SnglTFileNames.push_back("tree_ST_tW_antitop_MC2017.root");
        SnglTFileNames.push_back("tree_ST_tW_top_MC2017.root");
        SnglT = new TChain("tree");
        for( int i = 0 ; i < SnglTFileNames.size() ; i++ ) {
            SnglT->Add(skimTypeMC+"/"+SnglTFileNames[i]);
        }
        if( r == kSignal || r == kSLm || r == kSLe ){
            ntuples.push_back(new RA2bTree(SnglT));
            sampleName.push_back("SnglT");
            fillColor.push_back(kOrange);
            lineColor.push_back(1);
        }

        std::vector<TString> TTincFileNames;
        TTincFileNames.push_back("tree_TTJets_MC2017.root");
        TTinc = new TChain("tree");
        for( int i = 0 ; i < TTincFileNames.size() ; i++ ){
            TTinc->Add(skimTypeMC+"/"+TTincFileNames[i]);
        }

        std::vector<TString> TTFileNames;
        TTFileNames.push_back("tree_TTJets_HT-600to800_MC2017.root");
        TTFileNames.push_back("tree_TTJets_HT-800to1200_MC2017.root");
        TTFileNames.push_back("tree_TTJets_HT-1200to2500_MC2017.root");
        TTFileNames.push_back("tree_TTJets_HT-2500toInf_MC2017.root");
        TTFileNames.push_back("tree_TTJets_SingleLeptFromT_MC2017.root");
        TTFileNames.push_back("tree_TTJets_SingleLeptFromTbar_MC2017.root");
        TTFileNames.push_back("tree_TTJets_DiLept_MC2017.root");        
        TT = new TChain("tree");
        for( int i = 0 ; i < TTFileNames.size() ; i++ ){
            TT->Add(skimTypeMC+"/"+TTFileNames[i]);
        }
        if( r == kSignal || r == kSLm || r == kSLe || r == kLowDphi ){
            ntuples.push_back(new RA2bTree(TT));
            sampleName.push_back("TT");
            fillColor.push_back(kCyan);
            lineColor.push_back(kCyan);
        }

        std::vector<TString> DYFileNames;
        DYFileNames.push_back("tree_DYJetsToLL_M-50_HT-100to200_MC2017.root");
        DYFileNames.push_back("tree_DYJetsToLL_M-50_HT-200to400_MC2017.root");
        DYFileNames.push_back("tree_DYJetsToLL_M-50_HT-400to600_MC2017.root");
        DYFileNames.push_back("tree_DYJetsToLL_M-50_HT-600toInf_MC2017.root");
        DY = new TChain("tree");
        for( int i = 0 ; i < DYFileNames.size() ; i++ ){
            DY->Add(skimTypeMC+"/"+DYFileNames[i]);
            //DY->Add(skimTypeLDP+"/"+DYFileNames[i]);
        }
        //ntuples.push_back(new RA2bTree(DY));
        //sampleName.push_back("DY");
        //fillColor.push_back(kGreen);
        //lineColor.push_back(1);

        std::vector<TString> GJets0p4FileNames;
        GJets0p4FileNames.push_back("tree_GJets_DR-0p4_HT-100to200_MC2017.root");
        GJets0p4FileNames.push_back("tree_GJets_DR-0p4_HT-200to400_MC2017.root");
        GJets0p4FileNames.push_back("tree_GJets_DR-0p4_HT-400to600_MC2017.root");
        GJets0p4FileNames.push_back("tree_GJets_DR-0p4_HT-600toInf_MC2017.root");
        GJets0p4 = new TChain("tree");
        for( int i = 0 ; i < GJets0p4FileNames.size() ; i++ ){
            GJets0p4->Add(skimTypeMC+"/"+GJets0p4FileNames[i]);
        }
        if( r == kPhoton ){
            ntuples.push_back(new RA2bTree(GJets0p4));
            sampleName.push_back("GJets");
            fillColor.push_back(kGreen);
            lineColor.push_back(1);
        }

        std::vector<TString> GJetsFileNames;
        GJetsFileNames.push_back("tree_GJets_HT-100to200_MC2017.root");
        GJetsFileNames.push_back("tree_GJets_HT-200to400_MC2017.root");
        GJetsFileNames.push_back("tree_GJets_HT-400to600_MC2017.root");
        GJetsFileNames.push_back("tree_GJets_HT-600toInf_MC2017.root");
        GJets = new TChain("tree");
        for( int i = 0 ; i < GJetsFileNames.size() ; i++ ){
            GJets->Add(skimTypeMC+"/"+GJetsFileNames[i]);
        }
        std::vector<TString> QCDFileNames;
        QCDFileNames.push_back("tree_QCD_HT-200to300_MC2017.root");
        QCDFileNames.push_back("tree_QCD_HT-300to500_MC2017.root");
        QCDFileNames.push_back("tree_QCD_HT-500to700_MC2017.root");
        QCDFileNames.push_back("tree_QCD_HT-700to1000_MC2017.root");
        QCDFileNames.push_back("tree_QCD_HT-1000to1500_MC2017.root");
        QCDFileNames.push_back("tree_QCD_HT-1500to2000_MC2017.root");
        QCDFileNames.push_back("tree_QCD_HT-2000toInf_MC2017.root");
        QCD = new TChain("tree");
        for( int i = 0 ; i < QCDFileNames.size() ; i++ ){
            QCD->Add(skimTypeMC+"/"+QCDFileNames[i]);
        }
        if( r == kSignal || r == kPhoton || r == kLowDphi ){
            ntuples.push_back(new RA2bTree(QCD));
            sampleName.push_back("QCD");
            fillColor.push_back(kGray);
            lineColor.push_back(1);
        }

        ////////////////////////////////////////////////////////////
        // - - - - - - - - - - - DATA INPUTS - - - - - - - - - -  //
        ////////////////////////////////////////////////////////////

        std::vector<TString> HTMHTFileNames;
        HTMHTFileNames.push_back("tree_HTMHT_2016B.root");
        HTMHTFileNames.push_back("tree_HTMHT_2016C.root");
        HTMHTFileNames.push_back("tree_HTMHT_2016D.root");
        HTMHTFileNames.push_back("tree_HTMHT_2016E.root");
        HTMHTFileNames.push_back("tree_HTMHT_2016F.root");
        HTMHTFileNames.push_back("tree_HTMHT_2016G.root");
        HTMHTFileNames.push_back("tree_HTMHT_2016H.root");
       // HTMHTFileNames.push_back("tree_HTMHT_re2016H3.root");
        if( r == kSignal || r == kLowDphi ){
            data = new TChain("tree");
            for( int i = 0 ; i < HTMHTFileNames.size() ; i++ ){
                data->Add(skimType+"/"+HTMHTFileNames[i]);
            }    
            dataNtuple = new RA2bTree(data);
	    ntuples.push_back(dataNtuple);
	    sampleName.push_back("data"); 
	    fillColor.push_back(kWhite);
	    lineColor.push_back(1);
        }
        
	HTMHTFileNames.resize(0);
        HTMHTFileNames.push_back("tree_HTMHT_2017B.root");
        HTMHTFileNames.push_back("tree_HTMHT_2017C.root");
        HTMHTFileNames.push_back("tree_HTMHT_2017D.root");
        HTMHTFileNames.push_back("tree_HTMHT_2017E.root");
        HTMHTFileNames.push_back("tree_HTMHT_2017F.root");
       // HTMHTFileNames.push_back("tree_HTMHT_re2016H3.root");
        if( r == kSignal || r == kLowDphi ){
            data2017 = new TChain("tree");
            for( int i = 0 ; i < HTMHTFileNames.size() ; i++ ){
                data2017->Add(skimType+"/"+HTMHTFileNames[i]);
            }    
            dataNtuple = new RA2bTree(data2017);
	    ntuples.push_back(dataNtuple);
	    sampleName.push_back("data2017"); 
	    fillColor.push_back(kWhite);
	    lineColor.push_back(1);
        }

        std::vector<TString> SingleElectronNames;
        SingleElectronNames.push_back("tree_SingleElectron_2016B.root");
        SingleElectronNames.push_back("tree_SingleElectron_2016C.root");
        SingleElectronNames.push_back("tree_SingleElectron_2016D.root");
        SingleElectronNames.push_back("tree_SingleElectron_2016E.root");
        SingleElectronNames.push_back("tree_SingleElectron_2016F.root");
        SingleElectronNames.push_back("tree_SingleElectron_2016G.root");
        SingleElectronNames.push_back("tree_SingleElectron_2016H.root");
        if( r == kSLe ){
            data = new TChain("tree");
            for( int i = 0 ; i < SingleElectronNames.size() ; i++ ){
                data->Add(skimType+"/"+SingleElectronNames[i]);
	
            }
            dataNtuple = new RA2bTree(data);
	    ntuples.push_back(dataNtuple);
	    sampleName.push_back("data"); 
	    fillColor.push_back(kBlack);
	    lineColor.push_back(1);

        }

        std::vector<TString> SingleMuonNames;
        SingleMuonNames.push_back("tree_SingleMuon_2016B.root");
        SingleMuonNames.push_back("tree_SingleMuon_2016C.root");
        SingleMuonNames.push_back("tree_SingleMuon_2016D.root");
        SingleMuonNames.push_back("tree_SingleMuon_2016E.root");
        SingleMuonNames.push_back("tree_SingleMuon_2016F.root");
        SingleMuonNames.push_back("tree_SingleMuon_2016G.root");
        SingleMuonNames.push_back("tree_SingleMuon_2016H.root");
        if( r == kSLm ){
            data = new TChain("tree");
            for( int i = 0 ; i < SingleMuonNames.size() ; i++ ){
                data->Add(skimType+"/"+SingleMuonNames[i]);
            }
            dataNtuple = new RA2bTree(data);
	    ntuples.push_back(dataNtuple);
	    sampleName.push_back("data"); 
	    fillColor.push_back(kBlack);
	    lineColor.push_back(1);
        }
        SingleElectronNames.resize(0);
        SingleElectronNames.push_back("tree_SingleElectron_2017B.root");
        SingleElectronNames.push_back("tree_SingleElectron_2017C.root");
        SingleElectronNames.push_back("tree_SingleElectron_2017D.root");
        SingleElectronNames.push_back("tree_SingleElectron_2017E.root");
        SingleElectronNames.push_back("tree_SingleElectron_2017F.root");
        if( r == kSLe ){
            data2017 = new TChain("tree");
            for( int i = 0 ; i < SingleElectronNames.size() ; i++ ){
                data2017->Add(skimType+"/"+SingleElectronNames[i]);
	
            }
            dataNtuple2017 = new RA2bTree(data2017);
	    ntuples.push_back(dataNtuple2017);
	    sampleName.push_back("data2017"); 
	    fillColor.push_back(kBlack);
	    lineColor.push_back(1);

        }
/*
        SingleElectronNames.resize(0);
        SingleElectronNames.push_back("tree_SingleElectron_2018B.root");
        SingleElectronNames.push_back("tree_SingleElectron_2018C.root");
        SingleElectronNames.push_back("tree_SingleElectron_2018D.root");
        SingleElectronNames.push_back("tree_SingleElectron_2018E.root");
        SingleElectronNames.push_back("tree_SingleElectron_2018F.root");
        if( r == kSLe ){
            data2018 = new TChain("tree");
            for( int i = 0 ; i < SingleElectronNames.size() ; i++ ){
                data2017->Add(skimType+"/"+SingleElectronNames[i]);

            }
            dataNtuple2018 = new RA2bTree(data2018);
            ntuples.push_back(dataNtuple2018);
            sampleName.push_back("data2018");
            fillColor.push_back(kBlack);
            lineColor.push_back(1);

        }
*/
        SingleMuonNames.resize(0);
        SingleMuonNames.push_back("tree_SingleMuon_2017B.root");
        SingleMuonNames.push_back("tree_SingleMuon_2017C.root");
        SingleMuonNames.push_back("tree_SingleMuon_2017D.root");
        SingleMuonNames.push_back("tree_SingleMuon_2017E.root");
        SingleMuonNames.push_back("tree_SingleMuon_2017F.root");
        if( r == kSLm ){
            data2017 = new TChain("tree");
            for( int i = 0 ; i < SingleMuonNames.size() ; i++ ){
                data2017->Add(skimType+"/"+SingleMuonNames[i]);
            }
            dataNtuple2017 = new RA2bTree(data2017);
	    ntuples.push_back(dataNtuple2017);
	    sampleName.push_back("data2017"); 
	    fillColor.push_back(kBlack);
	    lineColor.push_back(1);
        }
        SingleMuonNames.resize(0);
        SingleMuonNames.push_back("tree_SingleMuon_2018A.root");
        SingleMuonNames.push_back("tree_SingleMuon_2018B.root");
        SingleMuonNames.push_back("tree_SingleMuon_2018C.root");
        SingleMuonNames.push_back("tree_SingleMuon_2018D.root");
        if( r == kSLm ){
            data2018 = new TChain("tree");
            for( int i = 0 ; i < SingleMuonNames.size() ; i++ ){
                data2018->Add(skimType+"/"+SingleMuonNames[i]);
            }
            dataNtuple2018 = new RA2bTree(data2018);
	    ntuples.push_back(dataNtuple2018);
	    sampleName.push_back("data2018"); 
	    fillColor.push_back(kBlack);
	    lineColor.push_back(1);
        }
        std::vector<TString> SinglePhotonFileNames;
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2016B.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2016C.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2016D.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2016E.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2016F.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2016G.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2016H.root");
        if( r == kPhoton ){
            data = new TChain("tree");
            for( int i = 0 ; i < SinglePhotonFileNames.size() ; i++ ){
                data->Add(skimType+"/"+SinglePhotonFileNames[i]);
            }
            dataNtuple = new RA2bTree(data);
	    ntuples.push_back(dataNtuple);
	    sampleName.push_back("data"); 
	    fillColor.push_back(kBlack);
	    lineColor.push_back(1);
        }
        SinglePhotonFileNames.resize(0);
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2017B.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2017C.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2017D.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2017E.root");
        SinglePhotonFileNames.push_back("tree_SinglePhoton_2017F.root");
        if( r == kPhoton ){
            data2017 = new TChain("tree");
            for( int i = 0 ; i < SinglePhotonFileNames.size() ; i++ ){
                data2017->Add(skimType+"/"+SinglePhotonFileNames[i]);
            }
            dataNtuple = new RA2bTree(data2017);
	    ntuples.push_back(dataNtuple);
	    sampleName.push_back("data2017"); 
	    fillColor.push_back(kBlack);
	    lineColor.push_back(1);
        }
/*
        SinglePhotonFileNames.resize(0);
        SinglePhotonFileNames.push_back("tree_EGamma_2018A.root");
        SinglePhotonFileNames.push_back("tree_EGamma_2018B.root");
        SinglePhotonFileNames.push_back("tree_EGamma_2018C.root");
        SinglePhotonFileNames.push_back("tree_EGamma_2018D.root");
        if( r == kPhoton ){
            data2018 = new TChain("tree");
            for( int i = 0 ; i < SinglePhotonFileNames.size() ; i++ ){
                data2018->Add(skimType+"/"+SinglePhotonFileNames[i]);
            }
            dataNtuple = new RA2bTree(data2018);
            ntuples.push_back(dataNtuple);
            sampleName.push_back("data2018");
            fillColor.push_back(kBlack);
            lineColor.push_back(1);
        }
*/
        std::vector<TString> T5HH750FilesNames;
        std::vector<TString> T5HH1000FilesNames;
        std::vector<TString> T5HH1100FilesNames;
        std::vector<TString> T5HH1200FilesNames;
        std::vector<TString> T5HH1300FilesNames;
        std::vector<TString> T5HH1400FilesNames;
        std::vector<TString> T5HH1500FilesNames;
        std::vector<TString> T5HH1600FilesNames;
        std::vector<TString> T5HH1700FilesNames;
        std::vector<TString> T5HH1800FilesNames;
        std::vector<TString> T5HH1900FilesNames;
        std::vector<TString> T5HH2000FilesNames;
        std::vector<TString> T5HH2100FilesNames;

	T5HH750FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_750_MC2016.root");
	T5HH1000FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1000_MC2016.root");
	T5HH1100FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1100_MC2016.root");
	T5HH1200FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1200_MC2016.root");
	T5HH1300FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1300_MC2016.root");
	T5HH1400FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1400_MC2016.root");
	T5HH1500FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1500_MC2016.root");
	T5HH1600FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1600_MC2016.root");
	T5HH1700FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1700_MC2016.root");
	T5HH1800FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1800_MC2016.root");
	T5HH1900FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_1900_MC2016.root");
	T5HH2000FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_2000_MC2016.root");
	T5HH2100FilesNames.push_back("root://cmseos.fnal.gov//store/user/rgp230/SUSY/T5ZH/RA2ProductionV16/tree_T5qqqqZH_2100_MC2016.root");

	/*
        for(unsigned int i=0; i<14; ++i)T5HH750FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino750_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<19; ++i)T5HH1000FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<11; ++i)T5HH1100FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<22; ++i)T5HH1200FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<13; ++i)T5HH1300FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<19; ++i)T5HH1400FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<25; ++i)T5HH1500FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<15; ++i)T5HH1600FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<8; ++i)T5HH1700FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<9; ++i)T5HH1800FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<9; ++i)T5HH1900FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino1900_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<29; ++i)T5HH2000FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
        for(unsigned int i=0; i<26; ++i)T5HH2100FilesNames.push_back(TString::Format("root://cmseos.fnal.gov//store/user/fojensen/T5qqqqZHProduction_21022018/Summer16.SMS-T5qqqqZH-mGluino2100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%d_RA2AnalysisTree.root",i));
	 */
        if( r == kSignal ){
            T5HH750 = new TChain("tree");
            for( int i = 0 ; i < T5HH750FilesNames.size() ; i++ ){
                T5HH750->Add(T5HH750FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH750));
            signalSampleName.push_back("T5HH750");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
	
            T5HH1000 = new TChain("tree");
            for( int i = 0 ; i < T5HH1000FilesNames.size() ; i++ ){
                T5HH1000->Add(T5HH1000FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1000));
            signalSampleName.push_back("T5HH1000");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
            T5HH1100 = new TChain("tree");
            for( int i = 0 ; i < T5HH1100FilesNames.size() ; i++ ){
                T5HH1100->Add(T5HH1100FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1100));
            signalSampleName.push_back("T5HH1100");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
            T5HH1200 = new TChain("tree");
            for( int i = 0 ; i < T5HH1200FilesNames.size() ; i++ ){
                T5HH1200->Add(T5HH1200FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1200));
            signalSampleName.push_back("T5HH1200");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
            T5HH1300 = new TChain("tree");
            for( int i = 0 ; i < T5HH1300FilesNames.size() ; i++ ){
                T5HH1300->Add(T5HH1300FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1300));
            signalSampleName.push_back("T5HH1300");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
            T5HH1400 = new TChain("tree");
            for( int i = 0 ; i < T5HH1400FilesNames.size() ; i++ ){
                T5HH1400->Add(T5HH1400FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1400));
            signalSampleName.push_back("T5HH1400");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
            T5HH1500 = new TChain("tree");
            for( int i = 0 ; i < T5HH1500FilesNames.size() ; i++ ){
                T5HH1500->Add(T5HH1500FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1500));
            signalSampleName.push_back("T5HH1500");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
            T5HH1600 = new TChain("tree");
            for( int i = 0 ; i < T5HH1600FilesNames.size() ; i++ ){
                T5HH1600->Add(T5HH1600FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1600));
            signalSampleName.push_back("T5HH1600");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
            T5HH1700 = new TChain("tree");
            for( int i = 0 ; i < T5HH1700FilesNames.size() ; i++ ){
                T5HH1700->Add(T5HH1700FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1700));
            signalSampleName.push_back("T5HH1700");
            sigLineColor.push_back(kOrange);
        }
        if( r == kSignal ){
            T5HH1800 = new TChain("tree");
            for( int i = 0 ; i < T5HH1800FilesNames.size() ; i++ ){
                T5HH1800->Add(T5HH1800FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1800));
            signalSampleName.push_back("T5HH1800");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
            T5HH1900 = new TChain("tree");
            for( int i = 0 ; i < T5HH1900FilesNames.size() ; i++ ){
                T5HH1900->Add(T5HH1900FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH1900));
            signalSampleName.push_back("T5HH1900");
            sigLineColor.push_back(kRed);
        }
	
        if( r == kSignal ){
            T5HH2000 = new TChain("tree");
            for( int i = 0 ; i < T5HH2000FilesNames.size() ; i++ ){
                T5HH2000->Add(T5HH2000FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH2000));
            signalSampleName.push_back("T5HH2000");
            sigLineColor.push_back(kRed);
        }
        if( r == kSignal ){
            T5HH2100 = new TChain("tree");
            for( int i = 0 ; i < T5HH2100FilesNames.size() ; i++ ){
                T5HH2100->Add(T5HH2100FilesNames[i]);
            }
            signalNtuples.push_back(new RA2bTree(T5HH2100));
            signalSampleName.push_back("T5HH2100");
            sigLineColor.push_back(kRed);
        }
    };

    RA2bTree* findNtuple(TString name){
        for( int iSam = 0 ; iSam < sampleName.size() ; iSam++ ){
            if( sampleName[iSam] == name )
                return ntuples[iSam] ;
        }
        for( int iSam = 0 ; iSam < signalSampleName.size() ; iSam++ ){
            if( signalSampleName[iSam] == name )
                return signalNtuples[iSam] ;
        }
        return NULL;
    };

};
