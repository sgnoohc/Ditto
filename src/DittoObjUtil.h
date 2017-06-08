// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

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
