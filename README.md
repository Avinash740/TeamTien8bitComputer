# TeamTien8bitComputer

## Defining the VeSPA ISA 

### Architecture

	2^13 x 8bit wide memory, 32 x 8bit wide instructions, 4 condition bits, C,V,N,Z.

### Define OPcode and condition codes
	
	NOP 	0x0		No operation
	ADD		0x1		Addition
	SUB 	0x2 	Subtraction
	OR 		0x3 	Bit-wise logical OR
	AND		0x4		Bit-wise logical AND		
	NOT		0x5 	Bit-wise logical complement		
	XOR 	0x6		Bit-wise logical XOR	
	CMP		0x7		Arithmetic comparison (Logically a subtract, 
					but it sets the condition bits)

	BXX 	0x8 	Branch on Conditional
	JMP		0x9		Jump indirectly, through a register + offset
	JMPL	0x9		Jump and Link indirectly through a register + offset
	LD 		0xA		Load Direct from MEM

	LDI		0xB 	Load an Immediate Value
	LDX 	0xC		Load indirect through index register + offset
	ST 		0xD		Store Direct to MEM
	STX 	0xE		Store indirect through index register + offset
	
	HLT		0x1		Halt Execution


### Define Branch Conditions

		C = Carry Flag - Set if a carry out has occurred from the MSB of an unsigned operation.
		V = Overflow Flag - Set if result produces a 2's complement arithmetic overflow.
		N = Negative Flag - Set if the result is negative.
		Z = Zero Flag - Set if result is all 0's; arithmetic value of result == 0.

	Condition 	(checkcc)			Assembly	COND 	Conditional Branch
	1									BRA 	0000 	BRanch Always
	0									BNV 	1000	Branch NeVer
	~C									BCC 	0001	Branch on Carry Clear
	C									BCS 	1001	Branch on Carry Set
	~V									BVC 	0010	Branch on (V)Overflow Clear
	V									BVS 	1010	Branch on (V)Overflow Set
	Z									BEQ 	0011	Branch on EQual
	~Z									BNE		1011	Branch on Not Equal
	(~N & ~V) | (N & V)					BGE 	0100	Branch on Greater than or Equal
	(N & ~V) | (~N & V)					BLT		1100	Branch on Less Than
	~Z & ((~N & ~V) | (N & V))			BGT 	0101	Branch on Greater Than
	Z | ((N & ~V) | (~N & V))			BLE 	1101	Branch on Less than or Equal
	~N									BPL 	0110	Branch on positive (PLus)
	N									BMI 	1110	Branch on negative (MInus)

## Compiling Code
The verilog simulation is already compiled in the demo folder, but to recompile it, run the command

	iverilog -o vespa vespa.v

vespa is the outfile, a compiled verilog simulation.

To compile c code into VeSPA machine code, run the command

	vcc your_Program.c 
	
which generates v.out, a hex representation of the compiled program.

## Running Code
To run a compiled VeSPA program, rename the binary you want to run to 'v.out' in the demo folder.
Then, run the command
	
	vvp vespa

A trace of the status of the instruction count, values of PC, IR, Condition Codes, OPCODE of instruction, and the status of the 32 registers in reg_file.

