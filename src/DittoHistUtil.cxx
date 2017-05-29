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
  void fillLepMTs(string prefix, ObjUtil::AnalysisData& a)
  {
    float minmt = -999;
    float maxmt = -999;
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      float tmpmt = VarUtil::MT(lepton, a.met);
      if (ilep == 0)
      {
        minmt = tmpmt;
        maxmt = tmpmt;
      }
      else
      {
        if (tmpmt < minmt)
          minmt = tmpmt;
        if (tmpmt > maxmt)
          maxmt = tmpmt;
      }
      PlotUtil::plot1D(TString::Format("lep%dmt", ilep).Data(), VarUtil::MT(lepton, a.met), a.wgt, a.hist_db , "", 180, 0., 180, prefix);
    }
    PlotUtil::plot1D("lepminmt", minmt, a.wgt, a.hist_db , "", 180, 0., 180, prefix);
    PlotUtil::plot1D("lepmaxmt", maxmt, a.wgt, a.hist_db , "", 180, 0., 180, prefix);
  }

  //______________________________________________________________________________________
  void fillLepSumPt(string prefix, ObjUtil::AnalysisData& a)
  {
    PlotUtil::plot1D("lepsumpt", VarUtil::LepSumPt(a), a.wgt, a.hist_db , "MET [GeV]", 180, 0., 500., prefix);
  }

  //______________________________________________________________________________________
  void fillLepRelIso03EA(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      PlotUtil::plot1D(TString::Format("lep%d_reliso03EA", ilep).Data(), lepton.relIso03EA, a.wgt, a.hist_db , "", 10000, 0., 0.25, prefix);
    }
  }

  //______________________________________________________________________________________
  void fillLepAbsIso03EA(string prefix, ObjUtil::AnalysisData& a)
  {
    for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep)
    {
      ObjUtil::Lepton lepton = a.leptons[ilep];
      PlotUtil::plot1D(TString::Format("lep%d_absiso03EA", ilep).Data(), lepton.relIso03EA * lepton.p4.Pt(), a.wgt, a.hist_db , "", 10000, 0., 7., prefix);
    }
  }

}
