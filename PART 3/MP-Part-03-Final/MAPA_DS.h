/*

    LASTNAME, FIRSTNAME: MAPA, JAMIE SHEKINAH
    SECTION: S11
    DATE: July 20, 2019
    
    CCPROG2 MP Solution for: Challenge #3  
        
*/


#include "CCPROG2_MP.h"  // DO NOT delete this #include

/*  
  Challenge #2: Design and Code Your Own SHD Data.
  
  Design and code the data structure for representing and storing the stock names and historical data 
  in the primary memory. The following are at your disposal: arrays, strings, and structures.

  Use the pre-declared data types which are encoded in “COMPRO2_MP.h” header file 
  (note: already included above.)
*/


// Encode your own Data Structure after this comment.  


#define nCompanies 30
#define MAX_ENTRIES 1250
typedef char string[50];

struct 
CompanyData {
	int nEntries;
	string CompanyName;
	DDType entry [MAX_ENTRIES];	
};
typedef struct CompanyData CDType;
	
//#define	CDType company [nCompanies]
	
