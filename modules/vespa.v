module vespa;

	// Enable TRACE_PC, TRACE_CC, and TRACE_REGS
	`define TRACE_PC 1
	`define TRACE_CC 1
	`define TRACE_REGS 1
	`define TRACE_IR 1

	// Declare global parameters
	parameter WIDTH = 32; 			// Datapath Width
	parameter NUMREGS = 32;			// Number of registers in ISA
	parameter MEMSIZE = (1 << 13);	// Size of simulated memory. Address range (0, 2^13 - 1)

	integer num_instrs;
	integer i;

	// Declare storage elements in ISA
	reg [7:0]		MEM[MEMSIZE-1:0];
	reg [WIDTH-1:0]	R[NUMREGS-1:0];
	reg [WIDTH-1:0]	PC;		 				// Program Counter
	reg [WIDTH-1:0] IR;						// Instruction Register
	reg 			C;	 					// Carry Flag - Set if a carry out has occurred from the MSB of an unsigned operation.
	reg 			V;						// Overflow Flag - Set if result produces a 2's complement arithmetic overflow.
	reg 			N;	 					// Negative Flag - Set if the result is negative.
	reg 			Z;						// Zero Flag - Set if result is all 0's; arithmetic value of result == 0.

	// Z = ~(|result[WIDTH-1:0]);
	// V = 	(result[WIDTH-1] & ~op1[WIDTH-1] & ~op1[WIDTH-1] &~(subt^op2[WIDTH-1])) | 
	// 		(~result[WIDTH-1] & op1[WIDTH-1] & (subt^op2[WIDTH-1]))
	//		overflow occurs whenever the sign of the result is the opposite the signs of the 2 input operands
	//		reversing the sign bit for the second operand makes this operation true for negative numbers
	//		subt = 0 when adding, and subt = 1 when subtracting.

	reg RUN;								// Execute while RUN == 1

	// Declare internal registers for ALU operations
	reg [WIDTH-1:0] op1; 	// Source operand 1
	reg [WIDTH-1:0] op2; 	// Source operand 1
	reg [WIDTH:0] result; 	// Source operand 1

	// Define OPcode and condition codes
	`define NOP 	5'd0
	`define ADD		5'd1
	`define SUB 	5'h2 	
	`define OR 		5'h3 
	`define AND		5'h4
	`define NOT		5'h5 	
	`define XOR 	5'h6		
	`define CMP		5'h7		
	`define BXX 	5'h8 	
	`define JMP		5'h9
	`define JMPL	5'h9		
	`define LD 		5'hA	
	`define LDI		5'hB
	`define LDX 	5'hC
	`define ST 		5'hD
	`define STX 	5'hE
	`define HLT		5'd31

	//Define Branch Conditions
	`define BRA 	4'b0000
	`define BNV 	4'b1000
	`define BCC 	4'b0001
	`define BCS 	4'b1001
	`define BVC 	4'b0010
	`define BVS 	4'b1010
	`define BEQ 	4'b0011
	`define BNE		4'b1011
	`define BGE 	4'b0100
	`define BLT		4'b1100
	`define BGT 	4'b0101
	`define BLE 	4'b1101
	`define BPL 	4'b0110
	`define BMI 	4'b1110

	// Define fields in instruction format
	`define OPCODE 	IR [31:27]		// opcode field
	`define rdst	IR [26:22]		// flag
	`define rs1		IR [21:17]		// source register 1
	`define IMM_OP	IR [16]			// IR[16] == 1 when source 2 is immediate operand
	`define rs2		IR [15:11]		// source register 2
	`define rst 	IR [26:22]		// source register for store op
	`define immed23	IR [22:0]		// 23-bit literal field
	`define immed22	IR [21:0]		// 23-bit literal field
	`define immed17	IR [16:0]		// 17-bit literal field
	`define immed16	IR [15:0]		// 16-bit literal field
	`define COND 	IR [26:23]		// Branch Conditions


	`define operand	IR [3:0]		// operand field

	// Main fetch-execute loop
	initial begin 

		for (i = 0; i < MEMSIZE; i = i + 1) 
			begin
				MEM[i]= 8'hF;		// Byte-wide main memory
		end
		for (i = 0; i < NUMREGS; i = i + 1)
			begin
				R[i] = 8'h0; 		// General-Purpose Registers
		end


		$readmemh("v.out",MEM);

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
			IR = read_mem(PC);
			PC = PC+4;
		end
	endtask

	function [WIDTH-1:0] read_mem;
		input [WIDTH-1:0] addr; 		// Address from which to read

		read_mem = {MEM[addr],MEM[addr+1],MEM[addr+2],MEM[addr+3]};
	endfunction 	// read_mem

	task execute;
		begin

			case (`OPCODE)
				
				`ADD: begin
					if (`IMM_OP == 0)
						op2 = R[`rs2];
					else 
						op2 = sext16(`immed16);
					op1 = R[`rs1];
					result = op1 + op2;
					R[`rdst] = result [WIDTH-1:0];
					setcc(op1, op2,result,0);
				end

				`AND: begin
					if (`IMM_OP == 0)
						op2 = R[`rs2];
					else 
						op2 = sext16(`immed16);
					op1 = R[`rs1];
					result = op1 & op2;
					R[`rdst] = result [WIDTH-1:0];
				end

				`XOR: begin
					if (`IMM_OP == 0)
						op2 = R[`rs2];
					else 
						op2 = sext16(`immed16);
					op1 = R[`rs1];
					result = op1 ^ op2;
					R[`rdst] = result [WIDTH-1:0];
				end

				`CMP: begin
					if (`IMM_OP == 0)
						op2 = R[`rs2];
					else 
						op2 = sext16(`immed16);
					op1 = R[`rs1];
					result = op1 - op2;
					setcc(op1, op2,result,1);
				end

				`BXX: begin
					if (checkcc(Z,C,N,V) == 1)
						PC = PC + sext23(`immed16);
				end

				`HLT: begin
					RUN = 0;
				end

				`JMP: begin
					if (`IMM_OP == 1)		// If JAL-ing, tho old PC must be saved before it is lost
						R [`rdst] = PC;		// Linking not automatic
					PC = R [`rs1] + sext16(`immed16);
				end

				`LD: begin
					R[`rdst] = read_mem (sext22(`immed22));
				end

				`LDI: begin
					R[`rdst] = sext22(`immed22);
				end

				`LDX: begin
					R[`rdst] = read_mem(R[`rs1] + sext17(`immed17));
				end

				`NOP: begin
				end

				`NOT: begin
					op1 = R[`rs1];
					result = ~op1;
					R[`rdst] = result[WIDTH-1:0];
				end

				`OR:begin
					if(`IMM_OP == 0)
						op2 = R[`rs2];
					else
						op2 = sext16(`immed16);
					op1 = R[`rs1];
					result = op1 | op2;
					R[`rdst] = result [WIDTH-1:0];
				end

				`ST: begin
					write_mem(sext22(`immed22),R[`rst]);
				end

				`STX: begin
					write_mem(R[`rs1] + sext17(`immed17), R[`rst]);
				end

				`SUB: begin
					if (`IMM_OP == 0)
						op2 = R[`rs2];
					else
						op2 = sext16(`immed16);
					op1 = R[`rs1];
					result = op1 - op2;
					R[`rdst] = result [WIDTH-1:0];
					setcc(op1, op2, result, 1);
				end

				default : begin
					$display("Error: undefined opcode: %d", `OPCODE);
				end

			endcase

		end
	endtask


	// Utility operations and functions

	function [WIDTH-1:0] sext16; 	// 16 bit input
		input [15:0] d_in;			// bit field to be sign-extended
		sext16[WIDTH-1:0] = { {(WIDTH-16){d_in[15]}} , d_in };
	endfunction

	function [WIDTH-1:0] sext17; 	// 17 bit input
		input [15:0] d_in;			// bit field to be sign-extended
		sext17[WIDTH-1:0] = { {(WIDTH-17){d_in[15]}} , d_in };
	endfunction

	function [WIDTH-1:0] sext22; 	// 22 bit input
		input [15:0] d_in;			// bit field to be sign-extended
		sext22[WIDTH-1:0] = { {(WIDTH-22){d_in[15]}} , d_in };
	endfunction

	function [WIDTH-1:0] sext23; 	// 23 bit input
		input [15:0] d_in;			// bit field to be sign-extended
		sext23[WIDTH-1:0] = { {(WIDTH-23){d_in[15]}} , d_in };
	endfunction

	task write_mem;
		
		input [WIDTH-1:0] addr;		// Address to which to write
		input [WIDTH-1:0] data;		// Data to be written

		begin 
			{MEM[addr],MEM[addr+1],MEM[addr+2],MEM[addr+3]} = data;
		end

	endtask // write_mem

	task setcc;
		input [WIDTH-1:0] op1;			// Operand 1
		input [WIDTH-1:0] op2;			// Operand 2
		input [WIDTH  :0] result;		// Calculated Result Value
		input subt;						// Checks if input was a subtraction. If set, sign bit of 
										// 		op2 must be inverted to properly find V, overflow

		begin
			C = result[WIDTH];			// Carryout of the result
			Z = ~(|result[WIDTH-1:0]);	// Zero if all bits are zero
			N = result[WIDTH-1];		// Negative if MSB == 1
			V = 	(result[WIDTH-1] & ~op1[WIDTH-1] & ~op1[WIDTH-1] &~(subt^op2[WIDTH-1])) | 
					(~result[WIDTH-1] & op1[WIDTH-1] & (subt^op2[WIDTH-1])) ;
										//	Overflow occurs whenever the sign of the result is the 
										// 		opposite the signs of the 2 input operands reversing 
										// 		the sign bit for the second operand makes this operation 
										//		true for negative numbers subt = 0 when adding, 
										//		and subt = 1 when subtracting.
	 	end

	 endtask

	function checkcc;
		input Z;
		input C;
		input N;
		input V;

		begin
			case (`COND)

				`BRA:begin
					checkcc = 1;
				end

				`BNV:begin
					checkcc = 0;
				end

				`BCC:begin
					checkcc = ~C;
				end

				`BCS:begin
					checkcc = C;
				end

				`BVC:begin
					checkcc = ~V;
				end

				`BVS:begin
					checkcc = V;
				end

				`BEQ:begin
					checkcc = Z;
				end

				`BNE:begin
					checkcc = ~Z;
				end

				`BGE:begin
					checkcc = (~N & ~V) | (N & V);
				end


				`BLT:begin
					checkcc = (N & ~V) | (~N & V);
				end


				`BGT:begin
					checkcc = ~Z & ( (~N & ~V) | (N & V) );
				end


				`BLE:begin
					checkcc = Z | ( (N & ~V) | (~N & V) );
				end


				`BPL:begin
					checkcc = ~N;
				end


				`BMI:begin
					checkcc = N;
				end
			
			endcase // COND
		end
	endfunction 	// checkcc

	task print_trace;
		integer i;
		integer j;
		integer k;

		begin
			`ifdef TRACE_PC
			begin
				$display("Instruction #:%d\tPC=%h\tOPCODE=%d",num_instrs,PC,`OPCODE);
			end
			`endif //TRACE_PC

			`ifdef TRACE_CC
			begin
				$display("Condition codes: C=%b V=%b Z=%d N=%b", C,V,Z,N);
			end
			`endif 	//TRACE_CC

			`ifdef  //TRACE_IR
			begin
				$display("Instruction Register:%b",IR);
			`endif 	//TRACE_IR

			`ifdef TRACE_REGS
			begin
				k = 0;
				for (i = 0; i < NUMREGS; i = i + 4)
					begin
						$write("R[%d]:",k);
						for(j = 0; j <= 3; j = j + 1)
							begin
								$write(" %h",R[k]);
								k=k+1;
							end
						$write("\n");
					end
				$write("\n");
			end
			`endif
		end
	endtask

endmodule