// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include "Ditto.h"

#define NMAX_INDIVD_OBJ_TO_PLOT 6

namespace Ditto
{

  namespace PlotUtil
  {

    bool plot1D(string name, float xval, double weight, Hist_DB &allhistos, string title, int numbinsx, float xmin, float xmax, string prefix)
    {

      /// Plot 1D histogram. If a histogram doesn't exist book first and fill.
      /// if the histogram exists, return true

      // If no title given, set title to name
      if (title == "") title = name;

      // If prefix exists add prefix
      if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

      // Find whether a histogram with the name already exists
      map<string, TH1*>::iterator iter= allhistos.find(name);

      // If the histogram is not found, make a new one
      if(iter == allhistos.end())
      {
        TH1D* currentHisto= new TH1D(name.c_str(), title.c_str(), numbinsx, xmin, xmax);
        currentHisto->GetXaxis()->SetTitle(title.c_str());
        currentHisto->Sumw2();
        currentHisto->SetDirectory(0);
        currentHisto->Fill(xval, weight);
        allhistos.insert(pair<string, TH1D*> (name,currentHisto) );
        return false;
      }
      // exists already, so just fill it
      else
      {
        (*iter).second->Fill(xval, weight);
        return true;
      }

    }

    bool plot1D(string name, float xval, double weight, std::map<string, TH1*> &allhistos, string title, int numbinsx, const float * xbins, string prefix)
    {

      /// Plot 1D histogram. If a histogram doesn't exist book first and fill. (with variable binning)

      // If no title given, set title to name
      if (title=="") title=name;

      // If prefix exists add prefix
      if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

      // Find whether a histogram with the name already exists
      std::map<string, TH1*>::iterator iter= allhistos.find(name);

      // If the histogram is not found, make a new one.
      if(iter == allhistos.end())
      {
        TH1D* currentHisto= new TH1D(name.c_str(), title.c_str(), numbinsx, xbins);
        currentHisto->GetXaxis()->SetTitle(title.c_str());
        currentHisto->Sumw2();
        currentHisto->SetDirectory(0);
        currentHisto->Fill(xval, weight);
        allhistos.insert(std::pair<string, TH1D*> (name,currentHisto) );
        return false;
      }
      else // exists already, so just fill it
      {
        (*iter).second->Fill(xval, weight);
        return true;
      }

    }

    void plot1D(string name, float xval, double weight, Hist_DB &allhistos, string prefix)
    {
      // If prefix exists add prefix
      if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

      /// Plot 1D histogram. If a histogram doesn't exist throw an error
      allhistos[name]->Fill(xval, weight);
      return;
    }

    bool plot2D(string name, float xval, float yval, double weight, Hist_DB &allhistos, string title, int numbinsx, float xmin, float xmax, int numbinsy, float ymin, float ymax, string prefix)
    {
      /// Plot 1D histogram. If a histogram doesn't exist book first and fill.
      /// if the histogram exists, return true
      // If no title given, set title to name
      if (title == "") title = name;

      // If prefix exists add prefix
      if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

      // Find whether a histogram with the name already exists
      map<string, TH1*>::iterator iter= allhistos.find(name);

      // If the histogram is not found, make a new one
      if(iter == allhistos.end())
      {
        TH2D* currentHisto= new TH2D(name.c_str(), title.c_str(), numbinsx, xmin, xmax, numbinsy, ymin, ymax);
        currentHisto->Sumw2();
        currentHisto->SetDirectory(0);
        currentHisto->Fill(xval, yval, weight);
        allhistos.insert(pair<string, TH1*> (name,currentHisto) );
        return false;
      }
      // exists already, so just fill it
      else
      {
        ((TH2D*) (*iter).second)->Fill(xval, yval, weight);
        return true;
      }
    }

    bool plot2D(string name, float xval, float yval, double weight, std::map<string, TH1*> &allhistos, string title, int numbinsx, const float * xbins, int numbinsy, const float* ybins, string prefix)
    {
      /// Plot 1D histogram. If a histogram doesn't exist book first and fill. (with variable binning)
      // If no title given, set title to name
      if (title=="") title=name;

      // If prefix exists add prefix
      if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

      // Find whether a histogram with the name already exists
      std::map<string, TH1*>::iterator iter= allhistos.find(name);

      // If the histogram is not found, make a new one.
      if(iter == allhistos.end())
      {
        TH2D* currentHisto= new TH2D(name.c_str(), title.c_str(), numbinsx, xbins, numbinsy, ybins);
        currentHisto->Sumw2();
        currentHisto->SetDirectory(0);
        currentHisto->Fill(xval, yval, weight);
        allhistos.insert(std::pair<string, TH1*> (name,currentHisto) );
        return false;
      }
      else // exists already, so just fill it
      {
        ((TH2D*) (*iter).second)->Fill(xval, yval, weight);
        return true;
      }
    }

    void plot2D(string name, float xval, float yval, double weight, Hist_DB &allhistos, string prefix)
    {
      // If prefix exists add prefix
      if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

      // Plot 1D histogram. If a histogram doesn't exist throw an error
      ((TH2D*) allhistos[name])->Fill(xval, yval, weight);
      return;
    }

    void savePlots(Hist_DB &h_1d, const char* outfilename)
    {

      /// Save histograms to a ROOT file

      // Create a TFile
      TFile outfile(outfilename,"RECREATE") ;

      // Print the info that I am saving to the file
      printf("[Ditto::PlotUtil::savePlots] Saving histograms to %s\n", outfilename);

      // Loop over the histograms
      Hist_DB::iterator it1d;
      for (it1d = h_1d.begin(); it1d!=h_1d.end(); it1d++)
      {
        // save the histograms
        it1d->second->Write();
        delete it1d->second;
      }

      // Write to file and close
      outfile.Write();
      outfile.Close();

      return;
    }

    void savePlots2D(Hist_DB &h_1d, const char* outfilename)
    {

      /// Save TH2 histograms to a ROOT file

      // Create a TFile
      TFile outfile(outfilename,"RECREATE") ;

      // Print the info that I am saving to the file
      printf("[Ditto::PlotUtil::savePlots] Saving histograms to %s\n", outfilename);

      // Loop over the histograms
      Hist_DB::iterator it1d;
      for (it1d = h_1d.begin(); it1d!=h_1d.end(); it1d++)
      {
        // save the histograms
        it1d->second->Write();
        delete it1d->second;
      }

      // Write to file and close
      outfile.Write();
      outfile.Close();

      return;
    }

  }

  namespace PrintUtil
  {

    void print(TString msg, int flush_before, int flush_after)
    {
      /// printf replacement
      if (flush_before) printf("\n");
      printf("Ditto:: %s\n", msg.Data());
      if (flush_after) printf("\n");
      fflush(stdout);
    }

    void warning(TString msg)
    {
      /// warning message. Does not exit the program.
      print("WARNING - "+msg+".\n");
    }

    void error(TString msg, int is_error)
    {
      /// Error & exit
      if (!is_error)
        return;
      //exit();
      print("ERROR - "+msg+", exiting.\n");
      abort();
    }

    void start(int q, int sleep_time)
    {
      /// Fun start (from TM Hong's BaBar days)
      if (q)
        return;

      print(" _");
      print("/\\\\");
      print("\\ \\\\  \\__/ \\__/");
      print(" \\ \\\\ (oo) (oo)  Here we come!");
      print("  \\_\\\\/~~\\_/~~\\_");
      print(" _.-~===========~-._");
      print("(___________________)");
      print("      \\_______/");
      print();
      print("System info:");
      gSystem->Exec("hostname");
      gSystem->Exec("uname -a");
      gSystem->Exec("date");
      gSystem->Exec("whoami");
      gSystem->Exec("pwd");
      fflush(stdout);
      if (sleep_time>0)
        sleep(sleep_time);
    }

    void announce(TString msg, Int_t q)
    {
      /// Fun message presented by the moose
      if (q)
        return;

      // Random
      srand(time(NULL));      // Init rand seed
      Int_t   r = rand()%10+1;// Generate rand number
      Int_t   moose = r>4 ? 1 : 0;

      // Moose type
      TString eyes  = "open";
      if      (r==9) eyes = "closed";
      else if (r==8) eyes = "dead";
      else if (r==7) eyes = "small";
      else if (r==7) eyes = "sunny";
      else if (r==6) eyes = "calc";
      else if (r==4) eyes = "crazy";
      else if (r==3) eyes = "vampire";
      else if (r==2) eyes = "rich";
      else if (r==1) eyes = "sick";
      print();
      if      (msg.Length()>0) print("________________________________________");
      if      (msg.Length()>0) print(msg);
      if      (msg.Length()>0) print("--O-------------------------------------");
      if      (moose)          print("  O    \\_\\_    _/_/");
      if      (moose)          print("   O       \\__/");
      else                     print("   O       ^__^");
      if      (eyes=="open")   print("    o      (oo)\\_______");
      else if (eyes=="closed") print("    o      (==)\\_______");
      else if (eyes=="dead")   print("    o      (xx)\\_______");
      else if (eyes=="small")  print("    o      (..)\\_______");
      else if (eyes=="sunny")  print("    o      (66)\\_______");
      else if (eyes=="calc")   print("    o      (00)\\_______");
      else if (eyes=="crazy")  print("    o      (**)\\_______");
      else if (eyes=="vampire")print("    o      (@@)\\_______");
      else if (eyes=="rich")   print("    o      ($$)\\_______");
      else if (eyes=="sick")   print("    o      (++)\\_______");
      if (true)                print("     o     (__)\\       )\\/\\");
      if      (eyes=="dead")   print("            U  ||----w |");
      else if (eyes=="crazy")  print("            U  ||----w |");
      else if (eyes=="sick")   print("            U  ||----w |");
      else if (eyes=="vampire")print("            VV ||----w |");
      else                     print("               ||----w |");
      if (true)                print("               ||     ||");
      print();
      //sleep(0);
    }

    void exit(int q)
    {
      /// Fun exit (from TM Hong's BaBar days)
      if (q)
        return;
      print();
      print("   \\__/    \\__/");
      print("   (oo)    (oo)");
      print("(\\//~~\\\\  //~~\\\\");
      print(" \\/\\__//  \\\\__//\\");
      print("   ||||    ||\\\\ Who cares!");
      print("__ |||| __ |||| ___");
      print("  (_)(_)  (_)(_)");
      print();
    }

  }

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
    TStopwatch my_timer;

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
      if (entry%print_rate == 0)
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

        print_rate = (int) (rate/4.);

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

  }

  namespace Analyses
  {

    AnalysisData* this_a = 0;

    //______________________________________________________________________________________
    void setAnalysisData(AnalysisData& a) { this_a = &a; }

    //______________________________________________________________________________________
    template <class T>
    void selectObjs(std::vector<T>& objs, std::function<bool (T&)> isgoodobj)
    {
      std::vector<T> goodobjs;
      for (auto& obj: objs) if (isgoodobj(obj)) goodobjs.push_back(obj);
      objs = std::vector<T>(goodobjs);
    }

    //______________________________________________________________________________________
    bool SM_WWW_3l0SFOS(AnalysisData& a)
    {
      if ( !(a.leptons.size() == 3) ) return false;
      if ( !(a.leptons[0].p4.Pt() > 20.) ) return false;
      if ( !(a.leptons[1].p4.Pt() > 20.) ) return false;
      if ( !(a.leptons[2].p4.Pt() > 20.) ) return false;
      std::sort(a.leptons.begin(), a.leptons.end(), comparator_pdgId<ObjUtil::Lepton>);
      // Leptons must be in one of following configurations:
      // +13, -11, -11
      // +13, +11, +11
      // +13, +13, -11
      // +13, +13, +11
      // +11, +11, +11
      // +11, +11, -13
      // +11, -13, -13
      // -11, -11, -13
      if (
          !(
            (a.leptons[0].pdgId ==  13 && a.leptons[1].pdgId == -11 && a.leptons[2].pdgId == -11) ||
            (a.leptons[0].pdgId ==  13 && a.leptons[1].pdgId ==  11 && a.leptons[2].pdgId ==  11) ||
            (a.leptons[0].pdgId ==  13 && a.leptons[1].pdgId ==  13 && a.leptons[2].pdgId == -11) ||
            (a.leptons[0].pdgId ==  13 && a.leptons[1].pdgId ==  13 && a.leptons[2].pdgId ==  11) ||
            (a.leptons[0].pdgId ==  11 && a.leptons[1].pdgId ==  11 && a.leptons[2].pdgId ==  11) ||
            (a.leptons[0].pdgId ==  11 && a.leptons[1].pdgId ==  11 && a.leptons[2].pdgId == -13) ||
            (a.leptons[0].pdgId ==  11 && a.leptons[1].pdgId == -13 && a.leptons[2].pdgId == -13) ||
            (a.leptons[0].pdgId ==  11 && a.leptons[1].pdgId == -11 && a.leptons[2].pdgId == -11)
           )
         ) return false;
      ObjUtil::Leptons electrons;
      ObjUtil::Leptons muons;
      for (auto& lep : a.leptons)
        if      (abs(lep.pdgId) == 11) electrons.push_back(lep);
        else if (abs(lep.pdgId) == 13) muons.push_back(lep);
      if (electrons.size() > 1)
        for (unsigned iel = 0; iel < electrons.size() - 1; ++iel)
          for (unsigned jel = iel + 1; jel < electrons.size(); ++ jel)
            if ( !((electrons.at(iel).p4 + electrons.at(jel).p4).M() > 20. && fabs((electrons.at(iel).p4 + electrons.at(jel).p4).M()-91.1876) > 15. ) ) return false;
      if (muons.size() > 1)
        for (unsigned imu = 0; imu < muons.size() - 1; ++imu)
          for (unsigned jmu = imu + 1; jmu < muons.size(); ++ jmu)
            if ( !((muons.at(imu).p4 + muons.at(jmu).p4).M() > 20. && fabs((muons.at(imu).p4 + muons.at(jmu).p4).M()-91.1876) > 15. ) ) return false;
      //// Mll > 20.
      //if (a.leptons[0].pdgId ==  13 && a.leptons[1].pdgId == -11 && a.leptons[2].pdgId == -11) if ( !( (a.leptons[1].p4 + a.leptons[2].p4).M() > 20.) ) return false;
      //if (a.leptons[0].pdgId ==  13 && a.leptons[1].pdgId ==  13 && a.leptons[2].pdgId == -11) if ( !( (a.leptons[0].p4 + a.leptons[1].p4).M() > 20.) ) return false;
      //if (a.leptons[0].pdgId ==  11 && a.leptons[1].pdgId == -13 && a.leptons[2].pdgId == -13) if ( !( (a.leptons[1].p4 + a.leptons[2].p4).M() > 20.) ) return false;
      //if (a.leptons[0].pdgId ==  11 && a.leptons[1].pdgId ==  11 && a.leptons[2].pdgId == -13) if ( !( (a.leptons[0].p4 + a.leptons[1].p4).M() > 20.) ) return false;
      //// Z veto
      //if (a.leptons[0].pdgId ==  13 && a.leptons[1].pdgId == -11 && a.leptons[2].pdgId == -11) if ( !( fabs( (a.leptons[1].p4 + a.leptons[2].p4).M() - 91.1876 ) < 15. ) ) return false;
      //if (a.leptons[0].pdgId ==  11 && a.leptons[1].pdgId ==  11 && a.leptons[2].pdgId == -13) if ( !( fabs( (a.leptons[0].p4 + a.leptons[1].p4).M() - 91.1876 ) < 15. ) ) return false;
      // Jet veto
      if ( !(a.jets.size() < 2) ) return false;
      // B-Jet veto
      if ( !(a.bjets.size() == 0) ) return false;
      // Angle between trilepton and MET
      if ( !( fabs((a.leptons[0].p4 + a.leptons[1].p4 + a.leptons[2].p4).DeltaPhi(a.met.p4)) > 2.5 ) ) return false;
      HistUtil::fillStdHistograms(__FUNCTION__, a);
      return true;
    }
    //______________________________________________________________________________________
    void SM_WWW_3l1SFOS(AnalysisData& a)
    {
      if ( !(a.leptons.size() == 3) ) return;
      HistUtil::fillStdHistograms(__FUNCTION__, a);
    }
    //______________________________________________________________________________________
    void SM_WWW_3l2SFOS(AnalysisData& a)
    {
      if ( !(a.leptons.size() == 3) ) return;
      HistUtil::fillStdHistograms(__FUNCTION__, a);
    }

    //______________________________________________________________________________________
    void SM_WWW_SSee(AnalysisData& a)
    {
      if ( !(a.leptons.size() == 2) ) return;
      if ( !(a.leptons[0].pdgId * a.leptons[1].pdgId == 121) ) return;
      HistUtil::fillCutflow(__FUNCTION__, a, __COUNTER__);
      if ( !(a.met.p4.Pt() > 60.) ) return;
      HistUtil::fillStdHistograms(__FUNCTION__, a);
    }
    //______________________________________________________________________________________
    void SM_WWW_SSem(AnalysisData& a)
    {
      if ( !(a.leptons.size() == 2) ) return;
      if ( !(a.leptons[0].pdgId * a.leptons[1].pdgId == 143) ) return;
      if ( !(a.met.p4.Pt() > 60.) ) return;
      HistUtil::fillStdHistograms(__FUNCTION__, a);
    }
    //______________________________________________________________________________________
    bool SM_WWW_SSmm(AnalysisData& a)
    {

      /// selectObjs
      selectObjects_SM_WWW_SS(a);

      /// Overlap removal
      overlapRemoval(a);

      // Boolean flag to pass whether it passed a "presel" so we can skim or not
      bool pass = false;

      HistUtil::fillCutflow(__FUNCTION__, a, 0);
      if (!( a.leptons.size() == 2                          )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 1);
      if (!( a.leptons[0].pdgId * a.leptons[1].pdgId == 169 )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 2); pass = true;
      if (!( a.jets.size() >= 2                             )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 3);
      if (!( a.bjets.size() == 0                            )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 4);
      if (!( a.leptons[0].p4.Pt() > 30.                     )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 5);
      if (!( a.leptons[1].p4.Pt() > 30.                     )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 6);
      if (!( a.jets[0].p4.Pt() > 30.                        )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 6);
      if (!( a.jets[1].p4.Pt() > 20.                        )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 7);
      if (!( fabs(a.jets[0].p4.Eta()) < 2.5                 )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 8);
      if (!( fabs(a.jets[1].p4.Eta()) < 2.5                 )) return pass; HistUtil::fillCutflow(__FUNCTION__, a, 9);
      if (!( VarUtil::DEtajj(a) < 1.5                       )) return pass; HistUtil::fillCutflow(__FUNCTION__, a,10);
      if (!( VarUtil::Mjj(a) < 105.                         )) return pass; HistUtil::fillCutflow(__FUNCTION__, a,11);
      if (!( VarUtil::Mjj(a) > 65.                          )) return pass; HistUtil::fillCutflow(__FUNCTION__, a,12);
      HistUtil::fillStdHistograms(__FUNCTION__, a);

      return pass;
    }

    //______________________________________________________________________________________
    void SM_Triboson_5l(AnalysisData& a)
    {
      if ( !(a.leptons.size() == 5) ) return;
      HistUtil::fillStdHistograms(__FUNCTION__, a);
    }

    //______________________________________________________________________________________
    void SM_Triboson_4l(AnalysisData& a)
    {
      if ( !(a.leptons.size() == 4) ) return;
      HistUtil::fillStdHistograms(__FUNCTION__, a);
    }

    //______________________________________________________________________________________
    void SM_VBS_WH(AnalysisData& a)
    {
      //selectObjects_SUSY_ISR_Soft2l_SUS_16_048(a);

      //if ( !( a.jets.size() == 6 ) ) return;
      //if ( !( a.leptons.size() == 0 ) ) return;
      //if ( !( a.bjets.size() >= 1 ) ) return;

      //HistUtil::fillStdHistograms(__FUNCTION__, a);
    }

    //______________________________________________________________________________________
    bool SM_VBS_WW_lvjj(AnalysisData& a)
    {
      selectObjects_SM_VBS_WW_lvjj(a);
      overlapRemoval(a);
      if (!( a.leptons.size() == 1 )) return false;
      if (!( a.jets.size()    >= 4 )) return false;
      HistUtil::fillStdHistograms(__FUNCTION__, a);
      return true;
    }

    //______________________________________________________________________________________
    void SUSY_ISR_Soft2l_SUS_16_048(AnalysisData& a)
    {

      selectObjects_SUSY_ISR_Soft2l_SUS_16_048(a);

      // no cut
      HistUtil::fillCutflow(__FUNCTION__, a, 0);

      // select good leptons
      if ( !(a.leptons.size() == 2 && a.leptons[0].p4.Pt() < 30.) ) return;
      HistUtil::fillCutflow(__FUNCTION__, a, 1);

      // is mm channel
      if ( VarUtil::isOSMMChannel(a) )
      {
        HistUtil::fillCutflow(__FUNCTION__, a, 2);
        int cf_bin = 0;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        if ( !(a.bjets.size() == 0                                            ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_BVeto"), a);
        if ( !(a.met.p4.Pt() > 125.                                           ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_METge125"), a);
        if ( !(VarUtil::Mll(a) > 4.                                           ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_Mllge4"), a);
        if ( !(fabs(VarUtil::Mll(a)-9.75) > 0.75                              ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_Mllaw9p75"), a);
        if ( !(VarUtil::Mll(a) < 50.                                          ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_Mllle50"), a);
        if ( !(VarUtil::Ptll(a) > 3.                                          ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_Ptllge3"), a);
        if ( !(VarUtil::METHTRatio(a) > 0.6 && VarUtil::METHTRatio(a) < 1.4   ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_METHTRatioge0p6le1p4"), a);
        if ( !(VarUtil::HT(a) > 100.                                          ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_HTge100"), a);
        if ( !(VarUtil::MTNthLep(a, 0) < 70. && VarUtil::MTNthLep(a, 1) < 70. ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_MT12le70"), a);
        if ( !(VarUtil::Mtt(a) < 0. || VarUtil::Mtt(a) > 160.                 ) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
        HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_MttVeto"), a);
        if      (a.met.p4.Pt() < 200.)
        {
          cf_bin += 0;
          HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
          HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_lowmet"), a);
        }
        else if (a.met.p4.Pt() < 250.)
        {
          cf_bin += 1;
          HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
          HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_medmet"), a);
        }
        else
        {
          cf_bin += 2;
          HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"ee"), a, cf_bin); cf_bin++;
          HistUtil::fillStdHistograms(HistUtil::catPrefix(__FUNCTION__,"ee_highmet"), a);
        }
      }
      // is ee channel
      else if ( VarUtil::isOSEEChannel(a) )
      {
        HistUtil::fillCutflow(__FUNCTION__, a, 3);
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"mm"), a, 0);
        if ( !(a.bjets.size() == 0) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"mm"), a, 1);
      }
      // is em channel
      else if ( VarUtil::isOSEMChannel(a) )
      {
        HistUtil::fillCutflow(__FUNCTION__, a, 4);
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"em"), a, 0);
        if ( !(a.bjets.size() == 0) ) return;
        HistUtil::fillCutflow(HistUtil::catPrefix(__FUNCTION__,"em"), a, 1);
      }

      //{
      //  fillISRCutflow(12);
      //  if      (Vbf::mt2tree.met_pt < 200.) { fillISRHistogram(Vbf::mee_low_name , VBFSUSYUtilities::getMll(), Vbf::evt_scale1fb); }
      //  else if (Vbf::mt2tree.met_pt < 250.) { fillISRHistogram(Vbf::mee_med_name , VBFSUSYUtilities::getMll(), Vbf::evt_scale1fb); fillISRHistogram(Vbf::mll_med_name , VBFSUSYUtilities::getMll(), Vbf::evt_scale1fb); }
      //  else                                 { fillISRHistogram(Vbf::mee_high_name, VBFSUSYUtilities::getMll(), Vbf::evt_scale1fb); fillISRHistogram(Vbf::mll_high_name, VBFSUSYUtilities::getMll(), Vbf::evt_scale1fb); }
      //}

    }

    //______________________________________________________________________________________
    void SUSY_VBF_Soft1l(AnalysisData& a)
    {

      if (!( a.met.p4.Pt()       >   200.    )) return;
      if (!( a.leptons.size()    >=    1     )) return;
      if (!( a.jets.size()       >=    2     )) return;
      if (!( a.jets[1].p4.Pt()   >    50.    )) return;
      if (!( VarUtil::DEtajj(a)  >     3.8   )) return;
      if (!( VarUtil::MT(a)      <    40.    )) return;
      HistUtil::fillStdHistograms(__FUNCTION__, a);

      int met_bin_idx = -1;
      int mjj_bin_idx = -1;
      int lpt_bin_idx = -1;

      float met = a.met.p4.Pt();
      float mjj = VarUtil::Mjj(a);
      float lpt = a.leptons[0].p4.Pt();

      // TODO: generalize the function
      // MET [200 ,  300 ,  400 , inf]
      // Mjj [500 , 1000 , 1500 , inf]
      // lPt [  5 ,   10 ,   20 ,  30]

      int finalbin = 0;

      if      (met <  200) met_bin_idx = -1;
      else if (met <  300) met_bin_idx =  0;
      else if (met <  400) met_bin_idx =  1;
      else                 met_bin_idx =  2;

      if      (mjj <  500) mjj_bin_idx = -1;
      else if (mjj < 1000) mjj_bin_idx =  0;
      else                 mjj_bin_idx =  1;

      if      (lpt <   10) lpt_bin_idx =  2;
      else if (lpt <   20) lpt_bin_idx =  1;
      else if (lpt <   30) lpt_bin_idx =  0;
      else                 lpt_bin_idx = -1;

      // if any of them don't fall into the bin return -1
      if (met_bin_idx < 0 || mjj_bin_idx < 0 || lpt_bin_idx < 0)
        finalbin = -1;

      finalbin = 1 * met_bin_idx + 3 * lpt_bin_idx;
      PlotUtil::plot1D("multibin", finalbin, a.wgt, a.hist_db, "Multibin", 9, 0., 9., __FUNCTION__);

    }

    //______________________________________________________________________________________
    void SUSY_VBF_MG5_Validation(AnalysisData& a)
    {
      //if (a.met.p4.Pt() > 100. && VarUtil::Mjj(a) > 150.0)
        HistUtil::fillStdHistograms(__FUNCTION__, a);
    }


    //______________________________________________________________________________________
    void selectObjects_SUSY_ISR_Soft2l_SUS_16_048(AnalysisData& a)
    {
      selectObjs<ObjUtil::Lepton>(a.leptons , isGoodLepton_SUSY_ISR_Soft2l_SUS_16_048);
      selectObjs<ObjUtil::Jet>   (a.jets    , isGoodJet_SUSY_ISR_Soft2l_SUS_16_048);
      selectObjs<ObjUtil::Jet>   (a.bjets   , isGoodBJet_SUSY_ISR_Soft2l_SUS_16_048);
    }

    //______________________________________________________________________________________
    void selectObjects_SM_WWW_SS(AnalysisData& a)
    {
      selectObjs<ObjUtil::Lepton>(a.leptons , isGoodLepton_SM_WWW_SS);
      selectObjs<ObjUtil::Jet>   (a.jets    , isGoodJet_SM_WWW_SS);
      selectObjs<ObjUtil::Jet>   (a.bjets   , isGoodBJet_SM_WWW_SS);
    }

    //______________________________________________________________________________________
    void selectObjects_SM_VBS_WW_lvjj(AnalysisData& a)
    {
      selectObjs<ObjUtil::Lepton>(a.leptons, isGoodLepton_SM_VBS_WW_lvjj);
      selectObjs<ObjUtil::Jet>   (a.jets   , isGoodJet_SM_VBS_WW_lvjj);
      selectObjs<ObjUtil::Jet>   (a.bjets  , isGoodBJet_SM_VBS_WW_lvjj);
    }

    //______________________________________________________________________________________
    bool isGoodMediumBJet(ObjUtil::Jet& jet)
    {
      //std::cout << jet.btagCSV << std::endl;
      if ( !(jet.p4.Pt() > 20.        ) ) return false;
      if ( !(fabs(jet.p4.Eta()) < 2.4 ) ) return false;
      if ( !(jet.btagCSV > 0.8484     ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodLooseBJet(ObjUtil::Jet& jet)
    {
      if ( !(jet.p4.Pt() > 20.        ) ) return false;
      if ( !(fabs(jet.p4.Eta()) < 2.4 ) ) return false;
      if ( !(jet.btagCSV > 0.5426     ) ) return false;
      return true;
    }

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
      // Loose criteria
      if ( !(lepton.muPidPFMuon                                   ) ) return false;
      if ( !((lepton.muType & (1<<1)) || (lepton.muType & (1<<2)) ) ) return false;
      //      ^^^^^^^^^^^^^^^^^^^^^       ^^^^^^^^^^^^^^^^^^^^^
      //      isGlobal muon               isTracker muon
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

      if (pfjet_eta <= 2.7){
        if (pfjet_nhf_ >= 0.99       ) return false;
        if (pfjet_nef_ >= 0.99       ) return false;
        if (pfjet_cm_ + pfjet_nm_ < 2) return false;
        // if (pfjet_muf_ >= 0.8        ) return false; removed again

        if (pfjet_eta < 2.4){
          if (!(pfjet_cm_  >   0.  ) ) return false;
          if (!(pfjet_chf_ >   0.  ) ) return false;
          if (!(pfjet_cef_ <   0.99) ) return false;
        }
      }else if( pfjet_eta > 2.7 && pfjet_eta <= 3.0 ){
        if (!(pfjet_nef_ < 0.9 ) ) return false;
        if (!(pfjet_nm_  > 2   ) ) return false;
      }else if( pfjet_eta > 3.0 ){
        if (!(pfjet_nef_ < 0.9 ) ) return false;
        if (!(pfjet_nm_  > 10  ) ) return false;
      }

      return true;
    }

    //______________________________________________________________________________________
    bool isTightMuonPOG(ObjUtil::Lepton& lepton)
    {

      return false;

      //if (!(  lepton.muPidPFMuon                           )) return false;
      //if (!(  lepton.muType & (1<<1)                       )) return false;
      //if (!(  lepton.muChi2OverNDof < 10.                  )) return false;


      //if (!mus_pid_PFMuon()            .at(muIdx)         ) return false;
      //if (((mus_type()                 .at(muIdx))
      //   & (1<<1)) == 0                                 ) return false;//global muon
      //if (mus_gfit_chi2()              .at(muIdx)at
      //  /get_mus_gfit_ndof          (muIdx)  >= 10  ) return false;
      //if (mus_gfit_validSTAHits()      .at(muIdx)  == 0   ) return false;
      //if (mus_numberOfMatchedStations().at(muIdx)  <  2   ) return false;
      //if (mus_validPixelHits()         .at(muIdx)  == 0   ) return false;
      //if (mus_nlayers()                .at(muIdx)  <  6   ) return false;
      //if (fabs(mus_dxyPV()             .at(muIdx)) >  0.2 ) return false;
      //if (fabs(mus_dzPV()              .at(muIdx)) >  0.5 ) return false;
      return true;
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
    bool isGoodLepton_SUSY_ISR_Soft2l_SUS_16_048(ObjUtil::Lepton& lepton)
    {
      if ( !(lepton.p4.Pt() >= 5.                                        ) ) return false;
      if ( (abs(lepton.pdgId) == 11) && !( (fabs(lepton.p4.Eta()) < 2.5) ) ) return false;
      if ( (abs(lepton.pdgId) == 13) && !( (fabs(lepton.p4.Eta()) < 2.4) ) ) return false;
      if ( !( fabs(lepton.sip3d) < 2.                                    ) ) return false;
      if ( !( fabs(lepton.dxy)   < 0.01                                  ) ) return false;
      if ( !( fabs(lepton.dz)    < 0.01                                  ) ) return false;
      if ( !( fabs(lepton.relIso03) < 0.5                                ) ) return false;
      if ( !( fabs(lepton.relIso03*lepton.p4.Pt()) < 5.                  ) ) return false;
      //if ( (abs(lepton.lep_pdgId) == 11) && !( (lepton.lep_tightId > ELECTRON_ID) ) ) return false;
      //if ( (abs(lepton.lep_pdgId) == 13) && !( (lepton.lep_tightId > MUON_ID)     ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodJet_SUSY_ISR_Soft2l_SUS_16_048(ObjUtil::Jet& jet)
    {
      if ( !(jet.p4.Pt() > 25. ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodBJet_SUSY_ISR_Soft2l_SUS_16_048(ObjUtil::Jet& jet)
    {
      if ( !(jet.p4.Pt() > 25.        ) ) return false;
      if ( !(fabs(jet.p4.Eta()) < 2.4 ) ) return false;
      if ( !(jet.btagCSV > 0.46       ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodJet_SM_WWW_SS(ObjUtil::Jet& jet)
    {
      if ( !(jet.p4.Pt()              > 20.) ) return false;
      if ( !(fabs(jet.p4.Eta())       <  5.) ) return false;
      //if ( !(isLoosePFJet_Summer16_v1(jet) ) ) return false;
      if ( !(jet.id & (1<<0)               ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodBJet_SM_WWW_SS(ObjUtil::Jet& jet)
    {
      if ( !(isGoodJet_SM_WWW_SS(jet)  ) ) return false;
      if ( !(isGoodMediumBJet(jet)     ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodLepton_SM_WWW_SS(ObjUtil::Lepton& lepton)
    {
      return isGoodElectron_SM_WWW_SS(lepton) || isGoodMuon_SM_WWW_SS(lepton);
    }

    //______________________________________________________________________________________
    bool isGoodElectron_SM_WWW_SS(ObjUtil::Lepton& lepton)
    {
      if ( !(lepton.p4.Pt()                   >  10.  ) ) return false;
      if ( !(fabs(lepton.p4.Eta())            <  2.4  ) ) return false;
      if ( !(fabs(lepton.pdgId)               == 11   ) ) return false;
      if ( !(fabs(lepton.elEtaSC)             <= 2.5  ) ) return false;
      if ( !(!(lepton.elConvVeto)                     ) ) return false;
      if ( !(lepton.elNmiss                   <= 0    ) ) return false;
      if ( !(fabs(lepton.dz)                  <  0.1  ) ) return false;
      if ( !(fabs(lepton.dxy)                 <  0.05 ) ) return false;
      if ( !(fabs(lepton.sip3d)               <  4    ) ) return false;
      if ( !(lepton.tightcharge               == 2    ) ) return false;
      if ( !(isElectronPOGMVAIDCut(lepton,
                 /* barrel */      0.77, 0.52, 0.77,
                 /* transition */  0.56, 0.11, 0.56,
                 /* endcap */      0.48,-0.01, 0.48)  ) ) return false;
      if ( !(isTriggerSafenoIso_v1(lepton)            ) ) return false;
      if ( !(isIsoElectron_SM_WWW_SS(lepton)          ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodMuon_SM_WWW_SS(ObjUtil::Lepton& lepton)
    {
      HistUtil::fillCutflow(__FUNCTION__, (*this_a), 0);
      if ( !(lepton.p4.Pt()             >    20.   ) ) return false; HistUtil::fillCutflow(__FUNCTION__, (*this_a), 1);
      if ( !(fabs(lepton.p4.Eta())      <    2.4   ) ) return false; HistUtil::fillCutflow(__FUNCTION__, (*this_a), 2);
      if ( !(abs(lepton.pdgId)          ==   13    ) ) return false; HistUtil::fillCutflow(__FUNCTION__, (*this_a), 3);
      if ( !(fabs(lepton.sip3d)         <     4    ) ) return false; HistUtil::fillCutflow(__FUNCTION__, (*this_a), 4);
      if ( !(fabs(lepton.dz)            <=    0.1  ) ) return false; HistUtil::fillCutflow(__FUNCTION__, (*this_a), 5);
      if ( !(fabs(lepton.dxy)           <=    0.05 ) ) return false; HistUtil::fillCutflow(__FUNCTION__, (*this_a), 6);
      if ( !(lepton.muPOverP            <     0.2  ) ) return false; HistUtil::fillCutflow(__FUNCTION__, (*this_a), 8);
      if ( !(isMediumMuonPOG(lepton)               ) ) return false; HistUtil::fillCutflow(__FUNCTION__, (*this_a), 9);
      if ( !(isIsoMuon_SM_WWW_SS(lepton)           ) ) return false; HistUtil::fillCutflow(__FUNCTION__, (*this_a),10);
      return true;
    }

    //______________________________________________________________________________________
    bool isIsoElectron_SM_WWW_SS(ObjUtil::Lepton& lepton)
    {
      if ( !(lepton.miniRelIsoCMS3_EA <  0.12                ) ) return false;
      if ( !(lepton.ptRatio >  0.80 || lepton.ptRel   >  7.2 ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isIsoMuon_SM_WWW_SS(ObjUtil::Lepton& lepton)
    {
      if ( !(lepton.miniRelIsoCMS3_EA         <  0.16  ) ) return false;
      if ( !(lepton.ptRatio >  0.76 || lepton.ptRel   >  7.2 ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodLepton_SM_VBS_WW_lvjj(ObjUtil::Lepton& lepton)
    {
      return isGoodElectron_SM_VBS_WW_lvjj(lepton) || isGoodMuon_SM_VBS_WW_lvjj(lepton);
    }

    //______________________________________________________________________________________
    bool isGoodElectron_SM_VBS_WW_lvjj(ObjUtil::Lepton& lepton)
    {
      // Basic
      if (!( lepton.p4.Pt()                   >  20.  )) return false;
      if (!( fabs(lepton.pdgId)               == 11   )) return false;
      // https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Offline_selection_criteria
      // Medium working point
      if (!(isElectronPOGCutBasedIDCut(lepton,
      /*barrel_elSigmaIEtaIEta_full5x5_cut , barrel_abs_elDEtaIn_cut , barrel_abs_elDPhiIn_cut ,                       */ 0.00998, 0.00311, 0.103,
      /*barrel_elHOverE_cut                , barrel_relIso03EA_cut   , barrel_elEpRatio_cut    , barrel_elNmiss_cut ,  */ 0.253  , 0.0695 , 0.134, 1,
      /*endcap_elSigmaIEtaIEta_full5x5_cut , endcap_abs_elDEtaIn_cut , endcap_abs_elDPhiIn_cut ,                       */ 0.0298 , 0.00609, 0.045,
      /*endcap_elHOverE_cut                , endcap_relIso03EA_cut   , endcap_elEpRatio_cut    , endcap_elNmiss_cut    */ 0.0878 , 0.0821 , 0.13 , 1) )) return false;
      // Kinematic cuts
      if ( !(fabs(lepton.elEtaSC)             <= 2.5  ) ) return false;
      if ( !(fabs(lepton.dz)                  <  0.1  ) ) return false;
      if ( !(fabs(lepton.dxy)                 <  0.05 ) ) return false;
      if ( !(fabs(lepton.sip3d)               <  4    ) ) return false;
      //if ( !(isTriggerSafenoIso_v1(lepton)            ) ) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodMuon_SM_VBS_WW_lvjj(ObjUtil::Lepton& lepton)
    {
      // Basic
      if (!( lepton.p4.Pt()                   >  20.  )) return false;
      if (!( fabs(lepton.pdgId)               == 13   )) return false;
      if (!( isMediumMuonPOG(lepton)                  )) return false;
      if (!( fabs(lepton.sip3d)               <  4    )) return false;
      if (!( fabs(lepton.dz)                  <  0.1  )) return false;
      if (!( fabs(lepton.dxy)                 <  0.05 )) return false;
      if (!( lepton.muPOverP                  <  0.2  )) return false;
      if (!( lepton.relIso03EA                <  0.1  )) return false;
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodJet_SM_VBS_WW_lvjj(ObjUtil::Jet& jet)
    {
      if (!( jet.p4.Pt()             > 20. )) return false;
      if (!( fabs(jet.p4.Eta())      <  5. )) return false;
      //if (!( isLoosePFJet_Summer16_v1(jet) )) return false; // isLoosePFJet
      if (!( jet.id & (1<<0)               )) return false; // isLoosePFJet
      //if (!( jet.id & (1<<5)               )) return false; // isLoosePileupJetId
      return true;
    }

    //______________________________________________________________________________________
    bool isGoodBJet_SM_VBS_WW_lvjj(ObjUtil::Jet& jet)
    {
      if (!( isGoodJet_SM_VBS_WW_lvjj(jet)   )) return false;
      if (!( isGoodMediumBJet(jet)           )) return false;
      return true;
    }

    //______________________________________________________________________________________
    void overlapRemoval(AnalysisData& ana_data)
    {

      ObjUtil::Jets ORedjets;
      for (auto& jet : ana_data.jets)
      {
        bool pass = true;
        for (auto& lepton : ana_data.leptons)
        {
          if (jet.p4.DeltaR(lepton.p4) < 0.3)
            pass = false;
        }
        if (pass)
          ORedjets.push_back(jet);
      }
      ana_data.jets = ObjUtil::Jets(ORedjets);

      ObjUtil::Jets ORedbjets;
      for (auto& bjet : ana_data.bjets)
      {
        bool pass = true;
        for (auto& lepton : ana_data.leptons)
        {
          if (bjet.p4.DeltaR(lepton.p4) < 0.3)
            pass = false;
        }
        if (pass)
          ORedbjets.push_back(bjet);
      }
      ana_data.bjets = ObjUtil::Jets(ORedbjets);

    }


  }

  namespace VarUtil
  {

    float DEta(TLorentzVector obj1, TLorentzVector obj2) { return fabs(obj1.Eta() - obj2.Eta()); }
    float DPhi(TLorentzVector obj1, TLorentzVector obj2) { return fabs(obj1.DeltaPhi(obj2)); }
    float DR  (TLorentzVector obj1, TLorentzVector obj2) { return fabs(obj1.DeltaR(obj2)); }
    float DPt (TLorentzVector obj1, TLorentzVector obj2) { return fabs(obj1.Pt()-obj2.Pt()); }
    float Mass(TLorentzVector obj1, TLorentzVector obj2) { return (obj1 + obj2).M(); }
    float Pt  (TLorentzVector obj1, TLorentzVector obj2) { return (obj1 + obj2).Pt(); }

    //
    float DEta(ObjUtil::Particle obj1, ObjUtil::Particle obj2) { return DEta(obj1.p4, obj2.p4); }
    float DPhi(ObjUtil::Particle obj1, ObjUtil::Particle obj2) { return DPhi(obj1.p4, obj2.p4); }
    float DR  (ObjUtil::Particle obj1, ObjUtil::Particle obj2) { return DR  (obj1.p4, obj2.p4); }
    float DPt (ObjUtil::Particle obj1, ObjUtil::Particle obj2) { return DPt (obj1.p4, obj2.p4); }
    float Mass(ObjUtil::Particle obj1, ObjUtil::Particle obj2) { return Mass(obj1.p4, obj2.p4); }
    float Pt  (ObjUtil::Particle obj1, ObjUtil::Particle obj2) { return Pt  (obj1.p4, obj2.p4); }
    float MT  (ObjUtil::Particle obj1, ObjUtil::Particle obj2) { return MT  (obj1.p4, obj2.p4); }

    //
    float DEta(TLorentzVector obj1, ObjUtil::Particle obj2) { return DEta(obj1, obj2.p4); }
    float DPhi(TLorentzVector obj1, ObjUtil::Particle obj2) { return DPhi(obj1, obj2.p4); }
    float DR  (TLorentzVector obj1, ObjUtil::Particle obj2) { return DR  (obj1, obj2.p4); }
    float DPt (TLorentzVector obj1, ObjUtil::Particle obj2) { return DPt (obj1, obj2.p4); }
    float Mass(TLorentzVector obj1, ObjUtil::Particle obj2) { return Mass(obj1, obj2.p4); }
    float Pt  (TLorentzVector obj1, ObjUtil::Particle obj2) { return Pt  (obj1, obj2.p4); }
    float MT  (TLorentzVector obj1, ObjUtil::Particle obj2) { return MT  (obj1, obj2.p4); }

    //
    float DEta(ObjUtil::Particle obj1, TLorentzVector obj2) { return DEta(obj1.p4, obj2); }
    float DPhi(ObjUtil::Particle obj1, TLorentzVector obj2) { return DPhi(obj1.p4, obj2); }
    float DR  (ObjUtil::Particle obj1, TLorentzVector obj2) { return DR  (obj1.p4, obj2); }
    float DPt (ObjUtil::Particle obj1, TLorentzVector obj2) { return DPt (obj1.p4, obj2); }
    float Mass(ObjUtil::Particle obj1, TLorentzVector obj2) { return Mass(obj1.p4, obj2); }
    float Pt  (ObjUtil::Particle obj1, TLorentzVector obj2) { return Pt  (obj1.p4, obj2); }
    float MT  (ObjUtil::Particle obj1, TLorentzVector obj2) { return MT  (obj1.p4, obj2); }

    // Closest to mass = X, not closest to dR = X
    float DRCloseToX(ObjUtil::Jets& jets, float X)
    {
      /// Compute the DR that has mass closest to "X"
      /// Return -999 if there are not enough number of jets

      float mjj_closest = -999;

      // if less than 2 jets just skip
      if (jets.size() < 2)
        return mjj_closest;

      int jetidx0 = -999;
      int jetidx1 = -999;

      for (unsigned int ijet = 0; ijet < jets.size()-1; ++ijet)
      {
        for (unsigned int jjet = ijet+1; jjet < jets.size(); ++jjet)
        {

          float mjj_tmp = (jets[ijet].p4 + jets[jjet].p4).M();

          if (mjj_closest < 0)
          {
            mjj_closest = mjj_tmp;
            jetidx0 = ijet;
            jetidx1 = jjet;
          }
          else if (mjj_closest > 0)
          {
            if (fabs(mjj_tmp - X) < fabs(mjj_closest - X))
            {
              mjj_closest = mjj_tmp;
              jetidx0 = ijet;
              jetidx1 = jjet;
            }
          }

        }
      }

      return jets.at(jetidx0).p4.DeltaR(jets.at(jetidx1).p4);

    }

    float MjjCloseToX(ObjUtil::Jets& jets, float X)
    {
      /// Compute the Mjj that is closes to "X"
      /// Return -999 if there are not enough number of jets

      float mjj_closest = -999;

      // if less than 2 jets just skip
      if (jets.size() < 2)
        return mjj_closest;

      for (unsigned int ijet = 0; ijet < jets.size()-1; ++ijet)
      {
        for (unsigned int jjet = ijet+1; jjet < jets.size(); ++jjet)
        {

          float mjj_tmp = (jets[ijet].p4 + jets[jjet].p4).M();

          if (mjj_closest < 0)
          {
            mjj_closest = mjj_tmp;
          }
          else if (mjj_closest > 0)
          {
            if (fabs(mjj_tmp - X) < fabs(mjj_closest - X))
              mjj_closest = mjj_tmp;
          }

        }
      }

      return mjj_closest;

    }

    float MT(TLorentzVector p4, TLorentzVector metp4)
    {
      /// Compute MT
      float mt = sqrt(2 * p4.Pt() * metp4.Pt() * ( 1 - cos(metp4.DeltaPhi(p4) ) ));
      return mt;
    }

    float MTNthLep(Analyses::AnalysisData& a, int lep_idx)
    {
      /// Compute MT with the Nth lepton provided by the lepton index argument
      if (a.leptons.size() <= (unsigned int) lep_idx) return -999;
      float mt = sqrt(2 * a.leptons[lep_idx].p4.Pt() * a.met.p4.Pt() * ( 1 - cos(a.met.p4.DeltaPhi(a.leptons[lep_idx].p4) ) ));
      return mt;
    }

    float DRjjWmass(Analyses::AnalysisData& a)
    {
      /// Compute the DR that has mass closest to the W mass
      return DRCloseToX(a.jets, 80.385);
    }

    float MjjWmass(Analyses::AnalysisData& a)
    {
      /// Compute the Mjj that is closest to the W mass
      return MjjCloseToX(a.jets, 80.385);
    }

    float HT(Analyses::AnalysisData& a)
    {
      float ht = 0;
      for (auto& jet : a.jets)
        ht += jet.p4.Pt();
      return ht;
    }

    float METHTRatio(Analyses::AnalysisData& a)
    {
      float ht = 0;
      for (auto& jet : a.jets)
        ht += jet.p4.Pt();
      return ht;
    }

    float DRjj(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.jets.size() < 2)
        return -999;
      return (a.jets[0].p4.DeltaR(a.jets[1].p4));
    }

    float Mjj(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.jets.size() < 2)
        return -999;
      return (a.jets[0].p4+a.jets[1].p4).M();
    }

    float MljClosest(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.jets.size() < 1)
        return -999;
      if (a.leptons.size() < 1)
        return -999;
      TLorentzVector jetp4;
      TLorentzVector lepp4;
      float dr = 999;
      for (auto& jet: a.jets)
        for (auto& lep: a.leptons)
          if (dr > jet.p4.DeltaR(lep.p4))
          {
            jetp4 = jet.p4;
            lepp4 = lep.p4;
          }
      return (jetp4+lepp4).M();
    }

    float Ptjj(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.jets.size() < 2)
        return -999;
      return (a.jets[0].p4+a.jets[1].p4).Pt();
    }

    float Mbb(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.bjets.size() < 2)
        return -999;
      return (a.bjets[0].p4+a.bjets[1].p4).M();
    }

    float Ptbb(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.bjets.size() < 2)
        return -999;
      return (a.bjets[0].p4+a.bjets[1].p4).Pt();
    }

    float DEtajj(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.jets.size() < 2)
        return -999;
      return fabs(a.jets[0].p4.Eta()-a.jets[1].p4.Eta());
    }

    float DEtabb(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.bjets.size() < 2)
        return -999;
      return fabs(a.bjets[0].p4.Eta()-a.bjets[1].p4.Eta());
    }

    float Ptll(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.leptons.size() < 2)
        return -999;
      return (a.leptons[0].p4+a.leptons[1].p4).Pt();
    }

    float Mll(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.leptons.size() < 2)
        return -999;
      return (a.leptons[0].p4+a.leptons[1].p4).M();
    }

    float DPhill(Analyses::AnalysisData& a)
    {
      // If less than 2 jets just skip
      if (a.leptons.size() < 2)
        return -999;
      return fabs(a.leptons[0].p4.DeltaPhi(a.leptons[1].p4));
    }

    float DPhiLepMET(Analyses::AnalysisData& a)
    {
      // If less than 1 lepton just skip
      if (a.leptons.size() < 1)
        return -999;
      return fabs(a.leptons[0].p4.DeltaPhi(a.met.p4));
    }

    float MT(Analyses::AnalysisData& a)
    {
      if (a.leptons.size() == 0)
        return -999;
      return MTNthLep(a, 0);
    }

    float MTll(Analyses::AnalysisData& a)
    {
      if (a.leptons.size() < 2)
        return -999;
      TLorentzVector dilep = a.leptons[0].p4 + a.leptons[1].p4;
      return MT(dilep, a.met.p4);
    }

    float Mtt(Analyses::AnalysisData& a)
    {

      if (a.leptons.size() < 2)
        return -999;

      TLorentzVector lep0_tlv;
      TLorentzVector lep1_tlv;
      TLorentzVector tmp_met;
      float x_1;
      float x_2;
      float mtt;
      float Mll;

      lep0_tlv = a.leptons[0].p4;
      lep1_tlv = a.leptons[1].p4;
      tmp_met = a.met.p4;
      Mll = (lep0_tlv + lep1_tlv).M();

      // below from HWWlvlvCode.cxx https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/HiggsPhys/HSG3/WWDileptonAnalysisCode/HWWlvlvCode/trunk/Root/HWWlvlvCode.cxx
      x_1= (lep0_tlv.Px()*lep1_tlv.Py()-lep0_tlv.Py()*lep1_tlv.Px())/(lep1_tlv.Py()*tmp_met.Px()-lep1_tlv.Px()*tmp_met.Py()+lep0_tlv.Px()*lep1_tlv.Py()-lep0_tlv.Py()*lep1_tlv.Px());
      x_2= (lep0_tlv.Px()*lep1_tlv.Py()-lep0_tlv.Py()*lep1_tlv.Px())/(lep0_tlv.Px()*tmp_met.Py()-lep0_tlv.Py()*tmp_met.Px()+lep0_tlv.Px()*lep1_tlv.Py()-lep0_tlv.Py()*lep1_tlv.Px());
      if (x_1 > 0 && x_2 > 0)
        mtt = Mll/sqrt(x_1*x_2);
      else
        mtt = -9999.;

      return mtt;
    }

    float Mlvjj(Analyses::AnalysisData& a, int lepidx, int jetidx0, int jetidx1)
    {
      if (a.leptons.size() < (unsigned int) lepidx+1) return -999;
      if (a.jets.size() < (unsigned int) jetidx1+1) return -999;
      float metpz = NeutrinoSolver(a);
      TLorentzVector metp4;
      metp4.SetXYZM(a.met.p4.Px(), a.met.p4.Py(), metpz, 0);
      return (a.leptons[lepidx].p4 + metp4 + a.jets[jetidx0].p4 + a.jets[jetidx1].p4).M();
    }

    float NeutrinoSolver(Analyses::AnalysisData& adb, int lepidx)
    {
      if (adb.leptons.size() < (unsigned int) lepidx + 1) return 0.;
      ObjUtil::Lepton lepton = adb.leptons[lepidx];
      float lpx = lepton.p4.Px();
      float lpy = lepton.p4.Py();
      float lpz = lepton.p4.Pz();
      float vpx = adb.met.p4.Px();
      float vpy = adb.met.p4.Py();
      float c = lpz*lpz + (lpx+vpx)*(lpx+vpx) + (lpy+vpy)*(lpy+vpy) - 80.385*80.385;
      float b = 2*lpz;
      float xp = (-b + sqrt(b*b - 4*c)) / 2.;
      float xm = (-b - sqrt(b*b - 4*c)) / 2.;
      return fabs(xp) < fabs(xm) ? xp : xm;
    }

    bool checkDilepPdgIdProduct(Analyses::AnalysisData& a, int check)
    {
      if (a.leptons.size() != 2) return false;
      if (a.leptons[0].pdgId * a.leptons[1].pdgId == check) return true;
      return false;
    }

    bool isOSEEChannel(Analyses::AnalysisData& a)
    {
      return checkDilepPdgIdProduct(a, -121);
    }

    bool isOSEMChannel(Analyses::AnalysisData& a)
    {
      return checkDilepPdgIdProduct(a, -143);
    }

    bool isOSMMChannel(Analyses::AnalysisData& a)
    {
      return checkDilepPdgIdProduct(a, -169);
    }

    double Rndm(){
       return ( double(rand())/RAND_MAX );
    }

    std::vector<std::vector<int> > comb(int N, int K)
    {
      std::string bitmask(K, 1); // K leading 1's
      bitmask.resize(N, 0); // N-K trailing 0's

      std::vector<std::vector<int> > combs;
      // print integers and permute bitmask
      do {
        std::vector<int> comb;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
          if (bitmask[i])
            comb.push_back(i);
        }
        combs.push_back(comb);
      } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
      return combs;
    }

  }

  namespace HistUtil
  {

    //______________________________________________________________________________________
    string catPrefix(string prefix1, string prefix2)
    {
      return TString::Format("%s_%s_", prefix1.c_str(), prefix2.c_str()).Data();
    }

    //______________________________________________________________________________________
    void fillStdHistograms(string prefix, Analyses::AnalysisData& a)
    {
      /// fill all histogram types
      fillNLep       (prefix, a);
      fillNJet       (prefix, a);
      fillNBjet      (prefix, a);
      fillMET        (prefix, a);
      fillLepPt      (prefix, a);
      fillJetPt      (prefix, a);
      fillBJetPt     (prefix, a);
      fillLepEta     (prefix, a);
      fillJetEta     (prefix, a);
      fillBJetEta    (prefix, a);
      fillLepPhi     (prefix, a);
      fillJetPhi     (prefix, a);
      fillBJetPhi    (prefix, a);
      fillMjjW       (prefix, a);
      fillMll        (prefix, a);
      fillMljClose   (prefix, a);
      fillVBFMjj     (prefix, a);
      fillVBFMbb     (prefix, a);
      fillMjj        (prefix, a);
      fillPtjj       (prefix, a);
      fillPtbb       (prefix, a);
      fillMT         (prefix, a);
      fillHT         (prefix, a);
      fillMTll       (prefix, a);
      fillDPhill     (prefix, a);
      fillDEtajj     (prefix, a);
      fillDRjj       (prefix, a);
      fillDEtabb     (prefix, a);
      fillDPhiLepMET (prefix, a);
      fillDRjjW      (prefix, a);
      fillLepDz      (prefix, a);
      fillLepDxy     (prefix, a);
      fillLepIp3d    (prefix, a);
      fillLepSip3d   (prefix, a);
      fillLepRelIso03(prefix, a);
      fillLepAbsIso03(prefix, a);
      fillLepMiniIso03(prefix, a);
      fillLepPtRatio (prefix, a);
      fillLepPtRel   (prefix, a);
      fillLepID      (prefix, a);
      fillJetID      (prefix, a);
    }

    //______________________________________________________________________________________
    /// Multiplicity variables
    void fillNLep      (string prefix , Analyses::AnalysisData& a) { PlotUtil::plot1D("nlep"  , a.leptons.size() , a.wgt , a.hist_db , "N_{lep}" , 10 , 0. , 10. , prefix); }
    void fillNJet      (string prefix , Analyses::AnalysisData& a) { PlotUtil::plot1D("njet"  , a.jets.size()    , a.wgt , a.hist_db , "N_{jet}" , 10 , 0. , 10. , prefix); }
    void fillNBjet     (string prefix , Analyses::AnalysisData& a) { PlotUtil::plot1D("nbjet" , a.bjets.size()   , a.wgt , a.hist_db , "N_{b-jet}" , 10 , 0. , 10. , prefix); }
    /// Single object kinematics
    void fillMET       (string prefix , Analyses::AnalysisData& a) { PlotUtil::plot1D("met"       , a.met.p4.Pt()          , a.wgt , a.hist_db , "MET [GeV]" , 180 , 0. , 500.   , prefix); }
    void fillLepPt     (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep  = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)  PlotUtil ::plot1D(TString::Format("lep%dpt"   , ilep).Data()  , a.leptons[ilep].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, lep%d} [GeV]"  , ilep).Data()  , 180     , 0.      , 200. - ilep * 20  , prefix); }
    void fillJetPt     (string prefix , Analyses::AnalysisData& a) { for (unsigned int ijet  = 0; ijet < a.jets   .size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)  PlotUtil ::plot1D(TString::Format("jet%dpt"   , ijet).Data()  , a.jets   [ijet].p4.Pt()    , a.wgt , a.hist_db , TString::Format("p_{T, jet%d} [GeV]"  , ijet).Data()  , 180     , 0.      , 200. - ijet * 20  , prefix); }
    void fillBJetPt    (string prefix , Analyses::AnalysisData& a) { for (unsigned int ibjet = 0; ibjet < a.bjets .size() && ibjet< NMAX_INDIVD_OBJ_TO_PLOT; ++ibjet) PlotUtil ::plot1D(TString::Format("bjet%dpt"  , ibjet).Data() , a.bjets   [ibjet].p4.Pt()  , a.wgt , a.hist_db , TString::Format("p_{T, bjet%d} [GeV]" , ibjet).Data() , 180     , 0.      , 200. - ibjet * 20 , prefix); }
    void fillLepEta    (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep  = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)  PlotUtil ::plot1D(TString::Format("lep%deta"  , ilep).Data()  , a.leptons[ilep].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{lep%d}"        , ilep).Data()  , 180     , -3.     , 3.     , prefix); }
    void fillJetEta    (string prefix , Analyses::AnalysisData& a) { for (unsigned int ijet  = 0; ijet < a.jets   .size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)  PlotUtil ::plot1D(TString::Format("jet%deta"  , ijet).Data()  , a.jets   [ijet].p4.Eta()   , a.wgt , a.hist_db , TString::Format("#eta_{jet%d}"        , ijet).Data()  , 180     , -5.     , 5.     , prefix); }
    void fillBJetEta   (string prefix , Analyses::AnalysisData& a) { for (unsigned int ibjet = 0; ibjet < a.bjets .size() && ibjet< NMAX_INDIVD_OBJ_TO_PLOT; ++ibjet) PlotUtil ::plot1D(TString::Format("bjet%deta" , ibjet).Data() , a.bjets   [ibjet].p4.Eta() , a.wgt , a.hist_db , TString::Format("#eta_{bjet%d}"       , ibjet).Data() , 180     , -5.     , 5.     , prefix); }
    void fillLepPhi    (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep  = 0; ilep < a.leptons.size() && ilep < NMAX_INDIVD_OBJ_TO_PLOT; ++ilep)  PlotUtil ::plot1D(TString::Format("lep%dphi"  , ilep).Data()  , a.leptons[ilep].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{lep%d}"        , ilep).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
    void fillJetPhi    (string prefix , Analyses::AnalysisData& a) { for (unsigned int ijet  = 0; ijet < a.jets   .size() && ijet < NMAX_INDIVD_OBJ_TO_PLOT; ++ijet)  PlotUtil ::plot1D(TString::Format("jet%dphi"  , ijet).Data()  , a.jets   [ijet].p4.Phi()   , a.wgt , a.hist_db , TString::Format("#phi_{jet%d}"        , ijet).Data()  , 180     , -3.1416 , 3.1416 , prefix); }
    void fillBJetPhi   (string prefix , Analyses::AnalysisData& a) { for (unsigned int ibjet = 0; ibjet < a.bjets .size() && ibjet< NMAX_INDIVD_OBJ_TO_PLOT; ++ibjet) PlotUtil ::plot1D(TString::Format("bjet%dphi" , ibjet).Data() , a.bjets   [ibjet].p4.Phi() , a.wgt , a.hist_db , TString::Format("#phi_{bjet%d}"       , ibjet).Data() , 180     , -3.1416 , 3.1416 , prefix); }
    /// Di object kinematics (GeV scales)
    void fillMll       (string prefix , Analyses::AnalysisData& a) { if (a.leptons.size() >= 2) PlotUtil::plot1D("mll"       , VarUtil::Mll(a)        , a.wgt , a.hist_db , "M_{#ell#ell} [GeV]" , 180 , 0. , 180.   , prefix); }
    void fillVBFMjj    (string prefix , Analyses::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("vbfmjj"    , VarUtil::Mjj(a)        , a.wgt , a.hist_db , "M_{jj} [GeV]" , 180 , 0. , 2500.  , prefix); }
    void fillVBFMbb    (string prefix , Analyses::AnalysisData& a) { if (a.bjets  .size() >= 2) PlotUtil::plot1D("vbfmbb"    , VarUtil::Mbb(a)        , a.wgt , a.hist_db , "M_{bb} [GeV]" , 180 , 0. , 2500.  , prefix); }
    void fillPtjj      (string prefix , Analyses::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("ptjj"      , VarUtil::Ptjj(a)       , a.wgt , a.hist_db , "p_{T,jj} [GeV]" , 180 , 0. , 1000.  , prefix); }
    void fillPtbb      (string prefix , Analyses::AnalysisData& a) { if (a.bjets  .size() >= 2) PlotUtil::plot1D("ptbb"      , VarUtil::Ptbb(a)       , a.wgt , a.hist_db , "p_{T,bb} [GeV]" , 180 , 0. , 1000.  , prefix); }
    void fillMjjW      (string prefix , Analyses::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("mjjw"      , VarUtil::MjjWmass(a)   , a.wgt , a.hist_db , "M_{jj,close-to-W} [GeV]" , 180 , 0. , 180.   , prefix); }
    void fillMjj       (string prefix , Analyses::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("mjj"       , VarUtil::Mjj(a)        , a.wgt , a.hist_db , "M_{jj} [GeV]" , 180 , 0. , 180.   , prefix); }
    void fillMT        (string prefix , Analyses::AnalysisData& a) { if (a.leptons.size() >= 1) PlotUtil::plot1D("mt"        , VarUtil::MT(a)         , a.wgt , a.hist_db , "M_{T} [GeV]" , 180 , 0. , 180.   , prefix); }
    void fillHT        (string prefix , Analyses::AnalysisData& a) { if (a.jets   .size() >= 1) PlotUtil::plot1D("ht"        , VarUtil::HT(a)         , a.wgt , a.hist_db , "H_{T} [GeV]" , 180 , 0. , 1200.  , prefix); }
    void fillMTll      (string prefix , Analyses::AnalysisData& a) { if (a.leptons.size() >= 2) PlotUtil::plot1D("mtll"      , VarUtil::MTll(a)       , a.wgt , a.hist_db , "M_{T,ll} [GeV]" , 180 , 0. , 400.   , prefix); }
    void fillMljClose  (string prefix , Analyses::AnalysisData& a) { if (a.jets   .size() >= 1) if (a.leptons.size() >= 1)PlotUtil::plot1D("mljclose"  , VarUtil::MljClosest(a)   , a.wgt , a.hist_db , "M_{lj,close} [GeV]" , 180 , 0. , 400.   , prefix); }
    /// Di object kinematics (angular)
    void fillDPhill    (string prefix , Analyses::AnalysisData& a) { if (a.leptons.size() >= 2) PlotUtil::plot1D("dphill"    , VarUtil::DPhill(a)     , a.wgt , a.hist_db , "#Delta#phi_{#ell#ell}" , 180 , 0. , 3.1416 , prefix); }
    void fillDEtajj    (string prefix , Analyses::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("detajj"    , VarUtil::DEtajj(a)     , a.wgt , a.hist_db , "#Delta#eta_{jj}" , 180 , 0. , 9.     , prefix); }
    void fillDRjj      (string prefix , Analyses::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("drjj"      , VarUtil::DRjj(a)       , a.wgt , a.hist_db , "#DeltaR{jj}" , 180 , 0. , 9.   , prefix); }
    void fillDEtabb    (string prefix , Analyses::AnalysisData& a) { if (a.bjets  .size() >= 2) PlotUtil::plot1D("detabb"    , VarUtil::DEtabb(a)     , a.wgt , a.hist_db , "#Delta#phi_{bb}" , 180 , 0. , 9.     , prefix); }
    void fillDPhiLepMET(string prefix , Analyses::AnalysisData& a) { if (a.leptons.size() >= 1) PlotUtil::plot1D("dphilepmet", VarUtil::DPhiLepMET(a) , a.wgt , a.hist_db , "#Delta#phi_{#ell,MET}" , 5   , 0. , 3.1416 , prefix); }
    void fillDRjjW     (string prefix , Analyses::AnalysisData& a) { if (a.jets   .size() >= 2) PlotUtil::plot1D("drjjw"     , VarUtil::DRjjWmass(a)  , a.wgt , a.hist_db , "#DeltaR{jj,close-to-W}" , 180 , 0. , 9.   , prefix); }
    /// Single object ID-related
    void fillLepDz       (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%ddz"        , ilep).Data() , a.leptons[ilep].dz                                 , a.wgt , a.hist_db , "" , 180 , 0. , 0.5, prefix); }
    void fillLepDxy      (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%ddxy"       , ilep).Data() , a.leptons[ilep].dxy                                , a.wgt , a.hist_db , "" , 180 , 0. , 0.5, prefix); }
    void fillLepIp3d     (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dip3d"      , ilep).Data() , a.leptons[ilep].ip3d                               , a.wgt , a.hist_db , "" , 180 , 0. , 10 , prefix); }
    void fillLepSip3d    (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dsip3d"     , ilep).Data() , a.leptons[ilep].sip3d                              , a.wgt , a.hist_db , "" , 180 , 0. , 10 , prefix); }
    void fillLepRelIso03 (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%drelIso03"  , ilep).Data() , a.leptons[ilep].relIso03                           , a.wgt , a.hist_db , "" , 180 , 0. , 0.4, prefix); }
    void fillLepAbsIso03 (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dabsIso03"  , ilep).Data() , a.leptons[ilep].relIso03 * a.leptons[ilep].p4.Pt() , a.wgt , a.hist_db , "" , 180 , 0. , 5. , prefix); }
    void fillLepMiniIso03(string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dminiIso03" , ilep).Data() , a.leptons[ilep].miniRelIsoCMS3_EA                  , a.wgt , a.hist_db , "" , 180 , 0. , 0.4, prefix); }
    void fillLepPtRel    (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dptrel"     , ilep).Data() , a.leptons[ilep].ptRel                              , a.wgt , a.hist_db , "" , 180 , 0. , 30., prefix); }
    void fillLepPtRatio  (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dptratio"   , ilep).Data() , a.leptons[ilep].ptRatio                            , a.wgt , a.hist_db , "" , 180 , 0. , 1.0, prefix); }
    void fillLepID       (string prefix , Analyses::AnalysisData& a) { for (unsigned int ilep = 0; ilep < a.leptons.size(); ++ilep) PlotUtil::plot1D(TString::Format("lep%dID"        , ilep).Data() , a.leptons[ilep].id                                 , a.wgt , a.hist_db , "" , 180 , 0. , 5  , prefix); }
    void fillJetID       (string prefix , Analyses::AnalysisData& a) { for (unsigned int ijet = 0; ijet < a.jets   .size(); ++ijet) PlotUtil::plot1D(TString::Format("jet%dID"        , ijet).Data() , a.jets   [ijet].id                                 , a.wgt , a.hist_db , "" ,   2 , 0. , 30 , prefix); }

    void fillCutflow    (string prefix, Analyses::AnalysisData& a, int ibin)
    {
      PlotUtil::plot1D("cutflow"   , ibin, a.wgt, a.hist_db, "", 20, 0., 20., prefix);
      PlotUtil::plot1D("rawcutflow", ibin,    1., a.hist_db, "", 20, 0., 20., prefix);
    }

  }

  namespace TreeUtil
  {

    TreeData treedata;
    TFile* skimfile = 0;
    TTree* skimtree = 0;

    void initTreeData()
    {
      for (auto& v: treedata.mapint) v.second = 0;
      for (auto& v: treedata.mapvfloat) (*v.second).clear();
      for (auto& v: treedata.mapvint) (*v.second).clear();
    }

    void createIntBranch(TTree* tree, TString name) { treedata.mapint[name] = 0; tree->Branch(name, &(treedata.mapint[name]), name+"/I"); }
    void createFloatBranch(TTree* tree, TString name) { treedata.mapfloat[name] = 0; tree->Branch(name, &(treedata.mapfloat[name]), name+"/F"); }
    void createVIntBranch(TTree* tree, TString name) { treedata.mapvint[name] = new std::vector<int>(); tree->Branch(name, &(treedata.mapvint[name])); }
    void createVFloatBranch(TTree* tree, TString name) { treedata.mapvfloat[name] = new std::vector<float>(); tree->Branch(name, &(treedata.mapvfloat[name])); }

    void setIntBranch(TString name, int val) { treedata.mapint[name] = val; }
    void setFloatBranch(TString name, float val) { treedata.mapfloat[name] = val; }
    void pushbackVIntBranch(TString name, int val) { (*(treedata.mapvint[name])).push_back(val); }
    void pushbackVFloatBranch(TString name, float val) { (*(treedata.mapvfloat[name])).push_back(val); }

    void create4VecBranch(TTree* tree, TString name)
    {
      createIntBranch(tree, name+"_n");
      createVFloatBranch(tree, name+"_pt");
      createVFloatBranch(tree, name+"_eta");
      createVFloatBranch(tree, name+"_phi");
      createVFloatBranch(tree, name+"_mass");
      createVFloatBranch(tree, name+"_energy");
    }

    void createTruthBranch(TTree* tree, TString name)
    {
      create4VecBranch(tree, name);
      createVIntBranch(tree, name+"_pdgId");
      createVIntBranch(tree, name+"_status");
      createVIntBranch(tree, name+"_motherId");
      createVIntBranch(tree, name+"_grandmotherId");
    }

    void createLeptonBranch(TTree* tree, TString name)
    {
      create4VecBranch  (tree, name);
      createVFloatBranch(tree, name+"_dxy");
      createVFloatBranch(tree, name+"_dz");
      createVFloatBranch(tree, name+"_ip3d");
      createVFloatBranch(tree, name+"_sip3d");
      createVIntBranch  (tree, name+"_tightcharge");
      createVIntBranch  (tree, name+"_charge");
      createVIntBranch  (tree, name+"_pdgId");
      createVIntBranch  (tree, name+"_id");
      createVFloatBranch(tree, name+"_ptRatio");
      createVFloatBranch(tree, name+"_ptRel");
      createVFloatBranch(tree, name+"_relIso03");
      createVFloatBranch(tree, name+"_relIso03DB");
      createVFloatBranch(tree, name+"_relIso03EA");
      createVFloatBranch(tree, name+"_miniRelIsoCMS3_EA");
      createVFloatBranch(tree, name+"_miniRelIsoCMS3_DB");
      // Muon specifics
      createVFloatBranch(tree, name+"_muPOverP");
      createVIntBranch  (tree, name+"_muPidPFMuon");
      createVIntBranch  (tree, name+"_muType");
      createVFloatBranch(tree, name+"_muChi2OverNDof");
      createVFloatBranch(tree, name+"_muChi2LocalPosition");
      createVFloatBranch(tree, name+"_muTrkKink");
      createVFloatBranch(tree, name+"_muValidHitFraction");
      createVFloatBranch(tree, name+"_muSegmCompatibility");
      createVIntBranch  (tree, name+"_muGFitValidSTAHits");
      createVIntBranch  (tree, name+"_muNMatchedStations");
      createVIntBranch  (tree, name+"_muValidPixelHits");
      createVIntBranch  (tree, name+"_muNLayers");
      // Electron specifics
      createVFloatBranch(tree, name+"_elEtaSC");
      createVFloatBranch(tree, name+"_elSigmaIEtaIEta_full5x5");
      createVFloatBranch(tree, name+"_elHOverE");
      createVFloatBranch(tree, name+"_elMva");
      createVFloatBranch(tree, name+"_elDEtaIn");
      createVFloatBranch(tree, name+"_elDPhiIn");
      createVFloatBranch(tree, name+"_elEpRatio");
      createVIntBranch  (tree, name+"_elConvVeto");
      createVIntBranch  (tree, name+"_elNmiss");
    }

    void createJetBranch(TTree* tree, TString name)
    {
      create4VecBranch  (tree, name);
      createVFloatBranch(tree, name+"_btagCSV");
      createVFloatBranch(tree, name+"_rawPt");
      createVFloatBranch(tree, name+"_mcPt");
      createVIntBranch  (tree, name+"_mcFlavour");
      createVIntBranch  (tree, name+"_hadronFlavour");
      createVFloatBranch(tree, name+"_area");
      createVFloatBranch(tree, name+"_undoJEC");
      createVFloatBranch(tree, name+"_jecCorr");
      createVFloatBranch(tree, name+"_jecCorrUp");
      createVFloatBranch(tree, name+"_jecCorrDn");
      createVFloatBranch(tree, name+"_chf");
      createVFloatBranch(tree, name+"_nhf");
      createVFloatBranch(tree, name+"_cef");
      createVFloatBranch(tree, name+"_nef");
      createVFloatBranch(tree, name+"_muf");
      createVFloatBranch(tree, name+"_cm");
      createVFloatBranch(tree, name+"_nm");
      createVFloatBranch(tree, name+"_puValue");
      createVFloatBranch(tree, name+"_mcdr");
      createVIntBranch  (tree, name+"_npfcand");
      createVIntBranch  (tree, name+"_id");
      createVIntBranch  (tree, name+"_puId");
      createVIntBranch  (tree, name+"_puIdpuppi");
      createVIntBranch  (tree, name+"_FSveto");
    }

    void createMETBranch(TTree* tree, TString name)
    {
      createFloatBranch(tree, name+"_pt");
      createFloatBranch(tree, name+"_phi");
    }

    void createEventInfoBranch(TTree* tree, TString name)
    {
      createIntBranch(tree, name+"_run");
      createIntBranch(tree, name+"_lumi");
      createIntBranch(tree, name+"_event");
      createFloatBranch(tree, name+"_scale1fb");
    }

    void setTruths(Analyses::AnalysisData& ana_data, TString name)
    {
      setIntBranch(name+"_n", ana_data.truths.size());
      for (auto& truth : ana_data.truths)
      {
        pushback4Vec(truth.p4, name);
        pushbackVIntBranch(name+"_pdgId", truth.pdgId);
        pushbackVIntBranch(name+"_status", truth.status);
        pushbackVIntBranch(name+"_motherId", truth.motherId);
        pushbackVIntBranch(name+"_grandmotherId", truth.grandmotherId);
      }
    }

    void setLeptons(Analyses::AnalysisData& ana_data, TString name)
    {
      setIntBranch(name+"_n", ana_data.leptons.size());
      for (auto& lepton : ana_data.leptons)
      {
        pushback4Vec(lepton.p4, name);
        pushbackVFloatBranch(name+"_dxy", lepton.dxy);
        pushbackVFloatBranch(name+"_dz", lepton.dz);
        pushbackVFloatBranch(name+"_ip3d", lepton.ip3d);
        pushbackVFloatBranch(name+"_sip3d", lepton.sip3d);
        pushbackVIntBranch  (name+"_tightcharge", lepton.tightcharge);
        pushbackVIntBranch  (name+"_charge", lepton.charge);
        pushbackVIntBranch  (name+"_pdgId", lepton.pdgId);
        pushbackVIntBranch  (name+"_id", lepton.id);
        pushbackVFloatBranch(name+"_ptRatio", lepton.ptRatio);
        pushbackVFloatBranch(name+"_ptRel", lepton.ptRel);
        pushbackVFloatBranch(name+"_relIso03", lepton.relIso03);
        pushbackVFloatBranch(name+"_relIso03DB", lepton.relIso03DB);
        pushbackVFloatBranch(name+"_relIso03EA", lepton.relIso03EA);
        pushbackVFloatBranch(name+"_miniRelIsoCMS3_EA", lepton.miniRelIsoCMS3_EA);
        pushbackVFloatBranch(name+"_miniRelIsoCMS3_DB", lepton.miniRelIsoCMS3_DB);
        // Muon specifics
        pushbackVFloatBranch(name+"_muPOverP", lepton.muPOverP);
        pushbackVIntBranch  (name+"_muPidPFMuon", lepton.muPidPFMuon);
        pushbackVIntBranch  (name+"_muType", lepton.muType);
        pushbackVFloatBranch(name+"_muChi2OverNDof", lepton.muChi2OverNDof);
        pushbackVFloatBranch(name+"_muChi2LocalPosition", lepton.muChi2LocalPosition);
        pushbackVFloatBranch(name+"_muTrkKink", lepton.muTrkKink);
        pushbackVFloatBranch(name+"_muValidHitFraction", lepton.muValidHitFraction);
        pushbackVFloatBranch(name+"_muSegmCompatibility", lepton.muSegmCompatibility);
        pushbackVIntBranch  (name+"_muGFitValidSTAHits", lepton.muGFitValidSTAHits);
        pushbackVIntBranch  (name+"_muNMatchedStations", lepton.muNMatchedStations);
        pushbackVIntBranch  (name+"_muValidPixelHits", lepton.muValidPixelHits);
        pushbackVIntBranch  (name+"_muNLayers", lepton.muNLayers);
        // Electron specifics
        pushbackVFloatBranch(name+"_elEtaSC", lepton.elEtaSC);
        pushbackVFloatBranch(name+"_elSigmaIEtaIEta_full5x5", lepton.elSigmaIEtaIEta_full5x5);
        pushbackVFloatBranch(name+"_elHOverE", lepton.elHOverE);
        pushbackVFloatBranch(name+"_elMva", lepton.elMva);
        pushbackVFloatBranch(name+"_elDEtaIn", lepton.elDEtaIn);
        pushbackVFloatBranch(name+"_elDPhiIn", lepton.elDPhiIn);
        pushbackVFloatBranch(name+"_elEpRatio", lepton.elEpRatio);
        pushbackVIntBranch  (name+"_elConvVeto", lepton.elConvVeto);
        pushbackVIntBranch  (name+"_elNmiss", lepton.elNmiss);
      }
    }

    void setJets(Analyses::AnalysisData& ana_data, TString name)
    {
      setIntBranch(name+"_n", ana_data.jets.size());
      for (auto& jet : ana_data.jets)
      {
        pushback4Vec(jet.p4, name);
        pushbackVFloatBranch(name+"_btagCSV", jet.btagCSV);
        pushbackVFloatBranch(name+"_rawPt", jet.rawPt);
        pushbackVFloatBranch(name+"_mcPt", jet.mcPt);
        pushbackVIntBranch  (name+"_mcFlavour", jet.mcFlavour);
        pushbackVIntBranch  (name+"_hadronFlavour", jet.hadronFlavour);
        pushbackVFloatBranch(name+"_area", jet.area);
        pushbackVFloatBranch(name+"_undoJEC", jet.undoJEC);
        pushbackVFloatBranch(name+"_jecCorr", jet.jecCorr);
        pushbackVFloatBranch(name+"_jecCorrUp", jet.jecCorrUp);
        pushbackVFloatBranch(name+"_jecCorrDn", jet.jecCorrDn);
        pushbackVFloatBranch(name+"_chf", jet.chf);
        pushbackVFloatBranch(name+"_nhf", jet.nhf);
        pushbackVFloatBranch(name+"_cef", jet.cef);
        pushbackVFloatBranch(name+"_nef", jet.nef);
        pushbackVFloatBranch(name+"_muf", jet.muf);
        pushbackVFloatBranch(name+"_cm", jet.cm);
        pushbackVFloatBranch(name+"_nm", jet.nm);
        pushbackVFloatBranch(name+"_puValue", jet.puValue);
        pushbackVFloatBranch(name+"_mcdr", jet.mcdr);
        pushbackVIntBranch  (name+"_npfcand", jet.npfcand);
        pushbackVIntBranch  (name+"_id", jet.id);
        pushbackVIntBranch  (name+"_puId", jet.puId);
        pushbackVIntBranch  (name+"_puIdpuppi", jet.puIdpuppi);
        pushbackVIntBranch  (name+"_FSveto", jet.FSveto);
      }
    }

    void setMET(Analyses::AnalysisData& ana_data, TString name)
    {
      setFloatBranch(name+"_pt", ana_data.met.p4.Pt());
      setFloatBranch(name+"_phi", ana_data.met.p4.Phi());
    }

    void setEventInfo(Analyses::AnalysisData& ana_data, TString name)
    {
      setIntBranch(name+"_run", ana_data.eventinfo.run);
      setIntBranch(name+"_lumi", ana_data.eventinfo.lumi);
      setIntBranch(name+"_event", ana_data.eventinfo.event);
      setFloatBranch(name+"_scale1fb", ana_data.eventinfo.scale1fb);
    }

    void pushback4Vec(TLorentzVector p4, TString name)
    {
      pushbackVFloatBranch(name+"_pt", p4.Pt());
      pushbackVFloatBranch(name+"_eta", p4.Eta());
      pushbackVFloatBranch(name+"_phi", p4.Phi());
      pushbackVFloatBranch(name+"_mass", p4.M());
      pushbackVFloatBranch(name+"_energy", p4.E());
    }

    void createSkimTree(const char* filename)
    {
      if (LoopUtil::getCurrentTFileName().Contains("skimtree")) return;
      printf("[Ditto::HistUtil::saveSkimTree] Creating %s to hold skimmed TTree\n", filename);
      skimfile = new TFile(filename, "recreate");
      skimtree = LoopUtil::getCurrentTTree()->CloneTree(0);
    }

    void fillSkimTree()
    {
      if (LoopUtil::getCurrentTFileName().Contains("skimtree")) return;
      skimtree->Fill();
    }

    void saveSkimTree()
    {
      if (!skimtree) return;
      printf("[Ditto::HistUtil::saveSkimTree] Writing skimmed TTree to %s\n", skimfile->GetName());
      skimfile->cd();
      skimtree->Write();
      delete skimtree;
      skimfile->Write();
      skimfile->Close();
    }

  }

}

//eof
