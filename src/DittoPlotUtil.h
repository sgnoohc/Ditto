namespace PlotUtil
{
  // Map to hold 1D histograms with unique names
  typedef map<string, TH1*> Hist_DB;

  // Plot Utilities
  bool plot1D(
      string name, float xval, double weight, Hist_DB &allhistos,
      string title, int numbinsx, float xmin, float xmax, string prefix="");
  bool plot1D(
      string name, float xval, double weight, Hist_DB &allhistos,
      string title, int numbinsx, const float* xbins, string prefix="");
  void plot1D(
      string name, float xval, double weight, Hist_DB &allhistos, string prefix="");
  bool plot2D(
      string name, float xval, float yval, double weight, Hist_DB &allhistos,
      string title, int numbinsx, float xmin, float xmax, int numbinsy, float ymin, float ymax, string prefix="");
  bool plot2D(
      string name, float xval, float yval, double weight, Hist_DB &allhistos,
      string title, int numbinsx, const float* xbins, int numbinsy, const float* ybins, string prefix="");
  void plot2D(
      string name, float xval, float yval, double weight, Hist_DB &allhistos, string prefix="");
  void savePlots(Hist_DB&, const char*);
  void savePlots2D(Hist_DB &h_1d, const char* outfilename);
  TH1* get(string name, Hist_DB &allhistos, string prefix);
}
