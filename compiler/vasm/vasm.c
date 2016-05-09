
/* Program to read in assembler code for the VeSPA processor.

   The command line options are:

   -o filename
   Write the object code to "filename".
   Default = v.out

   -q
   Print the statement quadruples.  Useful for debugging purposes.
   Default = NO.

   -s
   Print the symbol table for debugging purposes.
   Default = NO.

									*/


#include <stdio.h>
#include "gvars.h"		/* declaration of global variables	*/


main(argc,argv)
int	argc;		/* count of command line arguments		*/
char	*argv[];	/* pointers to command line arguments		*/
{
	int	i;		/* index counter			*/
	char	temp[80];	/* temp used for formatting a string	*/

	/* read command line arguments					*/
	read_args(argc,argv);

	/* initialize variables						*/
	init_vars();

	/* parse the input						*/
	if (yyparse() != 0)	/* if unrecoverable error in input	*/
		err_exit("Unrecoverable input error",PARSE_ABORT);
        

	/* generate object code						*/
	sprintf(temp,"%s",objfile);	 /* object file name */
	codegen(temp);

	/* print a header						*/
	printf("%6d lines read\n",curr_line - 1);
	printf("\n\n");

	/* print the statements						*/
	if (q_flag == YES)
		print_stmts(0,curr_stmt-1);

	/* print the symbol table					*/
	if (s_flag == YES)
		print_sym_table(1,next_free_ptr - 1);
}
