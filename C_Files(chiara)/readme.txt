// ------------ TB@CERN 07/2021 data evaluation ----------- // 


Time value calculated by :

        timeVal = framenum/3 * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9; //s 

where 65536 = max_Tcoarse value. The reason why framenum is divided by 3 follows:

Framecounts strings has different mode = "HB: " so we use this to identify framecount strings. There is a sequence of 6 framecount strings one for each tiger (0-5) 
        if (mode == "HB:"){  
            
            inFile.ignore(256, '\n'); //ingoring the line there is a problem that joints two lines 
            tcoarse = prev_tcoarse;
//debug
            //cout << "---------------- frame number ---------> " << framenum/3 << endl; //so dividing framenum by 3 it should be correct 

            framenum ++;
        }


            timeVal = framenum/3 * 204.8e-6 + tcoarse * 6.25e-9; //s
                
        if(prev_tcoarse - tcoarse > 20000 && framenum == prev_framenum){ 
//debug
            //cout << "---------------------->tcoarse roll over " << endl;
            timeVal = framenum/3 * 204.8e-6 + tcoarse * 6.25e-9 + 65536*6.25e-9;
        }

