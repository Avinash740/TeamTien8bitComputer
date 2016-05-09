/* initialization routines for vasm.c					*/

#include <stdio.h>
#include "gvars.h"
FILE    *yyin,*fopen();

/* read command line arguments						*/
read_args(argc,argv)
int	argc;
char	*argv[];
{
	char	*temp_ptr;	/* temp pointer to char string		*/
	int	i;		/* index counter			*/
	int	temp;		/* temp used to read numeric value	*/

	/* initialize default parameters				*/
	q_flag = NO;
	s_flag = NO;
	sprintf(objfile,"v.out");

	/* read args and change variables as required			*/
	for (i = 1; i < argc; i++)
	  {
	    if (*argv[i] != '-')		/* input file name if it */
		{				/* doesn't start with "-" */
		if ((yyin = fopen(argv[i],"r")) == NULL)
    		  {
    		  sprintf(err_msg,"can't open output file %s",argv[i]);
    		  err_exit(err_msg,FILE_ERROR);
    		  }
		}
	    else {
	      temp_ptr = argv[i] + 1;		/* char after "-"	*/

	      switch (*temp_ptr)
	        {
		  case 'o':
		    sprintf(objfile,"%s",argv[i+1]);
		    i++;
		    break;
		  case 'q':
		    q_flag = YES;
		    break;
		  case 's':
		    s_flag = YES;
		    break;
		  default:
		    printf("-%c:  ",*temp_ptr);
		    err_exit("illegal command line option",BAD_OPTION);
		    break;
	        }
	    }
	  }
}








/* initialize variables							*/

init_vars()
{
	int	i,j;		/* index counter			*/

	/* init global vars						*/
	curr_line = 1;
	curr_stmt = 0;

	/* init stuff for symbol table					*/
	next_free_ptr = 1;	/* location 0 has special significance	*/
	for (i = 0; i < MAX_HASH_TABLE; i++)
		hash_table[i] = NULL_PTR;

	/* add a zero value to the symbol table				*/
	zero_ptr = add_symbol("0");
	/* convert string to actual value                       */
	sscanf(sym_table[zero_ptr].name,"%d",&sym_table[zero_ptr].value);

	/* init some things in each stmt[i].xx, etc. */
	for (i = 0; i < MAX_ISTMT; i++)
		{
		stmt[i].op_type = 0;
		stmt[i].op1 = zero_ptr;
		stmt[i].op2 = zero_ptr;
		stmt[i].op3 = zero_ptr;
		stmt[i].misc = NO_TYPE;
		}
}
