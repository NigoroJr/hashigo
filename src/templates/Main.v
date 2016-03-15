/**
 * This is the top-level module for ${program_name}
 * Feel free to modify the inputs and outputs and adjust them for your needs.
 */

module ${program_name}(
    input [18:0]SW,
    input [3:0]KEY,
    input CLOCK_50,
    output [7:0]LEDG,
    output [18:0]LEDR
);

/* Clocks and control signals */
wire clk = CLOCK_50;
// On Altera DE2-115, key up (default state) is 1, key pressed down is 0
wire start = !KEY[0];
wire stop = !KEY[1];
wire rst = KEY[2];

// DEBUG
// Note: Assign outputs to check if the design is working correctly
// END DEBUG

/* Declare address registers */
${addresses}

// Make a slowed-down clock
// TODO: remove if not used?
wire tick;
DownClock down(clk, rst, tick);

/* Stamp out modules such as Master and Timer */
${modules}

reg [63:0]rung_count;
always @(posedge clk or negedge rst) begin
    if (rst == 1'b0) begin
        rung_count <= 64'd0;

        ${reset_addresses}
    end
    else begin
        rung_count <= (rung_count + 64'b1) % (${num_rungs} + 1);

        case (rung_count)
            ${rungs}
            ${num_rungs}: begin
                ${update_addresses}
            end
        endcase
    end
end

endmodule
