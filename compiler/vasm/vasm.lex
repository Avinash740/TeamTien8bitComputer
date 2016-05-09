
/* LEX source for vasm.c						*/

/* start of definitions							*/

letter		[a-zA-Z]
digit		[0-9]
hex		[a-fA-F]


/* start of rules							*/

/* These are all of the mnemonic op-codes recognized by the assembler.
   Note that the input file can be either upper or lower-case, or a mix
   of both.
*/

%%

add|ADD		{yylval = NONE;		return(ADD);	}
and|AND		{yylval = NONE;		return(AND);	}
bra|BRA		{yylval = BRA_COND;	return(BRANCH);	}
bnv|BNV		{yylval = BNV_COND;	return(BRANCH);	}
bcc|BCC		{yylval = BCC_COND;	return(BRANCH);	}
bcs|BCS		{yylval = BCS_COND;	return(BRANCH);	}
bvc|BVC		{yylval = BVC_COND;	return(BRANCH);	}
bvs|BVS		{yylval = BVS_COND;	return(BRANCH);	}
beq|BEQ		{yylval = BEQ_COND;	return(BRANCH);	}
bne|BNE		{yylval = BNE_COND;	return(BRANCH);	}
bge|BGE		{yylval = BGE_COND;	return(BRANCH);	}
blt|BLT		{yylval = BLT_COND;	return(BRANCH);	}
bgt|BGT		{yylval = BGT_COND;	return(BRANCH);	}
ble|BLE		{yylval = BLE_COND;	return(BRANCH);	}
bpl|BPL		{yylval = BPL_COND;	return(BRANCH);	}
bmi|BMI		{yylval = BMI_COND;	return(BRANCH);	}
cmp|CMP		{yylval = NONE;		return(CMP);	}
hlt|HLT		{yylval = NONE;		return(HLT);	}
jmp|JMP		{yylval = NONE;		return(JMP);	}
jmpl|JMPL	{yylval = NONE;		return(JMPL);	}
ld|LD		{yylval = NONE;		return(LD);	}
ldi|LDI		{yylval = NONE;		return(LDI);	}
ldx|LDX		{yylval = NONE;		return(LDX);	}
mov|MOV		{yylval = NONE;		return(MOV);	}
nop|NOP		{yylval = NONE;		return(NOP);	}
not|NOT		{yylval = NONE;		return(NOT);	}
or|OR		{yylval = NONE;		return(OR);	}
xor|XOR         {yylval = NONE;         return(XOR);    }
st|ST		{yylval = NONE;		return(ST);	}
stx|STX		{yylval = NONE;		return(STX);	}
sub|SUB		{yylval = NONE;		return(SUB);	}


r{digit}+	{	/* register, e.g. r24				*/
		yylval = add_symbol(yytext);
		/* extract register number from string			*/
		sscanf(sym_table[yylval].name,"r%d",&sym_table[yylval].value);
		return(REG_NUM);
		}

R{digit}+	{	/* register, e.g. R24				*/
		yylval = add_symbol(yytext);
		/* extract register number from string			*/
		sscanf(sym_table[yylval].name,"R%d",&sym_table[yylval].value);
		return(REG_NUM);
		}

(_|{letter})({letter}|{digit}|_|"."|"$")*	{
	yylval = add_symbol(yytext);
	return(IDENTIFIER);
	}

0x({digit}|{hex})+	{ /* hex constants, e.g. 0x1A			*/
		yylval = add_symbol(yytext);
		/* convert string to actual value			*/
		sscanf(yytext,"0x%x",&sym_table[yylval].value);
		return(NUMBER);
		}

{digit}+	{
		yylval = add_symbol(yytext);
		/* convert string to actual value			*/
		sscanf(yytext,"%d",&sym_table[yylval].value);
		return(NUMBER);
		}

".word"|".WORD"	{yylval = NONE;		return(DOT_WORD);	}

".byte"|".BYTE"	{yylval = NONE;		return(DOT_BYTE);	}

".alloc"|".ALLOC" {yylval = NONE;	return(DOT_ALLOC);	}

".org"|".ORG"	{yylval = NONE;		return(DOT_ORG);	}

".equ"|".EQU"	{yylval = NONE;		return(DOT_EQU);	}

","		{yylval = NONE;		return(',');	}

"#"		{yylval = NONE;		return('#');	}

"+"		{yylval = NONE;		return('+');	}

"-"		{yylval = NONE;		return('-');	}

":"		{yylval = NONE;		return(':');	}

"\n"		{
		curr_line++;		/* looking at next source line	*/
		}

[ \t]*		;		/* ignore any white space		*/

(";"|"//")(.)*	;		/* ; or // start comments		*/



%%
/* start of programs section						*/




