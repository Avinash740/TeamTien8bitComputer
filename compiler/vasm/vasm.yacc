
/* YACC grammar rules for vasm						*/

%{
#include <stdio.h>
#include "gvars.h"		/* declaration of global variables	*/

int	temp1;		/* temp used to add some implicit ops		*/
int	temp2;		/* temp used to add some implicit ops		*/
char	temp_str[80];	/* temp string used for conversions		*/
int	j;		/* loop counter					*/
int	lc = 0;		/* location counter--# bytes for this instr	*/

%}

/* start of definitions							*/

%start	stmt_list

/* tokens and values returned by lexical analyzer			*/

%token	ADD			/* yylval = NONE			*/
%token	AND			/* yylval = NONE			*/
%token	BRANCH			/* yylval = branch condition		*/
%token	CMP			/* yylval = NONE			*/
%token	HLT			/* yylval = NONE			*/
%token	JMP			/* yylval = NONE			*/
%token	JMPL			/* yylval = NONE			*/
%token	LD			/* yylval = NONE			*/
%token	LDI			/* yylval = NONE			*/
%token	LDX			/* yylval = NONE			*/
%token	MOV			/* yylval = NONE			*/
%token	NOP			/* yylval = NONE			*/
%token	NOT			/* yylval = NONE			*/
%token	OR			/* yylval = NONE			*/
%token  XOR                     /* yylval = NONE                        */
%token	ST			/* yylval = NONE			*/
%token	STX			/* yylval = NONE			*/
%token	SUB			/* yylval = NONE			*/
%token	IDENTIFIER		/* yylval = pointer into symbol table	*/
%token	NUMBER			/* yylval = pointer into symbol table	*/
%token	REG_NUM			/* yylval = pointer into symbol table	*/
%token	DOT_WORD		/* yylval = NONE			*/
%token	DOT_BYTE		/* yylval = NONE			*/
%token	DOT_ALLOC		/* yylval = NONE			*/
%token	DOT_ORG			/* yylval = NONE			*/
%token	DOT_EQU			/* yylval = NONE			*/




/* start of rules section						*/
%%

stmt_list :	stmt
	|	stmt_list stmt
	;

stmt	:	ADD	reg ',' reg ',' reg
			{
			add_stmt(ADD_OP,ADD_CODE,$2,$4,$6,REG_TYPE,WORD_SIZE);
			}
	|	ADD	reg ',' reg ',' '#' expr
			{
			add_stmt(ADD_OP,ADD_CODE,$2,$4,$7,IMMEDIATE,WORD_SIZE);
			}
	|	AND	reg ',' reg ',' reg
			{
			add_stmt(AND_OP,AND_CODE,$2,$4,$6,REG_TYPE,WORD_SIZE);
			}
	|	AND	reg ',' reg ',' '#' expr
			{
			add_stmt(AND_OP,AND_CODE,$2,$4,$7,IMMEDIATE,WORD_SIZE);
			}
	|	BRANCH	IDENTIFIER
			{
			add_stmt(BRANCH_OP,BXX_CODE,$2,zero_ptr,zero_ptr,$1,WORD_SIZE);
			}
	|	CMP	reg ',' reg
			{
			add_stmt(CMP_OP,CMP_CODE,$2,$4,zero_ptr,REG_TYPE,WORD_SIZE);
			}
	|	CMP	reg ',' '#' expr
			{
			add_stmt(CMP_OP,CMP_CODE,$2,$5,zero_ptr,IMMEDIATE,WORD_SIZE);
			}
	|	HLT
			{
			add_stmt(HLT_OP,HLT_CODE,zero_ptr,zero_ptr,zero_ptr,REG_TYPE,WORD_SIZE);
			}
	|	JMP	reg
			{
			add_stmt(JMP_OP,JMP_CODE,$2,zero_ptr,zero_ptr,REG_TYPE,WORD_SIZE);
			}
	|	JMP	reg ',' '#' expr
			{
			add_stmt(JMP_OP,JMP_CODE,$2,$5,zero_ptr,IMMEDIATE,WORD_SIZE);
			}
	|	JMPL	reg ',' reg
			{
			add_stmt(JMPL_OP,JMP_CODE,$2,$4,zero_ptr,REG_TYPE,WORD_SIZE);
			}
	|	JMPL	reg ',' reg ',' '#' expr
			{
			add_stmt(JMPL_OP,JMP_CODE,$2,$4,$7,IMMEDIATE,WORD_SIZE);
			}
	|	LD	reg ',' IDENTIFIER
			{
			add_stmt(LD_OP,LD_CODE,$2,$4,zero_ptr,IMMEDIATE,WORD_SIZE);
			}
	|	LDI	reg ',' '#' expr
			{
			add_stmt(LDI_OP,LDI_CODE,$2,$5,zero_ptr,IMMEDIATE,WORD_SIZE);
			}
	|	LDX	reg ',' reg
			{
			add_stmt(LDX_OP,LDX_CODE,$2,$4,zero_ptr,REG_TYPE,WORD_SIZE);
			}
	|	LDX	reg ',' reg ',' '#' expr
			{
			add_stmt(LDX_OP,LDX_CODE,$2,$4,$7,IMMEDIATE,WORD_SIZE);
			}
	|	MOV	reg ',' reg
			{
			add_stmt(MOV_OP,ADD_CODE,$2,$4,zero_ptr,REG_TYPE,WORD_SIZE);
			}
	|	NOP
			{
			add_stmt(NOP_OP,NOP_CODE,zero_ptr,zero_ptr,zero_ptr,REG_TYPE,WORD_SIZE);
			}
	|	NOT	reg ',' reg
			{
			add_stmt(NOT_OP,NOT_CODE,$2,$4,zero_ptr,REG_TYPE,WORD_SIZE);
			}
	|	OR	reg ',' reg ',' reg
			{
			add_stmt(OR_OP,OR_CODE,$2,$4,$6,REG_TYPE,WORD_SIZE);
			}
	|	OR	reg ',' reg ',' '#' expr
			{
			add_stmt(OR_OP,OR_CODE,$2,$4,$7,IMMEDIATE,WORD_SIZE);
			}
       |	ST	IDENTIFIER ',' reg
			{
			add_stmt(ST_OP,ST_CODE,$2,$4,zero_ptr,IMMEDIATE,WORD_SIZE);
			}
	|	STX	reg ',' reg
			{
			add_stmt(STX_OP,STX_CODE,$4,$2,zero_ptr,REG_TYPE,WORD_SIZE);
			}
	|	STX	reg ',' '#' expr ',' reg
			{
			add_stmt(STX_OP,STX_CODE,$7,$2,$5,IMMEDIATE,WORD_SIZE);
			}
	|	SUB	reg ',' reg ',' reg
			{
			add_stmt(SUB_OP,SUB_CODE,$2,$4,$6,REG_TYPE,WORD_SIZE);
			}
	|	SUB	reg ',' reg ',' '#' expr
			{
			add_stmt(SUB_OP,SUB_CODE,$2,$4,$7,IMMEDIATE,WORD_SIZE);
			}
	|	DOT_ALLOC expr
			{
			add_stmt(DOT_ALLOC_OP,0,$2,zero_ptr,zero_ptr,PSEUDO_OP,sym_table[$2].value);
			}
	|	DOT_WORD expr
			{
			add_stmt(DOT_WORD_OP,0,$2,zero_ptr,zero_ptr,PSEUDO_OP,4);
			}
	|	DOT_BYTE expr
			{
			add_stmt(DOT_BYTE_OP,0,$2,zero_ptr,zero_ptr,PSEUDO_OP,1);
			}
	|	DOT_ORG expr
			{
			add_stmt(DOT_ORG_OP,0,$2,zero_ptr,zero_ptr,PSEUDO_OP,0);
			}
	|	label
			{
			$$ = $1;
			}
	|	equ_stmt
			{
			$$ = $1;
			}
	|	error
			{
			sprintf(err_msg,"Syntax error near line #%d\n",curr_line);
			err_exit(err_msg,PARSE_ABORT);
			}
        |	XOR	reg ',' reg ',' reg
			{
			add_stmt(XOR_OP,XOR_CODE,$2,$4,$6,REG_TYPE,WORD_SIZE);
			}
	|	XOR	reg ',' reg ',' '#' expr
			{
			add_stmt(XOR_OP,XOR_CODE,$2,$4,$7,IMMEDIATE,WORD_SIZE);
			}
	;

equ_stmt:	IDENTIFIER DOT_EQU NUMBER
			{
			/* equate a value with a label			*/
			sym_table[$1].value = sym_table[$3].value;
			$$ = $1;
			}
	;

label	:	IDENTIFIER ':'
			{
			/* The value of a label is simply the current
			   value of the location counter.		*/
			sym_table[$1].value = lc;
			$$ = $1;
			}
	;

value	:	NUMBER
			{
			$$ = $1;
			}
	|	equ_stmt
			{
			$$ = $1;
			}
	|	label
			{
			$$ = $1;
			}
	|	IDENTIFIER
			{
			$$ = $1;
			}
	;

/* This provides a very simple form of expression evaluation at
assembly time.  Note, however, that all values (e.g. labels) must
be defined before they can be used in an expression.  This simple
approach does not allow foward references in expression evaluations! */

expr	:	value
			{
			$$ = $1;
			}
	|	'+' value
			{
			$$ = $2;
			}
	|	'-' value
			{
			temp1 = 0 - sym_table[$2].value;
			sprintf(temp_str,"%d",temp1);
			temp2 = add_symbol(temp_str);
			sym_table[temp2].value = temp1;
			$$ = temp2;
			}
	|	expr '+' value
			{
			temp1 = sym_table[$1].value + sym_table[$3].value;
			sprintf(temp_str,"%d",temp1);
			temp2 = add_symbol(temp_str);
			sym_table[temp2].value = temp1;
			$$ = temp2;
			}
	|	expr '-' value
			{
			temp1 = sym_table[$1].value - sym_table[$3].value;
			sprintf(temp_str,"%d",temp1);
			temp2 = add_symbol(temp_str);
			sym_table[temp2].value = temp1;
			$$ = temp2;
			}
	;


reg	:	REG_NUM
			{$$ = $1;	}
	;



/* start of programs section						*/
%%

/* add opcode, operands, etc. to current statement			*/
add_stmt(operation,code,o1,o2,o3,misc,n)
int	operation;	/* type of operation, e.g. ADD, JMPL		*/
int	code;	/* the opcode that will appear in the object file	*/
int	o1;	/* pointer into sym_table[] for operand 1		*/
int	o2;	/* pointer into sym_table[] for operand 2		*/
int	o3;	/* pointer into sym_table[] for operand 3		*/
int	misc;	/* misc info for this instruction			*/
int	n;	/* number of bytes for this instr			*/
{
	stmt[curr_stmt].op_type = operation;
	stmt[curr_stmt].op_code = code;
	stmt[curr_stmt].op1 = o1;
	stmt[curr_stmt].op2 = o2;
	stmt[curr_stmt].op3 = o3;
	stmt[curr_stmt].misc = misc;
	stmt[curr_stmt].line_num = curr_line;

	/* update lc by appropriate number of bytes, or jam it to the
	   value specified in the .org statement			*/
	if (operation == DOT_ORG_OP)
		lc = sym_table[o1].value;
	else	lc += n;

	curr_stmt++;
	if (curr_stmt >= MAX_ISTMT)
		err_exit("Too many input statements",STMT_OFLW);
}





#include "lex.yy.c"		/* source for lexical analyzer		*/




