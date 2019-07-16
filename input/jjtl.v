`timescale 1ps/100fs
module jjtl(input wire din, output reg dout = 0);
    
    integer JJs = 2;
    real biasi = 0.3;
    real area = 0.0009;
    real delay = 3.6;
    real tsetup; //i2c
    real thold;//c2i
    
    always@(posedge din) begin
        dout <= #(delay) 1'b1;
        dout <= #(delay+2) 1'b0;
    end
endmodule
