#!/bin/sh
output_dir=$1
executable=$2
args1=$3
args2=$4
args3=$5
args4=$6
args5=$7
args6=$8
echo "output_dir ${output_dir}"
echo "executable ${executable}"
echo "args ${args}"

mv ../../workingArea.tar .
tar -xf workingArea.tar
cd CMSSW_7_4_2/src/
eval `scramv1 runtime -sh`
echo "step 2"
cd boostedZPlusMET
export PATH=$PWD/bin/:$PATH
echo "PWD ${PWD}"
echo "PATH ${PATH}"
cd src
make all

`echo $executable $args1 $args2 $args3 $args4 $args5 $args6`

ls *root
ls ../plots/*/*
ls $CMSSW_BASE/../*condor
ls $CMSSW_BASE/../*stdout
ls $CMSSW_BASE/../*stderr

for file in $(ls *root)
do
    xrdcp -f $file root://cmseos.fnal.gov//store/user/${USER}/boostedZPlusMET/$output_dir/$file
done

cd ../
for file in $(ls plots/*/*)
do 
    xrdcp -f $file root://cmseos.fnal.gov//store/user/${USER}/boostedZPlusMET/$output_dir/$file
done

cd $CMSSW_BASE/
cd ../
for file in $(ls *condor)
do
    echo /store/user/${USER}/boostedZPlusMET/$output_dir/$file
    xrdcp -f $file root://cmseos.fnal.gov//store/user/${USER}/boostedZPlusMET/$output_dir/$file
done

for file in $(ls *stderr)
do
    echo /store/user/${USER}/boostedZPlusMET/$output_dir/$file
    xrdcp -f $file root://cmseos.fnal.gov//store/user/${USER}/boostedZPlusMET/$output_dir/$file
done

for file in $(ls *stdout)
do
    echo /store/user/${USER}/boostedZPlusMET/$output_dir/$file
    xrdcp -f $file root://cmseos.fnal.gov//store/user/${USER}/boostedZPlusMET/$output_dir/$file
done

