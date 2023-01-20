#include "Riostream.h"
#include "Rtypes.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TClonesArray.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TLegend.h"
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

//IdStrings declaration
string tiger;       
string mode;        
string channel;     
string tac_Id;      
string t_coarse;    
string e_coarse;    
string t_fine;      
string e_fine;     

//variables declaration
Int_t tigerId;       
Int_t ch;            
Int_t tacId;         
Int_t tcoarse;       
Int_t tcoarse_10b;   
Int_t ecoarse;       
Int_t tfine;         
Int_t efine;         

Int_t framenum = 0;          
Int_t prev_framenum =0;      
Int_t framecount = 0;        
 

Double_t timeVal;            
Double_t timeVal_prev = 0;   


Int_t prev_tcoarse=0;      
Int_t tcoarse_frame =0;     

Int_t efinesat =0; 

Int_t pinNum;
Int_t strNum;

void EfineDistEnsamble() {

        ifstream inFile1("../data_folder/Bonn@HISKPlab/RUN_196/SubRUN_0_GEMROC_0_TL.datout.txt");
     
        ifstream inFile2("../data_folder/Bonn@HISKPlab/RUN_198/SubRUN_0_GEMROC_0_TL.datout.txt");
        
        ifstream inFile3("../data_folder/Bonn@HISKPlab/RUN_200/SubRUN_0_GEMROC_0_TL.datout.txt");
       
        ifstream inFile4("../data_folder/Bonn@HISKPlab/RUN_202/SubRUN_0_GEMROC_0_TL.datout.txt");
       
        ifstream inFile5("../data_folder/Bonn@HISKPlab/RUN_204/SubRUN_0_GEMROC_0_TL.datout.txt");
       
        ifstream inFile6("../data_folder/Bonn@HISKPlab/RUN_206/SubRUN_0_GEMROC_0_TL.datout.txt");
        
        ifstream inFile7("../data_folder/Bonn@HISKPlab/RUN_208/SubRUN_0_GEMROC_0_TL.datout.txt");
       
        ifstream inFile8("../data_folder/Bonn@HISKPlab/RUN_210/SubRUN_0_GEMROC_0_TL.datout.txt");
      
        ifstream inFile9("../data_folder/Bonn@HISKPlab/RUN_212/SubRUN_0_GEMROC_0_TL.datout.txt");
        
        ifstream inFile10("../data_folder/Bonn@HISKPlab/RUN_214/SubRUN_0_GEMROC_0_TL.datout.txt");
       
        ifstream inFile11("../data_folder/Bonn@HISKPlab/RUN_216/SubRUN_0_GEMROC_0_TL.datout.txt");
        
        ifstream inFile12("../data_folder/Bonn@HISKPlab/RUN_218/SubRUN_0_GEMROC_0_TL.datout.txt");


    TH1D *efine_dist_T0T1_380 = new TH1D("Efine data distribution (T0T1) Vmesh =380",  Form("Efine distribution Vmesh=380 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_390 = new TH1D("Efine data distribution (T0T1) Vmesh =390",  Form("Efine distribution Vmesh=390 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_400 = new TH1D("Efine data distribution (T0T1) Vmesh =400",  Form("Efine distribution Vmesh=400 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_420 = new TH1D("Efine data distribution (T0T1) Vmesh =420",  Form("Efine distribution Vmesh=420 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_430 = new TH1D("Efine data distribution (T0T1) Vmesh =430",  Form("Efine distribution Vmesh=430 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_440 = new TH1D("Efine data distribution (T0T1) Vmesh =440",  Form("Efine distribution Vmesh=440 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_450 = new TH1D("Efine data distribution (T0T1) Vmesh =450",  Form("Efine distribution Vmesh=450 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_460 = new TH1D("Efine data distribution (T0T1) Vmesh =460",  Form("Efine distribution Vmesh=460 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_470 = new TH1D("Efine data distribution (T0T1) Vmesh =470",  Form("Efine distribution Vmesh=470 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_480 = new TH1D("Efine data distribution (T0T1) Vmesh =480",  Form("Efine distribution Vmesh=480 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_490 = new TH1D("Efine data distribution (T0T1) Vmesh =490",  Form("Efine distribution Vmesh=490 (T0 T1);Efine[digits]"), 120, 0, 1024);
    TH1D *efine_dist_T0T1_500 = new TH1D("Efine data distribution (T2T3) Vmesh =500",  Form("Efine distribution Vmesh=500 (T2 T3);Efine[digits]"), 120, 0, 1024);

    //validity check
   if (inFile1.fail()) {
        cerr << "errore nell'apertura del file, uscita dal programma" << endl;
        abort();
   }

//---------------------------------//
// ---------- file loop -----------//
//---------------------------------//
//1 FILE
    for (Int_t ibit = 0; !inFile1.eof(); ibit++) {

        //load SubRun0 data 
        inFile1 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile1.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }
    
// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos
                efine_dist_T0T1_380->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                //filling histos
                efine_dist_T0T1_380->Fill(efine);
                
        } 
        
        prev_tcoarse  = tcoarse;
        timeVal_prev  = timeVal;
        prev_framenum = framenum;
    }
//2 file
    for (Int_t ibit = 0; !inFile2.eof(); ibit++) {

        //load SubRun0 data 
        inFile2 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile2.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_390->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_390->Fill(efine);
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;
    }
//3 FILE 
    for (Int_t ibit = 0; !inFile3.eof(); ibit++) {

        //load SubRun0 data 
        inFile3 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile3.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_400->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_400->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }
//4 FILE
    for (Int_t ibit = 0; !inFile4.eof(); ibit++) {

        //load SubRun0 data 
        inFile4 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile4.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_420->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_420->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }
//5 FILE
    for (Int_t ibit = 0; !inFile5.eof(); ibit++) {

        //load SubRun0 data 
        inFile5 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile5.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_430->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_430->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }
//6 FILE
    for (Int_t ibit = 0; !inFile6.eof(); ibit++) {

        //load SubRun0 data 
        inFile6 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile6.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_440->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_440->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }
//7 FILE
    for (Int_t ibit = 0; !inFile7.eof(); ibit++) {

        //load SubRun0 data 
        inFile7 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile7.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_450->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_450->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }
//8 FILE
    for (Int_t ibit = 0; !inFile8.eof(); ibit++) {

        //load SubRun0 data 
        inFile8 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile8.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_460->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_460->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }
//9 FILE
    for (Int_t ibit = 0; !inFile9.eof(); ibit++) {

        //load SubRun0 data 
        inFile9 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile9.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_470->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_470->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }    
//10 FILE
    for (Int_t ibit = 0; !inFile10.eof(); ibit++) {

        //load SubRun0 data 
        inFile10 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile10.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_480->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_480->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }
//11 FILE
    for (Int_t ibit = 0; !inFile11.eof(); ibit++) {

        //load SubRun0 data 
        inFile11 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile11.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_490->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_490->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }
//12 FILE
    for (Int_t ibit = 0; !inFile12.eof(); ibit++) {

        //load SubRun0 data 
        inFile12 >> tiger >> tigerId >> mode >> channel  >> std::hex>> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine; 

//debug
        //cout << " SubRUN0 dat: "<< tiger <<  tigerId << " " << mode <<" " << channel << ch <<" " <<
        //tac_Id << tacId <<" " << t_coarse << tcoarse <<" " << e_coarse << ecoarse <<" " <<
        //t_fine << tfine <<" " << e_fine << efine << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode == "HB:"){

            framecount = ch;
            inFile12.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framecount * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //MAPPING PROCEDURE
            switch (ch){
			
	            case(0)  : pinNum = 77;  strNum = 111; break;
	            case(1)  : pinNum = 122; strNum = 61; break;
	            case(2)  : pinNum = 73;  strNum = 109 ; break;
                case(3)  : pinNum = 74;  strNum = 37; break;
                case(4)  : pinNum = 134; strNum = 68; break;
                case(5)  : pinNum = 62;  strNum = 31 ; break;
	            case(6)  : pinNum = 130; strNum = 65; break;
                case(7)  : pinNum = 72;  strNum = 36; break;
                case(8)  : pinNum = 144; strNum = 72; break;
                case(9)  : pinNum = 66;  strNum = 33; break;
	            case(10) : pinNum = 138; strNum = 69; break;
                case(11) : pinNum = 98;  strNum = 49; break;
                case(12) : pinNum = 132; strNum = 66; break;
                case(13) : pinNum = 70;  strNum = 35; break;
                case(14) : pinNum = 89;  strNum = 117; break;
                case(15) : pinNum = 114; strNum = 57; break;
                case(16) : pinNum = 81;  strNum = 113;break;
                case(17) : pinNum = 94;  strNum = 47; break;
	            case(18) : pinNum = 83;  strNum = 114;break;
                case(19) : pinNum = 112; strNum = 56; break;
                case(20) : pinNum = 67;  strNum = 106; break;
                case(21) : pinNum = 142; strNum = 71; break;
                case(22) : pinNum = 71;  strNum = 108; break;
                case(23) : pinNum = 136; strNum = 68; break;
                case(24) : pinNum = 69;  strNum = 107; break;
                case(25) : pinNum = 106; strNum = 53; break;
                case(26) : pinNum = 63;  strNum = 104; break;
                case(27) : pinNum = 102; strNum = 51; break;
                case(28) : pinNum = 65;  strNum = 105; break;
                case(29) : pinNum = 120; strNum = 60; break;
                case(30) : pinNum = 87;  strNum = 116;break;
                case(31) : pinNum = 118; strNum = 59; break;
                case(32) : pinNum = 76;  strNum = 38; break;
                case(33) : pinNum = 128; strNum = 64; break;
                case(34) : pinNum = 78;  strNum = 39; break;
                case(35) : pinNum = 124; strNum = 62; break;
	            case(36) : pinNum = 79;  strNum = 112; break;
	            case(37) : pinNum = 96;  strNum = 48;  break;
	            case(38) : pinNum = 85;  strNum = 115; break;
                case(39) : pinNum = 110; strNum = 55; break;    
                case(40) : pinNum = 135; strNum = 120; break;     
                case(41) : pinNum = 126; strNum = 63; break;      
                case(42) : pinNum = 64;  strNum = 32;break;    
                case(43) : pinNum = 86;  strNum = 43; break;
                case(44) : pinNum = 82;  strNum = 41; break;
                case(45) : pinNum = 141; strNum = 123; break;
                case(46) : pinNum = 80;  strNum = 40; break;
                case(47) : pinNum = 140; strNum = 70; break;
                case(48) : pinNum = 75;  strNum = 110; break;
                case(49) : pinNum = 116; strNum = 58; break;
                case(50) : pinNum = 139; strNum = 122; break;
                case(51) : pinNum = 100; strNum = 50; break;
                case(52) : pinNum = 137; strNum = 121; break;
                case(53) : pinNum = 92;  strNum = 46; break;
                case(54) : pinNum = 90;  strNum = 45; break;
                case(55) : pinNum = 108; strNum = 54; break;
                case(56) : pinNum = 84;  strNum = 42; break;
                case(57) : pinNum = 143; strNum = 124; break;
                case(58) : pinNum = 68;  strNum = 34; break;
                case(59) : pinNum = 88;  strNum = 44; break;
                case(60) : pinNum = 104; strNum = 52; break;
                case(61) : pinNum = 133; strNum = 119; break;
	            case(62) : break;
                case(63) : break;

            }
            
			//filling histos

                efine_dist_T0T1_500->Fill(efine);
                //}

        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
			
            //MAPPING procedure
            switch (ch){
            
                case(0) : pinNum =	21	; strNum= 83; break;            
                case(1) : pinNum =	28	; strNum= 14; break;            
                case(2) : pinNum =	42	; strNum= 21; break;            
                case(3) : pinNum =	1	; strNum= 73; break;            
                case(4) : pinNum =	7	; strNum= 76; break;            
                case(5) : pinNum =	52	; strNum= 26; break;            
                case(6) : pinNum =	18	; strNum= 9; break;           
                case(7) : pinNum =	26	; strNum= 13 ; break;       
                case(8) : pinNum =	48	; strNum= 24; break;            
                case(9) : pinNum =	20	; strNum= 10 ; break;       
                case(10): pinNum =	50	; strNum= 25 ; break;       
                case(11): pinNum =	3	; strNum= 74 ; break;       
                case(12): pinNum =	9	; strNum= 77 ; break;       
                case(13): pinNum =	32	; strNum= 16 ; break;       
                case(14): pinNum =	17	; strNum= 81 ; break;       
                case(15): pinNum =	15	; strNum= 80 ; break;       
                case(16): pinNum =	33	; strNum= 89 ; break;       
                case(17): pinNum =	44	; strNum= 22 ; break;       
                case(18): pinNum =	56	; strNum= 28 ; break;       
                case(19): pinNum =	13	; strNum= 79 ; break;       
                case(20): pinNum =	31	; strNum= 88 ; break;       
                case(21): pinNum =	46	; strNum= 23 ; break;       
                case(22): pinNum =	5	; strNum= 75 ; break;       
                case(23): pinNum =	11	; strNum= 78 ; break;       
                case(24): pinNum =	54	; strNum= 27 ; break;       
                case(25): pinNum =	22	; strNum= 11 ; break;       
                case(26): pinNum =	23	; strNum= 84 ; break;       
                case(27): pinNum =	30	; strNum= 15 ; break;       
                case(28): pinNum =	35	; strNum= 90 ; break;       
                case(29): pinNum =	24	; strNum= 12 ; break;       
                case(30): pinNum =	58	; strNum= 29 ; break;       
                case(31): pinNum =	34	; strNum= 17 ; break;       
                case(32): pinNum =	60	; strNum= 30 ; break;       
                case(33): pinNum =	12	; strNum= 6  ; break;      
                case(34): pinNum =	59	; strNum= 102; break;        
                case(35): pinNum =	36	; strNum= 18 ; break;       
                case(36): pinNum =	57	; strNum= 101; break;        
                case(37): pinNum =	16	; strNum= 8  ; break;      
                case(38): pinNum =	61	; strNum= 103; break;        
                case(39): pinNum =	14	; strNum= 7  ; break;      
                case(40): pinNum =	49	; strNum= 97 ; break;       
                case(41): pinNum =	8	; strNum= 4  ; break;      
                case(42): pinNum =	55	; strNum= 100; break;        
                case(43): pinNum =	10	; strNum= 5  ; break;      
                case(44): pinNum =	53	; strNum= 99 ; break;       
                case(45): pinNum =	2	; strNum= 1  ; break;      
                case(46): pinNum =	47	; strNum= 96 ; break;       
                case(47): pinNum =	4	; strNum= 2  ; break;      
                case(48): pinNum =	51	; strNum= 98 ; break;       
                case(49): pinNum =	25	; strNum= 85 ; break;       
                case(50): pinNum =	41	; strNum= 93 ; break;       
                case(51): pinNum =	29	; strNum= 87 ; break;       
                case(52): pinNum =	43	; strNum= 94 ; break;       
                case(53): pinNum =	40	; strNum= 20 ; break;       
                case(54): pinNum =	6	; strNum= 3  ; break;      
                case(55): pinNum =	27	; strNum= 86 ; break;       
                case(56): pinNum =	39	; strNum= 92 ; break;       
                case(57): pinNum =	38	; strNum= 19 ; break;       
                case(58): pinNum =	45	; strNum= 95 ; break;       
                case(59): pinNum =	37	; strNum= 91 ; break;       
                case(60): pinNum =	19	; strNum= 82 ; break;       
                case(61): pinNum =	91	; strNum= 118; break;        
                case(62): break;	
                case(63): break;	

            }

                efine_dist_T0T1_500->Fill(efine);
                
        }

    prev_tcoarse  = tcoarse;
    timeVal_prev  = timeVal;
    prev_framenum = framenum;

    }
//debug
    //cout <<"prev_tcoarse_BON : "<<prev_tcoarse << endl;
    //cout <<"tcoarse_BON : " << tcoarse << endl;
    //cout <<"prev_tVal_BON : "<< timeVal_prev <<endl;
    //cout <<"tVal_BON : " << timeVal << endl;
    //cout <<"prev_framenum : "<<prev_framenum << endl;
    //cout <<"framenum : "<<framenum << endl;
    //cout<<endl;
    

//functions for plot

    initFigTemplate();
//couloring histos
    efine_dist_T0T1_380->SetLineColor(kSpring);
    efine_dist_T0T1_390->SetLineColor(kYellow+2);
    efine_dist_T0T1_400->SetLineColor(kOrange);
    efine_dist_T0T1_420->SetLineColor(kRed+2);
    efine_dist_T0T1_430->SetLineColor(kPink);
    efine_dist_T0T1_440->SetLineColor(kMagenta+2);
    efine_dist_T0T1_450->SetLineColor(kViolet);
    efine_dist_T0T1_460->SetLineColor(kBlue+2);
    efine_dist_T0T1_470->SetLineColor(kAzure);
    efine_dist_T0T1_480->SetLineColor(kCyan+2);
    efine_dist_T0T1_490->SetLineColor(kTeal);
    efine_dist_T0T1_500->SetLineColor(kGreen+2);

//E fine data time distribution for each tiger

    TCanvas *hstack = new TCanvas("stucked histo","stucked histo");

        THStack *hs = new THStack("hs", "Efine distribution;Efine[digits];counts");
        hs->Add(efine_dist_T0T1_380);
        hs->Add(efine_dist_T0T1_390);
        hs->Add(efine_dist_T0T1_400);
        hs->Add(efine_dist_T0T1_420);
        hs->Add(efine_dist_T0T1_430);
        hs->Add(efine_dist_T0T1_440);
        hs->Add(efine_dist_T0T1_450);
        hs->Add(efine_dist_T0T1_460);
        hs->Add(efine_dist_T0T1_470);
        hs->Add(efine_dist_T0T1_480);
        hs->Add(efine_dist_T0T1_490);
        hs->Add(efine_dist_T0T1_500);

        hstack->cd();
        hs->Draw();
    
    auto legend = new TLegend();
    legend->AddEntry(efine_dist_T0T1_380,"Vmesh=-380 V","l");
    legend->AddEntry(efine_dist_T0T1_390,"Vmesh=-390 V","l");
    legend->AddEntry(efine_dist_T0T1_400,"Vmesh=-400 V","l");
    legend->AddEntry(efine_dist_T0T1_420,"Vmesh=-420 V","l");
    legend->AddEntry(efine_dist_T0T1_430,"Vmesh=-430 V","l");
    legend->AddEntry(efine_dist_T0T1_440,"Vmesh=-440 V","l");
    legend->AddEntry(efine_dist_T0T1_450,"Vmesh=-450 V","l");
    legend->AddEntry(efine_dist_T0T1_460,"Vmesh=-460 V","l");
    legend->AddEntry(efine_dist_T0T1_470,"Vmesh=-470 V","l");
    legend->AddEntry(efine_dist_T0T1_480,"Vmesh=-480 V","l");
    legend->AddEntry(efine_dist_T0T1_490,"Vmesh=-490 V","l");
    legend->AddEntry(efine_dist_T0T1_500,"Vmesh=-500 V","l");
    legend->Draw();
}