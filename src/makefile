CC=g++
CFLAGS=
LIBS=`root-config --cflags --glibs` -L $(ROOTSYS)/lib -I$(ROOTSYS)/include
ROOFITLIBS=-lRooFit -lHtml -lMinuit -lRooFitCore
INCLUDES=-I$(CMSSW_BASE)/src/AnalysisTools/src/ -I$(CMSSW_BASE)/src/ -I$(CMSSW_BASE)/src/Analysis/btag/ -I$(CMSSW_BASE)/src/cxxopts/include/
EXECS=fitWpeak flavorFit plotObs_photon_baseline plotObs_singleEleCR_baseline plotObs_lowDPhi_baseline plotObs_singleTag plotObs_doubleTag plotObs_antitag plotObs_baseline plotObs_singleMuCR_baseline cutFlow ALPHABET ALPHABET_photon datacardInputs photonSkim WtaggingEfficiency.cc plotWtagDist.cc unblindSignalRegion.cc
$(EXECS):RA2bTree.cc definitions.cc skimSamples.cc plotterUtils.cc skimMassSearchRegion.cc
flavorFit:flavorFit.cc
fitWpeak:fitWpeak.cc
plotObs_singleEleCR_baseline:plotObs_singleEleCR_baseline.cc
plotObs_singleMuCR_baseline:plotObs_singleMuCR_baseline.cc
plotObs_baseline:plotObs_baseline.cc
plotObs_antitag:plotObs_antitag.cc
plotObs_photon_baseline:plotObs_photon_baseline.cc
plotObs_lowDPhi_baseline:plotObs_lowDPhi_baseline.cc
plotObs_doubleTag:plotObs_doubleTag.cc
plotObs_singleTag:
cutFlow:cutFlow.cc RA2bTree.cc skimSamples.cc
ALPHABET:ALPHABET.cc
ALPHABET_photon:ALPHABET_photon.cc
datacardInputs:datacardInputs.cc
photonSkim:photonSkim.cc
WtaggingEfficiency:WtaggingEfficiency.cc
plotWtagDist:plotWtagDist.cc
unblindSignalRegion:unblindSignalRegion.cc
skimMassSearchRegion:skimMassSearchRegion.cc

all:$(EXECS) 

unblindSignalRegion:
	$(CC) $(CFLAGS) $(LIBS) $(ROOFITLIBS) $(INCLUDES) unblindSignalRegion.cc -o ../bin/$@	
plotWtagDist:
	$(CC) $(CFLAGS) $(LIBS) $(ROOFITLIBS) $(INCLUDES) plotWtagDist.cc -o ../bin/$@	
fitWpeak:
	$(CC) $(CFLAGS) $(LIBS) $(ROOFITLIBS) $(INCLUDES) fitWpeak.cc -o ../bin/$@	
WtaggingEfficiency:
	$(CC) $(CFLAGS) $(LIBS) $(ROOFITLIBS) $(INCLUDES) WtaggingEfficiency.cc -o ../bin/$@
photonSkim:
	$(CC) $(CFLAGS) $(LIBS) $(ROOFITLIBS) $(INCLUDES) photonSkim.cc -o ../bin/$@
flavorFit:
	$(CC) $(CFLAGS) $(LIBS) $(ROOFITLIBS) $(INCLUDES) flavorFit.cc -o ../bin/$@
plotObs_fastFullComp:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) plotObs_fastFullComp.cc -o ../bin/$@
ALPHABET:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) ALPHABET.cc -o ../bin/$@
ALPHABET_photon:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) ALPHABET_photon.cc -o ../bin/$@
cutFlow:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) cutFlow.cc -o ../bin/$@
plotObs_photon_baseline:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) plotObs_photon_baseline.cc -o ../bin/$@
plotObs_lowDPhi_baseline:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) plotObs_lowDPhi_baseline.cc -o ../bin/$@
plotObs_singleTag:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) plotObs_singleTag.cc -o ../bin/$@
plotObs_doubleTag:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) plotObs_doubleTag.cc -o ../bin/$@
plotObs_antitag:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) plotObs_antitag.cc -o ../bin/$@
plotObs_baseline:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) plotObs_baseline.cc -o ../bin/$@
plotObs_singleEleCR_baseline:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) plotObs_singleEleCR_baseline.cc -o ../bin/$@	
plotObs_singleMuCR_baseline:
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) plotObs_singleMuCR_baseline.cc -o ../bin/$@	
datacardInputs:
	$(CC) $(CFLAGS) $(LIBS) $(ROOFITLIBS) $(INCLUDES) datacardInputs.cc -o ../bin/$@
skimMassSearchRegion:
	$(CC) $(CFLAGS) $(LIBS) $(ROOFITLIBS) $(INCLUDES) skimMassSearchRegion.cc -o ../bin/$@

clean : 
	rm ../bin/*
