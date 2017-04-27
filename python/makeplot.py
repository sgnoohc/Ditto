#!/bin/env python

#  .
# ..: Philip Chang

# python script in creating plots

########################################################################
#
#
# Options
#
#
########################################################################

import os
import argparse

parser = argparse.ArgumentParser(description='Create plots from rootfiles with TH1 objects', formatter_class=argparse.ArgumentDefaultsHelpFormatter)

# Draw options
parser.add_argument('--plottype', dest='plottype', default='plot1d', required=True)
parser.add_argument('--drawratio', dest='drawratio', default=False, action='store_true')
parser.add_argument('--datadrawstyle', dest='datadrawstyle', default='ex0p')
parser.add_argument('--maximum_scale', dest='maximum_scale', type=float, default=1.2)

# Global options
parser.add_argument('--delimiter', dest='delimter', default='___', help=argparse.SUPPRESS)
parser.add_argument('--delimiter_histdef', dest='delimter_histdef', default=':::', help=argparse.SUPPRESS)
parser.add_argument('--delimiter_histdef_fileindex', dest='delimter_histdef_fileindex', default=0, help=argparse.SUPPRESS)
parser.add_argument('--delimiter_histdef_histindex', dest='delimter_histdef_histindex', default=1, help=argparse.SUPPRESS)
parser.add_argument('--delimiter_histdef_styleindex', dest='delimter_histdef_styleindex', default=2, help=argparse.SUPPRESS)

# gStyle
parser.add_argument('--gStyleSetOptStat', dest='gStyleSetOptStat', default=0, help=argparse.SUPPRESS)
parser.add_argument('--gStyleSetErrorX', dest='gStyleSetErrorX', default=0, help=argparse.SUPPRESS)
parser.add_argument('--draw_cms_logo', dest='draw_cms_logo', default=True, action='store_true', help=argparse.SUPPRESS)

# Options for input histograms
parser.add_argument('--sighist', dest='signal_histogram_fullpaths', action='append', help='fullpaths to the TH1 (e.g. hist.root:tfolder1/tfolder2/myhist)')
parser.add_argument('--bkghist', dest='background_histogram_fullpaths', action='append', help='fullpaths to the TH1 (e.g. hist.root:tfolder1/tfolder2/myhist)')
parser.add_argument('--datahist', dest='data_histogram_fullpaths', action='append', help='fullpaths to the TH1 (e.g. hist.root:tfolder1/tfolder2/myhist)')
parser.add_argument('--nbinx', dest='nbinx', type=int, help='N bins are used to check whether it\'s consistent. If 1080, rebin to make it so.')#, required=True)
parser.add_argument('--nbiny', dest='nbiny', type=int, help='N bins are used to check whether it\'s consistent. If 1080, rebin to make it so.')
parser.add_argument('--maximum_logy', dest='maximum_logy', type=float, help='Range maximum for logy option')
parser.add_argument('--minimum_logy', dest='minimum_logy', type=float, help='Range minimum for logy option')
parser.add_argument('--maximum'     , dest='maximum'     , type=str,   help='Range maximum')
parser.add_argument('--minimum'     , dest='minimum'     , type=str,   help='Range minimum')
parser.add_argument('--show_overflow',dest='show_overflow',action='store_true',help='show overflow bin', default=False)
parser.add_argument('--do_cutflow_style',dest='do_cutflow_style',action='store_true',help='show overflow bin', default=False)
parser.add_argument('--print_cutflow',dest='print_cutflow',action='store_true',help='show overflow bin', default=False)
parser.add_argument('--no_legend'    ,dest='no_legend'    ,action='store_true',help='do not draw legend', default=False)
parser.add_argument('--ratio_maximum', dest='ratio_maximum', type=float, help='Range maximum', default=3.5)
parser.add_argument('--ratio_minimum', dest='ratio_minimum', type=float, help='Range minimum', default=-1.5)
parser.add_argument('--restrict_min', dest='restrict_min', type=float, help='Range minimum', default=-1)
parser.add_argument('--restrict_max', dest='restrict_max', type=float, help='Range maximum', default=-1)
#parser.add_argument('--restrict_min_ibin', dest='restrict_min_ibin', type=int, help='Range minimum', default=-1)
#parser.add_argument('--restrict_max_ibin', dest='restrict_max_ibin', type=int, help='Range maximum', default=-1)

# Options for canvas
parser.add_argument('--canvas_name_prefix', dest='canvas_name_prefix', action='store_const', const='mycanvas', default='mycanvas', help=argparse.SUPPRESS)
parser.add_argument('--canvas_size_x', dest='canvas_size_x', type=int, default=800, help='X canvas size')
parser.add_argument('--canvas_size_y', dest='canvas_size_y', type=int, default=600, help='Y canvas size')
parser.add_argument('--canvas_left_margin', dest='canvas_left_margin', type=float, default=0.15, help='canvas left margin')
parser.add_argument('--canvas_bottom_margin', dest='canvas_bottom_margin', type=float, default=0.2, help='canvas bottom margin')
parser.add_argument('--canvas_right_margin', dest='canvas_right_margin', type=float, default=0.25, help='canvas right margin')
parser.add_argument('--canvas_top_margin', dest='canvas_top_margin', type=float, default=0.10, help='canvas top margin')
parser.add_argument('--canvas_def', dest='canvas_def', default='1,1:0-0-1-1-0.1-0.30-0.2-0.15', help='canvas def split:xl-yl-xh-yh-t-r-b-l')
parser.add_argument('--canvas_logy', dest='canvas_logy', help='SetLogy', action="store_true", default=False)
parser.add_argument('--canvas_logx', dest='canvas_logx', help='SetLogx', action="store_true", default=False)
parser.add_argument('--delimiter_canvas_def', dest='delimiter_canvas_def', default=':', help=argparse.SUPPRESS)
parser.add_argument('--delimiter_canvas_def_splitindex', dest='delimiter_canvas_def_splitindex', default=0, help=argparse.SUPPRESS)

# Options for saving TCanvases for root2html.py
parser.add_argument('--output_filename', dest='output_filename', help='output root file name where we will hold TCanvases for root2html.py', default='')
parser.add_argument('--output_path', dest='output_path', help='output path name for the given TCanvas', default='')
parser.add_argument('--output_tcanvas_name', dest='output_tcanvas_name', help='output path name for the given TCanvas', default='')
parser.add_argument('--output_file_open_option', dest='output_file_open_option', help='open to update? or open to recreate? etc.', default='update')

# Options for saving plot
parser.add_argument('--plotfiletype', dest='plotfiletypes', action='append', help='plot types (e.g. pdf, eps, png, etc.)', default=['pdf'])
parser.add_argument('--plotname', dest='plotname', help='plot name', default='myplot')
parser.add_argument('--plotlabel', dest='plotlabel', help='plot label on top')
parser.add_argument('--plotlabelXcoord', dest='plotlabelXcoord', default=.92, type=float, help='plot label X-coord on top')
parser.add_argument('--plotlabelYcoord', dest='plotlabelYcoord', default=.92, type=float, help='plot label Y-coord on top')
parser.add_argument('--labeltextsize', dest='labeltextsize', help='"CMS internal" text size', default=1.0, type=float)
parser.add_argument('--labelYcoord', dest='labelYcoord', help='"CMS" text y-coord', default=0.91, type=float)
parser.add_argument('--labelXcoord', dest='labelXcoord', help='"CMS" text x-coord', default=0.45, type=float)
parser.add_argument('--labelXcoordInternal', dest='labelXcoordInternal', help='"internal" text x-coord', default=0.555, type=float)
parser.add_argument('--labelXcoordLumi', dest='labelXcoordLumi', help='luminosity text x-coord', default=0.41, type=float)
parser.add_argument('--labelYcoordLumi', dest='labelYcoordLumi', help='luminosity text y-coord', default=0.835, type=float)

# Options for hist style
parser.add_argument('--delimiter_histstyles', dest='delimiter_histstyles', default=',', help=argparse.SUPPRESS)
parser.add_argument('--delimiter_histstyleitem', dest='delimiter_histstyleitem', default='=>', help=argparse.SUPPRESS)
parser.add_argument('--delimiter_histstyleitem_fieldindex', dest='delimiter_histstyleitem_fieldindex', default=0, help=argparse.SUPPRESS)
parser.add_argument('--delimiter_histstyleitem_valueindex', dest='delimiter_histstyleitem_valueindex', default=1, help=argparse.SUPPRESS)

# Options for axis and style
parser.add_argument('--XTitle', dest='XTitle', help='X-axis title (i.e. varname)', default='')
parser.add_argument('--YTitle', dest='YTitle', help='Y-axis title (i.e. varname)', default='')
parser.add_argument('--XLabelSize', dest='XLabelSize', help='X-axis label size (i.e. numbers)', default=1.5, type=float)
parser.add_argument('--YLabelSize', dest='YLabelSize', help='Y-axis label size (i.e. numbers)', default=1.5, type=float)
parser.add_argument('--XTitleSize', dest='XTitleSize', help='X-axis title size (i.e. varname)', default=1.5, type=float)
parser.add_argument('--YTitleSize', dest='YTitleSize', help='Y-axis title size (i.e. varname)', default=1.5, type=float)
parser.add_argument('--XLabelOffset', dest='XLabelOffset', help='X-axis label offset (i.e. numbers)', default=1.5, type=float)
parser.add_argument('--YLabelOffset', dest='YLabelOffset', help='Y-axis label offset (i.e. numbers)', default=1.5, type=float)
parser.add_argument('--XTitleOffset', dest='XTitleOffset', help='X-axis title offset (i.e. varname)', default=1.4, type=float)
parser.add_argument('--YTitleOffset', dest='YTitleOffset', help='Y-axis title offset (i.e. varname)', default=1.4, type=float)
parser.add_argument('--XNdivisions', dest='XNdivisions', help='X-axis Ndivisions', type=int, default=505)
parser.add_argument('--YNdivisions', dest='YNdivisions', help='Y-axis Ndivisions', type=int, default=505)

# Options for auto scaling signal sample
parser.add_argument('--auto_scale_signal', dest='auto_scale_signal', action='store_true', help='stack Integrate() small first', default=False)

# Options for stacking
parser.add_argument('--autostack', dest='autostack', action='store_true', help='stack Integrate() small first', default=False)
parser.add_argument('--reverseautostack', dest='reverseautostack', action='store_true', help='stack Integrate() small first', default=False)

# Options for legend
parser.add_argument('--legend_line_color', dest='legend_line_color', default=0, help=argparse.SUPPRESS)
parser.add_argument('--legendXlow', dest='legendXlow', help='legend x-low value', default=0.71, type=float)
parser.add_argument('--legendXhigh', dest='legendXhigh', help='legend x-high value', default=0.95, type=float)
parser.add_argument('--legendYlow', dest='legendYlow', help='legend y-low value', default=0.2, type=float)
parser.add_argument('--legendYhigh', dest='legendYhigh', help='legend y-high value', default=0.9, type=float)
parser.add_argument('--legendNCols', dest='legendNCols', help='legend ncolumns', default=1, type=int)
parser.add_argument('--delimiter_legendentry', dest='delimiter_legendentry', default='%', help=argparse.SUPPRESS)
parser.add_argument('--delimiter_legendentry_nameindex', dest='delimiter_legendentry_nameindex', default=0, help=argparse.SUPPRESS)
parser.add_argument('--delimiter_legendentry_styleindex', dest='delimiter_legendentry_styleindex', default=1, help=argparse.SUPPRESS)
parser.add_argument('--delimiter_legendentry_skipindex', dest='delimiter_legendentry_skipindex', default=2, help=argparse.SUPPRESS)

# Options for verbose print out
parser.add_argument('--print_ratio_plot', dest='print_ratio_plot', default=False, action='store_true', help='Print ratio plot results')


args = parser.parse_args()

import ROOT
import sys
import math
import fnmatch

#
# gStyle
#
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(args.gStyleSetOptStat)
ROOT.gStyle.SetCanvasColor(-1);
ROOT.gStyle.SetPadColor(-1);
ROOT.gStyle.SetFrameFillColor(-1);
ROOT.gStyle.SetHistFillColor(-1);
ROOT.gStyle.SetTitleFillColor(-1);
ROOT.gStyle.SetFillColor(-1);
ROOT.gStyle.SetFillStyle(4000);
ROOT.gStyle.SetStatStyle(0);
ROOT.gStyle.SetTitleStyle(0);
ROOT.gStyle.SetCanvasBorderSize(0);
ROOT.gStyle.SetFrameBorderSize(0);
ROOT.gStyle.SetLegendBorderSize(0);
ROOT.gStyle.SetStatBorderSize(0);
ROOT.gStyle.SetTitleBorderSize(0);
#ROOT.gStyle.SetErrorX(args.gStyleSetErrorX)


########################################################################
# New TColors
########################################################################
mycolors = []
mycolors.append(ROOT.TColor(11005 , 103 / 255. , 0   / 255. , 31  / 255.))
mycolors.append(ROOT.TColor(11004 , 178 / 255. , 24  / 255. , 43  / 255.))
mycolors.append(ROOT.TColor(11003 , 214 / 255. , 96  / 255. , 77  / 255.))
mycolors.append(ROOT.TColor(11002 , 244 / 255. , 165 / 255. , 130 / 255.))
mycolors.append(ROOT.TColor(11001 , 253 / 255. , 219 / 255. , 199 / 255.))
mycolors.append(ROOT.TColor(11000 , 247 / 255. , 247 / 255. , 247 / 255.))
mycolors.append(ROOT.TColor(11011 , 209 / 255. , 229 / 255. , 240 / 255.))
mycolors.append(ROOT.TColor(11012 , 146 / 255. , 197 / 255. , 222 / 255.))
mycolors.append(ROOT.TColor(11013 , 67  / 255. , 147 / 255. , 195 / 255.))
mycolors.append(ROOT.TColor(11014 , 33  / 255. , 102 / 255. , 172 / 255.))
mycolors.append(ROOT.TColor(11015 , 5   / 255. , 48  / 255. , 97  / 255.))

mycolors.append(ROOT.TColor(3001 , 239 / 255. , 138 / 255. , 98  / 255.))
mycolors.append(ROOT.TColor(3000 , 247 / 255. , 247 / 255. , 247 / 255.))
mycolors.append(ROOT.TColor(3011 , 103 / 255. , 169 / 255. , 207 / 255.))

mycolors.append(ROOT.TColor(5001 , 251 / 255. , 180 / 255. , 174 / 255.))
mycolors.append(ROOT.TColor(5002 , 179 / 255. , 205 / 255. , 227 / 255.))
mycolors.append(ROOT.TColor(5003 , 204 / 255. , 235 / 255. , 197 / 255.))
mycolors.append(ROOT.TColor(5004 , 222 / 255. , 203 / 255. , 228 / 255.))
mycolors.append(ROOT.TColor(5005 , 254 / 255. , 217 / 255. , 166 / 255.))

mycolors.append(ROOT.TColor(7001 ,   0/255. ,   0/255. ,   0/255.))
mycolors.append(ROOT.TColor(7002 , 230/255. , 159/255. ,   0/255.))
mycolors.append(ROOT.TColor(7003 ,  86/255. , 180/255. , 233/255.))
mycolors.append(ROOT.TColor(7004 ,   0/255. , 158/255. , 115/255.))
mycolors.append(ROOT.TColor(7005 , 240/255. , 228/255. ,  66/255.))
mycolors.append(ROOT.TColor(7006 ,   0/255. , 114/255. , 178/255.))
mycolors.append(ROOT.TColor(7007 , 213/255. ,  94/255. ,   0/255.))
mycolors.append(ROOT.TColor(7008 , 204/255. , 121/255. , 167/255.))

mycolors.append(ROOT.TColor(9001 ,  60/255. , 186/255. ,  84/255.))
mycolors.append(ROOT.TColor(9002 , 244/255. , 194/255. ,  13/255.))
mycolors.append(ROOT.TColor(9003 , 219/255. ,  50/255. ,  54/255.))
mycolors.append(ROOT.TColor(9004 ,  72/255. , 133/255. , 237/255.))





########################################################################
#
#
# Base Classes
#
#
########################################################################
class CanvasFactory:
    def __init__(self, args):
        self.canvas_index = 0
        self.args = args
    def get_canvas(self):
        canvas = ROOT.TCanvas(self.get_canvas_name(), self.get_canvas_name(), self.args.canvas_size_x, self.args.canvas_size_y)
        self.increment_canvas_index()
        self.stylize_canvas(canvas)
        return canvas
    def get_canvas_name(self):
        if self.args.output_tcanvas_name:
            return self.args.output_tcanvas_name
        plotname = os.path.basename(self.args.plotname)
        return self.args.canvas_name_prefix + '___' + plotname + '___' + str(self.canvas_index)
    def increment_canvas_index(self):
        self.canvas_index = self.canvas_index + 1
    def stylize_canvas(self, canvas):
        splitx = int(self.args.canvas_def.split(self.args.delimiter_canvas_def)[0].split(',')[0]) # hard code
        splity = int(self.args.canvas_def.split(self.args.delimiter_canvas_def)[0].split(',')[1]) # hard code
        margins = self.args.canvas_def.split(self.args.delimiter_canvas_def)[1:]
        canvas.Divide(splitx, splity)
        for i in xrange(splitx*splity):
            pad = canvas.cd(i+1)
            pad.SetPad(float(margins[i].split('-')[0]),float(margins[i].split('-')[1]),float(margins[i].split('-')[2]),float(margins[i].split('-')[3]))
            pad.SetTopMargin(float(margins[i].split('-')[4]))
            pad.SetRightMargin(float(margins[i].split('-')[5]))
            pad.SetBottomMargin(float(margins[i].split('-')[6]))
            pad.SetLeftMargin(float(margins[i].split('-')[7]))
            pad.SetFillStyle(4000)
            if i == 0: # scale up only the first one
                ROOT.gPad.SetLogy(args.canvas_logy)
            ROOT.gPad.SetTicky(+0)
            ROOT.gPad.SetTickx(+0)
            ROOT.gPad.SetLogx(args.canvas_logx)

class CanvasSaver:
    def __init__(self, args):
        self.args = args
    def save_canvas(self, canvas):
        if self.args.output_filename:
            ofile = ROOT.TFile(self.args.output_filename, self.args.output_file_open_option)
            ofile.cd()
            self.cd_recursive_directory(self.args.output_path.strip('/'))
            canvas.Write()
        for plotfiletype in self.args.plotfiletypes:
            canvas.SaveAs(self.args.plotname + '.' + plotfiletype)
    def cd_recursive_directory(self, path):
        paths = path.split('/')
        if len(paths) == 1:
            if ROOT.gDirectory.cd(paths[0]):
                return ROOT.gDirectory
            else:
                ROOT.gDirectory.mkdir(paths[0])
                ROOT.gDirectory.cd(paths[0])
        else:
            parentpath = paths[0]
            if ROOT.gDirectory.cd(parentpath):
                self.cd_recursive_directory(os.path.join(*paths[1:]))
            else:
                ROOT.gDirectory.mkdir(parentpath)
                ROOT.gDirectory.cd(parentpath)
                self.cd_recursive_directory(os.path.join(*paths[1:]))

class HistogramManager:
    def __init__(self, args):
        self.args = args
        self.files = dict()
        self.open_all_files()
    def open_all_files(self):
        self.open_all_files_in_paths(self.args.signal_histogram_fullpaths)
        self.open_all_files_in_paths(self.args.background_histogram_fullpaths)
        self.open_all_files_in_paths(self.args.data_histogram_fullpaths)
    def open_all_files_in_paths(self, paths):
        if paths:
            for path in paths:
                self.open_file(self.parse_file_path(path))
    def parse_file_path(self, path):
        return path.split(self.args.delimter_histdef)[self.args.delimter_histdef_fileindex].strip()
    def parse_hist_path(self, tfile, path):
        tmppaths=path.split(self.args.delimter_histdef)[self.args.delimter_histdef_histindex].strip()
        paths=tmppaths.split(',')
        finalpaths=[]
        for path in paths:
            if path.find("*") != -1:
                keys = []
                for key in tfile.GetListOfKeys():
                    keys.append(str(key.GetName()))
                filtered = fnmatch.filter(keys, path)
                finalpaths += filtered
            elif path.find("{") !=-1 and path.find("}") !=-1:
                mask = int(path.split("{")[1].split("}")[0],2)
                pattern = path.split("{")[0]
                keys = []
                for key in tfile.GetListOfKeys():
                    name = str(key.GetName())
                    if name.find("__") == -1:
                        continue
                    bitword = int(str(key.GetName()).split("__")[-1])
                    if (bitword & mask) == mask and name.find(pattern) != -1:
                        keys.append(name)
                finalpaths += keys
            else:
                finalpaths.append(path)
        return finalpaths
    def parse_style(self, path):
        try:
            stylestr = path.split(self.args.delimter_histdef)[self.args.delimter_histdef_styleindex].strip()
            histstyles = stylestr.split(self.args.delimiter_histstyles)
            style = dict()
            for histstyle in histstyles:
                items = histstyle.split(self.args.delimiter_histstyleitem)
                style[items[self.args.delimiter_histstyleitem_fieldindex].strip()] = items[self.args.delimiter_histstyleitem_valueindex].strip()
            return style
        except:
            print "parsing histstyle failed!", path
            sys.exit(-1)
    def open_file(self, path):
        self.files[path] = ROOT.TFile.Open(path)
    def get_file(self, path):
        return self.files[path]
    def get_signal_histograms(self):
        if self.args.signal_histogram_fullpaths:
            return self.get_histograms(self.args.signal_histogram_fullpaths)
        else:
            return []
    def get_background_histograms(self):
        if self.args.background_histogram_fullpaths:
            return self.get_histograms(self.args.background_histogram_fullpaths)
        else:
            return []
    def get_data_histograms(self):
        if self.args.data_histogram_fullpaths:
            return self.get_histograms(self.args.data_histogram_fullpaths)
        else:
            return []
    def copy_histogram(self, orighist):
        #print self.args.restrict_min
        #print self.args.restrict_max
        if self.args.restrict_min > 0 or self.args.restrict_max > 0:
            rmin = self.args.restrict_min
            rmax = self.args.restrict_max

            iminbin = orighist.GetXaxis().FindFixBin(rmin)
            imaxbin = orighist.GetXaxis().FindFixBin(rmax)


            if iminbin == -1: iminbin = 1;
            if imaxbin == -1: imaxbin = orighist.GetNbinsX();
            xmin = orighist.GetXaxis().GetBinLowEdge(iminbin);
            xmax = orighist.GetXaxis().GetBinUpEdge(imaxbin);
            nbin = imaxbin-iminbin+1
            hist = ROOT.TH1F(orighist.GetName()+"clone", "", nbin, xmin, xmax);
            hist.Sumw2();
            for i in xrange(iminbin, imaxbin+1):
                hist.SetBinContent(i-iminbin+1,orighist.GetBinContent(i))
                hist.SetBinError  (i-iminbin+1,orighist.GetBinError(i))
            return hist
        #if self.args.restrict_min_ibin > 0 or self.args.restrict_max_ibin > 0:
        #    iminbin = self.args.restrict_min_ibin
        #    imaxbin = self.args.restrict_max_ibin
        #    if iminbin == -1: iminbin = 1;
        #    if imaxbin == -1: imaxbin = orighist.GetNbinsX();
        #    xmin = orighist.GetXaxis().GetBinLowEdge(iminbin);
        #    xmax = orighist.GetXaxis().GetBinUpEdge(imaxbin);
        #    nbin = imaxbin-iminbin+1
        #    hist = ROOT.TH1F(orighist.GetName()+"clone", "", nbin, xmin, xmax);
        #    hist.Sumw2();
        #    for i in xrange(iminbin, imaxbin+1):
        #        hist.SetBinContent(i,orighist.GetBinContent(i))
        #        hist.SetBinError  (i,orighist.GetBinError(i))
        #    return hist
        else:
            return orighist
    def get_histograms(self, histogram_fullpaths):
        histlist = []
        for hist in histogram_fullpaths:
            hist = self.get_histogram(hist)
            if hist:
                histlist.append(hist)
        return histlist
    def get_histogram(self, histogram_fullpath):
        print 'Retrieving Histograms', histogram_fullpath
        hist = None
        tfile = self.files[self.parse_file_path(histogram_fullpath)]
        histpaths = self.parse_hist_path(tfile, histogram_fullpath)
        #print histpaths
        for index, parsed_hist_path in enumerate(histpaths):
            tmphist = tfile.Get(parsed_hist_path)
            if index == 0:
                hist = self.copy_histogram(tmphist)
            else:
                hist.Add(self.copy_histogram(tmphist))
        if not hist:
            return None
        hist.SetTitle("")
        self.set_histaxis_settings(hist)
        self.set_histaxis_labels(hist)
        self.stylize_histogram(hist, histogram_fullpath)
        self.modify_nbinx(hist, histogram_fullpath)
        return hist
    def set_histaxis_settings(self, hist, scale=1.):
        if hist.GetXaxis() == None:
            return
        hist.GetXaxis().SetLabelSize  (0.035 * 1.20 * scale * self.args.XLabelSize)
        hist.GetYaxis().SetLabelSize  (0.035 * 1.20 * scale * self.args.YLabelSize)
        hist.GetXaxis().SetTitleSize  (0.035 * 1.20 * scale * self.args.XTitleSize)
        hist.GetYaxis().SetTitleSize  (0.035 * 1.20 * scale * self.args.YTitleSize)
        hist.GetXaxis().SetLabelOffset(0.015 * self.args.XLabelOffset)
        hist.GetYaxis().SetLabelOffset(0.015 * self.args.YLabelOffset)
        hist.GetXaxis().SetTitleOffset(1.000 * self.args.XTitleOffset)
        hist.GetYaxis().SetTitleOffset(1.000 * self.args.YTitleOffset / scale)
        hist.GetXaxis().SetNdivisions (self.args.XNdivisions)
        hist.GetYaxis().SetNdivisions (self.args.YNdivisions)
        #hist.GetYaxis().SetTickLength (-1*hist.GetYaxis().GetTickLength())
        #print hist.GetYaxis().GetTickLength()
        hist.GetYaxis().SetTickLength (-0.02)
        hist.GetXaxis().SetTickLength (-0.03)
    def set_histaxis_labels(self, hist):
        if hist.GetXaxis() == None:
            return
        hist.GetXaxis().SetTitle(self.args.XTitle)
        hist.GetYaxis().SetTitle(self.args.YTitle)
    def stylize_histogram(self, hist, histogram_fullpath):
        styles = self.parse_style(histogram_fullpath)
        #print 'size of histogram',histogram_fullpath,hist.Integral()
        for item in styles:
            if item == 'Scale':
                if styles[item].find('norm')!=-1:
                    norm = 1.
                    opt = styles[item].rsplit('norm')[1]
                    if opt.find('%') != -1:
                        filename = opt.split('%')[0]
                        histname = opt.split('%')[1]
                        scaleoption = opt.split('%')[2]
                        if scaleoption.find('bin') != -1:
                            exec "scale = float(" + opt.split('%')[3] + ")"
                            binindex = int(scaleoption.split('bin')[1])
                            histref = self.get_file(filename).Get(histname)
                            denomsum = histref.GetBinContent(binindex)
                            print denomsum, scale
                            norm = 1./denomsum * scale * hist.Integral()
                            print norm
                        else:
                            exec "scale = float(" + opt.split('%')[2] + ")"
                            histref = self.get_file(filename).Get(histname)
                            norm = histref.Integral() * scale
                    elif opt.find('bin') != -1:
                        binnumber = int(opt.rsplit('bin')[1])
                        bincontent = hist.GetBinContent(binnumber)
                        norm = 1. / bincontent * hist.Integral()
                    else:
                        norm = float(opt)
                    integral = ROOT.Double()
                    error = ROOT.Double()
                    integral = hist.IntegralAndError(0, hist.GetNbinsX()+1, error)
                    #print integral, error
                    #print 'size of histogram',histogram_fullpath,hist.Integral()
                    if hist.Integral() > 0:
                        hist.Scale(norm/hist.Integral())
                else:
                    exec "hist.Scale("+styles[item]+")"
            elif item == 'Multiply':
                tf1def = styles[item].split('//')[0]
                tf1min = float(styles[item].split('//')[1])
                tf1max = float(styles[item].split('//')[2])
                tf1 = ROOT.TF1("temp", tf1def, tf1min, tf1max)
                hist.Multiply(tf1)
            elif item.find('Size') != -1:
                getattr(hist, item)(float(styles[item]))
            else:
                try:
                    getattr(hist, item)(styles[item])
                except:
                    getattr(hist, item)(int(styles[item]))
        if self.args.show_overflow:
            self.add_overflow(hist)
    def add_overflow(self, hist):
        ofbinc = hist.GetBinContent(hist.GetNbinsX()+1)
        ofbine = hist.GetBinError(hist.GetNbinsX()+1)
        lastbinc = hist.GetBinContent(hist.GetNbinsX())
        lastbine = hist.GetBinError(hist.GetNbinsX())
        hist.SetBinContent(hist.GetNbinsX(), ofbinc + lastbinc)
        hist.SetBinError(hist.GetNbinsX(), ROOT.TMath.Sqrt(ofbine*ofbine + lastbine*lastbine))
    def modify_nbinx(self, hist, histogram_fullpath):
        #if hist.GetNbinsX() != self.args.nbinx and hist.GetNbinsX() != 1080:
#               if hist.GetNbinsX() != self.args.nbinx:
#                   print 'Histogram', histogram_fullpath, 'has wrong number of bins! nbin=', hist.GetNbinsX(), '. You asked', self.args.nbinx
#                   sys.exit(-1)
        #elif hist.GetNbinsX() == 1080:
        #    hist.Rebin(1080 / self.args.nbinx)
#               else:
#                   hist.Rebin(hist.GetNbinsX() / self.args.nbinx)
        #print hist.GetNbinsX()
        #print self.args.nbinx
        if self.args.nbinx:
            hist.Rebin(hist.GetNbinsX() / self.args.nbinx)
            #pass
    def get_background_stacked_histograms(self):
        return self.get_stacked_histograms(self.get_background_histograms())
    def get_stacked_histograms(self, hists):
        stackedhist = ROOT.THStack('temp', '')
        if self.args.autostack:
            hists = sorted(hists, key=lambda hist: hist.Integral())
        if self.args.reverseautostack:
            hists = sorted(hists, key=lambda hist: hist.Integral(),reverse=True)
        stackedhist.Draw('hist') # must draw before accessing TAxis
        for hist in hists:
            stackedhist.Add(hist)
        self.set_histaxis_settings(stackedhist)
        self.set_histaxis_labels(stackedhist)
        return stackedhist, hists
    def get_summed_histograms(self, hists):
        if len(hists) == 0:
            print 'Asked for summed hists but no hist exists!'
            #sys.exit(-1)
            return None
        summedhist = hists[0].Clone()
        summedhist.Reset()
        for hist in hists:
            summedhist.Add(hist)
        self.set_histaxis_settings(summedhist)
        return summedhist

class LegendFactory:
    def __init__(self, args):
        self.args = args
    def get_legend(self, hists):
        #print self.args.legendXlow
        #print self.args.legendXhigh
        #print self.args.legendYlow
        #print self.args.legendYhigh
        legend = ROOT.TLegend(self.args.legendXlow, self.args.legendYlow, self.args.legendXhigh, self.args.legendYhigh)
        legend.SetNColumns(self.args.legendNCols)
        newhistarray = []
        for hist in hists:
            newhistarray.append(hist)
        newhistarray.reverse()
        for hist in newhistarray:
            name, style, skip = self.parse_legend_entry(hist)
            if skip:
                continue
            legend.AddEntry(hist, name, style)
        legend.SetLineColor(0)
        legend.SetFillStyle(0)
        return legend
    def parse_legend_entry(self, hist):
        legend_entry_str = hist.GetName()
        name = legend_entry_str.split(self.args.delimiter_legendentry)[self.args.delimiter_legendentry_nameindex].strip()
        style = legend_entry_str.split(self.args.delimiter_legendentry)[self.args.delimiter_legendentry_styleindex].strip()
        skip = False
        try:
            legend_entry_str.split(self.args.delimiter_legendentry)[self.args.delimiter_legendentry_skipindex].strip()
            skip = True
        except:
            pass
        return name, style, skip

########################################################################
#
#
# My Picasso
#
#
########################################################################
class HistogramPainter:

    def __init__(self, args):
        self.args = args
        self.canvasfactory = CanvasFactory(args)
        self.histmanager = HistogramManager(args)
        self.legendfactory = LegendFactory(args)
        self.canvassaver = CanvasSaver(args)
        self.objs = []

    # obtain max of the plots to plot
    def get_max(self, *hists):
        themax = 0
        for i in xrange(len(hists)):
            try:
                if themax < hists[i].GetMaximum() + hists[i].GetBinError(hists[i].GetMaximumBin()):
                    themax = hists[i].GetMaximum() + hists[i].GetBinError(hists[i].GetMaximumBin())
            except:
                pass
        return themax

    # Draw standard 1d plot
    def draw_standard_1d(self):
        canvas = self.canvasfactory.get_canvas()
        self.draw_standard_1d_on_current_pad()
        self.canvassaver.save_canvas(canvas)

    # Draw standard 1d plot
    def draw_standard_1d_with_ratio(self):
        canvas = self.canvasfactory.get_canvas()
        canvas.cd(1)
        self.draw_standard_1d_on_current_pad()
        canvas.cd(2).SetGridy()
        self.draw_ratio_1d_data__bkg()
        self.canvassaver.save_canvas(canvas)

    # Draw standard 1d plot + significance scan
    def draw_standard_1d_with_sigscan(self):
        splitx = int(self.args.canvas_def.split(self.args.delimiter_canvas_def)[0].split(',')[0]) # hard code
        splity = int(self.args.canvas_def.split(self.args.delimiter_canvas_def)[0].split(',')[1]) # hard code
        if splity != 2:
            #print 'override canvas def'
            self.args.canvas_def = '1,2:0-0.3-1-1-0.1-0.30-0.02-0.20:0-0-1-0.3-0.05-0.30-0.2-0.20'
        if float(self.args.canvas_size_x) / float(self.args.canvas_size_y) > 1:
            print 'override canvas ratio since canvas x-size is longer than y-size'
            self.args.canvas_size_x = 800
            self.args.canvas_size_y = 700
        canvas = self.canvasfactory.get_canvas()
        canvas.cd(1)
        self.draw_standard_1d_on_current_pad()
        canvas.cd(2).SetGridy()
        self.draw_sig_scan()
        self.canvassaver.save_canvas(canvas)

    # Draw standard 1d plot + significance scan
    def draw_standard_1d_with_individ_sigscan(self):
        splitx = int(self.args.canvas_def.split(self.args.delimiter_canvas_def)[0].split(',')[0]) # hard code
        splity = int(self.args.canvas_def.split(self.args.delimiter_canvas_def)[0].split(',')[1]) # hard code
        if splity != 2:
            #print 'override canvas def'
            self.args.canvas_def = '1,2:0-0.3-1-1-0.1-0.30-0.02-0.20:0-0-1-0.3-0.05-0.30-0.2-0.20'
        if float(self.args.canvas_size_x) / float(self.args.canvas_size_y) > 1:
            print 'override canvas ratio since canvas x-size is longer than y-size'
            self.args.canvas_size_x = 800
            self.args.canvas_size_y = 700
        canvas = self.canvasfactory.get_canvas()
        canvas.cd(1)
        self.draw_standard_1d_on_current_pad()
        canvas.cd(2).SetGridy()
        self.draw_individ_sig_scan()
        self.canvassaver.save_canvas(canvas)

    # Draw standard 1d plot on current pad (bkg-stacked, signal, data)
    def draw_standard_1d_on_current_pad(self):

        stacked = None
        bkghists = None
        totalbkghist = None
        datahists = None
        datahist = None
        sighists = None

        # If cutflow
        if self.args.do_cutflow_style:
            bkghists = self.histmanager.get_background_histograms()
            totalbkghist = self.histmanager.get_summed_histograms(bkghists)
            sighists = self.histmanager.get_signal_histograms()
            datahists = self.histmanager.get_data_histograms()
            datahist = None
            if len(datahists) != 0:
                datahist = self.histmanager.get_summed_histograms(datahists)

            scales = []
            scales_error = []
            for i in xrange(1, totalbkghist.GetNbinsX()+1):
                scales.append(totalbkghist.GetBinContent(i) / 100.)
                scales_error.append(totalbkghist.GetBinError(i))
            #print 'here', scales
            for sighist in sighists:
                for i in xrange(1, sighist.GetNbinsX()+1):
                    if scales[i-1] == 0: continue
                    binc = sighist.GetBinContent(i)
                    if binc == 0: continue
                    bine = sighist.GetBinError(i)
                    binfe = bine / binc
                    newbinc = binc / scales[i-1]
                    newbine = binfe / scales[i-1] * newbinc
                    sighist.SetBinContent(i, newbinc)
                    sighist.SetBinError(i, newbine)
            for bkghist in bkghists:
                for i in xrange(1, bkghist.GetNbinsX()+1):
                    if scales[i-1] == 0: continue
                    binc = bkghist.GetBinContent(i)
                    if binc == 0: continue
                    bine = bkghist.GetBinError(i)
                    binfe = bine / binc
                    newbinc = binc / scales[i-1]
                    newbine = binfe / scales[i-1] * newbinc
                    bkghist.SetBinContent(i, newbinc)
                    bkghist.SetBinError(i, newbine)
            if datahist:
                for i in xrange(1, datahist.GetNbinsX()+1):
                    if scales[i-1] == 0: continue
                    binc = datahist.GetBinContent(i)
                    if binc == 0: continue
                    bine = datahist.GetBinError(i)
                    binfe = bine / binc
                    newbinc = binc / scales[i-1]
                    newbine = binfe / scales[i-1] * newbinc
                    datahist.SetBinContent(i, newbinc)
                    datahist.SetBinError(i, newbine)

            self.objs.append(bkghists)
            totalbkghist = self.histmanager.get_summed_histograms(bkghists)
            self.objs.append(totalbkghist)
            self.objs.append(sighists)
            self.objs.append(datahists)
            stacked, dummy = self.histmanager.get_stacked_histograms(bkghists)
            self.objs.append(stacked)
            print stacked.GetXaxis().GetNbins()+1
            for i in xrange(1, stacked.GetXaxis().GetNbins()+1):
                print i
                stacked.GetXaxis().SetBinLabel(i, '%.1f #pm %.1f'%(scales[i-1] * 100., scales_error[i-1]))


        else:

            stacked, bkghists = self.histmanager.get_background_stacked_histograms()
            self.objs.append(stacked)
            self.objs.append(bkghists)
            sighists = self.histmanager.get_signal_histograms()
            self.objs.append(sighists)
            datahists = self.histmanager.get_data_histograms()
            self.objs.append(datahists)
            datahist = None
            totalbkghist = None
            if len(datahists) != 0:
                datahist = self.histmanager.get_summed_histograms(datahists)
            if len(bkghists) != 0:
                totalbkghist = self.histmanager.get_summed_histograms(bkghists)
            self.objs.append(totalbkghist)

        if self.args.print_cutflow:

            yields_table = []
            errors_table = []

            for sighist in sighists:
                yields = []
                errors = []
                yields.append(sighist.GetName())
                errors.append(sighist.GetName())
                for i in xrange(1, sighist.GetNbinsX()+1):
                    binc = sighist.GetBinContent(i)
                    bine = sighist.GetBinError(i)
                    yields.append(binc)
                    errors.append(bine)
                yields_table.append(yields)
                errors_table.append(errors)
            if totalbkghist:
                yields = []
                errors = []
                yields.append("Total Background")
                errors.append("Total Background")
                for i in xrange(1, totalbkghist.GetNbinsX()+1):
                    binc = totalbkghist.GetBinContent(i)
                    bine = totalbkghist.GetBinError(i)
                    yields.append(binc)
                    errors.append(bine)
                yields_table.append(yields)
                errors_table.append(errors)
            for bkghist in bkghists:
                yields = []
                errors = []
                yields.append(bkghist.GetName())
                errors.append(bkghist.GetName())
                for i in xrange(1, bkghist.GetNbinsX()+1):
                    binc = bkghist.GetBinContent(i)
                    bine = bkghist.GetBinError(i)
                    yields.append(binc)
                    errors.append(bine)
                yields_table.append(yields)
                errors_table.append(errors)
            if datahist:
                yields = []
                errors = []
                yields.append("Data")
                errors.append("Data")
                for i in xrange(1, datahist.GetNbinsX()+1):
                    binc = datahist.GetBinContent(i)
                    bine = datahist.GetBinError(i)
                    yields.append(binc)
                    errors.append(bine)
                yields_table.append(yields)
                errors_table.append(errors)

            # transpose
            yields_table_transpose = map(list, zip(*yields_table))
            errors_table_transpose = map(list, zip(*errors_table))

            import codecs

            # output file
            cutflow_file = codecs.open(self.args.plotname + '.csv', 'w', 'utf-8')

            index = 0
            for yields, errors in zip(yields_table_transpose, errors_table_transpose):
                row_string = ""
                for y, e in zip(yields, errors):
                    if index == 0:
                        row_string += '%30s,,,'%y
                    else:
                        #row_string += '%10.1f,'%y + u"\u00B1" + ', %10.1f, '%e
                        row_string += '%10.1f,'%y + "+-" + ', %10.1f, '%e
                row_string += '\n'
                cutflow_file.write(row_string)
                index += 1

        try:
            stacked.SetMaximum(self.get_max(totalbkghist, datahist) * self.args.maximum_scale) # assuming bkg matches data
        except:
            stacked.SetMaximum(self.get_max(totalbkghist) * self.args.maximum_scale)
        if self.args.minimum_logy:
            stacked.SetMinimum(self.args.minimum_logy)
        elif self.args.minimum:
            stacked.SetMinimum(eval(self.args.minimum))
            if datahist:
                datahist.SetMinimum(eval(self.args.minimum))
        if self.args.maximum_logy:
            stacked.SetMaximum(self.args.maximum_logy)
        elif self.args.maximum:
            stacked.SetMaximum(eval(self.args.maximum))

        # print amounts
        for sighist in sighists:
            print sighist
            sighist.Print("all")
        for bkghist in bkghists:
            print bkghist
            bkghist.Print("all")
        if datahist:
            print datahist
            datahist.Print("all")
        self.objs.append(datahist)
        if self.args.do_cutflow_style:
            ROOT.gStyle.SetPaintTextFormat("3.1f")
            stacked.Draw('histtext0')
        else:
            stacked.Draw('hist')
        if totalbkghist:
            totalbkghist.SetLineColor(1)
            totalbkghist.SetLineWidth(1)
            totalbkghist.SetFillColor(0)
            totalbkghist.DrawCopy('histsame')
            totalbkghist.SetFillStyle(3245)
            totalbkghist.SetFillColor(12)
            totalbkghist.Draw('E2 same')
        print 'totalbkghist'
        totalbkghist.Print('all')
        #print totalbkghist.Integral(2,3)
        #print totalbkghist.Integral(19,25)
        #print totalbkghist.Integral(19,26)
        #print totalbkghist.Integral(22,24)
        #print totalbkghist.Integral(41,50)
        #print totalbkghist.Integral(82,100)
        if self.args.auto_scale_signal:
            maxvalue = totalbkghist.GetBinContent(totalbkghist.GetMaximumBin())
            for sighist in sighists:
                sigmaxvalue = sighist.GetBinContent(sighist.GetMaximumBin())
                scaletomax = 1
                scaletosize = 1
                if sigmaxvalue != 0: scaletomax = maxvalue / sigmaxvalue
                if sighist.Integral() != 0: scaletosize = totalbkghist.Integral() / sighist.Integral()
                if scaletomax < scaletosize:
                    sighist.Scale(scaletomax)
                else:
                    sighist.Scale(scaletosize)
        if datahist:
            if totalbkghist:
                datahist.Draw(self.args.datadrawstyle+'same')
            else:
                datahist.Draw(self.args.datadrawstyle)
        for sighist in sighists:
            sighist.Draw('histsame')
            print 'sighist'
            sighist.Print('all')
            #print sighist.Integral(19,20)
            #print sighist.Integral(19,25)
            #print sighist.Integral(19,26)
            #print sighist.Integral(22,24)
            #print sighist.Integral(41,50)
            #print sighist.Integral(82,100)
        if not self.args.no_legend:
            legend = None
            if datahist:
                legend = self.legendfactory.get_legend(sighists + bkghists + [datahist])
                legend.Draw('same')
            else:
                legend = self.legendfactory.get_legend(sighists + bkghists)
                legend.Draw('same')
            self.objs.append(legend)
        latex = ROOT.TLatex()
        if self.args.plotlabel:
            latex.SetTextFont(42)
            latex.SetTextSize(0.050*self.args.labeltextsize)
            latex.SetTextAlign(10)
            latex.DrawLatexNDC(self.args.plotlabelXcoord,self.args.plotlabelYcoord,self.args.plotlabel)
        if self.args.draw_cms_logo:


            #latex.SetTextFont(62)
            #latex.SetTextSize(0.062*self.args.labeltextsize)
            #latex.SetTextAlign(11)
            #latex.DrawLatexNDC(self.args.labelXcoord,self.args.labelYcoord,'CMS')
            #latex.SetTextFont(52)
            #latex.SetTextSize(0.062*self.args.labeltextsize)
            #latex.SetTextAlign(11)
            #latex.DrawLatexNDC(self.args.labelXcoordInternal,self.args.labelYcoord,'internal')
            #latex.SetTextFont(42)
            #latex.SetTextSize(0.062*self.args.labeltextsize)
            #latex.SetTextAlign(11)
            #latex.DrawLatexNDC(self.args.labelXcoordLumi,self.args.labelYcoordLumi,'36 fb^{-1} (13 TeV)')

            # no "CMS blah" at all
            latex.SetTextFont(42)
            latex.SetTextSize(0.062*self.args.labeltextsize)
            latex.SetTextAlign(11)
            latex.DrawLatexNDC(self.args.labelXcoord-0.035,self.args.labelYcoord+0.01,'36 fb^{-1} (13 TeV)')





            ##tf2 = ROOT.TF1('fit', 'TMath::Voigt(TMath::Abs(x-[0]),[1],[2])*[3]+pol1(4)', 80., 100.)
            #tf2 = ROOT.TF1('fit', 'TMath::Voigt(TMath::Abs(x-[0]),[1],[2])*[3]', 85., 95.)
            #print datahist.GetMaximum()
            #fac = datahist.GetMaximum() / 1600.
            #tf2.SetParameter(0, 9.1e+01)
            #tf2.SetParameter(1, 9.1e-04)
            #tf2.SetParameter(2, 3.2e+00)
            #tf2.SetParameter(3, fac*7.8e+03)
            #tf2.SetParameter(4, 1.0e-01)
            #tf2.SetParameter(5, 1.0e-01)
            ##tf2.SetParameter(6, 0.0e-01)
            #tf2.SetLineColor(4)
            #datahist.Fit(tf2,"","lsame",80., 100.)
            #self.objs.append(tf2)
            #tf3 = ROOT.TF1('bkg', 'pol1(0)', 80., 100.)
            #tf3.SetParameter(0, tf2.GetParameter(4))
            #tf3.SetParameter(1, tf2.GetParameter(5))
            ##tf3.SetParameter(2, tf2.GetParameter(6))
            #tf3.SetLineColor(2)
            #tf3.Draw("lsame")
            #self.objs.append(tf3)

        # Following is the fit for the trigger purity study in march of 2017
        ##### polynomial fit============================
        #####tf2 = ROOT.TF1('fit', 'gaus(0)+gaus(3)+pol1(6)', 91.1876-15., 91.1876+15.)
        ####tf2 = ROOT.TF1('fit', 'gaus(0)+gaus(3)+pol1(6)', 60, 120)
        ####fac = datahist.GetMaximum() / 1701. * 2.0
        ####tf2.SetParameter(0, fac*1.5e+04)
        ####tf2.SetParameter(1, 9.1e+01)
        ####tf2.SetParameter(2, 5.2e+00)
        ####tf2.SetParameter(3, fac*7.8e+00)
        ####tf2.SetParameter(4, 9.1e+01)
        ####tf2.SetParameter(5, 5.2e+00)
        ####tf2.SetParameter(6, 1.0e-04)
        ####tf2.SetParameter(7, 1.0e-04)
        #####tf2.SetParameter(8, 1.0e-01)
        ####tf2.SetLineColor(4)
        ####datahist.Fit(tf2, "", "lsame", 60,120)
        #####datahist.Fit(tf2, "", "lsame", 91.1876-15., 91.1876+15.)
        ####tf3 = ROOT.TF1('bkg', 'pol1(0)', 91.1876-15., 91.1876+15.)
        ####tf3.SetParameter(0, tf2.GetParameter(6))
        ####tf3.SetParameter(1, tf2.GetParameter(7))
        #####tf3.SetParameter(2, tf2.GetParameter(8))
        ####tf3.SetLineColor(2)
        ####tf3.Draw("lsame")
        ####self.objs.append(tf2)
        ####self.objs.append(tf3)
        ##### polynomial fit============================

        self.objs.append(latex)

    # draw data over background
    def draw_ratio_1d_data__bkg(self):
        stacked, bkghists = self.histmanager.get_background_stacked_histograms()
        self.objs.append(stacked)
        self.objs.append(bkghists)
        datahists = self.histmanager.get_data_histograms()
        self.objs.append(datahists)
        datahist = None
        if len(datahists) != 0:
            datahist = self.histmanager.get_summed_histograms(datahists)
        else:
            print 'asked for ratio plot of data/bkg but no data plots exist!'
        self.objs.append(datahist)
        bkghist = None
        if len(bkghists) != 0:
            bkghist = self.histmanager.get_summed_histograms(bkghists)
        #else:
        #    print 'asked for ratio plot of data/bkg but no bkg plots exist!'
        self.objs.append(bkghist)
        ratios = []
        hists = []
        hists.append(bkghist)
        hists.append(datahist)
        for index, hist in enumerate(hists):
            if index == 0:
                continue
            ratios.append(hist.Clone())
            #print 'KS test=',ratios[-1].KolmogorovTest(hists[0])
            ratios[-1].Divide(hists[0])
        for index, ratio in enumerate(ratios):
            if self.args.print_ratio_plot:
                ratio.Print('all')
            if index == 0:
                ratio.Draw('ex0p')
                ratio.SetMaximum(self.args.ratio_maximum)
                ratio.SetMinimum(self.args.ratio_minimum)
                self.histmanager.set_histaxis_settings(ratio, 2.0)
                self.histmanager.set_histaxis_labels(ratio)
                ratio.GetYaxis().SetTitle('Ratio')
                ratio.Print("all")

                # polynomial fit============================
                #tf2 = ROOT.TF1('fit', 'pol1', 0., 500.)
                #tf2.SetParameter(0, 7.85922e-01)
                #tf2.SetParameter(1, 3.91114e+01)
                #tf2.SetParameter(2, 5.26925e+01)
                #tf2.Draw('same')
                #tf2.SetLineColor(4)
                #ratio.Fit(tf2,"","",150.,500.)
                # polynomial fit============================

                # polynomial fit============================
                #tf2 = ROOT.TF1('fit', '[0]*TMath::ATan((x-[2])/[1])', 0., 500.)
                #tf2.SetParameter(0, 7.85922e-01)
                #tf2.SetParameter(1, 3.91114e+01)
                #tf2.SetParameter(2, 5.26925e+01)
                #tf2.Draw('same')
                #tf2.SetLineColor(4)
                #ratio.Fit(tf2,"","",0.,500.)
                # polynomial fit============================
            else:
                ratio.Draw('ex0psame')
        # this is actually not needed as the errors are propagated to the "data points error bar"
        ## obtain unity with fractional error of background
        #unitybkghist = bkghist.Clone()
        #for index in xrange(unitybkghist.GetNbinsX()):
        #    bc = unitybkghist.GetBinContent(index+1)
        #    be = unitybkghist.GetBinError(index+1)
        #    frac = 0
        #    if bc != 0:
        #        frac = be/bc
        #    unitybkghist.SetBinContent(index+1, 1)
        #    unitybkghist.SetBinError(index+1, frac)
        #self.objs.append(unitybkghist)
        #unitybkghist.SetFillStyle(3245)
        #unitybkghist.SetFillColor(12)
        #unitybkghist.Draw('E2 same')
        ## redraw
        #for index, ratio in enumerate(ratios):
        #    ratio.Draw('ex0psame')
        self.objs.append(ratios)

    def draw_ratio_1d(self):
        canvas = self.canvasfactory.get_canvas()
        hists = self.histmanager.get_background_histograms()
        if len(hists) == 0:
            sys.exit(-1)
        ymax = 0
        canvas.cd(1)
        hists[0].Draw('hist')
        for index, hist in enumerate(hists):
            if index == 0:
                hist.Draw('histsame')
                print hist.GetMean()
            else:
                hist.Draw('epsame')
                print hist.GetMean()
            if ymax < hist.GetMaximum():
                ymax = hist.GetMaximum()
        hists[0].SetMaximum(ymax*1.2)
        legend = self.legendfactory.get_legend(hists)
        legend.Draw('same')
        latex = ROOT.TLatex()
        if self.args.plotlabel:
            latex.SetTextFont(42)
            latex.SetTextSize(0.050)
            latex.SetTextAlign(10)
            latex.DrawLatexNDC(.2,.92,self.args.plotlabel)
        canvas.cd(2).SetGridy()
        ratios = []
        for index, hist in enumerate(hists):
            if index == 0:
                continue
            ratios.append(hist.Clone())
            ratios[-1].Divide(hists[0])
        for index, ratio in enumerate(ratios):
            if index == 0:
                ratio.Draw('ep')
                ratio.SetMaximum(1.7)
                ratio.SetMinimum(0.3)
                self.histmanager.set_histaxis_settings(ratio, 2.0)
                self.histmanager.set_histaxis_labels(ratio)
                ratio.GetYaxis().SetTitle('Ratio')
                #tf1 = ROOT.TF1('fit', '[0]*TMath::ATan((x-[2])/[1])', 0., 500.)
                #tf1.SetParameter(0, 7.53069e-01)
                #tf1.SetParameter(1, 3.12394e+01)
                #tf1.SetParameter(2, 5.26925e+01)
                #tf1.Draw('same')
# ArcTan
#                       tf2 = ROOT.TF1('fit', '[0]*TMath::ATan((x-[2])/[1])', 0., 500.)
#                       tf2.SetParameter(0, 7.85922e-01)
#                       tf2.SetParameter(1, 3.91114e+01)
#                       tf2.SetParameter(2, 5.26925e+01)
#                       tf2.Draw('same')
#                       tf2.SetLineColor(4)
#                       ratio.Fit(tf2,"","",0.,500.)

#                       print "%.7g*TMath::ATan((x-%.7g)/%.7g)"%(tf2.GetParameter(0), tf2.GetParameter(1), tf2.GetParameter(2))
#                       tf3 = ROOT.TF1('fit', '[0]*TMath::ATan((x-[2])/[1])', 0., 500.)
#                       tf3.SetParameter(0, tf2.GetParameter(0))
#                       tf3.SetParameter(1, tf2.GetParameter(1))
#                       tf3.SetParameter(2, tf2.GetParameter(2)-45.8)
#                       tf3.Draw('same')
#                       print str(tf2.GetParameter(0))+"*TMath::ATan((x-"+str(tf2.GetParameter(2)-45.8)+")/"+str(tf2.GetParameter(1))+")"

# polynomial
                tf2 = ROOT.TF1('fit', 'pol1', 0., 500.)
                tf2.SetParameter(0, 7.85922e-01)
                #tf2.SetParameter(1, 3.91114e+01)
                #tf2.SetParameter(2, 5.26925e+01)
                tf2.Draw('same')
                tf2.SetLineColor(4)
                ratio.Fit(tf2,"","",0.,300.)

#                       print "%.7g%+.7g*x%+.7g*x*x%+.7g*x*x*x%+.7g*x*x*x*x"%(tf2.GetParameter(0), tf2.GetParameter(1), tf2.GetParameter(2), tf2.GetParameter(3), tf2.GetParameter(4))
#                       tf3 = ROOT.TF1('fit', 'pol3', 0., 500.)
#                       tf3.SetParameter(0, tf2.GetParameter(0))
#                       tf3.SetParameter(1, tf2.GetParameter(1))
#                       tf3.SetParameter(2, tf2.GetParameter(2)-45.8)
#                       tf3.Draw('same')
            else:
                ratio.Draw('epsame')
        self.canvassaver.save_canvas(canvas)

    def draw_individ_sig_scan(self):

        option = "s/sqrt(b)"

        stacked, bkghists = self.histmanager.get_background_stacked_histograms()
        self.objs.append(stacked)
        self.objs.append(bkghists)
        sighists = self.histmanager.get_signal_histograms()
        self.objs.append(sighists)
        #self.objs.append(datahist)
        bkghist = None
        if len(bkghists) != 0:
            bkghist = self.histmanager.get_summed_histograms(bkghists)
        else:
            print 'asked for a sig scan but not bkg hists exist'
        self.objs.append(bkghist)
        sig_scan_individ_hists = []
        sig_scan_lower_hists = []
        sig_scan_upper_hists = []
        hists = []
        hists.append(bkghist)
        hists += sighists
        for index, hist in enumerate(hists):
            if index == 0:
                continue
            sig_scan_individ_hists.append(hist.Clone())
            sig_scan_lower_hists.append(hist.Clone())
            sig_scan_upper_hists.append(hist.Clone())

        for index, sig_scan_individ_hist in enumerate(sig_scan_individ_hists):
            sighist = sighists[index]
            sig_scan_individ_hist.Reset()
            for i in xrange(1, bkghist.GetNbinsX()+1):
                # Individual significance
                passed_sig = sighist.GetBinContent(i)
                passed_bkg = bkghist.GetBinContent(i)
                signif = 0
                if passed_bkg > 0:
                    signif = passed_sig / math.sqrt(passed_bkg)
                sig_scan_individ_hist.SetBinContent(i,signif)

        for index, sig_scan_lower_hist in enumerate(sig_scan_lower_hists):
            sighist = sighists[index]
            sigindividhist = sig_scan_individ_hists[index]
            sig_scan_lower_hist.Reset()
            for i in xrange(1, bkghist.GetNbinsX()+1):
                # aggregate Individual significance
                total_sig = 0
                for j in xrange(1, i+1):
                    signif = sigindividhist.GetBinContent(j)
                    total_sig = math.sqrt(total_sig*total_sig + signif*signif)
                sig_scan_lower_hist.SetBinContent(i,total_sig)

        for index, sig_scan_upper_hist in enumerate(sig_scan_upper_hists):
            sighist = sighists[index]
            sigindividhist = sig_scan_individ_hists[index]
            sig_scan_upper_hist.Reset()
            sig_scan_upper_hist.SetLineStyle(2)
            for i in xrange(1, bkghist.GetNbinsX()+1):
                # aggregate Individual significance
                total_sig = 0
                for j in xrange(i, bkghist.GetNbinsX()+1):
                    signif = sigindividhist.GetBinContent(j)
                    total_sig = math.sqrt(total_sig*total_sig + signif*signif)
                sig_scan_upper_hist.SetBinContent(i,total_sig)

        globalmax = 0
        for index, sig_scan_lower_hist in enumerate(sig_scan_lower_hists):
            localmax = sig_scan_lower_hist.GetMaximum()
            if localmax > globalmax:
                globalmax = localmax
            if index == 0:
                sig_scan_lower_hist.Draw('hist')
                #sig_scan_lower_hist.SetMaximum(2.0)
                sig_scan_lower_hist.SetMinimum(0.0)
                self.histmanager.set_histaxis_settings(sig_scan_lower_hist, 2.0)
                self.histmanager.set_histaxis_labels(sig_scan_lower_hist)
                sig_scan_lower_hist.GetYaxis().SetTitle('s/sqrt(b)')
            else:
                sig_scan_lower_hist.Draw('histsame')
            self.objs.append(sig_scan_lower_hist)

        for index, sig_scan_upper_hist in enumerate(sig_scan_upper_hists):
            localmax = sig_scan_upper_hist.GetMaximum()
            if localmax > globalmax:
                globalmax = localmax
            if index == 0:
                sig_scan_upper_hist.Draw('histsame')
            else:
                sig_scan_upper_hist.Draw('histsame')
            self.objs.append(sig_scan_upper_hist)
        sig_scan_lower_hists[0].SetMaximum(globalmax*1.1)


    # draw data over background
    def draw_sig_scan(self):

        option = "s/sqrt(b)"

        stacked, bkghists = self.histmanager.get_background_stacked_histograms()
        self.objs.append(stacked)
        self.objs.append(bkghists)
        sighists = self.histmanager.get_signal_histograms()
        self.objs.append(sighists)
        #self.objs.append(datahist)
        bkghist = None
        if len(bkghists) != 0:
            bkghist = self.histmanager.get_summed_histograms(bkghists)
        else:
            print 'asked for ratio plot of data/bkg but no bkg plots exist!'
        self.objs.append(bkghist)
        sig_scan_lower_hists = []
        sig_scan_upper_hists = []
        sig_scan_lower_hists_accept = []
        sig_scan_upper_hists_accept = []
        hists = []
        hists.append(bkghist)
        hists += sighists
        for index, hist in enumerate(hists):
            if index == 0:
                continue
            sig_scan_lower_hists.append(hist.Clone())
            sig_scan_upper_hists.append(hist.Clone())
            sig_scan_lower_hists_accept.append(hist.Clone())
            sig_scan_upper_hists_accept.append(hist.Clone())

        for index, sig_scan_lower_hist in enumerate(sig_scan_lower_hists):

            bkghist
            sighist = sighists[index]

            sig_scan_lower_hist.Reset()
            sig_scan_lower_hists_accept[index].Reset()
            sig_scan_lower_hists_accept[index].SetLineStyle(3)

            all_sig_err = ROOT.Double()
            all_bkg_err = ROOT.Double()
            all_sig = sighist.IntegralAndError(0,sighist.GetNbinsX()+1,all_sig_err)
            all_bkg = bkghist.IntegralAndError(0,bkghist.GetNbinsX()+1,all_bkg_err)
            error_term = math.sqrt(0.1*0.1+(all_bkg_err/all_bkg)*(all_bkg_err/all_bkg))
            signif_base = ROOT.RooStats.NumberCountingUtils.BinomialExpZ(all_sig,all_bkg,error_term)
            print all_sig, all_sig_err, all_bkg, all_bkg_err, signif_base
            if option == "s/sqrt(b)":
                signif_base = all_sig / math.sqrt(all_bkg)

            passed_sig_err = ROOT.Double()
            passed_bkg_err = ROOT.Double()
            for i in xrange(bkghist.GetNbinsX()+1):
                passed_sig = sighist.IntegralAndError(i, sighist.GetNbinsX()+1,passed_sig_err)
                passed_bkg = bkghist.IntegralAndError(i, bkghist.GetNbinsX()+1,passed_bkg_err)
                signif = 0
                if passed_bkg > 0:
                    if option == "s/sqrt(b)":
                        signif = passed_sig / math.sqrt(passed_bkg)
                        signif /= signif_base
                    else:
                        error_term = math.sqrt(0.1*0.1+(passed_bkg_err/passed_bkg)*(passed_bkg_err/passed_bkg))
                        signif = ROOT.RooStats.NumberCountingUtils.BinomialExpZ(passed_sig,passed_bkg,error_term)
                        print i, signif, signif_base
                        signif /= signif_base
                sig_scan_lower_hist.SetBinContent(i+1,signif)
                sig_scan_lower_hists_accept[index].SetBinContent(i+1,passed_sig/all_sig)

        for index, sig_scan_upper_hist in enumerate(sig_scan_upper_hists):

            bkghist
            sighist = sighists[index]

            sig_scan_upper_hist.Reset()
            sig_scan_upper_hist.SetLineStyle(2)
            sig_scan_upper_hists_accept[index].Reset()
            sig_scan_upper_hists_accept[index].SetLineStyle(4)

            all_sig_err = ROOT.Double()
            all_bkg_err = ROOT.Double()
            all_sig = sighist.IntegralAndError(0,sighist.GetNbinsX()+1,all_sig_err)
            all_bkg = bkghist.IntegralAndError(0,bkghist.GetNbinsX()+1,all_bkg_err)
            error_term = math.sqrt(0.1*0.1+(all_bkg_err/all_bkg)*(all_bkg_err/all_bkg))
            signif_base = ROOT.RooStats.NumberCountingUtils.BinomialExpZ(all_sig,all_bkg,error_term)
            print all_sig, all_sig_err, all_bkg, all_bkg_err, signif_base
            if option == "s/sqrt(b)":
                signif_base = all_sig / math.sqrt(all_bkg)

            passed_sig_err = ROOT.Double()
            passed_bkg_err = ROOT.Double()
            for i in xrange(1,bkghist.GetNbinsX()+1):
                passed_sig = sighist.IntegralAndError(0, i, passed_sig_err)
                passed_bkg = bkghist.IntegralAndError(0, i, passed_bkg_err)
                signif = 0
                if passed_bkg > 0:
                    if option == "s/sqrt(b)":
                        signif = passed_sig / math.sqrt(passed_bkg)
                        signif /= signif_base
                    else:
                        error_term = math.sqrt(0.1*0.1+(passed_bkg_err/passed_bkg)*(passed_bkg_err/passed_bkg))
                        signif = ROOT.RooStats.NumberCountingUtils.BinomialExpZ(passed_sig,passed_bkg,error_term)
                        print i, signif, signif_base
                        signif /= signif_base
                sig_scan_upper_hist.SetBinContent(i+1,signif)
                sig_scan_upper_hists_accept[index].SetBinContent(i+1,passed_sig/all_sig)


        globalmax = 0
        for index, sig_scan_lower_hist in enumerate(sig_scan_lower_hists):
            #if self.args.print_ratio_plot:
            #    ratio.Print('all')
            localmax = sig_scan_lower_hist.GetMaximum()
            if localmax > globalmax:
                globalmax = localmax
            if index == 0:
                sig_scan_lower_hist.Draw('hist')
                sig_scan_lower_hist.SetMaximum(2.0)
                sig_scan_lower_hist.SetMinimum(0.0)
                self.histmanager.set_histaxis_settings(sig_scan_lower_hist, 2.0)
                self.histmanager.set_histaxis_labels(sig_scan_lower_hist)
                if option == "s/sqrt(b)":
                    sig_scan_lower_hist.GetYaxis().SetTitle('s/sqrt(b)')
                else:
                    sig_scan_lower_hist.GetYaxis().SetTitle('Z / Z_{0}')
                #sig_scan_lower_hist.Print("all")
            else:
                sig_scan_lower_hist.Draw('histsame')
            self.objs.append(sig_scan_lower_hist)

        for index, sig_scan_upper_hist in enumerate(sig_scan_upper_hists):
            #if self.args.print_ratio_plot:
            #    ratio.Print('all')
            localmax = sig_scan_upper_hist.GetMaximum()
            if localmax > globalmax:
                globalmax = localmax
            if index == 0:
                sig_scan_upper_hist.Draw('histsame')
                #self.histmanager.set_histaxis_settings(sig_scan_upper_hist, 2.0)
                #self.histmanager.set_histaxis_labels(sig_scan_upper_hist)
                #sig_scan_upper_hist.GetYaxis().SetTitle('S/#sqrt(B)')
                #sig_scan_upper_hist.Print("all")
            else:
                sig_scan_upper_hist.Draw('histsame')
            self.objs.append(sig_scan_upper_hist)
        sig_scan_lower_hists[0].SetMaximum(globalmax*1.1)

        for index, hist in enumerate(sig_scan_upper_hists_accept):
            localmax = hist.GetMaximum()
            if localmax > globalmax:
                globalmax = localmax
            if index == 0:
                hist.Draw('histsame')
            else:
                hist.Draw('histsame')
            self.objs.append(hist)

        for index, hist in enumerate(sig_scan_lower_hists_accept):
            localmax = hist.GetMaximum()
            if localmax > globalmax:
                globalmax = localmax
            if index == 0:
                hist.Draw('histsame')
            else:
                hist.Draw('histsame')
            self.objs.append(hist)

        #for hist, accepthist in zip(sig_scan_upper_hists, sig_scan_upper_hists_accept):
        #    for i in xrange(1, hist.GetNbinsX() + 1):
        #        if accepthist.GetBinContent(i)

if __name__ == '__main__':

    histpainter = HistogramPainter(args)
    if args.plottype == 'plot1d'      : histpainter.draw_standard_1d()
    if args.plottype == 'plot1dratio' : histpainter.draw_standard_1d_with_ratio()
    if args.plottype == 'ratio1d'     : histpainter.draw_ratio_1d()
    if args.plottype == 'plot1dsig'   : histpainter.draw_standard_1d_with_sigscan()
    if args.plottype == 'plot1dindsig': histpainter.draw_standard_1d_with_individ_sigscan()

