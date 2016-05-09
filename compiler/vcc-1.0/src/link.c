/*
 *	Links function calls to the proper address in memory.
 */
 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#define JMPL "JMPL"

#define kTempFilename	"v.tmp"
#define kMaxLineLen	128



char *readln(char *s, const int n, FILE *file);


int	link_functions(FILE *in, FILE *out)
{
	struct 	symtab *symbol;
	char 	buffer[kMaxLineLen];
	
	
	while (!feof(in))
	{
		readln(buffer, kMaxLineLen, in);
		if (strstr(buffer, JMPL) != NULL)
		{
			char funcName[16];
			
			strcpy(funcName, strchr(buffer, '#') + 1);
			
			buffer[strlen(buffer)-strlen(funcName)] = '\0';
			sscanf(funcName, "%s", funcName);
			symbol = s_find(funcName);
#ifdef TRACE
			printf("Linking to function %s: %d\n", funcName,
					symbol->byte_offset);
#endif
			sprintf(funcName, "%d", symbol->byte_offset);
			strcat(buffer, funcName);
			
		}
		fprintf(out, "%s\n", buffer);
	}
	
	return 0;
}



char 	*readln(char *s, const int n, FILE *infile)
{
	int i, c;
	char dummy[kMaxLineLen];
	
	for (i = 0; i < n && (c = fgetc(infile)) != '\n'; i++)
	{
		if (c == ';')
		{
			fgets(dummy, kMaxLineLen, infile);
			break;
		}
		
		if (feof(infile))
		{
			s[0] = '\0';
			return s;
		}		
		s[i] = (char)c;
	}	
	
	s[i] = '\0';	/* null terminate the string */
	
	
	return s;
}
