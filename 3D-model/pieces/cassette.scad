use <../libraries/commons.scad>


module cassette() {

    gold_number = 1.618;

    x_size = 20 * 2.54;
    y_size = 20 * 2.54 / gold_number;
    z_size = 4;

    round_radius = 4;

    //cube([x_size, y_size, z_size]);

    hull()
        forEachCoord([
            [0 + round_radius, 0 + round_radius],
            [0 + round_radius, y_size - round_radius],
            [x_size - round_radius, 0 + round_radius],
            [x_size - round_radius, y_size - round_radius]
        ])
            cylinder(r=round_radius, h=z_size);

}


cassette();
