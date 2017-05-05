#!/bin/bash

ERROR=echo
UL=echo
if [ -d "$HOME/login" ]; then
  LOGINEXISTS=true;
  source ~/login/bash/utils.sh
  ERROR=e_error
  UL=e_underline
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
  $ERROR "ERROR: This setup command must be sourced!"
  exit
fi

usage()
{
  echo "Usage:"
  echo ""
  echo "   $0 PACKAGEPATH"
  echo ""
  echo ""
  return
}

# Parse arguments
if [ -z $1 ]; then usage; return; fi
PACKAGEPATH=$('cd' $(dirname $1); pwd)/$(basename $1)

# Check that the analysis code exists
if [ ! -d "${PACKAGEPATH}" ]; then
  echo "Error!"
  echo "Provided path ${PACKAGEPATH} does not exist!"
  return
fi

# Verbose
date

# Set the variables
export PACKAGENAME=$(basename $PACKAGEPATH)
export BINARYNAME=ditto_ana_${PACKAGENAME}
export PACKAGEPATH=${PACKAGEPATH}
export PATH=$DIR:$PATH
export DITTOPATH=$DIR/../

$DIR/ditto_setup_check