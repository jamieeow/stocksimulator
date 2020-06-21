/*

    LASTNAME, FIRSTNAME:  (indicate your names in capital letters)
    SECTION:  (indicate your section)
    CCPROG2 MP Solutions for: Challenge #4 and #5.  
    
    Your task is to complete this source code to accomplish the specified 
	programming Challenges correctly.
	
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Do not edit the following #define.  It denotes the number of PSEI companies. */
#define NUM_COMPANIES  30

/*
*  TO DO #1: Replace the header file LASTNAME_DS.h with your own header file (see Challenge #3).
*
*    LASTNAME_DS.h should contain your Data Structure type definition for the Stock Historical Data
*
*  NOTE: In case there was a problem identified in your solution (see the Canvas comments for 
*        Challenge #3 assessment), then make sure to fix the problem first before commencing this 
*        Challenge #4 and #5.* 
*/
#include "LASTNAME_DS.h"  


/*
*  Note: You may or may not use this function.  In my own MP solution, I used it to 
*        convert the dates from strings into integers.
*
*  DO NOT CHANGE/EDIT THIS FUNCTION!!!!
*
*  numeric_date() returns the date as an integer in the format: YYYYMMDD
*  
*  Examples:
*    numeric_date("1/2/2017")   returns 20170102
*    numeric_date("12/8/2016")  returns 20161208
*    numeric_date("3/29/2014")  returns 20140329
*    numeric_date("10/23/2015") returns 20151023
*
*/
int 
numeric_date(char *str_date)
{
   int day, month, year;     
   char str[11];      
   int i;
   int ctr;
    
   // Step 1: get the month part from the string  
   strcpy(str, str_date);
   i = 0;
   ctr = 0;
   while (str[i] != '/') {  // find the fist '/'
       i++;
       ctr++;
   }       
   
   str[i] = '\0';   
   month = atoi(str); // capture the month as an integer
   
   
   // get the day part from the string
   ctr++; // move 1 character past '/'
   strcpy(str, str_date + ctr);
   i = 0;
   while (str[i] != '/') { // find the second '/'
      i++;
      ctr++;
   }  
   
   str[i] = '\0';
   day = atoi(str); // capture the day as an integer       
       
   // get the year part from the string
   ctr++;  // move 1 character past '/'
   strcpy(str, str_date + ctr);  
   year = atoi(str);  // capture the year as an integer      

   return year * 10000 + month * 100 + day;   
}
   
   
/*
    NOTE: you may define other functions that you may call in your solution to
          Challenge #4 and #5.
*/   
     


/*
*  TO DO #2: 
*
*  Challenge #4: Load ALL the 30 Text File Values into the Primary Memory.
*   
*  Implement the following function which should: [1] read the SHD from ALL the 30 text files and 
*  [2] load/store them into your data structure (DS) which is in the primary memory.
*
*/
void 
Initialize_SHD_Data_Structure( _datatype_ DS )
// note: you may change DS to DS[] if you declared it as an array
{
    Symbol Codes[30] = { "AC", "AEV", "AGI", "ALI", "AP", "BDO", "BLOOM", "BPI", "DMC", "FGEN", 
	                     "GLO", "GTCAP", "ICT", "JFC", "JGS", "LTG", "MBT", "MEG", "MER", "MPI",    
                         "PGOLD", "RLC", "RRHI", "SCC", "SECB", "SM", "SMC", "SMPH", "TEL", "URC" };

    FILE *fp;
    char filename[51]; 
    int i;
    
    
    // you may declare/use other local variables inside this function */
    
    // this loop will read data from all the 30 text files
    for (i = 0; i < NUM_COMPANIES; i++) {
        strcpy(filename, "SHD\\");   // the 30 text files are in the folder named SHD
        strcat(filename, Codes[i]);
        strcat(filename, ".txt");

        fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "ERROR: File %s not found! Exiting...\n", filename);
            exit(1);
        }

        // read code, number of daily data, and all the daily data for this particular company
        
        /*
        
                    SUPPLY THE MISSING CODES
               
        */             
               
               
        fclose(fp);
   }    
}  


/*
*  TO DO #3: 
*
*  Challenge #5: Display the Daily Data for a Given Stock Code, Start Date and End Date.
*
*  Assume that all actual parameters are correct/valid.  
*/
void 
Print_SHD( _datatype_ DS, const char *stock_code, const char *start_date, const char *end_date )  
// note: you may change DS to DS[] if you declared it as an array
{
         
        // you may declare/use your own local variables inside this function */ 
   
        /*
        
                    SUPPLY THE MISSING CODES
               
        */   
}



/*
*  Fill up the missing codes in the main() function.
* 
*/  
int
main()
{
    // DO NOT delete/edit existing variable declarations/definitions 
    StrDate start_date;
    StrDate end_date;
    Symbol stock_code;

/*
    TO DO #4: declare your own DS (Data Structure)
                 DS is the data structure containing SHD values for 30 companies
                 you are NOT allowed to declare other local variables except DS 
*/    
    _datatype_ DS;  // FILL THIS UP!  You should use the name DS, DO NOT use any variable name.
              
    /*
        Note that depending on your solution, DS, may be declared as:
           _datatype_ DS[30];  // if it is an array of 30 elements
           _datatype_ *DS;     // if it is a pointer to some memory space
    */      
    
    
    // Test Challenge #4 solution
    Initialize_SHD_Data_Structure( DS ); // you may change the parameter DS
     
     
     
	/* 
	   	++++++     MAKE SURE THAT YOU TEST YOUR SOLUTION THOROUGHLY!!!  +++++++
	   
	   	The following is a loop for testing Challenge #5 solution.  Note that the input values 
	   	for stock_code, start_date and end_date will come from test case files, supplied via
	   	input redirection.
	
	  	YOU HAVE TO CREATE YOUR OWN TESTCASE files.  
	  	
	    	Example Run #1:  D:\CCPROG2> SANTOS_C4to5 < SANTOS_TESTCASE1.txt
	
	    	Example Run #2:  D:\CCPROG2> SANTOS_C4to5 < SANTOS_TESTCASE2.txt
	   
	    The filenames used above are for an example student whose lastname is SANTOS. 
	    
		The test file SANTOS_TESTCASE1.txt was supplied to you together with this skeleton file.
		You'll need to create the TESTCASE2.txt file on your own.
	
	*/	
	while ( scanf("%s %s %s", stock_code, start_date, end_date) == 3 ) {   // DO NOT change this line!		
		Print_SHD(DS, stock_code, start_date, end_date); // you may change the parameter DS
		printf("\n\n");		// DO NOT change this line!
	}                
                 
    return 0;
}
