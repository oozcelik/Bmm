For mounting tier-3 to the scratch area:

cd /scratch

mkdir oozcelik (if you don't have any yet)

gfalFS -s store/ srm://t3se01.psi.ch/pnfs/psi.ch/cms/trivcat/store/

ls -lrt store/ (to make sure you mount it)

gfalFS_umount /scratch/oozcelik/store/ (to unmount it)

Bmm
===

Please see https://twiki.cern.ch/twiki/bin/viewauth/CMS/Bmm4 for more information.


Instructions to me at 9_4_X:

--------------- cmsRun -> T1 trees ---------------

cmsrel CMSSW_9_4_4

cd CMSSW_9_4_4/src

cmsenv

git cms-init   

git clone git@github.com:Bmm4/Bmm

cd Bmm/

export BMMBASE=$(pwd)

cd Bmm/RootAnalysis/rootio

make -j8 all links

cd ../common

make -j8 all links

cd ../..

scramv1 b -j8

cd CmsswAnalysis/test/bmm4/jobs/v11

cmsRun 'configuration file'


--------------- runBmm -> reduced trees ---------------

To make and run the treeReaders, do

# Production with custom tools 


## To run single jobs :

data2017: bin/runBmm -y 2017 -C cuts/bmmReader.2017 -f /afs/cern.ch/user/o/oozcelik/CMSSW_9_4_4/src/Bmm/CmsswAnalysis/test/bmm4/jobs/v11/bmm-rereco-RunNov2017A.root

---------------------------------------------------------------------------

MC2017: bin/runBmm -y 2017 -m 1 -C cuts/bmmReader.mix-Bu2JpsiK -f  root://t3dcachedb.psi.ch:1094/pnfs/psi.ch/cms/trivcat//store/user/oozcelik/BuToJpsiK_BMuonFilter_SoftQCDnonD_TuneCP5_13TeV-pythia8-evtgen/crab_BMM5_BuToJpsiK_MC_13Tev/180814_124253/0000/Bu2JpsiKstar_MC2017_654.root

## To run batch jobs :

—runBmm—

$BMMBASE/perl/srmFind -c -p MC2017 /scratch/oozcelik/store/user/oozcelik/BuToJpsiK_BMuonFilter_SoftQCDnonD_TuneCP5_13TeV-pythia8-evtgen/crab_BMM5_BuToJpsiK_PU2017_13TeV/180920_102113/0000/ | sort > b2mm

$BMMBASE/perl/mkCheckedChain b2mm

$BMMBASE/perl/splitCheckedChain -n 200000 cb2mm

$BMMBASE/perl/run -m batch -c $BMMBASE/RootAnalysis/macros/runBmmNoComp.csh -t /mnt/t3nfs01/data01/shome/oozcelik/bmm/CMSSW_9_4_6_patch1/runBmm.tar.gz -q short.q -x 'bin/runBmm -y 2017 -m 1 -C cuts/bmmReader.mix-Bu2JpsiK' -r 'PFNS srm://t3se01.psi.ch:8443/srm/managerv2\?SFN=/pnfs/psi.ch/cms/trivcat%STORAGE1 /store/user/$USER/bmm5/runBmm/Bu2JpsiK_PU2017%SITE T3_CH_PSI' cb2mm*


—merge files—

$BMMBASE/perl/srmHadd -x "$PSI"/store/user/oozcelik/bmm5/runBmm/Charmonium_2017 -p cb2mm -o output.root

—runPlot—

bin/runPlot -y 2017 -d /mnt/t3nfs01/data01/shome/oozcelik/bmm/CMSSW_9_4_6_patch1/src/Bmm/RootAnalysis/macros -s 2017 -c cuts/baseCuts.2017.cuts -f plotResults.2017.files -p overlays -m 2017

 
 




