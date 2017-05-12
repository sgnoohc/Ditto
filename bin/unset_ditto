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


# Set the variables
export PACKAGENAME=""
export BINARYNAME=""
export PACKAGEPATH=""
export PATH=$DIR:$PATH
export DITTOPATH=$DIR/../
