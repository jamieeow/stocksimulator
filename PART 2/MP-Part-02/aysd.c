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
    
	int x,y;
	char sample[11] = "11/09/2019";
	
	x = numeric_date(sample);
	y = numeric_date(DS[0].entry[5].date);
	printf ("%d %d", x,y);
	
    
    return 0;
}
