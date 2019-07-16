`timescale 1ps/100fs
module jrecPTL(input wire din, output reg dout = 0);

    integer JJs = 3;
    real biasi = 0.14;
    real area = 0.0009;
    real delay = 0; // drvPTL + recPTL = 9.9
	    
	always@(posedge din) begin
		dout <= #(delay) 1'b1;
		dout <= #(delay+2) 1'b0;
	end
endmodule
