use <../libraries/commons.scad>
use <../libraries/electronics.scad>
use <../libraries/breadboard.scad>
include <../configurations/global.scad>



module cassette3DPrintPiece(
    x_size = cassette_x_size,
    y_size = cassette_y_size,
    z_size = cassette_z_size,
    round_radius = cassette_round_radius,
    cny70set_x_point_coord = cassette_case_cny70set_x_point_coord,
    cny70set_y_point_coord = cassette_case_cny70set_y_point_coord
) {


    translate([0,0,7])
        scale([0.05, 0.05, 0.01])
            surface(file = "../assets/cassette_2D_2.png", center = false, invert = true);

    echo(str("cassette3DPrintPiece ", "x_size: ", x_size, " y_size: ", y_size, " z_size: ", z_size));

    difference() {
        hull()
            forEachCoord([
                [0 + round_radius, 0 + round_radius],
                [0 + round_radius, y_size - round_radius],
                [x_size - round_radius, 0 + round_radius],
                [x_size - round_radius, y_size - round_radius]
            ])
                cylinder(r=round_radius, h=z_size, $fn=100);



        translate(
            [
                getSizeFromPointCount(cny70set_x_point_coord - 1) - (cassette_case_x_size - cassette_x_size) / 2 + 2.54 / 2,
                getSizeFromPointCount(cny70set_y_point_coord - 1) - (cassette_case_y_size - cassette_y_size) / 2 + 2.54 / 2,
                0.5
            ]
        ) {
            for (offset_breadboard = [0, 3, 6, 9])
                translateBreadboard(offset_breadboard, 0, 0)
                    barcodePatch();
        }
    }
}

module barcodePatch() {
    patch_size = 6.5;
    translate([0,0, -patch_size / 2])
        cube(
            [
                patch_size,
                patch_size,
                patch_size
            ],
            center = true
        );
}


cassette3DPrintPiece();
