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

//data 
Int_t tigerId;
Int_t ch;
Int_t tacId;
Int_t tcoarse;
Int_t tcoarse_10b;
Int_t ecoarse;
Int_t tfine;
Int_t efine;
//timing reconstruction variables
Int_t framenum = 0;
Int_t prev_framenum =0;
LongDouble_t timeVal;
LongDouble_t timeVal_prev = 0;
Int_t prev_tcoarse=0;
Int_t tcoarse_rollover=0;
Int_t tcoarse_frame =0;
//mapping variables
Int_t pinNum;
Int_t strNum;

void data_analysis_prova() {
  
   ifstream inFile("../data_folder/RUN_31/SubRUN_0_GEMROC_0_TL.datout.txt");

   TH1D *data_dist_T0 = new TH1D("data time profile T0", Form("data time profile T0;Time[s];Counts"), 120,0,12);
   TH1D *data_dist_T1 = new TH1D("data time profile T1", Form("data time profile T1;Time[s];Counts"), 120,0,12);
   TH1D *data_dist_T2 = new TH1D("data time profile T2", Form("data time profile T2;Time[s];Counts"), 120,0,12);
   TH1D *data_dist_T3 = new TH1D("data time profile T3", Form("data time profile T3;Time[s];Counts"), 120,0,12);
   TH1D *data_dist_T4 = new TH1D("data time profile T4", Form("data time profile T4;Time[s];Counts"), 120,0,12);
   TH1D *data_dist_T5 = new TH1D("data time profile T5", Form("data time profile T5;Time[s];Counts"), 120,0,12);

   TH1D *data_dist_T0T1 = new TH1D("data time profile T0", Form("data time profile exTP (T0T1);Time[s];Counts"), 120,0,12);
   TH1D *data_dist_T2T3 = new TH1D("data time profile T1", Form("data time profile MM1 (T2T3);Time[s];Counts"), 120,0,12);
   TH1D *data_dist_T4T5 = new TH1D("data time profile T2", Form("data time profile MM2 (T4T5);Time[s];Counts"), 120,0,12);

   TH1D *beam_profile_T0T1 = new TH1D("beam profile T0", Form("beam profile exTP (T0T1);strNum;Counts"),124,-0.5,123.5);
   TH1D *beam_profile_T2T3 = new TH1D("beam profile T1", Form("beam profile MM1 (T2T3);strNum;Counts"),124,-0.5,123.5);
   TH1D *beam_profile_T4T5 = new TH1D("beam profile T2", Form("beam profile MM2 (T4T5);strNum;Counts"),124,-0.5,123.5);
   
   TH1D *ch_32_T1_efine = new TH1D("ch_41_t0_efine", Form("ch 41 TIGER:0 Efine BEAM ON; Efine[bin]; Counts"),1024,0,1024);
   TH1D *ch_56_T1_efine = new TH1D("ch_41_t0_efine", Form("ch 41 TIGER:0 Efine BEAM OFF; Efine[bin]; Counts"),1024,0,1024);
   TH1D *ch_54_T1_efine = new TH1D("ch_41_t0_efine", Form("ch 41 TIGER:0 Efine BEAM OFF; Efine[bin]; Counts"),1024,0,1024);

   TH2D *chn_time_dist_T0T1 = new TH2D("channels data time distribution exTP (T0T1)",  Form("channel data time distribution exTP (T0 T1);strip;Time[s]"), 124, -0.5, 123.5, 120,0,12);
   TH2D *chn_time_dist_T2T3 = new TH2D("channels data time distribution MM1 (T2T3)",  Form("channel data time distribution MM1 (T2 T3);strip;Time[s]"), 124, -0.5, 123.5, 120,0,12);
   TH2D *chn_time_dist_T4T5 = new TH2D("channels data time distribution MM2 (T4T5)",  Form("channel data time distribution MM2 (T4 T5);strip;Time[s]"), 124, -0.5, 123.5, 120,0,12);
   
   TH2D *chn_time_dist_after_selection_T0T1 = new TH2D("channels data time after selection distribution exTP (T0T1)",  Form("channel data time after selection distribution exTP (T0 T1);strip;Time[s]"), 124, -0.5, 123.5, 120,0,12);
   TH2D *chn_time_dist_after_selection_T2T3 = new TH2D("channels data time after selection distribution MM1 (T2T3)",  Form("channel data time after selection distribution MM1 (T2 T3);strip;Time[s]"), 124, -0.5, 123.5, 120,0,12);
   TH2D *chn_time_dist_after_selection_T4T5 = new TH2D("channels data time after selection distribution MM1 (T4T5)",  Form("channel data time after selection distribution MM2 (T4 T5);strip;Time[s]"), 124, -0.5, 123.5, 120,0,12);
   
//validity check
   if (inFile.fail()) {
        cerr << "errore nell'apertura del file, uscita dal programma" << endl;
        abort();
   }

//loop 
   for (Int_t ibit = 0; !inFile.eof() ; ibit++) {

        //load data
        inFile >> tiger >> tigerId >> mode >> channel >> std::hex >> ch >>
        tac_Id >> tacId >> t_coarse >> std::hex >> tcoarse >> e_coarse >> std::hex >> ecoarse >>
        t_fine >> std::hex >> tfine >> e_fine >> std::hex >> efine;

    ///*debug 
        //cout << tiger << " ";
        //cout << tigerId << " ";
        //cout << mode << " ";
        //cout << channel << " ";
        //cout << ch << " ";
        //cout << tac_Id << " ";
        //cout << tacId << " ";
        //cout << t_coarse << " ";
        //cout << tcoarse << " ";
        //cout << e_coarse << " ";
        //cout << ecoarse << " ";
        //cout << t_fine << " ";
        //cout << tfine << " ";
        //cout << e_fine << " ";
        //cout << efine << " " << endl;
    //debug */

        if (mode == "HB:"){
            
            inFile.ignore(256, '\n');
            tcoarse = prev_tcoarse;          
//debug
            //cout << "---------------- frame number ---------> " << framenum/3 << endl; // framecount identification
            framenum ++;
        }

//taking account of the tcoarse rolling over in the middle of frame        
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framenum/3 * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

//Allignement of tcoarse and framecount       
        if(timeVal - timeVal_prev > 0.0001){
            
            tcoarse_frame = tcoarse;
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE 
        timeVal = framenum/3 * 204.8e-6 + (tcoarse-tcoarse_frame) * 6.25e-9; //s

//debug
        //cout <<"prev_tcoarse : "<<prev_tcoarse << endl;
        //cout <<"tcoarse : " << tcoarse << endl;
        //cout <<"prev_tVal : "<< timeVal_prev <<endl;
        //cout <<"tVal : " << timeVal << endl;
        //cout<<endl;


// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId == 0 && mode == "EW:"){

            //filling TIGER histo
            data_dist_T0 -> Fill(timeVal);

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
             //filling MMs histos
            data_dist_T0T1 -> Fill(timeVal);
            chn_time_dist_T0T1 ->Fill(strNum, timeVal);
            //event selection
            if(timeVal< timeVal_prev + 50e-9) 
                chn_time_dist_after_selection_T0T1->Fill(strNum, timeVal);
                beam_profile_T0T1 ->Fill(strNum);
        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId == 1 && mode == "EW:") {
            
            // filling TIGER hist
            data_dist_T1 -> Fill(timeVal);
            if(ch == 32){
                ch_32_T1_efine -> Fill(efine);
            }
            if(ch == 56){
                ch_56_T1_efine -> Fill(efine);
            }
            if(ch == 54){
                ch_54_T1_efine -> Fill(efine);
            }

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

            data_dist_T0T1 -> Fill(timeVal);
            chn_time_dist_T0T1 ->Fill(strNum, timeVal);
            //event selection
            if(timeVal< timeVal_prev + 50e-9) 
                chn_time_dist_after_selection_T0T1->Fill(strNum, timeVal);
                beam_profile_T0T1 -> Fill(strNum);
        }
// ------------------------ TIGER 2 ------------------------------ //
        if (tigerId == 2 && mode == "EW:"){

            //filling tiger hist
            data_dist_T2 -> Fill(timeVal);

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

            data_dist_T2T3 -> Fill(timeVal);
            chn_time_dist_T2T3 ->Fill(strNum, timeVal);
            //event selection
            if(timeVal< timeVal_prev + 50e-9) 
                chn_time_dist_after_selection_T2T3->Fill(strNum, timeVal);
                beam_profile_T2T3 ->Fill(strNum);
        }
// ------------------------ TIGER 3 ------------------------------ //
        if (tigerId == 3 && mode == "EW:"){
            
            //filling tiger hist
            data_dist_T3 -> Fill(timeVal);

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

            //filling MMs hist
            data_dist_T2T3 -> Fill(timeVal);
            chn_time_dist_T2T3 ->Fill(strNum, timeVal);
            //event selection
            if(timeVal< timeVal_prev + 50e-9) 
                chn_time_dist_after_selection_T2T3->Fill(strNum, timeVal);
                beam_profile_T2T3->Fill(strNum);

        }
// ------------------------ TIGER 4 ------------------------------ //          
        if (tigerId == 4 && mode == "EW:"){

            //filling tiger hist 
            data_dist_T4 -> Fill(timeVal);

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

            //filling MMs hist
            data_dist_T4T5 -> Fill(timeVal);
            chn_time_dist_T4T5 ->Fill(strNum, timeVal);
            //event selection
            if(timeVal< timeVal_prev + 50e-9) 
                chn_time_dist_after_selection_T4T5->Fill(strNum, timeVal);
                beam_profile_T4T5->Fill(strNum);
        } 
// ------------------------ TIGER 5 ------------------------------ //
        if (tigerId == 5 && mode == "EW:"){

            //filling tiger hist 
            data_dist_T5 -> Fill(timeVal);

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

            //filling MMs hist
            data_dist_T4T5 -> Fill(timeVal);
            chn_time_dist_T4T5 ->Fill(strNum, timeVal);
             //event selection
            if(timeVal< timeVal_prev + 50e-9) 
                chn_time_dist_after_selection_T4T5->Fill(strNum, timeVal);
                beam_profile_T4T5->Fill(strNum);
        }

        prev_tcoarse = tcoarse;
        timeVal_prev = timeVal;
        prev_framenum = framenum;

   }

//functions for plot

    initFigTemplate();
    
//canvas 
//beam profile
    TCanvas *cbeam_profile = new TCanvas("cbeam_profile","cbeam_profile");
    cbeam_profile-> Divide(1,3,0.01,0.01);

    cbeam_profile->cd(1);
	  beam_profile_T0T1->Draw();
    cbeam_profile->cd(2);
	  beam_profile_T2T3->Draw();
    cbeam_profile->cd(3);
	  beam_profile_T4T5->Draw();

//   cbeam_profile->SaveAs("./plot/RUN_33/subRUN1/beam_profile.pdf");

//Efine active strips
TCanvas *cEfine_30_str = new TCanvas("cEfine_30str","cEfine_30str");
      ch_32_T1_efine->SetLineColor(kBlue);
	  ch_32_T1_efine->Draw("same");
TCanvas *cEfine_92_str = new TCanvas("cEfine_92str","cEfine_92str");
      ch_54_T1_efine->SetLineColor(kRed);
      ch_54_T1_efine->Draw("same");
TCanvas *cEfine_94_str = new TCanvas("cEfine_694str","cEfine_694str");
      ch_56_T1_efine->SetLineColor(kGreen);
      ch_56_T1_efine->Draw("same");

//data time distribution for each tiger
    TCanvas *cdata_time_dist = new TCanvas("cdata_time_dist","cdata_time_dist");
    cdata_time_dist-> Divide(3,2,0.01,0.01);

    cdata_time_dist->cd(1);
	data_dist_T0->Draw();
    cdata_time_dist->cd(2);
	data_dist_T1->Draw();
    cdata_time_dist->cd(3);
	data_dist_T2->Draw();
    cdata_time_dist->cd(4);
	data_dist_T3->Draw();
    cdata_time_dist->cd(5);
	data_dist_T4->Draw();
    cdata_time_dist->cd(6);
	data_dist_T5->Draw();

//    cdata_time_dist->SaveAs("./plot/RUN_33/subRUN1/data_time_dist_tigers_bin0.1s.pdf");
/*
//data time distribution for MMs
    TCanvas *cdata_time_dist_MicroMegas = new TCanvas("cdata_time_dist_MicroMegas","cdata_time_dist_MicroMegas");
    cdata_time_dist_MicroMegas-> Divide(1,3,0.01,0.01);

    cdata_time_dist_MicroMegas->cd(1);
	data_dist_T0T1->Draw();
    cdata_time_dist_MicroMegas->cd(2);
	data_dist_T2T3->Draw();
    cdata_time_dist_MicroMegas->cd(3);
	data_dist_T4T5->Draw();

//    cdata_time_dist_MicroMegas->SaveAs("./plot/RUN_33/subRUN1/data_time_dist_micromegas_bin0.1s.pdf");

//data time distribution for MMs with channels differentiation
    TCanvas *cCH_time_dist = new TCanvas("cCH_time_dist","cCH_time_dist");
    gStyle->SetPalette(kRainBow);
    cCH_time_dist-> Divide(1,3,0.01,0.01);

    cCH_time_dist->cd(1);
 	  chn_time_dist_T0T1->Draw("colz");
    cCH_time_dist->cd(2);
	  chn_time_dist_T2T3->Draw("colz");
    cCH_time_dist->cd(3);
	  chn_time_dist_T4T5->Draw("colz");
//    cCH_time_dist->SaveAs("./plot/RUN_33/subRUN1/chn_time_dist_micromegas_bin0.1s.pdf");

//data time distribution for MMs with channels differentiation after selection
    TCanvas *cCH_time_dist_after_selection = new TCanvas("cCH_time_dist_after_selection","cCH_time_dist_after_selection");
    gStyle->SetPalette(kRainBow);
    cCH_time_dist_after_selection-> Divide(1,3,0.01,0.01);

    cCH_time_dist_after_selection->cd(1);
	  chn_time_dist_after_selection_T0T1->Draw("colz");
    cCH_time_dist_after_selection->cd(2);
    chn_time_dist_after_selection_T2T3->Draw("colz");
    cCH_time_dist_after_selection->cd(3);
	  chn_time_dist_after_selection_T4T5->Draw("colz");

//    cCH_time_dist_after_selection->SaveAs("./plot/RUN_33/subRUN1/chn_time_dist_after_selection_micromegas_bin0.1s.pdf");
  */ 
}