`timescale  1ps/100fs

module jdff(input wire din, output reg dout = 0, input wire clk);

    integer JJs = 6;
    real biasi = 0.718;
    real area = 0.0009;
    real tdelay = 5.1;
	real tsetup = 1; //i2c
    real thold = -0.7; //c2i 
	reg state = 1'b0;
    real din_last_change;
	real clk_last_change;

	//record the lastest time of din's pulse
    always@(posedge din) begin
        din_last_change = $realtime;
		state <= 1'b1;
    end
	
    always@(posedge clk) begin
		//set time limit
        if(((clk_last_change - din_last_change) <= thold) && (($realtime - din_last_change) >= tsetup)) begin
				clk_last_change =  $realtime;
            	dout <= #(tdelay) state;
                dout <= #(tdelay+2) 1'b0;
            end
		else begin
			dout <= 1'b0;
			//record the lastest time of clk's pulse
			clk_last_change =  $realtime;
		end
		state <= 1'b0;
    end
endmodule