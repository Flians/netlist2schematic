`timescale 1ps/100fs
module jptl(input wire din, output reg dout = 0);
    
    integer JJs = 0;
    real biasi = 0;
    real area = 0.000225;
    real delay = 0.344;
        
    always@(posedge din) begin
        dout <= #(delay) 1'b1;
        dout <= #(delay+2) 1'b0;
    end
endmodule
