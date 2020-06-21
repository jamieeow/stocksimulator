/*

    LASTNAME, FIRSTNAME:  MAPA, JAMIE SHEKINAH 
    SECTION:  S11
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
#include "MAPA_DS.h"  


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
Initialize_SHD_Data_Structure( CDType DS[] )
// note: you may change DS to DS[] if you declared it as an array
{
    Symbol Codes[30] = { "AC", "AEV", "AGI", "ALI", "AP", "BDO", "BLOOM", "BPI", "DMC", "FGEN", 
	                     "GLO", "GTCAP", "ICT", "JFC", "JGS", "LTG", "MBT", "MEG", "MER", "MPI",    
                         "PGOLD", "RLC", "RRHI", "SCC", "SECB", "SM", "SMC", "SMPH", "TEL", "URC" };

    FILE *fp;
    char filename[51]; 
    int i,j;
    
    
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
        
		else {
	
			//company name and entries
			fscanf (fp, "%s %d", DS[i].CompanyName, &DS[i].nEntries); 	
			
			//daily data
			for (j = 0; j < DS[i].nEntries; j++)
			{
//				while ( fscanf(fp, "%s %f %f %f %f %lf", DS[i].entry[i].date, &DS[i].entry[i].open, &DS[i].entry[i].high, 
//														&DS[i].entry[i].low, &DS[i].entry[i].close, &DS[i].entry[i].volume) == 6) 
				{
					//date
					fscanf (fp, "%s", DS[i].entry[j].date);	
					
					fseek (fp, 2, SEEK_CUR);				
						
					//OHLC
					fscanf (fp, "%f", &DS[i].entry[j].open);	
					fscanf (fp, "%f", &DS[i].entry[j].high);
					fscanf (fp, "%f", &DS[i].entry[j].low);
					fscanf (fp, "%f", &DS[i].entry[j].close);
					
					//volume
					fscanf (fp, "%lf", &DS[i].entry[j].volume);
					
					fseek (fp, 2, SEEK_CUR);				
					
				}
			}
		}
               
               
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
Print_SHD( CDType DS[], const char *stock_code, const char *start_date, const char *end_date )  
// note: you may change DS to DS[] if you declared it as an array
{
         
    // you may declare/use your own local variables inside this function */ 

	int i, STOCK_INDEX, START = 0, END = 0;
	
	//loop to find stock code
	for (i = 0; i < NUM_COMPANIES; i++)
		if ( strcmp(DS[i].CompanyName, stock_code) == 0 ) {
			STOCK_INDEX = i;
		}
	
	///////////for checking 
	printf("CHECK STOCK NAME: %s ?= %s\n", DS[STOCK_INDEX].CompanyName, stock_code);
		
	//to find start date and end date
	
	int start_exists = 0, end_exists = 0;
		
	/*
		Loop through all dates to find START and END date indices.
	
		THERE ARE 3 CASES:
			1. The date exists in data
			2. The date exists in data, but is a saturday / holiday (OFFSET BY 1)
			3. The date exists in data, but is a sunday (OFFSET BY 2)
	*/

	for (i = 0; i < DS[STOCK_INDEX].nEntries  && start_exists == 0 ; i++) {	
		if ( numeric_date(DS[STOCK_INDEX].entry[i].date) < numeric_date(start_date) ){
			START = i-1;
			start_exists = 1;
		}
	}
	
	for (i = 0; i < DS[STOCK_INDEX].nEntries && end_exists == 0; i++) {
		if ( numeric_date(DS[STOCK_INDEX].entry[i].date) <= numeric_date(end_date) ){
			END = i;
			end_exists = 1;
		}
	}

	//CHECKING
	printf("\nSTART: %d\n", START);
	printf("END: %d\n", END);
	printf("CHECK START DATE: %s =? %s\n", DS[STOCK_INDEX].entry[START].date, start_date);
	printf("CHECK END DATE: %s =? %s\n\n", DS[STOCK_INDEX].entry[END].date, end_date);
	
	//loop to print daily data from start_date to end_date
	for (i = START; i >= END; i--)
	{
		printf ("%s \t %.2f \t %.2f \t %.2f \t %.2f \t %.2lf \t\n", DS[STOCK_INDEX].entry[i].date, DS[STOCK_INDEX].entry[i].open,
																DS[STOCK_INDEX].entry[i].high, DS[STOCK_INDEX].entry[i].low,
																DS[STOCK_INDEX].entry[i].close, DS[STOCK_INDEX].entry[i].volume);
	}
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


    CDType DS[NUM_COMPANIES];  // FILL THIS UP!  You should use the name DS, DO NOT use any variable name.
              
    /*
        Note that depending on your solution, DS, may be declared as:
           _datatype_ DS[30];  // if it is an array of 30 elements
           _datatype_ *DS;     // if it is a pointer to some memory space
    */      
    
    // Test Challenge #4 solution
    Initialize_SHD_Data_Structure( DS ); // you may change the parameter DS 
    
    ////////////////////////////////////////////////////////////////////////
//	printf("MAY PRINTF DITO HOY NALIMUTAN MO %s %d %.2f %.2f\n", DS[0].CompanyName, DS[0].nEntries, DS[0].entry[100].close, DS[0].entry[100].open);
	//oks so sa scanning talaga yung problem bc it already prints c:
     /////////////////////////////////////////////////////////////////////////
     
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
	
		//test
		Print_SHD(DS, "AC", "01/01/2015", "12/31/2015");
//		Print_SHD(DS, "DMC", "03/10/2017", "03/16/2017");
//		Print_SHD(DS, "GLO", "08/08/2018", "08/08/2018");
		//end of test
	
	while ( scanf("%s %s %s", stock_code, start_date, end_date) == 3 ) {   // DO NOT change this line!		
		Print_SHD(DS, stock_code, start_date, end_date); // you may change the parameter DS
		printf("\n\n");		// DO NOT change this line!
	}                
	
    
    return 0;
}
