namespace LoopUtil
{
  // Loop Utilities
  // Total number of events in the input
  extern unsigned int max_nevents;
  extern unsigned int total_nevents;
  extern unsigned int current_ttree_max_nevents;
  extern unsigned int current_ttree_event_index;
  extern unsigned int total_nevents_processed;
  extern double fraction_of_booked_nevents;
  extern TObjArray* list_of_input_files;
  extern TChain* current_tchain;
  extern TFile* current_tfile;
  extern TTree* current_ttree;
  extern TObjArrayIter* file_iter;
  extern TStopwatch my_timer;
  extern int bar_id;
  extern int print_rate;
  extern bool isdata;
  extern bool isfastsim;
  extern bool doskim;
  extern bool doprintprogressbar;
  extern TString output_name;
  extern bool eventlistloaded;
  extern std::vector<std::vector<int> > eventlisttocheck;

  void loadFileIter();
  void loadTotalNEvents();
  void loadCurrentTTreeWithName(const char* treename);
  TFile* getCurrentTFile();
  TTree* getCurrentTTree();
  TChain* getCurrentTChain();
  TString getCurrentTFileName();
  int getCurrentTTreeEventIndex();
  void setCurrentTTreeMaxNEvents();
  void setFractionOfBookedNEvents();
  bool nextFile();
  bool nextFileAndLoadTTreeWithName(const char* treename);
  void resetLoopCondition(TChain* chain, int nevents = -1);
  void resetCurrentTTreeLoopCondition();
  void resetTotalNEventsProcessed();
  int loadCurrentTTreeEvent();
  void setTotalCurrentTTreeNEvents();
  bool nextEvent();
  bool isAllEventsProcessed();
  void resetCurrentTTreeEventIndex();
  void incrementCurrentTTreeEventIndex();
  void incrementTotalNEventsProcessed();
  void setCurrentTChain(TChain* chain);
  void setCurrentTFile(TFile* file);
  void setCurrentTFileByPath(const char* path);
  void setCurrentTTree(TTree* tree);
  void setMaxNEvents(int nevents);
  void loadListOfFiles();
  void resetPreviousFile();
  void printProgressBar();
  void initProgressBar();
  void loadFractionOfBookedNEvents();
  double getFractionOfBookedNEvents();
  void setDoSkim(bool b=true);
  void loadEventListToCheck();
  bool failed(std::vector<int> eventid, int cutID,  float cutval=-999, TString message="");
  bool pass(std::vector<std::function<void (bool&, float&, string&, std::vector<int>&)> >& cuts);
}
