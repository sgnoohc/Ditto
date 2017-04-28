// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#ifndef TREECLASSNAMEConnector_h
#define TREECLASSNAMEConnector_h

#include "Ditto.h"
#include "TREECLASSNAME.h"

using namespace Ditto;

ObjUtil::Leptons getLeptons(TREECLASSNAME& mytree);
ObjUtil::Jets getJets(TREECLASSNAME& mytree);
ObjUtil::METs getMETs(TREECLASSNAME& mytree);
ObjUtil::MET getMET(TREECLASSNAME& mytree);

#endif
//eof
