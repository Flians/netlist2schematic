`timescale 1ps/100fs
module jspl3(input wire din, output reg doutA = 0, output reg doutB = 0, output reg doutC = 0);

    integer JJs = 4;
    real biasi = 0.3;
    real area = 0.0009;
    real delay = 4.1;
    real interval = 6.5;
    real din_last_change = -6.6; //satisfy the first arrival of din
    real tsetup; //i2c
    real thold;//c2i
        
    always@(posedge din) begin
        if($realtime - din_last_change > interval) begin
            din_last_change = $realtime;
            doutA <= #(delay) 1'b1;
            doutB <= #(delay) 1'b1;
            doutC <= #(delay) 1'b1;
            doutA <= #(delay+2) 1'b0;
            doutB <= #(delay+2) 1'b0;
            doutC <= #(delay+2) 1'b0;
        end
    end
endmodule