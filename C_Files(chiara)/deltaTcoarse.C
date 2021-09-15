#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TTree.h"
#include "Riostream.h"
#include <time.h>
#include "TStopwatch.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "lib/comFunc.h"
#include "lib/figTemplate.C"

using namespace std;

struct package {
  Int_t tigerId;
  Int_t ch;
  Int_t tacId;
  Int_t tcoarse;
  Int_t tcoarse_10b;
  Int_t ecoarse;
  Int_t tfine;
  Int_t efine;
};
package *p = new package;

void deltaTcoarse() {

    TFile *f = new TFile("RUN14_SubRUN_0_GEMROC_0_TL.root");

	TTree *treeTIGER0 = (TTree *)f ->Get("treeTIGER0");
	TTree *treeTIGER1 = (TTree *)f ->Get("treeTIGER1");

    treeTIGER0 ->GetBranch("packageTIGER0")->SetAddress(&p); //getting branch and contents for TIGER 0  
	treeTIGER1 ->GetBranch("packageTIGER1")->SetAddress(&p); //getting branch and contents for TIGER 1

    TH1D *DeltaTcoarseT0 = new TH1D ("TcoarseDistT0", Form("Delta Tcoarse distribution TIGER0; #DeltaTcoarse[bin]"), 20, -9.5, 10.5);
	TH1D *DeltaTcoarseT1 = new TH1D ("TcoarseDistT1", Form("Delta Tcoarse distribution TIGER1; #DeltaTcoarse[bin]"), 20, -9.5, 10.5);

    TF1 *f0 = new TF1("f0", "gaus(0)", -3.00 ,4.00); 
	//f0->SetParLimits(0, 59e3, 60e3);
	//f0->SetParLimits(3, 10, 10e3);
	TF1 *f1 = new TF1("f1", "gaus(0)", -4.00 ,4.00);
	//f1->SetParLimits(0, 110e3, 120e3);
	//f1->SetParLimits(3, 1.9, 2);      

    Int_t t0 = 0;       //variable added to save prev tcoarse value
	Int_t t1 = 0;       //variable added to save prev tcoarse value

    int deltaTcoarseT0, deltaTcoarseT1;

    for (int t0_entry = 0; t0_entry < treeTIGER0->GetEntries(); t0_entry++){
		
		treeTIGER0 -> GetEntry(t0_entry);
		
		deltaTcoarseT0 = t0 - p->tcoarse;
        DeltaTcoarseT0 -> Fill(deltaTcoarseT0);
	
		t0 = p->tcoarse;
	}
	
	for (int t1_entry = 0; t1_entry < treeTIGER1->GetEntries(); t1_entry ++){

		treeTIGER1 -> GetEntry(t1_entry);

		deltaTcoarseT1 = t1 - p->tcoarse;
        DeltaTcoarseT1 -> Fill(deltaTcoarseT1);

		t1 = p->tcoarse;
	}

initFigTemplate();
    TCanvas *cDeltaT0 = new TCanvas("cDeltaT0","cDeltaT");
	gStyle->SetPalette(kRainBow);
	gStyle ->SetOptFit(11);
    DeltaTcoarseT0 ->Draw();
    DeltaTcoarseT0 ->Fit(f0);

	TCanvas *cDeltaT1 = new TCanvas("cDeltaT1","cDeltaT");
	gStyle->SetPalette(kRainBow);
	DeltaTcoarseT1 ->Draw();
    DeltaTcoarseT1 ->Fit(f1);
	
}