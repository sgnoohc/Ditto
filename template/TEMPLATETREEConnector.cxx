// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include "TREECLASSNAMEConnector.h"

ObjUtil::Leptons getLeptons(TREECLASSNAME& mytree)
{
  ObjUtil::Leptons leptons;
  return leptons;
}

ObjUtil::Jets getJets(TREECLASSNAME& mytree)
{
  ObjUtil::Jets jets;
  return jets;
}

ObjUtil::Jets getBJets(TREECLASSNAME& mytree)
{
  ObjUtil::Jets jets;
  return jets;
}

ObjUtil::METs getMETs(TREECLASSNAME& mytree)
{
  ObjUtil::METs mets;
  return mets;
}

ObjUtil::MET getMET(TREECLASSNAME& mytree)
{
  ObjUtil::MET met;
  return met;
}

//eof

// MadGraph lhe output
// ------------------------------------------------------------------
//  for (unsigned int ip = 0; ip < mytree.P_X->size(); ++ip)
//  {
//    ObjUtil::Jet jet;
//    float px     = mytree.P_X -> at(ip);
//    float py     = mytree.P_Y -> at(ip);
//    float pz     = mytree.P_Z -> at(ip);
//    float energy = mytree.E   -> at(ip);
//    int   pdgId  = mytree.PID -> at(ip);
//    if (abs(pdgId) <= 5 || abs(pdgId) == 21)
//    {
//      jet.id = pdgId;
//      jet.p4.SetXYZT(px, py, pz, energy);
//      jets.push_back(jet);
//    }
//  }
//  std::sort(jets.begin(), jets.end(), comparator_pt<ObjUtil::Jet>);
// ------------------------------------------------------------------
