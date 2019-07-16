`timescale 1ps/100fs
module jspl(input wire din, output reg doutA = 0, output reg doutB = 0);

    integer JJs = 3;
    real biasi = 0.3;
    real area = 0.0009;
    real delay = 4.3;
	real interval = 6.3;
	real din_last_change = -6.4; //satisfy the first arrival of din
    real tsetup = 0; //i2c
    real thold = 0;//c2i

	always@(posedge din) begin
		if($realtime - din_last_change > interval) begin
			din_last_change = $realtime;
			doutA <= #(delay) 1'b1;
        	doutB <= #(delay) 1'b1;
			doutA <= #(delay+2) 1'b0;
        	doutB <= #(delay+2) 1'b0;
		end
	end
endmodule
