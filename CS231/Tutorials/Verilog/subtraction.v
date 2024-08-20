module halfAdder (
    a,b,S,cout
);

input a;
input b;
output S;
output cout;

xor(S,a,b);
and(cout,a,b);


endmodule

module fullAdder (
    a,b,cin,S,cout
);

input a;
input b;
input cin;
output S;
output cout;

wire sumAPlusB, carryAPlusB,carry,tmp;
halfAdder h1(.a(a),.b(b),.S(sumAPlusB),.cout(carryAPlusB));
halfAdder h2(.a(cin),.b(sumAPlusB),.S(S),.cout(carry));
halfAdder h3(.a(carry),.b(carryAPlusB),.S(cout),.cout(tmp)); // tmp is
// always 0 but why

endmodule

module rca #(
    parameter N = 32
) (
    a,b,S,cout
);

input wire [N-1:0] a;
input wire [N-1:0] b;
output wire [N-1:0] S; // N-1 least significant bits of a+b
output wire cout; // MSB of a+b

// we need N full adders
// we must use generate statement!!
wire carry[N:0];
assign carry[0] = 0;
generate
    genvar i;
    for (i=0; i<N; i=i+1) begin
        fullAdder t (.a(a[i]),.b(b[i]),.cin(carry[i]),.S(S[i]),.cout(carry[i+1])); 
    end
    assign cout = carry[N];
endgenerate

endmodule


module twosComplement #(
    parameter N = 32
) (
    a,c,carry // carry tells you if a is 0
);

input wire [N-1:0] a;
output wire[N-1:0] c;
output wire carry;

wire [N-1:0]d;
// wire carry;
assign d = ~a;

rca #(.N(N)) dut (.a(d),.b(1),.S(c),.cout(carry));

endmodule

module subtractor #(
    parameter N = 32
) (
    A,B,x
);
    
input [N-1:0] A;
input [N-1:0] B;
output [N-1:0] x; // x = B - A :)

wire [N-1:0] aComp;
wire tmp;
wire sign;

twosComplement #(.N(N)) dut1 (.a(A),.c(aComp),.carry(tmp));
rca #(.N(N)) dut2 (.a(B),.b(aComp),.S(x),.cout(sign));

endmodule

