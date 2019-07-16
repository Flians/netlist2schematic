`timescale 1ps/100fs
module jxor(input wire dina, input wire dinb, output reg dout = 0, input wire clk);
                            
    integer JJs = 11;
    real biasi = 1.068;
    real area = 0.0036;
    real tdelay = 6.5;
    real tsetup = 3.7;//i2c
    real thold = -4.1;//c2i
    real din_last_changea;
    real din_last_changeb;
    real clk_last_change;
    reg stateA = 1'b0;
    reg stateB = 1'b0;

    always@(posedge dina) begin
        din_last_changea = $realtime;
        stateA <= 1'b1;
    end

    always@(posedge dinb) begin
        din_last_changeb = $realtime;
        stateB <= 1'b1;
    end

    always@(posedge clk) begin
        dout <= 1'b0;
        if((((clk_last_change - din_last_changea) <= thold)&&(($realtime - din_last_changea)>=tsetup)&&(stateA == 1'b1)&&(stateB == 1'b0)) || 
            (((clk_last_change - din_last_changeb) <= thold) && (($realtime - din_last_changeb)>=tsetup) && (stateB == 1'b1) && (stateA == 1'b0))) begin
            clk_last_change =  $realtime;
            dout <= #(tdelay) 1'b1;
            dout <= #(tdelay+2) 1'b0;
        end
        else begin
            clk_last_change =  $realtime;
        end
        stateA <= 1'b0;
        stateB <= 1'b0;
    end
endmodule