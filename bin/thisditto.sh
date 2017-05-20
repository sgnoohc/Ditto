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

if [ "x${SCRAM_ARCH}" == "x" ]; then error; return; fi
if [ "x${CMSSW_VERSION}" == "x" ]; then error; return; fi

export PATH=$DIR:$PATH
export DITTOPATH=$DIR/..

alias setup_ditto="source $DIR/setup_ditto"
alias unset_ditto="source $DIR/unset_ditto"
alias ditto_looper_template="source $DIR/ditto_looper_template"
alias ditto_load="source $DIR/ditto_load"
