/*
 *	sample c -- memory routine declarations
 */
 
#ifndef __MEM__
#define __MEM__

#include "symtab.h"

extern int g_offset;
extern int l_offset;
extern int l_max;

void    all_var(struct symtab *symbol, int init);
void	all_array(struct symtab *symbol, const int dim);
void	all_program();
void	all_func(struct symtab *symbol);
void	all_parm(struct symtab *symbol);

#endif /* __MEM__ */
