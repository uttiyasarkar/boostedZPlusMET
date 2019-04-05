#include "TLorentzVector.h"
#include "TRandom3.h"
// constants
// ==============================================
const double bbtagCut = 0.3;
const double tau21Cut = 0.55;
const double ZmassWindowLow = 70.;
const double ZmassWindowHigh = 100.;
const double baselineMassLow = 50.;
const double baselineMassHigh = 200.;
TFile* puWeightFile = new TFile("../data/PileupHistograms_0121_69p2mb_pm4p6.root");
TH1F* puWeightHist = (TH1F*) puWeightFile->Get("pu_weights_down");
// - - - - - - weights for WJets, GJets, - - - - - - - - 
// - - - - - - and ZJets NLO Pt distribution - - - - - - 
TFile* NLOWeightFile = new TFile("../data/kfactors.root");
TH1F* GJets_NLO = (TH1F*) NLOWeightFile->Get("GJets_1j_NLO/nominal_G");
TH1F* GJets_LO = (TH1F*) NLOWeightFile->Get("GJets_LO/inv_pt_G");
TH1F* WJets_NLO = (TH1F*) NLOWeightFile->Get("WJets_012j_NLO/nominal");
TH1F* WJets_LO = (TH1F*) NLOWeightFile->Get("WJets_LO/inv_pt");
TH1F* ZJets_NLO = (TH1F*) NLOWeightFile->Get("ZJets_01j_NLO/nominal");
TH1F* ZJets_LO = (TH1F*) NLOWeightFile->Get("ZJets_LO/inv_pt");
// ==============================================

double CalcdPhi( double phi1 , double phi2 ){

  double dPhi = phi1-phi2;
  if( dPhi < -TMath::Pi() ) 
    dPhi += 2*TMath::Pi() ;
  if( dPhi > TMath::Pi() )
    dPhi -= 2*TMath::Pi() ;
  return fabs(dPhi);

}


template<typename ntupleType>void ntupleBranchStatus(ntupleType* ntuple){
  ntuple->fChain->SetBranchStatus("*",0);
  ntuple->fChain->SetBranchStatus("Muons",1);
  ntuple->fChain->SetBranchStatus("Electrons",1);
  ntuple->fChain->SetBranchStatus("isoElectronTracksclean",1);
  ntuple->fChain->SetBranchStatus("isoMuonTracksclean",1);
  ntuple->fChain->SetBranchStatus("isoPionTracksclean",1);
  ntuple->fChain->SetBranchStatus("isoElectronTracks",1);
  ntuple->fChain->SetBranchStatus("isoMuonTracks",1);
  ntuple->fChain->SetBranchStatus("isoPionTracks",1);
  ntuple->fChain->SetBranchStatus("Photon*",1);
  ntuple->fChain->SetBranchStatus("DeltaPhi*",1);
  ntuple->fChain->SetBranchStatus("GenTaus_had*", 1);
  ntuple->fChain->SetBranchStatus("MHT",1);
  ntuple->fChain->SetBranchStatus("HT",1);
  ntuple->fChain->SetBranchStatus("NJets",1);
  ntuple->fChain->SetBranchStatus("BTags",1);
  ntuple->fChain->SetBranchStatus("MET",1);
  ntuple->fChain->SetBranchStatus("MHT",1);
  ntuple->fChain->SetBranchStatus("METPhi",1);

  ntuple->fChain->SetBranchStatus("HTclean",1);
  ntuple->fChain->SetBranchStatus("NJetsclean",1);
  ntuple->fChain->SetBranchStatus("BTagsclean",1);
  ntuple->fChain->SetBranchStatus("METclean",1);
  ntuple->fChain->SetBranchStatus("METPhiclean",1);

  ntuple->fChain->SetBranchStatus("JetsAK8*",1);
  ntuple->fChain->SetBranchStatus("GenJets*",1);
  ntuple->fChain->SetBranchStatus("Jets*",1);
  ntuple->fChain->SetBranchStatus("Weight",1);  
  ntuple->fChain->SetBranchStatus("puWeightNew",1);  
  ntuple->fChain->SetBranchStatus("TrueNumInteractions",1);  
  ntuple->fChain->SetBranchStatus("TriggerPass",1);  
  ntuple->fChain->SetBranchStatus("HBHENoiseFilter",1);
  ntuple->fChain->SetBranchStatus("HBHEIsoNoiseFilter",1);
  ntuple->fChain->SetBranchStatus("globalSuperTightHalo2016Filter",1);
  ntuple->fChain->SetBranchStatus("eeBadScFilter",1);
  ntuple->fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter",1);
  ntuple->fChain->SetBranchStatus("BadPFMuonFilter",1);
  ntuple->fChain->SetBranchStatus("BadChargedCandidateFilter",1);
  ntuple->fChain->SetBranchStatus("CaloMET",1);
  ntuple->fChain->SetBranchStatus("NVtx",1);
  ntuple->fChain->SetBranchStatus("NumInteractions",1);
  ntuple->fChain->SetBranchStatus("nAllVertices",1);
  ntuple->fChain->SetBranchStatus("JetID*",1);
  ntuple->fChain->SetBranchStatus("madHT",1);
  ntuple->fChain->SetBranchStatus("NJetsISR",1);
  ntuple->fChain->SetBranchStatus("madMinDeltaRStatus",1);
  ntuple->fChain->SetBranchStatus("madMinPhotonDeltaR",1);

  ntuple->fChain->SetBranchStatus("GenParticles*",1);
}

/***************************************************************/
/* - - - - - - - - - - - - gen-level cuts - - - - - - - - - -  */
/***************************************************************/
template<typename ntupleType> bool genWmatched(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;
    
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( abs(ntuple->GenParticles_PdgId->at(i)) == 24 && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<0.4)
            return true;
    }
    return false;
}

template<typename ntupleType> bool genTmatched(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return false;
    
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( abs(ntuple->GenParticles_PdgId->at(i)) == 6 && ntuple->JetsAK8->at(0).DeltaR(ntuple->GenParticles->at(i))<0.4)
            return true;
    }
    return false;
}

template<typename ntupleType> int getNumGenHiggses(ntupleType* ntuple){
    int numHiggses=0;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( ntuple->GenParticles_PdgId->at(i) == 25 && 
            ntuple->GenParticles_ParentId->at(i) == 1000023 && 
            ntuple->GenParticles_Status->at(i) == 22 )
            numHiggses++;
    }
    return numHiggses;
}

template<typename ntupleType> int getNumGenZs(ntupleType* ntuple){
    int numZs=0;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( ntuple->GenParticles_PdgId->at(i) == 23 && 
            ntuple->GenParticles_ParentId->at(i) == 1000023 && 
            ntuple->GenParticles_Status->at(i) == 22 )
            numZs++;    
    }
    return numZs;
}

template<typename ntupleType> bool genLevelHHcut(ntupleType* ntuple){
    int numHiggses=getNumGenHiggses(ntuple),numZs=getNumGenZs(ntuple);
    if(numHiggses==2 && numZs==0) return true;
    else return false;
}

template<typename ntupleType> bool genLevelZHcut(ntupleType* ntuple){
    int numHiggses=getNumGenHiggses(ntuple),numZs=getNumGenZs(ntuple);
    if(numHiggses==1 && numZs==1) return true;
    else return false;
}

template<typename ntupleType> bool genLevelZZcut(ntupleType* ntuple){
    int numHiggses=getNumGenHiggses(ntuple),numZs=getNumGenZs(ntuple);
    if(numHiggses==0 && numZs==2) return true;
    else return false;
}

/***************************************************************/
/* - - - - - - - - - - - - custom weights - - - - - - - - - -  */
/***************************************************************/
template<typename ntupleType> double GJetsNLOWeights(ntupleType* ntuple){
    if( ntuple->Photons->size() == 0 ) return 0.;
    double photon_pt = -999.;//ntuple->Photons->at(0).Pt();
    int photonIndex=-1;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 22 ){
            if( photonIndex < 0 )
                photonIndex = p;
            else if( ntuple->GenParticles->at(p).Pt() > ntuple->GenParticles->at(photonIndex).Pt() )
                photonIndex = p;
        }
    }               
    photon_pt = ntuple->GenParticles->at(photonIndex).Pt();
    
    if( photon_pt>150. ){
        double LO = GJets_LO->GetBinContent( GJets_LO->FindBin(photon_pt) );
        double NLO = GJets_NLO->GetBinContent( GJets_NLO->FindBin(photon_pt) );
        return (LO==0?0.:NLO/LO);
    }else
        return GJets_NLO->GetBinContent(1)/GJets_LO->GetBinContent(1);
}

template<typename ntupleType> double WJetsNLOWeights(ntupleType* ntuple){
    double Wpt=-999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 24 )
            Wpt = ntuple->GenParticles->at(p).Pt();
    }
    if( Wpt>150. ){
        double LO = WJets_LO->GetBinContent( WJets_LO->FindBin(Wpt) );
        double NLO = WJets_NLO->GetBinContent( WJets_NLO->FindBin(Wpt) );
        return (LO==0?0.:NLO/LO/1.21);
    }else
        return WJets_NLO->GetBinContent(1)/WJets_LO->GetBinContent(1)/1.21;
}

template<typename ntupleType> double ZJetsNLOWeights(ntupleType* ntuple){
    double Zpt=-999.;
    for( unsigned int p = 0 ; p < ntuple->GenParticles->size() ; p++ ){
        if( abs(ntuple->GenParticles_PdgId->at(p)) == 23 )
            Zpt = ntuple->GenParticles->at(p).Pt();
    }
    if( Zpt>150. ){
        double LO = ZJets_LO->GetBinContent( ZJets_LO->FindBin(Zpt) );
        double NLO = ZJets_NLO->GetBinContent( ZJets_NLO->FindBin(Zpt) );
        return (LO==0?0.:NLO/LO/1.23);
    }else
        return ZJets_NLO->GetBinContent(1)/ZJets_LO->GetBinContent(1)/1.23;
}

template<typename ntupleType> double singleMuonTrigWeights(ntupleType* ntuple){
    if( ntuple->Muons->size() == 0 ) return 0.;
    else if( ntuple->HT > 300. ){
        if( ntuple->HT < 500.){
            if( ntuple->Muons->at(0).Pt() > 25. ){
                if( ntuple->Muons->at(0).Pt() < 30. ){
                    return .787;
                }else if( ntuple->Muons->at(0).Pt() < 50. ){
                    return .843;
                }else{
                    return .908;
                }
            }else{
                return 0.;
            }
        }else if( ntuple->HT > 500. ){
            return .949;
        }else{
            return 0.;
        }
    }
}

template<typename ntupleType> double singleElectronTrigWeights(ntupleType* ntuple){
    if( ntuple->Electrons->size() == 0 ) return 0.;
    else if( ntuple->HT > 450. ){
        
        //cout << "ntuple->HT: " << ntuple->HT << endl;
        //cout << "ntuple->Electrons->at(0).Pt(): " << ntuple->Electrons->at(0).Pt() << endl;

        if( ntuple->Electrons->at(0).Pt() > 25. ){
            if( ntuple->Electrons->at(0).Pt() < 30. ){
                return 0.794;
            }else if( ntuple->Electrons->at(0).Pt() < 40. ){
                return 0.826;
            }else if( ntuple->Electrons->at(0).Pt() < 50. ){
                return 0.872;
            }else if( ntuple->Electrons->at(0).Pt() < 75. ){
                return 0.884;
            }else if( ntuple->Electrons->at(0).Pt() < 100. ){
                return 0.913;
            }else{
                return 0.947;
            }
        }else{
            return 0.;
        }
    }else if( ntuple->HT > 300. ){

        //cout << "ntuple->HT: " << ntuple->HT << endl;
        //cout << "ntuple->Electrons->at(0).Pt(): " << ntuple->Electrons->at(0).Pt() << endl;

        if( ntuple->Electrons->at(0).Pt() > 25. ){
            if( ntuple->Electrons->at(0).Pt() < 30. ){
                return 0.572;
            }else if( ntuple->Electrons->at(0).Pt() < 40. ){
                return 0.775;
            }else if( ntuple->Electrons->at(0).Pt() < 50. ){
                return 0.858;
            }else if( ntuple->Electrons->at(0).Pt() < 75. ){
                return 0.861;
            }else if( ntuple->Electrons->at(0).Pt() < 100. ){
                return 0.932;
            }else{
                return 1.;
            }  
        }else{
            return 0.;
        }
    }else{
        return 0.;
    }
}

template<typename ntupleType> double lowDphiTrigWeights(ntupleType* ntuple){
    if( ntuple->MET>100. ){
        if( ntuple->MET<200. ){
            return 0.500;
        }else if( ntuple->MET<300. ){
            return 0.712;
        }else if( ntuple->MET<400. ){
            return 0.806;
        }else if( ntuple->MET<500. ){
            return 0.874;
        }else if( ntuple->MET<700. ){
            return 0.866;
        }else{
            return 0.766;
        }
    }else
        return 0.;
}

template<typename ntupleType> double customPUweights(ntupleType* ntuple){
    int nVtx = ntuple->TrueNumInteractions;
    return puWeightHist->GetBinContent(puWeightHist->GetXaxis()->FindBin(min(ntuple->TrueNumInteractions,puWeightHist->GetBinLowEdge(puWeightHist->GetNbinsX()+1))));
}

enum ISRweightType {kNom,kUp,kDn};
template<typename ntupleType> double ISRweights(ntupleType* ntuple, ISRweightType wType = kNom ){

    double wanted_w_isr=1.;
    double wanted_sys_isr[2]={1.,1.};

    TString sample = ntuple->fChain->GetFile()->GetName();

    // these are taken from here:
    // https://github.com/manuelfs/babymaker/blob/3a57e1bace6c52832fe40e401cf37bc6b50923c3/bmaker/genfiles/src/change_weights.cxx#L156-L175
    // via Manuel Franco Sevilla
    if(sample.Contains("TTJets_HT-600to800")) {
        wanted_w_isr = 0.7838;
        wanted_sys_isr[0] = 0.8965;
        wanted_sys_isr[1] = 0.6604;
    }else if(sample.Contains("TTJets_HT-800to1200")) {
        wanted_w_isr = 0.7600;
        wanted_sys_isr[0] = 0.8851;
        wanted_sys_isr[1] = 0.6230;
    }else if(sample.Contains("TTJets_HT-1200to2500")) {
        wanted_w_isr = 0.7365;
        wanted_sys_isr[0] = 0.8739;
        wanted_sys_isr[1] = 0.5861;
    }else if(sample.Contains("TTJets_HT-2500toInf")) {
        wanted_w_isr = 0.7254;
        wanted_sys_isr[0] = 0.8686;
        wanted_sys_isr[1] = 0.5687;
    }else{ //  if(sample.Contains("TTJets_SingleLept") or sample.Contains("TTJets_DiLept") ){
        // these numbers should really only be applied to the inclusive sample
        wanted_w_isr = 1.071;
        wanted_sys_isr[0] = 1.071;
        wanted_sys_isr[1] = 1.071;
    }
    
    double D;
    if( wType == kNom ) D = wanted_w_isr;
    else D = wanted_sys_isr[wType-1];

    double w[6]={0.920,0.821,0.715,0.662,0.561,0.511};
    if( ntuple->NJetsISR == 0 )
        return D;
    else if( ntuple->NJetsISR >= 6 )
        return w[5]*D;
    else 
        return w[ntuple->NJetsISR]*D;
}
//////////////////////
//////////////////////
//////////////////////
// Lepton functions //
//////////////////////
//////////////////////
//////////////////////

template<typename ntupleType> double computeMuonMT(ntupleType* ntuple){ 
    if( ntuple->Muons->size() == 0 ) return -9999.;
    double lepPt = ntuple->Muons->at(0).Pt();
    double lepPhi = ntuple->Muons->at(0).Phi(); 
    double MET = ntuple->MET;
    double METPhi = ntuple->METPhi;
    return sqrt( 2*lepPt*MET * ( 1 - cos( METPhi-lepPhi ) ) );
}

template<typename ntupleType> double computeElectronMT(ntupleType* ntuple){ 
    if( ntuple->Electrons->size() == 0 ) return -9999.;
    double lepPt = ntuple->Electrons->at(0).Pt();
    double lepPhi = ntuple->Electrons->at(0).Phi(); 
    double MET = ntuple->MET;
    double METPhi = ntuple->METPhi;
    return sqrt( 2*lepPt*MET * ( 1 - cos( METPhi-lepPhi ) ) );
}



///////////////////////////
// RECO Muon definitions //
///////////////////////////
template<typename ntupleType> int numMuons(ntupleType* ntuple){
  return ntuple->Muons->size();
}

template<typename ntupleType> double muonLeadJetdR(ntupleType* ntuple){
    if( ntuple->Muons->size() == 1 ){
        return ntuple->JetsAK8->size()>=1?ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(0)):-99.;
    }else 
        return -99.;
}

template<typename ntupleType> double muonSubleadJetdR(ntupleType* ntuple){
    if( ntuple->Muons->size() == 1 ){
        return ntuple->JetsAK8->size()>=2?ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(1)):-99.;
    }else 
        return -99.;
}

template<typename ntupleType> double leadJetMuondR_mass(ntupleType* ntuple){
    if( ntuple->Muons->size() == 1 ){
        if( ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(0)) < ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(1)) )
            return ntuple->JetsAK8_softDropMass->at(1);
        else 
            return ntuple->JetsAK8_softDropMass->at(0);
    }else 
        return -99.;
}

template<typename ntupleType> double subleadJetMuondR_mass(ntupleType* ntuple){
    if( ntuple->Muons->size() == 1 ){
        if( ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(0)) < ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(1)) )
            return ntuple->JetsAK8_softDropMass->at(0);
        else 
            return ntuple->JetsAK8_softDropMass->at(1);
    }else 
        return -99.;
}

template<typename ntupleType> double leadJetMuondR_bbdisc(ntupleType* ntuple){
    if( ntuple->Muons->size() == 1 ){
        if( ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(0)) < ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(1)) )
            return ntuple->JetsAK8_doubleBDiscriminator->at(1);
        else 
            return ntuple->JetsAK8_doubleBDiscriminator->at(0);
    }else 
        return -99.;
}

template<typename ntupleType> double subleadJetMuondR_bbdisc(ntupleType* ntuple){
    if( ntuple->Muons->size() == 1 ){
        if( ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(0)) < ntuple->Muons->at(0).DeltaR(ntuple->JetsAK8->at(1)) )
            return ntuple->JetsAK8_doubleBDiscriminator->at(0);
        else 
            return ntuple->JetsAK8_doubleBDiscriminator->at(1);
    }else 
        return -99.;
}

template<typename ntupleType> double fillNumMuons(ntupleType* ntuple){
  return double(ntuple->Muons->size());
}


///////////////////////////////////////////////
// - - - - - - - RECO ELECTRONS - - - - - -  //
///////////////////////////////////////////////
template<typename ntupleType> double electronLeadJetdR(ntupleType* ntuple){
    if( ntuple->Electrons->size() == 1 ){
        return ntuple->Electrons->at(0).DeltaR(ntuple->JetsAK8->at(0));
    }else 
        return -99.;
}

template<typename ntupleType> double electronSubleadJetdR(ntupleType* ntuple){
    if( ntuple->Electrons->size() == 1 ){
        return ntuple->Electrons->at(0).DeltaR(ntuple->JetsAK8->at(1));
    }else 
        return -99.;
}


template<typename ntupleType> int numElectrons(ntupleType* ntuple){
  return ntuple->Electrons->size();
}

template<typename ntupleType> double fillLepPt(ntupleType* ntuple){
  if( ntuple->Electrons->size() > 0 && ntuple->Muons->size() == 0 )
      return ntuple->Electrons->at(0).Pt();
  else if( ntuple->Electrons->size() ==0 && ntuple->Muons->size() > 0 )
    return ntuple->Muons->at(0).Pt();
  else
    return -9999.;
}

template<typename ntupleType> double fillLepEta(ntupleType* ntuple){
  if( ntuple->Electrons->size() > 0 && ntuple->Muons->size() == 0 )
      return ntuple->Electrons->at(0).Eta();
  else if( ntuple->Electrons->size() ==0 && ntuple->Muons->size() > 0 )
    return ntuple->Muons->at(0).Eta();
  else
    return -9999.;
}

template<typename ntupleType> double fillLepActivity(ntupleType* ntuple){
  if( ntuple->Electrons->size() > 0 && ntuple->Muons->size() == 0 )
    return ntuple->Electrons_MT2Activity->at(0);
  else if( ntuple->Electrons->size() ==0 && ntuple->Muons->size() > 0 )
    return ntuple->Muons_MT2Activity->at(0);
  else
    return -9999.;
}

//////////////////////
// END LEPTON STUFF //
//////////////////////

////////////////////////////////////////////////////////////
// - - - - - - - - EVENT LEVEL VARIABLES - - - - - - - -  //
////////////////////////////////////////////////////////////

template<typename ntupleType> double fillJetPt1(ntupleType* ntuple){
    if( ntuple->Jets->size() >= 1) 
        return ntuple->Jets->at(0).Pt();
    else 
        return -999.;
}

template<typename ntupleType> double fillJetPt2(ntupleType* ntuple){
    if( ntuple->Jets->size() >= 2) 
        return ntuple->Jets->at(1).Pt();
    else 
        return -999.;
}

template<typename ntupleType> double fillJetPt3(ntupleType* ntuple){
    if( ntuple->Jets->size() >= 3) 
        return ntuple->Jets->at(2).Pt();
    else 
        return -999.;
}

template<typename ntupleType> double fillJetPt4(ntupleType* ntuple){
    if( ntuple->Jets->size() >= 4) 
        return ntuple->Jets->at(3).Pt();
    else 
        return -999.;
}

template<typename ntupleType> double fillNVtx(ntupleType* ntuple){
  return ntuple->NVtx;
}

template<typename ntupleType> double fillnAllVertices(ntupleType* ntuple){
  return ntuple->nAllVertices;
}

template<typename ntupleType> double fillNumInteractions(ntupleType* ntuple){
  return ntuple->NumInteractions;
}

template<typename ntupleType> double fillMadHT(ntupleType* ntuple){
  return ntuple->madHT;
}

template<typename ntupleType> double fillDeltaPhi1(ntupleType* ntuple){
  return ntuple->DeltaPhi1;
}

template<typename ntupleType> double fillDeltaPhi2(ntupleType* ntuple){
  return ntuple->DeltaPhi2;
}

template<typename ntupleType> double fillDeltaPhi3(ntupleType* ntuple){
  return ntuple->DeltaPhi3;
}

template<typename ntupleType> double fillDeltaPhi4(ntupleType* ntuple){
  return ntuple->DeltaPhi4;
}

template<typename ntupleType> double fillDeltaPhi1clean(ntupleType* ntuple){
  return ntuple->DeltaPhi1clean;
}

template<typename ntupleType> double fillDeltaPhi2clean(ntupleType* ntuple){
  return ntuple->DeltaPhi2clean;
}

template<typename ntupleType> double fillDeltaPhi3clean(ntupleType* ntuple){
  return ntuple->DeltaPhi3clean;
}

template<typename ntupleType> double fillDeltaPhi4clean(ntupleType* ntuple){
  return ntuple->DeltaPhi4clean;
}

template<typename ntupleType> double fillHT(ntupleType* ntuple){
  return ntuple->HT;
}

template<typename ntupleType> double fillHTclean(ntupleType* ntuple){
  return ntuple->HTclean;
}

template<typename ntupleType> double fillMHT(ntupleType* ntuple){
  return ntuple->MHT;
}

template<typename ntupleType> double fillMET(ntupleType* ntuple){
  return ntuple->MET;
}

template<typename ntupleType> double fillMETclean(ntupleType* ntuple){
  return ntuple->METclean;
}

template<typename ntupleType> double fillOne(ntupleType* ntuple){
  return 1.;
}

template<typename ntupleType> double fillNJets(ntupleType* ntuple){
  return ntuple->NJets;
}

template<typename ntupleType> double fillNJetsclean(ntupleType* ntuple){
  return ntuple->NJetsclean;
}

template<typename ntupleType> double fillBTags(ntupleType* ntuple){
  return ntuple->BTags;
}

////////////////////////////////
// HIGHEST PT JET PROPERTIES  //
////////////////////////////////
template<typename ntupleType> double fillLeadingJetMinDRB(ntupleType* ntuple){
    if( ntuple->JetsAK8->size() == 0 ) return -999.;
    else{
        double minDRB = 999.;
        double DRB = 999.;
        for( int i = 0 ; i < ntuple->Jets->size() ; i++ ){
            DRB = 999.;            
            if( abs(ntuple->Jets_partonFlavor->at(i)) == 5 ){
                DRB = ntuple->JetsAK8->at(0).DeltaR(ntuple->Jets->at(i));
            }
            if( DRB < minDRB ) 
                minDRB = DRB;
        }
        return minDRB;
    }
}

template<typename ntupleType> double fillLeadingJetMass(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return -99999.;
  return ntuple->JetsAK8_softDropMass->at(0);
}

template<typename ntupleType> double fillLeadingJetMass_photon(ntupleType* ntuple){
    if(ntuple->JetsAK8Clean_prunedMass->size()==0) return -99999.;
    return ntuple->JetsAK8Clean_prunedMass->at(0);
}

template<typename ntupleType> double fillSubLeadingJetMass_photon(ntupleType* ntuple){
    if(ntuple->JetsAK8Clean_prunedMass->size()<2) return -99999.;
    return ntuple->JetsAK8Clean_prunedMass->at(1);
}

template<typename ntupleType> double fillLeadingJetFlavor(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return -99999.;
  if( ntuple->JetsAK8_NumBhadrons->at(0)==2 ) 
    return 21.;
  else if( ntuple->JetsAK8_NumBhadrons->at(0)==1 )
    return 5.;
  else return 1.;
}


template<typename ntupleType> double fillLeadingJetFlavor_photon(ntupleType* ntuple){
  if(ntuple->JetsAK8Clean->size()==0) return -99999.;
  if( ntuple->JetsAK8Clean_NumBhadrons->at(0)==2 ) 
    return 21.;
  else if( ntuple->JetsAK8Clean_NumBhadrons->at(0)==1 )
    return 5.;
  else return 1.;
}

template<typename ntupleType> double fillLeadingNbHadrons(ntupleType* ntuple){
    return ntuple->JetsAK8->size()>=1?ntuple->JetsAK8_NumBhadrons->at(0):-999.;
}

template<typename ntupleType> double fillLeadingJetPt(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8->at(0).Pt();
}
template<typename ntupleType> double fillLeadingJetPt_photon(ntupleType* ntuple){
  if(ntuple->JetsAK8Clean->size()==0) return-99999.;
  return ntuple->JetsAK8Clean->at(0).Pt();
}

template<typename ntupleType> double fillLeadingBBtag(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8_doubleBDiscriminator->at(0);
}

template<typename ntupleType> double fillLeadingBBtag_photon(ntupleType* ntuple){
    return ntuple->JetsAK8->size()>=1?ntuple->JetsAK8Clean_doubleBDiscriminator->at(0):-999;
}

template<typename ntupleType> double fillLeadingTau21(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  return ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0);
}

//////////////////////////////////////////
// SECOND HIGHEST PT AK8 JET PROPERTIES //
//////////////////////////////////////////
template<typename ntupleType> double fillSubLeadingJetMass(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()<=1) return-99999.;
  return ntuple->JetsAK8_softDropMass->at(1);
}

template<typename ntupleType> double fillSubLeadingJetFlavor(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()<=1) return-99999.;
  if( ntuple->JetsAK8_NumBhadrons->at(1)==2 ) 
    return 21.;
  else if (ntuple->JetsAK8_NumBhadrons->at(1)==1 )
    return 5.;
  else return 1.;
}

template<typename ntupleType> double fillSubLeadingJetFlavor_photon(ntupleType* ntuple){
  if(ntuple->JetsAK8Clean->size()<=1) return-99999.;
  if( ntuple->JetsAK8Clean_NumBhadrons->at(1)==2 ) 
    return 21.;
  else if (ntuple->JetsAK8Clean_NumBhadrons->at(1)==1 )
    return 5.;
  else return 1.;
}

template<typename ntupleType> double fillSubLeadingNbHadrons(ntupleType* ntuple){
    return ntuple->JetsAK8->size()>=2?ntuple->JetsAK8_NumBhadrons->at(1):-999.;
}

template<typename ntupleType> double fillSubLeadingJetPt(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()<=1) return -99999.;
  return ntuple->JetsAK8->at(1).Pt();
}

template<typename ntupleType> double fillSubLeadingJetPt_photon(ntupleType* ntuple){
  if(ntuple->JetsAK8Clean->size()<=1) return -99999.;
  return ntuple->JetsAK8Clean->at(1).Pt();
}

template<typename ntupleType> double fillSubLeadingBBtag(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()<=1) return-99999.;
  return ntuple->JetsAK8_doubleBDiscriminator->at(1);
}

template<typename ntupleType> double fillSubLeadingBBtag_photon(ntupleType* ntuple){
    return ntuple->JetsAK8->size()>=2?ntuple->JetsAK8Clean_doubleBDiscriminator->at(1):-999.;
}

template<typename ntupleType> double fillSubLeadingTau21(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()<=1) return-99999.;
  return ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1);
}

////////////////////////////////////////
// HIGHEST BBtag AK8 JET PROPERTIES  //
//////////////////////////////////////
template<typename ntupleType> double fillLeadingBBtagJetMass(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) < ntuple->JetsAK8_doubleBDiscriminator->at(1) );
    return ntuple->JetsAK8_softDropMass->at(index);
  }
}

template<typename ntupleType> double fillLeadingBBtagJetFlavor(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) < ntuple->JetsAK8_doubleBDiscriminator->at(1) );
    if( ntuple->JetsAK8_NumBhadrons->at(index)==2 ) 
      return 21.;
    else if( ntuple->JetsAK8_NumBhadrons->at(index)==1 )
      return 5.;
    else return 1.;
  }
}

template<typename ntupleType> double fillLeadingBBtagJetPt(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) < ntuple->JetsAK8_doubleBDiscriminator->at(1) );
    return ntuple->JetsAK8->at(index).Pt();
  }
}
template<typename ntupleType> double fillLeadingBBtagJetBBtag(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
      index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) < ntuple->JetsAK8_doubleBDiscriminator->at(1) );
      return ntuple->JetsAK8_doubleBDiscriminator->at(index);
  }
}

template<typename ntupleType> double fillLeadingBBtagJetTau21(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
      index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) < ntuple->JetsAK8_doubleBDiscriminator->at(1) );
      return ntuple->JetsAK8_NsubjettinessTau2->at(index)/ntuple->JetsAK8_NsubjettinessTau1->at(index);
  }
}

/////////////////////////////////////////////
// SECOND HIGHEST BBtag AK8 JET PROPERTIES //
/////////////////////////////////////////////
template<typename ntupleType> double fillSubLeadingBBtagJetMass(ntupleType* ntuple){
  int index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) > ntuple->JetsAK8_doubleBDiscriminator->at(1) );
  return ntuple->JetsAK8_softDropMass->at(index);
}

template<typename ntupleType> double fillSubLeadingBBtagJetFlavor(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) > ntuple->JetsAK8_doubleBDiscriminator->at(1) );
    if( ntuple->JetsAK8_NumBhadrons->at(index)==2 ) 
      return 21.;
    else if (ntuple->JetsAK8_NumBhadrons->at(index)==1 )
      return 5.;
    else return 1.;
  }
}

template<typename ntupleType> double fillSubLeadingBBtagJetPt(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) > ntuple->JetsAK8_doubleBDiscriminator->at(1) );
    return ntuple->JetsAK8->at(index).Pt();
  }
}

template<typename ntupleType> double fillSubLeadingBBtagJetBBtag(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) > ntuple->JetsAK8_doubleBDiscriminator->at(1) );
    return ntuple->JetsAK8_doubleBDiscriminator->at(index);
  }
}

template<typename ntupleType> double fillSubLeadingBBtagJetTau21(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_doubleBDiscriminator->at(0) > ntuple->JetsAK8_doubleBDiscriminator->at(1) );
    return ntuple->JetsAK8_NsubjettinessTau2->at(index)/ntuple->JetsAK8_NsubjettinessTau1->at(index);
  }
}


////////////////////////////////////////
// HIGHEST BBtag AK8 JET PROPERTIES  //
//////////////////////////////////////
template<typename ntupleType> double fillLeadingMassJetMass(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_softDropMass->at(0) < ntuple->JetsAK8_softDropMass->at(1) );
    return ntuple->JetsAK8_softDropMass->at(index);
  }
}

template<typename ntupleType> double fillLeadingMassJetFlavor(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_softDropMass->at(0) < ntuple->JetsAK8_softDropMass->at(1) );
    if( ntuple->JetsAK8_NumBhadrons->at(index)==2 ) 
      return 21.;
    else if( ntuple->JetsAK8_NumBhadrons->at(index)==1 )
      return 5.;
    else return 1.;
  }
}

template<typename ntupleType> double fillLeadingMassJetPt(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_softDropMass->at(0) < ntuple->JetsAK8_softDropMass->at(1) );
    return ntuple->JetsAK8->at(index).Pt();
  }
}
template<typename ntupleType> double fillLeadingMassJetBBtag(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
      index = int( ntuple->JetsAK8_softDropMass->at(0) < ntuple->JetsAK8_softDropMass->at(1) );
      return ntuple->JetsAK8_doubleBDiscriminator->at(index);
  }
}

template<typename ntupleType> double fillLeadingMassJetTau21(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
      index = int( ntuple->JetsAK8_softDropMass->at(0) < ntuple->JetsAK8_softDropMass->at(1) );
      return ntuple->JetsAK8_NsubjettinessTau2->at(index)/ntuple->JetsAK8_NsubjettinessTau1->at(index);
  }
}

/////////////////////////////////////////////
// SECOND HIGHEST Mass AK8 JET PROPERTIES //
/////////////////////////////////////////////
template<typename ntupleType> double fillSubLeadingMassJetMass(ntupleType* ntuple){
  int index = int( ntuple->JetsAK8_softDropMass->at(0) > ntuple->JetsAK8_softDropMass->at(1) );
  return ntuple->JetsAK8_softDropMass->at(index);
}

template<typename ntupleType> double fillSubLeadingMassJetFlavor(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_softDropMass->at(0) > ntuple->JetsAK8_softDropMass->at(1) );
    if( ntuple->JetsAK8_NumBhadrons->at(index)==2 ) 
      return 21.;
    else if (ntuple->JetsAK8_NumBhadrons->at(index)==1 )
      return 5.;
    else return 1.;
  }
}

template<typename ntupleType> double fillSubLeadingMassJetPt(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_softDropMass->at(0) > ntuple->JetsAK8_softDropMass->at(1) );
    return ntuple->JetsAK8->at(index).Pt();
  }
}

template<typename ntupleType> double fillSubLeadingMassJetBBtag(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_softDropMass->at(0) > ntuple->JetsAK8_softDropMass->at(1) );
    return ntuple->JetsAK8_doubleBDiscriminator->at(index);
  }
}

template<typename ntupleType> double fillSubLeadingMassJetTau21(ntupleType* ntuple){
  if(ntuple->JetsAK8->size()==0) return-99999.;
  int index;
  if(ntuple->JetsAK8->size()==1) index = 0;
  else{
    index = int( ntuple->JetsAK8_softDropMass->at(0) > ntuple->JetsAK8_softDropMass->at(1) );
    return ntuple->JetsAK8_NsubjettinessTau2->at(index)/ntuple->JetsAK8_NsubjettinessTau1->at(index);
  }
}

/////////////////////////////////////////////
// SECOND HIGHEST Mass AK8 JET PROPERTIES //
/////////////////////////////////////////////

template<typename ntupleType> double fillClosestJetMass(ntupleType* ntuple){
    if(ntuple->JetsAK8_softDropMass->size() == 0)
        return -999.;
    else if( ntuple->JetsAK8_softDropMass->size() == 1 )
        return ntuple->JetsAK8_softDropMass->at(0);
    else{       
        double J1diff,J2diff;
        J1diff = ntuple->JetsAK8_softDropMass->at(0)-110.;
        J2diff = ntuple->JetsAK8_softDropMass->at(1)-110.;
        //cout << "J1: " << ntuple->JetsAK8_softDropMass->at(0) << " J2: " << ntuple->JetsAK8_softDropMass->at(1) << endl;
        return fabs(J1diff)>fabs(J2diff) ?  ntuple->JetsAK8_softDropMass->at(1) :  ntuple->JetsAK8_softDropMass->at(0) ;       
    }
}

template<typename ntupleType> double fillFarthestJetMass(ntupleType* ntuple){
    if(ntuple->JetsAK8_softDropMass->size() == 0)
        return -999.;
    else if( ntuple->JetsAK8_softDropMass->size() == 1 )
        return ntuple->JetsAK8_softDropMass->at(0);
    else{       
        double J1diff,J2diff;
        J1diff = ntuple->JetsAK8_softDropMass->at(0)-110.;
        J2diff = ntuple->JetsAK8_softDropMass->at(1)-110.;
        //cout << "J1: " << ntuple->JetsAK8_softDropMass->at(0) << " J2: " << ntuple->JetsAK8_softDropMass->at(1) << endl;
        return fabs(J1diff)<fabs(J2diff) ?  ntuple->JetsAK8_softDropMass->at(1) :  ntuple->JetsAK8_softDropMass->at(0) ;       
    }
}

template<typename ntupleType> bool ptBinCut(double pt , int ithBin){
  if( ithBin > 5 ) return false;
  double ptCut[6] = {300.,400.,500.,700.,1000.,999999.};
  return pt>ptCut[ithBin] && pt<ptCut[ithBin+1];
}
 
template<typename ntupleType> bool FiltersCut(ntupleType* ntuple){
    return ntuple->HBHENoiseFilter==1 && 
        ntuple->HBHEIsoNoiseFilter==1 && 
        ntuple->eeBadScFilter==1 && 
        ntuple->EcalDeadCellTriggerPrimitiveFilter == 1 && 
        ntuple->NVtx>0 && 
        ntuple->MET/ntuple->CaloMET < 5. &&
        ntuple->BadPFMuonFilter == 1 &&
        ntuple->BadChargedCandidateFilter == 1  && ntuple->globalSuperTightHalo2016Filter==1;
}

template<typename ntupleType> bool AK8MultCut(ntupleType* ntuple){
  return ntuple->JetsAK8->size()>1 ; 
}

template<typename ntupleType> bool DeltaPhi1Cut(ntupleType* ntuple){
  return ntuple->DeltaPhi1>0.5;
}

template<typename ntupleType> bool DeltaPhi2Cut(ntupleType* ntuple){
  return ntuple->DeltaPhi2>0.5;
}

template<typename ntupleType> bool DeltaPhi3Cut(ntupleType* ntuple){
  return ntuple->DeltaPhi3>0.3;
}

template<typename ntupleType> bool DeltaPhi4Cut(ntupleType* ntuple){
  return ntuple->DeltaPhi4>0.3;
}

template<typename ntupleType> bool DeltaPhiCuts(ntupleType* ntuple){
    return ( DeltaPhi1Cut(ntuple) &&
             DeltaPhi2Cut(ntuple) &&
             DeltaPhi3Cut(ntuple) &&
             DeltaPhi4Cut(ntuple) ) ;
}             

template<typename ntupleType> bool lowDPhiCuts(ntupleType* ntuple){
    return !DeltaPhiCuts(ntuple);
}

template<typename ntupleType> bool METHTlooseCut(ntupleType* ntuple){
  return ( ntuple->MET > 100. && ntuple->HT > 300. );
}

template<typename ntupleType> bool METHTCut(ntupleType* ntuple){
  return ( ntuple->MET > 300. && ntuple->HT > 600. );
}

template<typename ntupleType> bool AK8JetPtCut(ntupleType* ntuple){
  return ( ntuple->JetsAK8->size() >= 2 &&
           ntuple->JetsAK8->at(0).Pt() > 200. &&
	   ntuple->JetsAK8->at(1).Pt() > 200. );
}

template<typename ntupleType> bool AK8JetLooseMassCut(ntupleType* ntuple){
  return ( ntuple->JetsAK8_softDropMass->at(0) > baselineMassLow &&
	   ntuple->JetsAK8_softDropMass->at(0) < baselineMassHigh &&
           ntuple->JetsAK8_softDropMass->at(1) > baselineMassLow &&
	   ntuple->JetsAK8_softDropMass->at(1) < baselineMassHigh );	   
}


template<typename ntupleType> bool baselineCut(ntupleType* ntuple){
 
  return ( ntuple->MET > 200.             &&
           ntuple->HT > 200.                         &&
           ntuple->JetsAK8->size() >1 &&
	   ntuple->JetsAK8->at(0).Pt() > 200. && 
	   ntuple->JetsAK8_softDropMass->at(0) > baselineMassLow &&
	   ntuple->JetsAK8_softDropMass->at(0) < baselineMassHigh &&
           //ntuple->JetsAK8->at(1).Pt() > 200. &&
           ntuple->JetsAK8_softDropMass->at(1) >baselineMassLow && 
           ntuple->JetsAK8_softDropMass->at(1) < baselineMassHigh
	    &&
	   dRtoClosestB(ntuple)>0.8	
	   //dRtoClosestB(ntuple)>2.0
	   &&
           DeltaPhiCuts(ntuple) && 
           ntuple->Muons->size()+ntuple->Electrons->size()==0 
           && ntuple->isoElectronTracks+ntuple->isoMuonTracks +ntuple->isoPionTracks==0 &&
           FiltersCut(ntuple) &&
           ntuple->JetID == 1);
}

template<typename ntupleType> float dRtoClosestB(ntupleType* ntuple){
//float leadjeteta= ntuple->JetsAK8->at(0).Eta();
//float leadjetphi= ntuple->JetsAK8->at(0).Phi();
float dRMin=999999.;
TString sample = ntuple->fChain->GetFile()->GetName();
double BTagDiscrimCut=0.4941;
if(sample.Contains("data2018"))BTagDiscrimCut=0.4184;
if(sample.Contains("data") && !sample.Contains("2017") && !sample.Contains("2018"))BTagDiscrimCut=0.6324;
	for(unsigned int j=0; j<ntuple->Jets->size(); ++j){
		//if(ntuple->Jets_bDiscriminatorCSV->at(j)<  0.8484  )continue;
		if(ntuple->Jets_bJetTagDeepCSVBvsAll->at(j)<  BTagDiscrimCut  )continue;
		//float deta=ntuple->Jets->at(j).Eta()-leadjeteta;
		//float dphi=ntuple->Jets->at(j).Phi()-leadjetphi;
		//float dR=sqrt((deta*deta)+(dphi*dphi));
		//if(dR<dRMin)dRMin=dR;		
		if(ntuple->JetsAK8->size()==1)continue;
		float subleadjeteta= ntuple->JetsAK8->at(1).Eta();
		float subleadjetphi= ntuple->JetsAK8->at(1).Phi();
	 	float deta=ntuple->Jets->at(j).Eta()-subleadjeteta;
                float dphi=ntuple->Jets->at(j).Phi()-subleadjetphi;
                float dR=sqrt((deta*deta)+(dphi*dphi));
		if(dR<dRMin)dRMin=dR;		
	}
//std::cout<<"dR to Closest B "<<dRMin<<std::endl;
return dRMin;
}
template<typename ntupleType> bool singleMuCut(ntupleType* ntuple){
    if( ntuple->Muons->size() != 1 || ntuple->Electrons->size() != 0 ) return false;
    double MT = computeMuonMT(ntuple);
    return ntuple->Muons->at(0).Pt()>25. && MT < 100.;

}

template<typename ntupleType> bool singleMuBaselineCut(ntupleType* ntuple){
  return ( ntuple->MET > 100.             &&
           ntuple->HT > 300.                         &&
           ntuple->JetsAK8->size() >1 &&
	   ntuple->JetsAK8->at(0).Pt() > 300. && 
	   ntuple->JetsAK8_softDropMass->at(0) > baselineMassLow &&
	   ntuple->JetsAK8_softDropMass->at(0) < baselineMassHigh &&
	   //if(ntuple->JetsAK8->size() > 1){
           ntuple->JetsAK8->at(1).Pt() > 200. &&
           ntuple->JetsAK8_softDropMass->at(1) >baselineMassLow && 
           ntuple->JetsAK8_softDropMass->at(1) < baselineMassHigh
	   && dRtoClosestB(ntuple)>0.8
	   &&
           DeltaPhiCuts(ntuple) && 
           FiltersCut(ntuple) &&
           ntuple->JetID == 1 && singleMuCut(ntuple));

    
}

template<typename ntupleType> bool singleEleCut(ntupleType* ntuple){
    if( ntuple->Muons->size() != 0 || ntuple->Electrons->size() != 1 ) return false;
    double MT = computeElectronMT(ntuple);
    return ( ntuple->Electrons->at(0).Pt()>25. && MT < 100. 
		) ;
}
template<typename ntupleType> bool singleEleBaselineCut(ntupleType* ntuple){

  return ( ntuple->MET > 100.             &&
           ntuple->HT > 500.                         &&
           ntuple->JetsAK8->size() >1 &&
	   ntuple->JetsAK8->at(0).Pt() > 300. && 
	   ntuple->JetsAK8_softDropMass->at(0) > baselineMassLow &&
	   ntuple->JetsAK8_softDropMass->at(0) < baselineMassHigh &&
	   //if(ntuple->JetsAK8->size() > 1){
           ntuple->JetsAK8->at(1).Pt() > 200. &&
           ntuple->JetsAK8_softDropMass->at(1) >baselineMassLow && 
           ntuple->JetsAK8_softDropMass->at(1) < baselineMassHigh
	   && dRtoClosestB(ntuple)>0.8	
	   &&
           DeltaPhiCuts(ntuple) && 
           FiltersCut(ntuple) &&
           ntuple->JetID == 1 && singleEleCut(ntuple));
}

template<typename ntupleType> bool lowDphiBaselineCut(ntupleType* ntuple){

    return ( ntuple->MET > 300.             &&
             ntuple->HT > 600.                         &&
             ntuple->JetsAK8->size() >= 2 &&
             ntuple->JetsAK8->at(0).Pt() > 200. && 
             ntuple->JetsAK8_softDropMass->at(0) > baselineMassLow && 
             ntuple->JetsAK8_softDropMass->at(0) < baselineMassHigh && 
             ntuple->JetsAK8->at(1).Pt() > 200. &&
             ntuple->JetsAK8_softDropMass->at(1) > baselineMassLow && 
             ntuple->JetsAK8_softDropMass->at(1) < baselineMassHigh&&
             ! DeltaPhiCuts( ntuple ) && 
             FiltersCut(ntuple) &&
             ntuple->JetID == 1);
}

template<typename ntupleType> bool photonBaselineCut(ntupleType* ntuple){
    return ( ntuple->Photons->size()==1 &&
             ntuple->Photons->at(0).Pt() > 100. && 
             ntuple->Photons_fullID->size() == 1 && 
             ntuple->Photons_fullID->at(0) == 1 &&
             ntuple->MET > 100.             &&
             ntuple->HT > 400.                         &&
             ntuple->JetsAK8->size()>=2 && 
             ntuple->JetsAK8->at(0).Pt() > 200  && 
             ntuple->JetsAK8_softDropMass->at(0) > baselineMassLow && 
             ntuple->JetsAK8_softDropMass->at(0) < baselineMassHigh && 
             ntuple->JetsAK8->at(1).Pt() > 200. &&
             ntuple->JetsAK8_softDropMass->at(1) > baselineMassLow && 
             ntuple->JetsAK8_softDropMass->at(1) < baselineMassHigh&&
             ntuple->DeltaPhi1>0.5 && 
             ntuple->DeltaPhi2>0.5 &&
             ntuple->DeltaPhi3>0.3 && 
             ntuple->DeltaPhi4>0.3 &&
             ntuple->isoElectronTracks==0 &&
             ntuple->isoMuonTracks == 0 && 
             ntuple->isoPionTracks == 0 &&
             ntuple->Electrons->size() == 0 &&
             ntuple->Muons->size() == 0 && 
             FiltersCut(ntuple) &&
             ntuple->JetID == 1);
}

template<typename ntupleType> bool photonBaselineCut_loose(ntupleType* ntuple){
    return ( ntuple->Photons->size()==1 &&
             ntuple->Photons->at(0).Pt() > 100. && 
             ntuple->Photons_fullID->size() == 1 && 
             ntuple->Photons_fullID->at(0) == 1 &&
             ntuple->METclean > 100.             &&
             ntuple->HTclean > 400.                         &&
             ntuple->JetsAK8Clean->size()>=2 && 
             ntuple->DeltaPhi1clean>0.5 && 
             ntuple->DeltaPhi2clean>0.5 &&
             ntuple->DeltaPhi3clean>0.3 && 
             ntuple->DeltaPhi4clean>0.3 &&
             ntuple->isoElectronTracksclean==0 &&
             ntuple->isoMuonTracksclean == 0 && 
             ntuple->isoPionTracksclean == 0 &&
             ntuple->Electrons->size() == 0 &&
             ntuple->Muons->size() == 0 && 
             FiltersCut(ntuple) &&
             ntuple->JetIDclean == 1);
}

template<typename ntupleType> bool singleTagLooseCut(ntupleType* ntuple ){ 
    return ( ( ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0) > tau21Cut ) 
             && ( ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1) < tau21Cut ) ) ||
        ( ( ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0) < tau21Cut ) 
          && ( ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1) > tau21Cut ) );
}

template<typename ntupleType> bool antiTaggingLooseCut(ntupleType* ntuple ){
    return ( ( ( ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0) > tau21Cut
               ) &&
               ( ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1) > tau21Cut 
               ) ) ) ;
}

template<typename ntupleType> bool doubleTaggingLooseCut(ntupleType* ntuple ){
    return ( ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0) < tau21Cut && 
             ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1) < tau21Cut );
}

template<typename ntupleType> bool doubleMassCut(ntupleType* ntuple ){
    return ( ntuple->JetsAK8_softDropMass->at(0) > ZmassWindowLow &&
             ntuple->JetsAK8_softDropMass->at(0) < ZmassWindowHigh &&
             ntuple->JetsAK8_softDropMass->at(1) > ZmassWindowLow &&
             ntuple->JetsAK8_softDropMass->at(1) < ZmassWindowHigh 
             );
}

template<typename ntupleType> bool singleTagCut(ntupleType* ntuple ){
  return ( (ntuple->JetsAK8_softDropMass->at(0) > ZmassWindowLow && 
            ntuple->JetsAK8_softDropMass->at(0) < ZmassWindowHigh && 
            ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0) > tau21Cut ) ||
           (ntuple->JetsAK8_softDropMass->at(1) > ZmassWindowLow && 
            ntuple->JetsAK8_softDropMass->at(1) < ZmassWindowHigh && 
            ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1) > tau21Cut ) );
}

template<typename ntupleType> bool doubleTagCut(ntupleType* ntuple ){
  return ( ntuple->JetsAK8_softDropMass->at(0) > ZmassWindowLow && 
           ntuple->JetsAK8_softDropMass->at(0) < ZmassWindowHigh && 
           ntuple->JetsAK8_NsubjettinessTau2->at(0)/ntuple->JetsAK8_NsubjettinessTau1->at(0) < tau21Cut && 
           ntuple->JetsAK8_softDropMass->at(1) > ZmassWindowLow && 
           ntuple->JetsAK8_softDropMass->at(1) < ZmassWindowHigh && 
           ntuple->JetsAK8_NsubjettinessTau2->at(1)/ntuple->JetsAK8_NsubjettinessTau1->at(1) < tau21Cut );
}

template<typename ntupleType> bool tagSR(ntupleType* ntuple, int i){
    if( ntuple->JetsAK8_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8_softDropMass->size() <= i ) return false;
    return ( ntuple->JetsAK8_NsubjettinessTau2->at(i)/ntuple->JetsAK8_NsubjettinessTau1->at(i) < tau21Cut &&
             ntuple->JetsAK8_softDropMass->at(i) > ZmassWindowLow && 
             ntuple->JetsAK8_softDropMass->at(i) < ZmassWindowHigh );
}

template<typename ntupleType> bool tagSB(ntupleType* ntuple, int i ){
    if( ntuple->JetsAK8_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8_softDropMass->size() <= i ) return false;
    return ( ntuple->JetsAK8_NsubjettinessTau2->at(i)/ntuple->JetsAK8_NsubjettinessTau1->at(i) < tau21Cut &&
             (
              ( ntuple->JetsAK8_softDropMass->at(i) < ZmassWindowLow &&
                ntuple->JetsAK8_softDropMass->at(i) > baselineMassLow ) ||
              ( ntuple->JetsAK8_softDropMass->at(i) > ZmassWindowHigh &&
                ntuple->JetsAK8_softDropMass->at(i) < baselineMassHigh ) 
              ) 
             );
}

template<typename ntupleType> bool antitagSR(ntupleType* ntuple, int i){
        if( ntuple->JetsAK8_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8_softDropMass->size() <= i ) return false;
        return ( ntuple->JetsAK8_NsubjettinessTau2->at(i)/ntuple->JetsAK8_NsubjettinessTau1->at(i) > tau21Cut && 
             ( ntuple->JetsAK8_softDropMass->at(i) > ZmassWindowLow &&
               ntuple->JetsAK8_softDropMass->at(i) < ZmassWindowHigh ) );
}
        
template<typename ntupleType> bool antitagSB(ntupleType* ntuple, int i){
    if( ntuple->JetsAK8_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8_softDropMass->size() <= i ) return false;
    return ( ntuple->JetsAK8_NsubjettinessTau2->at(i)/ntuple->JetsAK8_NsubjettinessTau1->at(i) > tau21Cut && 
             (
              ( ntuple->JetsAK8_softDropMass->at(i) < ZmassWindowLow &&
                ntuple->JetsAK8_softDropMass->at(i) > baselineMassLow ) ||
              ( ntuple->JetsAK8_softDropMass->at(i) > ZmassWindowHigh &&
                ntuple->JetsAK8_softDropMass->at(i) < baselineMassHigh ) 
              )
             );
}

template<typename ntupleType> bool antitagSRCut(ntupleType* ntuple){
    return ( antitagSR(ntuple,0)&&antitagSR(ntuple,1) );
}

template<typename ntupleType> bool antitagSBCut(ntupleType* ntuple){
    return ( ( antitagSB(ntuple,0)&&antitagSB(ntuple,1) ) ||
             ( antitagSB(ntuple,0)&&antitagSR(ntuple,1) ) ||
             ( antitagSR(ntuple,0)&&antitagSB(ntuple,1) ) );
}

template<typename ntupleType> bool tagSRCut(ntupleType* ntuple){
    return ( ( tagSR(ntuple,0)&&antitagSR(ntuple,1) ) || 
             ( antitagSR(ntuple,0)&&tagSR(ntuple,1) ) ) ;
}

template<typename ntupleType> bool tagSBCut(ntupleType* ntuple){
    return ( ( tagSB(ntuple,0)&&antitagSB(ntuple,1) ) ||
             ( tagSR(ntuple,0)&&antitagSB(ntuple,1) ) ||
             ( tagSB(ntuple,0)&&antitagSR(ntuple,1) ) ||
             ( antitagSB(ntuple,0)&&tagSB(ntuple,1) ) ||
             ( antitagSR(ntuple,0)&&tagSB(ntuple,1) ) ||
             ( antitagSB(ntuple,0)&&tagSR(ntuple,1) ) );

}

template<typename ntupleType> bool doubletagSRCut(ntupleType* ntuple){
    return ( tagSR(ntuple,0)&&tagSR(ntuple,1) );
}

template<typename ntupleType> bool doubletagSBCut(ntupleType* ntuple){
    return ( ( tagSB(ntuple,0)&&tagSB(ntuple,1) ) ||
             ( tagSB(ntuple,0)&&tagSR(ntuple,1) ) ||
             ( tagSR(ntuple,0)&&tagSB(ntuple,1) ) );
}

////////////////////////////////////////////////////////////////////////
// - - - - - - - - - - photon specializations - - - - - - - - - - - - //
////////////////////////////////////////////////////////////////////////
template<typename ntupleType> double fillPhotonPt(ntupleType* ntuple ){ 
    if( ntuple->Photons->size() == 0 )
        return -999.;
    else
        return ntuple->Photons->at(0).Pt();
}

template<typename ntupleType> bool singleTagLooseCut_photon(ntupleType* ntuple ){ 
    return ( ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(0)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(0) > tau21Cut )
             && ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(1)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(1) < tau21Cut ) ) ||
        ( ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(0)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(0) < tau21Cut ) 
          && ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(1)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(1) > tau21Cut ) );
}

template<typename ntupleType> bool antiTaggingLooseCut_photon(ntupleType* ntuple ){
    return ( ( ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(0)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(0) < tau21Cut
               ) &&
               ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(1)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(1) < tau21Cut
               ) ) ) ;
}

template<typename ntupleType> bool doubleTaggingLooseCut_photon(ntupleType* ntuple ){
    return ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(0)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(0) > tau21Cut && 
             ntuple->JetsAK8Clean_NsubjettinessTau2->at(1)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(1) > tau21Cut ) ;
}

template<typename ntupleType> bool doubleMassCut_photon(ntupleType* ntuple ){
    return ( ntuple->JetsAK8Clean_prunedMass->at(0) > ZmassWindowLow &&
             ntuple->JetsAK8Clean_prunedMass->at(0) < ZmassWindowHigh &&
             ntuple->JetsAK8Clean_prunedMass->at(1) > ZmassWindowLow &&
             ntuple->JetsAK8Clean_prunedMass->at(1) < ZmassWindowHigh );
}

template<typename ntupleType> bool singleTagCut_photon(ntupleType* ntuple ){
    return ( (ntuple->JetsAK8Clean_prunedMass->at(0) > ZmassWindowLow && 
              ntuple->JetsAK8Clean_prunedMass->at(0) < ZmassWindowHigh && 
              ntuple->JetsAK8Clean_NsubjettinessTau2->at(0)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(0) > tau21Cut ) || 
             (ntuple->JetsAK8Clean_prunedMass->at(1) > ZmassWindowLow && 
              ntuple->JetsAK8Clean_prunedMass->at(1) < ZmassWindowHigh && 
              ntuple->JetsAK8Clean_NsubjettinessTau2->at(1)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(1) > tau21Cut ) ) ;
}

template<typename ntupleType> bool doubleTagCut_photon(ntupleType* ntuple ){
    return ( ntuple->JetsAK8Clean_prunedMass->at(0) > ZmassWindowLow && 
             ntuple->JetsAK8Clean_prunedMass->at(0) < ZmassWindowHigh && 
             ntuple->JetsAK8Clean_NsubjettinessTau2->at(0)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(0) > tau21Cut && 
             ntuple->JetsAK8Clean_prunedMass->at(1) > ZmassWindowLow && 
             ntuple->JetsAK8Clean_prunedMass->at(1) < ZmassWindowHigh && 
             ntuple->JetsAK8Clean_NsubjettinessTau2->at(1)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(1) > tau21Cut ) ;
}

template<typename ntupleType> bool tagSR_photon(ntupleType* ntuple, int i){
    if( ntuple->JetsAK8Clean_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8Clean_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(i)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(i) > tau21Cut && 
             ntuple->JetsAK8Clean_prunedMass->at(i) > ZmassWindowLow && 
             ntuple->JetsAK8Clean_prunedMass->at(i) < ZmassWindowHigh );
}

template<typename ntupleType> bool tagSB_photon(ntupleType* ntuple, int i ){
    if( ntuple->JetsAK8Clean_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8Clean_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(i)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(i) > tau21Cut &&
             (
              ( ntuple->JetsAK8Clean_prunedMass->at(i) < ZmassWindowLow &&
                ntuple->JetsAK8Clean_prunedMass->at(i) > baselineMassLow ) ||
              ( ntuple->JetsAK8Clean_prunedMass->at(i) > ZmassWindowHigh &&
                ntuple->JetsAK8Clean_prunedMass->at(i) < baselineMassHigh ) 
              ) 
             );
}

template<typename ntupleType> bool antitagSR_photon(ntupleType* ntuple, int i){
    if( ntuple->JetsAK8Clean_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8Clean_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(i)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(i) < tau21Cut && 
             ( ntuple->JetsAK8Clean_prunedMass->at(i) > ZmassWindowLow &&
               ntuple->JetsAK8Clean_prunedMass->at(i) < ZmassWindowHigh ) );
}

template<typename ntupleType> bool antitagSB_photon(ntupleType* ntuple, int i){
    if( ntuple->JetsAK8Clean_doubleBDiscriminator->size() <= i || 
        ntuple->JetsAK8Clean_prunedMass->size() <= i ) return false;
    return ( ntuple->JetsAK8Clean_NsubjettinessTau2->at(i)/ntuple->JetsAK8Clean_NsubjettinessTau1->at(i) < tau21Cut &&
             (
              ( ntuple->JetsAK8Clean_prunedMass->at(i) < ZmassWindowLow &&
                ntuple->JetsAK8Clean_prunedMass->at(i) > baselineMassLow ) ||
              ( ntuple->JetsAK8Clean_prunedMass->at(i) > ZmassWindowHigh &&
                ntuple->JetsAK8Clean_prunedMass->at(i) < baselineMassHigh ) 
              )
             );
}

template<typename ntupleType> bool antitagSRCut_photon(ntupleType* ntuple){
    return ( antitagSR_photon(ntuple,0)&&antitagSR_photon(ntuple,1) );
}

template<typename ntupleType> bool antitagSBCut_photon(ntupleType* ntuple){
    return ( ( antitagSB_photon(ntuple,0)&&antitagSB_photon(ntuple,1) ) ||
             ( antitagSB_photon(ntuple,0)&&antitagSR_photon(ntuple,1) ) ||
             ( antitagSR_photon(ntuple,0)&&antitagSB_photon(ntuple,1) ) );
}

template<typename ntupleType> bool tagSRCut_photon(ntupleType* ntuple){
    return ( ( tagSR_photon(ntuple,0)&&antitagSR_photon(ntuple,1) ) || 
             ( antitagSR_photon(ntuple,0)&&tagSR_photon(ntuple,1) ) ) ;
}

template<typename ntupleType> bool tagSBCut_photon(ntupleType* ntuple){
    return ( ( tagSB_photon(ntuple,0)&&antitagSB_photon(ntuple,1) ) ||
             ( tagSR_photon(ntuple,0)&&antitagSB_photon(ntuple,1) ) ||
             ( tagSB_photon(ntuple,0)&&antitagSR_photon(ntuple,1) ) ||
             ( antitagSB_photon(ntuple,0)&&tagSB_photon(ntuple,1) ) ||
             ( antitagSR_photon(ntuple,0)&&tagSB_photon(ntuple,1) ) ||
             ( antitagSB_photon(ntuple,0)&&tagSR_photon(ntuple,1) ) );

}

template<typename ntupleType> bool doubletagSRCut_photon(ntupleType* ntuple){
    return ( tagSR_photon(ntuple,0)&&tagSR_photon(ntuple,1) );
}

template<typename ntupleType> bool doubletagSBCut_photon(ntupleType* ntuple){
    return ( ( tagSB_photon(ntuple,0)&&tagSB_photon(ntuple,1) ) ||
             ( tagSB_photon(ntuple,0)&&tagSR_photon(ntuple,1) ) ||
             ( tagSR_photon(ntuple,0)&&tagSB_photon(ntuple,1) ) );
}

/////////////////////////////////////////////////
// - - - - - - - Trigger Cuts - - - - - - - -  //
/////////////////////////////////////////////////
template<typename ntupleType> bool signalTriggerCut(ntupleType* ntuple){
    return ntuple->TriggerPass->at(42) == 1 || ntuple->TriggerPass->at(43) == 1 || ntuple->TriggerPass->at(44) == 1 || ntuple->TriggerPass->at(45) == 1 ; 
}

template<typename ntupleType> bool singleMuTriggerCut(ntupleType* ntuple){
    return ( ntuple->TriggerPass->at(20)==1 || ntuple->TriggerPass->at(21)==1 || ntuple->TriggerPass->at(22)==1 || ntuple->TriggerPass->at(23)==1 || ntuple->TriggerPass->at(24)==1 || ntuple->TriggerPass->at(28)==1 || ntuple->TriggerPass->at(29)==1 );
}

template<typename ntupleType> bool singleEleTriggerCut(ntupleType* ntuple){
    return ntuple->TriggerPass->at(6) == 1 || ntuple->TriggerPass->at(7) == 1 || ntuple->TriggerPass->at(8) == 1 || ntuple->TriggerPass->at(9) == 1 || ntuple->TriggerPass->at(10) == 1 || ntuple->TriggerPass->at(11) == 1 || ntuple->TriggerPass->at(12) == 1 || ntuple->TriggerPass->at(13) == 1 || ntuple->TriggerPass->at(14) == 1 ;
}

template<typename ntupleType> bool lowDphiTriggerCut(ntupleType* ntuple){
    return ntuple->TriggerPass->at(42) == 1 || ntuple->TriggerPass->at(43) == 1 || ntuple->TriggerPass->at(44) == 1 || ntuple->TriggerPass->at(45) == 1 ; 
}

template<typename ntupleType> bool photonTriggerCut(ntupleType* ntuple){
    return ntuple->TriggerPass->at(53) == 1 || ntuple->TriggerPass->at(54) == 1 ; // || ntuple->TriggerPass->at(51) || ntuple->TriggerPass->at(52);
}

template<typename ntupleType> int getClosestGenHiggses(ntupleType* ntuple, double jeteta, double jetphi){
    float dRMin=999999.;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( ntuple->GenParticles_PdgId->at(i) == 25 &&
            ntuple->GenParticles_ParentId->at(i) == 1000023 &&
            ntuple->GenParticles_Status->at(i) == 22 ){
                float dR=sqrt((jeteta-ntuple->GenParticles->at(i).Eta())*(jeteta-ntuple->GenParticles->at(i).Eta()) +(jetphi-ntuple->GenParticles->at(i).Phi())*(jetphi-ntuple->GenParticles->at(i).Phi()));
                if(dRMin>dR)dRMin=dR;
                }
    }
    return dRMin;
}
template<typename ntupleType> int getClosestGenZ(ntupleType* ntuple, double jeteta, double jetphi){
    float dRMin=999999.;
    for( int i=0 ; i < ntuple->GenParticles->size() ; i++ ){
        if( ntuple->GenParticles_PdgId->at(i) == 23 &&
            ntuple->GenParticles_ParentId->at(i) == 1000023 &&
            ntuple->GenParticles_Status->at(i) == 22 ){
                float dR=sqrt((jeteta-ntuple->GenParticles->at(i).Eta())*(jeteta-ntuple->GenParticles->at(i).Eta()) +(jetphi-ntuple->GenParticles->at(i).Phi())*(jetphi-ntuple->GenParticles->at(i).Phi()));
                if(dRMin>dR)dRMin=dR;
                }
    }
    return dRMin;
}

template<typename ntupleType>double ResolutionSmear(ntupleType* ntuple, int j,unsigned int seed, bool SFUp=false){
    TRandom3 rand(seed);
    double sigmaJMR=0;
    if(ntuple->JetsAK8_NumBhadrons->at(j)!=2)return ntuple->JetsAK8_softDropMass->at(j);
    if(ntuple->JetsAK8->at(j).Pt()>300. && ntuple->JetsAK8->at(j).Pt()<=600.)sigmaJMR=12.55;
    if(ntuple->JetsAK8->at(j).Pt()>600. && ntuple->JetsAK8->at(j).Pt()<=800.)sigmaJMR=10.24;
    if(ntuple->JetsAK8->at(j).Pt()>800. && ntuple->JetsAK8->at(j).Pt()<=1000.)sigmaJMR= 9.85;
    if(ntuple->JetsAK8->at(j).Pt()>1000.)sigmaJMR=9.44;
    sigmaJMR=sigmaJMR/110.;
    double sigmaJMRSF=1.23;
    if(SFUp)sigmaJMRSF=sigmaJMRSF-0.18;
    double dRHiggs=getClosestGenHiggses(ntuple, ntuple->JetsAK8->at(j).Eta(), ntuple->JetsAK8->at(j).Phi());
    double dRZ=getClosestGenZ(ntuple, ntuple->JetsAK8->at(j).Eta(), ntuple->JetsAK8->at(j).Phi());
    if(dRHiggs>dRZ){
        if(ntuple->JetsAK8->at(j).Pt()>300. && ntuple->JetsAK8->at(j).Pt()<=600.)sigmaJMR=8.27;
        if(ntuple->JetsAK8->at(j).Pt()>600. && ntuple->JetsAK8->at(j).Pt()<=800.)sigmaJMR=7.13;
        if(ntuple->JetsAK8->at(j).Pt()>800. && ntuple->JetsAK8->at(j).Pt()<=1000.)sigmaJMR=6.83;
        if(ntuple->JetsAK8->at(j).Pt()>1000.)sigmaJMR=6.90;
        sigmaJMR=sigmaJMR/83.;
    }
    double gausSmear=rand.Gaus(0, sigmaJMR)*sqrt((sigmaJMRSF*sigmaJMRSF -1));
    double smearmass=(gausSmear+1.)*ntuple->JetsAK8_softDropMass->at(j);
    return smearmass;
}
template<typename ntupleType>double SignalISRCorrection(ntupleType* ntuple){
    float ISRWeights[7]={1.0, 0.920, 0.821, 0.715, 0.662, 0.561,0.511};
    if(ntuple->NJetsISR==0) return ISRWeights[0];
    if(ntuple->NJetsISR==1) return ISRWeights[1];
    if(ntuple->NJetsISR==2) return ISRWeights[2];
    if(ntuple->NJetsISR==3) return ISRWeights[3];
    if(ntuple->NJetsISR==4) return ISRWeights[4];
    if(ntuple->NJetsISR==5) return ISRWeights[5];
    if(ntuple->NJetsISR>=6) return ISRWeights[6];
}

