
namespace LoopUtil
{

  // Total number of events in the input
  unsigned int max_nevents               =   0;
  unsigned int total_nevents             =   0;
  unsigned int current_ttree_max_nevents =   0;
  unsigned int current_ttree_event_index =  -1;
  unsigned int total_nevents_processed   =   0;
  double fraction_of_booked_nevents      =   1;
  TObjArray* list_of_input_files         =   0;
  TChain* current_tchain                 =   0;
  TFile* current_tfile                   =   0;
  TTree* current_ttree                   =   0;
  TObjArrayIter* file_iter               =   0;
  int bar_id                             =   0;
  int print_rate                         = 432;
  bool isdata                            = false;
  bool isfastsim                         = false;
  bool doskim                            = false;
  TStopwatch my_timer;
  TString output_name                    = "output";

  TTree* getCurrentTTree()
  {
    if (current_ttree)
      return current_ttree;
    else
      PrintUtil::error("current_ttree not set!");
    return 0;
  }

  TFile* getCurrentTFile()
  {
    if (current_tfile)
      return current_tfile;
    else
      PrintUtil::error("current_tfile not set!");
    return 0;
  }

  TChain* getCurrentTChain()
  {
    if (current_tchain)
      return current_tchain;
    else
      PrintUtil::error("current_tchain not set!");
    return 0;
  }

  TString getCurrentTFileName()
  {
    return TString(getCurrentTFile()->GetName());
  }

  void loadCurrentTTreeWithName(const char* treename)
  {

    current_ttree = (TTree*) getCurrentTFile()->Get(treename);

    if (!current_ttree)
    {
      PrintUtil::warning("failed to retrieve the TTree from TFile");
      PrintUtil::warning(TString::Format("TFile = %s", getCurrentTFile()->GetName()));
      PrintUtil::warning(TString::Format("TTree = %s", treename));
      PrintUtil::error("check the ttree name or tfile");
    }
    else
    {
      //current_ttree->Print("all");
    }

  }

  void loadTotalNEvents()
  {
    /// Set total number of events from the given TChain
    total_nevents = getCurrentTChain()->GetEntries();
    return;
  }

  void setCurrentTTreeMaxNEvents()
  {
    /// Set total number of ttree events
    current_ttree_max_nevents = getCurrentTTree()->GetEntries();
  }

  void resetLoopCondition(TChain* chain, int nevents)
  {
    /// Set Loop conditions such as total number of events and files to loop over
    setCurrentTChain(chain);
    loadTotalNEvents();
    setMaxNEvents(nevents);
    loadFractionOfBookedNEvents();
    loadListOfFiles();
    loadFileIter();
    resetCurrentTTreeEventIndex();
    resetTotalNEventsProcessed();
    initProgressBar();
    return;
  }

  void resetCurrentTTreeLoopCondition()
  {
    /// Reset loop condition for the TTree
    resetCurrentTTreeEventIndex();
    //loadCurrentTTreeEvent();
  }

  void loadFileIter()
  {
    /// Set TIter instance from list_of_input_files
    //PrintUtil::print("LoopUtil::loadFileIter() loaded file iterator from list of input files");
    if (!list_of_input_files)
      loadListOfFiles();
    file_iter = new TObjArrayIter(list_of_input_files);
  }

  void resetPreviousFile()
  {
    /// Reset previous file that was being looped over
    current_tfile = 0; // TODO: Memory leak!!!!!!!
  }

  bool nextFile()
  {

    /// Go to next file in iteration. Return true, if the file is good and we should loop over

    resetPreviousFile();

    if (!file_iter)
      PrintUtil::error("file_iter not set but you are trying to access the next file");

    // Get the TChain element from TObjArrayIter
    TFile* file_elem = (TFile*) file_iter->Next(); // file_iter returns not exactly TFile....

    // If the file element exists in the TChain we open and process
    if (file_elem)
    {
      // Get the file path
      const char* filepath = file_elem->GetTitle();

      // Set the TFile
      setCurrentTFileByPath(filepath);

      // Announce
      PrintUtil::announce(TString::Format("Working on file = %s", getCurrentTFile()->GetName()));

      return 1;
    }
    else
    {

      // Announce that we are done with this chain
      PrintUtil::print("Done with all files in this chain");

      return 0;
    }

  }

  bool nextFileAndLoadTTreeWithName(const char* treename)
  {
    /// Go to next file in the event and load the ttree with the name of user's choice
    bool is_next_file_good = nextFile();
    if (is_next_file_good)
    {
      loadCurrentTTreeWithName(treename);
      resetCurrentTTreeLoopCondition();
      return 1;
    }
    else
    {
      return 0;
    }
  }

  int loadCurrentTTreeEvent()
  {
    /// Load current ttree's event
    if (!current_ttree)
      PrintUtil::error("current ttree not set!");
    current_tchain->LoadTree(current_ttree_event_index);
    current_tchain->GetEntry(current_ttree_event_index);
    return current_ttree->LoadTree(current_ttree_event_index);
  }

  bool nextEvent()
  {
    /// Go to next event in the ttree
    incrementCurrentTTreeEventIndex();
    int loadresult = loadCurrentTTreeEvent();
    incrementTotalNEventsProcessed();
    printProgressBar();
    if (loadresult == -2) // TTree::LoadTree returns -2 if no entry exist
      return false;
    else
      return true;
  }

  bool isAllEventsProcessed()
  {
    /// Is all events processed? i.e. is the total number of events processed >= max_nevents?
    bool is_all_events_processed = total_nevents_processed >= max_nevents + 1;
    if (is_all_events_processed)
      PrintUtil::print(
          TString::Format("LoopUtil::isAllEventsProcessed() Processed all events! %d",
            total_nevents_processed-1).Data()
          );
    return is_all_events_processed;
  }

  int getCurrentTTreeEventIndex()
  {
    return current_ttree_event_index;
  }

  void resetCurrentTTreeEventIndex()
  {
    //PrintUtil::print("LoopUtil::resetCurrentTTreeEventIndex(): set current ttree event index to 0");
    current_ttree_event_index = -1;
  }

  void resetTotalNEventsProcessed()
  {
    //PrintUtil::print("LoopUtil::resetTotalNEventsProcessed(): set total nevents processed to 0");
    total_nevents_processed = 0;
  }

  void incrementCurrentTTreeEventIndex()
  {
    current_ttree_event_index ++;
  }

  void incrementTotalNEventsProcessed()
  {
    total_nevents_processed ++;
  }

  void setCurrentTChain(TChain* chain)
  {
    //PrintUtil::print("LoopUtil::setCurrentTChain(): set current tchain");
    current_tchain = chain;
  }

  void setCurrentTFile(TFile* file)
  {
    //PrintUtil::print("LoopUtil::setCurrentTFile(): set current tfile");
    current_tfile = file;
  }

  void setCurrentTFileByPath(const char* path)
  {
    //PrintUtil::print("LoopUtil::setCurrentTFileByPath(): set current tfile");
    current_tfile = new TFile(path);
  }

  void setCurrentTTree(TTree* tree)
  {
    //PrintUtil::print("LoopUtil::setCurrentTTree(): set current ttree");
    current_ttree = tree;
  }

  void setMaxNEvents(int nevents)
  {
    if (nevents < 0)
    {
      PrintUtil::print(TString::Format("LoopUtil::setMaxNEvents(): The requested nevents < 0. Set max events to %d", total_nevents).Data());
      max_nevents = total_nevents;
    }
    else if (nevents > (int) total_nevents)
    {
      PrintUtil::print(TString::Format("LoopUtil::setMaxNEvents(): The requested nevents > total_nevents. Set max events to %d", total_nevents).Data());
      max_nevents = total_nevents;
    }
    else
    {
      PrintUtil::print(TString::Format("LoopUtil::setMaxNEvents(): set max events to %d", nevents).Data());
      max_nevents = nevents;
    }
  }

  void loadListOfFiles()
  {
    //PrintUtil::print("LoopUtil::loadListOfFiles(): loaded list of files");
    list_of_input_files = getCurrentTChain()->GetListOfFiles();
  }

  void printProgressBar()
  {
    /// Print progress bar

    int entry = total_nevents_processed;
    int totalN = max_nevents;

    if (totalN < 20)
      totalN = 20;

    // Progress bar
    if (entry%(5*((int)print_rate)) < 100)
    {

      // sanity check
      if (entry >= totalN+10) // +2 instead of +1 since, the loop might be a while loop where to check I got a bad event the index may go over 1.
      {
        TString msg = TString::Format("%d %d", entry, totalN);
        PrintUtil::print(msg);
        PrintUtil::error("Total number of events processed went over max allowed! Check your loop boundary conditions!!");
      }

      int nbars = entry/(totalN/20);
      Double_t elapsed = my_timer.RealTime();
      Double_t rate;
      if (elapsed!=0)
        rate = entry / elapsed;
      else
        rate = -999;
      Double_t percentage = entry / (totalN * 1.) * 100;
      const int mins_in_hour = 60;
      const int secs_to_min = 60;
      Int_t input_seconds = (totalN-entry)/rate;
      Int_t seconds = input_seconds % secs_to_min;
      Int_t minutes = input_seconds / secs_to_min % mins_in_hour;
      Int_t hours   = input_seconds / secs_to_min / mins_in_hour;

      print_rate = (int) (rate) + 1;

      printf("\r");
      if (bar_id%4 == 3) printf("-");
      if (bar_id%4 == 2) printf("/");
      if (bar_id%4 == 1) printf("|");
      if (bar_id%4 == 0) printf("\\");
      printf("|");
      bar_id ++;

      for ( int nb = 0; nb < 20; ++nb )
      {
        if (nb < nbars) printf("=");
        else printf(".");
      }

      printf("| %.1f %% (%d/%d) with  [%d Hz]   ETA %.2d:%.2d:%.2d         ",percentage, entry+1, totalN,  (int)rate, hours, minutes, seconds);
      fflush(stdout);

    }
    else if ( entry == totalN - 1 )
    {
      Double_t elapsed = my_timer.RealTime();
      Double_t rate;
      if (elapsed!=0)
        rate = entry / elapsed;
      else
        rate = -999;
      const int mins_in_hour = 60;
      const int secs_to_min = 60;
      Int_t input_seconds = elapsed;
      Int_t seconds = input_seconds % secs_to_min;
      Int_t minutes = input_seconds / secs_to_min % mins_in_hour;
      Int_t hours   = input_seconds / secs_to_min / mins_in_hour;

      printf("\r");
      printf("+");
      printf("|====================");

      //for ( int nb = 0; nb < 20; ++nb )
      //{
      //  printf("=");
      //}

      printf("| %.1f %% (%d/%d) with  [avg. %d Hz]   Total Time: %.2d:%.2d:%.2d         ", 100.0, entry+1, totalN, (int)rate, hours, minutes, seconds);
      fflush(stdout);
      printf("\n");
    }

    my_timer.Start(kFALSE);
  }

  void initProgressBar()
  {
    /// Init progress bar
    my_timer.Start();
    bar_id = 0;
  }

  void loadFractionOfBookedNEvents()
  {
    /// compute fraction of booked events
    fraction_of_booked_nevents = ((double) max_nevents) / ((double) total_nevents);
    PrintUtil::print(TString::Format("LoopUtil::loadFractionOfBookedNEvents(): fraction_of_booked_nevents = %.2f percent", (fraction_of_booked_nevents*100.)).Data());
  }

  double getFractionOfBookedNEvents()
  {
    /// Return the fraction of number of events being processed
    return fraction_of_booked_nevents;
  }

  void setDoSkim(bool b)
  {
    doskim = b;
  }

}
