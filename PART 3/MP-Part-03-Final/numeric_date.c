//
// numeric_date.c
//

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
numeric_date(const char *str_date)
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
   
