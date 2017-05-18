#!/bin/bash

export SCRAM_ARCH=slc6_amd64_gcc530   # or whatever scram_arch you need for your desired CMSSW release
export CMSSW_VERSION=CMSSW_8_0_18
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$CMSSW_VERSION/src
eval `scramv1 runtime -sh`
cd -

ANALYSIS=$1
HADOOPDIR=$2
SAMPLEFILENAME=$3
NEVENTS=$4

./ditto_ana_${ANALYSIS} ${HADOOPDIR} ${SAMPLEFILENAME} ${NEVENTS}

if [ -e ${SAMPLEFILENAME}_skimtree.root ]; then
  gfal-copy -p -f -t 4200 file://`pwd`/${SAMPLEFILENAME}_skimtree.root srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=/hadoop/cms/store/user/phchang/ditto_skimmed_babies/${ANALYSIS}/${SAMPLEFILENAME}_skimtree.root --checksum ADLER32
else
  echo "Ditto::CondorExecutuable:: No *_skimtree.root files to copy..."
fi

if [ -e ${SAMPLEFILENAME//_skimtree}_hist.root ]; then
  gfal-copy -p -f -t 4200 file://`pwd`/${SAMPLEFILENAME//_skimtree}_hist.root srm://bsrm-3.t2.ucsd.edu:8443/srm/v2/server?SFN=/hadoop/cms/store/user/phchang/ditto_output/${ANALYSIS}/${SAMPLEFILENAME//_skimtree}_hist.root --checksum ADLER32
else
  echo "Ditto::CondorExecutuable:: No *_hist.root files to copy..."
fi