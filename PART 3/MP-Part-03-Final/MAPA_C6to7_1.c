/*

    LASTNAME, FIRSTNAME:  MAPA, JAMIE SHEKINAH
    SECTION:  S11
    CCPROG2 MP Solutions for: Challenges #6 and #7.
	
    Your task is to complete this source code to accomplish the specified 
	programming Challenges correctly.
	
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 	
	Do not edit the following #define.  It denotes the number of PSEI companies. 
*/
#define NUM_COMPANIES  30

/* 
	Do not edit the following #define.  They represent the rates for the different charges.

	You are REQUIRED to use these macros in solving the challenges in this file.
*/
#define COMMISSION_RATE  0.0025 
#define VAT_RATE         0.12       
#define SCCP_RATE        0.0001
#define PSE_RATE         0.00005
#define SALES_TAX_RATE   0.006


/*
*  TO DO #1: Replace the header file LASTNAME_DS.h with your own header file (see Challenge #3).
*
*    LASTNAME_DS.h should contain your Data Structure type definition for the Stock Historical Data
*
*  NOTE: In case there was a problem identified in your solution (see the Canvas comments for 
*        Challenge #3 assessment), then make sure to fix the problem first before solving the
*        challenges in this file.
*/

#include "MAPA_DS.h"  


/*
*  Note: You may or may not use the numeric_date() function included in the following file.
*/
#include "numeric_date.c"
 
/*
*  TO DO #2: Copy/paste your function definition for Initialize_SHD_Data_Structure() 
*            from a previous right after this comment.
*           
*  NOTE: Initialize_SHD_Data_Structure() will be called in main() before calling the functions 
*        for the challenges in this file.
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
    
    
    /* you may declare/use other local variables inside this function */
    
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
               
               
        fclose(fp);
   }    
}  



/*
    NOTE: you may define other functions that you may call in your solution to 
	      Challenge #6 and #7 below this comment.	
*/   



/*
*  TO DO #3: Define the function to accomplish Challenge #6.
* 
*  Question: If an investor/trader bought <number of shares> of stock <code> on <buy date>, 
*            how much should be paid for the different charges?  How much is the Net Amount 
*            be paid by the investor?  Assume that the investor/trader bought the stock using 
*            the average of the OHLC prices.
*
*  Assume that all function parameters are VALID.
*/
void 
Buy_Stock(CDType DS[], int n_shares, const char * stock_code, const char * buy_date)
// note: you may change DS to DS[] if you declared it as an array
{
  	/*
       You are REQUIRED to use the MACRO DEFINITIONs for the RATEs 
	   defined in line numbers 26 to 30.
	*/
	
	float	pShares, grossPrice,
			commission, VAT, fSCCP, 
			fPSE, tCharges, netAmount;
	
	int 	i, 
			stock_index, 
			entry_index;
	
	/*index initialization*/
	
	//look for stock index
	for (i = 0; i < NUM_COMPANIES; i++)
		if ( strcmp(stock_code,DS[i].CompanyName) == 0 )
			stock_index = i;
		
	//look for entry index
	for (i = 0; i < DS[stock_index].nEntries; i++)
		if ( strcmp(buy_date,DS[stock_index].entry[i].date) == 0 )
			entry_index = i;
			
	/*computations*/
	
	pShares =  (DS[stock_index].entry[entry_index].open + 
				DS[stock_index].entry[entry_index].high +
				DS[stock_index].entry[entry_index].low + 
				DS[stock_index].entry[entry_index].close) 
				/ 4;
				
	grossPrice = pShares * n_shares;
	commission = grossPrice * COMMISSION_RATE;
	VAT = commission * VAT_RATE;
	fSCCP = grossPrice * SCCP_RATE;
	fPSE = grossPrice * PSE_RATE;
	tCharges = commission + VAT + fSCCP + fPSE;
	netAmount = grossPrice + tCharges;
	
	/*saving to file*/
	
	//concatenating filename
	string FILENAME;
	strcpy(FILENAME, "BUY_");
	strcat(FILENAME, stock_code);
	strcat(FILENAME, "_");
	int intdate;
	string stringdate;
	intdate = numeric_date(buy_date);
	itoa(intdate, stringdate, 10);
	strcat(FILENAME, stringdate);
	strcat(FILENAME,".txt");
	
	//opening file
	FILE *fp;
	fp = fopen (FILENAME, "w");
	
	fprintf (fp, "DATE: \t %s\n", buy_date);
	fprintf (fp, "STOCK: \t %s\n", stock_code);
	fprintf (fp, "NUMBER_OF_SHARES: \t %d\n", n_shares);	
	fprintf (fp, "PRICE_PER_SHARE: \t %.4f\n", pShares);
	fprintf (fp, "GROSS_PRICE: \t %.4f\n", grossPrice);
	fprintf (fp, "COMMISSION: \t %.4f\n", commission);
	fprintf (fp, "VAT: \t %.4f\n", VAT);
	fprintf (fp, "SCCP_FEE: \t %.4f\n", fSCCP);
	fprintf (fp, "PSE_FEE: \t %.4f\n", fPSE);
	fprintf (fp, "TOTAL_CHARGES: \t %.4f\n", tCharges);
	fprintf (fp, "NET_AMOUNT: \t %.4f\n", netAmount);

	fclose (fp);
	
}



/*
*  TO DO #4: Define the function to accomplish Challenge #7.
* 
*  Question:  If an investor/trader sold <number of shares> of stock <code> on <sell date> 
*             how much should be paid for the different charges?  How much is the Net Amount 
*             be received by the investor?  Assume that the investor/trader sold the stock using 
*             the average of the OHLC prices.
*/
void 
Sell_Stock(CDType DS[], int n_shares, const char * stock_code, const char * sell_date)
// note: you may change DS to DS[] if you declared it as an array
{

  	/*
       You are REQUIRED to use the MACRO DEFINITIONs for the RATEs 
	   defined in line numbers 26 to 30.
	*/
	
	float	pShares, grossPrice,
			commission, VAT, fSCCP, 
			fPSE, tCharges, salesTax, netAmount;
	
	int 	i, 
			stock_index, 
			entry_index;
	
	/*index initialization*/
	
	//look for stock index
	for (i = 0; i < NUM_COMPANIES; i++)
		if ( strcmp(stock_code,DS[i].CompanyName) == 0 )
			stock_index = i;
	//look for entry index
	for (i = 0; i < DS[stock_index].nEntries; i++)
		if ( strcmp(sell_date,DS[stock_index].entry[i].date) == 0 )
			entry_index = i;
	
	/*computations*/
	
	pShares =  (DS[stock_index].entry[entry_index].open + 
				DS[stock_index].entry[entry_index].high +
				DS[stock_index].entry[entry_index].low + 
				DS[stock_index].entry[entry_index].close) 
				/ 4;
				
	grossPrice = pShares * n_shares;
	commission = grossPrice * COMMISSION_RATE;
	VAT = commission * VAT_RATE;
	fSCCP = grossPrice * SCCP_RATE;
	fPSE = grossPrice * PSE_RATE;
	salesTax = grossPrice * SALES_TAX_RATE;
	tCharges = commission + VAT + fSCCP + fPSE + salesTax;
	netAmount = grossPrice + tCharges;
	
	/*saving to file*/
	
	//concatenating filename
	string FILENAME;
	strcpy(FILENAME, "SELL_");
	strcat(FILENAME, stock_code);
	strcat(FILENAME, "_");
	int intdate;
	string stringdate;
	intdate = numeric_date(sell_date);
	itoa(intdate, stringdate, 10);
	strcat(FILENAME, stringdate);
	strcat(FILENAME,".txt");
	
	
	//opening file
	FILE *fp;
	fp = fopen (FILENAME, "w");
	
	fprintf (fp, "DATE: \t %s\n", sell_date);
	fprintf (fp, "STOCK: \t %s\n", stock_code);
	fprintf (fp, "NUMBER_OF_SHARES: \t %d\n", n_shares);	
	fprintf (fp, "PRICE_PER_SHARE: \t %.4f\n", pShares);
	fprintf (fp, "GROSS_PRICE: \t %.4f\n", grossPrice);
	fprintf (fp, "COMMISSION: \t %.4f\n", commission);
	fprintf (fp, "VAT: \t %.4f\n", VAT);
	fprintf (fp, "SCCP_FEE: \t %.4f\n", fSCCP);
	fprintf (fp, "PSE_FEE: \t %.4f\n", fPSE);
	fprintf (fp, "SALES_TAX: \t %.4f\n", salesTax);
	fprintf (fp, "TOTAL_CHARGES: \t %.4f\n", tCharges);
	fprintf (fp, "NET_AMOUNT: \t %.4f\n", netAmount);
	
	fclose (fp);
	
}



/*
*  Fill up the missing codes in the main() function.
*
*  DO NOT add any printf() statement that will execute in your final code.
*/  
int
main()
{
    // DO NOT delete/edit existing variable declarations/definitions 
	int n_shares;        // number of shares to buy/sell
    Symbol stock_code;
	StrDate date;
	char transaction[6]; // string that will contain "BUY" or "SELL"
    // DO NOT add or use other variables

/*
    TO DO #5: declare your own DS (Data Structure)
                 DS is the data structure containing SHD values for 30 companies
                 you are NOT allowed to declare other local variables except DS 
*/    
    CDType DS[30];  // FILL THIS UP!  You should use the name DS, DO NOT use any variable name.
              
    /*
        Note that depending on your solution, DS, may be declared as:
           _datatype_ DS[30];  // if it is an array of 30 elements
           _datatype_ *DS;     // if it is a pointer to some memory space
    */      
    
    // the following is from your solution to Challenge #4
    Initialize_SHD_Data_Structure( DS ); // you may change the parameter DS
	/* 
	   	++++++     MAKE SURE THAT YOU TEST YOUR SOLUTION THOROUGHLY!!!  +++++++
	   
	   	The following is a loop for testing Challenge #6 and #7 solution.  Note that the input 
		values for transaction, n_shares, stock_code, and date will come from test case files 
		supplied via input redirection.  The transaction is either a BUY or a SELL (assumed to
		in all caps).  Make sure to encode VALID values in your own test case files.
		
	  	YOU HAVE TO CREATE YOUR OWN TEST files.  
	  	
	    	Example Run:  D:\CCPROG2> SANTOS_C6to7 < SANTOS_TESTBUYSELL.txt
	
	    The filenames used above are for an example student whose lastname is SANTOS. 
	    
	*/	
	
	while ( scanf("%s %d %s %s", transaction, &n_shares, stock_code, date) == 4 ) {  // DO NOT change this line!		
#if 0
        /*
		    NOTE: you may change the #if 0 to #if 1 to activate the printf() for debugging purposes only.
		    
			      BUT YOU HAVE TO CHANGE IT BACK TO #if 0 BEFORE YOU SUBMIT YOUR FINAL SOLUTION.
		*/
		
		printf("%s %d %s %s\n", transaction, n_shares, stock_code, date);
#endif

		printf("inside while loop\n");
		printf("%s %d %s %s\n", transaction, n_shares, stock_code, date);
		if (strcmp(transaction, "BUY") == 0)  // DO NOT CHANGE THIS LINE
			Buy_Stock(DS, n_shares, stock_code, date);  // you may change the parameter DS only
		else if (strcmp(transaction, "SELL") == 0) // DO NOT CHANGE THIS LINE
		         Sell_Stock(DS, n_shares, stock_code, date); // you may change the parameter DS only		
	} 
    return 0;
}

