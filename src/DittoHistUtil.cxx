// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#define NMAX_INDIVD_OBJ_TO_PLOT 3

namespace HistUtil
{

  //______________________________________________________________________________________
  string catPrefix(string prefix1, string prefix2)
  {
    return TString::Format("%s_%s_", prefix1.c_str(), prefix2.c_str()).Data();
  }

  //______________________________________________________________________________________
  void fillCutflow(string prefix, ObjUtil::AnalysisData& a, int ibin, const char* label)
  {
    PlotUtil::plot1D("cutflow"   , ibin, a.wgt, a.hist_db, "", 20, 0., 20., prefix);
    PlotUtil::plot1D("rawcutflow", ibin,    1., a.hist_db, "", 20, 0., 20., prefix);
    if (strlen(label) != 0)
    {
      PlotUtil::get("cutflow", a.hist_db, prefix)->GetXaxis()->SetBinLabel(ibin+1, label);
      PlotUtil::get("rawcutflow", a.hist_db, prefix)->GetXaxis()->SetBinLabel(ibin+1, label);
    }
  }

  //______________________________________________________________________________________
  void fillCounter(string prefix, ObjUtil::AnalysisData& a, int ibin, const char* label)
  {
    PlotUtil::plot1D("counter"   , ibin, a.wgt, a.hist_db, "", 20, 0., 20., prefix);
    PlotUtil::plot1D("rawcounter", ibin,    1., a.hist_db, "", 20, 0., 20., prefix);
    if (strlen(label) != 0)
    {
      PlotUtil::get("counter", a.hist_db, prefix)->GetXaxis()->SetBinLabel(ibin+1, label);
      PlotUtil::get("rawcounter", a.hist_db, prefix)->GetXaxis()->SetBinLabel(ibin+1, label);
    }
  }

  //______________________________________________________________________________________
  void fillMET(string prefix, ObjUtil::AnalysisData& a)
  {
    PlotUtil::plot1D("met", a.met.p4.Pt(), a.wgt, a.hist_db , "MET [GeV]", 180, 0., 500., prefix);
  }

  //______________________________________________________________________________________
  void fillLeps(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)
    {
      PlotUtil::plot1D(TString::Format("lep%dpt"    , ilep).Data() , a.leptons[ilep].p4.Pt()  , a.wgt , a.hist_db , TString::Format("p_{T, lep%d} [GeV]" , ilep).Data() , 180     , 0.      , 200. - ilep * 20 , prefix);
      PlotUtil::plot1D(TString::Format("lep%deta"   , ilep).Data() , a.leptons[ilep].p4.Eta() , a.wgt , a.hist_db , TString::Format("#eta_{lep%d}"       , ilep).Data() , 180     , -3.     , 3.               , prefix);
      PlotUtil::plot1D(TString::Format("lep%dphi"   , ilep).Data() , a.leptons[ilep].p4.Phi() , a.wgt , a.hist_db , TString::Format("#phi_{lep%d}"       , ilep).Data() , 180     , -3.1416 , 3.1416           , prefix);
      PlotUtil::plot1D(TString::Format("lep%dpdgid" , ilep).Data() , a.leptons[ilep].p4.Phi() , a.wgt , a.hist_db , TString::Format("pdgid_{lep%d}"      , ilep).Data() ,  32     , -16     , 16               , prefix);
    }
  }

  //______________________________________________________________________________________
  void fillJets(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ijet = 0; ijet < a.jets.size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)
    {
      PlotUtil::plot1D(TString::Format("jet%dpt"  , ijet).Data() , a.jets[ijet].p4.Pt()  , a.wgt , a.hist_db , TString::Format("p_{T, jet%d} [GeV]" , ijet).Data() , 180     , 0.      , 200. - ijet * 20 , prefix);
      PlotUtil::plot1D(TString::Format("jet%deta" , ijet).Data() , a.jets[ijet].p4.Eta() , a.wgt , a.hist_db , TString::Format("#eta_{jet%d}"       , ijet).Data() , 180     , -3.     , 3.               , prefix);
      PlotUtil::plot1D(TString::Format("jet%dphi" , ijet).Data() , a.jets[ijet].p4.Phi() , a.wgt , a.hist_db , TString::Format("#phi_{jet%d}"       , ijet).Data() , 180     , -3.1416 , 3.1416           , prefix);
    }
  }

  //______________________________________________________________________________________
  void fillDiLepVars(string prefix, ObjUtil::AnalysisData& a, unsigned int ilep, unsigned int jlep)
  {
    if (a.leptons.size() < ilep || a.leptons.size() < jlep)
      return;
    PlotUtil::plot1D(TString::Format("mll%d%d"   , ilep, jlep).Data() , VarUtil::Mass(a.leptons[ilep], a.leptons[jlep]), a.wgt , a.hist_db , "", 180, 0.,180.    , prefix);
    PlotUtil::plot1D(TString::Format("detall%d%d", ilep, jlep).Data() , VarUtil::DEta(a.leptons[ilep], a.leptons[jlep]), a.wgt , a.hist_db , "", 180, 0.,  5.    , prefix);
    PlotUtil::plot1D(TString::Format("dphill%d%d", ilep, jlep).Data() , VarUtil::DPhi(a.leptons[ilep], a.leptons[jlep]), a.wgt , a.hist_db , "", 180, 0.,  3.1416, prefix);
    PlotUtil::plot1D(TString::Format("drll%d%d"  , ilep, jlep).Data() , VarUtil::DR  (a.leptons[ilep], a.leptons[jlep]), a.wgt , a.hist_db , "", 180, 0.,  9.    , prefix);
    PlotUtil::plot1D(TString::Format("ptll%d%d"  , ilep, jlep).Data() , VarUtil::Pt  (a.leptons[ilep], a.leptons[jlep]), a.wgt , a.hist_db , "", 180, 0.,180.    , prefix);
    PlotUtil::plot1D(TString::Format("dptll%d%d" , ilep, jlep).Data() , VarUtil::DPt (a.leptons[ilep], a.leptons[jlep]), a.wgt , a.hist_db , "", 180, 0.,180.    , prefix);
    PlotUtil::plot1D(TString::Format("mtll%d%d"  , ilep, jlep).Data() , VarUtil::MT  (a.leptons[ilep], a.leptons[jlep]), a.wgt , a.hist_db , "", 180, 0.,180.    , prefix);
  }

  //______________________________________________________________________________________
  void fillDiJetVars(string prefix, ObjUtil::AnalysisData& a, unsigned int ijet, unsigned int jjet)
  {
    if (a.jets.size() < ijet || a.jets.size() < jjet)
      return;
    PlotUtil::plot1D(TString::Format("mjj%d%d"   , ijet, jjet).Data() , VarUtil::Mass(a.jets[ijet], a.jets[jjet]), a.wgt , a.hist_db , "", 180, 0.,180.    , prefix);
    PlotUtil::plot1D(TString::Format("detajj%d%d", ijet, jjet).Data() , VarUtil::DEta(a.jets[ijet], a.jets[jjet]), a.wgt , a.hist_db , "", 180, 0.,  5.    , prefix);
    PlotUtil::plot1D(TString::Format("dphijj%d%d", ijet, jjet).Data() , VarUtil::DPhi(a.jets[ijet], a.jets[jjet]), a.wgt , a.hist_db , "", 180, 0.,  3.1416, prefix);
    PlotUtil::plot1D(TString::Format("drjj%d%d"  , ijet, jjet).Data() , VarUtil::DR  (a.jets[ijet], a.jets[jjet]), a.wgt , a.hist_db , "", 180, 0.,  9.    , prefix);
    PlotUtil::plot1D(TString::Format("ptjj%d%d"  , ijet, jjet).Data() , VarUtil::Pt  (a.jets[ijet], a.jets[jjet]), a.wgt , a.hist_db , "", 180, 0.,180.    , prefix);
    PlotUtil::plot1D(TString::Format("dptjj%d%d" , ijet, jjet).Data() , VarUtil::DPt (a.jets[ijet], a.jets[jjet]), a.wgt , a.hist_db , "", 180, 0.,180.    , prefix);
    PlotUtil::plot1D(TString::Format("mtjj%d%d"  , ijet, jjet).Data() , VarUtil::MT  (a.jets[ijet], a.jets[jjet]), a.wgt , a.hist_db , "", 180, 0.,180.    , prefix);
  }

  //______________________________________________________________________________________
  void fillDiLepChan(string prefix, ObjUtil::AnalysisData& a)
  {
    if (a.leptons.size() < 2)
      return;
    int pdgidprod = a.leptons[0].pdgId * a.leptons[1].pdgId;
    int pdgidprodcategory = -1;
    switch (pdgidprod)
    {
      case -121: pdgidprodcategory = 0; break;
      case -143: pdgidprodcategory = 1; break;
      case -169: pdgidprodcategory = 2; break;
      case  121: pdgidprodcategory = 3; break;
      case  143: pdgidprodcategory = 4; break;
      case  169: pdgidprodcategory = 5; break;
      default:   pdgidprodcategory = 6; break;
    }
    PlotUtil::plot1D("pdgIdProductTwoLead", pdgidprodcategory, a.wgt , a.hist_db , "", 7, 0, 7, prefix);
  }

  //______________________________________________________________________________________
  void fillMjj(string prefix, ObjUtil::AnalysisData& a)
  {
//	    PlotUtil::plot1D("mjj", VarUtil::Mjj(a), a.wgt, a.hist_db , "Mjj [GeV]", 180, 0., 1500., prefix);
  }

  //______________________________________________________________________________________
  void fillMjjWithMaxDEtajj(string prefix, ObjUtil::AnalysisData& a)
  {
//	    PlotUtil::plot1D("mjjwithmaxdetajj", VarUtil::Mjj(a), a.wgt, a.hist_db , "Mjj [GeV]", 180, 0., 1500., prefix);
  }

  //______________________________________________________________________________________
  void fillLepMTs(string prefix, ObjUtil::AnalysisData& a)
  {
    float minmt = -999;
    float maxmt = -999;
    float summt = -999;
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      float tmpmt = VarUtil::MT(lepton, a.met);
      if (ilep == 0)
      {
        minmt = tmpmt;
        maxmt = tmpmt;
        summt = tmpmt;
      }
      else
      {
        if (tmpmt < minmt)
          minmt = tmpmt;
        if (tmpmt > maxmt)
          maxmt = tmpmt;
        summt += tmpmt;
      }
      PlotUtil::plot1D(TString::Format("lep%dmt", ilep).Data(), tmpmt, a.wgt, a.hist_db , "", 180, 0., 180, prefix);
    }
    if (a.leptons.size() > 1)
    {
      PlotUtil::plot1D("lepminmt", minmt      , a.wgt, a.hist_db , "", 180, 0., 180, prefix);
      PlotUtil::plot1D("lepmaxmt", maxmt      , a.wgt, a.hist_db , "", 180, 0., 220, prefix);
      PlotUtil::plot1D("lepdmt"  , maxmt-minmt, a.wgt, a.hist_db , "", 180, 0., 180, prefix);
      PlotUtil::plot1D("lepsummt", summt      , a.wgt, a.hist_db , "", 180, 0., 300, prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepDPhiljs(string prefix, ObjUtil::AnalysisData& a)
  {
    float mindphilj = -999;
    float maxdphilj = -999;
    float sumdphilj = -999;
    for (unsigned int ijet = 0; ijet < a.jets.size(); ++ijet)
    {
      for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
      {
        ObjUtil::Lepton lepton = a.leptons[ilep];
        ObjUtil::Jet jet = a.jets[ilep];
        float tmpdphilj = VarUtil::DPhi(lepton, jet);
        if (ilep == 0 && ijet == 0)
        {
          mindphilj = tmpdphilj;
          maxdphilj = tmpdphilj;
          sumdphilj = tmpdphilj;
        }
        else
        {
          if (tmpdphilj < mindphilj)
            mindphilj = tmpdphilj;
          if (tmpdphilj > maxdphilj)
            maxdphilj = tmpdphilj;
          sumdphilj += tmpdphilj;
        }
        PlotUtil::plot1D(TString::Format("lep%djet%ddphilj", ilep, ijet).Data(), tmpdphilj, a.wgt, a.hist_db , "", 180, 0., 3.1416, prefix);
      }
    }
    if (a.leptons.size() > 1)
    {
      PlotUtil::plot1D("lepmindphilj" , mindphilj           , a.wgt , a.hist_db , "" , 180 , 0. , 3.1416 , prefix);
      PlotUtil::plot1D("lepmaxdphilj" , maxdphilj           , a.wgt , a.hist_db , "" , 180 , 0. , 3.1416 , prefix);
      PlotUtil::plot1D("lepddphilj"   , maxdphilj-mindphilj , a.wgt , a.hist_db , "" , 180 , 0. , 3.1416 , prefix);
      PlotUtil::plot1D("lepsumdphilj" , sumdphilj           , a.wgt , a.hist_db , "" , 180 , 0. , 3.1416 , prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepMljs(string prefix, ObjUtil::AnalysisData& a)
  {
    float minmlj = -999;
    float maxmlj = -999;
    float summlj = -999;
    for (unsigned int ijet = 0; ijet < a.jets.size(); ++ijet)
    {
      for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
      {
        ObjUtil::Lepton lepton = a.leptons[ilep];
        ObjUtil::Jet jet = a.jets[ilep];
        float tmpmlj = VarUtil::Mass(lepton, jet);
        if (ilep == 0 && ijet == 0)
        {
          minmlj = tmpmlj;
          maxmlj = tmpmlj;
          summlj = tmpmlj;
        }
        else
        {
          if (tmpmlj < minmlj)
            minmlj = tmpmlj;
          if (tmpmlj > maxmlj)
            maxmlj = tmpmlj;
          summlj += tmpmlj;
        }
        PlotUtil::plot1D(TString::Format("lep%djet%dmlj", ilep, ijet).Data(), tmpmlj, a.wgt, a.hist_db , "", 180, 0., 360, prefix);
      }
    }
    if (a.leptons.size() > 1)
    {
      PlotUtil::plot1D("lepminmlj" , minmlj         , a.wgt , a.hist_db , "" , 180 , 0. , 360, prefix);
      PlotUtil::plot1D("lepmaxmlj" , maxmlj         , a.wgt , a.hist_db , "" , 180 , 0. , 450, prefix);
      PlotUtil::plot1D("lepdmlj"   , maxmlj-minmlj , a.wgt , a.hist_db , ""  , 180 , 0. , 360, prefix);
      PlotUtil::plot1D("lepsummlj" , summlj         , a.wgt , a.hist_db , "" , 180 , 0. , 700, prefix);
    }
  }

//	  //______________________________________________________________________________________
//	  void fillLepMlvjs(string prefix, ObjUtil::AnalysisData& a)
//	  {
//	    float minmlvj = -999;
//	    float maxmlvj = -999;
//	    float summlvj = -999;
//	    for (unsigned int ijet = 0; ijet < a.jets.size(); ++ijet)
//	    {
//	      for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
//	      {
//	        ObjUtil::Lepton lepton = a.leptons[ilep];
//	        ObjUtil::Jet jet = a.jets[ilep];
//	        float tmpmlvj = VarUtil::Mlvj(a, ilep, ijet);
//	        if (ilep == 0 && ijet == 0)
//	        {
//	          minmlvj = tmpmlvj;
//	          maxmlvj = tmpmlvj;
//	          summlvj = tmpmlvj;
//	        }
//	        else
//	        {
//	          if (tmpmlvj < minmlvj)
//	            minmlvj = tmpmlvj;
//	          if (tmpmlvj > maxmlvj)
//	            maxmlvj = tmpmlvj;
//	          summlvj += tmpmlvj;
//	        }
//	        PlotUtil::plot1D(TString::Format("lep%djet%dmlvj", ilep, ijet).Data(), tmpmlvj, a.wgt, a.hist_db , "", 180, 0., 360, prefix);
//	      }
//	    }
//	    if (a.leptons.size() > 1)
//	    {
//	      PlotUtil::plot1D("lepminmlvj" , minmlvj         , a.wgt , a.hist_db , "" , 180 , 0. , 360 , prefix);
//	      PlotUtil::plot1D("lepmaxmlvj" , maxmlvj         , a.wgt , a.hist_db , "" , 180 , 0. , 450 , prefix);
//	      PlotUtil::plot1D("lepdmlvj"   , maxmlvj-minmlvj , a.wgt , a.hist_db , "" , 180 , 0. , 360 , prefix);
//	      PlotUtil::plot1D("lepsummlvj" , summlvj         , a.wgt , a.hist_db , "" , 180 , 0. , 700 , prefix);
//	    }
//	  }

  //______________________________________________________________________________________
  void fillLepSumPt(string prefix, ObjUtil::AnalysisData& a)
  {
//	    PlotUtil::plot1D("lepsumpt", VarUtil::LepSumPt(a), a.wgt, a.hist_db , "#Sum p_{T,lep} [GeV]", 180, 0., 500., prefix);
  }

  //______________________________________________________________________________________
  void fillLepRelIso03EA(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      PlotUtil::plot1D(TString::Format("lep%d_reliso03EA", ilep).Data(), lepton.relIso03EA, a.wgt, a.hist_db , "", 10000, 0., 0.25, prefix);
      PlotUtil::plot1D("lep_reliso03EA", lepton.relIso03EA, a.wgt, a.hist_db , "", 10000, 0., 0.25, prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepAbsIso03EA(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      PlotUtil::plot1D(TString::Format("lep%d_absiso03EA", ilep).Data(), lepton.relIso03EA * lepton.p4.Pt(), a.wgt, a.hist_db , "", 10000, 0., 7., prefix);
      PlotUtil::plot1D("lep_absiso03EA", lepton.relIso03EA * lepton.p4.Pt(), a.wgt, a.hist_db , "", 10000, 0., 7., prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepRelIso04EA(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      PlotUtil::plot1D(TString::Format("lep%d_reliso04EA", ilep).Data(), lepton.relIso04EA, a.wgt, a.hist_db , "", 10000, 0., 0.25, prefix);
      PlotUtil::plot1D("lep_reliso04EA", lepton.relIso04EA, a.wgt, a.hist_db , "", 10000, 0., 0.25, prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepAbsIso04EA(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      PlotUtil::plot1D(TString::Format("lep%d_absiso04EA", ilep).Data(), lepton.relIso04EA * lepton.p4.Pt(), a.wgt, a.hist_db , "", 10000, 0., 7., prefix);
      PlotUtil::plot1D("lep_absiso04EA", lepton.relIso04EA * lepton.p4.Pt(), a.wgt, a.hist_db , "", 10000, 0., 7., prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepIP(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      PlotUtil::plot1D(TString::Format("lep%d_ip3d"  , ilep).Data() , lepton.ip3d  , a.wgt , a.hist_db , "" , 10000 , 0. , 0.015 , prefix);
      PlotUtil::plot1D(TString::Format("lep%d_sip3d" , ilep).Data() , lepton.sip3d , a.wgt , a.hist_db , "" , 10000 , 0. , 4.    , prefix);
      PlotUtil::plot1D("lep_ip3d"  , lepton.ip3d  , a.wgt , a.hist_db , "" , 10000 , 0. , 0.015 , prefix);
      PlotUtil::plot1D("lep_sip3d" , lepton.sip3d , a.wgt , a.hist_db , "" , 10000 , 0. , 4.    , prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepTightCharge(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      PlotUtil::plot1D(TString::Format("lep%d_tightcharge", ilep).Data(), lepton.tightcharge, a.wgt, a.hist_db , "", 3, 0., 3, prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepNeutrinoNSol(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      float metpz_sol0 = 0;
      float metpz_sol1 = 0;
//	      PlotUtil::plot1D(TString::Format("lep%d_neutrinonsol", ilep).Data(), VarUtil::NeutrinoSolver(a, ilep, metpz_sol0, metpz_sol1), a.wgt, a.hist_db , "", 3, 0., 3, prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepIsFromX(string prefix, ObjUtil::AnalysisData& a)
  {
    string commonhistname = "lep_isFromX";
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      string histname = TString::Format("lep%d_isFromX", ilep).Data();
      if      (lepton.isFromX == (1 << 0)) PlotUtil::plot1D(histname, 1, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 1)) PlotUtil::plot1D(histname, 2, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 2)) PlotUtil::plot1D(histname, 3, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 3)) PlotUtil::plot1D(histname, 4, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 4)) PlotUtil::plot1D(histname, 5, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 5)) PlotUtil::plot1D(histname, 6, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == 0       ) PlotUtil::plot1D(histname, 0, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else                                 PlotUtil::plot1D(histname, 7, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      if      (lepton.isFromX == (1 << 0)) PlotUtil::plot1D(commonhistname, 1, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 1)) PlotUtil::plot1D(commonhistname, 2, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 2)) PlotUtil::plot1D(commonhistname, 3, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 3)) PlotUtil::plot1D(commonhistname, 4, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 4)) PlotUtil::plot1D(commonhistname, 5, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == (1 << 5)) PlotUtil::plot1D(commonhistname, 6, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else if (lepton.isFromX == 0       ) PlotUtil::plot1D(commonhistname, 0, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
      else                                 PlotUtil::plot1D(commonhistname, 7, a.wgt, a.hist_db, "", 8, 0., 8., prefix);
    }
  }

}
