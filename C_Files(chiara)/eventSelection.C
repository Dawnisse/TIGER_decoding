#include <iostream>
#include "TFile.h"
#include "TH1D.h"
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
  Int_t ecoarse;
  Int_t tfine;
  Int_t efine;
};
package *p = new package;

void eventSelection() {
	
	TFile *f = new TFile("SubRUN_10_GEMROC_7_TL.root");

	TTree *treeTIGER0 = (TTree *)f ->Get("treeTIGER0");
	TTree *treeTIGER1 = (TTree *)f ->Get("treeTIGER1");
	TTree *treeTIGER6 = (TTree *)f ->Get("treeTIGER6");
	TTree *treeTIGER7 = (TTree *)f ->Get("treeTIGER7");

	treeTIGER0 ->GetBranch("packageTIGER0")->SetAddress(&p); //getting branch and contents for TIGER 0  
	treeTIGER1 ->GetBranch("packageTIGER1")->SetAddress(&p); //getting branch and contents for TIGER 1
	treeTIGER6 ->GetBranch("packageTIGER6")->SetAddress(&p); //getting branch and contents for TIGER 6  
	treeTIGER7 ->GetBranch("packageTIGER7")->SetAddress(&p); //getting branch and contents for TIGER 6

	TH1D *DeltaTcoarseT0 = new TH1D ("TcoarseDistT0", Form("Delta Tcoarse distribution TIGER0; #DeltaTcoarse[bin]"), 100, -50, 50);
	TH1D *DeltaTcoarseT1 = new TH1D ("TcoarseDistT1", Form("Delta Tcoarse distribution TIGER1; #DeltaTcoarse[bin]"), 100, -50, 50);
	//TH2D *event_selectionT0 = new TH2D("event_selectionT0",  Form("Channel timing distribution(after selection) ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);
	//TH2D *event_selectionT1 = new TH2D("event_selectionT1",  Form("Channel timing distribution(after selection) ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);
	TH2D *event_selectionT6 = new TH2D("event_selectionT6",  Form("Channel timing distribution(after selection) ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);
	TH2D *event_selectionT7 = new TH2D("event_selectionT7",  Form("Channel timing distribution(after selection) ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);

	Int_t t6 = 0;       //variable added to save prev tcoarse value
	Int_t t7 = 0;       //variable added to save prev tcoarse value

	bool pause = true;

	for (int t6_entry = 0; t6_entry < treeTIGER6->GetEntries(); t6_entry ++){

		treeTIGER6 -> GetEntry(t6_entry);
		if (t6_entry == 0){
		  event_selectionT6 -> Fill(p->ch, p->tcoarse);
		}
        else if (p->tcoarse < t6 + 2){
           event_selectionT6 -> Fill(p->ch, p->tcoarse);
		}
		t6 = p->tcoarse;
	}

	for (int t7_entry = 0; t7_entry < treeTIGER7->GetEntries(); t7_entry ++){

		treeTIGER7 -> GetEntry(t7_entry);
		if (t7_entry == 0){
		  event_selectionT7 -> Fill(p->ch, p->tcoarse);
		}
        else if (p->tcoarse < t7 + 2){
           event_selectionT7 -> Fill(p->ch, p->tcoarse);
		}
		t7 = p->tcoarse;
	}

initFigTemplate();
	TCanvas *cEventSel = new TCanvas("cEventSel","cEventSel");
	gStyle->SetPalette(kRainBow);
	cEventSel ->Divide(1, 2);
	cEventSel->cd(1);
	event_selectionT6->Draw("colz");
	cEventSel->cd(2);
	event_selectionT7->Draw("colz");
}
	






