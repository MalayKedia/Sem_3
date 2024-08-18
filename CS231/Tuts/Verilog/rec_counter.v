//assuming N is a multiple of 2

module rec_count #(parameter N = 32)(
    input wire change , input wire clk, output reg [N-1:0] next
);
wire [N/2-1:0] l;
wire [N/2-1:0] r;
wire select;
// assign l = prev[N-1:N/2];
// assign r = prev[N/2-1:0];
parameter p1 = {N/2{1'b1}};
assign select = 
rec_count #(.N(N/2)) rc0(.clk(clk),.change(1'b1),.next(r));



generate
    if (N==1) begin
        
    end
    else begin
        
    end
endgenerate

always @(posedge clk) begin
    
end


endmodule