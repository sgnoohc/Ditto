// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

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
