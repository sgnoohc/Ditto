// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//  .
// ..: P. Chang, philip@physics.ucsd.edu

namespace CutUtil
{
  bool eventlistloaded  = false;
  bool verbosecheckeventlistloaded    = false;
  std::vector<std::vector<int> > eventlisttocheck;
  std::vector<std::vector<int> > eventlisttoverbosecheck;

  void loadEventListToCheck()
  {
    // https://stackoverflow.com/questions/9570991/how-to-read-space-and-newline-separated-integers-into-a-2d-array-in-c

    // Replace 'Plop' with your file name.
    std::ifstream file("eventlist.txt");

    if (!file.good())
      return;

    std::string line;
    // Read one line at a time intr the variable line:
    while(std::getline(file, line))
    {
      std::vector<int> lineData;
      std::stringstream lineStream(line);

      int value;
      // Read an integer at a time from the line
      while (lineStream >> value)
      {
        // Add the integers from a line to a 1D array (vector)
        lineData.push_back(value);
      }
      // When all the integers have been read, add the 1D array
      // into a 2D array (as one line in the 2D array)
      eventlisttocheck.push_back(lineData);
    }

    // set the eventlist loaded variable to true
    eventlistloaded = true;
  }

  void loadEventListToVerboseCheck()
  {
    // https://stackoverflow.com/questions/9570991/how-to-read-space-and-newline-separated-integers-into-a-2d-array-in-c

    // Replace 'Plop' with your file name.
    std::ifstream file("eventlistverbose.txt");

    if (!file.good())
      return;

    std::cout << "Loading eventlistverbose.txt" << std::endl;

    std::string line;
    // Read one line at a time intr the variable line:
    while(std::getline(file, line))
    {
      std::vector<int> lineData;
      std::stringstream lineStream(line);

      int value;
      // Read an integer at a time from the line
      while (lineStream >> value)
      {
        // Add the integers from a line to a 1D array (vector)
        std::cout << value << " ";
        lineData.push_back(value);
      }
      // When all the integers have been read, add the 1D array
      // into a 2D array (as one line in the 2D array)
      eventlisttoverbosecheck.push_back(lineData);
    }

    // set the eventlist loaded variable to true
    verbosecheckeventlistloaded = true;
  }

  void print(CutData& cutdata)
  {
    if (!verbosecheckeventlistloaded)
      return;
    std::vector<std::vector<int> >::iterator it;
    it = std::find(eventlisttoverbosecheck.begin(), eventlisttoverbosecheck.end(), cutdata.eventid);
    if (it != eventlisttoverbosecheck.end())
    {
      cutdata.print();
    }
    return;
  }

  bool failed(CutData& cutdata, TString message)
  {
    if (!eventlistloaded) return false;
    std::vector<std::vector<int> >::iterator it;
    it = std::find(eventlisttocheck.begin(), eventlisttocheck.end(), cutdata.eventid);
    if (it != eventlisttocheck.end())
    {
      std::cout << "cutfailed! ";
      std::cout << "event id = ";
      for (auto& id : cutdata.eventid)
        std::cout << id << " ";
      std::cout << "with val = ";
      std::cout << cutdata.val << " ";
      std::cout << "for cut = ";
      std::cout << cutdata.cutname << " ";
      if (!message.IsNull())
        std::cout << " failed for prefix = " << message.Data();
      std::cout << std::endl;
    }
    return false;
  }

  unsigned int passbit(Cuts& cuts, string prefix, ObjUtil::AnalysisData& a)
  {
    unsigned int bit = 0;
    unsigned int icut = 0;
    bool passed_so_far = true;
    HistUtil::fillCutflow(prefix, a, icut, "nocut");
    for (auto& cut : cuts)
    {
      CutData cutdata;
      cut(cutdata);
      bit |= (cutdata.pass << icut);
      passed_so_far = passed_so_far && cutdata.pass;
      icut++;
      if (passed_so_far)
        HistUtil::fillCutflow(prefix, a, icut, cutdata.cutname.c_str());
      if (!cutdata.pass)
        failed(cutdata, prefix);
      if (verbosecheckeventlistloaded)
        print(cutdata);

    }
    return bit;
  }

//	  bool pass(Cuts& cuts)
//	  {
//	    unsigned int passbit_result;
//	    return pass(cuts, passbit_result);
//	  }

  bool pass(Cuts& cuts, string prefix, ObjUtil::AnalysisData& a)
  {
    unsigned int passbit_result = passbit(cuts, prefix, a);
    bool isallhot = passbit_result && !(passbit_result & (passbit_result + 1));
    bool ispassN = (passbit_result + 1) & (1 << cuts.size());
    if (isallhot && ispassN)
      return true;
    else
      return false;
  }

  bool ifEventIdInVerboseCheckList(std::vector<int> eventid)
  {
    if (!verbosecheckeventlistloaded) return false;
    std::vector<std::vector<int> >::iterator it;
    it = std::find(eventlisttoverbosecheck.begin(), eventlisttoverbosecheck.end(), eventid);
    if (it != eventlisttoverbosecheck.end())
      return true;
    else
      return false;
  }

}
