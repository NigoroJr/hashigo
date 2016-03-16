/**
 * This is the top-level module of the CarWash sample program.
 * The CarWash program is meant to be a demonstration of how ladder logic
 * can be converted to Verilog HDL.
 */

module CarWash(
    input [18:0]SW,
    input [3:0]KEY,
    input CLOCK_50,
    output [7:0]LEDG,
    output [18:0]LEDR
);

/* Physical inputs and outputs */
wire clk = CLOCK_50;
// On DE2-115, key up (default state) is 1, key pressed down is 0
wire start = !KEY[0];
wire stop = !KEY[1];
wire rst = KEY[2];

/* Declare outputs */
reg [7:0]step_counter;
reg [7:0]n_step_counter;
reg
    master_on,
    water,
    soap,
    dryer,
    pre_wash,
    main_wash,
    dry,
    water_1,
    water_2,
    timer_1_enabled,
    timer_1_done,
    timer_2_enabled,
    timer_2_done,
    timer_3_enabled,
    timer_3_done,

    n_master_on,
    n_water,
    n_soap,
    n_dryer,
    n_pre_wash,
    n_main_wash,
    n_dry,
    n_water_1,
    n_water_2,
    n_timer_1_enabled,
    n_timer_1_done,
    n_timer_2_enabled,
    n_timer_2_done,
    n_timer_3_enabled,
    n_timer_3_done
;

// DEBUG
assign LEDG[2:0] = {dryer, soap, water};
assign LEDR[15:0] = {step_counter, dry, main_wash, pre_wash};
// END DEBUG

// Make a slowed-down clock
wire tick;
DownClock down(clk, rst, tick);

/* Rung 0 */
wire n_master_on_wire;
Master master(start, stop, master_on, n_master_on_wire);

/* Rung 5 */
wire n_timer_1_done_wire;
Timer t1(clk, rst, tick, 2000, pre_wash, n_timer_1_done_wire);

/* Rung 6 */
wire n_timer_2_done_wire;
Timer t2(clk, rst, tick, 5000, main_wash, n_timer_2_done_wire);

/* Rung 8 */
wire n_timer_3_done_wire;
Timer t3(clk, rst, tick, 3000, dry, n_timer_3_done_wire);

reg [63:0]rung_count;
always @(posedge clk or negedge rst) begin
    if (rst == 1'b0) begin
        rung_count <= 64'd0;

        master_on <= 1'b0;

        // Outputs
        water <= 1'b0;
        soap <= 1'b0;
        dryer <= 1'b0;

        // States
        pre_wash <= 1'b0;
        main_wash <= 1'b0;
        dry <= 1'b0;

        step_counter <= 8'b0;
        water_1 <= 1'b0;
        water_2 <= 1'b0;
        timer_1_enabled <= 1'b0;
        timer_1_done <= 1'b0;
        timer_2_enabled <= 1'b0;
        timer_2_done <= 1'b0;
        timer_3_enabled <= 1'b0;
        timer_3_done <= 1'b0;

        n_master_on <= 1'b0;

        // Outputs
        n_water <= 1'b0;
        n_soap <= 1'b0;
        n_dryer <= 1'b0;

        // States
        n_pre_wash <= 1'b0;
        n_main_wash <= 1'b0;
        n_dry <= 1'b0;

        n_step_counter <= 8'b0;
        n_water_1 <= 1'b0;
        n_water_2 <= 1'b0;
        n_timer_1_enabled <= 1'b0;
        n_timer_1_done <= 1'b0;
        n_timer_2_enabled <= 1'b0;
        n_timer_2_done <= 1'b0;
        n_timer_3_enabled <= 1'b0;
        n_timer_3_done <= 1'b0;
    end
    else begin
        rung_count <= (rung_count + 64'b1) % 11;

        case (rung_count)
            0: begin
                n_master_on = n_master_on_wire;
            end
            1: begin
                if (step_counter == 8'd3) begin
                    n_step_counter = 8'd0;
                end
            end
            2: begin
                n_pre_wash = master_on & (step_counter == 8'd0);
            end
            3: begin
                n_main_wash = step_counter == 8'd1;
            end
            4: begin
                n_dry = step_counter == 8'd2;
            end
            5: begin
                n_timer_1_done = n_timer_1_done_wire;

                n_timer_1_enabled = pre_wash;
                n_water_1 = timer_1_enabled;
            end
            6: begin
                n_timer_2_done = n_timer_2_done_wire;

                n_timer_2_enabled = main_wash;
                n_water_2 = timer_2_enabled;
                n_soap = timer_2_enabled;
            end
            7: begin
                n_water = water_1 | water_2;
            end
            8: begin
                n_timer_3_done = n_timer_3_done_wire;

                n_timer_3_enabled = dry;
                n_dryer = timer_3_enabled;
            end
            9: begin
                if (timer_1_done | timer_2_done | timer_3_done) begin
                    n_step_counter = step_counter + 8'd1;
                end
            end
            10: begin
                master_on <= n_master_on;

                // Outputs
                water <= n_water;
                soap <= n_soap;
                dryer <= n_dryer;

                // States
                pre_wash <= n_pre_wash;
                main_wash <= n_main_wash;
                dry <= n_dry;

                step_counter <= n_step_counter;
                water_1 <= n_water_1;
                water_2 <= n_water_2;
                timer_1_enabled <= n_timer_1_enabled;
                timer_1_done <= n_timer_1_done;
                timer_2_enabled <= n_timer_2_enabled;
                timer_2_done <= n_timer_2_done;
                timer_3_enabled <= n_timer_3_enabled;
                timer_3_done <= n_timer_3_done;
            end
        endcase
    end
end

endmodule
