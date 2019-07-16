`timescale 1ps/100fs
module jdrvPTL(input wire din, output reg dout = 0);

    integer JJs = 2;
    real biasi = 0.379;
    real area = 0.0009;
    real delay = 9.9;

    always@(posedge din) begin
        dout <= #(delay) 1'b1;
        dout <= #(delay+2) 1'b0;
    end
endmodule
