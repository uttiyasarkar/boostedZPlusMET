#define MassMETPlots_cxx
#include "MassMETPlots.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <iostream>
void MassMETPlots::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L MassMETPlots.C
//      Root > MassMETPlots t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   TH1D*MassSidebandPlot=new TH1D("MassSidebandPlot","", 30, 50,200);
   TH1D*MassPlot=new TH1D("MassPlot", "", 30, 50,200);
   TH1D*METPlot=new TH1D("METPlot","",24, 300,1500);
   TH1D*METPlotSB=new TH1D("METPlotSB","",110, 300,2100);
   TH1D*METPlotSR=new TH1D("METPlotSR","",110, 300,2100);
   METPlotSR->Sumw2(kTRUE);
   METPlotSB->Sumw2(kTRUE);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) < 0) continue;
       if(((PrunedMass1>50 && PrunedMass1<75) || (PrunedMass1>95 && PrunedMass1<200)) && PrunedMass2>75 && PrunedMass2<95 )METPlotSB->Fill(MET, Evtweight);
      if(PrunedMass1>75 && PrunedMass1<95 && PrunedMass2>75 && PrunedMass2<95 ){MassPlot->Fill(PrunedMass1,Evtweight); METPlotSR->Fill(MET, Evtweight);} //Signal Region;
      if(((PrunedMass1>50 && PrunedMass1<75) || (PrunedMass1>95 && PrunedMass1<200) ) && PrunedMass2>75 && PrunedMass2<95 )MassSidebandPlot->Fill(PrunedMass1,Evtweight);//Mass Sideband;
       if((PrunedMass1>50 && PrunedMass1<75) && PrunedMass2>50 && PrunedMass2<200){METPlot->Fill(MET, Evtweight); }//MET plot in Sideband Region;
      std::cout<<jentry<<std::endl;
   }
TFile*fout=new TFile(treename_+"OutputDistribtuions.root", "RECREATE");
MassSidebandPlot->Write(treename_+"SidebandPlot");
MassPlot->Write(treename_+"SignalRegionMassPlot");
METPlotSB->Write(treename_+"METShapeSB");
METPlotSR->Write(treename_+"METShapeSR");
METPlot->Write(treename_+"METShape");
fout->Close();
}
