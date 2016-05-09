#include <stdlib.h>
#include <stdio.h>

#include "gen.h"


#define OFFSET(s)	s->stack_offset * 4
#define LABEL		"LBL%d"


extern  FILE *temp;
int	byte_count = 0;		/* Counts bytes for linking */
int 	eval_hist[25]; 		/* records the last MAX_REG expression
				  evaluations for parameter passing*/


static int	label_count = 0;
static char *regs[]  = {"r0","r1","r2","r3","r4","r5","r6","r7",
			"r8","r9","r10","r11","r12","r13","r14","r15",
			"r16","r17","r18","r19","r20","r21","r22","r23",
			"r24","r25","r26","r27","r28","r29","r30","r31" };


/*
 *	Register allocations
 */
static int param_regs[] = { 0, 1, 2, 3 };
static int local_regs[] = { 4, 5, 6, 7, 8, 9, 10, 11 };
static int scratch_regs[] = { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };
static int unused_regs[] = { 24, 25, 26 };


#define PARAM(x)	param_regs[x]
#define LOCAL(x)	local_regs[x]
#define SCRATCH(x)	scratch_regs[x]
#define SPEC(x)		unused_regs[x]

#define R(x)		regs[x]

/*
 *	Tracks the symbols loaded into the param and local registers
 */
static struct symtab *reg_load[16];


/*
 *	NEXT_SCRATCH is a macro which calculates the next scratch
 *	register to use.
 */
static int scr_index = 0;
#define NEXT_SCRATCH	scr_index > 7 ? scr_index = 0 : ++scr_index


#define kInputLabel	"input"
#define kOutputLabel	"output"


/*
 *	Keeps track of continues and breaks for looping constructs.
 */
struct bc_stack 
{
	int bc_label;
	struct bc_stack *bc_next;
};

typedef struct bc_stack *BCStack;
static BCStack  b_top, c_top;

static char pendLabel[8][16];
static int  pendingCount = 0;



/************************************************************
 *	Break/Continue stack management functions
 ***********************************************************/

static BCStack push(BCStack stack, int label)
{
	BCStack new_entry = (BCStack)calloc(1, sizeof(struct bc_stack));
	
	if (!new_entry)
	{
		fatal("No more room to compile loops.");
	}
	new_entry->bc_next = stack;
	new_entry->bc_label = label;
	
	return new_entry;
}


static BCStack pop(BCStack stack)
{
	BCStack old_entry;
	
	if (!stack)
	{
		bug("break/continue stack underflow");
	}
	old_entry = stack;
	stack = old_entry->bc_next;
	free(old_entry);
	return stack;
}


static int top(BCStack stack)
{
	if (!stack)
	{
		error("no loop open");
		return 0;
	}
	else
	{
		return stack->bc_label;
	}
}



void push_break(int label)
{
	b_top = push(b_top, label);
}

void push_continue(int label)
{
	c_top = push(c_top, label);
}


void pop_break()
{
	b_top = pop(b_top);
}


void pop_continue()
{
	c_top = pop(c_top);
}


void gen_break()
{
	gen_jump(BRA, top(b_top), "BREAK");
}

void gen_continue()
{
	gen_jump(BRA, top(c_top), "CONTINUE");
}




/*********************************************************
 *	Label management functions
 ********************************************************/

/*
 *	Tells the compiler to emit a label with the next
 *	instruction.
 */
void	setPendLabel(const char *lbl)
{
	if (pendingCount >= 8)
		bug("Too many pending labels: setPendLabel");
	
	strcpy(pendLabel[pendingCount], lbl);
	strcat(pendLabel[pendingCount], ":");
	++pendingCount;
}


static char *format_label(const int label)
{
	static char buffer[sizeof(LABEL) + 2];
	
	sprintf(buffer, LABEL, label);
	return buffer;
}


static char *useLabel(void)
{
	static char rv[9];
	int i;
	
	for (i = pendingCount; i > 1; i--)
	{
		fprintf(temp, "%s\t%s\n", pendLabel[i-1], NOP);
		byte_count += 4;
	}
	
	strcpy(rv, pendLabel[0]);
	pendLabel[0][0] = '\0';
	pendingCount = 0;
	
	return rv;
}


int new_label()
{
	return ++label_count;
}



int gen_label(const int label)
{
	setPendLabel(format_label(label));
	return label;
}



/***************************************************
 *	Register management functions
 **************************************************/

/* 
 *	Determines which register a symbol should be loaded
 *	into.  If the symbol has a register specifically allocated
 *	to it (the first four parameters of a function and the first
 *	eight local variables are automatically allocated registers)
 *	then it returns that register.  Otherwise, it returns the
 *	next scratch register.
 */
int sym_reg(struct symtab *symbol)
{
	switch (symbol->s_blknum)
	{
		case 0:
			bug("sym_reg");
			break;
		case 1:		/* Global variable */
			return SCRATCH(NEXT_SCRATCH);
		case 2:		/* Parameter */
			if (symbol->scope_offset < kNumParamRegs)
				return PARAM(symbol->scope_offset);
			else
				return SCRATCH(NEXT_SCRATCH);
		default:	/* Local variable */
			if (symbol->scope_offset < kNumLocRegs)
				return LOCAL(symbol->scope_offset);
			else
				return SCRATCH(NEXT_SCRATCH);
	}		
}


/*
 *	This function is a bit cryptic, but it's purpose
 *	is tell the compiler that a certain symbol is currently
 *	loaded into a register.  While this registers symbols
 *	in scratch registers, the compiler generally doesn't pay
 *	attention.  This is used mostly for register variables (i.e.
 *	ones whose value is always loaded into a register.
 */
void	RegisterSymbol(struct symtab *s)
{
	if (s->loaded)
		reg_load[sym_reg(s)] = s;
}



/***********************************************************
 *	Overal program maintenance functions
 **********************************************************/	

/*
 *	Writes the program initialization routine.
 */
void	write_header(void)
{
	fprintf(temp, "\t%s\t%d\n", ".org", kProgramBaseAddr);
	fprintf(temp, "; Load the globals pointer register\n");
	fprintf(temp, "\t%s\t%s,\t#%d\n", LDI, R(GLOBAL_PTR), kGlobalBaseAddr);
	fprintf(temp, "\t%s\t%s,\t#%d\n", LDI, R(HEAP_PTR), kHeapBase);
	byte_count += 8;
	
	/*
	 *	Get ready to call main
	 */
	
	/*	Set up local stack pointer 	*/
	fprintf(temp, "\t%s\t%s,\t#%d\n",
		LDI,
		R(LOCAL_PTR),
		kGlobalBaseAddr + kGlobalSymSize);
	byte_count += 4;
	
	/*	Jump to main!	*/
	fprintf(temp, "\t%s\t%s,\t#%d\n",
		LDI,
		regs[0],
		kProgramBaseAddr);
	fprintf(temp, "\t%s\t%s,\t%s,\t#%s\t; Run main\n",
		JMPL,
		R(LINK_REG),
		regs[0],
		"main");
	
	/* Once we return it's okay to halt the simulator */
	fprintf(temp, "\tHLT\n");
	byte_count += 12;
}


/*
 *	Generates the I/O labels
 */
void write_io(void)
{
	fputs("\t.org 0\n", temp);
	fputs("input:\n\t.word 0x0\n", temp);
	fputs("output:\n\t.word 0x0\n", temp);
}
	

/*
 *	Global variables are initialized by using labels and initializers
 *	supported by the assembler rather than loaded directly in the 
 *	code.  See the documentation for the rationale.
 */
void write_globals(void)
{
	extern struct symtab symtab;
	struct symtab *symbol;
	
	fputs("\t;; Global initializers\n", temp);
	fprintf(temp, "\t.org %d\n", kGlobalBaseAddr);
	
	for (symbol = symtab.s_next; symbol; symbol = symbol->s_next)
	{
		if (symbol->s_type == VAR)
		{
			fprintf(temp, "\t.word %d\n", symbol->init_val);
		}
	}
}


/****************************************************************
 *	I/O functions
 ***************************************************************/

/*
 *	Generates stores or loads from the I/O system
 *
 *	Reads a value from input if io_type is kInput
 *	Writes a value to output if io_type is kOutput
 *
 *	r specifies the register containing the value to write for
 *	an output operation.
 *	returns the register the input value was stored to on an
 *	input operation.
 */
int gen_io(const int io_type, const int r)
{
	if (io_type == kInput)
	{
		int res = SCRATCH(NEXT_SCRATCH);
		fprintf(temp, "%s\t%s\t%s,\t%s\t\t; Read input\n",
			useLabel(),
			LD,
			R(res),
			kInputLabel);
		byte_count += 4;
		return res;
	}
	else if (io_type == kOutput)
	{
		fprintf(temp, "%s\t%s\t%s,\t%s\t\t; Write output\n",
			useLabel(),
			ST,
			kOutputLabel,
			R(r));
		byte_count += 4;
		return r;
	}
	
	bug("gen_io()");
	return -1;
}



/*********************************************************
 *	Array and heap functions
 ********************************************************/


/*
 *	Allocates an array in the heap
 */
void	gen_array_alloc(struct symtab *symbol)
{
	int byteSize = symbol->init_val * kWordLen;
	symbol->init_val = byteSize;
	
	 /*
	  *	Give the symbol the heap's address
	  */
	assign(symbol, HEAP_PTR);
	
	/*
	 *	Adjust the heap pointer to the next free address
	 */
	gen_aluc(ADD, HEAP_PTR, HEAP_PTR, byteSize, "Adjust the heap");
}


/*
 *	Cleans up an array at the end of a function
 */
void	gen_array_dealloc(struct symtab *symbol)
{
	int byteSize = symbol->init_val;
	
	/*
	 *	Readjust the heap pointer
	 */
	gen_aluc(SUB, HEAP_PTR, HEAP_PTR, byteSize, "Free heap memory");
}


/*
 *	Generates code for initializing an array upon declaration
 */
void arrayInit(struct symtab *s, const int len)
{
	int baseReg = gen_ldx(s, s->s_name);
	int i, valReg;
	char constStr[4];
	extern int initList[];
	
	for (i = 0; i < len; i++)
	{
		sprintf(constStr, "%d", initList[i]);
		valReg = gen_li(constStr);
		
		fprintf(temp, "\t%s\t%s,\t#%d,\t%s\t; Init element %d of %s\n",
			STX,
			R(baseReg),
			i*kWordLen,
			R(valReg),
			i, s->s_name);
		byte_count += 4;
	}
}



/************************************************************
 *	Load and store functions
 ***********************************************************/


/*
 *	Generates an immediate load.
 *	constant - The constant to load
 *	returns the register the value was loaded into
 */
int gen_li(char *constant)
{
	int thisReg = SCRATCH(NEXT_SCRATCH);
	fprintf(temp, "%s\t%s\t%s,\t#%s\t\t;\n", 
		useLabel(), LDI, R(thisReg), constant);
	byte_count += 4;
	
	
	return thisReg;
}



/*
 *	Generates an indexed load.  If the symbol is a register
 *	variable, then no code is generated because its value is
 *	already current in a register.
 *	If the symbol is a heap reference, then load_heap() is called
 *
 *	symbol - the symbol to load from memory
 *	returns the register the symbol is loaded into
 */
int gen_ldx(struct symtab *symbol, char *comment)
{
	int target;
	if (symbol->s_type == DUMMY)
	{
		return load_heap(symbol->s_regs[0], symbol->s_regs[1]);
	}
	
	target = sym_reg(symbol);
	if (!symbol->loaded)
	{
		fprintf(temp, "\t%s\t%s,\t%s,\t#%d\t; %s\n", 
			LDX, 			/* mnemonic */
			R(target),
			R(symbol->s_scope),	/* Jump register */
			OFFSET(symbol), /* Offset (int bytes) */
			comment);	/* symbol name (for readability) */
		
		
		byte_count += 4;
	}		
	/*
	 *	else do nothing--the symbol is already loaded with
	 *	the most recent value
	 */
	
	return target;
}


/*
 *	Loads a value from the heap.
 *	
 *	base_reg - the register holding the base address of the array
 *	offset_reg - the register holding the offset of the value to fetch
 */
int	load_heap(const int base_reg, const int offset_reg)
{
	int target_reg = SCRATCH(NEXT_SCRATCH);
	
	/*
	 *	Adjust the offset to compensate for word size
	 */
	target_reg = gen_aluc(MULT, -1, offset_reg, 4, "Adjust offset");
		
	/*
	 *	Compute address to load
	 */
	target_reg = gen_alu(ADD, -1, target_reg, base_reg, 
		"Compute heap address");
	
	
	/*
	 *	Load the value at that address
	 */
	fprintf(temp, "\t%s\t%s,\t%s\t\t; %s\n",
		LDX,
		R(target_reg),
		R(target_reg),
		"Fetch the value from the heap");
	byte_count += 4;
	
	return target_reg;
}


/*
 *	Generates an indexed store to memory.  Regardless of the type
 *	of variable, this function generates the store code.
 *
 *	symbol - the variable to store
 *	rs1 - the register holding the current value to store
 */
void	gen_st(struct symtab *symbol, int rs1, const char *comment)
{
	fprintf(temp, "%s\t%s\t%s,\t#%d,\t%s\t; %s\n",
		useLabel(),
		STX,
		R(symbol->s_scope),
		OFFSET(symbol),
		R(rs1),
		comment);
	byte_count += 4;
}


/*
 *	This function is called when value being stored needs to go
 *	to the heap rather than the function stack.
 *
 *	rst - the register holding the value to store
 *	base_reg - the register holding the base address of the array
 *	offset_reg - the register holding the offset of the array to target
 */
void	store_heap(int rst, const int base_reg, const int offset_reg)
{
	int target_reg;
	
	/*
	 *	Adjust the offset to compensate for word size
	 */
	target_reg = gen_aluc(MULT, -1, offset_reg, 4, "Adjust offset");
		
	/*
	 *	Compute address to load
	 */
	target_reg = gen_alu(ADD, -1, target_reg, base_reg, 
		"Compute heap address");
	
	/*
	 *	Store the value at that address
	 */
	fprintf(temp, "\t%s\t%s,\t%s\t; %s\n",
		STX,
		regs[target_reg],
		regs[rst],
		"Store the value to the heap");
	byte_count += 4;
}


/*
 *	Generates the code for an assignment.  Depending on what type
 *	of variable the value is being assigned to, this function calls
 *	the appropriate store routine (either gen_st or store_heap).  If the
 *	value is a register variable, no write to memory occurs; instead the
 *	value is copied to the appropriate register.
 *
 *	s - The symbol to which to assign the value
 *	rs1 - The register holding the value to assign
 */
int assign(struct symtab *s, const int rs1)
{
	switch (s->s_type)
	{
		case VAR:
		case ARRAY:
			if (s->loaded)
			{
				fprintf(temp, "%s\t%s\t%s,\t%s\t\t; %s\n",
					useLabel(),
					MOV,
					R(sym_reg(s)),
					regs[rs1],
					s->s_name);
				byte_count += 4;
			}
			else
			{
				gen_st(s, rs1, s->s_name);
			}
			break;
			
		case DUMMY:
			store_heap(rs1, s->s_regs[0], s->s_regs[1]);
			break;
			
		default:
			bug("assign");
	}

	return rs1;
}


	
/*******************************************************
 *	ALU functions
 ******************************************************/

/*
 *	Generates a function using the ALU.
 *
 *	mnem - What kind of alu instruction (add, sub, etc.)
 *	rst - The register to store the result to
 *	rs1 - The register containing the first operand
 *	rs2 - The register containing the second operand
 */
int gen_alu(const char *mnem, const int rst,
		const int rs1, const int rs2, char *comment)
{
	int resultReg;
	if (rst == -1)
		resultReg = SCRATCH(NEXT_SCRATCH);
	else
		resultReg = rst;
	
	fprintf(temp, "%s\t%s\t%s,\t%s,\t%s\t; %s\n",
		useLabel(),
		mnem,
		regs[resultReg],
		regs[rs1],
		regs[rs2],
		comment);
	byte_count += 4;
	
	return resultReg;
}


/*
 *	Generates an ALU instruction with an immediate operand
 *
 *	mnem - What kind of alu instruction
 *	rst - Where to store the result, -1 if any scratch register is okay
 *	rs1 - register containing the first operand
 *	val - the immediate operand
 *
 *	returns the register containing the result
 */
int gen_aluc(const char *mnem, const int rst,
		const int rs1, const int val, char *comment)
{
	int resultReg;
	if (rst == -1)
		resultReg = SCRATCH(NEXT_SCRATCH);
	else
		resultReg = rst;
	
	fprintf(temp, "%s\t%s\t%s,\t%s,\t#%d\t; %s\n",
		useLabel(),
		mnem,
		regs[resultReg],
		regs[rs1],
		val,
		comment);
	byte_count += 4;

	return resultReg;
}


/**********************************************************
 *	Comparison functions
 *********************************************************/

/*
 *	Can take two different directions depending on whether or not
 *	the condition flag is set.  If we are evaluating a conditional
 *	statement, in an if statement or a loop, for instance, we generate
 *	the jumping code directly based on the comparison type.  If not,
 *	(perhaps we are assigning a boolean value to a variable) then
 *	we just create a 1 or 0 depending on the result of the expression.
 */
int gen_cmp(const int sr1, const int sr2, const char *brType)
{
	char label[8];
	int  freeReg = SCRATCH(NEXT_SCRATCH);
	
	fprintf(temp, "%s\t%s\t%s,\t%s\t\t; Compare\n", 
		useLabel(), CMP, regs[sr1], regs[sr2]);
	fprintf(temp, "\t%s\t%s%d\t\t\t; Test condition\n",
		brType, "TRUE", label_count);
	fprintf(temp, "\t%s\t%s,\t#%d\t\t; Condition was false\n",
		LDI, 
		regs[freeReg],
		0x0);
	fprintf(temp, "\t%s\t%s%d\n", BRA, "DONE", label_count);
	fprintf(temp, "%s%d:\t%s\t%s,\t#%d\t\t; Condition was true\n",
		"TRUE", label_count,
		LDI,
		regs[freeReg],
		0x1);
	sprintf(label, "DONE%d", label_count);
	setPendLabel(label);
	byte_count += 20;
	
	label_count++;
	return freeReg;
}



/***********************************************************
 *	Conditional/looping functions
 *	Note that there are no instructions specifically 
 *	designed to implement loops in VeSPA so everything
 *	boils down to conditionals.
 **********************************************************/


/*
 *	Once a the expression for a conditional has been evaluated
 *	this function generates code to compare it with 0 and
 *	make the appropriate jump.
 */
int	gen_prefix(const int rs1, const char *comment)
{
	fprintf(temp, "%s\t%s\t%s,\t#0\t\t; %s\n", 
		useLabel(), CMP, regs[rs1], "");
	byte_count += 4;
	return gen_jump(BEQ, new_label(), comment);
}


/*
 *	Generates a BXX instruction to the appropriate label.
 *
 *	op - The type of break to use (e.g. BEQ, BNE, BGT...)
 *	label - The label to break to if the condition is true
 *
 *	returns the label
 */
int gen_jump(char *op, const int label, const char *comment)
{
	fprintf(temp, "%s\t%s\t%s\t\t\t; %s\n", 
		useLabel(), op, format_label(label), comment);
	byte_count += 4;
	
	return label;
}

			

/**********************************************************
 *	Function calling routines
 *********************************************************/


/*
 *	Generates the code to load the first four parameters to a
 *	function in the registers.
 *
 *	f - the function
 *	params - the list of parameters to the function
 */
void	gen_func_header(struct symtab *f, struct symtab *params)
{
	struct symtab *p;
	int i;
	
	for (i = 0, p = params; p && i < kNumParamRegs; i++, p = p->s_plist)
	{
		fprintf(temp, "\t%s\t%s,\t%s,\t#%d\n",
			LDX,
			R(sym_reg(p)),
			R(LOCAL_PTR),
			OFFSET(p));
		p->loaded = true;
		reg_load[i] = p;
		byte_count += 4;
	}
}
	

/*
 *	Generates all of the code needed to make a function call.  There
 *	is a lot of overhead concerning this procedure, since it has to
 *	store all register variables back to memory, set up the new functions
 *	stack space, and then reload all of the register variable back after
 *	the function call has been made.
 *
 *	symbol - the function to call
 *	count - the number of parameters in the function to call.
 */
int	gen_call(struct symtab *symbol, int count)
{
	int i;
	int base = SCRATCH(NEXT_SCRATCH);
	
	chk_parm(symbol, count);
	fprintf(temp, ";; Calling function %s\n", symbol->s_name);
	
	/*
	 *	Store locals and parameters stored in registers
	 *	back in memory
	 */
	for (i = 0; i < kNumParamRegs + kNumLocRegs; i++)
	{
		if (reg_load[i] != NULL)
		{
			gen_st(reg_load[i], i, "write back to memory");
			reg_load[i]->loaded = false;
		}
	}
	
	/*
	 *	Save the local variable pointer register
	 */
	fprintf(temp, "%s\t%s\t%s,\t#%d,\t%s\t; Store LOCAL_PTR\n",
		useLabel(),
		STX,
		regs[LOCAL_PTR],
		kStackFrameSize + 4,
		regs[LOCAL_PTR]);
	byte_count += 4;
	
	
	/*`
	 *	Save the return address for when this function
	 *	returns.
	 */
	fprintf(temp, "%s\t%s\t%s,\t#%d,\t%s\t; Store RETURN_REG\n",
		useLabel(),
		STX,
		regs[LOCAL_PTR],
		kStackFrameSize,
		regs[LINK_REG]);
	byte_count += 4;
	
	/*
	 *	Load the new local variable pointer
	 */
	fprintf(temp, "%s\t%s\t%s,\t%s,\t#%d\n",
		useLabel(),
		ADD,
		regs[LOCAL_PTR],
		regs[LOCAL_PTR],
		kStackFrameSize+8);
	
	byte_count += 4;
	
	/*
	 *	Load parameters
	 */
	for (i = 0; i < count; i++)
	{
		fprintf(temp, "%s\t%s\t%s,\t#%d,\t%s\t\n",
			useLabel(),
			STX,
			regs[LOCAL_PTR],
			i * kWordLen,
			regs[eval_hist[i]]);
		
		byte_count += 4;
	}
	
	/*
	 *	We should now be ready to actually start execution
	 *	of the called function
	 */
	fprintf(temp, "%s\t%s\t%s,\t#%d\t\t; Load program base address\n",
		useLabel(),
		LDI,
		R(base),
		kProgramBaseAddr);
	fprintf(temp, "%s\t%s\t%s,\t%s,\t#%s\t; Call function %s!\n",
		useLabel(),
		JMPL,
		regs[LINK_REG],
		R(base),
		symbol->s_name,
		symbol->s_name);
	byte_count += 8;
	
	/*
	 * It's necessary now to reload the registers with the variables
	 * that were there before
	 */
	for (i = 0; i < kNumParamRegs + kNumLocRegs; i++)
	{
		if (reg_load[i] != NULL)
		{
			gen_ldx(reg_load[i], "Load back into registers");
			reg_load[i]->loaded = true;
		}
	}
	
	
	return RTN_VAL_REG;
}


/*
 *	Return from a function call
 */
int	gen_return(const int retReg)
{
	extern struct symtab *heapVars;
	
	/*
	 *	First deallocate any arrays
	 */
	while (heapVars != NULL)
	{
		gen_array_dealloc(heapVars);
		heapVars = heapVars->heapList;
	}
	
	
	/*
	 *	Put the local pointer back
	 */
	fprintf(temp, "%s\t%s\t%s,\t%s,\t#%d\t; Return LOCAL_PTR\n",
		useLabel(),
		LDX,
		regs[LOCAL_PTR],
		regs[LOCAL_PTR],
		-4);
	byte_count += 4;
	
	
	/*
	 *	Put the return value (if necessary) in the proper
	 *	register
	 */
	if (retReg != -1)
	{	
		fprintf(temp, "%s\t%s\t%s,\t%s\t\t; Load reutrn value\n",
			useLabel(),
			MOV,
			regs[RTN_VAL_REG],
			regs[retReg]);
		byte_count += 4;
	}
	
	
	/*
	 *	Get our return address ready
	 */
	fprintf(temp, "%s\t%s\t%s,\t%s\n",
		useLabel(),
		MOV,
		regs[0],
		regs[LINK_REG]);
	byte_count += 4;
	
	/*
	 *	Put the calling function's return address back
	 *	where it expects it to be.
	 */
	fprintf(temp, "%s\t%s\t%s,\t%s,\t#%d\t; Fetch caller's return address\n",
		useLabel(),
		LDX,
		regs[LINK_REG],
		regs[LOCAL_PTR],
		kStackFrameSize);
	byte_count += 4;
	
	
	/*
	 *	Jump back to the calling function
	 */
	fprintf(temp, "%s\t%s\t%s\t\t\t; return control to caller\n",
		useLabel(),
		JMP,
		regs[0]);
	byte_count += 4;
	
	return 0;
}


/*
 *	Once a function exits, this cleans up the register allocation
 *	map so the compiler doesn't get confused.
 */
void	clear_regs(void)
{
	int i;
	for (i = 0; i < kNumParamRegs + kNumLocRegs; i++)
	{
		reg_load[i] = NULL;
	}
}
