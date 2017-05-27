// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu


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
    createVFloatBranch(tree, name+"_relIso03EAv2");
    createVFloatBranch(tree, name+"_relIso04");
    createVFloatBranch(tree, name+"_relIso04DB");
    createVFloatBranch(tree, name+"_relIso04EA");
    createVFloatBranch(tree, name+"_relIso04EAv2");
    createVFloatBranch(tree, name+"_miniRelIsoCMS3_EA");
    createVFloatBranch(tree, name+"_miniRelIsoCMS3_EAv2");
    createVFloatBranch(tree, name+"_miniRelIsoCMS3_DB");
    createVFloatBranch(tree, name+"_relIso005EAstudy");
    createVFloatBranch(tree, name+"_relIso010EAstudy");
    createVFloatBranch(tree, name+"_relIso015EAstudy");
    createVFloatBranch(tree, name+"_relIso020EAstudy");
    createVFloatBranch(tree, name+"_relIso025EAstudy");
    createVFloatBranch(tree, name+"_relIso030EAstudy");
    createVFloatBranch(tree, name+"_relIso035EAstudy");
    createVFloatBranch(tree, name+"_relIso040EAstudy");
    createVFloatBranch(tree, name+"_relIso045EAstudy");
    createVFloatBranch(tree, name+"_relIso050EAstudy");
    createVFloatBranch(tree, name+"_relIso005EAstudyv2");
    createVFloatBranch(tree, name+"_relIso010EAstudyv2");
    createVFloatBranch(tree, name+"_relIso015EAstudyv2");
    createVFloatBranch(tree, name+"_relIso020EAstudyv2");
    createVFloatBranch(tree, name+"_relIso025EAstudyv2");
    createVFloatBranch(tree, name+"_relIso030EAstudyv2");
    createVFloatBranch(tree, name+"_relIso035EAstudyv2");
    createVFloatBranch(tree, name+"_relIso040EAstudyv2");
    createVFloatBranch(tree, name+"_relIso045EAstudyv2");
    createVFloatBranch(tree, name+"_relIso050EAstudyv2");
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
    createVFloatBranch(tree, name+"_elMvaRaw");
    createVFloatBranch(tree, name+"_elMva");
    createVFloatBranch(tree, name+"_elDEtaIn");
    createVFloatBranch(tree, name+"_elDPhiIn");
    createVFloatBranch(tree, name+"_elEpRatio");
    createVIntBranch  (tree, name+"_elConvVeto");
    createVIntBranch  (tree, name+"_elNmiss");
    createVIntBranch  (tree, name+"_isFromX");
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
    createIntBranch(tree, name+"_nEvts");
//	    createIntBranch(tree, name+"_pileup");
    createIntBranch(tree, name+"_nvtx");
    createFloatBranch(tree, name+"_scale1fb");
  }

  void setTruths(ObjUtil::AnalysisData& ana_data, TString name)
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

  void setLeptons(ObjUtil::AnalysisData& ana_data, TString name)
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
      pushbackVFloatBranch(name+"_relIso03EAv2", lepton.relIso03EAv2);
      pushbackVFloatBranch(name+"_relIso04", lepton.relIso04);
      pushbackVFloatBranch(name+"_relIso04DB", lepton.relIso04DB);
      pushbackVFloatBranch(name+"_relIso04EA", lepton.relIso04EA);
      pushbackVFloatBranch(name+"_relIso04EAv2", lepton.relIso04EAv2);
      pushbackVFloatBranch(name+"_miniRelIsoCMS3_EA", lepton.miniRelIsoCMS3_EA);
      pushbackVFloatBranch(name+"_miniRelIsoCMS3_EAv2", lepton.miniRelIsoCMS3_EAv2);
      pushbackVFloatBranch(name+"_miniRelIsoCMS3_DB", lepton.miniRelIsoCMS3_DB);
      pushbackVFloatBranch(name+"_relIso005EAstudy", lepton.relIso005EAstudy);
      pushbackVFloatBranch(name+"_relIso010EAstudy", lepton.relIso010EAstudy);
      pushbackVFloatBranch(name+"_relIso015EAstudy", lepton.relIso015EAstudy);
      pushbackVFloatBranch(name+"_relIso020EAstudy", lepton.relIso020EAstudy);
      pushbackVFloatBranch(name+"_relIso025EAstudy", lepton.relIso025EAstudy);
      pushbackVFloatBranch(name+"_relIso030EAstudy", lepton.relIso030EAstudy);
      pushbackVFloatBranch(name+"_relIso035EAstudy", lepton.relIso035EAstudy);
      pushbackVFloatBranch(name+"_relIso040EAstudy", lepton.relIso040EAstudy);
      pushbackVFloatBranch(name+"_relIso045EAstudy", lepton.relIso045EAstudy);
      pushbackVFloatBranch(name+"_relIso050EAstudy", lepton.relIso050EAstudy);
      pushbackVFloatBranch(name+"_relIso005EAstudyv2", lepton.relIso005EAstudyv2);
      pushbackVFloatBranch(name+"_relIso010EAstudyv2", lepton.relIso010EAstudyv2);
      pushbackVFloatBranch(name+"_relIso015EAstudyv2", lepton.relIso015EAstudyv2);
      pushbackVFloatBranch(name+"_relIso020EAstudyv2", lepton.relIso020EAstudyv2);
      pushbackVFloatBranch(name+"_relIso025EAstudyv2", lepton.relIso025EAstudyv2);
      pushbackVFloatBranch(name+"_relIso030EAstudyv2", lepton.relIso030EAstudyv2);
      pushbackVFloatBranch(name+"_relIso035EAstudyv2", lepton.relIso035EAstudyv2);
      pushbackVFloatBranch(name+"_relIso040EAstudyv2", lepton.relIso040EAstudyv2);
      pushbackVFloatBranch(name+"_relIso045EAstudyv2", lepton.relIso045EAstudyv2);
      pushbackVFloatBranch(name+"_relIso050EAstudyv2", lepton.relIso050EAstudyv2);
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
      pushbackVFloatBranch(name+"_elMvaRaw", lepton.elMvaRaw);
      pushbackVFloatBranch(name+"_elMva", lepton.elMva);
      pushbackVFloatBranch(name+"_elDEtaIn", lepton.elDEtaIn);
      pushbackVFloatBranch(name+"_elDPhiIn", lepton.elDPhiIn);
      pushbackVFloatBranch(name+"_elEpRatio", lepton.elEpRatio);
      pushbackVIntBranch  (name+"_elConvVeto", lepton.elConvVeto);
      pushbackVIntBranch  (name+"_elNmiss", lepton.elNmiss);
      pushbackVIntBranch  (name+"_isFromX", lepton.isFromX);
    }
  }

  void setJets(ObjUtil::AnalysisData& ana_data, TString name)
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

  void setMET(ObjUtil::AnalysisData& ana_data, TString name)
  {
    setFloatBranch(name+"_pt", ana_data.met.p4.Pt());
    setFloatBranch(name+"_phi", ana_data.met.p4.Phi());
  }

  void setEventInfo(ObjUtil::AnalysisData& ana_data, TString name)
  {
    setIntBranch(name+"_run", ana_data.eventinfo.run);
    setIntBranch(name+"_lumi", ana_data.eventinfo.lumi);
    setIntBranch(name+"_event", ana_data.eventinfo.event);
    setIntBranch(name+"_nEvts", ana_data.eventinfo.nEvts);
//	    setIntBranch(name+"_pileup", ana_data.eventinfo.pileup);
    setIntBranch(name+"_nvtx", ana_data.eventinfo.nvtx);
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
    printf("[Ditto::HistUtil::saveSkimTree] Creating %s to hold skimmed TTree\n", filename);
    skimfile = new TFile(filename, "recreate");
    skimtree = LoopUtil::getCurrentTTree()->CloneTree(0);
  }

  void fillSkimTree()
  {
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
