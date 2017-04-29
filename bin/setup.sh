#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

usage()
{
  echo "Usage:"
  echo ""
  echo "   $0 PACKAGENAME BINARYNAME"
  echo ""
  echo ""
  return
}

# Parse arguments
if [ -z $1 ]; then usage; return; fi
if [ -z $2 ]; then usage; return; fi
PACKAGENAME=$1
BINARYNAME=$2
PACKAGEPATH=$DIR/../../${PACKAGENAME}

# Check that the analysis code exists
if [ ! -d "${PACKAGEPATH}" ]; then
  echo "Error!"
  echo "Provided path ${PACKAGEPATH} does not exist!"
  return
fi

# Verbose
date
echo "================================================"
echo "$(basename $0) $*"
echo "------------------------------------------------"
echo "PACKAGENAME    : ${PACKAGENAME}"
echo "BINARYNAME     : ${BINARYNAME}"
echo "PACKAGEPATH    : ${DIR}/../../${PACKAGENAME}"
echo "================================================"

# Set the variables
export PACKAGENAME=${PACKAGENAME}
export BINARYNAME=${BINARYNAME}
export PACKAGEPATH=${PACKAGEPATH}
export PATH=$DIR:$PATH;
export DITTOPATH=$DIR/../;
