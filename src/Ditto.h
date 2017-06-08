// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#ifndef Ditto_h
#define Ditto_h

// C++
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <functional>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <cstdlib> // exit
#include <time.h>  // rand seed
#include <unistd.h> // sleep
#include <iostream>
#include <vector>
#include <stdlib.h> // rand
#include <sstream>

// ROOT
#include <TCanvas.h>
#include <TChain.h>
#include <TFile.h>
#include <TGraph.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TSystem.h>
#include <TTree.h>
#include <TStopwatch.h>

// For simplicity use namespace. (I generally avoid this.)
using namespace std;

namespace Ditto
{

#include "DittoPlotUtil.h"
#include "DittoPrintUtil.h"
#include "DittoLoopUtil.h"
#include "DittoObjUtil.h"
#include "DittoVarUtil.h"
#include "DittoAnalyses.h"
#include "DittoCombUtil.h"
#include "DittoTreeUtil.h"

}

// comparators
template <class T>
bool comparator_abspdgId(T p0, T p1) { return abs(p0.pdgId) > abs(p1.pdgId); }
template <class T>
bool comparator_pdgId(T p0, T p1) { return p0.pdgId > p1.pdgId; }
template <class T>
bool comparator_pt(T p0, T p1) { return p0.p4.Pt() > p1.p4.Pt(); }

#endif
//eof
