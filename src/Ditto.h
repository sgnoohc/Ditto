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

  }

  namespace ObjUtil
  {

    struct Particle
    {
      TLorentzVector p4;
      TLorentzVector p4CorrUp;
      TLorentzVector p4CorrDn;
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
      float relIso04EA;
      float relIso04DB;
      float miniRelIsoCMS3_EA;
      float miniRelIsoCMS3_DB;
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
      float elMva;
      float elDEtaIn;
      float elDPhiIn;
      float elEpRatio;
      int   elConvVeto;
      int   elNmiss;
      int   isFromX;
      //float relIsoAn04;
      //int   mcMatchId;
      //int   lostHits;
      //int   tightCharge;
      //int   tightIdNoIso;
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
    };
    typedef std::vector<Jet> Jets;

    struct MET : Particle
    {
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
    };
    typedef std::vector<Truth> Truths;

    struct EventInfo
    {
      int run;
      int lumi;
      int event;
      float scale1fb;
    };

  }

  namespace Analyses
  {

    struct AnalysisData {
      ObjUtil::Leptons leptons;
      ObjUtil::Leptons vetoleptons;
      ObjUtil::Jets jets;
      ObjUtil::Jets bjets;
      ObjUtil::MET met;
      //ObjUtil::METs mets;
      ObjUtil::Truths truths;
      ObjUtil::EventInfo eventinfo;
      PlotUtil::Hist_DB hist_db;
      double wgt;
    };

    template <class T>
    void selectObjs(std::vector<T>& objs, std::function<bool (T&)> isgoodobj);

    extern AnalysisData* this_a;
    extern bool do_object_cutflow;

    /// this_a
    void setAnalysisData(AnalysisData& a);

    void doObjectCutflow();

    /// Lepton ID study
    bool PID_Isolation();

    /// SM physics
    bool SM_WWW_3l0SFOS(AnalysisData& a);
    void SM_WWW_3l1SFOS(AnalysisData& a);
    void SM_WWW_3l2SFOS(AnalysisData& a);
    void SM_WWW_SSee(AnalysisData& a);
    void SM_WWW_SSem(AnalysisData& a);
    bool SM_WWW_SSmm(AnalysisData& a);
    void SM_Triboson_4l(AnalysisData& a);
    void SM_Triboson_5l(AnalysisData& a);
    void SM_VBS_WH(AnalysisData& a);
    bool SM_VBS_WW_lvjj(AnalysisData& a);


    /// SUSY physics
    void SUSY_ISR_Soft2l_SUS_16_048(AnalysisData& a);
    void SUSY_VBF_Soft1l(AnalysisData& a);
    void SUSY_VBF_MG5_Validation(AnalysisData& a);

    /// Object selections
    void selectObjects_SUSY_ISR_Soft2l_SUS_16_048(AnalysisData& a);
    void selectObjects_SM_WWW_SS(AnalysisData& a);
    void selectObjects_SM_VBS_WW_lvjj(AnalysisData& a);
    void selectObjects_PID_Isolation(AnalysisData& a);

    /// Single object selections
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
    /// Muons
    bool isLooseMuonPOG(ObjUtil::Lepton& lepton);
    bool isMediumMuonPOG(ObjUtil::Lepton& lepton);
    /// Jets
    bool isLoosePFJet_Summer16_v1(ObjUtil::Jet& jet);
    /// BJets
    bool isGoodMediumBJet(ObjUtil::Jet& jet);
    bool isGoodLooseBJet(ObjUtil::Jet& jet);

    /// Analysis specifics
    /// SUSY_ISR_Soft2l_SUS_16_048
    bool isGoodLepton_SUSY_ISR_Soft2l_SUS_16_048(ObjUtil::Lepton& lepton);
    bool isGoodJet_SUSY_ISR_Soft2l_SUS_16_048(ObjUtil::Jet& jet);
    bool isGoodBJet_SUSY_ISR_Soft2l_SUS_16_048(ObjUtil::Jet& jet);

    /// SM_WWW_SS
    bool isGoodLepton_SM_WWW_SS(ObjUtil::Lepton& lepton);
    bool isGoodElectron_SM_WWW_SS(ObjUtil::Lepton& lepton);
    bool isGoodMuon_SM_WWW_SS(ObjUtil::Lepton& lepton);
    bool isGoodJet_SM_WWW_SS(ObjUtil::Jet& jet);
    bool isGoodBJet_SM_WWW_SS(ObjUtil::Jet& jet);
    bool isIsoElectron_SM_WWW_SS(ObjUtil::Lepton& lepton);
    bool isIsoMuon_SM_WWW_SS(ObjUtil::Lepton& lepton);
    bool isVetoLepton_SM_WWW_SS(ObjUtil::Lepton& lepton);
    bool isVetoElectron_SM_WWW_SS(ObjUtil::Lepton& lepton);
    bool isVetoMuon_SM_WWW_SS(ObjUtil::Lepton& lepton);

    /// SM_VBS_WW_lvjj
    bool isGoodLepton_SM_VBS_WW_lvjj(ObjUtil::Lepton& lepton);
    bool isGoodElectron_SM_VBS_WW_lvjj(ObjUtil::Lepton& lepton);
    bool isGoodMuon_SM_VBS_WW_lvjj(ObjUtil::Lepton& lepton);
    bool isGoodJet_SM_VBS_WW_lvjj(ObjUtil::Jet& jet);
    bool isGoodBJet_SM_VBS_WW_lvjj(ObjUtil::Jet& jet);

    /// PID_Isolation study
    bool isGoodMuon_PID_Isolation(ObjUtil::Lepton& lepton);
//	    bool isFakeMuon_PID_Isolation(ObjUtil::Lepton& lepton);

    /// Overlap Removal
    void overlapRemoval(AnalysisData& a);

  }

  namespace CombUtil
  {
  }

  namespace VarUtil
  {

    /// calculator with tlorentzvector
    float DEta(TLorentzVector, TLorentzVector);
    float DPhi(TLorentzVector, TLorentzVector);
    float DR  (TLorentzVector, TLorentzVector);
    float DPt (TLorentzVector, TLorentzVector);
    float Mass(TLorentzVector, TLorentzVector);
    float Pt  (TLorentzVector, TLorentzVector);
    float MT  (TLorentzVector, TLorentzVector); // defined below

    /// calculator with objects
    float DEta(ObjUtil::Particle, ObjUtil::Particle);
    float DPhi(ObjUtil::Particle, ObjUtil::Particle);
    float DR  (ObjUtil::Particle, ObjUtil::Particle);
    float DPt (ObjUtil::Particle, ObjUtil::Particle);
    float Mass(ObjUtil::Particle, ObjUtil::Particle);
    float Pt  (ObjUtil::Particle, ObjUtil::Particle);
    float MT  (ObjUtil::Particle, ObjUtil::Particle);

    /// calculator with tlorentzvector
    float DEta(TLorentzVector, ObjUtil::Particle);
    float DPhi(TLorentzVector, ObjUtil::Particle);
    float DR  (TLorentzVector, ObjUtil::Particle);
    float DPt (TLorentzVector, ObjUtil::Particle);
    float Mass(TLorentzVector, ObjUtil::Particle);
    float Pt  (TLorentzVector, ObjUtil::Particle);
    float MT  (TLorentzVector, ObjUtil::Particle);

    /// calculator with tlorentzvector
    float DEta(ObjUtil::Particle, TLorentzVector);
    float DPhi(ObjUtil::Particle, TLorentzVector);
    float DR  (ObjUtil::Particle, TLorentzVector);
    float DPt (ObjUtil::Particle, TLorentzVector);
    float Mass(ObjUtil::Particle, TLorentzVector);
    float Pt  (ObjUtil::Particle, TLorentzVector);
    float MT  (ObjUtil::Particle, TLorentzVector);

    /// calculator with some additional arguments
    float MjjCloseToX(Analyses::AnalysisData& a, float X);
    float MTNthLep(Analyses::AnalysisData& a, int lep_idx);
    /// calculator with just analysis data
    float HT(Analyses::AnalysisData& a);
    float METHTRatio(Analyses::AnalysisData& a);
    float DRjjWmass(Analyses::AnalysisData& a);
    float MjjWmass(Analyses::AnalysisData& a);
    float DRjj(Analyses::AnalysisData& a);
    float Mjj(Analyses::AnalysisData& a);
    float MljClosest(Analyses::AnalysisData& a);
    float Ptjj(Analyses::AnalysisData& a);
    float Mbb(Analyses::AnalysisData& a);
    float Ptbb(Analyses::AnalysisData& a);
    float DEtajj(Analyses::AnalysisData& a);
    float DEtabb(Analyses::AnalysisData& a);
    float Ptll(Analyses::AnalysisData& a);
    float Mll(Analyses::AnalysisData& a);
    float DPhill(Analyses::AnalysisData& a);
    float DPhiLepMET(Analyses::AnalysisData& a);
    float MT(Analyses::AnalysisData& a);
    float MTll(Analyses::AnalysisData& a);
    float Mtt(Analyses::AnalysisData& a);
    float Mlvjj(Analyses::AnalysisData& a, int lepidx = 0, int jetidx0 = 0, int jetidx1 = 1);
    float NeutrinoSolver(Analyses::AnalysisData& a, int lepidx = 0);
    bool isOSEEChannel(Analyses::AnalysisData& a);
    bool isOSMMChannel(Analyses::AnalysisData& a);
    bool isOSEMChannel(Analyses::AnalysisData& a);

    /// Math stuff
    double Rndm();
    std::vector<std::vector<int> > comb(int N, int K);

    // templated function needs to sit inside header
    template<class I, class O>
    std::vector<O> twoBodyDecay(I parent)
    {

      //
      // Below code is adopted from : http://www1.gantep.edu.tr/~bingul/simulation/twoBody/twoBody.cpp.html
      //

      double m = parent.p4.M();

      /// Setting to massless daughters
      double m1 = 0; ///double m1 = prod1.m;
      double m2 = 0; ///double m2 = prod2.m;

      /// CM energies and momentum
      double e1 = (m*m + m1*m1 - m2*m2) / (2.0*m);
      double e2 = (m*m - m1*m1 + m2*m2) / (2.0*m);
      double P  = sqrt(e1*e1 - m1*m1);

      /// Isotropic random angles
      double theta = acos( 2.0*Rndm() - 1.0 );
      double phi   = 2.0*M_PI *Rndm();

      /// Compute p4 componenets
      double pX = P*sin(theta)*cos(phi);
      double pY = P*sin(theta)*sin(phi);
      double pZ = P*cos(theta);

      /// Now we have the isotropic decay of daughters
      O prod1;
      O prod2;
      prod1.p4.SetPxPyPzE( pX,  pY,  pZ, e1);
      prod2.p4.SetPxPyPzE(-pX, -pY, -pZ, e2);

      /// Parent boost vector
      TVector3 b = parent.p4.BoostVector();

      /// Boost the products
      prod1.p4.Boost(b);
      prod2.p4.Boost(b);

      /// Return the result
      std::vector<O> objs;
      objs.push_back(prod1);
      objs.push_back(prod2);
      return objs;

    }

  }

  namespace HistUtil
  {

    string catPrefix(string prefix1, string prefix2);

    void fillStdHistograms(string prefix, Analyses::AnalysisData& a);
    void fillLeptonIDHistograms(string prefix, Analyses::AnalysisData& a);
    /// Multiplicity variables
    void fillNLep      (string prefix, Analyses::AnalysisData& a);
    void fillNJet      (string prefix, Analyses::AnalysisData& a);
    void fillNBjet     (string prefix, Analyses::AnalysisData& a);
    /// Single object kinematics
    void fillMET       (string prefix , Analyses::AnalysisData& a);
    void fillLepPt     (string prefix , Analyses::AnalysisData& a);
    void fillJetPt     (string prefix , Analyses::AnalysisData& a);
    void fillBJetPt    (string prefix , Analyses::AnalysisData& a);
    void fillLepEta    (string prefix , Analyses::AnalysisData& a);
    void fillJetEta    (string prefix , Analyses::AnalysisData& a);
    void fillBJetEta   (string prefix , Analyses::AnalysisData& a);
    void fillLepPhi    (string prefix , Analyses::AnalysisData& a);
    void fillJetPhi    (string prefix , Analyses::AnalysisData& a);
    void fillBJetPhi   (string prefix , Analyses::AnalysisData& a);
    /// Di object kinematics (GeV scales)
    void fillMll       (string prefix, Analyses::AnalysisData& a);
    void fillVBFMjj    (string prefix, Analyses::AnalysisData& a);
    void fillVBFMbb    (string prefix, Analyses::AnalysisData& a);
    void fillPtjj      (string prefix, Analyses::AnalysisData& a);
    void fillPtbb      (string prefix, Analyses::AnalysisData& a);
    void fillMjj       (string prefix, Analyses::AnalysisData& a);
    void fillMjjW      (string prefix, Analyses::AnalysisData& a);
    void fillMT        (string prefix, Analyses::AnalysisData& a);
    void fillHT        (string prefix, Analyses::AnalysisData& a);
    void fillMTll      (string prefix, Analyses::AnalysisData& a);
    void fillMljClose  (string prefix, Analyses::AnalysisData& a);
    /// Di object kinematics (angular)
    void fillDPhill    (string prefix, Analyses::AnalysisData& a);
    void fillDEtajj    (string prefix, Analyses::AnalysisData& a);
    void fillDRjj      (string prefix, Analyses::AnalysisData& a);
    void fillDEtabb    (string prefix, Analyses::AnalysisData& a);
    void fillDPhiLepMET(string prefix, Analyses::AnalysisData& a);
    void fillDRjjW     (string prefix, Analyses::AnalysisData& a);
    /// Single object ID-related
    void fillLepDz       (string prefix, Analyses::AnalysisData& a);
    void fillLepDxy      (string prefix, Analyses::AnalysisData& a);
    void fillLepIp3d     (string prefix, Analyses::AnalysisData& a);
    void fillLepSip3d    (string prefix, Analyses::AnalysisData& a);
    void fillLepRelIso03 (string prefix, Analyses::AnalysisData& a);
    void fillLepAbsIso03 (string prefix, Analyses::AnalysisData& a);
    void fillLepRelIso03EA(string prefix, Analyses::AnalysisData& a);
    void fillLepAbsIso03EA(string prefix, Analyses::AnalysisData& a);
    void fillLepRelIso03DB(string prefix, Analyses::AnalysisData& a);
    void fillLepAbsIso03DB(string prefix, Analyses::AnalysisData& a);
    void fillLepMiniIso03(string prefix, Analyses::AnalysisData& a);
    void fillLepPtRel    (string prefix, Analyses::AnalysisData& a);
    void fillLepPtRatio  (string prefix, Analyses::AnalysisData& a);
    void fillLepID       (string prefix, Analyses::AnalysisData& a);
    void fillLepIsFromW  (string prefix, Analyses::AnalysisData& a);
    /// Single object jet related
    void fillJetID       (string prefix, Analyses::AnalysisData& a);
    /// Single object veto lepton related
    void fillVetoLepDz       (string prefix, Analyses::AnalysisData& a);
    void fillVetoLepDxy      (string prefix, Analyses::AnalysisData& a);
    void fillVetoLepIp3d     (string prefix, Analyses::AnalysisData& a);
    void fillVetoLepSip3d    (string prefix, Analyses::AnalysisData& a);
    void fillVetoLepRelIso03 (string prefix, Analyses::AnalysisData& a);
    void fillVetoLepAbsIso03 (string prefix, Analyses::AnalysisData& a);
    void fillVetoLepRelIso03EA(string prefix, Analyses::AnalysisData& a);
    void fillVetoLepAbsIso03EA(string prefix, Analyses::AnalysisData& a);
    void fillVetoLepRelIso03DB(string prefix, Analyses::AnalysisData& a);
    void fillVetoLepAbsIso03DB(string prefix, Analyses::AnalysisData& a);
    void fillVetoLepMiniIso03(string prefix, Analyses::AnalysisData& a);
    void fillVetoLepPtRel    (string prefix, Analyses::AnalysisData& a);
    void fillVetoLepPtRatio  (string prefix, Analyses::AnalysisData& a);
    void fillVetoLepID       (string prefix, Analyses::AnalysisData& a);
    void fillVetoLepIsFromW  (string prefix, Analyses::AnalysisData& a);

    void fillCutflow    (string prefix, Analyses::AnalysisData& a, int ibin);

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

    void setTruths(Analyses::AnalysisData& ana_data, TString name);
    void setLeptons(Analyses::AnalysisData& ana_data, TString name);
    void setJets(Analyses::AnalysisData& ana_data, TString name);
    void setMET(Analyses::AnalysisData& ana_data, TString name);
    void setEventInfo(Analyses::AnalysisData& ana_data, TString name);
    void pushback4Vec(TLorentzVector p4, TString name);

    void createSkimTree(const char*);
    void fillSkimTree();
    void saveSkimTree();

  }

}

// comparators
template <class T>
bool comparator_pdgId(T p0, T p1) { return p0.pdgId > p1.pdgId; }
template <class T>
bool comparator_pt(T p0, T p1) { return p0.p4.Pt() > p1.p4.Pt(); }


#endif
//eof
