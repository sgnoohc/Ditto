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
#include <vector>

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
        string title, int numbinsx, float xmin, float xmax, string prefix="");
    bool plot1D(
        string name, float xval, double weight, Hist_DB &allhistos,
        string title, int numbinsx, const float* xbins, string prefix="");
    void plot1D(
        string name, float xval, double weight, Hist_DB &allhistos, string prefix="");
    bool plot2D(
        string name, float xval, float yval, double weight, Hist_DB &allhistos,
        string title, int numbinsx, float xmin, float xmax, int numbinsy, float ymin, float ymax, string prefix="");
    bool plot2D(
        string name, float xval, float yval, double weight, Hist_DB &allhistos,
        string title, int numbinsx, const float* xbins, int numbinsy, const float* ybins, string prefix="");
    void plot2D(
        string name, float xval, float yval, double weight, Hist_DB &allhistos, string prefix="");
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
      int   charge;
      int   pdgId;
      float dxy;
      float dz;
      int   tightId;
      int   heepId;
      float relIso03;
      float relIso04;
      float miniRelIso;
      float relIsoAn04;
      int   mcMatchId;
      int   lostHits;
      int   convVeto;
      int   tightCharge;
      float mva;
      float ptRatio;
      float ptRel;
      int   tightIdNoIso;
      float sip3d;
      TLorentzVector p4;
    };
    typedef std::vector<Lepton> Leptons;

    struct Jet
    {

      float btagCSV;
      float rawPt;
      float mcPt;
      int   mcFlavour;
      int   hadronFlavour;
      float qgl;
      float area;
      int   id;
      int   puId;
      TLorentzVector p4;
    };
    typedef std::vector<Jet> Jets;

    struct MET
    {
      TLorentzVector p4;
    };
    /// I don't expect to use the above very often.
    /// I only plan to use this when there are multiple flavors of MET
    typedef std::vector<MET> METs;

    struct Truth
    {
      int pdgId;
      int status;
      TLorentzVector p4;
    };
    typedef std::vector<Truth> Truths;
  }

  namespace Analyses
  {

    struct AnalysisData {
      ObjUtil::Leptons leptons;
      ObjUtil::Jets jets;
      ObjUtil::Jets bjets;
      ObjUtil::MET met;
      ObjUtil::Truths truths;
      PlotUtil::Hist_DB hist_db;
      double wgt;
    };

    /// SM physics
    void SM_WWW_3l0SFOS(AnalysisData& ana_db);
    void SM_WWW_3l1SFOS(AnalysisData& ana_db);
    void SM_WWW_3l2SFOS(AnalysisData& ana_db);
    void SM_WWW_SSee(AnalysisData& ana_db);
    void SM_WWW_SSem(AnalysisData& ana_db);
    void SM_WWW_SSmm(AnalysisData& ana_db);
    void SM_Triboson_4l(AnalysisData& ana_db);
    void SM_Triboson_5l(AnalysisData& ana_db);

    /// SUSY physics
    void SUSY_VBF_Soft1l(AnalysisData& ana_db);
    void SUSY_VBF_MG5_Validation(AnalysisData& ana_db);

  }

  namespace VarUtil
  {

    /// calculator with some additional arguments
    float MjjCloseToX(Analyses::AnalysisData& a, float X);
    float MTNthLep(Analyses::AnalysisData& a, int lep_idx);
    /// calculator with just analysis data
    float MjjWmass(Analyses::AnalysisData& a);
    float Mjj(Analyses::AnalysisData& a);
    float Ptjj(Analyses::AnalysisData& a);
    float Mbb(Analyses::AnalysisData& a);
    float Ptbb(Analyses::AnalysisData& a);
    float DEtajj(Analyses::AnalysisData& a);
    float DEtabb(Analyses::AnalysisData& a);
    float Mll(Analyses::AnalysisData& a);
    float DPhill(Analyses::AnalysisData& a);
    float DPhiLepMET(Analyses::AnalysisData& a);
    float MT(Analyses::AnalysisData& a);

  }

  namespace HistUtil
  {

    void fillHistograms(const char* prefix, Analyses::AnalysisData& ana_db);
    /// Multiplicity variables
    void fillNLep      (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillNJet      (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillNBjet     (const char* prefix, Analyses::AnalysisData& ana_db);
    /// Single object kinematics
    void fillMET       (const char* prefix , Analyses::AnalysisData& a);
    void fillLepPt     (const char* prefix , Analyses::AnalysisData& a);
    void fillJetPt     (const char* prefix , Analyses::AnalysisData& a);
    void fillLepEta    (const char* prefix , Analyses::AnalysisData& a);
    void fillJetEta    (const char* prefix , Analyses::AnalysisData& a);
    void fillLepPhi    (const char* prefix , Analyses::AnalysisData& a);
    void fillJetPhi    (const char* prefix , Analyses::AnalysisData& a);
    /// Di object kinematics (GeV scales)
    void fillMll       (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillVBFMjj    (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillVBFMbb    (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillPtjj      (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillPtbb      (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillMjj       (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillMjjW      (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillMT        (const char* prefix, Analyses::AnalysisData& ana_db);
    /// Di object kinematics (angular)
    void fillDPhill    (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillDEtajj    (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillDEtabb    (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillDPhiLepMET(const char* prefix, Analyses::AnalysisData& ana_db);
    /// Single object ID-related
    void fillLepDz      (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillLepDxy     (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillLepSip3d   (const char* prefix, Analyses::AnalysisData& ana_db);
    void fillLepRelIso03(const char* prefix, Analyses::AnalysisData& ana_db);
    void fillLepAbsIso03(const char* prefix, Analyses::AnalysisData& ana_db);
    void fillLepID      (const char* prefix, Analyses::AnalysisData& ana_db);

  }

}

// comparators
template <class T>
bool comparator_pdgId(T p0, T p1) { return p0.pdgId > p1.pdgId; }
template <class T>
bool comparator_pt(T p0, T p1) { return p0.p4.Pt() > p1.p4.Pt(); }


#endif
//eof
