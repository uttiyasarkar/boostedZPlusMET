//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Oct 13 16:59:39 2018 by ROOT version 6.10/09
// from TTree tree/all observables, signal
// found on file: /eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV15/tree_signal/tree_MET_2016B.root
//////////////////////////////////////////////////////////

#ifndef RA2bTree_h
#define RA2bTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"

// Header file for the classes stored in the TTree if any.
#include "vector"
using namespace std;
class RA2bTree {
public :
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          RunNum;
   UInt_t          LumiBlockNum;
   ULong64_t       EvtNum;
   Bool_t          BadChargedCandidateFilter;
   Bool_t          BadPFMuonFilter;
   Int_t           BTags;
   Int_t           BTagsDeepCSV;
   Double_t        CaloMET;
   Double_t        CaloMETPhi;
   Int_t           CSCTightHaloFilter;
   Double_t        DeltaPhi1;
   Double_t        DeltaPhi1_AK8;
   Double_t        DeltaPhi2;
   Double_t        DeltaPhi2_AK8;
   Double_t        DeltaPhi3;
   Double_t        DeltaPhi4;
   Double_t        DeltaPhiMin_AK8;
   Int_t           ecalBadCalibFilter;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           eeBadScFilter;
   vector<TLorentzVector> *Electrons;
   vector<int>     *Electrons_charge;
   vector<bool>    *Electrons_mediumID;
   vector<double>  *Electrons_MiniIso;
   vector<double>  *Electrons_MT2Activity;
   vector<double>  *Electrons_MTW;
   vector<bool>    *Electrons_passIso;
   vector<bool>    *Electrons_tightID;
   vector<TLorentzVector> *GenParticles;
   vector<int>     *GenParticles_ParentId;
   vector<int>     *GenParticles_ParentIdx;
   vector<int>     *GenParticles_PdgId;
   vector<int>     *GenParticles_Status;
   vector<TLorentzVector> *GenTaus;
   vector<bool>    *GenTaus_had;
   Int_t           globalSuperTightHalo2016Filter;
   Int_t           globalTightHalo2016Filter;
   Bool_t          hasGenPromptPhoton;
   Int_t           HBHEIsoNoiseFilter;
   Int_t           HBHENoiseFilter;
   Double_t        HT;
   Double_t        HT5;
   Double_t        HTOnline;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Bool_t          JetID;
   Bool_t          JetIDAK8;
   vector<TLorentzVector> *Jets;
   vector<double>  *Jets_axismajor;
   vector<double>  *Jets_axisminor;
   vector<double>  *Jets_bDiscriminatorCSV;
   vector<double>  *Jets_bJetTagDeepCSVBvsAll;
   vector<double>  *Jets_bJetTagDeepCSVCvsB;
   vector<double>  *Jets_bJetTagDeepCSVCvsL;
   vector<double>  *Jets_bJetTagDeepCSVprobb;
   vector<double>  *Jets_bJetTagDeepCSVprobbb;
   vector<double>  *Jets_bJetTagDeepCSVprobc;
   vector<double>  *Jets_bJetTagDeepCSVprobudsg;
   vector<double>  *Jets_bJetTagDeepFlavourprobb;
   vector<double>  *Jets_bJetTagDeepFlavourprobbb;
   vector<double>  *Jets_bJetTagDeepFlavourprobc;
   vector<double>  *Jets_bJetTagDeepFlavourprobg;
   vector<double>  *Jets_bJetTagDeepFlavourproblepb;
   vector<double>  *Jets_bJetTagDeepFlavourprobuds;
   vector<double>  *Jets_chargedEmEnergyFraction;
   vector<double>  *Jets_chargedHadronEnergyFraction;
   vector<int>     *Jets_chargedHadronMultiplicity;
   vector<int>     *Jets_chargedMultiplicity;
   vector<double>  *Jets_electronEnergyFraction;
   vector<int>     *Jets_electronMultiplicity;
   vector<int>     *Jets_hadronFlavor;
   vector<double>  *Jets_hfEMEnergyFraction;
   vector<double>  *Jets_hfHadronEnergyFraction;
   vector<bool>    *Jets_HTMask;
   vector<bool>    *Jets_ID;
   vector<double>  *Jets_jecFactor;
   vector<double>  *Jets_jecUnc;
   vector<bool>    *Jets_LeptonMask;
   vector<bool>    *Jets_MHTMask;
   vector<int>     *Jets_multiplicity;
   vector<double>  *Jets_muonEnergyFraction;
   vector<int>     *Jets_muonMultiplicity;
   vector<double>  *Jets_neutralEmEnergyFraction;
   vector<double>  *Jets_neutralHadronEnergyFraction;
   vector<int>     *Jets_neutralHadronMultiplicity;
   vector<int>     *Jets_neutralMultiplicity;
   vector<int>     *Jets_partonFlavor;
   vector<double>  *Jets_photonEnergyFraction;
   vector<int>     *Jets_photonMultiplicity;
   vector<double>  *Jets_ptD;
   vector<double>  *Jets_qgLikelihood;
   vector<TLorentzVector> *JetsAK8;
   vector<double>  *JetsAK8_axismajor;
   vector<double>  *JetsAK8_axisminor;
   vector<double>  *JetsAK8_doubleBDiscriminator;
   vector<double>  *JetsAK8_ecfN2b1;
   vector<double>  *JetsAK8_ecfN2b2;
   vector<double>  *JetsAK8_ecfN3b1;
   vector<double>  *JetsAK8_ecfN3b2;
   vector<double>  *JetsAK8_girth;
   vector<double>  *JetsAK8_hDiscriminatorDeep;
   vector<double>  *JetsAK8_hDiscriminatorDeepDecorrel;
   vector<bool>    *JetsAK8_ID;
   vector<double>  *JetsAK8_lean;
   vector<double>  *JetsAK8_momenthalf;
   vector<int>     *JetsAK8_multiplicity;
   vector<double>  *JetsAK8_NsubjettinessTau1;
   vector<double>  *JetsAK8_NsubjettinessTau2;
   vector<double>  *JetsAK8_NsubjettinessTau3;
   vector<int>     *JetsAK8_NumBhadrons;
   vector<int>     *JetsAK8_NumChadrons;
   vector<double>  *JetsAK8_overflow;
   vector<double>  *JetsAK8_prunedMass;
   vector<double>  *JetsAK8_ptD;
   vector<double>  *JetsAK8_ptdrlog;
   vector<double>  *JetsAK8_softDropMass;
   vector<vector<TLorentzVector> > *JetsAK8_subjets;
   vector<vector<double> > *JetsAK8_subjets_axismajor;
   vector<vector<double> > *JetsAK8_subjets_axisminor;
   vector<vector<double> > *JetsAK8_subjets_bDiscriminatorCSV;
   vector<vector<int> > *JetsAK8_subjets_multiplicity;
   vector<vector<double> > *JetsAK8_subjets_ptD;
   vector<double>  *JetsAK8_tDiscriminatorDeep;
   vector<double>  *JetsAK8_tDiscriminatorDeepDecorrel;
   vector<double>  *JetsAK8_wDiscriminatorDeep;
   vector<double>  *JetsAK8_wDiscriminatorDeepDecorrel;
   vector<double>  *JetsAK8_zDiscriminatorDeep;
   vector<double>  *JetsAK8_zDiscriminatorDeepDecorrel;
   Double_t        madHT;
   Double_t        MET;
   Double_t        METPhi;
   Double_t        METSignificance;
   Double_t        MHT;
   Double_t        MHTOnline;
   Double_t        MHTPhi;
   Double_t        MJJ_AK8;
   Double_t        Mmc_AK8;
   Double_t        MT2;
   Double_t        MT_AK8;
   vector<TLorentzVector> *Muons;
   vector<int>     *Muons_charge;
   vector<double>  *Muons_MiniIso;
   vector<double>  *Muons_MT2Activity;
   vector<double>  *Muons_MTW;
   vector<bool>    *Muons_passIso;
   vector<bool>    *Muons_tightID;
   Int_t           nAllVertices;
   Int_t           NElectrons;
   Int_t           NJets;
   Int_t           NMuons;
   Int_t           NVtx;
   Double_t        PFCaloMETRatio;
   vector<TLorentzVector> *Photons;
   vector<bool>    *Photons_electronFakes;
   vector<bool>    *Photons_fullID;
   vector<double>  *Photons_genMatched;
   vector<double>  *Photons_hadTowOverEM;
   vector<double>  *Photons_hasPixelSeed;
   vector<double>  *Photons_isEB;
   vector<bool>    *Photons_nonPrompt;
   vector<double>  *Photons_passElectronVeto;
   vector<double>  *Photons_pfChargedIso;
   vector<double>  *Photons_pfChargedIsoRhoCorr;
   vector<double>  *Photons_pfGammaIso;
   vector<double>  *Photons_pfGammaIsoRhoCorr;
   vector<double>  *Photons_pfNeutralIso;
   vector<double>  *Photons_pfNeutralIsoRhoCorr;
   vector<double>  *Photons_sigmaIetaIeta;
   Double_t        PrescaleWeightHT;
   Int_t           PrimaryVertexFilter;
   vector<TLorentzVector> *TAPElectronTracks;
   vector<double>  *TAPElectronTracks_activity;
   vector<int>     *TAPElectronTracks_charge;
   vector<double>  *TAPElectronTracks_mT;
   vector<double>  *TAPElectronTracks_trkiso;
   vector<TLorentzVector> *TAPMuonTracks;
   vector<double>  *TAPMuonTracks_activity;
   vector<int>     *TAPMuonTracks_charge;
   vector<double>  *TAPMuonTracks_mT;
   vector<double>  *TAPMuonTracks_trkiso;
   vector<TLorentzVector> *TAPPionTracks;
   vector<double>  *TAPPionTracks_activity;
   vector<int>     *TAPPionTracks_charge;
   vector<double>  *TAPPionTracks_mT;
   vector<double>  *TAPPionTracks_trkiso;
   vector<string>  *TriggerNames;
   vector<int>     *TriggerPass;
   vector<int>     *TriggerPrescales;
   vector<int>     *TriggerVersion;
   Double_t        Weight;
   vector<TLorentzVector> *ZCandidates;
   UInt_t          RA2bin;

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_LumiBlockNum;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_BadChargedCandidateFilter;   //!
   TBranch        *b_BadPFMuonFilter;   //!
   TBranch        *b_BTags;   //!
   TBranch        *b_BTagsDeepCSV;   //!
   TBranch        *b_CaloMET;   //!
   TBranch        *b_CaloMETPhi;   //!
   TBranch        *b_CSCTightHaloFilter;   //!
   TBranch        *b_DeltaPhi1;   //!
   TBranch        *b_DeltaPhi1_AK8;   //!
   TBranch        *b_DeltaPhi2;   //!
   TBranch        *b_DeltaPhi2_AK8;   //!
   TBranch        *b_DeltaPhi3;   //!
   TBranch        *b_DeltaPhi4;   //!
   TBranch        *b_DeltaPhiMin_AK8;   //!
   TBranch        *b_ecalBadCalibFilter;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_eeBadScFilter;   //!
   TBranch        *b_Electrons;   //!
   TBranch        *b_Electrons_charge;   //!
   TBranch        *b_Electrons_mediumID;   //!
   TBranch        *b_Electrons_MiniIso;   //!
   TBranch        *b_Electrons_MT2Activity;   //!
   TBranch        *b_Electrons_MTW;   //!
   TBranch        *b_Electrons_passIso;   //!
   TBranch        *b_Electrons_tightID;   //!
   TBranch        *b_GenParticles;   //!
   TBranch        *b_GenParticles_ParentId;   //!
   TBranch        *b_GenParticles_ParentIdx;   //!
   TBranch        *b_GenParticles_PdgId;   //!
   TBranch        *b_GenParticles_Status;   //!
   TBranch        *b_GenTaus;   //!
   TBranch        *b_GenTaus_had;   //!
   TBranch        *b_globalSuperTightHalo2016Filter;   //!
   TBranch        *b_globalTightHalo2016Filter;   //!
   TBranch        *b_hasGenPromptPhoton;   //!
   TBranch        *b_HBHEIsoNoiseFilter;   //!
   TBranch        *b_HBHENoiseFilter;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_HT5;   //!
   TBranch        *b_HTOnline;   //!
   TBranch        *b_isoElectronTracks;   //!
   TBranch        *b_isoMuonTracks;   //!
   TBranch        *b_isoPionTracks;   //!
   TBranch        *b_JetID;   //!
   TBranch        *b_JetIDAK8;   //!
   TBranch        *b_Jets;   //!
   TBranch        *b_Jets_axismajor;   //!
   TBranch        *b_Jets_axisminor;   //!
   TBranch        *b_Jets_bDiscriminatorCSV;   //!
   TBranch        *b_Jets_bJetTagDeepCSVBvsAll;   //!
   TBranch        *b_Jets_bJetTagDeepCSVCvsB;   //!
   TBranch        *b_Jets_bJetTagDeepCSVCvsL;   //!
   TBranch        *b_Jets_bJetTagDeepCSVprobb;   //!
   TBranch        *b_Jets_bJetTagDeepCSVprobbb;   //!
   TBranch        *b_Jets_bJetTagDeepCSVprobc;   //!
   TBranch        *b_Jets_bJetTagDeepCSVprobudsg;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobb;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobbb;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobc;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobg;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourproblepb;   //!
   TBranch        *b_Jets_bJetTagDeepFlavourprobuds;   //!
   TBranch        *b_Jets_chargedEmEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronMultiplicity;   //!
   TBranch        *b_Jets_chargedMultiplicity;   //!
   TBranch        *b_Jets_electronEnergyFraction;   //!
   TBranch        *b_Jets_electronMultiplicity;   //!
   TBranch        *b_Jets_hadronFlavor;   //!
   TBranch        *b_Jets_hfEMEnergyFraction;   //!
   TBranch        *b_Jets_hfHadronEnergyFraction;   //!
   TBranch        *b_Jets_HTMask;   //!
   TBranch        *b_Jets_ID;   //!
   TBranch        *b_Jets_jecFactor;   //!
   TBranch        *b_Jets_jecUnc;   //!
   TBranch        *b_Jets_LeptonMask;   //!
   TBranch        *b_Jets_MHTMask;   //!
   TBranch        *b_Jets_multiplicity;   //!
   TBranch        *b_Jets_muonEnergyFraction;   //!
   TBranch        *b_Jets_muonMultiplicity;   //!
   TBranch        *b_Jets_neutralEmEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronMultiplicity;   //!
   TBranch        *b_Jets_neutralMultiplicity;   //!
   TBranch        *b_Jets_partonFlavor;   //!
   TBranch        *b_Jets_photonEnergyFraction;   //!
   TBranch        *b_Jets_photonMultiplicity;   //!
   TBranch        *b_Jets_ptD;   //!
   TBranch        *b_Jets_qgLikelihood;   //!
   TBranch        *b_JetsAK8;   //!
   TBranch        *b_JetsAK8_axismajor;   //!
   TBranch        *b_JetsAK8_axisminor;   //!
   TBranch        *b_JetsAK8_doubleBDiscriminator;   //!
   TBranch        *b_JetsAK8_ecfN2b1;   //!
   TBranch        *b_JetsAK8_ecfN2b2;   //!
   TBranch        *b_JetsAK8_ecfN3b1;   //!
   TBranch        *b_JetsAK8_ecfN3b2;   //!
   TBranch        *b_JetsAK8_girth;   //!
   TBranch        *b_JetsAK8_hDiscriminatorDeep;   //!
   TBranch        *b_JetsAK8_hDiscriminatorDeepDecorrel;   //!
   TBranch        *b_JetsAK8_ID;   //!
   TBranch        *b_JetsAK8_lean;   //!
   TBranch        *b_JetsAK8_momenthalf;   //!
   TBranch        *b_JetsAK8_multiplicity;   //!
   TBranch        *b_JetsAK8_NsubjettinessTau1;   //!
   TBranch        *b_JetsAK8_NsubjettinessTau2;   //!
   TBranch        *b_JetsAK8_NsubjettinessTau3;   //!
   TBranch        *b_JetsAK8_NumBhadrons;   //!
   TBranch        *b_JetsAK8_NumChadrons;   //!
   TBranch        *b_JetsAK8_overflow;   //!
   TBranch        *b_JetsAK8_prunedMass;   //!
   TBranch        *b_JetsAK8_ptD;   //!
   TBranch        *b_JetsAK8_ptdrlog;   //!
   TBranch        *b_JetsAK8_softDropMass;   //!
   TBranch        *b_JetsAK8_subjets;   //!
   TBranch        *b_JetsAK8_subjets_axismajor;   //!
   TBranch        *b_JetsAK8_subjets_axisminor;   //!
   TBranch        *b_JetsAK8_subjets_bDiscriminatorCSV;   //!
   TBranch        *b_JetsAK8_subjets_multiplicity;   //!
   TBranch        *b_JetsAK8_subjets_ptD;   //!
   TBranch        *b_JetsAK8_tDiscriminatorDeep;   //!
   TBranch        *b_JetsAK8_tDiscriminatorDeepDecorrel;   //!
   TBranch        *b_JetsAK8_wDiscriminatorDeep;   //!
   TBranch        *b_JetsAK8_wDiscriminatorDeepDecorrel;   //!
   TBranch        *b_JetsAK8_zDiscriminatorDeep;   //!
   TBranch        *b_JetsAK8_zDiscriminatorDeepDecorrel;   //!
   TBranch        *b_madHT;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METPhi;   //!
   TBranch        *b_METSignificance;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_MHTOnline;   //!
   TBranch        *b_MHTPhi;   //!
   TBranch        *b_MJJ_AK8;   //!
   TBranch        *b_Mmc_AK8;   //!
   TBranch        *b_MT2;   //!
   TBranch        *b_MT_AK8;   //!
   TBranch        *b_Muons;   //!
   TBranch        *b_Muons_charge;   //!
   TBranch        *b_Muons_MiniIso;   //!
   TBranch        *b_Muons_MT2Activity;   //!
   TBranch        *b_Muons_MTW;   //!
   TBranch        *b_Muons_passIso;   //!
   TBranch        *b_Muons_tightID;   //!
   TBranch        *b_nAllVertices;   //!
   TBranch        *b_NElectrons;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_NMuons;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_PFCaloMETRatio;   //!
   TBranch        *b_Photons;   //!
   TBranch        *b_Photons_electronFakes;   //!
   TBranch        *b_Photons_fullID;   //!
   TBranch        *b_Photons_genMatched;   //!
   TBranch        *b_Photons_hadTowOverEM;   //!
   TBranch        *b_Photons_hasPixelSeed;   //!
   TBranch        *b_Photons_isEB;   //!
   TBranch        *b_Photons_nonPrompt;   //!
   TBranch        *b_Photons_passElectronVeto;   //!
   TBranch        *b_Photons_pfChargedIso;   //!
   TBranch        *b_Photons_pfChargedIsoRhoCorr;   //!
   TBranch        *b_Photons_pfGammaIso;   //!
   TBranch        *b_Photons_pfGammaIsoRhoCorr;   //!
   TBranch        *b_Photons_pfNeutralIso;   //!
   TBranch        *b_Photons_pfNeutralIsoRhoCorr;   //!
   TBranch        *b_Photons_sigmaIetaIeta;   //!
   TBranch        *b_PrescaleWeightHT;   //!
   TBranch        *b_PrimaryVertexFilter;   //!
   TBranch        *b_TAPElectronTracks;   //!
   TBranch        *b_TAPElectronTracks_activity;   //!
   TBranch        *b_TAPElectronTracks_charge;   //!
   TBranch        *b_TAPElectronTracks_mT;   //!
   TBranch        *b_TAPElectronTracks_trkiso;   //!
   TBranch        *b_TAPMuonTracks;   //!
   TBranch        *b_TAPMuonTracks_activity;   //!
   TBranch        *b_TAPMuonTracks_charge;   //!
   TBranch        *b_TAPMuonTracks_mT;   //!
   TBranch        *b_TAPMuonTracks_trkiso;   //!
   TBranch        *b_TAPPionTracks;   //!
   TBranch        *b_TAPPionTracks_activity;   //!
   TBranch        *b_TAPPionTracks_charge;   //!
   TBranch        *b_TAPPionTracks_mT;   //!
   TBranch        *b_TAPPionTracks_trkiso;   //!
   TBranch        *b_TriggerNames;   //!
   TBranch        *b_TriggerPass;   //!
   TBranch        *b_TriggerPrescales;   //!
   TBranch        *b_TriggerVersion;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_ZCandidates;   //!
   TBranch        *b_RA2binBranch;   //!

   RA2bTree(TChain *tree=0);
   virtual ~RA2bTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TChain *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef RA2bTree_cxx
RA2bTree::RA2bTree(TChain *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV15/tree_signal/tree_MET_2016B.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV15/tree_signal/tree_MET_2016B.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

RA2bTree::~RA2bTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t RA2bTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t RA2bTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void RA2bTree::Init(TChain *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Electrons = 0;
   Electrons_charge = 0;
   Electrons_mediumID = 0;
   Electrons_MiniIso = 0;
   Electrons_MT2Activity = 0;
   Electrons_MTW = 0;
   Electrons_passIso = 0;
   Electrons_tightID = 0;
   GenParticles = 0;
   GenParticles_ParentId = 0;
   GenParticles_ParentIdx = 0;
   GenParticles_PdgId = 0;
   GenParticles_Status = 0;
   GenTaus_had = 0;
   Jets = 0;
   Jets_axismajor = 0;
   Jets_axisminor = 0;
   Jets_bDiscriminatorCSV = 0;
   Jets_bJetTagDeepCSVBvsAll = 0;
   Jets_bJetTagDeepCSVCvsB = 0;
   Jets_bJetTagDeepCSVCvsL = 0;
   Jets_bJetTagDeepCSVprobb = 0;
   Jets_bJetTagDeepCSVprobbb = 0;
   Jets_bJetTagDeepCSVprobc = 0;
   Jets_bJetTagDeepCSVprobudsg = 0;
   Jets_bJetTagDeepFlavourprobb = 0;
   Jets_bJetTagDeepFlavourprobbb = 0;
   Jets_bJetTagDeepFlavourprobc = 0;
   Jets_bJetTagDeepFlavourprobg = 0;
   Jets_bJetTagDeepFlavourproblepb = 0;
   Jets_bJetTagDeepFlavourprobuds = 0;
   Jets_chargedEmEnergyFraction = 0;
   Jets_chargedHadronEnergyFraction = 0;
   Jets_chargedHadronMultiplicity = 0;
   Jets_chargedMultiplicity = 0;
   Jets_electronEnergyFraction = 0;
   Jets_electronMultiplicity = 0;
   Jets_hadronFlavor = 0;
   Jets_hfEMEnergyFraction = 0;
   Jets_hfHadronEnergyFraction = 0;
   Jets_HTMask = 0;
   Jets_ID = 0;
   Jets_jecFactor = 0;
   Jets_jecUnc = 0;
   Jets_LeptonMask = 0;
   Jets_MHTMask = 0;
   Jets_multiplicity = 0;
   Jets_muonEnergyFraction = 0;
   Jets_muonMultiplicity = 0;
   Jets_neutralEmEnergyFraction = 0;
   Jets_neutralHadronEnergyFraction = 0;
   Jets_neutralHadronMultiplicity = 0;
   Jets_neutralMultiplicity = 0;
   Jets_partonFlavor = 0;
   Jets_photonEnergyFraction = 0;
   Jets_photonMultiplicity = 0;
   Jets_ptD = 0;
   Jets_qgLikelihood = 0;
   JetsAK8 = 0;
   JetsAK8_axismajor = 0;
   JetsAK8_axisminor = 0;
   JetsAK8_doubleBDiscriminator = 0;
   JetsAK8_ecfN2b1 = 0;
   JetsAK8_ecfN2b2 = 0;
   JetsAK8_ecfN3b1 = 0;
   JetsAK8_ecfN3b2 = 0;
   JetsAK8_girth = 0;
   JetsAK8_hDiscriminatorDeep = 0;
   JetsAK8_hDiscriminatorDeepDecorrel = 0;
   JetsAK8_ID = 0;
   JetsAK8_lean = 0;
   JetsAK8_momenthalf = 0;
   JetsAK8_multiplicity = 0;
   JetsAK8_NsubjettinessTau1 = 0;
   JetsAK8_NsubjettinessTau2 = 0;
   JetsAK8_NsubjettinessTau3 = 0;
   JetsAK8_NumBhadrons = 0;
   JetsAK8_NumChadrons = 0;
   JetsAK8_overflow = 0;
   JetsAK8_prunedMass = 0;
   JetsAK8_ptD = 0;
   JetsAK8_ptdrlog = 0;
   JetsAK8_softDropMass = 0;
   JetsAK8_subjets = 0;
   JetsAK8_subjets_axismajor = 0;
   JetsAK8_subjets_axisminor = 0;
   JetsAK8_subjets_bDiscriminatorCSV = 0;
   JetsAK8_subjets_multiplicity = 0;
   JetsAK8_subjets_ptD = 0;
   JetsAK8_tDiscriminatorDeep = 0;
   JetsAK8_tDiscriminatorDeepDecorrel = 0;
   JetsAK8_wDiscriminatorDeep = 0;
   JetsAK8_wDiscriminatorDeepDecorrel = 0;
   JetsAK8_zDiscriminatorDeep = 0;
   JetsAK8_zDiscriminatorDeepDecorrel = 0;
   Muons = 0;
   Muons_charge = 0;
   Muons_MiniIso = 0;
   Muons_MT2Activity = 0;
   Muons_MTW = 0;
   Muons_passIso = 0;
   Muons_tightID = 0;
   Photons = 0;
   Photons_electronFakes = 0;
   Photons_fullID = 0;
   Photons_genMatched = 0;
   Photons_hadTowOverEM = 0;
   Photons_hasPixelSeed = 0;
   Photons_isEB = 0;
   Photons_nonPrompt = 0;
   Photons_passElectronVeto = 0;
   Photons_pfChargedIso = 0;
   Photons_pfChargedIsoRhoCorr = 0;
   Photons_pfGammaIso = 0;
   Photons_pfGammaIsoRhoCorr = 0;
   Photons_pfNeutralIso = 0;
   Photons_pfNeutralIsoRhoCorr = 0;
   Photons_sigmaIetaIeta = 0;
   TAPElectronTracks = 0;
   TAPElectronTracks_activity = 0;
   TAPElectronTracks_charge = 0;
   TAPElectronTracks_mT = 0;
   TAPElectronTracks_trkiso = 0;
   TAPMuonTracks = 0;
   TAPMuonTracks_activity = 0;
   TAPMuonTracks_charge = 0;
   TAPMuonTracks_mT = 0;
   TAPMuonTracks_trkiso = 0;
   TAPPionTracks = 0;
   TAPPionTracks_activity = 0;
   TAPPionTracks_charge = 0;
   TAPPionTracks_mT = 0;
   TAPPionTracks_trkiso = 0;
   TriggerNames = 0;
   TriggerPass = 0;
   TriggerPrescales = 0;
   TriggerVersion = 0;
   ZCandidates = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
   fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("BTagsDeepCSV", &BTagsDeepCSV, &b_BTagsDeepCSV);
   fChain->SetBranchAddress("CaloMET", &CaloMET, &b_CaloMET);
   fChain->SetBranchAddress("CaloMETPhi", &CaloMETPhi, &b_CaloMETPhi);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi1_AK8", &DeltaPhi1_AK8, &b_DeltaPhi1_AK8);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi2_AK8", &DeltaPhi2_AK8, &b_DeltaPhi2_AK8);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
   fChain->SetBranchAddress("DeltaPhiMin_AK8", &DeltaPhiMin_AK8, &b_DeltaPhiMin_AK8);
   fChain->SetBranchAddress("ecalBadCalibFilter", &ecalBadCalibFilter, &b_ecalBadCalibFilter);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
   fChain->SetBranchAddress("Electrons_charge", &Electrons_charge, &b_Electrons_charge);
   fChain->SetBranchAddress("Electrons_mediumID", &Electrons_mediumID, &b_Electrons_mediumID);
   fChain->SetBranchAddress("Electrons_MiniIso", &Electrons_MiniIso, &b_Electrons_MiniIso);
   fChain->SetBranchAddress("Electrons_MT2Activity", &Electrons_MT2Activity, &b_Electrons_MT2Activity);
   fChain->SetBranchAddress("Electrons_MTW", &Electrons_MTW, &b_Electrons_MTW);
   fChain->SetBranchAddress("Electrons_passIso", &Electrons_passIso, &b_Electrons_passIso);
   fChain->SetBranchAddress("Electrons_tightID", &Electrons_tightID, &b_Electrons_tightID);
   fChain->SetBranchAddress("GenParticles", &GenParticles, &b_GenParticles);
   fChain->SetBranchAddress("GenParticles_ParentId", &GenParticles_ParentId, &b_GenParticles_ParentId);
   fChain->SetBranchAddress("GenParticles_ParentIdx", &GenParticles_ParentIdx, &b_GenParticles_ParentIdx);
   fChain->SetBranchAddress("GenParticles_PdgId", &GenParticles_PdgId, &b_GenParticles_PdgId);
   fChain->SetBranchAddress("GenParticles_Status", &GenParticles_Status, &b_GenParticles_Status);
   fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
   fChain->SetBranchAddress("GenTaus_had", &GenTaus_had, &b_GenTaus_had);
   fChain->SetBranchAddress("globalTightHalo2016Filter", &globalTightHalo2016Filter, &b_globalTightHalo2016Filter);
   fChain->SetBranchAddress("globalSuperTightHalo2016Filter", &globalTightHalo2016Filter, &b_globalTightHalo2016Filter);
   fChain->SetBranchAddress("hasGenPromptPhoton", &hasGenPromptPhoton, &b_hasGenPromptPhoton);
   fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("HT5", &HT5, &b_HT5);
   fChain->SetBranchAddress("HTOnline", &HTOnline, &b_HTOnline);
   fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
   fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
   fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
   fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
   fChain->SetBranchAddress("JetIDAK8", &JetIDAK8, &b_JetIDAK8);
   fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
   fChain->SetBranchAddress("Jets_axismajor", &Jets_axismajor, &b_Jets_axismajor);
   fChain->SetBranchAddress("Jets_axisminor", &Jets_axisminor, &b_Jets_axisminor);
   fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVBvsAll", &Jets_bJetTagDeepCSVBvsAll, &b_Jets_bJetTagDeepCSVBvsAll);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVCvsB", &Jets_bJetTagDeepCSVCvsB, &b_Jets_bJetTagDeepCSVCvsB);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVCvsL", &Jets_bJetTagDeepCSVCvsL, &b_Jets_bJetTagDeepCSVCvsL);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobb", &Jets_bJetTagDeepCSVprobb, &b_Jets_bJetTagDeepCSVprobb);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobbb", &Jets_bJetTagDeepCSVprobbb, &b_Jets_bJetTagDeepCSVprobbb);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobc", &Jets_bJetTagDeepCSVprobc, &b_Jets_bJetTagDeepCSVprobc);
   fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobudsg", &Jets_bJetTagDeepCSVprobudsg, &b_Jets_bJetTagDeepCSVprobudsg);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobb", &Jets_bJetTagDeepFlavourprobb, &b_Jets_bJetTagDeepFlavourprobb);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobbb", &Jets_bJetTagDeepFlavourprobbb, &b_Jets_bJetTagDeepFlavourprobbb);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobc", &Jets_bJetTagDeepFlavourprobc, &b_Jets_bJetTagDeepFlavourprobc);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobg", &Jets_bJetTagDeepFlavourprobg, &b_Jets_bJetTagDeepFlavourprobg);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourproblepb", &Jets_bJetTagDeepFlavourproblepb, &b_Jets_bJetTagDeepFlavourproblepb);
   fChain->SetBranchAddress("Jets_bJetTagDeepFlavourprobuds", &Jets_bJetTagDeepFlavourprobuds, &b_Jets_bJetTagDeepFlavourprobuds);
   fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
   fChain->SetBranchAddress("Jets_chargedMultiplicity", &Jets_chargedMultiplicity, &b_Jets_chargedMultiplicity);
   fChain->SetBranchAddress("Jets_electronEnergyFraction", &Jets_electronEnergyFraction, &b_Jets_electronEnergyFraction);
   fChain->SetBranchAddress("Jets_electronMultiplicity", &Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
   fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
   fChain->SetBranchAddress("Jets_hfEMEnergyFraction", &Jets_hfEMEnergyFraction, &b_Jets_hfEMEnergyFraction);
   fChain->SetBranchAddress("Jets_hfHadronEnergyFraction", &Jets_hfHadronEnergyFraction, &b_Jets_hfHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_HTMask", &Jets_HTMask, &b_Jets_HTMask);
   fChain->SetBranchAddress("Jets_ID", &Jets_ID, &b_Jets_ID);
   fChain->SetBranchAddress("Jets_jecFactor", &Jets_jecFactor, &b_Jets_jecFactor);
   fChain->SetBranchAddress("Jets_jecUnc", &Jets_jecUnc, &b_Jets_jecUnc);
   fChain->SetBranchAddress("Jets_LeptonMask", &Jets_LeptonMask, &b_Jets_LeptonMask);
   fChain->SetBranchAddress("Jets_MHTMask", &Jets_MHTMask, &b_Jets_MHTMask);
   fChain->SetBranchAddress("Jets_multiplicity", &Jets_multiplicity, &b_Jets_multiplicity);
   fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
   fChain->SetBranchAddress("Jets_muonMultiplicity", &Jets_muonMultiplicity, &b_Jets_muonMultiplicity);
   fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronEnergyFraction", &Jets_neutralHadronEnergyFraction, &b_Jets_neutralHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity, &b_Jets_neutralHadronMultiplicity);
   fChain->SetBranchAddress("Jets_neutralMultiplicity", &Jets_neutralMultiplicity, &b_Jets_neutralMultiplicity);
   fChain->SetBranchAddress("Jets_partonFlavor", &Jets_partonFlavor, &b_Jets_partonFlavor);
   fChain->SetBranchAddress("Jets_photonEnergyFraction", &Jets_photonEnergyFraction, &b_Jets_photonEnergyFraction);
   fChain->SetBranchAddress("Jets_photonMultiplicity", &Jets_photonMultiplicity, &b_Jets_photonMultiplicity);
   fChain->SetBranchAddress("Jets_ptD", &Jets_ptD, &b_Jets_ptD);
   fChain->SetBranchAddress("Jets_qgLikelihood", &Jets_qgLikelihood, &b_Jets_qgLikelihood);
   fChain->SetBranchAddress("JetsAK8", &JetsAK8, &b_JetsAK8);
   fChain->SetBranchAddress("JetsAK8_axismajor", &JetsAK8_axismajor, &b_JetsAK8_axismajor);
   fChain->SetBranchAddress("JetsAK8_axisminor", &JetsAK8_axisminor, &b_JetsAK8_axisminor);
   fChain->SetBranchAddress("JetsAK8_doubleBDiscriminator", &JetsAK8_doubleBDiscriminator, &b_JetsAK8_doubleBDiscriminator);
   fChain->SetBranchAddress("JetsAK8_ecfN2b1", &JetsAK8_ecfN2b1, &b_JetsAK8_ecfN2b1);
   fChain->SetBranchAddress("JetsAK8_ecfN2b2", &JetsAK8_ecfN2b2, &b_JetsAK8_ecfN2b2);
   fChain->SetBranchAddress("JetsAK8_ecfN3b1", &JetsAK8_ecfN3b1, &b_JetsAK8_ecfN3b1);
   fChain->SetBranchAddress("JetsAK8_ecfN3b2", &JetsAK8_ecfN3b2, &b_JetsAK8_ecfN3b2);
   fChain->SetBranchAddress("JetsAK8_girth", &JetsAK8_girth, &b_JetsAK8_girth);
   fChain->SetBranchAddress("JetsAK8_hDiscriminatorDeep", &JetsAK8_hDiscriminatorDeep, &b_JetsAK8_hDiscriminatorDeep);
   fChain->SetBranchAddress("JetsAK8_hDiscriminatorDeepDecorrel", &JetsAK8_hDiscriminatorDeepDecorrel, &b_JetsAK8_hDiscriminatorDeepDecorrel);
   fChain->SetBranchAddress("JetsAK8_ID", &JetsAK8_ID, &b_JetsAK8_ID);
   fChain->SetBranchAddress("JetsAK8_lean", &JetsAK8_lean, &b_JetsAK8_lean);
   fChain->SetBranchAddress("JetsAK8_momenthalf", &JetsAK8_momenthalf, &b_JetsAK8_momenthalf);
   fChain->SetBranchAddress("JetsAK8_multiplicity", &JetsAK8_multiplicity, &b_JetsAK8_multiplicity);
   fChain->SetBranchAddress("JetsAK8_NsubjettinessTau1", &JetsAK8_NsubjettinessTau1, &b_JetsAK8_NsubjettinessTau1);
   fChain->SetBranchAddress("JetsAK8_NsubjettinessTau2", &JetsAK8_NsubjettinessTau2, &b_JetsAK8_NsubjettinessTau2);
   fChain->SetBranchAddress("JetsAK8_NsubjettinessTau3", &JetsAK8_NsubjettinessTau3, &b_JetsAK8_NsubjettinessTau3);
   fChain->SetBranchAddress("JetsAK8_NumBhadrons", &JetsAK8_NumBhadrons, &b_JetsAK8_NumBhadrons);
   fChain->SetBranchAddress("JetsAK8_NumChadrons", &JetsAK8_NumChadrons, &b_JetsAK8_NumChadrons);
   fChain->SetBranchAddress("JetsAK8_overflow", &JetsAK8_overflow, &b_JetsAK8_overflow);
   fChain->SetBranchAddress("JetsAK8_prunedMass", &JetsAK8_prunedMass, &b_JetsAK8_prunedMass);
   fChain->SetBranchAddress("JetsAK8_ptD", &JetsAK8_ptD, &b_JetsAK8_ptD);
   fChain->SetBranchAddress("JetsAK8_ptdrlog", &JetsAK8_ptdrlog, &b_JetsAK8_ptdrlog);
   fChain->SetBranchAddress("JetsAK8_softDropMass", &JetsAK8_softDropMass, &b_JetsAK8_softDropMass);
   fChain->SetBranchAddress("JetsAK8_subjets", &JetsAK8_subjets, &b_JetsAK8_subjets);
   fChain->SetBranchAddress("JetsAK8_subjets_axismajor", &JetsAK8_subjets_axismajor, &b_JetsAK8_subjets_axismajor);
   fChain->SetBranchAddress("JetsAK8_subjets_axisminor", &JetsAK8_subjets_axisminor, &b_JetsAK8_subjets_axisminor);
   fChain->SetBranchAddress("JetsAK8_subjets_bDiscriminatorCSV", &JetsAK8_subjets_bDiscriminatorCSV, &b_JetsAK8_subjets_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsAK8_subjets_multiplicity", &JetsAK8_subjets_multiplicity, &b_JetsAK8_subjets_multiplicity);
   fChain->SetBranchAddress("JetsAK8_subjets_ptD", &JetsAK8_subjets_ptD, &b_JetsAK8_subjets_ptD);
   fChain->SetBranchAddress("JetsAK8_tDiscriminatorDeep", &JetsAK8_tDiscriminatorDeep, &b_JetsAK8_tDiscriminatorDeep);
   fChain->SetBranchAddress("JetsAK8_tDiscriminatorDeepDecorrel", &JetsAK8_tDiscriminatorDeepDecorrel, &b_JetsAK8_tDiscriminatorDeepDecorrel);
   fChain->SetBranchAddress("JetsAK8_wDiscriminatorDeep", &JetsAK8_wDiscriminatorDeep, &b_JetsAK8_wDiscriminatorDeep);
   fChain->SetBranchAddress("JetsAK8_wDiscriminatorDeepDecorrel", &JetsAK8_wDiscriminatorDeepDecorrel, &b_JetsAK8_wDiscriminatorDeepDecorrel);
   fChain->SetBranchAddress("JetsAK8_zDiscriminatorDeep", &JetsAK8_zDiscriminatorDeep, &b_JetsAK8_zDiscriminatorDeep);
   fChain->SetBranchAddress("JetsAK8_zDiscriminatorDeepDecorrel", &JetsAK8_zDiscriminatorDeepDecorrel, &b_JetsAK8_zDiscriminatorDeepDecorrel);
   fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("METSignificance", &METSignificance, &b_METSignificance);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("MHTOnline", &MHTOnline, &b_MHTOnline);
   fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
   fChain->SetBranchAddress("MJJ_AK8", &MJJ_AK8, &b_MJJ_AK8);
   fChain->SetBranchAddress("Mmc_AK8", &Mmc_AK8, &b_Mmc_AK8);
   fChain->SetBranchAddress("MT2", &MT2, &b_MT2);
   fChain->SetBranchAddress("MT_AK8", &MT_AK8, &b_MT_AK8);
   fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
   fChain->SetBranchAddress("Muons_charge", &Muons_charge, &b_Muons_charge);
   fChain->SetBranchAddress("Muons_MiniIso", &Muons_MiniIso, &b_Muons_MiniIso);
   fChain->SetBranchAddress("Muons_MT2Activity", &Muons_MT2Activity, &b_Muons_MT2Activity);
   fChain->SetBranchAddress("Muons_MTW", &Muons_MTW, &b_Muons_MTW);
   fChain->SetBranchAddress("Muons_passIso", &Muons_passIso, &b_Muons_passIso);
   fChain->SetBranchAddress("Muons_tightID", &Muons_tightID, &b_Muons_tightID);
   fChain->SetBranchAddress("nAllVertices", &nAllVertices, &b_nAllVertices);
   fChain->SetBranchAddress("NElectrons", &NElectrons, &b_NElectrons);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("NMuons", &NMuons, &b_NMuons);
   fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
   fChain->SetBranchAddress("PFCaloMETRatio", &PFCaloMETRatio, &b_PFCaloMETRatio);
   fChain->SetBranchAddress("Photons", &Photons, &b_Photons);
   fChain->SetBranchAddress("Photons_electronFakes", &Photons_electronFakes, &b_Photons_electronFakes);
   fChain->SetBranchAddress("Photons_fullID", &Photons_fullID, &b_Photons_fullID);
   fChain->SetBranchAddress("Photons_genMatched", &Photons_genMatched, &b_Photons_genMatched);
   fChain->SetBranchAddress("Photons_hadTowOverEM", &Photons_hadTowOverEM, &b_Photons_hadTowOverEM);
   fChain->SetBranchAddress("Photons_hasPixelSeed", &Photons_hasPixelSeed, &b_Photons_hasPixelSeed);
   fChain->SetBranchAddress("Photons_isEB", &Photons_isEB, &b_Photons_isEB);
   fChain->SetBranchAddress("Photons_nonPrompt", &Photons_nonPrompt, &b_Photons_nonPrompt);
   fChain->SetBranchAddress("Photons_passElectronVeto", &Photons_passElectronVeto, &b_Photons_passElectronVeto);
   fChain->SetBranchAddress("Photons_pfChargedIso", &Photons_pfChargedIso, &b_Photons_pfChargedIso);
   fChain->SetBranchAddress("Photons_pfChargedIsoRhoCorr", &Photons_pfChargedIsoRhoCorr, &b_Photons_pfChargedIsoRhoCorr);
   fChain->SetBranchAddress("Photons_pfGammaIso", &Photons_pfGammaIso, &b_Photons_pfGammaIso);
   fChain->SetBranchAddress("Photons_pfGammaIsoRhoCorr", &Photons_pfGammaIsoRhoCorr, &b_Photons_pfGammaIsoRhoCorr);
   fChain->SetBranchAddress("Photons_pfNeutralIso", &Photons_pfNeutralIso, &b_Photons_pfNeutralIso);
   fChain->SetBranchAddress("Photons_pfNeutralIsoRhoCorr", &Photons_pfNeutralIsoRhoCorr, &b_Photons_pfNeutralIsoRhoCorr);
   fChain->SetBranchAddress("Photons_sigmaIetaIeta", &Photons_sigmaIetaIeta, &b_Photons_sigmaIetaIeta);
   fChain->SetBranchAddress("PrescaleWeightHT", &PrescaleWeightHT, &b_PrescaleWeightHT);
   fChain->SetBranchAddress("PrimaryVertexFilter", &PrimaryVertexFilter, &b_PrimaryVertexFilter);
   fChain->SetBranchAddress("TAPElectronTracks", &TAPElectronTracks, &b_TAPElectronTracks);
   fChain->SetBranchAddress("TAPElectronTracks_activity", &TAPElectronTracks_activity, &b_TAPElectronTracks_activity);
   fChain->SetBranchAddress("TAPElectronTracks_charge", &TAPElectronTracks_charge, &b_TAPElectronTracks_charge);
   fChain->SetBranchAddress("TAPElectronTracks_mT", &TAPElectronTracks_mT, &b_TAPElectronTracks_mT);
   fChain->SetBranchAddress("TAPElectronTracks_trkiso", &TAPElectronTracks_trkiso, &b_TAPElectronTracks_trkiso);
   fChain->SetBranchAddress("TAPMuonTracks", &TAPMuonTracks, &b_TAPMuonTracks);
   fChain->SetBranchAddress("TAPMuonTracks_activity", &TAPMuonTracks_activity, &b_TAPMuonTracks_activity);
   fChain->SetBranchAddress("TAPMuonTracks_charge", &TAPMuonTracks_charge, &b_TAPMuonTracks_charge);
   fChain->SetBranchAddress("TAPMuonTracks_mT", &TAPMuonTracks_mT, &b_TAPMuonTracks_mT);
   fChain->SetBranchAddress("TAPMuonTracks_trkiso", &TAPMuonTracks_trkiso, &b_TAPMuonTracks_trkiso);
   fChain->SetBranchAddress("TAPPionTracks", &TAPPionTracks, &b_TAPPionTracks);
   fChain->SetBranchAddress("TAPPionTracks_activity", &TAPPionTracks_activity, &b_TAPPionTracks_activity);
   fChain->SetBranchAddress("TAPPionTracks_charge", &TAPPionTracks_charge, &b_TAPPionTracks_charge);
   fChain->SetBranchAddress("TAPPionTracks_mT", &TAPPionTracks_mT, &b_TAPPionTracks_mT);
   fChain->SetBranchAddress("TAPPionTracks_trkiso", &TAPPionTracks_trkiso, &b_TAPPionTracks_trkiso);
   fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
   fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
   fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
   fChain->SetBranchAddress("TriggerVersion", &TriggerVersion, &b_TriggerVersion);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("ZCandidates", &ZCandidates, &b_ZCandidates);
   fChain->SetBranchAddress("RA2bin", &RA2bin, &b_RA2binBranch);
   Notify();
}

Bool_t RA2bTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void RA2bTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t RA2bTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef RA2bTree_cxx
