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

    echo(str("cassette3DPrintPiece ", "x_size: ", x_size, " y_size: ", y_size, " z_size: ", z_size));
    
    svg_x_size = 173.49324;
    svg_y_size = 107.69361;

    cassette_svg_height = 1;
    barcode_patch_z_size = 0.5;

    translate([0,0,z_size - cassette_svg_height])
        render()
            intersection() {
                scale([
                    x_size / (svg_x_size / 72 * 25.4),
                    y_size / (svg_y_size / 72 * 25.4) * 1.01,
                    1]
                )
                    linear_extrude(height = cassette_svg_height)
                        import("../assets/cassette_2D.svg");

                cassetteCountour(x_size, y_size, cassette_svg_height, round_radius);

            }

    difference() {
        cassetteCountour(x_size, y_size, z_size - cassette_svg_height, round_radius);

        translate(
            [
                getSizeFromPointCount(cny70set_x_point_coord - 1) - (cassette_case_x_size - cassette_x_size) / 2 + 2.54 / 2,
                getSizeFromPointCount(cny70set_y_point_coord - 1) - (cassette_case_y_size - cassette_y_size) / 2 + 2.54 / 2,
                barcode_patch_z_size
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


module cassetteCountour(
    x_size,
    y_size,
    z_size,
    round_radius
) {
    hull()
        forEachCoord([
            [0 + round_radius, 0 + round_radius],
            [0 + round_radius, y_size - round_radius],
            [x_size - round_radius, 0 + round_radius],
            [x_size - round_radius, y_size - round_radius]
        ])
            cylinder(r=round_radius, h=z_size, $fn=100);
}


cassette3DPrintPiece();
