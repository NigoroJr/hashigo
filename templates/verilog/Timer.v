/**
 * The Timer ladder logic module in Verilog.
 * This module counts in milliseconds and flips on the `done' bit once that
 * much time has elapsed.
 *
 * \param[in] clk the system clock of the FPGA.
 * \param[in] rst the reset signal.
 * \param[in] tick the slowed-down system clock. Frequency must be 1 kHz
 *                 (1 ms per tick).
 * \param[in] [31:0] preset the time for this timer to wait in milliseconds.
 * \param[in] enabled 1 if this timer should be enabled (i.e. counting), 0
 *                    otherwise. Counter is reset when enabled becomes low.
 * \param[out] done 1 if counting is done, 0 otherwise. This remains high
 *                  after time has elapsed until `enabled' or `rst' is
 *                  triggered.
 */

module Timer(
    input clk,
    input rst,
    input tick,
    input [31:0]preset,
    input enabled,
    output done
);

// Used to figure out high-low, low-high
// transition of down-sampled clock signal
reg last_tick;
reg [31:0] counter;
reg done_reg;
assign done = done_reg;

always @(posedge clk or negedge rst) begin
    if (rst == 1'b0) begin
        last_tick <= 1'b0;
        counter <= 32'b0;
        done_reg <= 1'b0;
    end
    else begin
        last_tick <= tick;

        if (enabled == 1'b0) begin
            counter <= 32'b0;
            done_reg <= 1'b0;
            last_tick <= 1'b0;
        end
        // Capture posedge of down-sampled clock
        else if (tick != last_tick && tick == 1'b1) begin
            if (counter >= preset) begin
                done_reg <= 1'b1;
            end
            else begin
                counter <= counter + 1;
                done_reg <= 1'b0;
            end
        end
        else begin
            done_reg <= 1'b0;
        end
    end
end

endmodule
