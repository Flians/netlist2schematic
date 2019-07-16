`timescale 1ps/100fs

module one_full_adder(A, B, Carry_in, clk, Sum, Carry_out);
        //the ports
        input A, B, Carry_in, clk;
	output Carry_out, Sum;
	wire[8:0] ds;
	//the first stage
	jdff dff_0_0(Carry_in, ds[0], clk);
	jxor xor_0_0(A, B, ds[1], clk);
	jand and_0_0(A, B, ds[2], clk);
	jspl spl_0_0(ds[0], ds[3], ds[4]);
	jspl spl_0_1(ds[1], ds[5], ds[6]);
        //the second stage;
	jxor xor_1_0(ds[3], ds[5], Sum, clk);
	jand and_1_0(ds[4], ds[6], ds[7], clk);
	jdff dff_1_0(ds[2], ds[8], clk);
	jcb cb_1_0(ds[7], ds[8], Carry_out);

endmodule
