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
#include <map>
#include <string>
#include <utility>
#include <cstdlib> // exit
#include <time.h>  // rand seed
#include <unistd.h> // sleep
#include <iostream>
#include <vector>
#include <stdlib.h> // rand

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
    extern bool isdata;
    extern bool isfastsim;
    extern bool doskim;
    extern bool doprintprogressbar;
    extern TString output_name;

    void loadFileIter();
    void loadTotalNEvents();
    void loadCurrentTTreeWithName(const char* treename);
    TFile* getCurrentTFile();
    TTree* getCurrentTTree();
    TChain* getCurrentTChain();
    TString getCurrentTFileName();
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
    void setDoSkim(bool b=true);

  }

  namespace ObjUtil
  {

    struct Particle
    {
      TLorentzVector p4;
      TLorentzVector p4CorrUp;
      TLorentzVector p4CorrDn;
      Particle()
      {
        p4.SetXYZT(0, 0, 0, 0);
        p4CorrUp.SetXYZT(0, 0, 0, 0);
        p4CorrDn.SetXYZT(0, 0, 0, 0);
      }
    };

    struct Lepton : Particle
    {
      // General
      float dxy;
      float dz;
      float ip3d;
      float sip3d;
      int   tightcharge;
      int   charge;
      int   pdgId;
      int   id;
      // Isolation related
      float ptRatio;
      float ptRel;
      float relIso03;
      float relIso03DB;
      float relIso03EA;
      float relIso03EAv2;
      float relIso04;
      float relIso04EA;
      float relIso04EAv2;
      float relIso04DB;
      float miniRelIsoCMS3_EA;
      float miniRelIsoCMS3_EAv2;
      float miniRelIsoCMS3_DB;
      float relIso005EAstudy;
      float relIso010EAstudy;
      float relIso015EAstudy;
      float relIso020EAstudy;
      float relIso025EAstudy;
      float relIso030EAstudy;
      float relIso035EAstudy;
      float relIso040EAstudy;
      float relIso045EAstudy;
      float relIso050EAstudy;
      float relIso005EAstudyv2;
      float relIso010EAstudyv2;
      float relIso015EAstudyv2;
      float relIso020EAstudyv2;
      float relIso025EAstudyv2;
      float relIso030EAstudyv2;
      float relIso035EAstudyv2;
      float relIso040EAstudyv2;
      float relIso045EAstudyv2;
      float relIso050EAstudyv2;
      // Muon specifics
      float muPOverP;
      int   muPidPFMuon;
      int   muType;
      float muChi2OverNDof;
      float muChi2LocalPosition;
      float muTrkKink;
      //float muValidHitFraction;
      double muValidHitFraction;
      float muSegmCompatibility;
      int   muGFitValidSTAHits;
      int   muNMatchedStations;
      int   muValidPixelHits;
      int   muNLayers;
      // Electron specifics
      float elEtaSC;
      float elSigmaIEtaIEta_full5x5;
      float elHOverE;
      float elMvaRaw;
      float elMva;
      float elDEtaIn;
      float elDPhiIn;
      float elEpRatio;
      int   elConvVeto;
      int   elNmiss;
      int   isFromX;

      Lepton() : Particle()
      {
        // General
        dxy = -999;
        dz = -999;
        ip3d = -999;
        sip3d = -999;
        tightcharge = -999;
        charge = -999;
        pdgId = -999;
        id = -999;
        // Isolation related
        ptRatio = -999;
        ptRel = -999;
        relIso03 = -999;
        relIso03DB = -999;
        relIso03EA = -999;
        relIso03EAv2 = -999;
        relIso04 = -999;
        relIso04DB = -999;
        relIso04EA = -999;
        relIso04EAv2 = -999;
        miniRelIsoCMS3_EA = -999;
        miniRelIsoCMS3_EAv2 = -999;
        miniRelIsoCMS3_DB = -999;
        relIso005EAstudy = -999;
        relIso010EAstudy = -999;
        relIso015EAstudy = -999;
        relIso020EAstudy = -999;
        relIso025EAstudy = -999;
        relIso030EAstudy = -999;
        relIso035EAstudy = -999;
        relIso040EAstudy = -999;
        relIso045EAstudy = -999;
        relIso050EAstudy = -999;
        relIso005EAstudyv2 = -999;
        relIso010EAstudyv2 = -999;
        relIso015EAstudyv2 = -999;
        relIso020EAstudyv2 = -999;
        relIso025EAstudyv2 = -999;
        relIso030EAstudyv2 = -999;
        relIso035EAstudyv2 = -999;
        relIso040EAstudyv2 = -999;
        relIso045EAstudyv2 = -999;
        relIso050EAstudyv2 = -999;
        // Muon specifics
        muPOverP = -999;
        muPidPFMuon = -999;
        muType = -999;
        muChi2OverNDof = -999;
        muChi2LocalPosition = -999;
        muTrkKink = -999;
        //float muValidHitFraction;
        muValidHitFraction = -999;
        muSegmCompatibility = -999;
        muGFitValidSTAHits = -999;
        muNMatchedStations = -999;
        muValidPixelHits = -999;
        muNLayers = -999;
        // Electron specifics
        elEtaSC = -999;
        elSigmaIEtaIEta_full5x5 = -999;
        elHOverE = -999;
        elMvaRaw = -999;
        elMva = -999;
        elDEtaIn = -999;
        elDPhiIn = -999;
        elEpRatio = -999;
        elConvVeto = -999;
        elNmiss = -999;
        isFromX = -999;
      }

      void print() {
        std::cout << "Lepton::print()  dxy = " << dxy << std::endl;;
        std::cout << "Lepton::print()  dz = " << dz << std::endl;;
        std::cout << "Lepton::print()  ip3d = " << ip3d << std::endl;;
        std::cout << "Lepton::print()  sip3d = " << sip3d << std::endl;;
        std::cout << "Lepton::print()  tightcharge = " << tightcharge << std::endl;;
        std::cout << "Lepton::print()  charge = " << charge << std::endl;;
        std::cout << "Lepton::print()  pdgId = " << pdgId << std::endl;;
        std::cout << "Lepton::print()  id = " << id << std::endl;;
        // Isolation related
        std::cout << "Lepton::print()  ptRatio = " << ptRatio << std::endl;;
        std::cout << "Lepton::print()  ptRel = " << ptRel << std::endl;;
        std::cout << "Lepton::print()  relIso03 = " << relIso03 << std::endl;;
        std::cout << "Lepton::print()  relIso03DB = " << relIso03DB << std::endl;;
        std::cout << "Lepton::print()  relIso03EA = " << relIso03EA << std::endl;;
        std::cout << "Lepton::print()  miniRelIsoCMS3_EA = " << miniRelIsoCMS3_EA << std::endl;;
        std::cout << "Lepton::print()  miniRelIsoCMS3_DB = " << miniRelIsoCMS3_DB << std::endl;;
        // Muon specifics
        std::cout << "Lepton::print()  muPOverP = " << muPOverP << std::endl;;
        std::cout << "Lepton::print()  muPidPFMuon = " << muPidPFMuon << std::endl;;
        std::cout << "Lepton::print()  muType = " << muType << std::endl;;
        std::cout << "Lepton::print()  muChi2OverNDof = " << muChi2OverNDof << std::endl;;
        std::cout << "Lepton::print()  muChi2LocalPosition = " << muChi2LocalPosition << std::endl;;
        std::cout << "Lepton::print()  muTrkKink = " << muTrkKink << std::endl;;
        std::cout << "Lepton::print()  muValidHitFraction = " << muValidHitFraction << std::endl;;
        std::cout << "Lepton::print()  muSegmCompatibility = " << muSegmCompatibility << std::endl;;
        std::cout << "Lepton::print()  muGFitValidSTAHits = " << muGFitValidSTAHits << std::endl;;
        std::cout << "Lepton::print()  muNMatchedStations = " << muNMatchedStations << std::endl;;
        std::cout << "Lepton::print()  muValidPixelHits = " << muValidPixelHits << std::endl;;
        std::cout << "Lepton::print()  muNLayers = " << muNLayers << std::endl;;
        // Electron specifics
        std::cout << "Lepton::print()  elEtaSC = " << elEtaSC << std::endl;;
        std::cout << "Lepton::print()  elSigmaIEtaIEta_full5x5 = " << elSigmaIEtaIEta_full5x5 << std::endl;;
        std::cout << "Lepton::print()  elHOverE = " << elHOverE << std::endl;;
        std::cout << "Lepton::print()  elMvaRaw = " << elMvaRaw << std::endl;;
        std::cout << "Lepton::print()  elMva = " << elMva << std::endl;;
        std::cout << "Lepton::print()  elDEtaIn = " << elDEtaIn << std::endl;;
        std::cout << "Lepton::print()  elDPhiIn = " << elDPhiIn << std::endl;;
        std::cout << "Lepton::print()  elEpRatio = " << elEpRatio << std::endl;;
        std::cout << "Lepton::print()  elConvVeto = " << elConvVeto << std::endl;;
        std::cout << "Lepton::print()  elNmiss = " << elNmiss << std::endl;;
      }

    };

    typedef std::vector<Lepton> Leptons;

    struct Jet : Particle
    {
      float btagCSV;
      float rawPt;
      float mcPt;
      int   mcFlavour;
      int   hadronFlavour;
      float area;
      float undoJEC;
      float jecCorr;
      float jecCorrUp;
      float jecCorrDn;
      float chf;
      float nhf;
      float cef;
      float nef;
      float muf;
      float cm;
      float nm;
      float puValue;
      float mcdr;
      int   npfcand;
      int   id;
      int   puId;
      int   puIdpuppi;
      int   FSveto;

      Jet() : Particle()
      {
        btagCSV = -999;
        rawPt = -999;
        mcPt = -999;
        mcFlavour = -999;
        hadronFlavour = -999;
        area = -999;
        undoJEC = -999;
        jecCorr = -999;
        jecCorrUp = -999;
        jecCorrDn = -999;
        chf = -999;
        nhf = -999;
        cef = -999;
        nef = -999;
        muf = -999;
        cm = -999;
        nm = -999;
        puValue = -999;
        mcdr = -999;
        npfcand = -999;
        id = -999;
        puId = -999;
        puIdpuppi = -999;
        FSveto = -999;
      }

    };

    typedef std::vector<Jet> Jets;

    struct MET : Particle
    {
      MET() : Particle() { }
    };

    /// I don't expect to use the above very often.
    /// I only plan to use this when there are multiple flavors of MET
    typedef std::vector<MET> METs;

    struct Truth : Particle
    {
      int pdgId;
      int status;
      int motherId;
      int grandmotherId;

      Truth() : Particle()
      {
        pdgId = -999;
        status = -999;
        motherId = -999;
        grandmotherId = -999;
      }
    };

    typedef std::vector<Truth> Truths;

    struct EventInfo
    {
      int run;
      int lumi;
      int event;
      int nEvts;
      float scale1fb;
      float pileup;
      int nvtx;

      EventInfo()
      {
        run = -999;
        lumi = -999;
        event = -999;
        nEvts = -999;
        scale1fb = -999;
      }

    };

    typedef std::map<TString, Leptons> LeptonsCollection;
    typedef std::map<TString, Jets> JetsCollection;

    struct AnalysisData {
      LeptonsCollection lepcol;
      JetsCollection jetcol;
      Leptons leptons;
      Jets jets;
      Jets bjets;
      MET met;
      Truths truths;
      EventInfo eventinfo;
      PlotUtil::Hist_DB hist_db;
      double wgt;
    };

    extern AnalysisData* ana_data;

    /// this_a
    void setAnalysisData(AnalysisData& a);

  }

  namespace Analyses
  {

    template <class T>
    void selectObjs(std::vector<T>& objs, std::function<bool (T&)> isgoodobj)
    {
      std::vector<T> goodobjs;
      for (auto& obj: objs) if (isgoodobj(obj)) goodobjs.push_back(obj);
      objs = std::vector<T>(goodobjs);
    }

    /// Electrons
    bool isElectronPOGMVAIDCut(ObjUtil::Lepton& lepton,
                               float barrel_highpt_mvacut    , float barrel_lowpt_mvacut    , float barrel_lowerpt_mvacut    ,
                               float transition_highpt_mvacut, float transition_lowpt_mvacut, float transition_lowerpt_mvacut,
                               float endcap_highpt_mvacut    , float endcap_lowpt_mvacut    , float endcap_lowerpt_mvacut);
    bool isElectronPOGCutBasedIDCut(ObjUtil::Lepton& lepton,
                                    float barrel_elSigmaIEtaIEta_full5x5_cut , float barrel_abs_elDEtaIn_cut , float barrel_abs_elDPhiIn_cut ,
                                    float barrel_elHOverE_cut                , float barrel_relIso03EA_cut   , float barrel_elEpRatio_cut    , int barrel_elNmiss_cut ,
                                    float endcap_elSigmaIEtaIEta_full5x5_cut , float endcap_abs_elDEtaIn_cut , float endcap_abs_elDPhiIn_cut ,
                                    float endcap_elHOverE_cut                , float endcap_relIso03EA_cut   , float endcap_elEpRatio_cut    , int endcap_elNmiss_cut);
    bool isTriggerSafenoIso_v1(ObjUtil::Lepton& lepton);
    bool isMediumElectronPOGCutbased(ObjUtil::Lepton& lepton);

    /// Muons
    bool isLooseMuonPOG(ObjUtil::Lepton& lepton);
    bool isMediumMuonPOG(ObjUtil::Lepton& lepton);

    /// Jets
    bool isLoosePFJet_Summer16_v1(ObjUtil::Jet& jet);

    /// B-tagging
    bool isMediumBJet(ObjUtil::Jet& jet);
    bool isLooseBJet(ObjUtil::Jet& jet);

    /// Overlap Removal
    int removeJetsOverlappingLeptons(ObjUtil::Jets& jets, ObjUtil::Leptons& leptons);

  }

  #include "DittoVarUtil.h"

  namespace HistUtil
  {

    string catPrefix(string prefix1, string prefix2);
    void fillCutflow(string prefix, ObjUtil::AnalysisData& a, int& ibin);
    void fillCounter(string prefix, ObjUtil::AnalysisData& a, int ibin);
    void fillMET(string prefix, ObjUtil::AnalysisData& a);
    void fillLepMTs(string prefix, ObjUtil::AnalysisData& a);
    void fillLepSumPt(string prefix, ObjUtil::AnalysisData& a);
    void fillLepRelIso03EA(string prefix, ObjUtil::AnalysisData& a);
    void fillLepAbsIso03EA(string prefix, ObjUtil::AnalysisData& a);
    void fillLepTightCharge(string prefix, ObjUtil::AnalysisData& a);

  }

  namespace TreeUtil
  {

    typedef std::map<TString, int> mapInt;
    typedef std::map<TString, float> mapFloat;
    typedef std::map<TString, std::vector<float>*> mapVFloat;
    typedef std::map<TString, std::vector<int>*> mapVInt;

    struct TreeData
    {
      mapInt mapint;
      mapFloat mapfloat;
      mapVFloat mapvfloat;
      mapVInt mapvint;
    };

    extern TreeData treedata;
    extern TFile* skimfile;
    extern TTree* skimtree;

    void initTreeData();

    void createIntBranch(TTree* tree, TString name);
    void createFloatBranch(TTree* tree, TString name);
    void createVIntBranch(TTree* tree, TString name);
    void createVFloatBranch(TTree* tree, TString name);

    void setIntBranch(TString name, int val);
    void setFloatBranch(TString name, float val);
    void pushbackVIntBranch(TString name, int val);
    void pushbackVFloatBranch(TString name, float val);

    void create4VecBranch(TTree* tree, TString name);
    void createTruthBranch(TTree* tree, TString name);
    void createLeptonBranch(TTree* tree, TString name);
    void createJetBranch(TTree* tree, TString name);
    void createMETBranch(TTree* tree, TString name);
    void createEventInfoBranch(TTree* tree, TString name);

    void setTruths(ObjUtil::AnalysisData& ana_data, TString name);
    void setLeptons(ObjUtil::AnalysisData& ana_data, TString name);
    void setJets(ObjUtil::AnalysisData& ana_data, TString name);
    void setMET(ObjUtil::AnalysisData& ana_data, TString name);
    void setEventInfo(ObjUtil::AnalysisData& ana_data, TString name);
    void pushback4Vec(TLorentzVector p4, TString name);

    void createSkimTree(const char*);
    void fillSkimTree();
    void saveSkimTree();

  }

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
