#include "Riostream.h"
#include "Rtypes.h"
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "fstream"
#include "istream" //file input
#include "sstream" //string manip
#include <string>
#include <time.h>
#include <signal.h>
#include "TTimer.h"

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

void channelTimingDist() {
	
	TFile *f = new TFile("RUN14_SubRUN_0_GEMROC_0_TL.root");

	TTree *treeTIGER0 = (TTree *)f ->Get("treeTIGER0");
	TTree *treeTIGER1 = (TTree *)f ->Get("treeTIGER1");
	TTree *treeTIGER2 = (TTree *)f ->Get("treeTIGER2");
	TTree *treeTIGER3 = (TTree *)f ->Get("treeTIGER3");
	TTree *treeTIGER4 = (TTree *)f ->Get("treeTIGER4");
	TTree *treeTIGER5 = (TTree *)f ->Get("treeTIGER5");

	treeTIGER0 ->GetBranch("packageTIGER0")->SetAddress(&p); //getting branch and contents for TIGER 0  
	treeTIGER1 ->GetBranch("packageTIGER1")->SetAddress(&p); //getting branch and contents for TIGER 1
	treeTIGER2 ->GetBranch("packageTIGER2")->SetAddress(&p); //getting branch and contents for TIGER 2 
	treeTIGER3 ->GetBranch("packageTIGER3")->SetAddress(&p); //getting branch and contents for TIGER 3
	treeTIGER4 ->GetBranch("packageTIGER4")->SetAddress(&p); //getting branch and contents for TIGER 4 
	treeTIGER5 ->GetBranch("packageTIGER5")->SetAddress(&p); //getting branch and contents for TIGER 5

	TH2D *channel_distT0 = new TH2D("channel_distT0",  Form("Channel timing distribution ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);
	TH2D *channel_distT1 = new TH2D("channel_distT1",  Form("Channel timing distribution ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);
	TH2D *channel_distT2 = new TH2D("channel_distT2",  Form("Channel timing distribution ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);
	TH2D *channel_distT3 = new TH2D("channel_distT3",  Form("Channel timing distribution ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);
	TH2D *channel_distT4 = new TH2D("channel_distT4",  Form("Channel timing distribution ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);
	TH2D *channel_distT5 = new TH2D("channel_distT5",  Form("Channel timing distribution ;Channel;Tcoarse [bin]"), 64, -0.5, 63.5, 65000, 0, 65000);

	//TTimer *timer = new TTimer(1000);

	//auto start = std::chrono::high_resolution_clock::now(); //starting reading

	//timer->Connect("Timeout()", "TCanvas", cChannelDistT0, "Update()");

	for (int t0_entry = 0; t0_entry < treeTIGER0->GetEntries(); t0_entry++){
	
		treeTIGER0 -> GetEntry(t0_entry);
		channel_distT0 -> Fill(p->ch, p->tcoarse);  //fill histo for TIGER0
			
	}

	for (int t1_entry = 0; t1_entry < treeTIGER1->GetEntries(); t1_entry ++){

		treeTIGER1 -> GetEntry(t1_entry);
		channel_distT1 -> Fill(p->ch, p->tcoarse);  //fill hito for TIGER1
	}

	for (int t2_entry = 0; t2_entry < treeTIGER2->GetEntries(); t2_entry ++){

		treeTIGER2 -> GetEntry(t2_entry);
		channel_distT2 -> Fill(p->ch, p->tcoarse);  //fill hito for TIGER2
	}

	for (int t3_entry = 0; t3_entry < treeTIGER3->GetEntries(); t3_entry ++){

		treeTIGER3 -> GetEntry(t3_entry);
		channel_distT3 -> Fill(p->ch, p->tcoarse);  //fill hito for TIGER3
	}

	for (int t4_entry = 0; t4_entry < treeTIGER4->GetEntries(); t4_entry ++){

		treeTIGER4 -> GetEntry(t4_entry);
		channel_distT4 -> Fill(p->ch, p->tcoarse);  //fill hito for TIGER3
	}

	for (int t5_entry = 0; t5_entry < treeTIGER5->GetEntries(); t5_entry ++){

		treeTIGER5 -> GetEntry(t5_entry);
		channel_distT5 -> Fill(p->ch, p->tcoarse);  //fill hito for TIGER3
	}

	/* one canvas settings
	TCanvas *cChannelDist = new TCanvas("cChannelDist","cChannelDist");
	gStyle->SetPalette(kRainBow);
	//timer->Start(2000,kTRUE);
	cChannelDist->Divide(2,2,0,0);
	cChannelDist->cd(1);
	channel_distT0->Draw("colz");
	cChannelDist->cd(2);
	channel_distT1->Draw("colz");
	cChannelDist->cd(3);
	channel_distT2->Draw("colz");
	cChannelDist->cd(4);
	channel_distT7->Draw("colz");
	*/
	TCanvas *cChannelDistT0 = new TCanvas("cChannelDistT0","cChannelDistT0");
	gStyle->SetPalette(kRainBow);
	channel_distT0->Draw("colz");
	TCanvas *cChannelDistT1 = new TCanvas("cChannelDistT1","cChannelDistT1");
	channel_distT1->Draw("colz");
	TCanvas *cChannelDistT2 = new TCanvas("cChannelDistT2","cChannelDistT2");
	channel_distT2->Draw("colz");
	TCanvas *cChannelDistT3 = new TCanvas("cChannelDistT3","cChannelDistT3");
	channel_distT3->Draw("colz");
	TCanvas *cChannelDistT4 = new TCanvas("cChannelDistT4","cChannelDistT4");
	channel_distT4->Draw("colz");
	TCanvas *cChannelDistT5 = new TCanvas("cChannelDistT5","cChannelDistT5");
	channel_distT5->Draw("colz");
}
