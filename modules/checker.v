module checker (op1,op2,result,add,sub,cmp,clk);

	parameter WIDTH = 32;
	input [WIDTH - 1:0] op1, op2;
	input [WIDTH:0] result;
	input add,sub,cmp;
	
	reg ref_c,ref_v,ref_n,ref_z,subt;

	initial
		begin
			#(20);
			$display("%h\t%h\t%h %b %b %b at time %d",op1,op2,resul,add,sub,cmp,$time);
			subt = sub || cmp;
			ref_c = result[WIDTH];			// Carryout of the result
			ref_z = ~(|result[WIDTH-1:0]);	// Zero if all bits are zero
			ref_n = result[WIDTH-1];		// Negative if MSB == 1
			rev_v = 	(result[WIDTH-1] & ~op1[WIDTH-1] & ~op1[WIDTH-1] &~(subt^op2[WIDTH-1])) | 
					(~result[WIDTH-1] & op1[WIDTH-1] & (subt^op2[WIDTH-1])) ;

			if ( (ref_c != c) || (ref_z != z) || (ref_n != n) || (ref_v != v)   )
				begin
					$display("-E- Error in verifying condition codes");
					$display("Computed CC:C = %b Z = %b N = %b V = %b",c,z,n,v);
					$display("Reference CC:C = %b Z = %b N = %b V = %b",ref_c,ref_z,ref_n,ref_v);
					$stop;
				end
			else
				$display("Condition codes verified C = %b Z = %b N = %b V = %b",c,z,n,v);
		end

endmodule