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

void channelHits() {
	
	TFile *f = new TFile("./root_data/RUN17_SubRUN_0_GEMROC_0_TL.root");

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

	TH1D *channel_distT0 = new TH1D("channel_hitsT0",  Form("ChnHitT0 ;Channel; hits"), 64, -0.5, 63.5);
	TH1D *channel_distT1 = new TH1D("channel_hitsT1",  Form("ChnHitT1 ;Channel; hits"), 64, -0.5, 63.5);
	TH1D *channel_distT2 = new TH1D("channel_hitsT2",  Form("ChnHitT2 ;Channel; hits"), 64, -0.5, 63.5);
	TH1D *channel_distT3 = new TH1D("channel_hitsT3",  Form("ChnHitT3 ;Channel; hits"), 64, -0.5, 63.5);
	TH1D *channel_distT4 = new TH1D("channel_hitsT4",  Form("ChnHitT4 ;Channel; hits"), 64, -0.5, 63.5);
	TH1D *channel_distT5 = new TH1D("channel_hitsT5",  Form("ChnHitT5 ;Channel; hits"), 64, -0.5, 63.5);

    for (int t0_entry = 0; t0_entry < treeTIGER0->GetEntries(); t0_entry++){
	
		treeTIGER0 -> GetEntry(t0_entry);
		channel_distT0 -> Fill(p->ch);  //fill histo for TIGER0
			
	}

	for (int t1_entry = 0; t1_entry < treeTIGER1->GetEntries(); t1_entry ++){

		treeTIGER1 -> GetEntry(t1_entry);
		channel_distT1 -> Fill(p->ch);  //fill hito for TIGER1
	}

	for (int t2_entry = 0; t2_entry < treeTIGER2->GetEntries(); t2_entry ++){

		treeTIGER2 -> GetEntry(t2_entry);
		channel_distT2 -> Fill(p->ch);  //fill hito for TIGER2
	}

	for (int t3_entry = 0; t3_entry < treeTIGER3->GetEntries(); t3_entry ++){

		treeTIGER3 -> GetEntry(t3_entry);
		channel_distT3 -> Fill(p->ch);  //fill hito for TIGER3
	}

	for (int t4_entry = 0; t4_entry < treeTIGER4->GetEntries(); t4_entry ++){

		treeTIGER4 -> GetEntry(t4_entry);
		channel_distT4 -> Fill(p->ch);  //fill hito for TIGER3
	}

	for (int t5_entry = 0; t5_entry < treeTIGER5->GetEntries(); t5_entry ++){

		treeTIGER5 -> GetEntry(t5_entry);
		channel_distT5 -> Fill(p->ch);  //fill hito for TIGER3
	}

    TCanvas *cChnHitT0 = new TCanvas("cChnHitT0","cChnHitT0");
	gStyle->SetPalette(kRainBow);
	channel_distT0->Draw("colz");
    channel_distT0->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/channels/subRUN3/chnVShits_TIGER0.pdf");
	TCanvas *cChnHitT1 = new TCanvas("cChnHitT1","cChnHitT1");
	channel_distT1->Draw("colz");
    channel_distT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/channels/subRUN3/chnVShits_TIGER1.pdf");
	TCanvas *cChnHitT2 = new TCanvas("cChnHitT2","cChnHitT2");
	channel_distT2->Draw("colz");
    channel_distT2->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/channels/subRUN3/chnVShits_TIGER2.pdf");
	TCanvas *cChnHitT3 = new TCanvas("cChnHitT3","cChnHitT3");
	channel_distT3->Draw("colz");
    channel_distT3->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/channels/subRUN3/chnVShits_TIGER3.pdf");
	TCanvas *cChnHitT4 = new TCanvas("cChnHitT4","cChnHitT4");
	channel_distT4->Draw("colz");
    channel_distT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/channels/subRUN3/chnVShits_TIGER4.pdf");
	TCanvas *cChnHitT5 = new TCanvas("cChnHitT5","cChnHitT5");
    channel_distT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/channels/subRUN3/chnVShits_TIGER5.pdf");
	channel_distT5->Draw("colz");


}
