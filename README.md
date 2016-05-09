# TeamTien8bitComputer

## Defining the VeSPA ISA 

### Architecture

	2^13 x 8bit wide memory, 32 x 8bit wide instructions, 4 condition bits.

### Define OPcode and condition codes
	
	NOP 	0x0
	ADD		0x1			 
	SUB 	0x2 		
	OR 		0x3 		
	AND		0x4			
	NOT		0x5 		
	XOR 	0x6			
	CMP		0x7

	BXX 	0x8 		
	JMP		0x9			
	JMPL	0x9			
	LD 		0xA

	LDI		0xB
	LDX 	0xC
	ST 		0xD
	STX 	0xE
	
	HLT		0x1


### Define Branch Conditions

	BRA 	0000
	BNV 	1000
	BCC 	0001
	BCS 	1001
	BVC 	0010
	BVS 	1010
	BEQ 	0011
	BNE		1011
	BGE 	0100
	BLT		1100
	BGT 	0101
	BLE 	1101
	BPL 	0110
	BMI 	1110

## Running Code
	The verilog simulation is already compiled in the demo folder, but to recompile it, run the command

		iverilog -o vespa vespa.v

	vespa is the compiled verilog simulation.

	To run a compiled VeSPA program, rename the binary you want to run to 'v.out' in the demo folder.
		Then, run the command

		vvp vespa

	A trace of the status of the instruction count, values of PC, IR, Condition Codes, OPCODE of instruction, and the status of the 32 registers in reg_file.

	To compile code, run the command
	
		vcc your_Program.c 
	
	which generates v.out, a hex representation of the compiled program.