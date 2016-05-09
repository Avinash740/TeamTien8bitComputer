module rand_data_generator(op1,op2,result,add,sub,cmp,clk);

	parameter WIDTH = 32;
	output [WIDTH - 1:0] op1, op2;
	output[WIDTH:0] result;
	output add,sub,cmp;
	input clk;

	integer input_file;
	integer i;
	reg[WIDTH-1:0] op1, op2;
	reg [WIDTH:0] result;
	reg add,sub,cmp;
	
	always @(posedge clk) 
		begin 
			#(5);
			if ($time > 100000)
				$stop;
			op1 = $random;
			op2 = $random;
			add = $random;

			if (add == 1)
				begin
					sub = 0;
					cmp = 0;
					result = op1 + op2;
			end
			else
				begin
					sub = $random;
					if (sub == 1)
						cmp = 0;
					else 
						cmp = 1;
					result = op1 - op2;
			end
	end	
endmodule // data_generator