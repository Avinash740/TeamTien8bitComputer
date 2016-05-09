module setcc_tb;
	parameter WIDTH = 32;
	wire [WIDTH-1:0] op1,op2;
	wire [WIDTH  :0] result;
	
	wire add, sub, cmp;

	// Instantiate module being tested
	setcc set_condition(op1,op2,ressult, add, sub, cmp,c,z,n,v);

	// Read the manually generated test vectors to test setcc.
	rand_data_generator datagen(op1,op2,result,add,sub,cmp,c,z,n,c,clk);

	// Check the outputs of the module being tested with the manually generated test vectors
	checker check(op1,op2,result,add,sub,cmp,c,z,n,c,clk);

	//Instantiate Oscillator
	oscillator osc(clk,clk_n);

endmodule