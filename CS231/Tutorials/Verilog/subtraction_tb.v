module test ();
    
reg [31:0] x; // our goal is going to be to compute y - x
reg [31:0] y;
wire [31:0] z; // z = y - x

subtractor #(.N(32)) dut (.A(x),.B(y),.x(z));

initial begin
    // here we put our testcases
    x = 59;
    y = 61;
    #5
    x = 77;
    y = 99;
    #5
    x = 30;
    y = 15; // lets just see what happens :)
end

initial begin
    // here we put out monitoring
    $monitor("x = %d\t y = %d\t z = %d\t",x,y,z);
end

endmodule