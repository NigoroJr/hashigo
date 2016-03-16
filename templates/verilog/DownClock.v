/**
 * Slows down the system clock (however fast it is) to 1 kHz.
 * The slowed-down clock is used for counting time in milliseconds.
 * Set the parameter `TICKS' in this module to an appropriate value so that
 * the output is a signal that has frequency of 1 kHz. For Altera DE2-115,
 * `TICKS' is set to 50,000 because the board has a clock of 50 MHz.
 *
 * \param[in] clk the system clock.
 * \param[in] rst the reset signal.
 * \param[out] tick the down-sampled clock with frequency of 1 kHz.
 */

module DownClock(
    input clk, rst,
    // Slow down `clk' so that it can be used as a timer
    output tick
);

// Assuming 50 MHz clock (since that's what DE2-115 has)
// 1 tick per 1 ms (i.e. 1 kHz)
parameter TICKS = 50000;

reg [31:0]count;
assign tick = tick_reg;
reg tick_reg;

always @(posedge clk or negedge rst) begin
    if (rst == 1'b0) begin
        count <= 32'b0;
        tick_reg <= 1'b0;
    end
    else begin
        if (count >= TICKS / 2) begin
            tick_reg <= !tick_reg;
            count <= 32'b0;
        end
        else begin
            count <= count + 1;
        end
    end
end

endmodule
