#include "TH1F.h"
class hist{

public:
TH1D*METSnglT;
TH1D*METOther;
TH1D*METZBkg;
TH1D*METWBkg;
TH1D*METTTBarBkg;
TH1D*METQCDBkg;
TH1D*METT5HH1300Sig;
TH1D*METT5HH1700Sig;

TH1D*HTSnglT;
TH1D*HTOther;
TH1D*HTZBkg;
TH1D*HTWBkg;
TH1D*HTTTBarBkg;
TH1D*HTQCDBkg;
TH1D*HTT5HH1300Sig;
TH1D*HTT5HH1700Sig;

TH1D*JetPt1SnglT;
TH1D*JetPt1Other;
TH1D*JetPt1ZBkg;
TH1D*JetPt1WBkg;
TH1D*JetPt1TTBarBkg;
TH1D*JetPt1QCDBkg;
TH1D*JetPt1T5HH1300Sig;
TH1D*JetPt1T5HH1700Sig;

TH1D*JetPt2SnglT;
TH1D*JetPt2Other;
TH1D*JetPt2ZBkg;
TH1D*JetPt2WBkg;
TH1D*JetPt2TTBarBkg;
TH1D*JetPt2QCDBkg;
TH1D*JetPt2T5HH1300Sig;
TH1D*JetPt2T5HH1700Sig;

TH1D*PrunedMass1SnglT;
TH1D*PrunedMass1Other;
TH1D*PrunedMass1ZBkg;
TH1D*PrunedMass1WBkg;
TH1D*PrunedMass1TTBarBkg;
TH1D*PrunedMass1QCDBkg;
TH1D*PrunedMass1T5HH1300Sig;
TH1D*PrunedMass1T5HH1700Sig;

TH1D*PrunedMass2SnglT;
TH1D*PrunedMass2Other;
TH1D*PrunedMass2ZBkg;
TH1D*PrunedMass2WBkg;
TH1D*PrunedMass2TTBarBkg;
TH1D*PrunedMass2QCDBkg;
TH1D*PrunedMass2T5HH1300Sig;
TH1D*PrunedMass2T5HH1700Sig;
hist();
};
hist::hist(){
METSnglT=new TH1D("METSnglT", "MET [GeV]", 30.,300.,2000.);
METOther=new TH1D("METOther", "MET [GeV]", 30.,300.,2000.);
METZBkg=new TH1D("METZBkg", "MET [GeV]", 30.,300.,2000.);
METWBkg=new TH1D("METWBkg", "MET [GeV]", 30.,300.,2000.);
METTTBarBkg=new TH1D("METTTBarBkg", "MET [GeV]", 30.,300.,2000.);
METQCDBkg=new TH1D("METQCDBkg", "MET [GeV]", 30.,300.,2000.);
METT5HH1300Sig=new TH1D("METT5HH1300Sig", "MET [GeV]", 30.,300.,2000.);
METT5HH1700Sig=new TH1D("METT5HH1700Sig", "MET [GeV]", 30.,300.,2000.);

HTSnglT=new TH1D("HTSnglT", "HT [GeV]", 30.,200.,3000.);
HTOther=new TH1D("HTOther", "HT [GeV]", 30.,200.,3000.);
HTZBkg=new TH1D("HTZBkg", "HT [GeV]", 30.,200.,3000.);
HTWBkg=new TH1D("HTWBkg", "HT [GeV]", 30.,200.,3000.);
HTTTBarBkg=new TH1D("HTTTBarBkg", "HT [GeV]", 30.,200.,3000.);
HTQCDBkg=new TH1D("HTQCDBkg", "HT [GeV]", 30.,200.,3000.);
HTT5HH1300Sig=new TH1D("HTT5HH1300Sig", "HT [GeV]", 30.,200.,3000.);
HTT5HH1700Sig=new TH1D("HTT5HH1700Sig", "HT [GeV]", 30.,200.,3000.);

JetPt1SnglT=new TH1D("JetPt1SnglT", "JetPt1 [GeV]", 30.,0.,2000.);
JetPt1Other=new TH1D("JetPt1Other", "JetPt1 [GeV]", 30.,0.,2000.);
JetPt1ZBkg=new TH1D("JetPt1ZBkg", "JetPt1 [GeV]", 30.,0.,2000.);
JetPt1WBkg=new TH1D("JetPt1WBkg", "JetPt1 [GeV]", 30.,0.,2000.);
JetPt1TTBarBkg=new TH1D("JetPt1TTBarBkg", "JetPt1 [GeV]", 30.,0.,2000.);
JetPt1QCDBkg=new TH1D("JetPt1QCDBkg", "JetPt1 [GeV]", 30.,0.,2000.);
JetPt1T5HH1300Sig=new TH1D("JetPt1T5HH1300Sig", "JetPt1 [GeV]", 30.,0.,2000.);
JetPt1T5HH1700Sig=new TH1D("JetPt1T5HH1700Sig", "JetPt1 [GeV]", 30.,0.,2000.);

JetPt2SnglT=new TH1D("JetPt2SnglT", "JetPt2 [GeV]", 30.,0.,2000.);
JetPt2Other=new TH1D("JetPt2Other", "JetPt2 [GeV]", 30.,0.,2000.);
JetPt2ZBkg=new TH1D("JetPt2ZBkg", "JetPt2 [GeV]", 30.,0.,2000.);
JetPt2WBkg=new TH1D("JetPt2WBkg", "JetPt2 [GeV]", 30.,0.,2000.);
JetPt2TTBarBkg=new TH1D("JetPt2TTBarBkg", "JetPt2 [GeV]", 30.,0.,2000.);
JetPt2QCDBkg=new TH1D("JetPt2QCDBkg", "JetPt2 [GeV]", 30.,0.,2000.);
JetPt2T5HH1300Sig=new TH1D("JetPt2T5HH1300Sig", "JetPt2 [GeV]", 30.,0.,2000.);
JetPt2T5HH1700Sig=new TH1D("JetPt2T5HH1700Sig", "JetPt2 [GeV]", 30.,0.,2000.);

PrunedMass1SnglT=new TH1D("PrunedMass1SnglT", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass1Other=new TH1D("PrunedMass1Other", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass1ZBkg=new TH1D("PrunedMass1ZBkg", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass1WBkg=new TH1D("PrunedMass1WBkg", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass1TTBarBkg=new TH1D("PrunedMass1TTBarBkg", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass1QCDBkg=new TH1D("PrunedMass1QCDBkg", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass1T5HH1300Sig=new TH1D("PrunedMass1T5HH1300Sig", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass1T5HH1700Sig=new TH1D("PrunedMass1T5HH1700Sig", "Pruned Mass [GeV]", 50.,50.,200.);

PrunedMass2SnglT=new TH1D("PrunedMass2SnglT", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass2Other=new TH1D("PrunedMass2Other", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass2ZBkg=new TH1D("PrunedMass2ZBkg", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass2WBkg=new TH1D("PrunedMass2WBkg", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass2TTBarBkg=new TH1D("PrunedMass2TTBarBkg", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass2QCDBkg=new TH1D("PrunedMass2QCDBkg", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass2T5HH1300Sig=new TH1D("PrunedMass2T5HH1300Sig", "Pruned Mass [GeV]", 50.,50.,200.);
PrunedMass2T5HH1700Sig=new TH1D("PrunedMass2T5HH1700Sig", "Pruned Mass [GeV]", 50.,50.,200.);

}

