// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

namespace VarUtil
{

  /// calculator with tlorentzvector
  float DEta(TLorentzVector, TLorentzVector);
  float DPhi(TLorentzVector, TLorentzVector);
  float DR  (TLorentzVector, TLorentzVector);
  float DPt (TLorentzVector, TLorentzVector);
  float Mass(TLorentzVector, TLorentzVector);
  float Pt  (TLorentzVector, TLorentzVector);
  float MT  (TLorentzVector, TLorentzVector);

  /// calculator with objects
  float DEta(ObjUtil::Particle, ObjUtil::Particle);
  float DPhi(ObjUtil::Particle, ObjUtil::Particle);
  float DR  (ObjUtil::Particle, ObjUtil::Particle);
  float DPt (ObjUtil::Particle, ObjUtil::Particle);
  float Mass(ObjUtil::Particle, ObjUtil::Particle);
  float Pt  (ObjUtil::Particle, ObjUtil::Particle);
  float MT  (ObjUtil::Particle, ObjUtil::Particle);

  /// calculator with tlorentzvector
  float DEta(TLorentzVector, ObjUtil::Particle);
  float DPhi(TLorentzVector, ObjUtil::Particle);
  float DR  (TLorentzVector, ObjUtil::Particle);
  float DPt (TLorentzVector, ObjUtil::Particle);
  float Mass(TLorentzVector, ObjUtil::Particle);
  float Pt  (TLorentzVector, ObjUtil::Particle);
  float MT  (TLorentzVector, ObjUtil::Particle);

  /// calculator with tlorentzvector
  float DEta(ObjUtil::Particle, TLorentzVector);
  float DPhi(ObjUtil::Particle, TLorentzVector);
  float DR  (ObjUtil::Particle, TLorentzVector);
  float DPt (ObjUtil::Particle, TLorentzVector);
  float Mass(ObjUtil::Particle, TLorentzVector);
  float Pt  (ObjUtil::Particle, TLorentzVector);
  float MT  (ObjUtil::Particle, TLorentzVector);

  /// Math stuff
  double Rndm();
  std::vector<std::vector<int> > comb(int N, int K);

  // templated function needs to sit inside header
  template<class I, class O>
    std::vector<O> twoBodyDecay(I parent)
    {

      //
      // Below code is adopted from : http://www1.gantep.edu.tr/~bingul/simulation/twoBody/twoBody.cpp.html
      //

      double m = parent.p4.M();

      /// Setting to massless daughters
      double m1 = 0; ///double m1 = prod1.m;
      double m2 = 0; ///double m2 = prod2.m;

      /// CM energies and momentum
      double e1 = (m*m + m1*m1 - m2*m2) / (2.0*m);
      double e2 = (m*m - m1*m1 + m2*m2) / (2.0*m);
      double P  = sqrt(e1*e1 - m1*m1);

      /// Isotropic random angles
      double theta = acos( 2.0*Rndm() - 1.0 );
      double phi   = 2.0*M_PI *Rndm();

      /// Compute p4 componenets
      double pX = P*sin(theta)*cos(phi);
      double pY = P*sin(theta)*sin(phi);
      double pZ = P*cos(theta);

      /// Now we have the isotropic decay of daughters
      O prod1;
      O prod2;
      prod1.p4.SetPxPyPzE( pX,  pY,  pZ, e1);
      prod2.p4.SetPxPyPzE(-pX, -pY, -pZ, e2);

      /// Parent boost vector
      TVector3 b = parent.p4.BoostVector();

      /// Boost the products
      prod1.p4.Boost(b);
      prod2.p4.Boost(b);

      /// Return the result
      std::vector<O> objs;
      objs.push_back(prod1);
      objs.push_back(prod2);
      return objs;

    }

}
