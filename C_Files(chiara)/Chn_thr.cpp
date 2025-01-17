#include "Riostream.h"
#include "Rtypes.h"
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
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



Double_t thr_TBranch[] = {57,58.0,56.0,58.0,58.0,58.0, 0.0,58.0,56.0,57.0,57.0,56.0,58.0, 0.0,58.0,58.0,57.0,58.0, 0.0,57.0,57.0, 0.0, 0.0,55.0,58.0, 0.0,57.0,55.0,55.0
                        ,0.0,53.0,55.0,58.0, 0.0,55.0,57.0, 0.0,56.0, 0.0,57.0,56.0,56.0,58.0,58.0,58.0,57.0,56.0,55.0,56.0, 0.0,57.0,57.0,56.0, 0.0,55.0,55.0,57.0,55.0
                        ,56.0,55.0,56.0, 0.0, 0.0,57.0,44.0,50.0,47.0,47.0, 0.0,47.0,47.0,45.0, 0.0,50.0, 0.0, 0.0,46.0,47.0,46.0, 0.0,47.0,47.0,49.0, 48.,48.0,47.0, 0.0
                        ,47.0 ,48,0.0,50.0,46.0, 0.0,46.0, 48.,48.0,49.0,50.0,46.0, 48.,50.0,49.0, 48.,45.0, 48.,47.0,45.0,46.0,50.0, 0.0,47.0, 48.,46.0,49.0,47.0,50.0,49.0
                        ,49.0,49.0,50.0,46.0,47.0,47.0,47.0,47.0,47.0, 48.,49.0} ;

Double_t err_thr_TBranch[] = {0.05245475291319557,0.058293994228602375, 0.11265268563580288, 0.3949413069787719 ,.07982997583609037  ,0.058293994228602375,1,0.058293994228602375
                        ,0.0717835218698612  ,0.4859623708599439  , 0.14814227592050885,0.0717835218698612  ,0.058293994228602375,1,0.058293994228602375,0.058293994228602375
                        , 0.05245475291319557,0.058293994228602375,1, 0.05245475291319557, 0.14706178029487968,1,1,1,0.058293994228602375,1, 0.05245475291319557,0.12213565632385348 ,0.06911373739922179 
                        ,1,0.07391721902071502 ,1,0.058293994228602375,1,0.06911373739922179 , 0.05245475291319557,1,0.0717835218698612  ,1, 0.05245475291319557,0.0717835218698612  
                        ,0.10104586652243984 ,0.058293994228602375,0.13897183287828402 ,0.058293994228602375, 0.05245475291319557,0.10502838143720673 ,0.06911373739922179 ,0.0717835218698612  
                        ,1, 0.05245475291319557, 0.05245475291319557,0.10563165411394977 ,1,0.06911373739922179 ,0.06911373739922179 , 0.05245475291319557,0.06911373739922179 ,0.0717835218698612  
                        ,0.06911373739922179 ,0.1264953889107706  ,1,1,0.1466906596633007,0.07506372040288395,0.14401349287110515 , 0.14404490364284367,0.10345533940883475 ,1
                        , 0.07495522210303956,0.07495522210303956,0.07488941806773136,1, 0.896753529546775  ,1,1, 0.07233927322455891, 0.07495522210303956,1,1, 0.07495522210303956
                        , 0.07495522210303956,0.0638755187984818  ,  0.0669268773563488, 0.12367276542807808, 0.07495522210303956,1, 0.07495522210303956,  0.0669268773563488
                        ,1,0.05663609454776297 , 0.07233927322455891,1, 0.07233927322455891,  0.0669268773563488,1, 1.5334448590191982 ,0.05663609454776297 , 0.07233927322455891,  0.0669268773563488
                        , 0.14539788244444857,0.0638755187984818  ,  0.0669268773563488,  0.9450082864496214,  0.0669268773563488, 0.07495522210303956, 0.07488941806773136, 0.07233927322455891
                        ,0.05663609454776297 ,1, 0.07495522210303956,  0.0669268773563488, 0.07233927322455891,0.0638755187984818  , 0.07495522210303956,0.05663609454776297 ,  1.2270296337622089
                        ,0.0638755187984818  ,0.0638755187984818  , 1.3586785786600728 , 0.07233927322455891,1, 0.07495522210303956,1, 0.07495522210303956, 0.07495522210303956,  0.0669268773563488,0.0638755187984818  } ;
Double_t thr_EBranch[] = {56.0, 56.,  55,56.0, 58.,56.0, 0.0, 59.,56.0,54.0, 57.,  59,  57, 0.0,  57, 55., 55.,56.0, 0.0,57.0,56.0, 0.0, 0.0,  57, 55., 55.,  57,55.0, 55.
                        , 0.0,56.0,  57,  58, 0.0,55.0,  54, 0.0, 56., 0.0,56.0,56.0,56.0,60.0, 55.,  58,56.0, 55., 54., 58., 0.0,55.0, 55.,54.0, 0.0, 58.,56.0,56.0, 55.,59.0
                        ,57,55.,0.0,0.0,57.,48.0,47.0,47.0,46.0, 0.0,48.0,47.0,46.0, 0.0,44.0, 0.0, 0.0,47.0,48.0,46.0, 0.0,48.0,49.0,49.0,47.0,47.0,49.0, 0.0,49.0,47.0
                        , 0.0,51.0,48.0, 0.0,47.0,45.0,48.0,44.0,48.0,46.0,47.0,48.0,46.0,48.0,48.0,46.0,47.0,46.0,48.0,48.0, 0.0,48.0,49.0,48.0,47.0,48.0,47.0,44.0,46.0
                        ,51.0,41.0,48.0,47.0,49.0,46.0,44.0,48.0,51.0,48.0} ;
Double_t err_thr_EBranch[] = {0.0717835218698612,0.1417789168814965, 0.096305207254413,1.78094916826555  ,0.0552952519238751,1,1,0.0490048036393825,0.0717835218698612
                        ,1.7863068200612238,0.1482574578549307, 0.110191512699241, 0.148498790354927,1, 0.052454752913195,0.0691137373992217,0.0691137373992217,0.0717835218698612
                        ,1,1,1,1,1, 0.052454752913195,0.0691137373992217,0.0691137373992217, 0.052454752913195,1, 0.145560203528357,1,0.0717835218698612, 0.052454752913195,0.0582939942286023
                        ,1,1, 0.136725586642597,1, 0.108350837046831,1,0.0717835218698612,1,0.0717835218698612,0.0741638951525153,0.1060880719150714,0.0582939942286023,1
                        ,0.0691137373992217,0.0620775903309399,0.0996891703782115,1,1,0.0691137373992217,1,1,0.1011568172234841,0.0717835218698612,0.0717835218698612,0.0691137373992217
                        ,.06322858788557195, 0.052454752913195,0.0691137373992217,1,1, 0.1428750365386428,0.10851995986204936 ,1,1,1,1,1,1,  0.11603451362295468  ,1,   2.2103651642952493  
                        ,1,1,  0.07495522210303956  ,  0.10354608556104798  ,  0.13760236214531507,1, 0.10182838190503388 , 0.0638755187984818 ,1,0.13234645933185052  ,0.0980862495773461  
                        ,1,1, 0.0638755187984818    ,  0.07495522210303956  ,1,   0.07249971325812514 ,   0.06692687735634881 ,1,  0.07495522210303956  ,  0.07488941806773136  
                        ,  0.1450357522268851   ,  2.886580997484062    ,   0.06692687735634881 ,  0.07233927322455891  ,1,1,  0.07233927322455891  ,   0.06692687735634881 ,  1.691540419442685    
                        ,1,  0.07495522210303956  ,   0.10084757571640045 ,  0.12819399259616576  ,   0.06692687735634881 ,1,  0.11256101042993358  , 0.0638755187984818    ,0.098740368853842      
                        ,  0.07495522210303956  ,  0.10067390033281028  ,  0.10432764319616272  ,   3.102532120500129   ,  0.07233927322455891  ,   0.07249971325812514 ,  2.8870653334366567   
                        ,0.06692687735634881 ,1, 0.0638755187984818    ,  0.07233927322455891  ,1,   0.06692687735634881 ,1,1};
Double_t strip[128];

void Chn_thr(){

for(int i=0; i<128; i++){

                switch (i){
			
	            case(0)  : strip[i] = 111; break;
	            case(1)  : strip[i] = 61; break;
	            case(2)  : strip[i] = 109 ; break;
                case(3)  : strip[i] = 37; break;
                case(4)  : strip[i] = 68; break;
                case(5)  : strip[i] = 31 ; break;
	            case(6)  : strip[i] = 65; break;
                case(7)  : strip[i] = 36; break;
                case(8)  : strip[i] = 72; break;
                case(9)  : strip[i] = 33; break;
	            case(10) : strip[i] = 69; break;
                case(11) : strip[i] = 49; break;
                case(12) : strip[i] = 66; break;
                case(13) : strip[i] = 35; break;
                case(14) : strip[i] = 117; break;
                case(15) : strip[i] = 57; break;
                case(16) : strip[i] = 113;break;
                case(17) : strip[i] = 47; break;
	            case(18) : strip[i] = 114;break;
                case(19) : strip[i] = 56; break;
                case(20) : strip[i] = 106; break;
                case(21) : strip[i] = 71; break;
                case(22) : strip[i] = 108; break;
                case(23) : strip[i] = 68; break;
                case(24) : strip[i] = 107; break;
                case(25) : strip[i] = 53; break;
                case(26) : strip[i] = 104; break;
                case(27) : strip[i] = 51; break;
                case(28) : strip[i] = 105; break;
                case(29) : strip[i] = 60; break;
                case(30) : strip[i] = 116;break;
                case(31) : strip[i] = 59; break;
                case(32) : strip[i] = 38; break;
                case(33) : strip[i] = 64; break;
                case(34) : strip[i] = 39; break;
                case(35) : strip[i] = 62; break;
	            case(36) : strip[i] = 112; break;
	            case(37) : strip[i] = 48;  break;
	            case(38) : strip[i] = 115; break;
                case(39) : strip[i] = 55; break;    
                case(40) : strip[i] = 120; break;     
                case(41) : strip[i] = 63; break;      
                case(42) : strip[i] = 32;break;    
                case(43) : strip[i] = 43; break;
                case(44) : strip[i] = 41; break;
                case(45) : strip[i] = 123; break;
                case(46) : strip[i] = 40; break;
                case(47) : strip[i] = 70; break;
                case(48) : strip[i] = 110; break;
                case(49) : strip[i] = 58; break;
                case(50) : strip[i] = 122; break;
                case(51) : strip[i] = 50; break;
                case(52) : strip[i] = 121; break;
                case(53) : strip[i] = 46; break;
                case(54) : strip[i] = 45; break;
                case(55) : strip[i] = 54; break;
                case(56) : strip[i] = 42; break;
                case(57) : strip[i] = 124; break;
                case(58) : strip[i] = 34; break;
                case(59) : strip[i] = 44; break;
                case(60) : strip[i] = 52; break;
                case(61) : strip[i] = 119; break;
	            case(62) : break;
                case(63) : break;
                case(64) : strip[i]= 83; break;            
                case(65) : strip[i]= 14; break;            
                case(66) : strip[i]= 21; break;            
                case(67) : strip[i]= 73; break;            
                case(68) : strip[i]= 76; break;            
                case(69) : strip[i]= 26; break;            
                case(70) : strip[i]= 9; break;           
                case(71) : strip[i]= 13 ; break;       
                case(72) : strip[i]= 24; break;            
                case(73) : strip[i]= 10 ; break;       
                case(74):  strip[i]= 25 ; break;       
                case(75):  strip[i]= 74 ; break;       
                case(76):  strip[i]= 77 ; break;       
                case(77):  strip[i]= 16 ; break;       
                case(78):  strip[i]= 81 ; break;       
                case(79):  strip[i]= 80 ; break;       
                case(80):  strip[i]= 89 ; break;       
                case(81):  strip[i]= 22 ; break;       
                case(82):  strip[i]= 28 ; break;       
                case(83):  strip[i]= 79 ; break;       
                case(84):  strip[i]= 88 ; break;       
                case(85):  strip[i]= 23 ; break;       
                case(86):  strip[i]= 75 ; break;       
                case(87):  strip[i]= 78 ; break;       
                case(88):  strip[i]= 27 ; break;       
                case(89):  strip[i]= 11 ; break;       
                case(90):  strip[i]= 84 ; break;       
                case(91):  strip[i]= 15 ; break;       
                case(92):  strip[i]= 90 ; break;       
                case(93):  strip[i]= 12 ; break;       
                case(94):  strip[i]= 29 ; break;       
                case(95):  strip[i]= 17 ; break;       
                case(96):  strip[i]= 30 ; break;       
                case(97):  strip[i]= 6  ; break;      
                case(98):  strip[i]= 102; break;        
                case(99):  strip[i]= 18 ; break;       
                case(100): strip[i]= 101; break;        
                case(101): strip[i]= 8  ; break;      
                case(102): strip[i]= 103; break;        
                case(103): strip[i]= 7  ; break;      
                case(104): strip[i]= 97 ; break;       
                case(105): strip[i]= 4  ; break;      
                case(106): strip[i]= 100; break;        
                case(107): strip[i]= 5  ; break;      
                case(108): strip[i]= 99 ; break;       
                case(109): strip[i]= 1  ; break;      
                case(110): strip[i]= 96 ; break;       
                case(111): strip[i]= 2  ; break;      
                case(112): strip[i]= 98 ; break;       
                case(113): strip[i]= 85 ; break;       
                case(114): strip[i]= 93 ; break;       
                case(115): strip[i]= 87 ; break;       
                case(116): strip[i]= 94 ; break;       
                case(117): strip[i]= 20 ; break;       
                case(118): strip[i]= 3  ; break;      
                case(119): strip[i]= 86 ; break;       
                case(120): strip[i]= 92 ; break;       
                case(121): strip[i]= 19 ; break;       
                case(122): strip[i]= 95 ; break;       
                case(123): strip[i]= 91 ; break;       
                case(124): strip[i]= 82 ; break;       
                case(125): strip[i]= 118; break;        
                case(126): break;	
                case(127): break;	
            }

}

TCanvas *cThrs = new TCanvas("cThrs","cThrs");
TMultiGraph *mTHR_T0 = new TMultiGraph("thresholds",Form("thresholds;strip;thr [bin]"));

TGraphErrors *gTHR_TBranch = new TGraphErrors(126,strip,thr_TBranch,0,err_thr_TBranch);
gTHR_TBranch -> SetMarkerStyle(20);
gTHR_TBranch -> SetMarkerColor(1);
gTHR_TBranch ->SetTitle("TBranch");

TGraphErrors *gTHR_EBranch = new TGraphErrors(126,strip,thr_EBranch,0,err_thr_EBranch);
gTHR_EBranch -> SetMarkerStyle(20);
gTHR_EBranch -> SetMarkerColor(2);
gTHR_EBranch ->SetTitle("EBranch");

mTHR_T0->Add(gTHR_TBranch);
mTHR_T0->Add(gTHR_EBranch);

mTHR_T0->Draw("AP");
cThrs ->BuildLegend();

}