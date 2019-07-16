`timescale  1ps/100fs
module jnot(input wire din, input wire clk, output reg dout = 1);
    //initialize dout to 1

    integer JJs = 11;
    real biasi = 0.847;
    real area = 0.0036;
    real delay = 6.5;
    real tsetup = 7.4; //tsetup = i2c
    real thold = -0.2; //thold = c2i

    reg buffer_out = 1'b0;
    real din_last_change;
    real clk_last_change;
    reg state = 1'b0;

    always@(posedge din) begin
        if(state == 0)
            din_last_change = $realtime;
        buffer_out <= 1'b1;
        state <= 1'b1; 
        end

    always@(posedge clk) begin
        if(((clk_last_change - din_last_change)<=thold) && (($realtime - din_last_change)>=tsetup) && (state == 1)) begin //first clk is used to let din into jnot. 
            state <= 1'b0;
        end
        else if((state == 0) && (buffer_out == 1)) begin //second clk is used to output data.
            dout <= #(delay) 1'b0;
            buffer_out <= 1'b0;
            dout <= #(delay+2) 1'b1;
        end
        else
            dout <= #(delay) 1'b1;  //default output 1
    end

endmodule
