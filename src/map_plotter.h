#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip> // for setw()
#include <time.h>

#include "TSystem.h"
#include "TRandom.h"
#include "TROOT.h"
#include "TF1.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TBranch.h"
#include "TString.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TLatex.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TColor.h"

#include "utilities.C"
using namespace std;


class map_plotter{

public:

	pair<int,int> nLGADHitsAndChannel();
	int indexGoodPhotekHit();
	void InitBranches();
	void makeMaps();
	void FillChannelMap(TH2F * map, vector<TH2F*> effs);
	void FillSummaryMap(vector<TH2F*> v_map, TH2F * channel_map);
	void FillSummaryMapCoarse(vector<TH2F*> v_map, TH2F* effmap, TH2F * channel_map);
	void FillSummary1D(vector<TH1F*> v_map, TH2F * channel_map, bool isX);

	void ConvertMap(TH3F * h3, TH2F * h2, int type);
	void Convert1D(TH3F * h3, TH1F * h1, int type, bool isX);
	void FillBox(TH3F * h3, TH1D * h1, int ibox);
	void CleanMap(TH2F * map, float xmin, float xmax, float ymin, float ymax, bool scale);
	float GetEff(TH3F * h3, int x_lo, int x_hi, int y_lo, int y_hi, int den=0);

	TString tag;
	TString chainPath;
	bool debug;
	int run_start;
	int run_end;
	static const int nchan=4;
	static const int nchan_lgad=3;
	static const int npad=16;//3;//16;
	float hitThres;
	float photekMin;
	float photekMax;

	float angle;
	float x_offset;
	float y_offset;
	float saturation;
	//Divide interior of each pad in subsections (3x3 grid)
	//Specify bounds on one corner, use avg pad width including dead region to extrapolate to other pads
	//Plot boundaries at end for sanity check.

	vector<float> y_div;
	vector<float> x_div;

	float npad_y;
	float npad_x;
	float pad_width;


	//efficiency
	int nbinsX;
	int nbinsY;
	int gainbinfactor; //coarser binning for gain maps


	int minX;
	int maxX;
	float minY;
	float maxY;

	//// For 1D projections
	float xSliceMin;
	float xSliceMax;
	float ySliceMin;
	float ySliceMax;


	float nbinsAmp;
	float nbinsTime;
	float minAmp;
	float maxAmp;
	float minTime;
	float maxTime;


	//////


	TChain * t;
	TFile * outRootFile;

	Float_t amp[nchan];
	Float_t LP2_20[nchan];
	Float_t LP2_40[nchan];
	Float_t chi2;
	Int_t ntracks;
	Int_t nback;
	Int_t npix;
	Float_t y_dut[3];
	Float_t x_dut[3];

	Int_t run;
	Int_t gconf;
	vector<int> *pads;
	vector<string> *sensors;

	vector<TH3F*> v_h_eff;
	vector<TH3F*> v_h_eff_timing;
	vector<TH3F*> v_h_amp;
	vector<TH3F*> v_h_time;
	vector<TH3F*> v_h_run;

	TH2F * channel_map;

	vector<TH2F*> v_map_eff;
	vector<TH2F*> v_map_eff_timing;
	vector<TH2F*> v_map_nhits;
	vector<TH2F*> v_map_amp;
	vector<TH2F*> v_map_deltat;
	vector<TH2F*> v_map_sigmat;

	TH2F * cosmetic_map;

	vector<TH1F*> v_x_eff_top;
	vector<TH1F*> v_x_nhits_top;
	vector<TH1F*> v_x_amp_top;
	vector<TH1F*> v_x_deltat_top;
	vector<TH1F*> v_x_sigmat_top;

	vector<TH1F*> v_x_eff_bot;
	vector<TH1F*> v_x_nhits_bot;
	vector<TH1F*> v_x_amp_bot;
	vector<TH1F*> v_x_deltat_bot;
	vector<TH1F*> v_x_sigmat_bot;

	vector<TH1F*> v_y_eff;
	vector<TH1F*> v_y_nhits;
	vector<TH1F*> v_y_amp;
	vector<TH1F*> v_y_deltat;
	vector<TH1F*> v_y_sigmat;

	vector<TH1D*> v_amp_dists;
	vector<TH1D*> v_run_dists;

	vector<TH1F*> v_eff_uniformity;
	vector<TH1F*> v_den_uniformity;


};

