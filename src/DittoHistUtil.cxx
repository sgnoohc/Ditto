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
  void fillCutflow(string prefix, ObjUtil::AnalysisData& a, int ibin)
  {
    PlotUtil::plot1D("cutflow"   , ibin, a.wgt, a.hist_db, "", 20, 0., 20., prefix);
    PlotUtil::plot1D("rawcutflow", ibin,    1., a.hist_db, "", 20, 0., 20., prefix);
  }

  //______________________________________________________________________________________
  void fillMET(string prefix, ObjUtil::AnalysisData& a)
  {
    PlotUtil::plot1D("met", a.met.p4.Pt(), a.wgt, a.hist_db , "MET [GeV]", 180, 0., 500., prefix);
  }

  //______________________________________________________________________________________
  void fillLepSumPt(string prefix, ObjUtil::AnalysisData& a)
  {
    PlotUtil::plot1D("lepsumpt", VarUtil::LepSumPt(a), a.wgt, a.hist_db , "MET [GeV]", 180, 0., 500., prefix);
  }
}
