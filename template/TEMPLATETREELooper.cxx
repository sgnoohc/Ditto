// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include "TEMPLATETREENAMELooper.h"

TEMPLATETREENAME mytree;
//ObjUtil::Leptons leptons;
//ObjUtil::Jets jets;
//ObjUtil::Jets bjets;
//ObjUtil::MET met;

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
void beforeLoop(TChain* chain, TString output_name, int nevents)
{

  // Fun start ASCII art
  PrintUtil::start();

  // Initialize configurations for event looping
  LoopUtil::resetLoopCondition(chain, nevents);

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
  setObjects();
}

//______________________________________________________________________________________
void setObjects()
{
  /// Get and set objects
  //leptons = getLeptons(mytree);
  //jets = getJets(mytree);
  //met = getMET(mytree);
}

//______________________________________________________________________________________
void afterLoop()
{
  // Fun exit
  PrintUtil::exit();
}

//eof
