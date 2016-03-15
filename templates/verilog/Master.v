/**
 * The master-on logic module.
 */

module Master(
    input start,
    input stop,
    input i_master_on,
    output o_master_on
);

assign o_master_on = (i_master_on | start) & !stop;

endmodule
