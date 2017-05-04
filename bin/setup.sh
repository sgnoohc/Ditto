#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

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
echo "================================================"
echo "$(basename $0) $*"
echo "------------------------------------------------"
echo "PACKAGEPATH    : ${PACKAGEPATH}"
echo "================================================"

# Set the variables
export PACKAGENAME=$(basename $PACKAGEPATH)
export BINARYNAME=ditto
export PACKAGEPATH=${PACKAGEPATH}
export PATH=$DIR:$PATH;
export DITTOPATH=$DIR/../;
