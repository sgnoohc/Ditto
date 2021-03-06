// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include "TEMPLATETREENAMELooper.h"

//TEMPLATETREENAME mytree;
ObjUtil::AnalysisData ana_data;
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

  // Replace all ".root" added accidentally
  output_name_.ReplaceAll(".root", "");
  LoopUtil::output_name = output_name_;

  // If output_name does not contain "_skimtree" then skim the event
  //if (!output_name.Contains("_skimtree"))
  //  LoopUtil::setDoSkim();

  // If output_name contains "_skimtree" remove it.
  LoopUtil::output_name.ReplaceAll("_skimtree", "");

}


//______________________________________________________________________________________
void loop()
{

  // Loop over file:ttree -> and loop over events in ttree
  // (usually I only have one file each.. so kinda redundant)
  while (LoopUtil::nextFileAndLoadTTreeWithName("TEMPLATETREESHORTNAME"))
  {

    initTEMPLATETREENAME();

    // I am assuming I only run one file at a time
    // NOTE: Later I should probably update this to be more general
    if (LoopUtil::doskim) TreeUtil::createSkimTree((LoopUtil::output_name+"_skimtree.root").Data());

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
  //if (LoopUtil::doskim) mytree.LoadAllBranches();
}

//______________________________________________________________________________________
void loadTEMPLATETREENAMEEvent()
{
  //mytree.LoadTree(LoopUtil::getCurrentTTreeEventIndex());
  mytree.GetEntry(LoopUtil::getCurrentTTreeEventIndex());
}

//______________________________________________________________________________________
void processTEMPLATETREENAMEEvent()
{
  /// Set objects
  getObjects();

  /// Fill histograms
  // HistUtil::fillStdHistograms("", ana_data);

  //bool pass = Analyses::SM_VBS_WW_lvjj(ana_data);

  /// Fill skimmed ttree
  //if (pass)
  //  TreeUtil::fillSkimTree();
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
  PlotUtil::savePlots(ana_data.hist_db, (LoopUtil::output_name+"_hist.root").Data());

  // Save skimmmed tree
  if (LoopUtil::doskim) TreeUtil::saveSkimTree();

  // Fun exit
  PrintUtil::exit();
}

//eof
