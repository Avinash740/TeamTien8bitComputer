%{
/*
 *	sample c -- lexical analysis
 */


#ifdef DEBUG
	/* Debugging version - if assert ok */
	
#include <assert.h>

int main()
{
	char *p;
	
	assert(sizeof(int) >= sizeof(char *));
	
	while (p = (char *)yylex())
	{
		printf("%-10.10s is \"%s\"\n", p, yytext);
	}
	
	return 0;
}

s_lookup() {}
int yyerrs = 0;

#define token(x)	(int) #x

#else
/* !DEBUG -- production version */

#include "parser.tab.h"
#define  token(x)	x



#endif /* DEBUG */

#define END(v)	(v-1 + sizeof(v) / sizeof(v[0]))
static int screen();


%}

%option yylineno

letter			[a-zA-Z_]
digit			[0-9]
letter_or_digit		[a-zA-Z_0-9]
white_space		[ \t\n\r]
blank			[ \t]
other			.

%%

^"#"{blank}*{digit}+({blank}+.*)?\n	yymark();

">="		return token(GE);
"<="		return token(LE);
"=="		return token(EQ);
"!="		return token(NE);
"+="		return token(PE);
"-="		return token(ME);
"*="		return token(TE);
"/="		return token(DE);
"%="		return token(RE);
"++"		return token(PP);
"--"		return token(MM);

{letter}{letter_or_digit}*	return screen();

{digit}+		{
				s_lookup(token(Constant));
				return token(Constant);
			}

{white_space}+		;
{other}			return token(yytext[0]);

%%

/*
 *	Reserved word screener
 */
static struct rwtable 		/* Reserved word table */
{
	char *rw_name;		/* representation */
	int  rw_yylex;		/* yylex() value */
} rwtable[] = {			/* sorted */
	{"break", token(BREAK)},
	{"continue", token(CONTINUE)},
	{"else", token(ELSE)},
	{"for", token(FOR)},
	{"getc", token(GETC)},
	{"if", token(IF)},
	{"int", token(INT)},
	{"putc", token(PUTC)},
	{"return", token(RETURN)},
	{"void", token(VOID)},
	{"while", token(WHILE)}
};



static int screen()
{
	struct rwtable *low = rwtable;
	struct rwtable *high = END(rwtable);
	struct rwtable *mid;
	
	int c;
	
	while (low <= high)
	{
		mid = low + (high-low)/2;
		if ((c = strcmp(mid->rw_name, yytext)) == 0)
			return mid->rw_yylex;
		else if (c < 0)
			low = mid+1;
		else
			high = mid-1;
	}
	s_lookup(token(Identifier));
	
	return token(Identifier);
}
