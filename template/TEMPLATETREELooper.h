// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#ifndef TEMPLATETREENAMELooper_h
#define TEMPLATETREENAMELooper_h

// ROOT
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TObjArray.h>
#include <TString.h>
#include <TTree.h>

// C++
#include <iostream>

// Ditto
#include "Ditto.h"
#include "TEMPLATETREENAME.h"
#include "TEMPLATETREENAMEConnector.h"

using namespace Ditto;

extern TEMPLATETREENAME mytree;
//extern ObjUtil::Leptons leptons;
//extern ObjUtil::Jets jets;
//extern ObjUtil::MET met;

int TEMPLATETREENAMELooper(TChain* chain, TString output_name, int nEvents);
void loop();
void beforeLoop(TChain* chain, TString output_name, int nevents);
void afterLoop();
void initTEMPLATETREENAME();
void loadTEMPLATETREENAMEEvent();
void processTEMPLATETREENAMEEvent();
void setObjects();

#endif
//eof
