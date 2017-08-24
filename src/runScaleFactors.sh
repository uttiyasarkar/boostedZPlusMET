#!/bin/sh

if [ $# != 1 ]
then
    echo "NEED TO PROVIDE HASH CODE"
    exit
fi

COMMIT=$1

echo "COMMIT: ${COMMIT}"

regions="_looseCuts_photon _photon _singleMu _looseCuts_singleMu _singleEle _looseCuts_singleEle _singleLep _looseCuts_singleLep _lowDphi _looseCuts_lowDphi"

echo "^^^^ Signal region ^^^^^" 
echo ">>>> >100 "
root -l -n -b -q 'checkScaleFactors.cc("",true,"~/eos/boostedZPlusMET/'$COMMIT'/","MET",1,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
#root -l -n -b -q 'checkScaleFactors.cc("",false,"~/eos/boostedZPlusMET/'$COMMIT'/","MET",1,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
echo ">>>> >100 fine"
root -l -n -b -q 'checkScaleFactors.cc("",true,"~/eos/boostedZPlusMET/'$COMMIT'/","METfine",1,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
#root -l -n -b -q 'checkScaleFactors.cc("",false,"~/eos/boostedZPlusMET/'$COMMIT'/","METfine",1,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
echo ">>>> >300 "
root -l -n -b -q 'checkScaleFactors.cc("",true,"~/eos/boostedZPlusMET/'$COMMIT'/","MET",2,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
#root -l -n -b -q 'checkScaleFactors.cc("",false,"~/eos/boostedZPlusMET/'$COMMIT'/","MET",2,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'

for region in $regions 
do
    echo "^^^^ "$region" region ^^^^^" 
    echo ">>>> >100 "
    root -l -n -b -q 'checkScaleFactors.cc("'$region'",true,"~/eos/boostedZPlusMET/'$COMMIT'/","MET",1,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
    #root -l -n -b -q 'checkScaleFactors.cc("'$region'",false,"~/eos/boostedZPlusMET/'$COMMIT'/","MET",1,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
    echo ">>>> >100 fine"
    root -l -n -b -q 'checkScaleFactors.cc("'$region'",true,"~/eos/boostedZPlusMET/'$COMMIT'/","METfine",1,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
    #root -l -n -b -q 'checkScaleFactors.cc("'$region'",false,"~/eos/boostedZPlusMET/'$COMMIT'/","METfine",1,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
    echo ">>>> >300 "
    root -l -n -b -q 'checkScaleFactors.cc("'$region'",true,"~/eos/boostedZPlusMET/'$COMMIT'/","MET",2,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
    #root -l -n -b -q 'checkScaleFactors.cc("'$region'",false,"~/eos/boostedZPlusMET/'$COMMIT'/","MET",2,4,"~/eos/boostedZPlusMET/'$COMMIT'/plots/ABCDscaleFactors/")'
done
