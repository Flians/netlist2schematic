`timescale  1ps/100fs
module jndro(input wire din, input wire reset, input wire clk, output reg dout = 0);

    integer JJs = 11;
    real biasi = 1.112;
    real area = 0.0018;
    real delay = 6.3;
    real tsetup = 0.5; //tsetup = i2c
    real thold = -0.4; //thold = c2i

    real din_last_change;
	real clk_last_change;
    reg state = 1'b0;
    reg buffer_out = 1'b0;
	
	//when reset's pulse arrives, dout=0 and state=0
    always@(posedge reset) begin
        dout <= 1'b0;
        state <= 1'b0;
    end	
	
	//when din's pulse arrives, record the lastest time of din's pulse and change its state to 1
    always@(posedge din) begin
        if(state == 0) begin
            din_last_change = $realtime;
			state <= 1'b1;
        end
	end

    always@(posedge clk) begin
		//state==1 and satisfy arrival timing
        if(((clk_last_change - din_last_change)<=thold) && (($realtime - din_last_change)>=tsetup) && (state == 1)) begin
			clk_last_change =  $realtime;
			dout <= #(delay) 1'b1;
			dout <= #(delay+2) 1'b0;
		end
        else
			clk_last_change =  $realtime;
            dout <= 1'b0;
    end
    
endmodule
