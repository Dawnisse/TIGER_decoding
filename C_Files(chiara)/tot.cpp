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

void tot() {
	
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

	TH1D *totdistT0 = new TH1D("tothitsT0",  Form("ChnHitT0 ;tot[bin]; hits"),1024,0,1024);
	TH1D *totdistT1 = new TH1D("tothitsT1",  Form("ChnHitT1 ;tot[bin]; hits"),1024,0,1024);
	TH1D *totdistT2 = new TH1D("tothitsT2",  Form("ChnHitT2 ;tot[bin]; hits"),1024,0,1024);
	TH1D *totdistT3 = new TH1D("tothitsT3",  Form("ChnHitT3 ;tot[bin]; hits"),1024,0,1024);
	TH1D *totdistT4 = new TH1D("tothitsT4",  Form("ChnHitT4 ;tot[bin]; hits"),1024,0,1024);
	TH1D *totdistT5 = new TH1D("tothitsT5",  Form("ChnHitT5 ;tot[bin]; hits"),1024,0,1024);

    for (int t0_entry = 0; t0_entry < treeTIGER0->GetEntries(); t0_entry++){
	
		treeTIGER0 -> GetEntry(t0_entry);
		if(p->ecoarse < 1024)
        totdistT0 -> Fill(p->ecoarse - p->tcoarse_10b);
        else
        totdistT1 -> Fill((p->ecoarse - p->tcoarse_10b)+1024);  //fill histo for TIGER0
			
	}

	for (int t1_entry = 0; t1_entry < treeTIGER1->GetEntries(); t1_entry ++){

		treeTIGER1 -> GetEntry(t1_entry);
		if(p->ecoarse < 1024)
        totdistT1 -> Fill(p->ecoarse - p->tcoarse_10b);
        else
        totdistT1 -> Fill((p->ecoarse - p->tcoarse_10b)+1024);  //fill hito for TIGER1
	}

	for (int t2_entry = 0; t2_entry < treeTIGER2->GetEntries(); t2_entry ++){

		treeTIGER2 -> GetEntry(t2_entry);
		if(p->ecoarse < 1024)
        totdistT2 -> Fill(p->ecoarse - p->tcoarse_10b);
        else
        totdistT1 -> Fill((p->ecoarse - p->tcoarse_10b)+1024);  //fill hito for TIGER2
	}

	for (int t3_entry = 0; t3_entry < treeTIGER3->GetEntries(); t3_entry ++){

		treeTIGER3 -> GetEntry(t3_entry);
		if(p->ecoarse < 1024)
        totdistT3 -> Fill(p->ecoarse - p->tcoarse_10b);
        else
        totdistT1 -> Fill((p->ecoarse - p->tcoarse_10b)+1024);  //fill hito for TIGER3
	}

	for (int t4_entry = 0; t4_entry < treeTIGER4->GetEntries(); t4_entry ++){

		treeTIGER4 -> GetEntry(t4_entry);
		if(p->ecoarse < 1024)
        totdistT4 -> Fill(p->ecoarse - p->tcoarse_10b);
        else
        totdistT1 -> Fill((p->ecoarse - p->tcoarse_10b)+1024);  //fill hito for TIGER3
	}

	for (int t5_entry = 0; t5_entry < treeTIGER5->GetEntries(); t5_entry ++){

		treeTIGER5 -> GetEntry(t5_entry);
		if(p->ecoarse < 1024)
        totdistT5 -> Fill(p->ecoarse - p->tcoarse_10b);
        else
        totdistT1 -> Fill((p->ecoarse - p->tcoarse_10b)+1024);  //fill hito for TIGER3
	}

    TCanvas *ctotT0 = new TCanvas("ctotT0","ctotT0");
	gStyle->SetPalette(kRainBow);
	totdistT0->Draw("colz");
    totdistT0->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tot/subRUN3/totTIGER0.pdf");
	TCanvas *ctotT1 = new TCanvas("ctotT1","ctotT1");
	totdistT1->Draw("colz");
    totdistT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tot/subRUN3/totTIGER1.pdf");
	TCanvas *ctotT2 = new TCanvas("ctotT2","ctotT2");
	totdistT2->Draw("colz");
    totdistT2->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tot/subRUN3/totTIGER2.pdf");
	TCanvas *ctotT3 = new TCanvas("ctotT3","ctotT3");
	totdistT3->Draw("colz");
    totdistT3->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tot/subRUN3/totTIGER3.pdf");
	TCanvas *ctotT4 = new TCanvas("ctotT4","ctotT4");
	totdistT4->Draw("colz");
    totdistT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tot/subRUN3/totTIGER4.pdf");
	TCanvas *ctotT5 = new TCanvas("ctotT5","ctotT5");
    totdistT1->SaveAs("../data_folder/TIGER-data_2021/RUN_19_plot/tot/subRUN3/totTIGER5.pdf");
	totdistT5->Draw("colz");
}