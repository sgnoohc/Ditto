namespace CombUtil
{

  enum PAIRCRITERION {
    MIN = 0,
    MAX = 1,
    CLOSETOX = 2,
    AWAYFROMX = 3
  };

  bool MinDRPair(ObjUtil::Jets& jets, ObjUtil::Jet& jet0, ObjUtil::Jet& jet1);

  template <class I, class O>
  bool GetPair(std::vector<I>& cand0s, std::vector<O>& cand1s, I& p0, O& p1, std::function<float(ObjUtil::Particle, ObjUtil::Particle)> comparator, PAIRCRITERION mode, float critical_x = -999)
  {
    float val = -999;
    switch (mode)
    {
      case MIN:       val =  999           ; break;
      case MAX:       val = -999           ; break;
      case CLOSETOX:  val =  999*critical_x; break;
      case AWAYFROMX: val =      critical_x; break;
      default:
                      PrintUtil::error(TString::Format("CombUtil::GetPair() Not a recognized PAIRCRITERION value = %d", mode)); break;
    }
    bool pairfound = false;
    for (auto& cand0: cand0s)
    {
      for (auto& cand1: cand1s)
      {
        if (&cand0 != &cand1)
        {
          float tmpval = comparator(cand0, cand1);
          switch (mode)
          {
            case MIN:
              if (val > tmpval)
              {
                val = tmpval;
                p0 = cand0;
                p1 = cand1;
                pairfound = true;
              }
              break;
            case MAX:
              if (val < tmpval)
              {
                val = tmpval;
                p0 = cand0;
                p1 = cand1;
                pairfound = true;
              }
              break;
            case CLOSETOX:
              if (fabs(val - critical_x) > fabs(tmpval - critical_x))
              {
                val = tmpval;
                p0 = cand0;
                p1 = cand1;
                pairfound = true;
              }
              break;
            case AWAYFROMX:
              if (fabs(val - critical_x) < fabs(tmpval - critical_x))
              {
                val = tmpval;
                p0 = cand0;
                p1 = cand1;
                pairfound = true;
              }
              break;
            default:
              PrintUtil::error(TString::Format("CombUtil::GetPair() Not a recognized PAIRCRITERION value = %d", mode));
              break;
          }
        }
      }
    }
    return pairfound;
  }

}
