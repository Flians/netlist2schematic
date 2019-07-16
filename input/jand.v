`timescale  1ps/100fs

module jand(input wire dina, input wire dinb, output reg dout = 0, input wire clk);
    integer JJs = 14;
    real biasi = 1.32;
    real area = 0.0036;
    real tdelay = 7.9;
    real tsetup = 1.4; //tsetup = i2c
    real thold = -2; //thold = c2i
    real din_last_changea;
    real din_last_changeb;
    real clk_last_change;
    reg stateA = 1'b0;
    reg stateB = 1'b0;
    //record the lastest time of dina's pulse
    always@(posedge dina) begin
        din_last_changea = $realtime;
        stateA <= 1'b1;
    end
    //record the lastest time of dinb's pulse
    always@(posedge dinb) begin
        din_last_changeb = $realtime;
        stateB <= 1'b1;
    end
    //set time limit
    always@(posedge clk) begin  
        dout <= 1'b0;
        if(((clk_last_change - din_last_changea) <= thold) && ((clk_last_change - din_last_changeb) <= thold) && 
            (($realtime - din_last_changea) >= tsetup) && (($realtime - din_last_changeb) >= tsetup) && (stateA == 1'b1) && (stateB == 1'b1)) begin
            clk_last_change =  $realtime;
            dout <= #(tdelay) 1'b1;
            dout <= #(tdelay+2) 1'b0;
        end
        else begin
            clk_last_change =  $realtime;  //record the lastest time of clk's pulse 
        end
        stateA <= 1'b0;
        stateB <= 1'b0;
    end

endmodule
