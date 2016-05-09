/*
 *	Message routines
 */

#include <stdio.h>

#define	VARARG fmt, v1, v2, v3, v4, v5
#define VARPARM (VARARG) char *fmt;

extern FILE *yyerfp;
extern bool err;

				/*VARARGS1*/
void message VARPARM
{
	yywhere();
	fprintf(yyerfp, VARARG);
	fputc('\n', yyerfp);
}


				/*VARARGS1*/
void error VARPARM
{
	extern int yynerrs;
	
	fprintf(yyerfp, "[error] ");
	message(VARARG);
	err = true;
}


				/*VARARGS1*/
void warning VARPARM
{
	fputs("[warning] ", yyerfp);
	message(VARARG);
}


				/*VARARGS1*/
void fatal VARPARM
{
	fputs("[fatal error] ", yyerfp);
	message(VARARG);
	exit(1);
}


				/*VARARGS1*/
void bug VARPARM
{
	fputs("BUG: ", yyerfp);
	message(VARARG);
	exit(1);
}


char *strsave(const char *s)
{
	char *cp = (char *)calloc(strlen(s)+1, 1);
	
	if (!cp)
	{
		fatal("No more room to save strings.");
	}
	strcpy(cp, s);
	return cp;
}
