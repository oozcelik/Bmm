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

cd $BMMBASE/RootAnalysis/common

data2017: bin/runBmm -y 2017 -C cuts/bmmReader.2017 -f /afs/cern.ch/user/o/oozcelik/CMSSW_9_4_4/src/Bmm/CmsswAnalysis/test/bmm4/jobs/v11/bmm-rereco-RunNov2017A.root

---------------------------------------------------------------------------

ONE CAN FILL THE TREES USING CRAB3 BUT CANNOT READ THEM. ONE SHOULD USE BATCH FOR READING THE TREES!!


# Production with custom tools 

Here I will only give the instructions to read the 'private' files which means the roottuples that includes TREES.

+ Create the catalogs for the rootuples - create a file including their directories. 

cd CmsswAnalysis/test/bmm4/catalogs/

mkdir Run2017__Charmonium && cd Run2017__Charmonium

eos ls oozcelik/Charmonium/crab_BMM5_crabtest_Charmonium_Run2017B_Rereco/180519_095252/0000/ > Charmonium_Run2017B_Rereco 

+ Create the python files for each datasets

cd  $BMMBASE/CmsswAnalysis/test/bmm4/jobs/v11

mkdir Run2017B_Rereco & cd Run2017B_Rereco

$BMMBASE/perl/mkPyFiles -t ../bmm-rereco-RunNov2017-XXXX.py -f ../../../catalogs/Run2017__Charmonium/Charmonium_Run2017B_Rereco -s v11 -n 2 -l

++ you should add this into runAll.jobs

+ Create tar file (with compilation in the batch job)

cd $BMMBASE/..

$BMMBASE/perl/mkTarFile new.tar.gz

+ Submit jobs

cd  $BMMBASE/CmsswAnalysis/test/bmm4/jobs/v11

//// TO BE CONFIRMED ////

$BMMBASE/perl/run -t /afs/cern.ch/user/o/oozcelik/CMSSW_9_4_4/new.tar.gz -q all.q -m batch -c $BMMBASE/CmsswAnalysis/test/bmm4/prod.csh -r 'PFNS root://eoscms//eos/cms/ /store/user/oozcelik/' Run2017B_Rereco/bmm-rereco-RunNov2017-Charmonium_Run2017B_Rereco-v11-0000.py





