namespace PlotUtil
{

  bool plot1D(string name, float xval, double weight, Hist_DB &allhistos, string title, int numbinsx, float xmin, float xmax, string prefix)
  {

    /// Plot 1D histogram. If a histogram doesn't exist book first and fill.
    /// if the histogram exists, return true

    // If no title given, set title to name
    if (title == "") title = name;

    // If prefix exists add prefix
    if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

    // Find whether a histogram with the name already exists
    map<string, TH1*>::iterator iter= allhistos.find(name);

    // If the histogram is not found, make a new one
    if(iter == allhistos.end())
    {
      TH1D* currentHisto= new TH1D(name.c_str(), title.c_str(), numbinsx, xmin, xmax);
      currentHisto->GetXaxis()->SetTitle(title.c_str());
      currentHisto->Sumw2();
      currentHisto->SetDirectory(0);
      currentHisto->Fill(xval, weight);
      allhistos.insert(pair<string, TH1D*> (name,currentHisto) );
      return false;
    }
    // exists already, so just fill it
    else
    {
      (*iter).second->Fill(xval, weight);
      return true;
    }

  }

  bool plot1D(string name, float xval, double weight, std::map<string, TH1*> &allhistos, string title, int numbinsx, const float * xbins, string prefix)
  {

    /// Plot 1D histogram. If a histogram doesn't exist book first and fill. (with variable binning)

    // If no title given, set title to name
    if (title=="") title=name;

    // If prefix exists add prefix
    if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

    // Find whether a histogram with the name already exists
    std::map<string, TH1*>::iterator iter= allhistos.find(name);

    // If the histogram is not found, make a new one.
    if(iter == allhistos.end())
    {
      TH1D* currentHisto= new TH1D(name.c_str(), title.c_str(), numbinsx, xbins);
      currentHisto->GetXaxis()->SetTitle(title.c_str());
      currentHisto->Sumw2();
      currentHisto->SetDirectory(0);
      currentHisto->Fill(xval, weight);
      allhistos.insert(std::pair<string, TH1D*> (name,currentHisto) );
      return false;
    }
    else // exists already, so just fill it
    {
      (*iter).second->Fill(xval, weight);
      return true;
    }

  }

  void plot1D(string name, float xval, double weight, Hist_DB &allhistos, string prefix)
  {
    // If prefix exists add prefix
    if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

    /// Plot 1D histogram. If a histogram doesn't exist throw an error
    allhistos[name]->Fill(xval, weight);
    return;
  }

  bool plot2D(string name, float xval, float yval, double weight, Hist_DB &allhistos, string title, int numbinsx, float xmin, float xmax, int numbinsy, float ymin, float ymax, string prefix)
  {
    /// Plot 1D histogram. If a histogram doesn't exist book first and fill.
    /// if the histogram exists, return true
    // If no title given, set title to name
    if (title == "") title = name;

    // If prefix exists add prefix
    if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

    // Find whether a histogram with the name already exists
    map<string, TH1*>::iterator iter= allhistos.find(name);

    // If the histogram is not found, make a new one
    if(iter == allhistos.end())
    {
      TH2D* currentHisto= new TH2D(name.c_str(), title.c_str(), numbinsx, xmin, xmax, numbinsy, ymin, ymax);
      currentHisto->Sumw2();
      currentHisto->SetDirectory(0);
      currentHisto->Fill(xval, yval, weight);
      allhistos.insert(pair<string, TH1*> (name,currentHisto) );
      return false;
    }
    // exists already, so just fill it
    else
    {
      ((TH2D*) (*iter).second)->Fill(xval, yval, weight);
      return true;
    }
  }

  bool plot2D(string name, float xval, float yval, double weight, std::map<string, TH1*> &allhistos, string title, int numbinsx, const float * xbins, int numbinsy, const float* ybins, string prefix)
  {
    /// Plot 1D histogram. If a histogram doesn't exist book first and fill. (with variable binning)
    // If no title given, set title to name
    if (title=="") title=name;

    // If prefix exists add prefix
    if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

    // Find whether a histogram with the name already exists
    std::map<string, TH1*>::iterator iter= allhistos.find(name);

    // If the histogram is not found, make a new one.
    if(iter == allhistos.end())
    {
      TH2D* currentHisto= new TH2D(name.c_str(), title.c_str(), numbinsx, xbins, numbinsy, ybins);
      currentHisto->Sumw2();
      currentHisto->SetDirectory(0);
      currentHisto->Fill(xval, yval, weight);
      allhistos.insert(std::pair<string, TH1*> (name,currentHisto) );
      return false;
    }
    else // exists already, so just fill it
    {
      ((TH2D*) (*iter).second)->Fill(xval, yval, weight);
      return true;
    }
  }

  void plot2D(string name, float xval, float yval, double weight, Hist_DB &allhistos, string prefix)
  {
    // If prefix exists add prefix
    if (prefix != "") name  = TString::Format("%s_%s", prefix.c_str(), name.c_str()).Data();

    // Plot 1D histogram. If a histogram doesn't exist throw an error
    ((TH2D*) allhistos[name])->Fill(xval, yval, weight);
    return;
  }

  void savePlots(Hist_DB &h_1d, const char* outfilename)
  {

    /// Save histograms to a ROOT file

    // if size is 0 don't save
    if (h_1d.size() == 0)
    {
      printf("[Ditto::PlotUtil::savePlots] histogram size is 0 skip saving ...\n");
      return;
    }

    // Create a TFile
    TFile outfile(outfilename,"RECREATE") ;

    // Print the info that I am saving to the file
    printf("[Ditto::PlotUtil::savePlots] Saving histograms to %s\n", outfilename);

    // Loop over the histograms
    Hist_DB::iterator it1d;
    for (it1d = h_1d.begin(); it1d!=h_1d.end(); it1d++)
    {
      // save the histograms
      it1d->second->Write();
      delete it1d->second;
    }

    // Write to file and close
    outfile.Write();
    outfile.Close();

    return;
  }

  void savePlots2D(Hist_DB &h_1d, const char* outfilename)
  {

    /// Save TH2 histograms to a ROOT file

    // Create a TFile
    TFile outfile(outfilename,"RECREATE") ;

    // Print the info that I am saving to the file
    printf("[Ditto::PlotUtil::savePlots] Saving histograms to %s\n", outfilename);

    // Loop over the histograms
    Hist_DB::iterator it1d;
    for (it1d = h_1d.begin(); it1d!=h_1d.end(); it1d++)
    {
      // save the histograms
      it1d->second->Write();
      delete it1d->second;
    }

    // Write to file and close
    outfile.Write();
    outfile.Close();

    return;
  }

}
