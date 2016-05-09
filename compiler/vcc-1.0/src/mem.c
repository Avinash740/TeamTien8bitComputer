/*
 *	sample c -- memory allocation functions
 */
 
#include "mem.h"
#include "heap.h"
#include "machine.h"


int	g_offset = 0;
int	st_offset = 0;
int	l_offset = 0;
int 	l_max;


void all_var(struct symtab *symbol, int init)
{
	symbol = make_var(symbol);
	
	/* if not in parameter region, assign suitable offset */
	switch (symbol->s_blknum)
	{
		case 2:
			break;
		case 1:
			symbol->scope_offset = g_offset++;
			break;
		case 0:
			bug("all_var");
			break;
		default:	/* local region */
			symbol->stack_offset = st_offset++;
			symbol->scope_offset = l_offset++;
			if (symbol->scope_offset < kNumLocRegs)
			{
				symbol->loaded = true;
				RegisterSymbol(symbol);
			}
			break;
	}
	symbol->init_val = init;
}


void all_array(struct symtab *symbol, const int dim)
{
	extern struct symtab *heapVars;
	
	all_var(symbol, dim);
	symbol->s_type = ARRAY;
	
	symbol->heapList = heapVars;
	heapVars = symbol;
}


void	all_program()
{
	blk_pop();
	
#ifdef TRACE
	message("global region has %d word(s)", g_offset);
#endif
}


void	all_func(struct symtab *symbol)
{
	blk_pop();
	
#ifdef TRACE
	message("local region has %d word(s)", l_max);
#endif
}


void	all_parm(struct symtab *symbol)
{
	int p_offset = 0;
	while (symbol)
	{
		symbol->scope_offset = p_offset++;
		symbol->stack_offset = st_offset++;
		
		if (symbol->scope_offset < kNumParamRegs)
		{
			symbol->loaded = true;
			RegisterSymbol(symbol);
		}
		
		symbol = symbol->s_plist;
	}
	
#ifdef TRACE
	message("parameter region has %d word(s)", p_offset);
#endif
}
