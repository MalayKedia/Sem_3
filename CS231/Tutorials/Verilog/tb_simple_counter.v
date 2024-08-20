`timescale 1ns/1ps
module tb_simple_counter;

reg clk;
reg rst;
reg enable;

wire out;



initial begin
    $display("time\t, clk\t rst\t, enable\t, out\t ");
    $monitor ("%g\t %b\t   %b\t     %b\t      %b\t     ", $time, clk, rst, enable,out);	

    clk = 1;
    rst = 0;

    #10 rst = 1;
    #10 rst = 0;
    #10 enable  = 1;
    
    
    #150
    #5 $finish;
end

always begin
    #5 clk = ~clk;
end

simple_counter dut(.clk(clk),.rst(rst), .enable(enable), .out(out));

initial begin
    $dumpfile("simple_counter.vcd");
    $dumpvars(0,tb_simple_counter);
end

endmodule

