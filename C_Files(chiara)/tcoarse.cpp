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

void tcoarse() {
	
	TFile *f = new TFile("RUN19_SubRUN_3_GEMROC_0_TL.root");

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

	TH1D *tcoarse_distT0 = new TH1D("tcoarse_hitsT0",  Form("ChnHitT0 ;tcoarse[bin]; hits"),65535,0,65535);
	TH1D *tcoarse_distT1 = new TH1D("tcoarse_hitsT1",  Form("ChnHitT1 ;tcoarse[bin]; hits"),65535,0,65535);
	TH1D *tcoarse_distT2 = new TH1D("tcoarse_hitsT2",  Form("ChnHitT2 ;tcoarse[bin]; hits"),65535,0,65535);
	TH1D *tcoarse_distT3 = new TH1D("tcoarse_hitsT3",  Form("ChnHitT3 ;tcoarse[bin]; hits"),65535,0,65535);
	TH1D *tcoarse_distT4 = new TH1D("tcoarse_hitsT4",  Form("ChnHitT4 ;tcoarse[bin]; hits"),65535,0,65535);
	TH1D *tcoarse_distT5 = new TH1D("tcoarse_hitsT5",  Form("ChnHitT5 ;tcoarse[bin]; hits"),65535,0,65535);

    for (int t0_entry = 0; t0_entry < treeTIGER0->GetEntries(); t0_entry++){
	
		treeTIGER0 -> GetEntry(t0_entry);
		tcoarse_distT0 -> Fill(p->tcoarse);  //fill histo for TIGER0
			
	}

	for (int t1_entry = 0; t1_entry < treeTIGER1->GetEntries(); t1_entry ++){

		treeTIGER1 -> GetEntry(t1_entry);
		tcoarse_distT1 -> Fill(p->tcoarse);  //fill hito for TIGER1
	}

	for (int t2_entry = 0; t2_entry < treeTIGER2->GetEntries(); t2_entry ++){

		treeTIGER2 -> GetEntry(t2_entry);
		tcoarse_distT2 -> Fill(p->tcoarse);  //fill hito for TIGER2
	}

	for (int t3_entry = 0; t3_entry < treeTIGER3->GetEntries(); t3_entry ++){

		treeTIGER3 -> GetEntry(t3_entry);
		tcoarse_distT3 -> Fill(p->tcoarse);  //fill hito for TIGER3
	}

	for (int t4_entry = 0; t4_entry < treeTIGER4->GetEntries(); t4_entry ++){

		treeTIGER4 -> GetEntry(t4_entry);
		tcoarse_distT4 -> Fill(p->tcoarse);  //fill hito for TIGER3
	}

	for (int t5_entry = 0; t5_entry < treeTIGER5->GetEntries(); t5_entry ++){

		treeTIGER5 -> GetEntry(t5_entry);
		tcoarse_distT5 -> Fill(p->tcoarse);  //fill hito for TIGER3
	}

    TCanvas *cTcoarseT0 = new TCanvas("cTcoarseT0","cTcoarseT0");
	gStyle->SetPalette(kRainBow);
	tcoarse_distT0->Draw("colz");
    tcoarse_distT0->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tcoarse/subRUN3/tcoarse_TIGER0.pdf");
	TCanvas *cTcoarseT1 = new TCanvas("cTcoarseT1","cTcoarseT1");
	tcoarse_distT1->Draw("colz");
    tcoarse_distT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tcoarse/subRUN3/tcoarse_TIGER1.pdf");
	TCanvas *cTcoarseT2 = new TCanvas("cTcoarseT2","cTcoarseT2");
	tcoarse_distT2->Draw("colz");
    tcoarse_distT2->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tcoarse/subRUN3/tcoarse_TIGER2.pdf");
	TCanvas *cTcoarseT3 = new TCanvas("cTcoarseT3","cTcoarseT3");
	tcoarse_distT3->Draw("colz");
    tcoarse_distT3->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tcoarse/subRUN3/tcoarse_TIGER3.pdf");
	TCanvas *cTcoarseT4 = new TCanvas("cTcoarseT4","cTcoarseT4");
	tcoarse_distT4->Draw("colz");
    tcoarse_distT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tcoarse/subRUN3/tcoarse_TIGER4.pdf");
	TCanvas *cTcoarseT5 = new TCanvas("cTcoarseT5","cTcoarseT5");
    tcoarse_distT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tcoarse/subRUN3/tcoarse_TIGER5.pdf");
	tcoarse_distT5->Draw("colz");
}
