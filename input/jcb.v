`timescale 1ps/100fs
module jcb(input wire dina, input wire dinb, output reg dout = 0);

    integer JJs = 7;
    real biasi = 0.88;
    real area = 0.0009;
    real tdelay = 8.2;
    reg buffera = 1'b0;
    reg bufferb = 1'b0;
    real din_last_changea;
    real din_last_changeb;
    real tlimit = 5;

    always@(posedge dina) begin
        //record the lastest time of dina's pulse
        din_last_changea = $realtime;
        //the absolute value between dina's pulse and dinb's pulse must greater than tlimit
        if(din_last_changea - din_last_changeb > tlimit) begin
            dout <= #(tdelay) 1'b1;
            dout <= #(tdelay+2) 1'b0;
        end
    end

    always@(posedge dinb) begin
        din_last_changeb = $realtime;
        if(din_last_changeb - din_last_changea > tlimit) begin
            dout <= #(tdelay) 1'b1;
            dout <= #(tdelay+2) 1'b0;
        end
    end

endmodule
