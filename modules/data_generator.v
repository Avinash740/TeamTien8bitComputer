module data_generator(op1,op2,result,add,sub,cmp,clk);

	parameter WIDTH = 32;
	output [WIDTH - 1:0] op1, op2;
	output[WIDTH:0] result;
	output add,sub,cmp;
	input clk;

	integer input_file;
	integer EOF;
	reg[WIDTH-1:0] op1, op2;
	reg [WIDTH:0] result;
	reg add,sub,cmp;
	
	initial 
		begin
			input_file = $fopen("./test_vectors","r");
			if (input_file == 0)
				$stop;
	end
	always @(posedge clk) 
		begin 
			#(5);
			EOF = $fscanf(input_file, "%h %h %b %b %b", op1,op2,add,sub,cmp);
			if (EOF == -1)
				$stop;
			if (add == 1)
				result = op1 + op2;
			else
				result = op1 - op2;
	end
endmodule // data_generator