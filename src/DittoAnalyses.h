// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

namespace Analyses
{

  template <class T>
    void selectObjs(std::vector<T>& objs, std::function<bool (T&)> isgoodobj)
    {
      std::vector<T> goodobjs;
      for (auto& obj: objs) if (isgoodobj(obj)) goodobjs.push_back(obj);
      objs = std::vector<T>(goodobjs);
    }

  /// Electrons
  bool isElectronPOGMVAIDCut(ObjUtil::Lepton& lepton,
      float barrel_highpt_mvacut    , float barrel_lowpt_mvacut    , float barrel_lowerpt_mvacut    ,
      float transition_highpt_mvacut, float transition_lowpt_mvacut, float transition_lowerpt_mvacut,
      float endcap_highpt_mvacut    , float endcap_lowpt_mvacut    , float endcap_lowerpt_mvacut);
  bool isElectronPOGCutBasedIDCut(ObjUtil::Lepton& lepton,
      float barrel_elSigmaIEtaIEta_full5x5_cut , float barrel_abs_elDEtaIn_cut , float barrel_abs_elDPhiIn_cut ,
      float barrel_elHOverE_cut                , float barrel_relIso03EA_cut   , float barrel_elEpRatio_cut    , int barrel_elNmiss_cut ,
      float endcap_elSigmaIEtaIEta_full5x5_cut , float endcap_abs_elDEtaIn_cut , float endcap_abs_elDPhiIn_cut ,
      float endcap_elHOverE_cut                , float endcap_relIso03EA_cut   , float endcap_elEpRatio_cut    , int endcap_elNmiss_cut);
  bool isTriggerSafenoIso_v1(ObjUtil::Lepton& lepton);
  bool isMediumElectronPOGCutbased(ObjUtil::Lepton& lepton);

  /// Muons
  bool isLooseMuonPOG(ObjUtil::Lepton& lepton);
  bool isMediumMuonPOG(ObjUtil::Lepton& lepton);

  /// Jets
  bool isLoosePFJet_Summer16_v1(ObjUtil::Jet& jet);

  /// B-tagging
  bool isMediumBJet(ObjUtil::Jet& jet);
  bool isLooseBJet(ObjUtil::Jet& jet);

  /// Overlap Removal
  int removeJetsOverlappingLeptons(ObjUtil::Jets& jets, ObjUtil::Leptons& leptons, float thresh=0.3);

  template <class V, class K> // 'V'ictim and 'K'iller
  int removeOverlap(std::vector<V>& victims, std::vector<K>& killers, float thresh=0.3)
  {

    /// return number of jets that are removed
    int nvictims_killed = 0;

    std::vector<V> survivors;
    for (auto& victim : victims)
    {
      bool pass = true;
      for (auto& killer : killers)
      {
        if (victim.p4.DeltaR(killer.p4) < thresh)
          pass = false;
      }
      if (pass)
        survivors.push_back(victim);
      else
        nvictims_killed++;
    }
    victims = std::vector<V>(survivors);

    return nvictims_killed;
  }

}
