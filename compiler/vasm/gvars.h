

/* declaration of global variables, constants, etc.			*/

/* List all of the operations visible to the assembler.	  These are
defined for the convenience of the assembler.				*/
#define  ADD_OP		0
#define  AND_OP		1
#define  BRANCH_OP	2
#define  CMP_OP		3
#define  HLT_OP		4
#define  JMP_OP		5
#define  JMPL_OP	6
#define  LD_OP		7
#define  LDI_OP		8
#define  LDX_OP		9
#define  MOV_OP		10
#define  NOP_OP		11
#define  NOT_OP		12
#define  OR_OP		13
#define  ST_OP		14
#define  STX_OP		15
#define  SUB_OP		16
#define  DOT_WORD_OP	17
#define  DOT_BYTE_OP	18
#define  DOT_ALLOC_OP	19
#define  DOT_ORG_OP	20
#define  XOR_OP         21

/* Define all of the op-code values.  Note that there are fewer
op-codes than there are operations visible to the assembler.  These
are the values that will actually appear in the object code file.	*/
#define	NOP_CODE	0
#define	ADD_CODE	1
#define	SUB_CODE	2
#define	OR_CODE		3
#define	AND_CODE	4
#define	NOT_CODE	5
#define XOR_CODE	6
#define	CMP_CODE	7
#define	BXX_CODE	8
#define	JMP_CODE	9
#define	LD_CODE		10
#define	LDI_CODE	11
#define	LDX_CODE	12
#define	ST_CODE		13
#define	STX_CODE	14
#define	HLT_CODE	31

/* Define all of the possible branch conditions.  Stored in stmt[].misc	*/
#define	BRA_COND	0
#define	BNV_COND	8
#define	BCC_COND	1
#define	BCS_COND	9
#define	BVC_COND	2
#define	BVS_COND	10
#define	BEQ_COND	3
#define	BNE_COND	11
#define	BGE_COND	4
#define	BLT_COND	12
#define	BGT_COND	5
#define	BLE_COND	13
#define	BPL_COND	6
#define	BMI_COND	14

/* error exit abort codes						*/
#define	PARSE_ABORT	1	/* unrecoverable parser error		*/
#define	SYM_TABLE_OFLW	2	/* overflow of symbol table		*/
#define	NAME_LEN_OFLW	3	/* too many characters in a symbol	*/
#define	BAD_REG_TYPE	4	/* bad register type in lexical analysis*/
#define STMT_OFLW	5	/* too many statements in input		*/
#define BAD_TARGET	6	/* undefined target address of branch	*/
#define	BAD_OPTION	7	/* illegal command line option		*/
#define	FILE_ERROR	9	/* error opening a file			*/
#define	BAD_SYM_TYPE	10	/* invalid type in symbol table		*/
#define	BAD_OPTYPE	11	/* wrong operation type specified	*/

/* define some useful macros						*/
#define	max(A, B) ((A) > (B) ? (A) : (B))
#define	min(A, B) ((A) < (B) ? (A) : (B))

/* miscellaneous constants						*/
#define	INFINITY	(1<<30)	/* biggest positive number expected	*/
#define	NONE		0	/* yylval for tokens without a value	*/
#define	NULL_PTR	-1	/* null pointer for symbol table lists	*/
#define	UN_INIT_LABEL	-1	/* uninitialized labels			*/
#define	YES		1
#define	NO		0
#define	MAX_HASH_TABLE	60013	/* hash_table size, should be prime	*/
#define	MAX_SYM_TABLE	20000	/* sym_table size			*/
#define	MAX_NAME_LEN	128	/* maximum # chars allowed in a name	*/
#define	MAX_ISTMT	17000	/* maximum number of input statements	*/
#define	WORD_SIZE	4	/* bytes per word			*/

/* command line options flags						*/
int	q_flag;
int	s_flag;

/* global variables							*/

int	zero_ptr;	/* pointer into sym_table[] for 0 value		*/
int	curr_line;	/* current source code line number being read in */
int	curr_stmt;	/* current location counter			*/
char	objfile[80];	/* write the object code to this file		*/
char	err_msg[80];	/* used to pass error to err_exit routine	*/

/* symbol table structures						*/
int	next_free_ptr;	/* points to next available slot in sym_table[]	*/
int	hash_table[MAX_HASH_TABLE];	/* points into sym_table[]	*/
struct	{
	char	name[MAX_NAME_LEN];	/* the symbol itself		*/
	int	value;		/* mem addr, reg #, constant value, etc	*/
	int	link;		/* points to next symbol in this chain	*/
	}	sym_table[MAX_SYM_TABLE];

/* structure for holding statement quadruples				*/
struct	{
	int	op_type;	/* type of operation, e.g. ADD, JMPL	*/
	int	op_code;	/* op-code that will appear in object file */
	int	op1;		/* pointer to sym_table[] for operand 1	*/
	int	op2;		/* pointer to sym_table[] for operand 2	*/
	int	op3;		/* pointer to sym_table[] for operand 3	*/
	int	misc;		/* is src2 a REG_TYPE or IMMEDIATE	*/
	int	line_num;	/* input source line number for this stmt
				   the type of branch condition		*/
	}	stmt[MAX_ISTMT];

/* The type fields for stmt[].misc					*/
#define	NO_TYPE		0
#define	REG_TYPE	1
#define	IMMEDIATE	2
#define	PSEUDO_OP	3

