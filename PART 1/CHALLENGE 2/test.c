#include <stdio.h>
#include <string.h>
typedef char str[20];
int main()
{
	str word = "JAMIEorig";
	str space = "";
	
//	strcat (word,end);
	word[strlen(word)-4] = '\0';
		
	printf ("%s",word);
}
