/*
 *	Operations for VeSPA processor architecture
 */
 
#ifndef __VESPA_GEN__
#define __VESPA_GEN__

#include "symtab.h"
#include "machine.h"
			

enum
{
	kInput,
	kOutput
};
	
	
int 	sym_reg(struct symtab *symbol);
void	RegisterSymbol(struct symtab *s);
void	write_header(void);
void	gen_array_alloc(struct symtab *symbol);
void	gen_array_dealloc(struct symtab *symbol);
void	arrayInit(struct symtab *s, const int len);
int 	gen_li(char *constant);
int 	load_var(struct symtab *symbol, char *comment);
void	gen_st(struct symtab *symbol, int rs1, const char *comment);
int 	assign(struct symtab *symbol, const int rs1);
int 	gen_alu(const char *mnem, const int rst,
		const int rs1, const int rs2, char *comment);
int 	gen_aluc(const char *mnem, const int rst,
		 const int rs1, const int val, char *comment);
int	gen_inc(const char *mnem, struct symtab *s, const int inc, char *comment);
int 	gen_cmp(const int sr1, const int sr2, const char *brType);
void 	gen_cond(const int reg1);
int	gen_prefix(const int rs1, const char *comment);
int 	gen_jump(char *op, const int label, const char *comment);
int 	new_label();
int 	gen_label(const int label);
void 	push_break(int label);
void 	push_continue(int label);
void 	pop_break();
void 	pop_continue();
void 	gen_break();
void 	gen_continue();
int	gen_io(const int io_type, const int r);
void	gen_func_header(struct symtab *f, struct symtab *params);
int	gen_call(struct symtab *symbol, int count);
int	gen_return(const int retReg);
void	clear_regs(void);
void	write_io(void);
void	write_globals(void);


extern int  eval_hist[];


#endif /* __VESPA_GEN__ */
