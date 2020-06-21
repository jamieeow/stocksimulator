/*
    Sample program accompanying the supplementary document on MP Testing.
    
    The program will read student data via file processing commands from STUDENTS.txt file.
    Thereafter, it calls Get_Grade() function which answers the following:
   
   		Question: What is the grade of <param_lastname> <param_firstname>?
       	Example: What is the grade of CRUZ JOSE?
    
    The main() function contains a while () loop that tests if Get_Grade() 
	produces the expected correct answer or not.
	
	Compile this program to produce SHAZAM.exe.  Run the exe from the command line as follows:
	
	        D:\CCPROG2> SHAZAM < TEST-DATA.txt
	
	Author: F. R. Salvador
	Date  : 7/14/2019	
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 30
#define FILENAME "STUDENTS.txt"

#include "datastructure.h"   // this file contains the typedef and struct declarations

/*
    Opens the file "STUDENTS.txt", and reads the contents via fscanf() copying it into 
    List which is an array of structures.  Finally, it returns a value corresponds
    to the number of student records that were read from the input text file.
*/
int
Load_Data(struct studentTag List[])
{
	FILE *fp;
	int id;
	String20 lastname;
	String20 firstname;
	float grade;
	
	int i = 0;           // for array indexing
	int nstudents = 0;   // number of students	
	
	fp = fopen(FILENAME, "r");
	
	// read data from the text file
	if (fp != NULL) {
		while ( fscanf(fp, "%d %s %s %f", &id, lastname, firstname, &grade) == 4) {
			List[i].ID = id;
			strcpy(List[i].name.last, lastname);
			strcpy(List[i].name.first, firstname);
			List[i].grade = grade;
			i++;
		}	
		
		fclose (fp);
		nstudents = i;		
	}
	else {
		fprintf(stderr, "ERROR: %s not found, program terminating...\n", FILENAME);
		exit(1);
	}
	
	return nstudents;
}


/*
	Question: What is the grade of <param_lastname> <param_firstname>?
    
    Example: What is the grade of CRUZ JOSE?
    
	Assumption: Both parameters are in upper case.	  	
*/
float
Get_Grade(struct studentTag List[], int nstudents, const char *param_lastname, const char *param_firstname)	
{
	int i;
	
	// search the student whose name matches the parameters lastname and firstname
	for (i = 0; i < nstudents; i++) {
		if ( strcmp(List[i].name.last, param_lastname) == 0 
		     && strcmp(List[i].name.first, param_firstname) == 0) 
		 	return List[i].grade;	// student was found	
	}	
	
	return -1.0;   // -1.0 means no such student found in the list	
}
	

int
main()
{
	struct studentTag List[MAX_SIZE];    // List of students
	int nstudents;                       // actual number of students in the list
    String20 param_lastname, param_firstname;
    float answer;
	  
	nstudents = Load_Data(List);
  
    /*
		The while loop is used for testing the function Get_Grade() with different
		parameter values.  The parameter values will be read via input redirection.		
	*/
	while ( scanf("%s %s", param_lastname, param_firstname) == 2) {	
		answer = Get_Grade(List, nstudents, param_lastname, param_firstname); 
		printf("%s %s %.1f\n", param_lastname, param_firstname, answer);		
	}
			
	return 0;
}


