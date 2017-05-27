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

    //______________________________________________________________________________________
    bool isElectronPOGMVAIDCut(ObjUtil::Lepton& lepton,
                               float barrel_highpt_mvacut    , float barrel_lowpt_mvacut    , float barrel_lowerpt_mvacut    ,
                               float transition_highpt_mvacut, float transition_lowpt_mvacut, float transition_lowerpt_mvacut,
                               float endcap_highpt_mvacut    , float endcap_lowpt_mvacut    , float endcap_lowerpt_mvacut)
    {
      // for morioned MVA WPs: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SUSLeptonSF#ID_IP_ISO_AN1
      // returns A if pt<ptmin, B if pt>ptmax, and linear interpolation between. if pt<10, use C
      float ptmin = 15;
      float ptmax = 25;
      auto mvacut = [ptmin,ptmax](float A, float B, float C, float pt_) {
        return pt_>10 ? std::min(A, std::max(B,A + (B-A)/(ptmax-ptmin)*(pt_-ptmin))) : C;
      };

      float aeta = fabs(lepton.elEtaSC);
      if (aeta < 0.8)                     return lepton.elMva > mvacut(barrel_highpt_mvacut, barrel_lowpt_mvacut, barrel_lowerpt_mvacut, lepton.p4.Pt());
      if ((aeta >= 0.8 && aeta <= 1.479)) return lepton.elMva > mvacut(transition_highpt_mvacut, transition_lowpt_mvacut, transition_lowerpt_mvacut, lepton.p4.Pt());
      if (aeta > 1.479)                   return lepton.elMva > mvacut(endcap_highpt_mvacut, endcap_lowpt_mvacut, endcap_lowerpt_mvacut, lepton.p4.Pt());
      return false;
    }

    //______________________________________________________________________________________
    bool isElectronPOGCutBasedIDCut(ObjUtil::Lepton& lepton,
                                    float barrel_elSigmaIEtaIEta_full5x5_cut , float barrel_abs_elDEtaIn_cut , float barrel_abs_elDPhiIn_cut ,
                                    float barrel_elHOverE_cut                , float barrel_relIso03EA_cut   , float barrel_elEpRatio_cut    , int barrel_elNmiss_cut ,
                                    float endcap_elSigmaIEtaIEta_full5x5_cut , float endcap_abs_elDEtaIn_cut , float endcap_abs_elDPhiIn_cut ,
                                    float endcap_elHOverE_cut                , float endcap_relIso03EA_cut   , float endcap_elEpRatio_cut    , int endcap_elNmiss_cut)
    {
      if (fabs(lepton.elEtaSC) <= 1.479)
      {
        if (!( lepton.elSigmaIEtaIEta_full5x5 <  barrel_elSigmaIEtaIEta_full5x5_cut )) return false;
        if (!( fabs(lepton.elDEtaIn)          <  barrel_abs_elDEtaIn_cut            )) return false;
        if (!( fabs(lepton.elDPhiIn)          <  barrel_abs_elDPhiIn_cut            )) return false;
        if (!( lepton.elHOverE                <  barrel_elHOverE_cut                )) return false;
        if (!( lepton.relIso03EA              <  barrel_relIso03EA_cut              )) return false;
        if (!( lepton.elEpRatio               <  barrel_elEpRatio_cut               )) return false;
        if (!( lepton.elNmiss                 <= barrel_elNmiss_cut                 )) return false;
        if (!(!lepton.elConvVeto                                                    )) return false;
        return true;
      }
      else
      {
        if (!( lepton.elSigmaIEtaIEta_full5x5 <  endcap_elSigmaIEtaIEta_full5x5_cut )) return false;
        if (!( fabs(lepton.elDEtaIn)          <  endcap_abs_elDEtaIn_cut            )) return false;
        if (!( fabs(lepton.elDPhiIn)          <  endcap_abs_elDPhiIn_cut            )) return false;
        if (!( lepton.elHOverE                <  endcap_elHOverE_cut                )) return false;
        if (!( lepton.relIso03EA              <  endcap_relIso03EA_cut              )) return false;
        if (!( lepton.elEpRatio               <  endcap_elEpRatio_cut               )) return false;
        if (!( lepton.elNmiss                 <= endcap_elNmiss_cut                 )) return false;
        if (!(!lepton.elConvVeto                                                    )) return false;
        return true;
      }
    }

    //______________________________________________________________________________________
    bool isTriggerSafenoIso_v1(ObjUtil::Lepton& lepton)
    {
      if (fabs(lepton.elEtaSC) <= 1.479) {
        if (lepton.elSigmaIEtaIEta_full5x5 >= 0.011) return false;
        if (lepton.elHOverE >= 0.08) return false;
        if (fabs(lepton.elDEtaIn) >= 0.01) return false;
        if (fabs(lepton.elDPhiIn) >= 0.04) return false;
        if (fabs(lepton.elEpRatio) >= 0.01) return false; // ????
      } else if ((fabs(lepton.elEtaSC) > 1.479) && (fabs(lepton.elEtaSC) < 2.5)) {
        if (lepton.elSigmaIEtaIEta_full5x5 >= 0.031) return false;
        if (lepton.elHOverE >= 0.08) return false;
        if (fabs(lepton.elDEtaIn) >= 0.01) return false;
        if (fabs(lepton.elDPhiIn) >= 0.08) return false;
        if (fabs(lepton.elEpRatio) >= 0.01) return false; // ????
      }
      return true;
    }

    //______________________________________________________________________________________
    bool isMediumElectronPOGCutbased(ObjUtil::Lepton& lepton)
    {
      if (!(isElectronPOGCutBasedIDCut(lepton,
      /*barrel_elSigmaIEtaIEta_full5x5_cut , barrel_abs_elDEtaIn_cut , barrel_abs_elDPhiIn_cut ,                       */ 0.00998, 0.00311, 0.103,
      /*barrel_elHOverE_cut                , barrel_relIso03EA_cut   , barrel_elEpRatio_cut    , barrel_elNmiss_cut ,  */ 0.253  , 0.0695 , 0.134, 1,
      /*endcap_elSigmaIEtaIEta_full5x5_cut , endcap_abs_elDEtaIn_cut , endcap_abs_elDPhiIn_cut ,                       */ 0.0298 , 0.00609, 0.045,
      /*endcap_elHOverE_cut                , endcap_relIso03EA_cut   , endcap_elEpRatio_cut    , endcap_elNmiss_cut    */ 0.0878 , 0.0821 , 0.13 , 1) )) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isLooseMuonPOG(ObjUtil::Lepton& lepton)
    {
      // Loose criteria
      if ( !(lepton.muPidPFMuon                                   ) ) return false;
      if ( !((lepton.muType & (1<<1)) || (lepton.muType & (1<<2)) ) ) return false;
      //      ^^^^^^^^^^^^^^^^^^^^^       ^^^^^^^^^^^^^^^^^^^^^
      //      isGlobal muon               isTracker muon
      return true;
    }

    //______________________________________________________________________________________
    bool isMediumMuonPOG(ObjUtil::Lepton& lepton)
    {
      bool goodGlb = (lepton.muType & (1<<1))   != 0  &&
                     lepton.muChi2OverNDof      <  3. &&
                     lepton.muChi2LocalPosition < 12. &&
                     lepton.muTrkKink           < 20.;
      double segmCompatibilityCut = goodGlb ? 0.303 : 0.451;

      // Medium criteria
      if ( !(lepton.muValidHitFraction  >  0.8                  ) ) return false;
      if ( !(lepton.muSegmCompatibility >= segmCompatibilityCut ) ) return false;
      if ( !(isLooseMuonPOG(lepton)                             ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isLoosePFJet_Summer16_v1(ObjUtil::Jet& jet)
    {
      float pfjet_chf_ = jet.chf;
      float pfjet_nhf_ = jet.nhf;
      float pfjet_cef_ = jet.cef;
      float pfjet_nef_ = jet.nef;
      int   pfjet_cm_  = jet.cm;
      int   pfjet_nm_  = jet.nm;
      float pfjet_eta  = fabs(jet.p4.Eta());

      if (pfjet_eta <= 2.7)
      {
        if (pfjet_nhf_ >= 0.99       ) return false;
        if (pfjet_nef_ >= 0.99       ) return false;
        if (pfjet_cm_ + pfjet_nm_ < 2) return false;

        if (pfjet_eta < 2.4){
          if (!(pfjet_cm_  >   0.  ) ) return false;
          if (!(pfjet_chf_ >   0.  ) ) return false;
          if (!(pfjet_cef_ <   0.99) ) return false;
        }
      }
      else if( pfjet_eta > 2.7 && pfjet_eta <= 3.0 )
      {
        if (!(pfjet_nef_ < 0.9 ) ) return false;
        if (!(pfjet_nm_  > 2   ) ) return false;
      }
      else if( pfjet_eta > 3.0 )
      {
        if (!(pfjet_nef_ < 0.9 ) ) return false;
        if (!(pfjet_nm_  > 10  ) ) return false;
      }

      return true;
    }

    //______________________________________________________________________________________
    bool isMediumBJet(ObjUtil::Jet& jet)
    {
      if ( !(jet.p4.Pt() > 20.        ) ) return false;
      if ( !(fabs(jet.p4.Eta()) < 2.4 ) ) return false;
      if ( !(jet.btagCSV > 0.8484     ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isLooseBJet(ObjUtil::Jet& jet)
    {
      if ( !(jet.p4.Pt() > 20.        ) ) return false;
      if ( !(fabs(jet.p4.Eta()) < 2.4 ) ) return false;
      if ( !(jet.btagCSV > 0.5426     ) ) return false;
      return true;
    }


    //______________________________________________________________________________________
    int removeJetsOverlappingLeptons(ObjUtil::Jets& jets, ObjUtil::Leptons& leptons)
    {

      /// return number of jets that are removed
      int njet_removed = 0;

      ObjUtil::Jets ORedjets;
      for (auto& jet : jets)
      {
        bool pass = true;
        for (auto& lepton : leptons)
        {
          if (jet.p4.DeltaR(lepton.p4) < 0.3)
            pass = false;
        }
        if (pass)
          ORedjets.push_back(jet);
        else
          njet_removed++;
      }
      jets = ObjUtil::Jets(ORedjets);

      return njet_removed;
    }

  }

  #include "DittoHistUtil.cxx"
  #include "DittoTreeUtil.cxx"

}

//eof
//
//	    //______________________________________________________________________________________
//	    /// Multiplicity variables
//	    void fillNLep      (string prefix , ObjUtil::AnalysisData& a) { PlotUtil::plot1D("nlep"  , a.leptons.size() , a.wgt , a.hist_db , "N_{lep}" , 10 , 0. , 10. , prefix); }
//	    void fillNJet      (string prefix , ObjUtil::AnalysisData& a) { PlotUtil::plot1D("njet"  , a.jets.size()    , a.wgt , a.hist_db , "N_{jet}" , 10 , 0. , 10. , prefix); }
//	    void fillNBjet     (string prefix , ObjUtil::AnalysisData& a) { PlotUtil::plot1D("nbjet" , a.bjets.size()   , a.wgt , a.hist_db , "N_{b-jet}" , 10 , 0. , 10. , prefix); }
//	    /// Single object kinematics
//	    void fillMET       (string prefix , ObjUtil::AnalysisData& a) { PlotUtil::plot1D("met"       , a.met.p4.Pt()          , a.wgt , a.hist_db , "MET [GeV]" , 180 , 0. , 500.   , prefix); }
//	    void fillLepPt     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep  = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)  PlotUtil ::plot1D(TString::Format("lep%dpt"   , ilep).Data()  , a.leptons[ilep].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, lep%d} [GeV]"  , ilep).Data()  , 180     , 0.      , 200. - ilep * 20  , prefix); }
//	    void fillJetPt     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ijet  = 0; ijet < a.jets   .size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)  PlotUtil ::plot1D(TString::Format("jet%dpt"   , ijet).Data()  , a.jets   [ijet].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, jet%d} [GeV]"  , ijet).Data()  , 180     , 0.      , 200. - ijet * 20  , prefix); }
//	    void fillBJetPt    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ibjet = 0; ibjet < a.bjets .size() && ibjet< NMAX_INDIVD_OBJ_TO_PLOT; ++ibjet) PlotUtil ::plot1D(TString::Format("bjet%dpt"  , ibjet).Data() , a.bjets   [ibjet].p4.Pt()  , a.wgt , a.hist_db , TString::Format("p_{T, bjet%d} [GeV]" , ibjet).Data() , 180     , 0.      , 200. - ibjet * 20 , prefix); }
//	    void fillLepEta    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep  = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)  PlotUtil ::plot1D(TString::Format("lep%deta"  , ilep).Data()  , a.leptons[ilep].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{lep%d}"        , ilep).Data()  , 180     , -3.     , 3.     , prefix); }
//	    void fillJetEta    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ijet  = 0; ijet < a.jets   .size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)  PlotUtil ::plot1D(TString::Format("jet%deta"  , ijet).Data()  , a.jets   [ijet].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{jet%d}"        , ijet).Data()  , 180     , -5.     , 5.     , prefix); }
//	    void fillBJetEta   (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ibjet = 0; ibjet < a.bjets .size() && ibjet< NMAX_INDIVD_OBJ_TO_PLOT; ++ibjet) PlotUtil ::plot1D(TString::Format("bjet%deta" , ibjet).Data() , a.bjets   [ibjet].p4.Eta() , a.wgt , a.hist_db , TString::Format("#eta_{bjet%d}"       , ibjet).Data() , 180     , -5.     , 5.     , prefix); }
//	    void fillLepPhi    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep  = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)  PlotUtil ::plot1D(TString::Format("lep%dphi"  , ilep).Data()  , a.leptons[ilep].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{lep%d}"        , ilep).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
//	    void fillJetPhi    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ijet  = 0; ijet < a.jets   .size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)  PlotUtil ::plot1D(TString::Format("jet%dphi"  , ijet).Data()  , a.jets   [ijet].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{jet%d}"        , ijet).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
//	    void fillBJetPhi   (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ibjet = 0; ibjet < a.bjets .size() && ibjet< NMAX_INDIVD_OBJ_TO_PLOT; ++ibjet) PlotUtil ::plot1D(TString::Format("bjet%dphi" , ibjet).Data() , a.bjets   [ibjet].p4.Phi() , a.wgt , a.hist_db , TString::Format("#phi_{bjet%d}"       , ibjet).Data() , 180     , -3.1416 , 3.1416 , prefix); }
//	    /// Di object kinematics (GeV scales)
//	    void fillMll       (string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 2) PlotUtil::plot1D("mll"       , VarUtil::Mll(a)        , a.wgt , a.hist_db , "M_{#ell#ell} [GeV]" , 180 , 0. , 180.   , prefix); }
//	    void fillVBFMjj    (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("vbfmjj"    , VarUtil::Mjj(a)        , a.wgt , a.hist_db , "M_{jj} [GeV]" , 180 , 0. , 2500.  , prefix); }
//	    void fillVBFMbb    (string prefix , ObjUtil::AnalysisData& a) { if (a.bjets  .size() >= 2) PlotUtil::plot1D("vbfmbb"    , VarUtil::Mbb(a)        , a.wgt , a.hist_db , "M_{bb} [GeV]" , 180 , 0. , 2500.  , prefix); }
//	    void fillPtjj      (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("ptjj"      , VarUtil::Ptjj(a)       , a.wgt , a.hist_db , "p_{T,jj} [GeV]" , 180 , 0. , 1000.  , prefix); }
//	    void fillPtbb      (string prefix , ObjUtil::AnalysisData& a) { if (a.bjets  .size() >= 2) PlotUtil::plot1D("ptbb"      , VarUtil::Ptbb(a)       , a.wgt , a.hist_db , "p_{T,bb} [GeV]" , 180 , 0. , 1000.  , prefix); }
//	    void fillMjjW      (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("mjjw"      , VarUtil::MjjWmass(a)   , a.wgt , a.hist_db , "M_{jj,close-to-W} [GeV]" , 180 , 0. , 180.   , prefix); }
//	    void fillMjj       (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("mjj"       , VarUtil::Mjj(a)        , a.wgt , a.hist_db , "M_{jj} [GeV]" , 180 , 0. , 180.   , prefix); }
//	    void fillMT        (string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 1) PlotUtil::plot1D("mt"        , VarUtil::MT(a)         , a.wgt , a.hist_db , "M_{T} [GeV]" , 180 , 0. , 180.   , prefix); }
//	    void fillHT        (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 1) PlotUtil::plot1D("ht"        , VarUtil::HT(a)         , a.wgt , a.hist_db , "H_{T} [GeV]" , 180 , 0. , 1200.  , prefix); }
//	    void fillMTll      (string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 2) PlotUtil::plot1D("mtll"      , VarUtil::MTll(a)       , a.wgt , a.hist_db , "M_{T,ll} [GeV]" , 180 , 0. , 400.   , prefix); }
//	    void fillMljClose  (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 1) if (a.leptons.size() >= 1)PlotUtil::plot1D("mljclose"  , VarUtil::MljClosest(a)   , a.wgt , a.hist_db , "M_{lj,close} [GeV]" , 180 , 0. , 400.   , prefix); }
//	    /// Di object kinematics (angular)
//	    void fillDPhill    (string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 2) PlotUtil::plot1D("dphill"    , VarUtil::DPhill(a)     , a.wgt , a.hist_db , "#Delta#phi_{#ell#ell}" , 180 , 0. , 3.1416 , prefix); }
//	    void fillDEtajj    (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("detajj"    , VarUtil::DEtajj(a)     , a.wgt , a.hist_db , "#Delta#eta_{jj}" , 180 , 0. , 9.     , prefix); }
//	    void fillDRjj      (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("drjj"      , VarUtil::DRjj(a)       , a.wgt , a.hist_db , "#DeltaR{jj}" , 180 , 0. , 9.   , prefix); }
//	    void fillDEtabb    (string prefix , ObjUtil::AnalysisData& a) { if (a.bjets  .size() >= 2) PlotUtil::plot1D("detabb"    , VarUtil::DEtabb(a)     , a.wgt , a.hist_db , "#Delta#phi_{bb}" , 180 , 0. , 9.     , prefix); }
//	    void fillDPhiLepMET(string prefix , ObjUtil::AnalysisData& a) { if (a.leptons.size() >= 1) PlotUtil::plot1D("dphilepmet", VarUtil::DPhiLepMET(a) , a.wgt , a.hist_db , "#Delta#phi_{#ell,MET}" , 5   , 0. , 3.1416 , prefix); }
//	    void fillDRjjW     (string prefix , ObjUtil::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("drjjw"     , VarUtil::DRjjWmass(a)  , a.wgt , a.hist_db , "#DeltaR{jj,close-to-W}" , 180 , 0. , 9.   , prefix); }
//	    /// Single object ID-related
//	    void fillLepDz          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%ddz"        , ilep).Data() , a.leptons[ilep].dz                                   , a.wgt , a.hist_db , "" , 180 , 0. , 0.05, prefix); }
//	    void fillLepDxy         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%ddxy"       , ilep).Data() , a.leptons[ilep].dxy                                  , a.wgt , a.hist_db , "" , 180 , 0. , 0.01, prefix); }
//	    void fillLepIp3d        (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dip3d"      , ilep).Data() , a.leptons[ilep].ip3d                                 , a.wgt , a.hist_db , "" , 180 , 0. , 0.05, prefix); }
//	    void fillLepSip3d       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dsip3d"     , ilep).Data() , a.leptons[ilep].sip3d                                , a.wgt , a.hist_db , "" , 180 , 0. , 10 , prefix); }
//	    void fillLepRelIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%drelIso03"  , ilep).Data() , a.leptons[ilep].relIso03                             , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
//	    void fillLepAbsIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dabsIso03"  , ilep).Data() , a.leptons[ilep].relIso03 * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180 , 0. , 20. , prefix); }
//	    void fillLepRelIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%drelIso03EA", ilep).Data() , a.leptons[ilep].relIso03EA                           , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
//	    void fillLepAbsIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dabsIso03EA", ilep).Data() , a.leptons[ilep].relIso03EA * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180 , 0. , 20. , prefix); }
//	    void fillLepRelIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%drelIso03EA", ilep).Data() , a.leptons[ilep].relIso03EA                           , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
//	    void fillLepAbsIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dabsIso03EA", ilep).Data() , a.leptons[ilep].relIso03EA * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180 , 0. , 20. , prefix); }
//	    void fillLepRelIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%drelIso03DB", ilep).Data() , a.leptons[ilep].relIso03DB                           , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
//	    void fillLepAbsIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dabsIso03DB", ilep).Data() , a.leptons[ilep].relIso03DB * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180 , 0. , 20. , prefix); }
//	    void fillLepMiniIso     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dminiIso03" , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EA                    , a.wgt , a.hist_db , "" , 1080 , 0. , 1.5, prefix); }
//	    void fillLepPtRel       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dptrel"     , ilep).Data() , a.leptons[ilep].ptRel                                , a.wgt , a.hist_db , "" , 180 , 0. , 30., prefix); }
//	    void fillLepPtRatio     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dptratio"   , ilep).Data() , a.leptons[ilep].ptRatio                              , a.wgt , a.hist_db , "" , 180 , 0.5, 1.0, prefix); }
//	    void fillLepIsFromW     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dIsFromW"   , ilep).Data() , (a.leptons[ilep].isFromX) & (1<<0)                   , a.wgt , a.hist_db , "" ,   2 , 0. , 2  , prefix); }
//	    /// Leptons from W
//	    void fillIsFromWLepPt          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil ::plot1D(TString::Format("lep%dpt"   , ilep).Data()  , a.leptons[ilep].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, lep%d} [GeV]"  , ilep).Data()  , 180     , 0.      , 200. - ilep * 20  , prefix); }
//	    void fillIsFromWLepEta         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil ::plot1D(TString::Format("lep%deta"  , ilep).Data()  , a.leptons[ilep].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{lep%d}"        , ilep).Data()  , 180     , -3.     , 3.     , prefix); }
//	    void fillIsFromWLepPhi         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil ::plot1D(TString::Format("lep%dphi"  , ilep).Data()  , a.leptons[ilep].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{lep%d}"        , ilep).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
//	    void fillIsFromWLepDz          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%ddz"           , ilep).Data() , a.leptons[ilep].dz                                     , a.wgt , a.hist_db , "" , 180  , 0.  , 0.05 , prefix); }
//	    void fillIsFromWLepDxy         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%ddxy"          , ilep).Data() , a.leptons[ilep].dxy                                    , a.wgt , a.hist_db , "" , 180  , 0.  , 0.01 , prefix); }
//	    void fillIsFromWLepIp3d        (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dip3d"         , ilep).Data() , a.leptons[ilep].ip3d                                   , a.wgt , a.hist_db , "" , 180  , 0.  , 0.05 , prefix); }
//	    void fillIsFromWLepSip3d       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dsip3d"        , ilep).Data() , a.leptons[ilep].sip3d                                  , a.wgt , a.hist_db , "" , 180  , 0.  , 10   , prefix); }
//	    void fillIsFromWLepRelIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso03"     , ilep).Data() , a.leptons[ilep].relIso03                               , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsFromWLepAbsIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso03"     , ilep).Data() , a.leptons[ilep].relIso03 * a.leptons[ilep].p4.Pt()     , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsFromWLepRelIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso03EA"   , ilep).Data() , a.leptons[ilep].relIso03EA                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsFromWLepAbsIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso03EA"   , ilep).Data() , a.leptons[ilep].relIso03EA * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsFromWLepRelIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso03EAv2" , ilep).Data() , a.leptons[ilep].relIso03EAv2                           , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsFromWLepAbsIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso03EAv2" , ilep).Data() , a.leptons[ilep].relIso03EAv2 * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsFromWLepRelIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso03DB"   , ilep).Data() , a.leptons[ilep].relIso03DB                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsFromWLepAbsIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso03DB"   , ilep).Data() , a.leptons[ilep].relIso03DB * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsFromWLepRelIso04EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso04EA"   , ilep).Data() , a.leptons[ilep].relIso04EA                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsFromWLepAbsIso04EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso04EA"   , ilep).Data() , a.leptons[ilep].relIso04EA * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsFromWLepRelIso04EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso04EAv2" , ilep).Data() , a.leptons[ilep].relIso04EAv2                           , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsFromWLepAbsIso04EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso04EAv2" , ilep).Data() , a.leptons[ilep].relIso04EAv2 * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsFromWLepRelIso04DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%drelIso04DB"   , ilep).Data() , a.leptons[ilep].relIso04DB                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsFromWLepAbsIso04DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dabsIso04DB"   , ilep).Data() , a.leptons[ilep].relIso04DB * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsFromWLepMiniIso     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dminiIso"      , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EA                      , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsFromWLepMiniIsov2   (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dminiIsov2"    , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EAv2                    , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsFromWLepPtRel       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dptrel"        , ilep).Data() , a.leptons[ilep].ptRel                                  , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsFromWLepPtRatio     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dptratio"      , ilep).Data() , a.leptons[ilep].ptRatio                                , a.wgt , a.hist_db , "" , 180  , 0.5 , 1.0  , prefix); }
//	    void fillIsFromWLepIsFromW     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (a.leptons[ilep].isFromX & (1<<0)) PlotUtil::plot1D(TString::Format("lep%dIsFromW"      , ilep).Data() , (a.leptons[ilep].isFromX) & (1<<0)                     , a.wgt , a.hist_db , "" , 2    , 0.  , 2    , prefix); }
//	    /// Leptons Is not from W
//	    void fillIsNotFromWLepPt          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil ::plot1D(TString::Format("lep%dpt"   , ilep).Data()  , a.leptons[ilep].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, lep%d} [GeV]"  , ilep).Data()  , 180     , 0.      , 200. - ilep * 20  , prefix); }
//	    void fillIsNotFromWLepEta         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil ::plot1D(TString::Format("lep%deta"  , ilep).Data()  , a.leptons[ilep].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{lep%d}"        , ilep).Data()  , 180     , -3.     , 3.     , prefix); }
//	    void fillIsNotFromWLepPhi         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil ::plot1D(TString::Format("lep%dphi"  , ilep).Data()  , a.leptons[ilep].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{lep%d}"        , ilep).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
//	    void fillIsNotFromWLepDz          (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%ddz"           , ilep).Data() , a.leptons[ilep].dz                                     , a.wgt , a.hist_db , "" , 180  , 0.  , 0.05 , prefix); }
//	    void fillIsNotFromWLepDxy         (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%ddxy"          , ilep).Data() , a.leptons[ilep].dxy                                    , a.wgt , a.hist_db , "" , 180  , 0.  , 0.01 , prefix); }
//	    void fillIsNotFromWLepIp3d        (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dip3d"         , ilep).Data() , a.leptons[ilep].ip3d                                   , a.wgt , a.hist_db , "" , 180  , 0.  , 0.05 , prefix); }
//	    void fillIsNotFromWLepSip3d       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dsip3d"        , ilep).Data() , a.leptons[ilep].sip3d                                  , a.wgt , a.hist_db , "" , 180  , 0.  , 10   , prefix); }
//	    void fillIsNotFromWLepRelIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso03"     , ilep).Data() , a.leptons[ilep].relIso03                               , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsNotFromWLepAbsIso03    (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso03"     , ilep).Data() , a.leptons[ilep].relIso03 * a.leptons[ilep].p4.Pt()     , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsNotFromWLepRelIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso03EA"   , ilep).Data() , a.leptons[ilep].relIso03EA                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsNotFromWLepAbsIso03EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso03EA"   , ilep).Data() , a.leptons[ilep].relIso03EA * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsNotFromWLepRelIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso03EAv2" , ilep).Data() , a.leptons[ilep].relIso03EAv2                           , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsNotFromWLepAbsIso03EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso03EAv2" , ilep).Data() , a.leptons[ilep].relIso03EAv2 * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsNotFromWLepRelIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso03DB"   , ilep).Data() , a.leptons[ilep].relIso03DB                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsNotFromWLepAbsIso03DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso03DB"   , ilep).Data() , a.leptons[ilep].relIso03DB * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsNotFromWLepRelIso04EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso04EA"   , ilep).Data() , a.leptons[ilep].relIso04EA                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsNotFromWLepAbsIso04EA  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso04EA"   , ilep).Data() , a.leptons[ilep].relIso04EA * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsNotFromWLepRelIso04EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso04EAv2" , ilep).Data() , a.leptons[ilep].relIso04EAv2                           , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsNotFromWLepAbsIso04EAv2(string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso04EAv2" , ilep).Data() , a.leptons[ilep].relIso04EAv2 * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsNotFromWLepRelIso04DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%drelIso04DB"   , ilep).Data() , a.leptons[ilep].relIso04DB                             , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsNotFromWLepAbsIso04DB  (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dabsIso04DB"   , ilep).Data() , a.leptons[ilep].relIso04DB * a.leptons[ilep].p4.Pt()   , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsNotFromWLepMiniIso     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dminiIso"      , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EA                      , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsNotFromWLepMiniIsov2   (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dminiIso"      , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EAv2                    , a.wgt , a.hist_db , "" , 1080 , 0.  , 0.25  , prefix); }
//	    void fillIsNotFromWLepPtRel       (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dptrel"        , ilep).Data() , a.leptons[ilep].ptRel                                  , a.wgt , a.hist_db , "" , 180  , 0.  , 30.  , prefix); }
//	    void fillIsNotFromWLepPtRatio     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dptratio"      , ilep).Data() , a.leptons[ilep].ptRatio                                , a.wgt , a.hist_db , "" , 180  , 0.5 , 1.0  , prefix); }
//	    void fillIsNotFromWLepIsFromW     (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) if (!(a.leptons[ilep].isFromX & (1<<0))) PlotUtil::plot1D(TString::Format("lep%dIsFromW"      , ilep).Data() , (a.leptons[ilep].isFromX) & (1<<0)                     , a.wgt , a.hist_db , "" , 2    , 0.  , 2    , prefix); }
//	    // Jet single object
//	    void fillJetID        (string prefix , ObjUtil::AnalysisData& a) { for (unsigned int ijet = 0; ijet < a.jets   .size(); ++ijet) PlotUtil::plot1D(TString::Format("jet%dID"        , ijet).Data() , a.jets   [ijet].id                                   , a.wgt , a.hist_db , "" ,   2 , 0. , 30 , prefix); }

