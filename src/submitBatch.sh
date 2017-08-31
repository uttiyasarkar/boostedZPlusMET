#!/bin/bash

submitDir=$PWD
branch=$1
hash=`git rev-parse origin/${branch}`

if [ ! -e /eos/uscms/store/user/${USER}/boostedZPlusMET/ ] 
    then
    echo "I need /eos/uscms/store/user/${USER}/boosteZPlusMET/"
    exit
fi

echo "hash ${hash}"               # this is intended to correspond to the hash of your git commit for tracking/reproducibility
                                  # -- you can get the hash with `git rev-parse origin/RA2b_V12_v0`
source makeOutputDir.sh $hash     # setup directories in eos for output
source makeTar.sh                 # package up code to transfer to worker nodes
cd $submitDir

condor_submit batchExecute.jdl exec_name="cutFlow_signal" arguments="${hash} cutFlow --region=0"
condor_submit batchExecute.jdl exec_name="cutFlow_singleMu" arguments="${hash} cutFlow --region=1"
condor_submit batchExecute.jdl exec_name="cutFlow_singleEle" arguments="${hash} cutFlow --region=2"
condor_submit batchExecute.jdl exec_name="cutFlow_lowDphi" arguments="${hash} cutFlow --region=3"

condor_submit batchExecute.jdl exec_name="plotObs_baseline" arguments="${hash} plotObs_baseline"
condor_submit batchExecute.jdl exec_name="plotObs_antitag" arguments="${hash} plotObs_antitag"
condor_submit batchExecute.jdl exec_name="plotObs_doubleTag" arguments="${hash} plotObs_doubleTag"
condor_submit batchExecute.jdl exec_name="plotObs_singleTag" arguments="${hash} plotObs_singleTag"

condor_submit batchExecute.jdl exec_name="plotObs_singleEleCR_baseline" arguments="${hash} plotObs_singleEleCR_baseline"
condor_submit batchExecute.jdl exec_name="plotObs_singleMuCR_baseline" arguments="${hash} plotObs_singleMuCR_baseline"

condor_submit batchExecute.jdl exec_name="plotObs_photon_baseline" arguments="${hash} plotObs_photon_baseline"
condor_submit batchExecute.jdl exec_name="plotObs_photon_looseCuts_baseline" arguments="${hash} plotObs_photon_baseline --loose_cuts=1"

condor_submit batchExecute.jdl exec_name="plotObs_lowDPhi_baseline" arguments="${hash} plotObs_lowDPhi_baseline"

condor_submit batchExecute.jdl exec_name="ALPHABET_signal" arguments="${hash} ALPHABET --region=0"
condor_submit batchExecute.jdl exec_name="ALPHABET_singleMu" arguments="${hash} ALPHABET --region=1"
condor_submit batchExecute.jdl exec_name="ALPHABET_singleEle" arguments="${hash} ALPHABET --region=2"
condor_submit batchExecute.jdl exec_name="ALPHABET_lowDPhi" arguments="${hash} ALPHABET --region=3"

condor_submit batchExecute.jdl exec_name="ALPHABET_signal_loose" arguments="${hash} ALPHABET --region=0 --loose_cuts=1"
condor_submit batchExecute.jdl exec_name="ALPHABET_singleMu_loose" arguments="${hash} ALPHABET --region=1 --loose_cuts=1"
condor_submit batchExecute.jdl exec_name="ALPHABET_singleEle_loose" arguments="${hash} ALPHABET --region=2 --loose_cuts=1"
condor_submit batchExecute.jdl exec_name="ALPHABET_lowDPhi_loose" arguments="${hash} ALPHABET --region=3 --loose_cuts=1"

condor_submit batchExecute.jdl exec_name="ALPHABET_photon" arguments="${hash} ALPHABET_photon"
condor_submit batchExecute.jdl exec_name="ALPHABET_photon_loose" arguments="${hash} ALPHABET_photon --loose_cuts=1"

condor_submit batchExecute.jdl exec_name="datacardInputs" arguments="${hash} datacardInputs"

