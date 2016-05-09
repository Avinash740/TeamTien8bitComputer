/*
 *	sample c -- symbol table defion and manipulation
 */
 
#include <stdlib.h>
#include "symtab.h"
#include "machine.h"
#include "parser.tab.h"


extern bool argRgn;

/*
 *	symbol table
 */
 
struct symtab symtab;	/* blind element (?) */
static struct symtab *s_gbl; 	/* global end of chain */
#define s_lcl	(&symtab)	/* local end of chain */

struct symtab *heapVars = NULL;


/*
 *	block table
 */

static int blknum = 0;


extern int byte_count;

/*
 *	Stores the symbol for the current function
 */
struct symtab *currentf;


/*
 *	Adds a new, local entry to the symbol table
 *	for the name given as an argument.  The new entry is
 *	marked as being undeclared.
 */
static struct symtab *s_create(const char *name)
{
	struct symtab *new_entry = 
			(struct symtab *)malloc(sizeof(struct symtab));
	
	if (!new_entry)
	{
		fatal("Out of memory: s_create()\n");
	}
	
	new_entry->s_next = s_lcl->s_next;
	s_lcl->s_next = new_entry;
	new_entry->s_name = strsave(name);
	new_entry->s_type = UDEC;
	new_entry->s_blknum = 0;
	new_entry->s_pnum = NOT_SET;
	new_entry->array = 0;
	return new_entry;
}


/*
 *	Moves the symbol parameter to the bottom of the chain
 */
static void s_move(struct symtab *symbol)
{
	struct symtab *ptr;
	
	/* Find the desired entry in the symtab chain */
	for (ptr = s_lcl; ptr->s_next != symbol; ptr = ptr->s_next)
	{
		if (!ptr->s_next)
			bug("s_move()\n");
	}
	
	/* unlink it from its present position */
	ptr->s_next = symbol->s_next;
	
	/* relink it at global end of symtab */
	s_gbl->s_next = symbol;
	s_gbl = symbol;
	s_gbl->s_next = NULL;
}


/*
 *	Initializes the symbol table list
 */
void	SymtabInit()
{
	blk_push();
	s_gbl = s_create("main");
	s_gbl->s_type = UFUNC;
}


/*
 *	Pushes the block stack
 */
void	blk_push()
{
	++blknum;
}


void	s_lookup(int yylex)
{
	extern	char *yytext;
	
	switch (yylex)
	{
		case Constant:
			yylval.y_str = strsave(yytext);
			break;
		case Identifier:
			if (yylval.y_sym = s_find(yytext))
				break;
			yylval.y_sym = s_create(yytext);
			break;
		default:
			bug("s_lookup()");
	}
}


struct symtab *s_find(const char *name)
{
	struct symtab *ptr;
	
	for (ptr = s_lcl->s_next; ptr; ptr = ptr->s_next)
	{
		if (!ptr->s_name)
		{
			bug("s_find: symbol entry with no name");
		}
		else
		{
			if (strcmp(ptr->s_name, name) == 0)
				return ptr;
		}
	}
	
	/* search failed */
	return NULL;
}


struct symtab *link_parm(struct symtab *symbol, struct symtab *next)
{
	switch (symbol->s_type)
	{
		/* This case should never occur */
		case PARM:
			error("duplicate parameter %s", symbol->s_name);
			return next;
		case FUNC:
		case UFUNC:
		case VAR:
		case ARRAY:
			symbol = s_create(symbol->s_name);
		case UDEC:
			break;
		default:
			bug("link_parm");
			break;
	}
	
	symbol->s_type = PARM;
	symbol->s_blknum = blknum;
	symbol->s_plist = next;
	return symbol;
}


struct symtab *make_parm(struct symtab *symbol)
{
	switch (symbol->s_type)
	{
		case VAR:
		case ARRAY:
			if (symbol->s_blknum == 2)
			{
				error("parameter %s declared twice",
						symbol->s_name);
				return symbol;
			}
			break;
		case UDEC:
		case FUNC:
		case UFUNC:
			error("%s is not a parameter", symbol->s_name);
			symbol = s_create(symbol->s_name);
		case PARM:
			break;
		default:
			bug("make_parm");
	}
	
	if (symbol->array)
	{
		symbol->s_type = ARRAY;
	}
	else
	{
		symbol->s_type = VAR;
	}
	symbol->s_blknum = blknum;
	symbol->s_scope = LOCAL_PTR;
	return symbol;
}


struct symtab *make_var(struct symtab *symbol)
{
	switch (symbol->s_type)
	{
		case VAR:
		case FUNC:
		case UFUNC:
			if (symbol->s_blknum == blknum
			    || symbol->s_blknum == 2 && blknum == 3)
				error("duplicate name %s", symbol->s_name);
			symbol = s_create(symbol->s_name);
		case UDEC:
			break;
		case PARM:
			error("unexpected parameter %s", symbol->s_name);
			break;
		default:
			bug("make_var");
	}
	symbol->s_type = VAR;
	symbol->s_blknum = blknum;
	symbol->loaded = false;
	if (blknum == 1)
	{
		symbol->s_scope = GLOBAL_PTR;
	}
	else
	{
		symbol->s_scope = LOCAL_PTR;
	}
	
	return symbol;
}


struct symtab *make_func(struct symtab *symbol)
{
	switch (symbol->s_type)
	{
		case UFUNC:
		case UDEC:
			break;
		case VAR:
			error("function name %s same as global variable",
				symbol->s_name);
			return symbol;
		case FUNC:
			error("duplicate function definition %s",
				symbol->s_name);
			return symbol;
		default:
			bug("make_func");
	}
	symbol->s_type = FUNC;
	symbol->s_blknum = 1;
	symbol->byte_offset = byte_count;
	return symbol;
}


struct symtab *make_dummy(int r1, int r2)
{
	struct symtab *dummy = (struct symtab *)calloc(sizeof(struct symtab), 1);
	dummy->s_regs[0] = r1;
	dummy->s_regs[1] = r2;
	dummy->loaded = false;
	dummy->s_blknum = 3;
	dummy->scope_offset = 99;
	dummy->s_type = DUMMY;
	
	return dummy;
}



void chk_parm(struct symtab *symbol, int count)
{
	if (symbol->s_pnum == NOT_SET)
	{
		symbol->s_pnum = count;
	}
	else if (symbol->s_pnum != count)
	{
		warning("function %s should have %d argument(s)",
			symbol->s_name, symbol->s_pnum);
	}
}


int count_parms(struct symtab *symbol)
{
	int count = 0;
	
	while (symbol)
	{
		count++;
		symbol = symbol->s_plist;
	}
	return count;
}


void blk_pop()
{
	struct symtab *ptr;
	
	for (ptr = s_lcl->s_next;
		ptr && (ptr->s_blknum >= blknum || ptr->s_blknum == 0);
		ptr = s_lcl->s_next)
	{
		if (!ptr->s_name)
			bug("blk_pop null name");
#ifdef TRACE
		{
			char *type[] = { SYMmap };
			message("Popping %s: %s, depth %d, offset %d",
				ptr->s_name, type[ptr->s_type],
				ptr->s_blknum, ptr->scope_offset);
		}
#endif /* TRACE */
		
		if (ptr->s_type == UFUNC)
			error("undefined function %s", ptr->s_name);
		
		
		free(ptr->s_name);
		s_lcl->s_next = ptr->s_next;
		free(ptr);
	}
	blknum--;
}


void	arrayparam(struct symtab *symbol)
{
	symbol->array = 1;
}


void	chk_var(struct symtab *symbol)
{
	switch (symbol->s_type)
	{
		case UDEC:
			error("undeclared variable %s", symbol->s_name);
			break;
		case PARM:
			error("unexpected parameter %s", symbol->s_name);
			break;
		case FUNC:
		case UFUNC:
			error("function %s used as variable",
				symbol->s_name);
			return;
		case ARRAY:
			if (!argRgn)
			{
				warning("array %s used as a scalar variable",
					symbol->s_name);
			}
		case VAR:
		case DUMMY:
			return;
		default:
			bug("check_var");
	}
	symbol->s_type = VAR;
	symbol->s_blknum = blknum;
}
		

void	chk_func(struct symtab *symbol)
{
	switch (symbol->s_type)
	{
		case UDEC:
			break;
		case PARM:
			error("unexpected parameter %s", symbol->s_name);
			symbol->s_pnum = NOT_SET;
			return;
		case VAR:
			error("variable %s used as function",
				symbol->s_name);
			symbol->s_pnum = NOT_SET;
		case UFUNC:
		case FUNC:
			return;
		default:
			bug("check_func");
	}
	s_move(symbol);
	symbol->s_type = UFUNC;
	symbol->s_blknum = 1;
}


void	chk_array(struct symtab *symbol)
{
	if (symbol->s_type != ARRAY)
		error("%s is not an array", symbol->s_name);
}
