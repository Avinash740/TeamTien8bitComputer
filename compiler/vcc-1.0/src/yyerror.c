/*
 *	yywhere() -- input position for yyparse()
 *	yymark() -- get information form '# line file'
 *	yyerror() -- print error information
 */
 
#include <stdio.h>


FILE *yyerfp;		/* Error stream */

extern char *yytext;		/* Current token */
extern int  yyleng;		/* and its length */
extern int  yylineno;		/* current input line number */

static char *source;		/* current input file name */

void yywhere();
void yymark();



void yywhere()
{
	char colon = 0;		/* a flag */
	char *tmp;
	
	tmp = yytext;
	
	if (source && *source && strcmp(source, "\"\""))
	{
		char *cp = source;
		int  len = strlen(source);
		
		if (*cp == '"')
		{
			++cp;
			len -= 2;
		}
		if (strncmp(cp, "./", 2) == 0)
		{
			cp += 2;
			len -= 2;
		}
		
		fprintf(yyerfp, "file %*s", len, cp);
		colon = 1;
	}
	if (yylineno > 0)
	{
		if (colon)
			fputs(", ", yyerfp);
		fprintf(yyerfp, "line %d", 
				yylineno - 
				(*yytext == '\n' || !*yytext));
		colon = 1;
	}
	if (*yytext)
	{
		register int i;
		for (i = 0; i < 20; i++)
		{
			if (!yytext[i] || yytext[i] == '\n')
				break;
		}
			
		if (i)
		{
			if (colon)
				putc(' ', yyerfp);
			fprintf(yyerfp, "near \"%*s\"", i, yytext);
			colon = 1;
		}
	}
	if (colon)
		
		fputs(": ", yyerfp);
}


void yymark()
{
	if (source)
		free(source);
	source = (char *)calloc(yyleng, sizeof(char));
	if (source)
		sscanf(yytext, "# %d %s", &yylineno, source);
}

		
void yyerror(register char *s)
{
	error(s);
}
				
