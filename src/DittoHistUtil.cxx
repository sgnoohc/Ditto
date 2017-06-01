// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

namespace HistUtil
{

  //______________________________________________________________________________________
  string catPrefix(string prefix1, string prefix2)
  {
    return TString::Format("%s_%s_", prefix1.c_str(), prefix2.c_str()).Data();
  }

  //______________________________________________________________________________________
  void fillCutflow(string prefix, ObjUtil::AnalysisData& a, int& ibin)
  {
    PlotUtil::plot1D("cutflow"   , ibin, a.wgt, a.hist_db, "", 20, 0., 20., prefix);
    PlotUtil::plot1D("rawcutflow", ibin,    1., a.hist_db, "", 20, 0., 20., prefix);
    ibin++;
  }

  //______________________________________________________________________________________
  void fillCounter(string prefix, ObjUtil::AnalysisData& a, int ibin)
  {
    PlotUtil::plot1D("counter"   , ibin, a.wgt, a.hist_db, "", 20, 0., 20., prefix);
    PlotUtil::plot1D("rawcounter", ibin,    1., a.hist_db, "", 20, 0., 20., prefix);
  }

  //______________________________________________________________________________________
  void fillMET(string prefix, ObjUtil::AnalysisData& a)
  {
    PlotUtil::plot1D("met", a.met.p4.Pt(), a.wgt, a.hist_db , "MET [GeV]", 180, 0., 500., prefix);
  }

  //______________________________________________________________________________________
  void fillMjj(string prefix, ObjUtil::AnalysisData& a)
  {
    PlotUtil::plot1D("mjj", VarUtil::Mjj(a), a.wgt, a.hist_db , "Mjj [GeV]", 180, 0., 1500., prefix);
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
  void fillLepMlvjs(string prefix, ObjUtil::AnalysisData& a)
  {
    float minmlvj = -999;
    float maxmlvj = -999;
    float summlvj = -999;
    for (unsigned int ijet = 0; ijet < a.jets.size(); ++ijet)
    {
      for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
      {
        ObjUtil::Lepton lepton = a.leptons[ilep];
        ObjUtil::Jet jet = a.jets[ilep];
        float tmpmlvj = VarUtil::Mlvj(a, ilep, ijet);
        if (ilep == 0 && ijet == 0)
        {
          minmlvj = tmpmlvj;
          maxmlvj = tmpmlvj;
          summlvj = tmpmlvj;
        }
        else
        {
          if (tmpmlvj < minmlvj)
            minmlvj = tmpmlvj;
          if (tmpmlvj > maxmlvj)
            maxmlvj = tmpmlvj;
          summlvj += tmpmlvj;
        }
        PlotUtil::plot1D(TString::Format("lep%djet%dmlvj", ilep, ijet).Data(), tmpmlvj, a.wgt, a.hist_db , "", 180, 0., 360, prefix);
      }
    }
    if (a.leptons.size() > 1)
    {
      PlotUtil::plot1D("lepminmlvj" , minmlvj         , a.wgt , a.hist_db , "" , 180 , 0. , 360 , prefix);
      PlotUtil::plot1D("lepmaxmlvj" , maxmlvj         , a.wgt , a.hist_db , "" , 180 , 0. , 450 , prefix);
      PlotUtil::plot1D("lepdmlvj"   , maxmlvj-minmlvj , a.wgt , a.hist_db , "" , 180 , 0. , 360 , prefix);
      PlotUtil::plot1D("lepsummlvj" , summlvj         , a.wgt , a.hist_db , "" , 180 , 0. , 700 , prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepSumPt(string prefix, ObjUtil::AnalysisData& a)
  {
    PlotUtil::plot1D("lepsumpt", VarUtil::LepSumPt(a), a.wgt, a.hist_db , "#Sum p_{T,lep} [GeV]", 180, 0., 500., prefix);
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
      PlotUtil::plot1D(TString::Format("lep%d_neutrinonsol", ilep).Data(), VarUtil::NeutrinoSolver(a, ilep, metpz_sol0, metpz_sol1), a.wgt, a.hist_db , "", 3, 0., 3, prefix);
    }
  }

}
