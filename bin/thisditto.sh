#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

ERROR=echo
UL=echo
SUCCESS=echo
if [ -d "$HOME/login" ]; then
  LOGINEXISTS=true;
  source ~/login/bash/utils.sh
  ERROR=e_error
  UL=e_underline
  SUCCESS=e_success
fi

error()
{
  $ERROR "ERROR: prerequisite environment is not set!"
  $UL "Please run some CMS setup first."
  echo ""
  echo "==================================================="
  echo SCRAM_ARCH=$SCRAM_ARCH
  echo CMSSW_VERSION=$CMSSW_VERSION
  echo "==================================================="
  echo ""
  echo ""
}


# Environment setting same as my ditto environment
#source /code/osgcode/cmssoft/cmsset_default.sh  > /dev/null 2>&1
#export SCRAM_ARCH=slc6_amd64_gcc530   # or whatever scram_arch you need for your desired CMSSW release
#export CMSSW_VERSION=CMSSW_8_0_18
#cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$CMSSW_VERSION/src
#eval `scramv1 runtime -sh`
#cd -

if [ "x${SCRAM_ARCH}" == "x" ]; then error; return; fi
if [ "x${CMSSW_VERSION}" == "x" ]; then error; return; fi

export PATH=$DIR:$PATH
export DITTOPATH=${DIR///bin/}

alias ditto_setup="source $DIR/setup_ditto"
alias ditto_unset="source $DIR/unset_ditto"
alias ditto_include_core="source $DIR/ditto_include_core"
alias ditto_looper_template="source $DIR/ditto_looper_template"
alias ditto_load="source $DIR/ditto_load"

