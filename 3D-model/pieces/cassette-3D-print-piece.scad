use <../libraries/commons.scad>
use <../libraries/electronics.scad>
use <../libraries/breadboard.scad>
include <../configurations/global.scad>


// @todo: place the bar code positionning
module cassette3DPrintPiece(
    x_size = cassette_x_size,
    y_size = cassette_y_size,
    z_size = cassette_z_size,
    round_radius = cassette_round_radius,
    cny70set_x_point_coord = cassette_case_cny70set_x_point_coord,
    cny70set_y_point_coord = cassette_case_cny70set_y_point_coord
) {

    echo(str("cassette3DPrintPiece ", "x_size: ", x_size, " y_size: ", y_size, " z_size: ", z_size));

    patch_size = 7.3;

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
                2
            ]
        ) {

            cube([
                patch_size,
                patch_size,
                patch_size
            ], center = true);

            translateBreadboard(3, 0, 0)
                cube([
                    patch_size,
                    patch_size,
                    patch_size
                ], center = true);

            translateBreadboard(6, 0, 0)
                cube([
                    patch_size,
                    patch_size,
                    patch_size
                ], center = true);

            translateBreadboard(9, 0, 0)
                cube([
                    patch_size,
                    patch_size,
                    patch_size
                ], center = true);

        }
    }
}


cassette3DPrintPiece();
