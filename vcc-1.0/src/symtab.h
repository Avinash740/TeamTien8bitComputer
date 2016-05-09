/*
 *	sample c -- header file for symbol table
 */
 
#ifndef __SYMTAB__
#define __SYMTAB__


typedef enum
{
	int_lval
} LVal;
	

struct symtab
{
	char	*s_name;	/* name pointer */
	int	s_type;		/* symbol type */
	int	s_blknum;	/* static block depth */
	int	s_scope;	/* symbol scope 	MPT 2003/6/24 */
	char	array;		/* Pointer flag */
	LVal	lval;		/* lval for the symbol */
	
	union
	{
		int s__num;
		int s__dummy[2];
		struct symtab *s__link;
	} s__;
	
	int	scope_offset;	/* symbol definition */
	int	stack_offset;
	struct	symtab *s_next;	/* next entry */
	int	init_val;
	
	union
	{
		bool	in_reg;	/* MPT 2003/6/24 	*/
		int	reg;
		bool	retFlag;
	} stat;
	
	bool	initialized;
	int	used;
	int	byte_offset;	/* Used for locating functions */
	
	/* Only used for arrays */
	struct symtab *heapList;
};


#define	s_pnum	s__.s__num	/* count of parameters */
#define NOT_SET (-1)		/* no count set yet */
#define	s_plist s__.s__link	/* chain of parameters */
#define s_regs s__.s__dummy	/* dummy symbol information */

#define loaded stat.in_reg	/* Is the symbol loaded in a register? */
#define returnSet stat.retFlag 	/* Has the function generated a return? */
#define reg_alloc stat.reg	/* The register the symbol's loaded in */

#define NOT_ALLOC	(-1)

/*
 *	s_type values
 */
 
enum
{
	UDEC = 0,	/* not declared--perhaps deprecated */
	FUNC,		/* function */
	UFUNC,		/* undefined function */
	VAR,		/* declared variable */
	PARM,		/* undeclared parameter */
	ARRAY,		/* An array (pointer) */
	DUMMY		/* Dummy symbol */
};
	
/*
 *	s_type values for S_TRACE
 */
#define	SYMmap	"undeclared", "function", "undefined function", \
		"variable", "parameter", "array", "dummy"
		
		
/*
 *	Current function pointer
 */
extern struct symtab *currentf;

extern int st_offset;


/*
 *	type functions, symbol table module
 */
void		SymtabInit();		/* initializes the table */
struct symtab 	*link_parm(struct symtab *symbol,
			    struct symtab *next);	/* chain parameters */
struct symtab 	*s_find(const char *name);	/* locate symbol by name */
struct symtab 	*make_parm(struct symtab *symbol);	/* declare parameter */
struct symtab 	*make_var(struct symtab *symbol);	/* define variable */
struct symtab 	*make_func(struct symtab *symbol);	/* define function */
struct symtab	*make_dummy(int r1, int r2);

/*
 * Other symbol table functions
 */
void 	blk_push();
void 	blk_pop();
void	arrayparam(struct symtab *symbol);
void 	s_lookup(int yylex);
void 	chk_parm(struct symtab *symbol, int count);
void	chk_var(struct symtab *symbol);
void	chk_func(struct symtab *symbol);
int	count_parms(struct symtab *symbol);


/*
 *	typed library functions
 */

char *strsave(const char *s);		/* dynamically save a string */
/* char *calloc();		...don't think we need to declare this... */

#endif	/* __SYMTAB__ */
