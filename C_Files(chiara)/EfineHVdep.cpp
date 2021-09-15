#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TTree.h"
#include "Riostream.h"
#include <time.h>
#include "TStopwatch.h"
#include <TStyle.h>
#include <TCanvas.h>


Double_t Efine_center[] = {632.2, 855.4, 735.9, 704.89 , 733.74} ;
Double_t Efine_right[] = {823.02, 786.46, 824.98, 696.8 , 769.58} ;
Double_t Efine_left[] = {823.02, 855.4, 735.9, 704.89 , 733.74} ;
Double_t  HV_mesh[] = {450, 460, 470, 480, 490};

void EfineHVdep(){

    TGraphErrors *Efine_vs_Vmesh = new TGraphErrors(5, Efine_center, HV_mesh, 0,0);


}