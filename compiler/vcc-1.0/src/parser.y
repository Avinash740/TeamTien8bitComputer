/*
 *	sample c
 *	syntax analysis with error recovery
 *	(s/r conflicts: one on ELSE, one on error)
 */
 
 %{


#include <stdio.h>

#include "symtab.h"  
#include "mem.h"
#include "gen.h"
#include "heap.h"


extern 	int  byte_count;

static 	int break_loc, loop_body;

extern	FILE *temp;
bool 	err = false;
bool 	argRgn = false;
int 	storageClass;

enum
{
	kInt,
	kVoid
};


 %}

%union {
	struct symtab *y_sym;	/* Identifier */
	char *y_str;		/* Constant */
	int  y_num;		/* count */
	int  y_lab;		/* label */
	int  y_reg;		/* Register */
}
 
 
/*
 *	terminal symbols
 */
 
%token <y_sym> Identifier
%token <y_str> Constant
%token INT
%token VOID
%token IF
%token ELSE
%token <y_lab> WHILE
%token <y_lab> FOR
%token BREAK
%token CONTINUE
%token RETURN
%token GETC
%token PUTC
%token ';'
%token '('
%token ')'
%token '{'
%token '}'
%token '+'
%token '-'
%token '*'
%token '/'
%token '%'
%token '<'
%token '>'
%token GE	/* >= */
%token LE	/* <= */
%token EQ	/* == */
%token NE	/* != */
%token '&'
%token '^'
%token '|'
%token '='
%token PE	/* += */
%token ME	/* -= */
%token TE	/* *= */
%token DE	/* /= */
%token RE	/* %= */
%token PP	/* ++ */
%token MM	/* -- */
%token ','


/*
 *	typed non-terminal symbols
 */

%type	<y_sym> optional_parameter_list, parameter_list, param_decl, memory_ref
%type 	<y_num> optional_argument_list, argument_list, integer_list, type_class
%type	<y_reg> binary, expression
%type	<y_lab> if_prefix, loop_prefix


/*
 *	Precedence table
 */

%right '=' PE ME TE DE RE
%left '|'
%left '^'
%left '&'
%left EQ NE
%left '<' '>' GE LE
%left '+' '-'
%left '*' '/' '%'
%right PP MM

%%

program   :	
	  { 
	  	SymtabInit(); 
		write_header();
	  } 
	  definitions
	  { 
	  	write_io();
		write_globals();
	  	#ifdef TRACE
		message("\n;; Total number of bytes: %d\n", byte_count);
		#endif
		
		if (err) return -1;
		
	  }
		

definitions 
	: type_class { storageClass = $1; } definition
	| definitions type_class
		{ storageClass = $2; }
		definition
		{ yyerrok; }
	| error
	| definitions error
	
		
definition 
	: function_definition
	| declaration
	

function_definition 
	: Identifier '(' 
	  { 
	  	make_func($1);
		blk_push(); 
		st_offset = 0;
	  }
	  optional_parameter_list rp
	  { 
		$<y_lab>$ = l_offset;
		chk_parm($1, count_parms($4)); 
		all_parm($4);
		l_max = st_offset;
		fprintf(temp, "\n;; Function %s - offset %d\n", 
			$1->s_name, $1->byte_offset);
		
		gen_func_header($1, $4);
		currentf = $1;
	  }
	  compound_statement
	  { 
	  	all_func($1);
		if (currentf->returnSet == 0)
		{
			gen_return(-1);
			if (storageClass != kVoid)
				warning("Function %s should return a value.\n",
					currentf->s_name);
		} 
		l_offset = $<y_lab>6;
		clear_regs();
		currentf = NULL;
	  }
	 
type_class: INT 
		{ $$ = kInt; } 
	  | VOID 
	  	{ $$ = kVoid; } 

	
optional_parameter_list 
	: { $$ = 0; /* No formal parameters */ }
	| parameter_list
		
	
parameter_list 
	: param_decl
		{ $$ = link_parm($1, NULL);
		  make_parm($1); }
	| param_decl ',' parameter_list
		{ $$ = link_parm($1, $3);
		  make_parm($1);
		  yyerrok; 
		}
	| error
		{ $$ = 0; }
	| error parameter_list
		{ $$ = $2; }
	| param_decl error parameter_list
	  { 
	  	$$ = link_parm($1, $3);
		make_parm($1);
		yyerrok;
	  }
	| error ',' parameter_list
		{ $$ = $3;
		  yyerrok;
		}
	
	
param_decl :	INT Identifier
		{
			$$ = $2;
		}
	| INT Identifier '[' ']'
	  {
	  	arrayparam($2);
	  	$$ = $2;
	  }
	   
	   
compound_statement
	: '{' 
	  { 
	  	$<y_lab>$ = l_offset;
	  	blk_push(); 
	  }
	  declarations statements rr
	  { 
	  	if (l_offset > l_max)
			l_max = l_offset;
		l_offset = $<y_lab>2;
		blk_pop(); 
	  }
	
declarations
	: /* NULL */
	| declarations declaration
		{ yyerrok; }
	| declarations error

	
declaration
	: INT declarator_list sc
	
declarator_list
	: initializer
	| declarator_list ',' initializer
		{  yyerrok; }
	| error
	| declarator_list error
	| declarator_list error initializer
		{ yyerrok; }
	| declarator_list ',' error
		
		
initializer:	Identifier
		{ all_var($1, 0); }
	| Identifier '=' Constant
	  { 
	  	all_var($1, atoi($3));
	  	/* We don't want to load globals immediately into registers */
	  	if ($1->s_scope == LOCAL_PTR)
	  	{
			assign($1, gen_li($3));
	  	}
	  }
	| Identifier '[' Constant ']'
	  { 
	  	all_array($1, atoi($3));
	  	gen_array_alloc($1);
	  }
	| Identifier '[' ']' '=' '{' integer_list '}'
	  {
	  	all_array($1, $6);
		gen_array_alloc($1);
		arrayInit($1, $6);
	  }
	;
	
integer_list:	Constant
		{ 
			$$ = 1; 
			addInitElement($1, 0);
		}
	| integer_list ',' Constant
		{ 
			addInitElement($3, $1);
			$$ += 1; 
		}
	| integer_list ',' error
		{ $$ = 0; }
	| integer_list error
		{ $$ = 0; }
	;
	
statements
	: /* NULL */
	| statements statement
		{ yyerrok; }
	| statements error
	
		
	
statement
	: expression sc
		{ $<y_reg>$ = $1; 
		  currentf->returnSet = 0;
		}
	| sc /* null statement */
	| BREAK sc
	  { 
	  	gen_break(); 
		currentf->returnSet = 0;
	  }
	| CONTINUE sc
		{ gen_continue(); 
			currentf->returnSet = 0;
		}
	| RETURN sc
		{ gen_return(-1);
		  currentf->returnSet = 1;
		 }
	| RETURN expression sc
		{ gen_return($2); 
		  currentf->returnSet = 1;
		}
	| compound_statement
	| if_prefix statement
	  { 
	  	gen_label($1); 
		currentf->returnSet = 0;
	  }
	| if_prefix statement ELSE 
	  {
	  	$<y_lab>$ = gen_jump(BRA, new_label(), "past ELSE");
		gen_label($1);
	  }	
	  statement
	  { 
	  	gen_label($<y_lab>4); 
	  }
	| loop_prefix 
	  {
	  	push_break(break_loc);
		$<y_lab>$ = break_loc;
	  }
	  statement
	  {
	  	gen_jump(BRA, $1, "repeat loop");
		gen_label($<y_lab>2);
		pop_break();
		pop_continue();
		currentf->returnSet = 0;
	  }
	;
	  
	
if_prefix
	: IF '(' expression rp
		{ $$ = gen_prefix($3, "IF"); }
	| IF error
		{ $<y_lab>$ = -1; }
	;
		
	
loop_prefix:	WHILE '(' 
	  {
	  	$<y_lab>$ = gen_label(new_label());
		push_continue($<y_lab>$);
	  }
	  expression rp
	  {
	  		break_loc = gen_prefix($4, "WHILE loop");
	  		$$ = $<y_lab>3; 
	  }
	  
	| FOR '(' expression ';' 
	  {
		$<y_lab>$ = gen_label(new_label()); /* COND */
	  }
	  expression ';' 
	  {
		break_loc = gen_prefix($6, "FOR loop"); /* DONE */
		loop_body = gen_jump(BRA, new_label(), "Goto loop body"); /* BODY */
		$<y_lab>$ = gen_label(new_label());	/* LOOPBACK */
		push_continue($<y_lab>$);
	  }
	  expression rp
	  {
		gen_jump(BRA, $<y_lab>5, "Goto test condition");
		gen_label(loop_body);
		$$ = $<y_lab>8;
	  }
		
	
	| WHILE error
	  {
	  	$$ = gen_label(new_label());
		push_continue($$);
	  }
	;
	
	
expression
	: binary
	| expression ',' binary
	  {
	  	$$ = $3; 
		yyerrok; 
	  }
	| error ',' binary
		{ yyerrok; }
	| expression error
	| expression ',' error
		
	
binary	: memory_ref
		{ $$ = gen_ldx($1, $1->s_name); }
	| Constant
	  { 
	  	$$ = gen_li($1); 
	  }
	| '(' expression rp
		{ $$ = $2; }
	| '(' error rp
		{ $$ = MAX_REG; }
	| Identifier '(' 
		{ chk_func($1); argRgn = true; }
	  optional_argument_list rp
	  	{ $$ = gen_call($1, $4); 
		  argRgn = false;
		}
	| PP memory_ref		
	  { 
		chk_var($2);
		$$ = assign($2, gen_aluc(ADD, sym_reg($2), gen_ldx($2), 1, "Increment"));
	  }	
	| MM memory_ref		
	  { 
	  	chk_var($2);
		$$ = assign($2, gen_aluc(SUB, sym_reg($2), gen_ldx($2), 1, "Decrement"));
	  }	
	| GETC '(' rp
	  {
	  	$$ = gen_io(kInput, -1);
	  }
	| PUTC '(' expression rp
	  {
	  	$$ = gen_io(kOutput, $3);
	  }
	| binary '+' binary
	  	{ $$ = gen_alu(ADD, -1, $1, $3, "+"); }
	| binary '-' binary
	  	{ $$ = gen_alu(SUB, -1, $1, $3, "-"); }
	| binary '*' binary	
		{ $$ = gen_alu(MULT, -1, $1, $3, "*"); }	
	| binary '/' binary		
		{ $$ = gen_alu(DIV, -1, $1, $3, "/"); }
	| binary '>' binary
	  	{ $$ = gen_cmp($1, $3, BGT); }	
	| binary '<' binary		
	  	{ $$ = gen_cmp($1, $3, BLT); }
	| binary GE binary		
	  	{ $$ = gen_cmp($1, $3, BGE); }
	| binary LE binary	
	  	{ $$ = gen_cmp($1, $3, BLE); }	
	| binary EQ binary	
	  	{ $$ = gen_cmp($1, $3, BEQ); }	
	| binary NE binary	
	  	{ $$ = gen_cmp($1, $3, BNE); }	
	| binary '&' binary		
	  	{ $$ = gen_alu(AND, -1, $1, $3, "&"); }
	| binary '^' binary	
		{ $$ = gen_alu(XOR, -1, $1, $3, "^"); }	
	| binary '|' binary
	 	 { $$ = gen_alu(OR, -1, $1, $3, "|"); }		
	| memory_ref '=' binary
		{ chk_var($1);
		  $$ = assign($1, $<y_reg>3); }		
	| memory_ref PE binary	
	  { 
	  	chk_var($1); 
		$$ = assign($1, gen_alu(ADD, -1, gen_ldx($1), $3, "+=")); 
	  }	
	| memory_ref ME binary	
	  { 
	  	chk_var($1); 
		$$ = assign($1, gen_alu(SUB, -1, gen_ldx($1), $3, "-="));
	  }	
	| memory_ref TE binary	
		{ chk_var($1); 
		  $$ = assign($1, gen_alu(MULT, -1, gen_ldx($1), $3, "*="));
		}	
	| memory_ref DE binary	
		{ chk_var($1); 
		  $$ = assign($1, gen_alu(DIV, -1, gen_ldx($1), $3, "/="));
		}	
	

memory_ref: Identifier
	  {
	  	chk_var($1);
	  }
	  
	| Identifier '[' expression ']'
	  { 
	  	int reg;
	  	chk_array($1); 
		reg = gen_ldx($1, $1->s_name);
		$$ = make_dummy(reg, $3);
	  }
	;

optional_argument_list
	: { $$ = 0; /* No args */ }
	| argument_list
	

argument_list
	: binary
	  { 
	  	$$ = 1;
		eval_hist[0] = $<y_reg>1;
	  }
	| argument_list ',' binary
	  { 
	  	eval_hist[$$] = $3;
		++$$;
		yyerrok; 
	  }
	| error
		{ $$ = 0; }
	| argument_list error
	| argument_list ',' error


/*
 *	Make certain terminals important
 */
rp	: ')'	{ yyerrok; }
sc	: ';'	{ yyerrok; }
rr	: '}'	{ yyerrok; }
