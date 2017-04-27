// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#ifndef Ditto_h
#define Ditto_h

// C++
#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <utility>
#include <cstdlib> // exit
#include <time.h>  // rand seed
#include <unistd.h> // sleep
#include <iostream>

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

  namespace PlotUtil
  {
    // Map to hold 1D histograms with unique names
    typedef map<string, TH1*> Hist_DB;

    // Plot Utilities
    bool plot1D(
        string name, float xval, double weight, Hist_DB &allhistos,
        string title, int numbinsx, float xmin, float xmax);
    bool plot1D(
        string name, float xval, double weight, Hist_DB &allhistos,
        string title, int numbinsx, const float* xbins);
    void plot1D(
        string name, float xval, double weight, Hist_DB &allhistos);
    bool plot2D(
        string name, float xval, float yval, double weight, Hist_DB &allhistos,
        string title, int numbinsx, float xmin, float xmax, int numbinsy, float ymin, float ymax);
    bool plot2D(
        string name, float xval, float yval, double weight, Hist_DB &allhistos,
        string title, int numbinsx, const float* xbins, int numbinsy, const float* ybins);
    void plot2D(
        string name, float xval, float yval, double weight, Hist_DB &allhistos);
    void savePlots(Hist_DB&, const char*);
    void savePlots2D(Hist_DB &h_1d, const char* outfilename);
  }

  namespace PrintUtil
  {
    // Print Utilities
    void print   (TString msg="", int flush_before=0, int flush_after=0);
    void error   (TString msg, int is_error=1);
    void warning (TString msg);
    void announce(TString msg="", int quiet=0);
    void start   (int quiet=0, int sleep_time=0);
    void exit    (int quiet=0);
  }

  namespace LoopUtil
  {
    // Loop Utilities
    // Total number of events in the input
    extern unsigned int max_nevents;
    extern unsigned int total_nevents;
    extern unsigned int current_ttree_max_nevents;
    extern unsigned int current_ttree_event_index;
    extern unsigned int total_nevents_processed;
    extern double fraction_of_booked_nevents;
    extern TObjArray* list_of_input_files;
    extern TChain* current_tchain;
    extern TFile* current_tfile;
    extern TTree* current_ttree;
    extern TObjArrayIter* file_iter;
    extern TStopwatch my_timer;
    extern int bar_id;
    extern int print_rate;

    void loadFileIter();
    void loadTotalNEvents();
    void loadCurrentTTreeWithName(const char* treename);
    TFile* getCurrentTFile();
    TTree* getCurrentTTree();
    TChain* getCurrentTChain();
    int getCurrentTTreeEventIndex();
    void setCurrentTTreeMaxNEvents();
    void setFractionOfBookedNEvents();
    bool nextFile();
    bool nextFileAndLoadTTreeWithName(const char* treename);
    void resetLoopCondition(TChain* chain, int nevents = -1);
    void resetCurrentTTreeLoopCondition();
    void resetTotalNEventsProcessed();
    int loadCurrentTTreeEvent();
    void setTotalCurrentTTreeNEvents();
    bool nextEvent();
    bool isAllEventsProcessed();
    void resetCurrentTTreeEventIndex();
    void incrementCurrentTTreeEventIndex();
    void incrementTotalNEventsProcessed();
    void setCurrentTChain(TChain* chain);
    void setCurrentTFile(TFile* file);
    void setCurrentTFileByPath(const char* path);
    void setCurrentTTree(TTree* tree);
    void setMaxNEvents(int nevents);
    void loadListOfFiles();
    void resetPreviousFile();
    void printProgressBar();
    void initProgressBar();
    void loadFractionOfBookedNEvents();
    double getFractionOfBookedNEvents();

  }

  namespace ObjUtil
  {

    struct Lepton
    {
      TLorentzVector p4;
    }
    typedef std::vector<Lepton> Leptons;

    struct Jet
    {
      TLorentzVector p4;
    }
    typedef std::vector<Jet> Jets;

    struct MET
    {
      TLorentzVector p4;
    }
    /// I don't expect to use the above very often.
    /// I only plan to use this when there are multiple flavors of MET
    typedef std::vector<MET> METs;
  }

}


#endif
//eof
