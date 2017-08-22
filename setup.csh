#!/bin/tcsh

if ( ! -d bin ) then 
    mkdir bin
endif

setenv PATH $PWD/bin/:$PATH

if ( ! -d plots ) then
    mkdir plots
    endif
set plotsDirList="plotObs_singleEleCR_baseline_plots plotObs_doubleTag_plots plotObs_singleTag_plots plotObs_singleMuCR_baseline_plots ABCDscaleFactors cutFlow_plots cutFlow_lowDPhi_plots cutFlow_singleEleCR_plots cutFlow_singleMuCR_plots plotObs_lowDPhi_baseline_plots ALPHABET NminusOne_plots plotObs_antitag_plots plotObs_photon_baseline_plots plotObs_photon_looseCuts_baseline_plots plotObs_baseline_plots"
foreach i ($plotsDirList) 
    if ( ! -d plots/$i ) then 
        mkdir plots/$i
        endif
end
