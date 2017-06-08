namespace PrintUtil
{
  // Print Utilities
  void print   (TString msg="", int flush_before=0, int flush_after=0);
  void error   (TString msg, int is_error=1);
  void warning (TString msg);
  void announce(TString msg="", int quiet=0);
  void start   (int quiet=0, int sleep_time=0);
  void exit    (int quiet=0);
}
