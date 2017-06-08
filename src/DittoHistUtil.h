// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

namespace HistUtil
{

  string catPrefix(string prefix1, string prefix2);
  void fillCutflow(string prefix, ObjUtil::AnalysisData& a, int& ibin, const char* label="");
  void fillCounter(string prefix, ObjUtil::AnalysisData& a, int ibin, const char* label="");
  void fillMjj(string prefix, ObjUtil::AnalysisData& a);
  void fillMjjWithMaxDEtajj(string prefix, ObjUtil::AnalysisData& a);
  void fillMET(string prefix, ObjUtil::AnalysisData& a);
  void fillLeps(string prefix, ObjUtil::AnalysisData& a);
  void fillLepMTs(string prefix, ObjUtil::AnalysisData& a);
  void fillLepDPhiljs(string prefix, ObjUtil::AnalysisData& a);
  void fillLepMljs(string prefix, ObjUtil::AnalysisData& a);
  void fillLepMlvjs(string prefix, ObjUtil::AnalysisData& a);
  void fillLepSumPt(string prefix, ObjUtil::AnalysisData& a);
  void fillLepRelIso03EA(string prefix, ObjUtil::AnalysisData& a);
  void fillLepAbsIso03EA(string prefix, ObjUtil::AnalysisData& a);
  void fillLepRelIso04EA(string prefix, ObjUtil::AnalysisData& a);
  void fillLepAbsIso04EA(string prefix, ObjUtil::AnalysisData& a);
  void fillLepIP(string prefix, ObjUtil::AnalysisData& a);
  void fillLepTightCharge(string prefix, ObjUtil::AnalysisData& a);
  void fillLepNeutrinoNSol(string prefix, ObjUtil::AnalysisData& a);
  void fillLepIsFromX(string prefix, ObjUtil::AnalysisData& a);

}
