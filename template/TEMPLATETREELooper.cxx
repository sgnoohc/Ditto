// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include "TEMPLATETREENAMELooper.h"

//TEMPLATETREENAME mytree;
Analyses::AnalysisData ana_data;
TString output_name;

//______________________________________________________________________________________
int TEMPLATETREENAMELooper(TChain* chain, TString output_name, int nevents)
{

  // Before the loop set up some configuration, histograms and etc.
  beforeLoop(chain, output_name, nevents);

  // During the event loop process each event one by one
  loop();

  // After the loop is done, save histograms and etc.
  afterLoop();

  return 0;
}

//______________________________________________________________________________________
void beforeLoop(TChain* chain, TString output_name_, int nevents)
{

  // Fun start ASCII art
  PrintUtil::start();

  // Initialize configurations for event looping
  LoopUtil::resetLoopCondition(chain, nevents);

  output_name = output_name_;

}


//______________________________________________________________________________________
void loop()
{

  // Loop over file:ttree -> and loop over events in ttree
  // (usually I only have one file each.. so kinda redundant)
  while (LoopUtil::nextFileAndLoadTTreeWithName("TEMPLATETREESHORTNAME"))
  {

    initTEMPLATETREENAME();

    // Loop over the TTree
    while (LoopUtil::nextEvent())
    {

      if (LoopUtil::isAllEventsProcessed()) break;

      loadTEMPLATETREENAMEEvent();

      //=================================================================
      // <3 of the code
      // Do whatever you want to in the following function for each event
      //=================================================================
      processTEMPLATETREENAMEEvent();

    } // End TTree loop

  } // End Loop over files
}

//______________________________________________________________________________________
void initTEMPLATETREENAME()
{
  // Init the Class
  mytree.Init(LoopUtil::getCurrentTTree());
}

//______________________________________________________________________________________
void loadTEMPLATETREENAMEEvent()
{
  mytree.LoadTree(LoopUtil::getCurrentTTreeEventIndex());
  mytree.GetEntry(LoopUtil::getCurrentTTreeEventIndex());
}

//______________________________________________________________________________________
void processTEMPLATETREENAMEEvent()
{
  /// Set objects
  getObjects();

  /// Fill histograms
  // HistUtil::fillStdHistograms("", ana_data);
}

//______________________________________________________________________________________
void getObjects()
{
  /// Get objects
  //ana_data.leptons = getLeptons(/*mytree*/);
  //ana_data.jets    = getJets(/*mytree*/);
  //ana_data.met     = getMET(/*mytree*/);
  //ana_data.wgt     = mytree.evt_scale1fb;
}

//______________________________________________________________________________________
void afterLoop()
{
  // Save histograms
  PlotUtil::savePlots(ana_data.hist_db, output_name.Data());

  // Fun exit
  PrintUtil::exit();
}

//eof
