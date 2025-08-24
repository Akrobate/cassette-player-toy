use <../libraries/commons.scad>
include <../configurations/global.scad>

module cassetteCncPiece(
    x_size = cassette_x_size,
    y_size = cassette_y_size,
    z_size = cassette_z_size,
    round_radius = cassette_round_radius,
) {

    echo(str("cassetteCncPiece ", "x_size: ", x_size, " y_size: ", y_size, " z_size: ", z_size));

    hull()
        forEachCoord([
            [0 + round_radius, 0 + round_radius],
            [0 + round_radius, y_size - round_radius],
            [x_size - round_radius, 0 + round_radius],
            [x_size - round_radius, y_size - round_radius]
        ])
            cylinder(r=round_radius, h=z_size, $fn=100);

}


cassetteCncPiece();
