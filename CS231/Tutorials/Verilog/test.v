module test #(parameter N = 16, M = 4)(input wire [N-1:0] [0:M-1] X  ,output wire [N-1:0] Z);
    assign Z = {N{1'b0}};
endmodule