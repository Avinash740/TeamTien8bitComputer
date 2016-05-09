module tienISA;

// Declare global parameters
parameter WIDTH = 8; 			// Datapath Width
parameter NUMREGS = 16;			// Number of registers in ISA
parameter MEMSIZE = (1 << 8);	// Size of simulated memory. Address range (0, 2^8 - 1)

// Declare storage elements in ISA
reg [7:0]		MEMFILE[MEMSIZE-1:0];	// Byte-wide main memory
reg [WIDTH-1:0]	REGFILE[NUMREGS-1:0]; 	// General-Purpose Registers
reg [WIDTH-1:0]	PGRM[MEMSIZE-1:0];		// INSTRUCTION MEMORY
reg [WIDTH-1:0]	PC;		 				// Program Counter
reg [WIDTH-1:0] IR;						// Instruction Register
reg [WIDTH-1:0]	ACC;	 				// Accumulator

reg RUN;								// Execute while RUN == 1

// Declare internal registers for ALU operations
reg [WIDTH-1:0] op1; 	// Source operand 1
reg [WIDTH-1:0] op2; 	// Source operand 1
reg [WIDTH:0] result; 	// Source operand 1

// Define OPcode and condition codes
// OPCODE 		Repres.	Translation					HDL Pseudocode							acc_write_en ALU_en mem_en mem_rw reg_write
`define GOL 	`d0 	// Goto Literal				current instruction pointer +/- 		00000
						//							operand [2:0] -> calc_instr_ptr
`define GOR		`d1 	// Goto RegVal				regfile[operand] -> calc_instr_ptr		00000
`define MEM_LW 	`d2 	// Memory Load Word			memfile[regfile[operand]] -> ACC 		10110
`define MEM_SW	`d3 	// Memory Store Word		ACC -> memfile[regfile[operand]] 		00100
`define SLL 	`d4 	// Shift Left Logical		ACC -> ACC 								11000
`define SRL		`d5 	// Shift Right Logical		ACC -> ACC 								11000
`define CLT 	`d6		// Compare Less Than		{ 8 {regfile[operand] < ACC } } -> ACC 	11000
`define CGT		`d7		// Compare Greater Than		{ 8 {regfile[operand] > ACC } } -> ACC 	11000
`define AND_FW 	`d8 	// AND Reg to ACC 			regfile[operand] & ACC -> ACC 			11000
`define OR_FW	`d9		// OR Reg to ACC 			regfile[operand] | ACC -> ACC 			11000
`define NOT_FW	`d10	// NOT ACC to ACC 			~ACC -> ACC 							11000
`define XOR_FW	`d11	// XOR Reg to ACC 			regfile[operand] ^ ACC -> ACC 			11000
`define MOV_WF 	`d12 	// Move ACC to Reg 			ACC -> regfile[operand] 				00001
`define MOV_LW	`d13	// Move Literal to ACC 		operand[3:0] -> ACC [3:0]				10000
`define ADD_FW 	`d14	// Increment ACC by RegVal 	ACC + regfile[operand] -> ACC 			11000
`define SKIP	`d15 	// SKIP																00000

// Define fields in instruction format
`define OPCODE 	IR [7:4]		// opcode field
`define flag	IR [4]			// flag
`define operand	IR [3:0]		// operand field

// Main fetch-execute loop
initial begin 

	$readmemh("v.out",MEMFILE);

	RUN = 1; 
	PC = 0;
	num_instrs = 0;

	while(RUN == 1)
		begin 
			num_instrs = num_instrs + 1 ;	// Number of instruction executed
			fetch; 							// Fetch the next instruction
			execute;						// Execute instruction in IR
			print_trace;					// print a trace of execution if enabled

		end

		$display("\nTotal number of instructions executed: %d\n\n", num_instrs);
	$finish;	// Terminate simulation and exit
end

// Task and function definitions
task fetch;
	begin 
		IR = PGRM[PC];
		PC = PC+1; 						//THIS WILL PROBABLY NEED TO BE FIXED
	end
endtask

task next_instr;
endtask

task execute;
	begin

		case (`OPCODE)
			
			`GOL: begin
				if ('flag == 1)
					PC = PC - `operand[2:0];
				else 
					PC = PC + `operand[2:0];
				
`define GOR		`d1 	// Goto RegVal				regfile[operand] -> calc_instr_ptr		00000
`define MEM_LW 	`d2 	// Memory Load Word			memfile[regfile[operand]] -> ACC 		10110
`define MEM_SW	`d3 	// Memory Store Word		ACC -> memfile[regfile[operand]] 		00100
`define SLL 	`d4 	// Shift Left Logical		ACC -> ACC 								11000
`define SRL		`d5 	// Shift Right Logical		ACC -> ACC 								11000
`define CLT 	`d6		// Compare Less Than		{ 8 {regfile[operand] < ACC } } -> ACC 	11000
`define CGT		`d7		// Compare Greater Than		{ 8 {regfile[operand] > ACC } } -> ACC 	11000
`define AND_FW 	`d8 	// AND Reg to ACC 			regfile[operand] & ACC -> ACC 			11000
`define OR_FW	`d9		// OR Reg to ACC 			regfile[operand] | ACC -> ACC 			11000
`define NOT_FW	`d10	// NOT ACC to ACC 			~ACC -> ACC 							11000
`define XOR_FW	`d11	// XOR Reg to ACC 			regfile[operand] ^ ACC -> ACC 			11000
`define MOV_WF 	`d12 	// Move ACC to Reg 			ACC -> regfile[operand] 				00001
`define MOV_LW	`d13	// Move Literal to ACC 		operand[3:0] -> ACC [3:0]				10000
`define ADD_FW 	`d14	// Increment ACC by RegVal 	ACC + regfile[operand] -> ACC 			11000
`define SKIP	`d15 	// SKIP																00000
			default : /* default */;
		endcase

// Utility operations and functions



endmodule


