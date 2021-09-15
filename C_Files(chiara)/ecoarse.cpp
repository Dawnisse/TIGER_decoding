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

void ecoarse() {
	
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

	TH1D *ecoarsedistT0 = new TH1D("ecoarsehitsT0",  Form("ChnHitT0 ;ecoarse[bin]; hits"),1024,0,1024);
	TH1D *ecoarsedistT1 = new TH1D("ecoarsehitsT1",  Form("ChnHitT1 ;ecoarse[bin]; hits"),1024,0,1024);
	TH1D *ecoarsedistT2 = new TH1D("ecoarsehitsT2",  Form("ChnHitT2 ;ecoarse[bin]; hits"),1024,0,1024);
	TH1D *ecoarsedistT3 = new TH1D("ecoarsehitsT3",  Form("ChnHitT3 ;ecoarse[bin]; hits"),1024,0,1024);
	TH1D *ecoarsedistT4 = new TH1D("ecoarsehitsT4",  Form("ChnHitT4 ;ecoarse[bin]; hits"),1024,0,1024);
	TH1D *ecoarsedistT5 = new TH1D("ecoarsehitsT5",  Form("ChnHitT5 ;ecoarse[bin]; hits"),1024,0,1024);

    for (int t0_entry = 0; t0_entry < treeTIGER0->GetEntries(); t0_entry++){
	
		treeTIGER0 -> GetEntry(t0_entry);
		ecoarsedistT0 -> Fill(p->ecoarse);  //fill histo for TIGER0
			
	}

	for (int t1_entry = 0; t1_entry < treeTIGER1->GetEntries(); t1_entry ++){

		treeTIGER1 -> GetEntry(t1_entry);
		ecoarsedistT1 -> Fill(p->ecoarse);  //fill hito for TIGER1
	}

	for (int t2_entry = 0; t2_entry < treeTIGER2->GetEntries(); t2_entry ++){

		treeTIGER2 -> GetEntry(t2_entry);
		ecoarsedistT2 -> Fill(p->ecoarse);  //fill hito for TIGER2
	}

	for (int t3_entry = 0; t3_entry < treeTIGER3->GetEntries(); t3_entry ++){

		treeTIGER3 -> GetEntry(t3_entry);
		ecoarsedistT3 -> Fill(p->ecoarse);  //fill hito for TIGER3
	}

	for (int t4_entry = 0; t4_entry < treeTIGER4->GetEntries(); t4_entry ++){

		treeTIGER4 -> GetEntry(t4_entry);
		ecoarsedistT4 -> Fill(p->ecoarse);  //fill hito for TIGER3
	}

	for (int t5_entry = 0; t5_entry < treeTIGER5->GetEntries(); t5_entry ++){

		treeTIGER5 -> GetEntry(t5_entry);
		ecoarsedistT5 -> Fill(p->ecoarse);  //fill hito for TIGER3
	}

    TCanvas *cecoarseT0 = new TCanvas("cecoarseT0","cecoarseT0");
	gStyle->SetPalette(kRainBow);
	ecoarsedistT0->Draw("colz");
    ecoarsedistT0->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/ecoarse/subRUN3/ecoarseTIGER0.pdf");
	TCanvas *cecoarseT1 = new TCanvas("cecoarseT1","cecoarseT1");
	ecoarsedistT1->Draw("colz");
    ecoarsedistT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/ecoarse/subRUN3/ecoarseTIGER1.pdf");
	TCanvas *cecoarseT2 = new TCanvas("cecoarseT2","cecoarseT2");
	ecoarsedistT2->Draw("colz");
    ecoarsedistT2->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/ecoarse/subRUN3/ecoarseTIGER2.pdf");
	TCanvas *cecoarseT3 = new TCanvas("cecoarseT3","cecoarseT3");
	ecoarsedistT3->Draw("colz");
    ecoarsedistT3->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/ecoarse/subRUN3/ecoarseTIGER3.pdf");
	TCanvas *cecoarseT4 = new TCanvas("cecoarseT4","cecoarseT4");
	ecoarsedistT4->Draw("colz");
    ecoarsedistT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/ecoarse/subRUN3/ecoarseTIGER4.pdf");
	TCanvas *cecoarseT5 = new TCanvas("cecoarseT5","cecoarseT5");
    ecoarsedistT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/ecoarse/subRUN3/ecoarseTIGER5.pdf");
	ecoarsedistT5->Draw("colz");
}