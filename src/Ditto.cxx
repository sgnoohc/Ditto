// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include "Ditto.h"

#define NMAX_INDIVD_OBJ_TO_PLOT 6

namespace Ditto
{
  #include "DittoPlotUtil.cxx"
  #include "DittoPrintUtil.cxx"
  #include "DittoLoopUtil.cxx"

  namespace ObjUtil
  {
    AnalysisData* ana_data;
    void setAnalysisData(AnalysisData& a) { ana_data = &a; }
  }

  #include "DittoVarUtil.cxx"

  namespace Analyses
  {

    bool do_object_cutflow = false;

    //______________________________________________________________________________________
    void doObjectCutflow() { do_object_cutflow = true; }
    void doNotObjectCutflow() { do_object_cutflow = false; }

    //______________________________________________________________________________________
    template <class T>
    void selectObjs(std::vector<T>& objs, std::function<bool (T&)> isgoodobj)
    {
      std::vector<T> goodobjs;
      for (auto& obj: objs) if (isgoodobj(obj)) goodobjs.push_back(obj);
      objs = std::vector<T>(goodobjs);
    }

  }


  namespace HistUtil
  {

    //______________________________________________________________________________________
    string catPrefix(string prefix1, string prefix2)
    {
      return TString::Format("%s_%s_", prefix1.c_str(), prefix2.c_str()).Data();
    }

    //______________________________________________________________________________________
    void fillStdHistograms(string prefix, ObjUtil::AnalysisData& a)
    {
      /// fill all histogram types
      fillNLep       (prefix, a);
      fillNJet       (prefix, a);
      fillNBjet      (prefix, a);
      fillMET        (prefix, a);
      fillLepPt      (prefix, a);
      fillJetPt      (prefix, a);
      fillBJetPt     (prefix, a);
      fillLepEta     (prefix, a);
      fillJetEta     (prefix, a);
      fillBJetEta    (prefix, a);
      fillLepPhi     (prefix, a);
      fillJetPhi     (prefix, a);
      fillBJetPhi    (prefix, a);
      fillMjjW       (prefix, a);
      fillMll        (prefix, a);
      fillMljClose   (prefix, a);
      fillVBFMjj     (prefix, a);
      fillVBFMbb     (prefix, a);
      fillMjj        (prefix, a);
      fillPtjj       (prefix, a);
      fillPtbb       (prefix, a);
      fillMT         (prefix, a);
      fillHT         (prefix, a);
      fillMTll       (prefix, a);
      fillDPhill     (prefix, a);
      fillDEtajj     (prefix, a);
      fillDRjj       (prefix, a);
      fillDEtabb     (prefix, a);
      fillDPhiLepMET (prefix, a);
      fillDRjjW      (prefix, a);
      //fillLepDz      (prefix, a);
      //fillLepDxy     (prefix, a);
      //fillLepIp3d    (prefix, a);
      //fillLepSip3d   (prefix, a);
      //fillLepRelIso03(prefix, a);
      //fillLepAbsIso03(prefix, a);
      //fillLepRelIso03EA(prefix, a);
      //fillLepAbsIso03EA(prefix, a);
      //fillLepRelIso03DB(prefix, a);
      //fillLepAbsIso03DB(prefix, a);
      //fillLepMiniIso03(prefix, a);
      //fillLepPtRatio (prefix, a);
      //fillLepPtRel   (prefix, a);
      ////fillLepID      (prefix, a);
      //fillLepIsFromW (prefix, a);
      //fillJetID      (prefix, a);
    }

    //______________________________________________________________________________________
    void fillLeptonIDHistograms(string prefix, ObjUtil::AnalysisData& a)
    {
      /// fill all histogram types
      fillLepDz        (prefix, a);
      fillLepDxy       (prefix, a);
      fillLepIp3d      (prefix, a);
      fillLepSip3d     (prefix, a);
      fillLepRelIso03  (prefix, a);
      fillLepAbsIso03  (prefix, a);
      fillLepRelIso03EA(prefix, a);
      fillLepAbsIso03EA(prefix, a);
      fillLepRelIso03DB(prefix, a);
      fillLepAbsIso03DB(prefix, a);
      fillLepMiniIso   (prefix, a);
      fillLepPtRatio   (prefix, a);
      fillLepPtRel     (prefix, a);
      fillLepIsFromW   (prefix, a);
    }

    //______________________________________________________________________________________
    void fillIsFromWLeptonIDHistograms(string prefix, ObjUtil::AnalysisData& a)
    {
      /// fill all histogram types
      fillIsFromWLepPt          (prefix, a);
      fillIsFromWLepEta         (prefix, a);
      fillIsFromWLepPhi         (prefix, a);
      fillIsFromWLepPt          (prefix, a);
      fillIsFromWLepEta         (prefix, a);
      fillIsFromWLepDz          (prefix, a);
      fillIsFromWLepDxy         (prefix, a);
      fillIsFromWLepIp3d        (prefix, a);
      fillIsFromWLepSip3d       (prefix, a);
      fillIsFromWLepRelIso03    (prefix, a);
      fillIsFromWLepAbsIso03    (prefix, a);
      fillIsFromWLepRelIso03EA  (prefix, a);
      fillIsFromWLepAbsIso03EA  (prefix, a);
      fillIsFromWLepRelIso03EAv2(prefix, a);
      fillIsFromWLepAbsIso03EAv2(prefix, a);
      fillIsFromWLepRelIso04EA  (prefix, a);
      fillIsFromWLepAbsIso04EA  (prefix, a);
      fillIsFromWLepRelIso04EAv2(prefix, a);
      fillIsFromWLepAbsIso04EAv2(prefix, a);
      fillIsFromWLepRelIso03DB  (prefix, a);
      fillIsFromWLepAbsIso03DB  (prefix, a);
      fillIsFromWLepMiniIso     (prefix, a);
      fillIsFromWLepMiniIsov2   (prefix, a);
      fillIsFromWLepPtRatio     (prefix, a);
      fillIsFromWLepPtRel       (prefix, a);
      fillIsFromWLepIsFromW     (prefix, a);
    }

    //______________________________________________________________________________________
    void fillIsNotFromWLeptonIDHistograms(string prefix, ObjUtil::AnalysisData& a)
    {
      /// fill all histogram types
      fillIsNotFromWLepPt          (prefix, a);
      fillIsNotFromWLepEta         (prefix, a);
      fillIsNotFromWLepPhi         (prefix, a);
      fillIsNotFromWLepDz          (prefix, a);
      fillIsNotFromWLepDxy         (prefix, a);
      fillIsNotFromWLepIp3d        (prefix, a);
      fillIsNotFromWLepSip3d       (prefix, a);
      fillIsNotFromWLepRelIso03    (prefix, a);
      fillIsNotFromWLepAbsIso03    (prefix, a);
      fillIsNotFromWLepRelIso03EA  (prefix, a);
      fillIsNotFromWLepAbsIso03EA  (prefix, a);
      fillIsNotFromWLepRelIso03EAv2(prefix, a);
      fillIsNotFromWLepAbsIso03EAv2(prefix, a);
      fillIsNotFromWLepRelIso04EA  (prefix, a);
      fillIsNotFromWLepAbsIso04EA  (prefix, a);
      fillIsNotFromWLepRelIso04EAv2(prefix, a);
      fillIsNotFromWLepAbsIso04EAv2(prefix, a);
      fillIsNotFromWLepRelIso03DB  (prefix, a);
      fillIsNotFromWLepAbsIso03DB  (prefix, a);
      fillIsNotFromWLepMiniIso     (prefix, a);
      fillIsNotFromWLepMiniIsov2   (prefix, a);
      fillIsNotFromWLepPtRatio     (prefix, a);
      fillIsNotFromWLepPtRel       (prefix, a);
      fillIsNotFromWLepIsFromW     (prefix, a);
    }

    //______________________________________________________________________________________
    /// Multiplicity variables
    void fillNLep      (string prefix , ObjUtil::AnalysisData& a) { PlotUtil::plot1D("nlep"  , a.leptons.size() , a.wgt , a.hist_db , "N_{lep}" , 10 , 0. , 10. , prefix); }
    void fillNJet      (string prefix , ObjUtil::AnalysisData& a) { PlotUtil::plot1D("njet"  , a.jets.size()    , a.wgt , a.hist_db , "N_{jet}" , 10 , 0. , 10. , prefix); }
    void fillNBjet     (string prefix , ObjUtil::AnalysisData& a) { PlotUtil::plot1D("nbjet" , a.bjets.size()   , a.wgt , a.hist_db , "N_{b-jet}" , 10 , 0. , 10. , prefix); }
    /// Single object kinematics
    void fillMET       (string prefix , ObjUtil::AnalysisData& a) { PlotUtil::plot1D("met"       , a.met.p4.Pt()          , a.wgt , a.hist_db , "MET [GeV]" , 180 , 0. , 500.   , prefix); }
    void fillLepPt     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep  = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)  PlotUtil ::plot1D(TString::Format("lep%dpt"   , ilep).Data()  , a.leptons[ilep].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, lep%d} [GeV]"  , ilep).Data()  , 180     , 0.      , 200. - ilep * 20  , prefix); }
    void fillJetPt     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ijet  = 0; ijet < a.jets   .size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)  PlotUtil ::plot1D(TString::Format("jet%dpt"   , ijet).Data()  , a.jets   [ijet].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, jet%d} [GeV]"  , ijet).Data()  , 180     , 0.      , 200. - ijet * 20  , prefix); }
    void fillBJetPt    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ibjet = 0; ibjet < a.bjets .size() && ibjet< NMAX_INDIVD_OBJ_TO_PLOT; ++ibjet) PlotUtil ::plot1D(TString::Format("bjet%dpt"  , ibjet).Data() , a.bjets   [ibjet].p4.Pt()  , a.wgt , a.hist_db , TString::Format("p_{T, bjet%d} [GeV]" , ibjet).Data() , 180     , 0.      , 200. - ibjet * 20 , prefix); }
    void fillLepEta    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep  = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)  PlotUtil ::plot1D(TString::Format("lep%deta"  , ilep).Data()  , a.leptons[ilep].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{lep%d}"        , ilep).Data()  , 180     , -3.     , 3.     , prefix); }
    void fillJetEta    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ijet  = 0; ijet < a.jets   .size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)  PlotUtil ::plot1D(TString::Format("jet%deta"  , ijet).Data()  , a.jets   [ijet].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{jet%d}"        , ijet).Data()  , 180     , -5.     , 5.     , prefix); }
    void fillBJetEta   (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ibjet = 0; ibjet < a.bjets .size() && ibjet< NMAX_INDIVD_OBJ_TO_PLOT; ++ibjet) PlotUtil ::plot1D(TString::Format("bjet%deta" , ibjet).Data() , a.bjets   [ibjet].p4.Eta() , a.wgt , a.hist_db , TString::Format("#eta_{bjet%d}"       , ibjet).Data() , 180     , -5.     , 5.     , prefix); }
    void fillLepPhi    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep  = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)  PlotUtil ::plot1D(TString::Format("lep%dphi"  , ilep).Data()  , a.leptons[ilep].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{lep%d}"        , ilep).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
    void fillJetPhi    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ijet  = 0; ijet < a.jets   .size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)  PlotUtil ::plot1D(TString::Format("jet%dphi"  , ijet).Data()  , a.jets   [ijet].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{jet%d}"        , ijet).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
    void fillBJetPhi   (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ibjet = 0; ibjet < a.bjets .size() && ibjet< NMAX_INDIVD_OBJ_TO_PLOT; ++ibjet) PlotUtil ::plot1D(TString::Format("bjet%dphi" , ibjet).Data() , a.bjets   [ibjet].p4.Phi() , a.wgt , a.hist_db , TString::Format("#phi_{bjet%d}"       , ibjet).Data() , 180     , -3.1416 , 3.1416 , prefix); }
    /// Di object kinematics (GeV scales)
    void fillMll       (string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 2) PlotUtil::plot1D("mll"       , VarUtil::Mll(a)        , a.wgt , a.hist_db , "M_{#ell#ell} [GeV]" , 180 , 0. , 180.   , prefix); }
    void fillVBFMjj    (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("vbfmjj"    , VarUtil::Mjj(a)        , a.wgt , a.hist_db , "M_{jj} [GeV]" , 180 , 0. , 2500.  , prefix); }
    void fillVBFMbb    (string prefix , ObjUtil::AnalysisData& a) { if (a.bjets  .size() >= 2) PlotUtil::plot1D("vbfmbb"    , VarUtil::Mbb(a)        , a.wgt , a.hist_db , "M_{bb} [GeV]" , 180 , 0. , 2500.  , prefix); }
    void fillPtjj      (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("ptjj"      , VarUtil::Ptjj(a)       , a.wgt , a.hist_db , "p_{T,jj} [GeV]" , 180 , 0. , 1000.  , prefix); }
    void fillPtbb      (string prefix , ObjUtil::AnalysisData& a) { if (a.bjets  .size() >= 2) PlotUtil::plot1D("ptbb"      , VarUtil::Ptbb(a)       , a.wgt , a.hist_db , "p_{T,bb} [GeV]" , 180 , 0. , 1000.  , prefix); }
    void fillMjjW      (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("mjjw"      , VarUtil::MjjWmass(a)   , a.wgt , a.hist_db , "M_{jj,close-to-W} [GeV]" , 180 , 0. , 180.   , prefix); }
    void fillMjj       (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("mjj"       , VarUtil::Mjj(a)        , a.wgt , a.hist_db , "M_{jj} [GeV]" , 180 , 0. , 180.   , prefix); }
    void fillMT        (string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 1) PlotUtil::plot1D("mt"        , VarUtil::MT(a)         , a.wgt , a.hist_db , "M_{T} [GeV]" , 180 , 0. , 180.   , prefix); }
    void fillHT        (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 1) PlotUtil::plot1D("ht"        , VarUtil::HT(a)         , a.wgt , a.hist_db , "H_{T} [GeV]" , 180 , 0. , 1200.  , prefix); }
    void fillMTll      (string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 2) PlotUtil::plot1D("mtll"      , VarUtil::MTll(a)       , a.wgt , a.hist_db , "M_{T,ll} [GeV]" , 180 , 0. , 400.   , prefix); }
    void fillMljClose  (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 1) if (a.leptons.size() >= 1)PlotUtil::plot1D("mljclose"  , VarUtil::MljClosest(a)   , a.wgt , a.hist_db , "M_{lj,close} [GeV]" , 180 , 0. , 400.   , prefix); }
    /// Di object kinematics (angular)
    void fillDPhill    (string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 2) PlotUtil::plot1D("dphill"    , VarUtil::DPhill(a)     , a.wgt , a.hist_db , "#Delta#phi_{#ell#ell}" , 180 , 0. , 3.1416 , prefix); }
    void fillDEtajj    (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("detajj"    , VarUtil::DEtajj(a)     , a.wgt , a.hist_db , "#Delta#eta_{jj}" , 180 , 0. , 9.     , prefix); }
    void fillDRjj      (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("drjj"      , VarUtil::DRjj(a)       , a.wgt , a.hist_db , "#DeltaR{jj}" , 180 , 0. , 9.   , prefix); }
    void fillDEtabb    (string prefix , ObjUtil::AnalysisData& a) { if (a.bjets  .size() >= 2) PlotUtil::plot1D("detabb"    , VarUtil::DEtabb(a)     , a.wgt , a.hist_db , "#Delta#phi_{bb}" , 180 , 0. , 9.     , prefix); }
    void fillDPhiLepMET(string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 1) PlotUtil::plot1D("dphilepmet", VarUtil::DPhiLepMET(a) , a.wgt , a.hist_db , "#Delta#phi_{#ell,MET}" , 5   , 0. , 3.1416 , prefix); }
    void fillDRjjW     (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("drjjw"     , VarUtil::DRjjWmass(a)  , a.wgt , a.hist_db , "#DeltaR{jj,close-to-W}" , 180 , 0. , 9.   , prefix); }
    /// Single object ID-related
    void fillLepDz          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%ddz"        , ilep).Data() , a.leptons[ilep].dz                                   , a.wgt , a.hist_db , "" , 180 , 0. , 0.05, prefix); }
    void fillLepDxy         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%ddxy"       , ilep).Data() , a.leptons[ilep].dxy                                  , a.wgt , a.hist_db , "" , 180 , 0. , 0.01, prefix); }
    void fillLepIp3d        (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dip3d"      , ilep).Data() , a.leptons[ilep].ip3d                                 , a.wgt , a.hist_db , "" , 180 , 0. , 0.05, prefix); }
    void fillLepSip3d       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dsip3d"     , ilep).Data() , a.leptons[ilep].sip3d                                , a.wgt , a.hist_db , "" , 180 , 0. , 10 , prefix); }
    void fillLepRelIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%drelIso03"  , ilep).Data() , a.leptons[ilep].relIso03                             , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
    void fillLepAbsIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dabsIso03"  , ilep).Data() , a.leptons[ilep].relIso03 * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180 , 0. , 20. , prefix); }
    void fillLepRelIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%drelIso03EA", ilep).Data() , a.leptons[ilep].relIso03EA                           , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
    void fillLepAbsIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dabsIso03EA", ilep).Data() , a.leptons[ilep].relIso03EA * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180 , 0. , 20. , prefix); }
    void fillLepRelIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%drelIso03EA", ilep).Data() , a.leptons[ilep].relIso03EA                           , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
    void fillLepAbsIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dabsIso03EA", ilep).Data() , a.leptons[ilep].relIso03EA * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180 , 0. , 20. , prefix); }
    void fillLepRelIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%drelIso03DB", ilep).Data() , a.leptons[ilep].relIso03DB                           , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
    void fillLepAbsIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dabsIso03DB", ilep).Data() , a.leptons[ilep].relIso03DB * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180 , 0. , 20. , prefix); }
    void fillLepMiniIso     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dminiIso03" , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EA                    , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
    void fillLepPtRel       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dptrel"     , ilep).Data() , a.leptons[ilep].ptRel                                , a.wgt , a.hist_db , "" , 180 , 0. , 30., prefix); }
    void fillLepPtRatio     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dptratio"   , ilep).Data() , a.leptons[ilep].ptRatio                              , a.wgt , a.hist_db , "" , 180 , 0.5, 1.0, prefix); }
    void fillLepIsFromW     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dIsFromW"   , ilep).Data() , (a.leptons[ilep].isFromX) & (1<<0)                   , a.wgt , a.hist_db , "" ,   2 , 0. , 2  , prefix); }
    /// Leptons from W
    void fillIsFromWLepPt          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil ::plot1D(TString::Format("lep%dpt"   , ilep).Data()  , a.leptons[ilep].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, lep%d} [GeV]"  , ilep).Data()  , 180     , 0.      , 200. - ilep * 20  , prefix); }
    void fillIsFromWLepEta         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil ::plot1D(TString::Format("lep%deta"  , ilep).Data()  , a.leptons[ilep].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{lep%d}"        , ilep).Data()  , 180     , -3.     , 3.     , prefix); }
    void fillIsFromWLepPhi         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil ::plot1D(TString::Format("lep%dphi"  , ilep).Data()  , a.leptons[ilep].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{lep%d}"        , ilep).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
    void fillIsFromWLepDz          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%ddz"           , ilep).Data() , a.leptons[ilep].dz                                     , a.wgt , a.hist_db , "" , 180  , 0.  , 0.05 , prefix); }
    void fillIsFromWLepDxy         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%ddxy"          , ilep).Data() , a.leptons[ilep].dxy                                    , a.wgt , a.hist_db , "" , 180  , 0.  , 0.01 , prefix); }
    void fillIsFromWLepIp3d        (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dip3d"         , ilep).Data() , a.leptons[ilep].ip3d                                   , a.wgt , a.hist_db , "" , 180  , 0.  , 0.05 , prefix); }
    void fillIsFromWLepSip3d       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dsip3d"        , ilep).Data() , a.leptons[ilep].sip3d                                  , a.wgt , a.hist_db , "" , 180  , 0.  , 10   , prefix); }
    void fillIsFromWLepRelIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso03"     , ilep).Data() , a.leptons[ilep].relIso03                               , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsFromWLepAbsIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso03"     , ilep).Data() , a.leptons[ilep].relIso03 * a.leptons[ilep].p4.Pt()     , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsFromWLepRelIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso03EA"   , ilep).Data() , a.leptons[ilep].relIso03EA                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsFromWLepAbsIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso03EA"   , ilep).Data() , a.leptons[ilep].relIso03EA * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsFromWLepRelIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso03EAv2" , ilep).Data() , a.leptons[ilep].relIso03EAv2                           , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsFromWLepAbsIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso03EAv2" , ilep).Data() , a.leptons[ilep].relIso03EAv2 * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsFromWLepRelIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso03DB"   , ilep).Data() , a.leptons[ilep].relIso03DB                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsFromWLepAbsIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso03DB"   , ilep).Data() , a.leptons[ilep].relIso03DB * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsFromWLepRelIso04EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso04EA"   , ilep).Data() , a.leptons[ilep].relIso04EA                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsFromWLepAbsIso04EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso04EA"   , ilep).Data() , a.leptons[ilep].relIso04EA * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsFromWLepRelIso04EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso04EAv2" , ilep).Data() , a.leptons[ilep].relIso04EAv2                           , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsFromWLepAbsIso04EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso04EAv2" , ilep).Data() , a.leptons[ilep].relIso04EAv2 * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsFromWLepRelIso04DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso04DB"   , ilep).Data() , a.leptons[ilep].relIso04DB                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsFromWLepAbsIso04DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso04DB"   , ilep).Data() , a.leptons[ilep].relIso04DB * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsFromWLepMiniIso     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dminiIso"      , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EA                      , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsFromWLepMiniIsov2   (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dminiIsov2"    , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EAv2                    , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsFromWLepPtRel       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dptrel"        , ilep).Data() , a.leptons[ilep].ptRel                                  , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsFromWLepPtRatio     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dptratio"      , ilep).Data() , a.leptons[ilep].ptRatio                                , a.wgt , a.hist_db , "" , 180  , 0.5 , 1.0  , prefix); }
    void fillIsFromWLepIsFromW     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dIsFromW"      , ilep).Data() , (a.leptons[ilep].isFromX) & (1<<0)                     , a.wgt , a.hist_db , "" , 2    , 0.  , 2    , prefix); }
    /// Leptons Is not from W
    void fillIsNotFromWLepPt          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil ::plot1D(TString::Format("lep%dpt"   , ilep).Data()  , a.leptons[ilep].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, lep%d} [GeV]"  , ilep).Data()  , 180     , 0.      , 200. - ilep * 20  , prefix); }
    void fillIsNotFromWLepEta         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil ::plot1D(TString::Format("lep%deta"  , ilep).Data()  , a.leptons[ilep].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{lep%d}"        , ilep).Data()  , 180     , -3.     , 3.     , prefix); }
    void fillIsNotFromWLepPhi         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil ::plot1D(TString::Format("lep%dphi"  , ilep).Data()  , a.leptons[ilep].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{lep%d}"        , ilep).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
    void fillIsNotFromWLepDz          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%ddz"           , ilep).Data() , a.leptons[ilep].dz                                     , a.wgt , a.hist_db , "" , 180  , 0.  , 0.05 , prefix); }
    void fillIsNotFromWLepDxy         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%ddxy"          , ilep).Data() , a.leptons[ilep].dxy                                    , a.wgt , a.hist_db , "" , 180  , 0.  , 0.01 , prefix); }
    void fillIsNotFromWLepIp3d        (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dip3d"         , ilep).Data() , a.leptons[ilep].ip3d                                   , a.wgt , a.hist_db , "" , 180  , 0.  , 0.05 , prefix); }
    void fillIsNotFromWLepSip3d       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dsip3d"        , ilep).Data() , a.leptons[ilep].sip3d                                  , a.wgt , a.hist_db , "" , 180  , 0.  , 10   , prefix); }
    void fillIsNotFromWLepRelIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso03"     , ilep).Data() , a.leptons[ilep].relIso03                               , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsNotFromWLepAbsIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso03"     , ilep).Data() , a.leptons[ilep].relIso03 * a.leptons[ilep].p4.Pt()     , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsNotFromWLepRelIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso03EA"   , ilep).Data() , a.leptons[ilep].relIso03EA                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsNotFromWLepAbsIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso03EA"   , ilep).Data() , a.leptons[ilep].relIso03EA * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsNotFromWLepRelIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso03EAv2" , ilep).Data() , a.leptons[ilep].relIso03EAv2                           , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsNotFromWLepAbsIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso03EAv2" , ilep).Data() , a.leptons[ilep].relIso03EAv2 * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsNotFromWLepRelIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso03DB"   , ilep).Data() , a.leptons[ilep].relIso03DB                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsNotFromWLepAbsIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso03DB"   , ilep).Data() , a.leptons[ilep].relIso03DB * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsNotFromWLepRelIso04EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso04EA"   , ilep).Data() , a.leptons[ilep].relIso04EA                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsNotFromWLepAbsIso04EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso04EA"   , ilep).Data() , a.leptons[ilep].relIso04EA * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsNotFromWLepRelIso04EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso04EAv2" , ilep).Data() , a.leptons[ilep].relIso04EAv2                           , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsNotFromWLepAbsIso04EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso04EAv2" , ilep).Data() , a.leptons[ilep].relIso04EAv2 * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsNotFromWLepRelIso04DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso04DB"   , ilep).Data() , a.leptons[ilep].relIso04DB                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsNotFromWLepAbsIso04DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso04DB"   , ilep).Data() , a.leptons[ilep].relIso04DB * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsNotFromWLepMiniIso     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dminiIso"      , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EA                      , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsNotFromWLepMiniIsov2   (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dminiIso"      , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EAv2                    , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
    void fillIsNotFromWLepPtRel       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dptrel"        , ilep).Data() , a.leptons[ilep].ptRel                                  , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
    void fillIsNotFromWLepPtRatio     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dptratio"      , ilep).Data() , a.leptons[ilep].ptRatio                                , a.wgt , a.hist_db , "" , 180  , 0.5 , 1.0  , prefix); }
    void fillIsNotFromWLepIsFromW     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dIsFromW"      , ilep).Data() , (a.leptons[ilep].isFromX) & (1<<0)                     , a.wgt , a.hist_db , "" , 2    , 0.  , 2    , prefix); }
    // Jet single object
    void fillJetID        (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ijet = 0; ijet < a.jets   .size(); ++ijet) PlotUtil::plot1D(TString::Format("jet%dID"        , ijet).Data() , a.jets   [ijet].id                                   , a.wgt , a.hist_db , "" ,   2 , 0. , 30 , prefix); }

    void fillCutflow    (string prefix, ObjUtil::AnalysisData& a, int ibin)
    {
      PlotUtil::plot1D("cutflow"   , ibin, a.wgt, a.hist_db, "", 20, 0., 20., prefix);
      PlotUtil::plot1D("rawcutflow", ibin,    1., a.hist_db, "", 20, 0., 20., prefix);
    }

  }

  namespace TreeUtil
  {

    TreeData treedata;
    TFile* skimfile = 0;
    TTree* skimtree = 0;

    void initTreeData()
    {
      for (auto& v: treedata.mapint) v.second = 0;
      for (auto& v: treedata.mapvfloat) (*v.second).clear();
      for (auto& v: treedata.mapvint) (*v.second).clear();
    }

    void createIntBranch(TTree* tree, TString name) { treedata.mapint[name] = 0; tree->Branch(name, &(treedata.mapint[name]), name+"/I"); }
    void createFloatBranch(TTree* tree, TString name) { treedata.mapfloat[name] = 0; tree->Branch(name, &(treedata.mapfloat[name]), name+"/F"); }
    void createVIntBranch(TTree* tree, TString name) { treedata.mapvint[name] = new std::vector<int>(); tree->Branch(name, &(treedata.mapvint[name])); }
    void createVFloatBranch(TTree* tree, TString name) { treedata.mapvfloat[name] = new std::vector<float>(); tree->Branch(name, &(treedata.mapvfloat[name])); }

    void setIntBranch(TString name, int val) { treedata.mapint[name] = val; }
    void setFloatBranch(TString name, float val) { treedata.mapfloat[name] = val; }
    void pushbackVIntBranch(TString name, int val) { (*(treedata.mapvint[name])).push_back(val); }
    void pushbackVFloatBranch(TString name, float val) { (*(treedata.mapvfloat[name])).push_back(val); }

    void create4VecBranch(TTree* tree, TString name)
    {
      createIntBranch(tree, name+"_n");
      createVFloatBranch(tree, name+"_pt");
      createVFloatBranch(tree, name+"_eta");
      createVFloatBranch(tree, name+"_phi");
      createVFloatBranch(tree, name+"_mass");
      createVFloatBranch(tree, name+"_energy");
    }

    void createTruthBranch(TTree* tree, TString name)
    {
      create4VecBranch(tree, name);
      createVIntBranch(tree, name+"_pdgId");
      createVIntBranch(tree, name+"_status");
      createVIntBranch(tree, name+"_motherId");
      createVIntBranch(tree, name+"_grandmotherId");
    }

    void createLeptonBranch(TTree* tree, TString name)
    {
      create4VecBranch  (tree, name);
      createVFloatBranch(tree, name+"_dxy");
      createVFloatBranch(tree, name+"_dz");
      createVFloatBranch(tree, name+"_ip3d");
      createVFloatBranch(tree, name+"_sip3d");
      createVIntBranch  (tree, name+"_tightcharge");
      createVIntBranch  (tree, name+"_charge");
      createVIntBranch  (tree, name+"_pdgId");
      createVIntBranch  (tree, name+"_id");
      createVFloatBranch(tree, name+"_ptRatio");
      createVFloatBranch(tree, name+"_ptRel");
      createVFloatBranch(tree, name+"_relIso03");
      createVFloatBranch(tree, name+"_relIso03DB");
      createVFloatBranch(tree, name+"_relIso03EA");
      createVFloatBranch(tree, name+"_relIso03EAv2");
      createVFloatBranch(tree, name+"_relIso04DB");
      createVFloatBranch(tree, name+"_relIso04EA");
      createVFloatBranch(tree, name+"_relIso04EAv2");
      createVFloatBranch(tree, name+"_miniRelIsoCMS3_EA");
      createVFloatBranch(tree, name+"_miniRelIsoCMS3_EAv2");
      createVFloatBranch(tree, name+"_miniRelIsoCMS3_DB");
      // Muon specifics
      createVFloatBranch(tree, name+"_muPOverP");
      createVIntBranch  (tree, name+"_muPidPFMuon");
      createVIntBranch  (tree, name+"_muType");
      createVFloatBranch(tree, name+"_muChi2OverNDof");
      createVFloatBranch(tree, name+"_muChi2LocalPosition");
      createVFloatBranch(tree, name+"_muTrkKink");
      createVFloatBranch(tree, name+"_muValidHitFraction");
      createVFloatBranch(tree, name+"_muSegmCompatibility");
      createVIntBranch  (tree, name+"_muGFitValidSTAHits");
      createVIntBranch  (tree, name+"_muNMatchedStations");
      createVIntBranch  (tree, name+"_muValidPixelHits");
      createVIntBranch  (tree, name+"_muNLayers");
      // Electron specifics
      createVFloatBranch(tree, name+"_elEtaSC");
      createVFloatBranch(tree, name+"_elSigmaIEtaIEta_full5x5");
      createVFloatBranch(tree, name+"_elHOverE");
      createVFloatBranch(tree, name+"_elMvaRaw");
      createVFloatBranch(tree, name+"_elMva");
      createVFloatBranch(tree, name+"_elDEtaIn");
      createVFloatBranch(tree, name+"_elDPhiIn");
      createVFloatBranch(tree, name+"_elEpRatio");
      createVIntBranch  (tree, name+"_elConvVeto");
      createVIntBranch  (tree, name+"_elNmiss");
      createVIntBranch  (tree, name+"_isFromX");
    }

    void createJetBranch(TTree* tree, TString name)
    {
      create4VecBranch  (tree, name);
      createVFloatBranch(tree, name+"_btagCSV");
      createVFloatBranch(tree, name+"_rawPt");
      createVFloatBranch(tree, name+"_mcPt");
      createVIntBranch  (tree, name+"_mcFlavour");
      createVIntBranch  (tree, name+"_hadronFlavour");
      createVFloatBranch(tree, name+"_area");
      createVFloatBranch(tree, name+"_undoJEC");
      createVFloatBranch(tree, name+"_jecCorr");
      createVFloatBranch(tree, name+"_jecCorrUp");
      createVFloatBranch(tree, name+"_jecCorrDn");
      createVFloatBranch(tree, name+"_chf");
      createVFloatBranch(tree, name+"_nhf");
      createVFloatBranch(tree, name+"_cef");
      createVFloatBranch(tree, name+"_nef");
      createVFloatBranch(tree, name+"_muf");
      createVFloatBranch(tree, name+"_cm");
      createVFloatBranch(tree, name+"_nm");
      createVFloatBranch(tree, name+"_puValue");
      createVFloatBranch(tree, name+"_mcdr");
      createVIntBranch  (tree, name+"_npfcand");
      createVIntBranch  (tree, name+"_id");
      createVIntBranch  (tree, name+"_puId");
      createVIntBranch  (tree, name+"_puIdpuppi");
      createVIntBranch  (tree, name+"_FSveto");
    }

    void createMETBranch(TTree* tree, TString name)
    {
      createFloatBranch(tree, name+"_pt");
      createFloatBranch(tree, name+"_phi");
    }

    void createEventInfoBranch(TTree* tree, TString name)
    {
      createIntBranch(tree, name+"_run");
      createIntBranch(tree, name+"_lumi");
      createIntBranch(tree, name+"_event");
      createIntBranch(tree, name+"_nEvts");
      createFloatBranch(tree, name+"_scale1fb");
    }

    void setTruths(ObjUtil::AnalysisData& ana_data, TString name)
    {
      setIntBranch(name+"_n", ana_data.truths.size());
      for (auto& truth : ana_data.truths)
      {
        pushback4Vec(truth.p4, name);
        pushbackVIntBranch(name+"_pdgId", truth.pdgId);
        pushbackVIntBranch(name+"_status", truth.status);
        pushbackVIntBranch(name+"_motherId", truth.motherId);
        pushbackVIntBranch(name+"_grandmotherId", truth.grandmotherId);
      }
    }

    void setLeptons(ObjUtil::AnalysisData& ana_data, TString name)
    {
      setIntBranch(name+"_n", ana_data.leptons.size());
      for (auto& lepton : ana_data.leptons)
      {
        pushback4Vec(lepton.p4, name);
        pushbackVFloatBranch(name+"_dxy", lepton.dxy);
        pushbackVFloatBranch(name+"_dz", lepton.dz);
        pushbackVFloatBranch(name+"_ip3d", lepton.ip3d);
        pushbackVFloatBranch(name+"_sip3d", lepton.sip3d);
        pushbackVIntBranch  (name+"_tightcharge", lepton.tightcharge);
        pushbackVIntBranch  (name+"_charge", lepton.charge);
        pushbackVIntBranch  (name+"_pdgId", lepton.pdgId);
        pushbackVIntBranch  (name+"_id", lepton.id);
        pushbackVFloatBranch(name+"_ptRatio", lepton.ptRatio);
        pushbackVFloatBranch(name+"_ptRel", lepton.ptRel);
        pushbackVFloatBranch(name+"_relIso03", lepton.relIso03);
        pushbackVFloatBranch(name+"_relIso03DB", lepton.relIso03DB);
        pushbackVFloatBranch(name+"_relIso03EA", lepton.relIso03EA);
        pushbackVFloatBranch(name+"_relIso03EAv2", lepton.relIso03EAv2);
        pushbackVFloatBranch(name+"_relIso04DB", lepton.relIso04DB);
        pushbackVFloatBranch(name+"_relIso04EA", lepton.relIso04EA);
        pushbackVFloatBranch(name+"_relIso04EAv2", lepton.relIso04EAv2);
        pushbackVFloatBranch(name+"_miniRelIsoCMS3_EA", lepton.miniRelIsoCMS3_EA);
        pushbackVFloatBranch(name+"_miniRelIsoCMS3_EAv2", lepton.miniRelIsoCMS3_EAv2);
        pushbackVFloatBranch(name+"_miniRelIsoCMS3_DB", lepton.miniRelIsoCMS3_DB);
        // Muon specifics
        pushbackVFloatBranch(name+"_muPOverP", lepton.muPOverP);
        pushbackVIntBranch  (name+"_muPidPFMuon", lepton.muPidPFMuon);
        pushbackVIntBranch  (name+"_muType", lepton.muType);
        pushbackVFloatBranch(name+"_muChi2OverNDof", lepton.muChi2OverNDof);
        pushbackVFloatBranch(name+"_muChi2LocalPosition", lepton.muChi2LocalPosition);
        pushbackVFloatBranch(name+"_muTrkKink", lepton.muTrkKink);
        pushbackVFloatBranch(name+"_muValidHitFraction", lepton.muValidHitFraction);
        pushbackVFloatBranch(name+"_muSegmCompatibility", lepton.muSegmCompatibility);
        pushbackVIntBranch  (name+"_muGFitValidSTAHits", lepton.muGFitValidSTAHits);
        pushbackVIntBranch  (name+"_muNMatchedStations", lepton.muNMatchedStations);
        pushbackVIntBranch  (name+"_muValidPixelHits", lepton.muValidPixelHits);
        pushbackVIntBranch  (name+"_muNLayers", lepton.muNLayers);
        // Electron specifics
        pushbackVFloatBranch(name+"_elEtaSC", lepton.elEtaSC);
        pushbackVFloatBranch(name+"_elSigmaIEtaIEta_full5x5", lepton.elSigmaIEtaIEta_full5x5);
        pushbackVFloatBranch(name+"_elHOverE", lepton.elHOverE);
        pushbackVFloatBranch(name+"_elMvaRaw", lepton.elMvaRaw);
        pushbackVFloatBranch(name+"_elMva", lepton.elMva);
        pushbackVFloatBranch(name+"_elDEtaIn", lepton.elDEtaIn);
        pushbackVFloatBranch(name+"_elDPhiIn", lepton.elDPhiIn);
        pushbackVFloatBranch(name+"_elEpRatio", lepton.elEpRatio);
        pushbackVIntBranch  (name+"_elConvVeto", lepton.elConvVeto);
        pushbackVIntBranch  (name+"_elNmiss", lepton.elNmiss);
        pushbackVIntBranch  (name+"_isFromX", lepton.isFromX);
      }
    }

    void setJets(ObjUtil::AnalysisData& ana_data, TString name)
    {
      setIntBranch(name+"_n", ana_data.jets.size());
      for (auto& jet : ana_data.jets)
      {
        pushback4Vec(jet.p4, name);
        pushbackVFloatBranch(name+"_btagCSV", jet.btagCSV);
        pushbackVFloatBranch(name+"_rawPt", jet.rawPt);
        pushbackVFloatBranch(name+"_mcPt", jet.mcPt);
        pushbackVIntBranch  (name+"_mcFlavour", jet.mcFlavour);
        pushbackVIntBranch  (name+"_hadronFlavour", jet.hadronFlavour);
        pushbackVFloatBranch(name+"_area", jet.area);
        pushbackVFloatBranch(name+"_undoJEC", jet.undoJEC);
        pushbackVFloatBranch(name+"_jecCorr", jet.jecCorr);
        pushbackVFloatBranch(name+"_jecCorrUp", jet.jecCorrUp);
        pushbackVFloatBranch(name+"_jecCorrDn", jet.jecCorrDn);
        pushbackVFloatBranch(name+"_chf", jet.chf);
        pushbackVFloatBranch(name+"_nhf", jet.nhf);
        pushbackVFloatBranch(name+"_cef", jet.cef);
        pushbackVFloatBranch(name+"_nef", jet.nef);
        pushbackVFloatBranch(name+"_muf", jet.muf);
        pushbackVFloatBranch(name+"_cm", jet.cm);
        pushbackVFloatBranch(name+"_nm", jet.nm);
        pushbackVFloatBranch(name+"_puValue", jet.puValue);
        pushbackVFloatBranch(name+"_mcdr", jet.mcdr);
        pushbackVIntBranch  (name+"_npfcand", jet.npfcand);
        pushbackVIntBranch  (name+"_id", jet.id);
        pushbackVIntBranch  (name+"_puId", jet.puId);
        pushbackVIntBranch  (name+"_puIdpuppi", jet.puIdpuppi);
        pushbackVIntBranch  (name+"_FSveto", jet.FSveto);
      }
    }

    void setMET(ObjUtil::AnalysisData& ana_data, TString name)
    {
      setFloatBranch(name+"_pt", ana_data.met.p4.Pt());
      setFloatBranch(name+"_phi", ana_data.met.p4.Phi());
    }

    void setEventInfo(ObjUtil::AnalysisData& ana_data, TString name)
    {
      setIntBranch(name+"_run", ana_data.eventinfo.run);
      setIntBranch(name+"_lumi", ana_data.eventinfo.lumi);
      setIntBranch(name+"_event", ana_data.eventinfo.event);
      setIntBranch(name+"_nEvts", ana_data.eventinfo.nEvts);
      setFloatBranch(name+"_scale1fb", ana_data.eventinfo.scale1fb);
    }

    void pushback4Vec(TLorentzVector p4, TString name)
    {
      pushbackVFloatBranch(name+"_pt", p4.Pt());
      pushbackVFloatBranch(name+"_eta", p4.Eta());
      pushbackVFloatBranch(name+"_phi", p4.Phi());
      pushbackVFloatBranch(name+"_mass", p4.M());
      pushbackVFloatBranch(name+"_energy", p4.E());
    }

    void createSkimTree(const char* filename)
    {
      printf("[Ditto::HistUtil::saveSkimTree] Creating %s to hold skimmed TTree\n", filename);
      skimfile = new TFile(filename, "recreate");
      skimtree = LoopUtil::getCurrentTTree()->CloneTree(0);
    }

    void fillSkimTree()
    {
      skimtree->Fill();
    }

    void saveSkimTree()
    {
      if (!skimtree) return;
      printf("[Ditto::HistUtil::saveSkimTree] Writing skimmed TTree to %s\n", skimfile->GetName());
      skimfile->cd();
      skimtree->Write();
      delete skimtree;
      skimfile->Write();
      skimfile->Close();
    }

  }

}

//eof
