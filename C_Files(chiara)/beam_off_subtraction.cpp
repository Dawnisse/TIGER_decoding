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
string tiger_bon0;     string tiger_boff1;     
string mode_bon0;      string mode_boff1;      
string channel_bon0;   string channel_boff1;   
string tac_Id_bon0;    string tac_Id_boff1;    
string t_coarse_bon0;  string t_coarse_boff1;  
string e_coarse_bon0;  string e_coarse_boff1;  
string t_fine_bon0;    string t_fine_boff1;    
string e_fine_bon0;    string e_fine_boff1;   

//variables declaration
Int_t tigerId_bon0;       Int_t tigerId_boff1;     
Int_t ch_bon0;            Int_t ch_boff1;          
Int_t tacId_bon0;         Int_t tacId_boff1;       
Int_t tcoarse_bon0;       Int_t tcoarse_boff1;     
Int_t tcoarse_10b_bon0;   Int_t tcoarse_10b_boff1; 
Int_t ecoarse_bon0;       Int_t ecoarse_boff1;     
Int_t tfine_bon0;         Int_t tfine_boff1;       
Int_t efine_bon0;         Int_t efine_boff1;       

Int_t framenum_bon0 = 0;          
Int_t framenum_boff1 = 0;         
Int_t prev_framenum_bon0 =0;      
Int_t prev_framenum_boff1 =0;     
Int_t framecount_bon0 = 0;        
Int_t framecount_boff1 = 0;       

Double_t timeVal_bon0; 
Double_t timeVal_bon0_fordiff;           
Double_t timeVal_boff1;
Double_t timeVal_boff1_fordiff;           
Double_t timeVal_prev_bon0 = 0;   
Double_t timeVal_prev_boff1 = 0;  

Int_t prev_tcoarse_bon0=0;        
Int_t prev_tcoarse_boff1=0;      
Int_t tcoarse_frame_bon0 =0;     
Int_t tcoarse_frame_boff1 =0;    

Int_t pinNum;
Int_t strNum;

void beam_off_subtraction() {
  
    ifstream inFile_bon0("../data_folder/RUN_33/SubRUN_0_GEMROC_0_TL.datout.txt");
    ifstream inFile_boff1("../data_folder/RUN_38/SubRUN_0_GEMROC_0_TL.datout.txt"); 
    
    TH1D *data_dist_T0 = new TH1D("data time profile T0", Form("data time profile T0;Time[s];Counts"), 115, 9.8,21.3);
    TH1D *data_dist_T1 = new TH1D("data time profile T1", Form("data time profile T1;Time[s];Counts"), 115, 9.8,21.3);
    TH1D *data_dist_T2 = new TH1D("data time profile T2", Form("data time profile T2;Time[s];Counts"), 115, 9.8,21.3);
    TH1D *data_dist_T3 = new TH1D("data time profile T3", Form("data time profile T3;Time[s];Counts"), 115, 9.8,21.3);
    TH1D *data_dist_T4 = new TH1D("data time profile T4", Form("data time profile T4;Time[s];Counts"), 115, 9.8,21.3);
    TH1D *data_dist_T5 = new TH1D("data time profile T5", Form("data time profile T5;Time[s];Counts"), 115, 9.8,21.3); 

    TH1D *data_dist_T0T1 = new TH1D("data time profile T0", Form("data time profile ExtTP (T0T1);Time[s];Counts"), 115,9.8,21.3);
    TH1D *data_dist_T2T3 = new TH1D("data time profile T1", Form("data time profile MM1 (T2T3);Time[s];Counts"), 115,9.8,21.3);
    TH1D *data_dist_T4T5 = new TH1D("data time profile T2", Form("data time profile MM2 (T4T5);Time[s];Counts"), 115,9.8,21.3);  
    
    TH1D *beam_profile_SUB0_T0T1 = new TH1D("beam profile", Form("Channel activity Fe55-F source;strNum;Counts"),124,-0.5,123.5);
    TH1D *beam_profile_SUB0_T2T3 = new TH1D("beam profile", Form("beam profile MM1 (T2T3);strNum;Counts"),124,-0.5,123.5);
    TH1D *beam_profile_SUB0_T4T5 = new TH1D("beam profile", Form("beam profile MM2 (T4T5);strNum;Counts"),124,-0.5,123.5);

    TH1D *beam_profile_SUB1_T0T1 = new TH1D("beam profile", Form("beam profile ExtTP (T0T1);strNum;Counts"),124,-0.5,123.5);
    TH1D *beam_profile_SUB1_T2T3 = new TH1D("beam profile", Form("beam profile MM1 (T2T3);strNum;Counts"),124,-0.5,123.5);
    TH1D *beam_profile_SUB1_T4T5 = new TH1D("beam profile", Form("beam profile MM2 (T4T5);strNum;Counts"),124,-0.5,123.5);
 
    TH1D *beam_profile_diffSUB0SUB1_T0T1 = new TH1D("beam profile", Form("beam profile ExtTP (T0T1);strNum;Counts"),124,-0.5,123.5);
    TH1D *beam_profile_diffSUB0SUB1_T2T3 = new TH1D("beam profile", Form("beam profile MM1 (T2T3);strNum;Counts"),124,-0.5,123.5);
    TH1D *beam_profile_diffSUB0SUB1_T4T5 = new TH1D("beam profile", Form("beam profile MM2 (T4T5);strNum;Counts"),124,-0.5,123.5);
    
    TH1D *ch_41_T0_efine_bon = new TH1D("ch_41_t0_efine", Form("ch 41 TIGER:0 Efine BEAM ON; Efine[bin]; Counts"),1024,0,1024);
    TH1D *ch_41_T0_efine_boff = new TH1D("ch_41_t0_efine", Form("ch 41 TIGER:0 Efine BEAM OFF; Efine[bin]; Counts"),1024,0,1024);
 
    TH2D *chn_time_dist_SUB0_T0T1 = new TH2D("channels data time distribution SUB0 exTP (T0T1)",  Form("channel data time distribution Sub0  exTP (T0 T1);strip;Time[s]"), 124, -0.5, 123.5, 42,0,4.2);
    TH2D *chn_time_dist_SUB0_T2T3 = new TH2D("channels data time distribution SUB0 MM1 (T2T3)",  Form("channel data time distribution  Sub0 MM1 (T2 T3);strip;Time[s]"), 124, -0.5, 123.5, 42,0,4.2);
    TH2D *chn_time_dist_SUB0_T4T5 = new TH2D("channels data time distribution SUB0 MM1 (T4T5)",  Form("channel data time distribution  Sub0 MM2 (T4 T5);strip;Time[s]"), 124, -0.5, 123.5, 42,0,4.2);

    TH2D *chn_time_dist_SUB1_T0T1 = new TH2D("channels data time distribution exTP (T0T1)",  Form("channel data time distribution Sub1 exTP (T0 T1);strip;Time[s]"), 124, -0.5, 123.5,42,0,4.2);
    TH2D *chn_time_dist_SUB1_T2T3 = new TH2D("channels data time distribution MM1 (T2T3)",  Form("channel data time distribution  Sub1MM1 (T2 T3);strip;Time[s]"), 124, -0.5, 123.5,42,0,4.2);
    TH2D *chn_time_dist_SUB1_T4T5 = new TH2D("channels data time distribution MM1 (T4T5)",  Form("channel data time distribution  Sub1MM2 (T4 T5);strip;Time[s]"), 124, -0.5, 123.5,42,0,4.2);
    
    TH2D *chn_time_dist_diffSUB0SUB1_T0T1 = new TH2D("channels data time distribution exTP (T0T1)",  Form("channel data time distribution Sub0-Sub1  exTP (T0 T1);strip;Time[s]"), 124, -0.5, 123.5,42,0,4.2);
    TH2D *chn_time_dist_diffSUB0SUB1_T2T3 = new TH2D("channels data time distribution MM1 (T2T3)",  Form("channel data time distribution  Sub0-Sub1 MM1 (T2 T3);strip;Time[s]"), 124, -0.5, 123.5,42,0,4.2);
    TH2D *chn_time_dist_diffSUB0SUB1_T4T5 = new TH2D("channels data time distribution MM1 (T4T5)",  Form("channel data time distribution  Sub0-Sub1 MM2 (T4 T5);strip;Time[s]"), 124, -0.5, 123.5,42,0,4.2);
    
    //validity check
   if (inFile_bon0.fail()) {
        cerr << "errore nell'apertura del file, uscita dal programma" << endl;
        abort();
   }

   if (inFile_boff1.fail()) {
        cerr << "errore nell'apertura del file, uscita dal programma" << endl;
        abort();
   }

//----------------------------------------------//
// ---------- beam on SUB0 file loop -----------//
//----------------------------------------------//
    for (Int_t ibit = 0; !inFile_bon0.eof(); ibit++) {

        //load SubRun0 data 
        inFile_bon0 >> tiger_bon0 >> tigerId_bon0 >> mode_bon0 >> channel_bon0  >> std::hex>> ch_bon0 >>
        tac_Id_bon0 >> tacId_bon0 >> t_coarse_bon0 >> std::hex >> tcoarse_bon0 >> e_coarse_bon0 >> std::hex >> ecoarse_bon0 >>
        t_fine_bon0 >> std::hex >> tfine_bon0 >> e_fine_bon0 >> std::hex >> efine_bon0; 

//debug
        //cout << " SubRUN0 dat: "<< tiger_bon0 <<  tigerId_bon0 << " " << mode_bon0 <<" " << channel_bon0 << ch_bon0 <<" " <<
        //tac_Id_bon0 << tacId_bon0 <<" " << t_coarse_bon0 << tcoarse_bon0 <<" " << e_coarse_bon0 << ecoarse_bon0 <<" " <<
        //t_fine_bon0 << tfine_bon0 <<" " << e_fine_bon0 << efine_bon0 << endl;

//FRAMECOUNTS IDENTIFICATION for beam on data
        if (mode_bon0 == "HB:"){

            framecount_bon0 = ch_bon0;
            inFile_bon0.ignore(256, '\n');
            tcoarse_bon0 = prev_tcoarse_bon0;          
//debug
            //cout << "---------------- frame number BON ---------> " << framenum_bon0/3 << endl; // framecount identification
            //cout << "---------------- frame counter BON ---------> " << framecount_bon0 << endl; // framecount identification
            framenum_bon0 ++;
        }

//taking account of the tcoarse rolling over in the middle of frame 

        // ----- BEAM ON -----//
        if(prev_tcoarse_bon0 - tcoarse_bon0 > 20000 && framenum_bon0 == prev_framenum_bon0){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal_bon0 = framecount_bon0 * 204.8e-6 + tcoarse_bon0 * 6.25e-9 + 65536*6.25e-9;
        }

//Alignement of frame counter and tcoarse counter
        // ----- BEAM ON -----//
        if(timeVal_bon0 - timeVal_prev_bon0 > 0.0001){
            
            tcoarse_frame_bon0 = tcoarse_bon0; // subtraction of tcoarse value of the framecount in order to achieve correct alignement 
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

// TIME VALUE
        if (framecount_bon0 >= prev_framenum_bon0){
            
            timeVal_bon0  = framecount_bon0 * 204.8e-6 + (tcoarse_bon0-tcoarse_frame_bon0) * 6.25e-9; //s
            
        }
        else{
            timeVal_bon0  = (framecount_bon0+65536) * 204.8e-6 + (tcoarse_bon0-tcoarse_frame_bon0) * 6.25e-9; //s  
        }

        //for subtraction
        timeVal_bon0_fordiff = framenum_bon0/3 * 204.8e-6 + (tcoarse_bon0-tcoarse_frame_bon0) * 6.25e-9; //s
// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId_bon0 == 0 && mode_bon0 == "EW:"){

            //filling data timing distribution histos
            data_dist_T0 -> Fill(timeVal_bon0);
            data_dist_T0T1 -> Fill(timeVal_bon0);
            if(ch_bon0 == 41) {
                ch_41_T0_efine_bon->Fill(efine_bon0);
            }

            //MAPPING PROCEDURE
            switch (ch_bon0){
			
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
            beam_profile_SUB0_T0T1->Fill(strNum);
            if(timeVal_bon0< timeVal_prev_bon0 + 20e-9) {
                chn_time_dist_SUB0_T0T1->Fill(strNum, timeVal_bon0_fordiff);
                
            }
        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId_bon0 == 1 && mode_bon0 == "EW:") {

            //filling data timing distribution histos
            data_dist_T1 -> Fill(timeVal_bon0);
            data_dist_T0T1 -> Fill(timeVal_bon0);

            //MAPPING procedure
            switch (ch_bon0){
            
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

            beam_profile_SUB0_T0T1->Fill(strNum);
            if(timeVal_bon0< timeVal_prev_bon0 + 20e-9){ 
                chn_time_dist_SUB0_T0T1->Fill(strNum, timeVal_bon0_fordiff);
                
            }
        }
// ------------------------ TIGER 2 ------------------------------ //
        if (tigerId_bon0 == 2 && mode_bon0 == "EW:"){

            //filling data timing distribution histos
            data_dist_T2 -> Fill(timeVal_bon0);
            data_dist_T2T3 -> Fill(timeVal_bon0);

            //MAPPING PROCEDURE
            switch (ch_bon0){
			
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

            if(timeVal_bon0< timeVal_prev_bon0 + 20e-9) {
                chn_time_dist_SUB0_T2T3->Fill(strNum, timeVal_bon0_fordiff);
                beam_profile_SUB0_T2T3->Fill(strNum);
            }
        }
// ------------------------ TIGER 3 ------------------------------ //
        if (tigerId_bon0 == 3 && mode_bon0 == "EW:"){

            //filling data timing distribution histos
            data_dist_T3 -> Fill(timeVal_bon0);
            data_dist_T2T3 -> Fill(timeVal_bon0);

            //MAPPING procedure
            switch (ch_bon0){
            
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

            if(timeVal_bon0< timeVal_prev_bon0 + 20e-9) {
                chn_time_dist_SUB0_T2T3->Fill(strNum, timeVal_bon0_fordiff);
                beam_profile_SUB0_T2T3->Fill(strNum);
            }
        }
// ------------------------ TIGER 4 ------------------------------ //          
        if (tigerId_bon0 == 4 && mode_bon0 == "EW:"){

            //filling data timing distribution histos
            data_dist_T4 -> Fill(timeVal_bon0);
            data_dist_T4T5 -> Fill(timeVal_bon0);

            //MAPPING PROCEDURE
            switch (ch_bon0){
			
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

            if(timeVal_bon0< timeVal_prev_bon0 + 20e-9) {
                chn_time_dist_SUB0_T4T5->Fill(strNum, timeVal_bon0_fordiff);
                beam_profile_SUB0_T4T5->Fill(strNum);
            }
        } 
// ------------------------ TIGER 5 ------------------------------ //
        if (tigerId_bon0 == 5 && mode_bon0 == "EW:"){

            //filling data timing distribution histos
            data_dist_T5 -> Fill(timeVal_bon0);
            data_dist_T4T5 -> Fill(timeVal_bon0);

            //MAPPING procedure
            switch (ch_bon0){
            
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
            if(timeVal_bon0< timeVal_prev_bon0 + 20e-9) {
                chn_time_dist_SUB0_T4T5->Fill(strNum, timeVal_bon0_fordiff);
                beam_profile_SUB0_T4T5->Fill(strNum);
            }
            
        }

    prev_tcoarse_bon0  = tcoarse_bon0;
    timeVal_prev_bon0  = timeVal_bon0;
    prev_framenum_bon0 = framenum_bon0;
//debug
    //cout <<"prev_tcoarse_BON : "<<prev_tcoarse_bon0 << endl;
    //cout <<"tcoarse_BON : " << tcoarse_bon0 << endl;
    //cout <<"prev_tVal_BON : "<< timeVal_prev_bon0 <<endl;
    //cout <<"tVal_BON : " << timeVal_bon0 << endl;
    //cout<<endl;
    }

//----------------------------------------------//
// ---------- beam off SUB1 file loop --------- //
//----------------------------------------------//
   for (Int_t ibit = 0; !inFile_boff1.eof() ; ibit++) {

        //load SubRun1 data
        inFile_boff1 >> tiger_boff1 >> tigerId_boff1 >> mode_boff1 >> channel_boff1 >> std::hex >> ch_boff1 >>
        tac_Id_boff1 >> tacId_boff1 >> t_coarse_boff1 >> std::hex >> tcoarse_boff1 >> e_coarse_boff1 >> std::hex >> ecoarse_boff1 >>
        t_fine_boff1 >> std::hex >> tfine_boff1 >> e_fine_boff1 >> std::hex >> efine_boff1;

//FRAMECOUNT IDENTIFICATION    
         if (mode_boff1 == "HB:"){

            framecount_boff1 = ch_boff1;
            inFile_boff1.ignore(256, '\n');
            tcoarse_boff1 = prev_tcoarse_boff1;          
//debug
            //cout << "---------------- frame number BOFF ---------> " << framenum_boff1/3 << endl; // framecount identification
            //cout << "---------------- frame counter BOFF ---------> " << framecount_boff1 << endl; // framecount identification
            framenum_boff1 ++;
        }
        //----- BEAM OFF -----//
        if(prev_tcoarse_boff1 - tcoarse_boff1 > 20000 && framenum_boff1 == prev_framenum_boff1){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal_boff1 = framecount_boff1 * 204.8e-6 + tcoarse_boff1 * 6.25e-9 + 65536*6.25e-9;
        }

//Allignement of tcoarse and framecount       
         //----- BEAM OFF -----//
        if(timeVal_boff1 - timeVal_prev_boff1 > 0.0001){
            
            tcoarse_frame_boff1 = tcoarse_boff1;
            //cout << "----------- tcoarse framecount ---------> " << tcoarse_frame << endl;
        }

//TIME VALUE        
         if (framecount_boff1 >= prev_framenum_boff1 && framenum_boff1 == prev_framenum_boff1){
            timeVal_boff1 = framecount_boff1 * 204.8e-6 + (tcoarse_boff1-tcoarse_frame_boff1) * 6.25e-9; //s
         }
        else {
            timeVal_boff1  = (framecount_boff1+65536) * 204.8e-6 + (tcoarse_boff1-tcoarse_frame_boff1) * 6.25e-9; //s
        } 

        //for subtraction
        timeVal_boff1_fordiff = framenum_boff1/3 * 204.8e-6 + (tcoarse_boff1-tcoarse_frame_boff1) * 6.25e-9; //s
// ------------------------ TIGER 0 ------------------------------ //
        if (tigerId_boff1 == 0 && mode_boff1 == "EW:"){

            //filling data timing distribution histos
            data_dist_T0 -> Fill(timeVal_boff1);
            data_dist_T0T1 -> Fill(timeVal_boff1);

            if(ch_boff1==41) {
                ch_41_T0_efine_boff->Fill(efine_boff1);
            }

            //MAPPING PROCEDURE
            switch (ch_boff1){
			
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
            beam_profile_SUB1_T0T1->Fill(strNum);
            if(strNum==63){
                ch_41_T0_efine_boff->Fill(efine_boff1);
            }
            if(timeVal_boff1< timeVal_prev_boff1 + 20e-9) {
                chn_time_dist_SUB1_T0T1->Fill(strNum, timeVal_boff1_fordiff);
                
            }
        }
// ------------------------ TIGER 1 ------------------------------ //
        if (tigerId_boff1 == 1 && mode_boff1 == "EW:") {

            //filling data timing distribution histos
            data_dist_T1 -> Fill(timeVal_boff1);
            data_dist_T0T1 -> Fill(timeVal_boff1);

            //MAPPING procedure
            switch (ch_boff1){
            
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
            beam_profile_SUB1_T0T1->Fill(strNum);
                

            if(timeVal_boff1< timeVal_prev_boff1 + 20e-9) {
                chn_time_dist_SUB1_T0T1->Fill(strNum, timeVal_boff1_fordiff);
                
            }
        }
// ------------------------ TIGER 2 ------------------------------ //
        if (tigerId_boff1 == 2 && mode_boff1 == "EW:"){

            //filling data timing distribution histos
            data_dist_T2 -> Fill(timeVal_boff1);
            data_dist_T2T3 -> Fill(timeVal_boff1);

            //MAPPING PROCEDURE
            switch (ch_boff1){
			
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

            if(timeVal_boff1< timeVal_prev_boff1 + 20e-9) {
                chn_time_dist_SUB1_T2T3->Fill(strNum, timeVal_boff1_fordiff);
                beam_profile_SUB1_T2T3->Fill(strNum);
            }
        }
// ------------------------ TIGER 3 ------------------------------ //
        if (tigerId_boff1 == 3 && mode_boff1 == "EW:"){
            
            //filling data timing distribution histos
            data_dist_T3 -> Fill(timeVal_boff1);
            data_dist_T2T3 -> Fill(timeVal_boff1);

            //MAPPING procedure
            switch (ch_boff1){
            
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
            
            if(timeVal_boff1< timeVal_prev_boff1 + 20e-9) {
                chn_time_dist_SUB1_T2T3->Fill(strNum, timeVal_boff1_fordiff);
                beam_profile_SUB1_T2T3->Fill(strNum);
            }
        }
// ------------------------ TIGER 4 ------------------------------ //          
        if (tigerId_boff1 == 4 && mode_boff1 == "EW:"){

            //filling data timing distribution histos
            data_dist_T4 -> Fill(timeVal_boff1);
            data_dist_T4T5 -> Fill(timeVal_boff1);

            //MAPPING PROCEDURE
            switch (ch_boff1){
			
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

            if(timeVal_boff1< timeVal_prev_boff1 + 20e-9){ 
                chn_time_dist_SUB1_T4T5->Fill(strNum, timeVal_boff1_fordiff);
                beam_profile_SUB1_T4T5->Fill(strNum);
            }
        } 
// ------------------------ TIGER 5 ------------------------------ //
        if (tigerId_boff1 == 5 && mode_boff1 == "EW:"){

            //filling data timing distribution histos
            data_dist_T5 -> Fill(timeVal_boff1);
            data_dist_T4T5 -> Fill(timeVal_boff1);

            //MAPPING procedure
            switch (ch_boff1){
            
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

            if(timeVal_boff1< timeVal_prev_boff1 + 20e-9){ 
                chn_time_dist_SUB1_T4T5->Fill(strNum, timeVal_boff1_fordiff);
                beam_profile_SUB1_T4T5->Fill(strNum);
            }

        }
//debug
        //cout <<"prev_tcoarse_BOFF : "<<prev_tcoarse_boff1 << endl;
        //cout <<"tcoarse_BOFF : " << tcoarse_boff1 << endl;
        //cout <<"prev_tVal_BOFF : "<< timeVal_prev_boff1 <<endl;
        //cout <<"tVal_BOFF : " << timeVal_boff1 << endl;
        //cout<<endl;s

    prev_tcoarse_boff1  = tcoarse_boff1;
    timeVal_prev_boff1  = timeVal_boff1;
    prev_framenum_boff1 = framenum_boff1;

    }


//functions for plot

    initFigTemplate();
/*
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


//data time distribution for MMs
    TCanvas *cdata_time_dist_MicroMegas = new TCanvas("cdata_time_dist_MicroMegas","cdata_time_dist_MicroMegas");
    cdata_time_dist_MicroMegas-> Divide(1,3,0.01,0.01);

    cdata_time_dist_MicroMegas->cd(1);
	data_dist_T0T1->Draw();
    cdata_time_dist_MicroMegas->cd(2);
	data_dist_T2T3->Draw();
    cdata_time_dist_MicroMegas->cd(3);
	data_dist_T4T5->Draw();
*/
//beam profile
beam_profile_diffSUB0SUB1_T0T1->Add(beam_profile_SUB0_T0T1, beam_profile_SUB1_T0T1,-1,1);

THStack *hs = new THStack("hs",Form("channels activity Vmesh=450 Vdrift=800;strNum;Counts"));
hs->Add(beam_profile_SUB1_T0T1);
hs->Add(beam_profile_SUB0_T0T1);
hs->Add(beam_profile_diffSUB0SUB1_T0T1);

TCanvas *cChannel_beam_profileT0T1 = new TCanvas("cChannel_beam_profileT0T1","cChannel_beam_profileT0T1");
      
      beam_profile_SUB1_T0T1->SetLineColor(kRed);
      beam_profile_SUB0_T0T1->SetFillColor(kBlue);
      beam_profile_diffSUB0SUB1_T0T1->SetLineColor(kGreen);
      hs->Draw("nostack");

TLegend *legt0t1 = new TLegend(0.1,0.7,0.48,0.9);
        legt0t1->SetFillColor(0);
        legt0t1->SetHeader("Legend");
        legt0t1->AddEntry(beam_profile_SUB0_T0T1, "no source", "lp");
        legt0t1->AddEntry(beam_profile_SUB1_T0T1, "Fe55 source central", "lp");
        legt0t1->AddEntry(beam_profile_diffSUB0SUB1_T0T1, "diff");
        legt0t1->Draw();

beam_profile_diffSUB0SUB1_T2T3->Add(beam_profile_SUB0_T2T3, beam_profile_SUB1_T2T3, 1,-1);
/*
TCanvas *cChannel_beam_profileT2T3 = new TCanvas("cChannel_beam_profileT2T3","cChannel_beam_profileT2T3");
      
      beam_profile_SUB1_T2T3->SetLineColor(kBlue);
      beam_profile_SUB1_T2T3->Draw("same");
      beam_profile_SUB0_T2T3->SetLineColor(kRed);
	  beam_profile_SUB0_T2T3->Draw("same");
      beam_profile_diffSUB0SUB1_T2T3->SetLineColor(kBlueGreenYellow);
      beam_profile_diffSUB0SUB1_T2T3->Draw("same");

TLegend *legt2t3 = new TLegend(0.1,0.7,0.48,0.9);
        legt2t3->SetFillColor(0);
        legt2t3->SetHeader("Legend");
        legt2t3->AddEntry(beam_profile_SUB0_T2T3, "beam on", "lp");
        legt2t3->AddEntry(beam_profile_SUB1_T2T3, "beam off", "lp");
        legt2t3->AddEntry(beam_profile_diffSUB0SUB1_T2T3, "diff");
        legt2t3->Draw();

beam_profile_diffSUB0SUB1_T4T5->Add(beam_profile_SUB0_T4T5, beam_profile_SUB1_T4T5, 1,-1);

TCanvas *cChannel_beam_profileT4T5 = new TCanvas("cChannel_beam_profileT4T5","cChannel_beam_profileT4T5");
      
      beam_profile_SUB1_T4T5->SetLineColor(kBlue);
      beam_profile_SUB1_T4T5->Draw("same");
      beam_profile_SUB0_T4T5->SetLineColor(kRed);
	  beam_profile_SUB0_T4T5->Draw("same");
      beam_profile_diffSUB0SUB1_T4T5->SetLineColor(kBlueGreenYellow);
      beam_profile_diffSUB0SUB1_T4T5->Draw("same");
*/
//TLegend *legt4t5 = new TLegend(0.1,0.7,0.48,0.9);
//        legt4t5->SetFillColor(0);
//        //legt4t5->SetHeader("Legend");
//        //legt4t5->AddEntry(beam_profile_SUB0_T4T5, "beam on", "lp");
//        //legt4t5->AddEntry(beam_profile_SUB1_T4T5, "beam off", "lp");
//        legt4t5->AddEntry(beam_profile_diffSUB0SUB1_T4T5, "diff");
//        legt4t5->Draw();
//
//Efine canale attivo
//TCanvas *cEfine_63str = new TCanvas("cEfine_63str","cEfine_63str");
//      ch_41_T0_efine_bon->SetLineColor(kBlue);
//	  ch_41_T0_efine_bon->Draw("same");
//      ch_41_T0_efine_boff->SetLineColor(kRed);
//      ch_41_T0_efine_boff->Draw("same");

//TLegend *legenda = new TLegend(0.1,0.7,0.48,0.9);
//        legenda->SetFillColor(0);
//        legenda->SetHeader("Legend");
//        legenda->AddEntry(beam_profile_SUB0_T0T1, "background no source", "lp");
//        legenda->AddEntry(beam_profile_SUB1_T0T1, "Fe55 source center", "lp");
//        
//        legenda->Draw();

        /*
    TCanvas *cChannel_beam_profile = new TCanvas("cChannel_beam_profile","cChannel_beam_profile");
    cChannel_beam_profile-> Divide(1,3,0.01,0.01);

    cChannel_beam_profile->cd(1);
      beam_profile_SUB0_T0T1->SetLineColor(kBlue);
	  beam_profile_SUB0_T0T1->Draw("same");
      beam_profile_SUB1_T0T1->SetLineColor(kRed);
      beam_profile_SUB1_T0T1->Draw("same");
    cChannel_beam_profile->cd(2);
      beam_profile_SUB0_T2T3->SetLineColor(kBlue);
	  beam_profile_SUB0_T2T3->Draw("same");
      beam_profile_SUB1_T2T3->SetLineColor(kRed);
      beam_profile_SUB1_T2T3->Draw("same");
    cChannel_beam_profile->cd(3);
      beam_profile_SUB0_T4T5->SetLineColor(kBlue);
	  beam_profile_SUB0_T4T5->Draw("same");
      beam_profile_SUB1_T4T5->SetLineColor(kRed);
      beam_profile_SUB1_T4T5->Draw("same");
    
    TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
        leg->SetFillColor(0);
        leg->SetHeader("Legend");
        leg->AddEntry(beam_profile_SUB0_T0T1, "background no source", "lp");
        leg->AddEntry(beam_profile_SUB1_T0T1, "Fe55 source center", "lp");
        leg->Draw();


//channel correlation with data time distribution for MMs (SUB0->BEAM-ON)

    TCanvas *cCH_time_dist_SubRUN0 = new TCanvas("cCH_time_dist_SubRUN0","cCH_time_dist_SubRUN0");
    gStyle->SetPalette(kRainBow);
    cCH_time_dist_SubRUN0-> Divide(1,3,0.01,0.01);

    cCH_time_dist_SubRUN0->cd(1);
 	  chn_time_dist_SUB0_T0T1->Draw("colz");
    cCH_time_dist_SubRUN0->cd(2);
	  chn_time_dist_SUB0_T2T3->Draw("colz");
    cCH_time_dist_SubRUN0->cd(3);
	  chn_time_dist_SUB0_T4T5->Draw("colz");

//channel correlation with data time distribution for MMs (SUB1->BEAM-OFF)

    TCanvas *cCH_time_dist_SubRUN1 = new TCanvas("cCH_time_dist_SubRUN1","cCH_time_dist_SubRUN1");
    gStyle->SetPalette(kRainBow);
    cCH_time_dist_SubRUN1-> Divide(1,3,0.01,0.01);

    cCH_time_dist_SubRUN1->cd(1);
 	  chn_time_dist_SUB1_T0T1->Draw("colz");
    cCH_time_dist_SubRUN1->cd(2);
	  chn_time_dist_SUB1_T2T3->Draw("colz");
    cCH_time_dist_SubRUN1->cd(3);
	  chn_time_dist_SUB1_T4T5->Draw("colz");

//sottrazione del fondo
    chn_time_dist_diffSUB0SUB1_T0T1->Add(chn_time_dist_SUB0_T0T1, chn_time_dist_SUB1_T0T1, 1,-1);
    chn_time_dist_diffSUB0SUB1_T2T3->Add(chn_time_dist_SUB0_T2T3, chn_time_dist_SUB1_T2T3, 1,-1);
    chn_time_dist_diffSUB0SUB1_T4T5->Add(chn_time_dist_SUB0_T4T5, chn_time_dist_SUB1_T4T5, 1,-1);

    TCanvas *cCH_time_dist_DIFF = new TCanvas("cCh_time_dist_DIFF","cCh_time_dist_DIFF");
    gStyle->SetPalette(kRainBow);
    cCH_time_dist_DIFF->Divide(1,3,0.01,0.01);

    cCH_time_dist_DIFF->cd(1);
    chn_time_dist_diffSUB0SUB1_T0T1->Draw("colz");
    cCH_time_dist_DIFF->cd(2);
    chn_time_dist_diffSUB0SUB1_T2T3->Draw("colz");
    cCH_time_dist_DIFF->cd(3);
    chn_time_dist_diffSUB0SUB1_T4T5->Draw("colz");
*/



}