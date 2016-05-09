# TeamTien8bitComputer

## Defining the VeSPA ISA 

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
	The verilog simulation is already compiled in the demo folder.
	To run a compiled VeSPA program, rename the binary to 'v.out' in the demo folder.
	