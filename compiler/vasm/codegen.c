
/* Generate object code from the stmt[] structure.
   The object code is written to a file named in "objfile" with
   all values in hexadecimal.
                                    */

#include <stdio.h>
#include "gvars.h"
FILE    *fp,*fopen();    /* file descriptor stuff        */



codegen(objfile)
char    objfile[];    /* the name of the file to write the object code to */
{
int    i;        /* current stmt[] being generated    */
int    lc;        /* current location counter value (bytes)*/
unsigned code;        /* the object code for stmt[i]        */
int    j;        /* index counter            */
int    br_displ;    /* branch displacement value        */

/* open the object code output file                */
if ((fp = fopen(objfile,"w")) == NULL)
    {
    sprintf(err_msg,"can't open output file %s",objfile);
    err_exit(err_msg,FILE_ERROR);
    }

/* generate object code for each statement in the given range    */
lc = 0;
for (i = 0; i < curr_stmt; i++)
    {
    /* generate code word for each different instr format    */
    switch (stmt[i].op_type)
        {
        case ADD_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op3].value,16,i);
               code |= 1 << 16;
               code |= (0xffff & sym_table[stmt[i].op3].value);
               }
            else {
               code |= (0x1f & sym_table[stmt[i].op3].value) << 11;
               }
            print_code(code,4,&lc);
            break;

        case AND_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op3].value,16,i);
               code |= 1 << 16;
               code |= (0xffff & sym_table[stmt[i].op3].value);
               }
            else {
               code |= (0x1f & sym_table[stmt[i].op3].value) << 11;
               }
            print_code(code,4,&lc);
            break;

        case BRANCH_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            /* the specific condition					*/
            code |= (0xf & stmt[i].misc) << 23;
            /* branch displacement = dest_PC - (curr_PC + 4)            */
            if (sym_table[stmt[i].op1].value == UN_INIT_LABEL)
		printf("****Error:  Uninitialized symbol: %s\n",
            	    sym_table[stmt[i].op1].name);
            br_displ = sym_table[stmt[i].op1].value - (lc + 4);
            check_branch(br_displ,23,i);
            code |= (0x7fffff & br_displ);
            print_code(code,4,&lc);
            break;

        case CMP_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & 0) << 22;	/* this is obviously not needed	*/
            code |= (0x1f & sym_table[stmt[i].op1].value) << 17;
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op2].value,16,i);
               code |= 1 << 16;
               code |= (0xffff & sym_table[stmt[i].op2].value);
               }
            else {
               code |= (0x1f & sym_table[stmt[i].op2].value) << 11;
               }
            print_code(code,4,&lc);
            break;

        case HLT_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            print_code(code,4,&lc);
            break;

        case JMP_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & 0) << 22; /* this step is obviously not needed */
            code |= (0x1f & sym_table[stmt[i].op1].value) << 17;
            code |= 0 << 16;	/* this step is obviously not needed	*/
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op2].value,16,i);
               code |= (0xffff & sym_table[stmt[i].op2].value);
               }
            print_code(code,4,&lc);
            break;

        case JMPL_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            code |= 1 << 16;
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op3].value,16,i);
               code |= (0xffff & sym_table[stmt[i].op3].value);
               }
            print_code(code,4,&lc);
            break;

        case LD_OP:
            if (sym_table[stmt[i].op2].value == UN_INIT_LABEL)
	        printf("****Error:  Uninitialized symbol: %s\n",
            	    sym_table[stmt[i].op2].name);
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            check_immed(sym_table[stmt[i].op2].value,22,i);
            code |= (0x3fffff & sym_table[stmt[i].op2].value);
            print_code(code,4,&lc);
            break;

        case LDI_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            check_immed(sym_table[stmt[i].op2].value,22,i);
            code |= (0x3fffff & sym_table[stmt[i].op2].value);
            print_code(code,4,&lc);
            break;

        case LDX_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op3].value,17,i);
               code |= (0x1ffff & sym_table[stmt[i].op3].value);
               }
            print_code(code,4,&lc);
            break;

        case MOV_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            code |= 1 << 16;
            print_code(code,4,&lc);
            break;

        case NOP_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            print_code(code,4,&lc);
            break;

        case NOT_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            print_code(code,4,&lc);
            break;

        case OR_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op3].value,16,i);
               code |= 1 << 16;
               code |= (0xffff & sym_table[stmt[i].op3].value);
               }
            else {
               code |= (0x1f & sym_table[stmt[i].op3].value) << 11;
               }
            print_code(code,4,&lc);
            break;

	case XOR_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op3].value,16,i);
               code |= 1 << 16;
               code |= (0xffff & sym_table[stmt[i].op3].value);
               }
            else {
               code |= (0x1f & sym_table[stmt[i].op3].value) << 11;
               }
            print_code(code,4,&lc);
            break;

        case ST_OP:
            if (sym_table[stmt[i].op1].value == UN_INIT_LABEL)
	        printf("****Error:  Uninitialized symbol: %s\n",
            	    sym_table[stmt[i].op1].name);
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 22;
            check_immed(sym_table[stmt[i].op1].value,22,i);
            code |= (0x3fffff & sym_table[stmt[i].op1].value);
            print_code(code,4,&lc);
            break;

        case STX_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op3].value,17,i);
               code |= (0x1ffff & sym_table[stmt[i].op3].value);
               }
            print_code(code,4,&lc);
            break;

        case SUB_OP:
            code = 0;
            code |= (0x1f & stmt[i].op_code) << 27;
            code |= (0x1f & sym_table[stmt[i].op1].value) << 22;
            code |= (0x1f & sym_table[stmt[i].op2].value) << 17;
            if (stmt[i].misc == IMMEDIATE)
               {
               check_immed(sym_table[stmt[i].op3].value,16,i);
               code |= 1 << 16;
               code |= (0xffff & sym_table[stmt[i].op3].value);
               }
            else {
               code |= (0x1f & sym_table[stmt[i].op3].value) << 11;
               }
            print_code(code,4,&lc);
            break;

        case DOT_BYTE_OP:
            check_immed(sym_table[stmt[i].op1].value,8,i);
            code = sym_table[stmt[i].op1].value & 0xff;
            print_code(code,1,&lc);
            break;

        case DOT_WORD_OP:
            code = sym_table[stmt[i].op1].value & 0xffffffff;
            print_code(code,4,&lc);
            break;

        case DOT_ALLOC_OP:
            /* print a bunch of 0s					*/
            for (j = 1; j <= sym_table[stmt[i].op1].value; j++)
                print_code(0,1,&lc);
            break;

        case DOT_ORG_OP:
            lc = sym_table[stmt[i].op1].value;
            break;

        default:
            err_exit("Unknown instruction.",BAD_OPTYPE);
            break;
        }

    }

/* close the file                        */
fclose(fp);
}







/* Print count bytes of the given code word in hex using ASCII
characters.
                                    */
print_code(code,count,lc)
unsigned code;        /* the object code value            */
int    count;        /* number of bytes to print            */
int    *lc;        /* current program counter value        */
{
    int    i;

    /* Print the address at which these bytes should be loaded
       into memory, preceded by "@".                */
    fprintf(fp,"@%04x",*lc);

    /* print the object code one byte at a time in big-endian order */
    for (i = count; i >= 1; i--)
        {
        fprintf(fp," %02x",(0xff & (code >> (8 * (i-1))) ));
        }

    /* End with a newline character.                */
    fprintf(fp,"\n");

    /* increment lc by count bytes                    */
    *lc += count;
}





/* Verify that the literal value specified fits within the immediate
field available in this instruction.					*/

check_immed(value,width,i)
int	value;		/* the immediate value to be checked		*/
int	width;		/* number of bits available in this field	*/
int	i;		/* the assembly code statement number		*/
{

int	largest_value;	/* largest possible value for this field */

largest_value = 1 << (width-1);	/* 2^(width-1)				*/

/*
printf("### line:  %d\tvalue=%d\twidth=%d\tlargest=%d\n",stmt[i].line_num,value,width,largest_value);
*/
if ((value >= largest_value) || (value <= -largest_value) )
	{
	printf("****Error:  The absolute value of the literal %d in line %d must be smaller than %d.\n",value,stmt[i].line_num,largest_value);
	}

}







/* Verify that the branch displacement specified fits within the immediate
field available in this instruction.					*/

check_branch(value,width,i)
int	value;		/* the immediate value to be checked		*/
int	width;		/* number of bits available in this field	*/
int	i;		/* the assembly code statement number		*/
{

int	largest_value;	/* largest possible value for this field */

largest_value = 1 << (width-1);	/* 2^(width-1)				*/


if ((value >= largest_value) || (value <= -largest_value) )
	{
	printf("****Error:  The absolute value of the branch displacement %d in line %d must be smaller than %d.\n",value,stmt[i].line_num,largest_value);
	}

}
