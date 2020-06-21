/*
	Program: MP CHALLENGE 1
	Author: MAPA, Jamie Shekinah B.
	Date: 7/19/2019
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char StrDate[11];   // for dates in string format "MM/DD/YYYY", ex. "10/24/2016"
typedef char Symbol[9];     // for stock names,  ex. "EEI", "SMPH","URC"

struct DailyData {
     StrDate date;
     float open, high, low, close;  // OHLC values
     float volume;
};

typedef struct DailyData DDType;

typedef char string[20];
const char * nullify(char date[], int len);

///// MODIFY FILENAME HERE ///
//#define FILENAME "AEVorig"
#define nStocks 30

/*
	-loads file and saves data as DDType entry, into DDType list[]
	-returns number of entries
*/
int 
loadData (DDType list[], string stocks)
{
	FILE *fp;	
	
	StrDate date;
	float open, high, low, close;	//OHLC
	float volume;
	string dump;
	
	int i = 0;           // for array indexing
	
	fp = fopen(strcat(stocks,".txt"), "r");
	
	
	
	// read data from the text file
	if (fp != NULL) {
		
		fgets(dump, 20, fp);
		
		while ( fscanf(fp, "%s %f %f %f %f %f", date, &open, &high, &low, &close, &volume) == 6) {
			strcpy(list[i].date, date); 	//NOT FINAL FORMAT
			list[i].open = open;
			list[i].high = high;
			list[i].low = low;
			list[i].close = close;
			list[i].volume = volume;
//			printf ("test: this part is working \n");
			i++;
		}	
		
		fclose (fp);
	}
	else {
		fprintf(stderr, "ERROR: %s not found, program terminating...\n", stocks);
		exit(1);
	}
	
	return i;
	
}

const char *  fix_format(string dd, string mm, string yyyy){
	char temp, temp1;
	static string format;

//	printf("dd mm yyyy = %s/%s/%s\n",dd,mm,yyyy);
	if (strlen(dd)==1){
		temp = dd[0];
		dd[0] = '0';
		dd[1] = temp;
	}

	if (strlen(mm)==1){
		temp = mm[0];
		mm[0] = '0';
		mm[1] = temp;
//		printf("mm: %s\n", mm);
	}
	if (strlen(yyyy)==2){
		temp = yyyy[0];
		temp1 = yyyy[1];
		yyyy[0] = '2';
		yyyy[1] = '0';
		yyyy[2] = temp;
		yyyy[3] = temp1;
	}
//	printf("maayos ka dapat: %s/%s/%s\n",dd,mm,yyyy);
	format[0] = dd[0];
	format[1] = dd[1];
	format[2] = '/';
	format[3] = mm[0];
	format[4] = mm[1];
	format[5] = '/';
	format[6] = yyyy[0];
	format[7] = yyyy[1];
	format[8] = yyyy[2];
	format[9] = yyyy[3];
//	printf("format: %s\n", format);	
	
	
	return format;
}
const char * nullify(char date[], int len){
	int i;
	static char nullified[2];
	
	for (i=0; i<len; i++)
		nullified[i] = date[i];
	nullified[i] = '\0';
	return nullified;
}

void
formatDate(DDType list[], int nEntries)
{
	int i, j, k, ctr=0;
	int dd_len, mm_len, yyyy_len;
	char dd[2], mm[2], yyyy[4];
//	size_t len = strlen(dd);
	
	for (i = 0; i < nEntries; i++) {
		dd[0] = '\0';
		mm[0] = '\0';
		yyyy[0] = '\0';
		ctr = 0;
		k=0;
		dd_len=0;
		mm_len=0;
		yyyy_len=0;
		for (j=0; j<strlen(list[i].date); j++) {
			if (list[i].date[j] != '/') {				
				if(ctr == 0) {
					dd[k] = list[i].date[j];
					dd_len++;
				}
				else if (ctr == 1) {
					mm[k] = list[i].date[j];
					mm_len++;
				}
				else if (ctr == 2) {
					yyyy[k] = list[i].date[j];
					yyyy_len++;
				}
				k++;
			}
			else {
				ctr++;			
				k=0;
			} 
		}		
		strcpy(dd,nullify(dd, dd_len));
		strcpy(mm, nullify(mm, mm_len));
		strcpy(yyyy, nullify(yyyy, yyyy_len));
//		printf("format date dd mm yyyy = %s/%s/%s\n",dd,mm,yyyy);
		strcpy(list[i].date, fix_format(dd, mm, yyyy));
//		printf("after fix: %s\n", list[i].date);
	}
	
	
}

void
saveFile (DDType list[], int nEntries, string stocks)
{
	FILE *fp;	

	int i;           
	
	//code to remove "orig" concatenation from stocks
	string fName;
	strcpy (fName, stocks);
	fName[strlen(fName)-8] = '\0';
	strcpy(stocks, fName);
	
	fp = fopen(strcat(fName,".txt"), "w+");
	
//	printf("hey look at me im saving files\n");

	fprintf(fp, "%s %d\n\n", stocks, nEntries);
	
	//writes data into new file		
	for (i = 0; i < nEntries; i++)
	{
		//fprintf (fp, "%s", "TEST");
		//PROBLEM SOMEWHERE HERE
		fprintf (fp, "%s %.2f %.2f %.2f %.2f %.2f \n", 
				list[i].date, list[i].open, list[i].high, list[i].low, list[i].close, list[i].volume);
	}
		
	fclose (fp);
	
}

int 
main()
{

	
	DDType list[1215];
	int nEntries;
	
	string stocks[nStocks];
		strcpy (stocks[0], "ACorig");
		strcpy (stocks[1], "AEVorig");
		strcpy (stocks[2], "AGIorig");
		strcpy (stocks[3], "ALIorig");
		strcpy (stocks[4], "APorig");
		strcpy (stocks[5], "BDOorig");
		strcpy (stocks[6], "BLOOMorig");
		strcpy (stocks[7], "BPIorig");
		strcpy (stocks[8], "DMCorig");
		strcpy (stocks[9], "FGENorig");
		strcpy (stocks[10], "GLOorig");
		strcpy (stocks[11], "GTCAPorig");
		strcpy (stocks[12], "ICTorig");
		strcpy (stocks[13], "JFCorig");
		strcpy (stocks[14], "JGSorig");
		strcpy (stocks[15], "LTGorig");
		strcpy (stocks[16], "MBTorig");
		strcpy (stocks[17], "MEGorig");
		strcpy (stocks[18], "MERorig");
		strcpy (stocks[19], "MPIorig");
		strcpy (stocks[20], "PGOLDorig");
		strcpy (stocks[21], "RLCorig");
		strcpy (stocks[22], "RRHIorig");
		strcpy (stocks[23], "SCCorig");
		strcpy (stocks[24], "SECBorig");
		strcpy (stocks[25], "SMCorig");
		strcpy (stocks[26], "SMorig");
		strcpy (stocks[27], "SMPHorig");
		strcpy (stocks[28], "TELorig");
		strcpy (stocks[29], "URCorig");


	int i;
	
	for (i = 0; i < nStocks; i++)
	{
		nEntries = loadData(list, stocks[i]);
		formatDate(list, nEntries);
		saveFile(list, nEntries, stocks[i]);
	}	

//	printf("LIST NUMBER 1215 = %s", list[1214].date);
	return 0;
}

/*

INSTRUCTIONS:

1. The destination files should contain dates in uniform format following MM/DD/YYYY. For example, if the original data is
	“1/1/2014”, then the new date in the destination file should be “01/01/2014”. Another example, if the original date is
	“1/3/18”, then the new date should be “01/03/2018”.

2. The values for OHLC and Volume should be encoded as floating point values with two digits after the decimal point.

*/
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/*

PROBLEMS: 
	-code to format date
	-nEntries is always 0
	-writes nothing to new text files
	
*/
