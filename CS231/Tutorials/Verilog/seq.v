module simple_counter(clk,rst, enable, out);
    input clk;
    input rst;
    input enable;
    
    
    output reg out;
    
    reg [1:0] state, nxt_state;
    parameter S0 = 2'b00;
    parameter S1 = 2'b01;
    parameter S2 = 2'b10;
    parameter S3 = 2'b11;

    always @(posedge clk) begin
        if (rst) begin
            state <= S0;
        end
        else if (enable) begin
            state <= nxt_state;
        end
    end
    

    always@(*) begin
        case(state) 
            S0: 
                begin
                    nxt_state = S1;
                    out = 0; 
                end
            S1:
                begin
                    nxt_state = S2;
                    out = 0; 
                end
            S2:
                begin
                    nxt_state = S3;
                    out = 0; 
                end
            S3:
                begin
                    nxt_state = S0;
                    out = 1; 
                end
            default: 
                begin
                    nxt_state = S0;
                    out = 0; 
                end            
        endcase
        
    end

endmodule