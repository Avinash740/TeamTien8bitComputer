/*
 *	Machine information
 */

#ifndef	__VESPA_MAC__
#define __VESPA_MAC__

/*
 *	opcode mnemonics
 */
#define	NOP	"NOP"	/* No-op			*/
#define ADD	"ADD"	/* Add				*/
#define SUB	"SUB"	/* Subtract			*/
#define MULT	"MLT"	/* Multiply			*/
#define DIV	"DIV"	/* Integer division		*/
#define OR	"OR"	/* Logical OR			*/
#define AND	"AND"	/* Logical AND			*/
#define XOR	"XOR"	/* Logical exclusive-OR		*/
#define NOT	"NOT"	/* Logical NOT			*/
#define CMP	"CMP"	/* Arithmetic comparison	*/
#define JMP	"JMP"	/* Jump indirectly thru reg+offset		*/
#define JMPL	"JMPL"	/* Jump and link indirectly thru reg+offset	*/
#define LD	"LD"	/* Load direct from memory 	*/
#define LDI	"LDI"	/* Load an immediate value	*/
#define LDX	"LDX"	/* Load indirect thru reg+offset		*/
#define ST	"ST"	/* Store direct to memory	*/
#define STX	"STX"	/* Store indirect thru reg+offset		*/
#define HLT	"HLT"	/* Halt execution		*/
#define MOV	"MOV"	/* Copy one register to another	*/


/*
 *	Branch instructions
 */
#define BRA	"BRA"	/* Unconditional branch				*/
#define BNV	"BNV"	/* Branch never 				*/
#define BCC	"BCC"	/* Branch on carry clear (~C) 			*/
#define BCS	"BCS"	/* Branch on carry set	(C) 			*/
#define BVC	"BVC"	/* Branch on overflow clear (~V) 		*/
#define BVS	"BVS"	/* Branch on overflow set (V) 			*/
#define BEQ	"BEQ"	/* Branch on equal (Z)				*/
#define BNE	"BNE"	/* Branch on not equal (~Z)			*/
#define BGE	"BGE"	/* Branch on >= (~N~V+NV)			*/
#define BLT	"BLT"	/* Branch on less than (N~V+~NV) 		*/
#define BGT	"BGT"	/* Branch on greather than ~Z(~N~V+NV) 		*/
#define BLE	"BLE"	/* Branch on less than or equal to (Z+(N~V+~NV))*/
#define BPL	"BPL"	/* Branch on plus (positive) (~N) 		*/
#define BMI	"BMI"	/* Branch on minus (negative) (N) 		*/



#define kNumRegs	32
		
/*
 *	Reserved registers
 */
#define LINK_REG	31	/* Where function calls link the return addr */
#define GLOBAL_PTR	30	/* Global variable jump register */
#define	LOCAL_PTR	29	/* Local variable jump register */
#define HEAP_PTR	28	/* Pointer into the heap (unimplemented) */
#define RTN_VAL_REG	27

#define MAX_REG		26

/*
 *	Define how big variable spaces will be
 */
#define kGlobalBaseAddr		2048	/* Globals start at 2k */
#define kGlobalSymSize		512	/* 512 for globals */
#define kStackFrameSize		512	/* 512 per stack frame */

#define kProgramBaseAddr	0x8	 /* The program loads into addr 8 */
#define kHeapBase		0x80000 /* The heap will be 1MB */

#define kTotalMemory  (1 << 23)
#define kWordLen	4

#define kNumParamRegs	4
#define	kNumLocRegs	8	
#define kNumScratchRegs	12

#endif
