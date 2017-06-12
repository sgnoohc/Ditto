// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

namespace CutUtil
{
  extern bool eventlistloaded;
  extern bool verbosecheckeventlistloaded;
  extern std::vector<std::vector<int> > eventlisttocheck;
  extern std::vector<std::vector<int> > eventlisttoverbosecheck;

  struct CutData {
    bool pass;
    float val;
    string cutname;
    std::vector<int> eventid;
    void print()
    {
      // Event ID
      std::cout << "Event#  = ( ";
      for (auto& id : eventid)
        std::cout << id << " ";
      std::cout << ")";
      std::cout << std::endl;
      // Cut name
      std::cout << "Cutname = ";
      std::cout << cutname;
      std::cout << std::endl;
      // Cut val
      std::cout << "Cutval  = ";
      std::cout << val;
      std::cout << std::endl;
      // Cut pass
      std::cout << "Cutpass = ";
      std::cout << pass;
      std::cout << std::endl;
    }
  };
  typedef std::function<void(CutData&)> Cut;
  typedef std::vector<Cut> Cuts;

  void loadEventListToCheck();
  void loadEventListToVerboseCheck();
  void print(CutData& cutdata);
  bool failed(CutData& cutdata, TString message="");
  unsigned int passbit(Cuts& cuts, string prefix, ObjUtil::AnalysisData& a);
  bool pass(Cuts& cuts, string prefix, ObjUtil::AnalysisData& a);
  bool ifEventIdInVerboseCheckList(std::vector<int>);
}
