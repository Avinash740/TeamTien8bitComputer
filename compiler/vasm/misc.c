/* miscellaneous routines for vasm.c					*/

#include <stdio.h>
#include "gvars.h"



/* Print error message and abort					*/

err_exit(msg,code)
char	*msg;		/* message string to print			*/
int	code;		/* exit code					*/
{
	printf("vasm ERROR EXIT:  %s\n",msg);
	exit(code);
}








/* print out all of the statements from the stmt[] structure		*/

print_stmts(first,last)
int	first;		/* start printing with this statement		*/
int	last;		/* stop printing with this statement		*/
{
	int	i;	/* index counter				*/

	printf("\f");		/* go to top of new page		*/
	printf("Statement quadruples\n");
	printf("   stmt   opcode   op1    op2    op3   format_type\n\n");
	for (i = first; i <= last; i++)
		{
		printf("%6d:  %6d  %6d  %6d  %6d  %6d\n",
			i,
			stmt[i].op_type,
			stmt[i].op1,
			stmt[i].op2,
			stmt[i].op3,
			stmt[i].misc);
		}
}








/* print the symbol table						*/

print_sym_table(first,last)
int	first;		/* start printing with this symbol		*/
int	last;		/* stop printing with this symbol		*/
{
	int	i;	/* index counter				*/

	printf("\f");		/* go to top of new page		*/
	printf("Symbol table\n");
	printf("%6s  %-30s  %6s  %6s\n\n",
		"index","name","value","link");
	for (i = first; i <= last; i++)
		{
		printf("%6d  %-30s  %6d  %6d\n",
			i,
			sym_table[i].name,
			sym_table[i].value,
			sym_table[i].link);
		}
}
