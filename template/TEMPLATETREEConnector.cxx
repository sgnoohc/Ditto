// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

#include "TREECLASSNAMEConnector.h"

ObjUtil::Leptons getLeptons(/*TREECLASSNAME& mytree*/)
{
  ObjUtil::Leptons leptons;
  for (int ilep = 0; ilep < mytree.lep_n(); ++ilep)
  {
    ObjUtil::Lepton lepton;
    lepton.p4.SetPtEtaPhiM(mytree.lep_pt().at(ilep),mytree.lep_eta().at(ilep),mytree.lep_phi().at(ilep),mytree.lep_mass().at(ilep));
    // General
    lepton.dxy = mytree.lep_dxy().at(ilep);
    lepton.dz = mytree.lep_dz().at(ilep);
    lepton.ip3d = mytree.lep_ip3d().at(ilep);
    lepton.sip3d = mytree.lep_sip3d().at(ilep);
    lepton.tightcharge = mytree.lep_tightcharge().at(ilep);
    lepton.charge = mytree.lep_charge().at(ilep);
    lepton.pdgId = mytree.lep_pdgId().at(ilep);
    lepton.id = mytree.lep_id().at(ilep);
    // Isolation related
    lepton.ptRatio = mytree.lep_ptRatio().at(ilep);
    lepton.ptRel = mytree.lep_ptRel().at(ilep);
    lepton.relIso03 = mytree.lep_relIso03().at(ilep);
    lepton.relIso03DB = mytree.lep_relIso03DB().at(ilep);
    lepton.relIso03EA = mytree.lep_relIso03EA().at(ilep);
    lepton.miniRelIsoCMS3_EA = mytree.lep_miniRelIsoCMS3_EA().at(ilep);
    lepton.miniRelIsoCMS3_DB = mytree.lep_miniRelIsoCMS3_DB().at(ilep);
    // Muon specifics
    lepton.muPOverP = mytree.lep_muPOverP().at(ilep);
    lepton.muPidPFMuon = mytree.lep_muPidPFMuon().at(ilep);
    lepton.muType = mytree.lep_muType().at(ilep);
    lepton.muChi2OverNDof = mytree.lep_muChi2OverNDof().at(ilep);
    lepton.muChi2LocalPosition = mytree.lep_muChi2LocalPosition().at(ilep);
    lepton.muTrkKink = mytree.lep_muTrkKink().at(ilep);
    lepton.muValidHitFraction = mytree.lep_muValidHitFraction().at(ilep);
    lepton.muSegmCompatibility = mytree.lep_muSegmCompatibility().at(ilep);
    // Electron specifics
    lepton.elEtaSC = mytree.lep_elEtaSC().at(ilep);
    lepton.elSigmaIEtaIEta_full5x5 = mytree.lep_elSigmaIEtaIEta_full5x5().at(ilep);
    lepton.elHOverE = mytree.lep_elHOverE().at(ilep);
    lepton.elMva = mytree.lep_elMva().at(ilep);
    lepton.elDEtaIn = mytree.lep_elDEtaIn().at(ilep);
    lepton.elDPhiIn = mytree.lep_elDPhiIn().at(ilep);
    lepton.elEpRatio = mytree.lep_elEpRatio().at(ilep);
    lepton.elConvVeto = mytree.lep_elConvVeto().at(ilep);
    lepton.elNmiss = mytree.lep_elNmiss().at(ilep);
  }
  return leptons;
}

ObjUtil::Jets getJets(/*TREECLASSNAME& mytree*/)
{
  ObjUtil::Jets jets;
  for (int ilep = 0; ilep < mytree.lep_n(); ++ilep)
  {
    ObjUtil::Jet jet;
    jet.p4.SetPtEtaPhiM(mytree.jet_pt().at(ilep),mytree.jet_eta().at(ilep),mytree.jet_phi().at(ilep),mytree.jet_mass().at(ilep));
    jet.btagCSV = mytree.jet_btagCSV().at(ilep);
    jet.rawPt = mytree.jet_rawPt().at(ilep);
    jet.mcPt = mytree.jet_mcPt().at(ilep);
    jet.mcFlavour = mytree.jet_mcFlavour().at(ilep);
    jet.hadronFlavour = mytree.jet_hadronFlavour().at(ilep);
    jet.area = mytree.jet_area().at(ilep);
    jet.undoJEC = mytree.jet_undoJEC().at(ilep);
    jet.jecCorr = mytree.jet_jecCorr().at(ilep);
    jet.jecCorrUp = mytree.jet_jecCorrUp().at(ilep);
    jet.jecCorrDn = mytree.jet_jecCorrDn().at(ilep);
    jet.chf = mytree.jet_chf().at(ilep);
    jet.id = mytree.jet_id().at(ilep);
    jet.puId = mytree.jet_puId().at(ilep);
    jet.puIdpuppi = mytree.jet_puIdpuppi().at(ilep);
    jet.FSveto = mytree.jet_FSveto().at(ilep);
  }
  return jets;
}

ObjUtil::Jets getBJets(/*TREECLASSNAME& mytree*/)
{
  ObjUtil::Jets jets;
  return jets;
}

ObjUtil::METs getMETs(/*TREECLASSNAME& mytree*/)
{
  ObjUtil::METs mets;
  return mets;
}

ObjUtil::MET getMET(/*TREECLASSNAME& mytree*/)
{
  ObjUtil::MET met;
  met.p4.SetPtEtaPhiE(mytree.met_pt, 0, mytree.met_phi, mytree.met_pt);
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
