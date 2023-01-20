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
//#include <bits/stdc++.h>

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

int frameNumber = 0;
package *p = new package;

void readData() {
  
   ifstream inFile("../../../test.txt");
 
   //validity check
   if (inFile.fail()) {
     cerr << "errore nell'apertura del file, uscita dal programma" << endl;
     abort();
   }

   TFile *outputFile = new TFile("../../../test.root", "RECREATE"); 

   TTree *treeTIGER0 = new TTree("treeTIGER0", "treeTIGER0"); //TTree TIGER_0
   TTree *treeTIGER1 = new TTree("treeTIGER1", "treeTIGER1"); //TTree TIGER_1
   TTree *treeTIGER2 = new TTree("treeTIGER2", "treeTIGER2"); //TTree TIGER_2
   TTree *treeTIGER3 = new TTree("treeTIGER3", "treeTIGER3"); //TTree TIGER_3
   TTree *treeTIGER4 = new TTree("treeTIGER4", "treeTIGER4"); //TTree TIGER_4
   TTree *treeTIGER5 = new TTree("treeTIGER5", "treeTIGER5"); //TTree TIGER_5
   
   
   treeTIGER0->Branch("packageTIGER0", &p);
   treeTIGER1->Branch("packageTIGER1", &p);
   treeTIGER2->Branch("packageTIGER2", &p);
   treeTIGER3->Branch("packageTIGER3", &p);
   treeTIGER4->Branch("packageTIGER4", &p);
   treeTIGER5->Branch("packageTIGER5", &p);
 
   string tiger;
   string mode;
   string channel;
   string tac_Id;
   string t_coarse;
   string e_coarse;
   string t_fine;
   string e_fine;

  unsigned long int tcoarse_10b;

  for (Int_t ibit = 0; !inFile.eof(); ibit++) {
      
    //load package
     inFile >> tiger >> p->tigerId >> mode >> channel >> std::hex >> p->ch >>
     tac_Id >> p->tacId >> t_coarse >> std::hex >> p->tcoarse >> e_coarse >> std::hex >> p->ecoarse >>
     t_fine >> std::hex >> p->tfine >> e_fine >> std::hex >> p->efine;
///*debug 
    //cout << tiger << " ";
    //cout << p->tigerId << " ";
    //cout << mode << " ";
    //cout << channel << " ";
    //cout << p->ch << " ";
    //cout << tac_Id << " ";
    //cout << p->tacId << " ";
    //cout << t_coarse << " ";
    //cout << p->tcoarse << " ";
    //cout << e_coarse << " ";
    //cout << p->ecoarse << " ";
    //cout << t_fine << " ";
    //cout << p->tfine << " ";
    //cout << e_fine << " ";
    //cout << p->efine << " " << endl;
//debug */

    //taking only 10LSB of tcoarse for analysis
    
    //bitset<10> tcoarse_10b_bin(p->tcoarse);
    //p->tcoarse_10b = tcoarse_10b_bin.to_ulong();
    //debug
    //cout << "tcoarse 10 bit: " << p->tcoarse_10b << endl;
    
    if (mode == "HB:"){
       
       printf("---------------------------------------------->framecount: %d \n", frameNumber); // framecount identification
       inFile.ignore(256, '\n');
       frameNumber ++;
    } 
    if (p->tigerId == 0)
    treeTIGER0->Fill();
    if (p->tigerId == 1)
    treeTIGER1->Fill();
    if (p->tigerId == 2)
    treeTIGER2->Fill();
    if (p->tigerId == 3)
    treeTIGER3->Fill();  
    if (p->tigerId == 4)
    treeTIGER4->Fill();  
    if (p->tigerId == 5)
    treeTIGER5->Fill();    
    
  }

  printf("End of file reached \n");
  outputFile->Write();
}

