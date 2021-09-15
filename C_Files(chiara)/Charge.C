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

void Charge() {

    TFile *f = new TFile("SubRUN_10_GEMROC_7_TL.root");

    TTree *treeTIGER0 = (TTree *)f ->Get("treeTIGER0");
	TTree *treeTIGER1 = (TTree *)f ->Get("treeTIGER1");
	TTree *treeTIGER6 = (TTree *)f ->Get("treeTIGER6");
	TTree *treeTIGER7 = (TTree *)f ->Get("treeTIGER7");

    treeTIGER0 ->GetBranch("packageTIGER0")->SetAddress(&p); //getting branch and contents for TIGER 0  
	treeTIGER1 ->GetBranch("packageTIGER1")->SetAddress(&p); //getting branch and contents for TIGER 1
    treeTIGER6 ->GetBranch("packageTIGER6")->SetAddress(&p); //getting branch and contents for TIGER 6  
	treeTIGER7 ->GetBranch("packageTIGER7")->SetAddress(&p); //getting branch and contents for TIGER 7

//histograms
    TH1D *h_Efine_T0 = new TH1D ("h_Efine_T0", Form("Charge TIGER0; Efine[bin]"), 1200, 0, 1200);  //TODO aggiustare il binning
	TH1D *h_Efine_T1 = new TH1D ("h_Efine_T1", Form("Charge TIGER1; Efine[bin]"), 1200, 0, 1200);
    TH1D *h_Efine_T6 = new TH1D ("h_Efine_T6", Form("Charge TIGER6; Efine[bin]"), 1200, 0, 1200);
	TH1D *h_Efine_T7 = new TH1D ("h_Efine_T7", Form("Charge TIGER7; Efine[bin]"), 1200, 0, 1200);

    TH1D *h_Charge_T0 = new TH1D ("h_Charge_T0", Form("Charge TIGER0; charge = Ecoarse-Tcoarse_10b[bin]"), 1200, 0, 1200);  //TODO aggiustare il binning
	TH1D *h_Charge_T1 = new TH1D ("h_Charge_T1", Form("Charge TIGER1; charge = Ecoarse-Tcoarse_10b[bin]"), 1200, 0, 1200);
    TH1D *h_Charge_T6 = new TH1D ("h_Charge_T6", Form("Charge TIGER6; charge = Ecoarse-Tcoarse_10b[bin]"), 1200, 0, 1200);
	TH1D *h_Charge_T7 = new TH1D ("h_Charge_T7", Form("Charge TIGER7; charge = Ecoarse-Tcoarse_10b[bin]"), 1200, 0, 1200);

    int charge_T0, charge_T1, charge_T6, charge_T7;

//S&H mode --> charge = Efine
    for( int i = 0; i < treeTIGER0 -> GetEntries(); i++){

        treeTIGER0 -> GetEntry(i);
        h_Efine_T0 -> Fill(p->efine);
    }
    for( int i = 0; i < treeTIGER1 -> GetEntries(); i++){

        treeTIGER1 -> GetEntry(i);
        h_Efine_T1 -> Fill(p->efine);
    }
    for( int i = 0; i < treeTIGER6 -> GetEntries(); i++){

        treeTIGER6 -> GetEntry(i);
        h_Efine_T6 -> Fill(p->efine);
    }
    for( int i = 0; i < treeTIGER7 -> GetEntries(); i++){

        treeTIGER7 -> GetEntry(i);
        h_Efine_T7 -> Fill(p->efine);
    }

//ToT mode ---> charge = Ecoarse - Tcoarse
    for (int i = 0; i<treeTIGER0-> GetEntries(); i++){
		
		treeTIGER0 -> GetEntry(i);
        
        if(p->tcoarse_10b < p->ecoarse){             //check for tcoarse counter roll over
		charge_T0 = p->ecoarse - p->tcoarse_10b;
        //cout << "charge: "<< charge_T0<< endl;     //debug
        }
        else{
        charge_T0 = (p->ecoarse + 1024) - p->tcoarse_10b;
        //cout << "charge: "<< charge_T0<< endl;     //debug
        }
        h_Charge_T0 -> Fill(charge_T0);

	}
	
	for (int i = 0; i < treeTIGER1->GetEntries(); i++){
		
		treeTIGER1 -> GetEntry(i);
        
		if(p->tcoarse_10b < p->ecoarse)              //check for tcoarse counter roll over
		charge_T1 = p->ecoarse - p->tcoarse_10b;
        else
        charge_T1 = (p->ecoarse + 1024) - p->tcoarse_10b; 
        //cout << "charge: "<< charge_T1<< endl;     //debug 

        h_Charge_T1 -> Fill(charge_T1);

	}
    for (int i = 0; i<treeTIGER6-> GetEntries(); i++){
		
		treeTIGER6 -> GetEntry(i);
        if(p->tcoarse_10b < p->ecoarse){             //check for tcoarse counter roll over
		charge_T6 = p->ecoarse - p->tcoarse_10b;
        //cout << "charge: "<< charge_T0<< endl;     //debug 
        }
        else{
        charge_T6 = (p->ecoarse + 1024) - p->tcoarse_10b;
        //cout << "charge: "<< charge_T0<< endl;     //debug 
        }
        h_Charge_T6 -> Fill(charge_T6);

	}
	
	for (int i = 0; i < treeTIGER7->GetEntries(); i++){
		
		treeTIGER7 -> GetEntry(i);
		if(p->tcoarse_10b < p->ecoarse)              //check for tcoarse counter roll over
		charge_T7 = p->ecoarse - p->tcoarse_10b;
        else
        charge_T7 = (p->ecoarse + 1024) - p->tcoarse_10b; 
        //cout << "charge: "<< charge_T1<< endl;     //debug 

        h_Charge_T7 -> Fill(charge_T7);

	}

    initFigTemplate();
    TCanvas *cCharge_SHmode = new TCanvas("cCharge_SHmode","cCharge_SHmode");
    cCharge_SHmode -> Divide(2,2);
    gStyle->SetPalette(kRainBow);
    cCharge_SHmode->cd(1);
    h_Efine_T0 ->Draw();
    cCharge_SHmode->cd(2);
    h_Efine_T1->Draw();
    cCharge_SHmode->cd(3);
    h_Efine_T6->Draw();
    cCharge_SHmode->cd(4);
    h_Efine_T7->Draw();

    

	TCanvas *cCharge_ToTmode = new TCanvas("cCharge_ToTmode","cCharge_ToTmode");
	cCharge_ToTmode -> Divide(2,2);
    cCharge_ToTmode->cd(1);
    h_Charge_T0->Draw();
    cCharge_ToTmode->cd(2);
    h_Charge_T1->Draw();
    cCharge_ToTmode->cd(3);
    h_Charge_T6->Draw();
    cCharge_ToTmode->cd(4);
    h_Charge_T7->Draw();
	


}