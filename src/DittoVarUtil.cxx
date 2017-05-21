// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

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

  float MTNthLep(ObjUtil::AnalysisData& a, int lep_idx)
  {
    /// Compute MT with the Nth lepton provided by the lepton index argument
    if (a.leptons.size() <= (unsigned int) lep_idx) return -999;
    float mt = sqrt(2 * a.leptons[lep_idx].p4.Pt() * a.met.p4.Pt() * ( 1 - cos(a.met.p4.DeltaPhi(a.leptons[lep_idx].p4) ) ));
    return mt;
  }

  float DRjjWmass(ObjUtil::AnalysisData& a)
  {
    /// Compute the DR that has mass closest to the W mass
    return DRCloseToX(a.jets, 80.385);
  }

  float MjjWmass(ObjUtil::AnalysisData& a)
  {
    /// Compute the Mjj that is closest to the W mass
    return MjjCloseToX(a.jets, 80.385);
  }

  float LepSumPt(ObjUtil::AnalysisData& a)
  {
    float lepsumpt = 0;
    for (auto& lepton : a.leptons)
      lepsumpt += lepton.p4.Pt();
    return lepsumpt;
  }

  float HT(ObjUtil::AnalysisData& a)
  {
    float ht = 0;
    for (auto& jet : a.jets)
      ht += jet.p4.Pt();
    return ht;
  }

  float METHTRatio(ObjUtil::AnalysisData& a)
  {
    float ht = 0;
    for (auto& jet : a.jets)
      ht += jet.p4.Pt();
    return ht;
  }

  float DRjj(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.jets.size() < 2)
      return -999;
    return (a.jets[0].p4.DeltaR(a.jets[1].p4));
  }

  float Mjj(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.jets.size() < 2)
      return -999;
    return (a.jets[0].p4+a.jets[1].p4).M();
  }

  float MljClosest(ObjUtil::AnalysisData& a)
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

  float Ptjj(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.jets.size() < 2)
      return -999;
    return (a.jets[0].p4+a.jets[1].p4).Pt();
  }

  float Mbb(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.bjets.size() < 2)
      return -999;
    return (a.bjets[0].p4+a.bjets[1].p4).M();
  }

  float Ptbb(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.bjets.size() < 2)
      return -999;
    return (a.bjets[0].p4+a.bjets[1].p4).Pt();
  }

  float DEtajj(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.jets.size() < 2)
      return -999;
    return fabs(a.jets[0].p4.Eta()-a.jets[1].p4.Eta());
  }

  float DEtabb(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.bjets.size() < 2)
      return -999;
    return fabs(a.bjets[0].p4.Eta()-a.bjets[1].p4.Eta());
  }

  float Ptll(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.leptons.size() < 2)
      return -999;
    return (a.leptons[0].p4+a.leptons[1].p4).Pt();
  }

  float Mll(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.leptons.size() < 2)
      return -999;
    return (a.leptons[0].p4+a.leptons[1].p4).M();
  }

  float DPhill(ObjUtil::AnalysisData& a)
  {
    // If less than 2 jets just skip
    if (a.leptons.size() < 2)
      return -999;
    return fabs(a.leptons[0].p4.DeltaPhi(a.leptons[1].p4));
  }

  float DPhiLepMET(ObjUtil::AnalysisData& a)
  {
    // If less than 1 lepton just skip
    if (a.leptons.size() < 1)
      return -999;
    return fabs(a.leptons[0].p4.DeltaPhi(a.met.p4));
  }

  float MT(ObjUtil::AnalysisData& a)
  {
    if (a.leptons.size() == 0)
      return -999;
    return MTNthLep(a, 0);
  }

  float MTll(ObjUtil::AnalysisData& a)
  {
    if (a.leptons.size() < 2)
      return -999;
    TLorentzVector dilep = a.leptons[0].p4 + a.leptons[1].p4;
    return MT(dilep, a.met.p4);
  }

  float Mtt(ObjUtil::AnalysisData& a)
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

  float Mlvjj(ObjUtil::AnalysisData& a, int lepidx, int jetidx0, int jetidx1)
  {
    if (a.leptons.size() < (unsigned int) lepidx+1) return -999;
    if (a.jets.size() < (unsigned int) jetidx1+1) return -999;
    float metpz = NeutrinoSolver(a);
    TLorentzVector metp4;
    metp4.SetXYZM(a.met.p4.Px(), a.met.p4.Py(), metpz, 0);
    return (a.leptons[lepidx].p4 + metp4 + a.jets[jetidx0].p4 + a.jets[jetidx1].p4).M();
  }

  float NeutrinoSolver(ObjUtil::AnalysisData& adb, int lepidx)
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

  bool checkDilepPdgIdProduct(ObjUtil::AnalysisData& a, int check)
  {
    if (a.leptons.size() != 2) return false;
    if (a.leptons[0].pdgId * a.leptons[1].pdgId == check) return true;
    return false;
  }

  bool isOSEEChannel(ObjUtil::AnalysisData& a)
  {
    return checkDilepPdgIdProduct(a, -121);
  }

  bool isOSEMChannel(ObjUtil::AnalysisData& a)
  {
    return checkDilepPdgIdProduct(a, -143);
  }

  bool isOSMMChannel(ObjUtil::AnalysisData& a)
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

