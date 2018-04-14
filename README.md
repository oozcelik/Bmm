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
cd Bmm/RootAnalysis/rootio
make -j8 all links
cd ../common
make -j8 all links
cd ../..
scramv1 b -j8
cd CmsswAnalysis/test/bmm4/jobs/v11
cmsRun 'configuration file'
