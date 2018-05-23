import os
from array import array
from ROOT import *
f=open("realistic-counting-experimentoptimization.txt", "r")
#fsig=TFile("T5ZZSignalModelsSubJetCut.root", "READ");
#fsig=TFile("T5ZZSignalModels.root", "READ");
finputs=TFile("TwoAK8JetDataCards.root", "READ");
SLControlSB=finputs.Get("SLSBOther")
SLControlSB.Add(finputs.Get("SLSBWJets"));
SLControlSB.Add(finputs.Get("SLSBTT"));
SLControlSB.Add(finputs.Get("SLSBSnglT"));
SLControlSR=finputs.Get("SLSROther")
SLControlSR.Add(finputs.Get("SLSRWJets"));
SLControlSR.Add(finputs.Get("SLSRTT"));
SLControlSR.Add(finputs.Get("SLSRSnglT"));
SLControlSB.Scale(1.0/SLControlSB.Integral())
SLControlSR.Scale(1.0/SLControlSR.Integral())
fout=TFile("HistogramsOptimization.root","RECREATE");
Other=finputs.Get("METBinsOther")
TT=finputs.Get("METBinsTT")
ZJets=finputs.Get("METBinsZJets")
WJets=finputs.Get("METBinsWJets")
QCD=finputs.Get("METBinsQCD")
SnglT=finputs.Get("METBinsSnglT")
TT.SetFillColor(kCyan);
ZJets.SetFillColor(kGreen);
WJets.SetFillColor(kBlue);
Other.SetFillColor(kMagenta);
QCD.SetFillColor(kRed);
SnglT.SetFillColor(kOrange);
hs=THStack();
hs.Add(Other);
hs.Add(SnglT);
hs.Add(TT);
hs.Add(QCD);
hs.Add(WJets);
hs.Add(ZJets);
Total=hs.GetStack().Last()
mGo=[750,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100]
fout.cd();
hs.Write("TotalBkgMET");
Total.Write("InputBkg");
###### Define MET BIN
#METBin=[300, 500, 700, 2000]
METBin=[300, 500, 700, 900, 1100,2000]
#METBin=[300, 400,500, 700, 900,2000]
#METBin=[300, 350,400,500, 600,700, 900,2000]
#METBin=[300, 350,400,500, 600,700, 900,2000]
SearchBins=TH1D("SearchBins", "", len(METBin)-1, array('d',METBin));
BkgBins=[]
BkgUnc=[]
##Bkg Bins
for i in range(0,len(METBin)-1):
	lowbin=Total.GetXaxis().FindBin(METBin[i])	
	highbin=Total.GetXaxis().FindBin(METBin[i+1])	
	BkgBins.append(Total.Integral(lowbin,highbin))
	fracUnc=1.0+(SLControlSB.Integral(lowbin,highbin)-SLControlSR.Integral(lowbin,highbin))/(SLControlSB.Integral(lowbin,highbin));
	print SLControlSR.Integral(lowbin,highbin),SLControlSB.Integral(lowbin,highbin)
	BkgUnc.append(fracUnc);
	
print BkgBins
print BkgUnc
for m in mGo:
	signal=finputs.Get("METT5HH%d" %m)
	SignalYields=[]
	for i in range(0,len(METBin)-1):
		lowbin=signal.GetXaxis().FindBin(METBin[i])
        	highbin=signal.GetXaxis().FindBin(METBin[i+1])	
		SignalYields.append(signal.Integral(lowbin,highbin));
	print SignalYields
	fout=open("T5ZZ%dSingleJet.txt" %m,"w")
	fout.write("# Simple counting experiment, with one signal and a few background processes\n");
	fout.write("# Simplified version of the 35/pb H->WW analysis for mH = 160 GeV\n")
	fout.write("imax %d  number of channels\n" %(len(METBin)-1))
	fout.write("jmax 1  number of backgrounds\n")
	fout.write("kmax *  number of nuisance parameters (sources of systematical uncertainties)\n")
	fout.write("bin ");
	for i in range(0,len(METBin)-1):fout.write("bin%d " %i);
	fout.write("\n");
	fout.write("observation ")
	for i in range(0,len(METBin)-1):fout.write(" %.2f" %BkgBins[i])
	fout.write("\n");
	fout.write("bin ");
	for i in range(0,len(METBin)-1):fout.write(" bin%d bin%d " %(i,i));
	fout.write("\nprocess ");
	for i in range(0,len(METBin)-1):fout.write(" sig bkg ")
	fout.write("\nprocess ");
	for i in range(0,len(METBin)-1):fout.write(" 0 1 ")
	fout.write("\nrate ")
	for i in range(0,len(METBin)-1):fout.write("%.2f %.2f " %(SignalYields[i],BkgBins[i]))
	fout.write("\n------------\n");
	fout.write("BkgMetUnc lnN ")
	for i in range(0,len(METBin)-1):fout.write(" -  %.2f " %BkgUnc[i])
	fout.write("\nBkgShapeUnc lnN ")
	for i in range(0,len(METBin)-1):fout.write(" -  1.1 ")
	fout.close()
	os.system("combine -M Asymptotic T5ZZ%dSingleJet.txt -m %d -n T5ZZ%d " %(m,m,m))
	#break;
'''
	f.seek(0);
	for line in f:
		if "rate" in line:
			line=line.replace("sig1", "%g" %signal.GetBinContent(1));
			line=line.replace("sig2", "%g" %signal.GetBinContent(2));
			line=line.replace("sig3", "%g" %signal.GetBinContent(3));
			#print line
		fout.write(line)
	fout.close()
	#os.system("combine -M Asymptotic T5ZZ%d.txt -m %d -n T5ZZ%d.txt " %(m,m,m))
f1=open("realistic-counting-experimentSingleBin.txt", "r")

for m in mGo:
        signal=fsig1.Get("T5HH%d" %m)
	f1.seek(0);
  	for line in f1:
                if "rate" in line:line=line.replace("sig1", "%g" %signal.GetBinContent(3));
		fout.write(line)
	fout.close()
	#os.system("combineCards.py T5ZZ%d.txt T5ZZ%dSingleJet.txt> T5ZZCombine%d.txt" %(m,m,m) ) 
	#os.system("combine -M Asymptotic T5ZZCombine%d.txt -m %d -n T5ZZ%d.txt " %(m,m,m))
f2=open("realistic-counting-experimentBtags.txt","r")
fsigb=TFile("SignalCards2Ak8DoubleB.root", "READ");

for m in mGo:
        signal=fsigb.Get("T5HH%d" %m)
        fout=open("T5ZZ%dBtags.txt" %m,"w")
	f2.seek(0);
	for line in f2:
                if "rate" in line:line=line.replace("sig1", "%g" %signal.GetBinContent(1));
                if "rate" in line:line=line.replace("sig2", "%g" %signal.GetBinContent(2));
                if "rate" in line:line=line.replace("sig3", "%g" %signal.GetBinContent(3));
                fout.write(line)
        fout.close()
	#os.system("combineCards.py T5ZZ%d.txt T5ZZ%dSingleJet.txt T5ZZ%dBtags.txt  > T5ZZCombine%d.txt" %(m,m,m,m) ) 
	os.system("combineCards.py T5ZZ%d.txt T5ZZ%dSingleJet.txt   > T5ZZCombine%d.txt" %(m,m,m) ) 
	os.system("combine -M Asymptotic T5ZZCombine%d.txt -m %d -n T5ZZ%d.txt " %(m,m,m))
'''	
