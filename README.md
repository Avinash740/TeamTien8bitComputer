# TeamTien8bitComputer

## Defining the VeSPA ISA 

### Architecture

	2^32 x 8bit wide memory, 32 x 8bit wide registers, 4 condition bits, C,V,N,Z.

### OPcodes
	
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


### Branch Conditions

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

### Instruction Format

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;}
.tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;}
.tg .tg-s6z2{text-align:center}
.tg .tg-baqh{text-align:center;vertical-align:top}
.tg .tg-yw4l{vertical-align:top}
</style>
<table class="tg">
  <tr>
    <th class="tg-yw4l"></th>
    <th class="tg-baqh">31-27</th>
    <th class="tg-baqh">26-23</th>
    <th class="tg-baqh">22</th>
    <th class="tg-baqh">21-17</th>
    <th class="tg-baqh">16</th>
    <th class="tg-baqh">15-11</th>
    <th class="tg-baqh">10-0<br></th>
  </tr>
  <tr>
    <td class="tg-baqh">ADD, AND, OR, SUB, XOR<br>(register to register)</td>
    <td class="tg-s6z2" rowspan="13">opcode</td>
    <td class="tg-baqh" colspan="2">rdst</td>
    <td class="tg-baqh">rs1</td>
    <td class="tg-baqh">0</td>
    <td class="tg-baqh">rs2</td>
    <td class="tg-baqh">0...0</td>
  </tr>
  <tr>
    <td class="tg-baqh">ADD, AND, OR, SUB, XOR<br>(immediate operand)</td>
    <td class="tg-baqh" colspan="2">rdst</td>
    <td class="tg-baqh">rs1</td>
    <td class="tg-baqh">1</td>
    <td class="tg-baqh" colspan="2">immed16</td>
  </tr>
  <tr>
    <td class="tg-yw4l">CMP (register to register)</td>
    <td class="tg-baqh" colspan="2">0...0</td>
    <td class="tg-baqh">rs1</td>
    <td class="tg-baqh">0</td>
    <td class="tg-baqh">rs2</td>
    <td class="tg-yw4l">0...0</td>
  </tr>
  <tr>
    <td class="tg-yw4l">CMP (immediate operand)</td>
    <td class="tg-baqh" colspan="2">0...0</td>
    <td class="tg-baqh">rs1</td>
    <td class="tg-baqh">1</td>
    <td class="tg-baqh" colspan="2">immed16</td>
  </tr>
  <tr>
    <td class="tg-yw4l">Bxx</td>
    <td class="tg-baqh">Condition Bits</td>
    <td class="tg-baqh" colspan="5">immed23</td>
  </tr>
  <tr>
    <td class="tg-yw4l">HALT, NOP</td>
    <td class="tg-baqh" colspan="6">0...0</td>
  </tr>
  <tr>
    <td class="tg-yw4l">JMP</td>
    <td class="tg-baqh" colspan="2">0...0</td>
    <td class="tg-baqh">rs1</td>
    <td class="tg-baqh">0</td>
    <td class="tg-yw4l" colspan="2">immed16<br></td>
  </tr>
  <tr>
    <td class="tg-yw4l">JMPL</td>
    <td class="tg-baqh" colspan="2">rdst</td>
    <td class="tg-baqh">rs1</td>
    <td class="tg-baqh">1</td>
    <td class="tg-yw4l" colspan="2">immed16</td>
  </tr>
  <tr>
    <td class="tg-yw4l">LD, LDI</td>
    <td class="tg-baqh" colspan="2">rdst</td>
    <td class="tg-baqh" colspan="4">immed22<br></td>
  </tr>
  <tr>
    <td class="tg-yw4l">LDX</td>
    <td class="tg-baqh" colspan="2">rdst</td>
    <td class="tg-baqh">rs1</td>
    <td class="tg-baqh" colspan="3">immed17</td>
  </tr>
  <tr>
    <td class="tg-yw4l">NOT</td>
    <td class="tg-baqh" colspan="2">rdst</td>
    <td class="tg-baqh">rs1</td>
    <td class="tg-baqh" colspan="3">0...0</td>
  </tr>
  <tr>
    <td class="tg-yw4l">ST</td>
    <td class="tg-baqh" colspan="2">rst</td>
    <td class="tg-baqh" colspan="4">immed22</td>
  </tr>
  <tr>
    <td class="tg-yw4l">STX</td>
    <td class="tg-baqh" colspan="2">rst</td>
    <td class="tg-baqh">rs1</td>
    <td class="tg-baqh" colspan="3">immed17<br></td>
  </tr>
</table>

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

A trace of the status of the instruction count, values of PC, IR, Condition Codes, OPCODE of instruction, and the status of the 32 registers in reg_file are printed out by vvp
