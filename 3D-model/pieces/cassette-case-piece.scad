use <../libraries/commons.scad>
use <../libraries/electronics.scad>

use <./subpieces/rounded-pane.scad>
include <../configurations/global.scad>


module cassetteCasePiece(
    cassette_x_size = cassette_x_size,
    cassette_y_size = cassette_y_size,
    cassette_z_size = cassette_z_size,
    cassette_round_radius = cassette_round_radius,

    cassette_case_x_size = cassette_case_x_size,
    cassette_case_y_size = cassette_case_y_size,
    cassette_case_z_size = cassette_case_z_size,
    cassette_case_round_radius = cassette_case_round_radius,

    cassette_case_x_y_margin = cassette_case_x_y_margin,

    throws_margin = cassette_case_throws_margin,
    throws_diameter = cassette_case_throws_diameter,
    grip_enveloppe_diameter = cassette_case_grip_enveloppe_diameter,
    grip_enveloppe_offset = cassette_case_grip_enveloppe_offset,

    embed_x_size = cassette_case_embed_x_size,
    embed_y_size = cassette_case_embed_y_size,
    embed_z_size = cassette_case_embed_z_size,
    embed_offsets = cassette_case_embed_offsets,
    embed_round_radius = cassette_case_embed_round_radius,

    cny70set_x_point_coord = cassette_case_cny70set_x_point_coord,
    cny70set_y_point_coord = cassette_case_cny70set_y_point_coord,
    cny70set_x_y_margin = cassette_case_cny70set_x_y_margin,

    $fn = 100
) {




    difference() {

        
        roundedPane(
            [
                cassette_case_x_size,
                cassette_case_y_size,
                cassette_case_z_size
            ],
            cassette_case_round_radius,
            cassette_case_round_radius,
            $fn=100
        );

        translate(
            [
                (cassette_case_x_size - (cassette_x_size + (cassette_case_x_y_margin * 2))) / 2,
                (cassette_case_y_size - (cassette_y_size + (cassette_case_x_y_margin * 2))) / 2,
                cassette_case_z_size - cassette_z_size
            ]
        )
            roundedPane(
                [
                    cassette_x_size + (cassette_case_x_y_margin * 2),
                    cassette_y_size + (cassette_case_x_y_margin * 2),
                    cassette_z_size + 1
                ],
                cassette_round_radius,
                cassette_round_radius,
                $fn=100
            );


        // grip enveloppe
        translate(
            [
                cassette_case_x_size / 2,
                cassette_case_y_size / 2 + cassette_y_size / 2 
                    + cassette_case_x_y_margin - (grip_enveloppe_diameter / 2) + grip_enveloppe_offset,
                cassette_case_z_size - cassette_z_size
            ]
        )
            cylinder(h = cassette_case_z_size, d = grip_enveloppe_diameter, $fn = $fn);


        // embed
        difference() {
            translate(
                [
                    -embed_offsets,
                    -embed_offsets,
                    cassette_case_z_size - embed_z_size
                ]
            )
                cube(
                    [
                        cassette_case_x_size + embed_offsets * 2,
                        cassette_case_y_size + embed_offsets * 2,
                        cassette_case_z_size
                    ],
                    center = false
                );


            translate(
                [
                    (cassette_case_x_size - embed_x_size) / 2,
                    (cassette_case_y_size - embed_y_size) / 2,
                    cassette_case_z_size - embed_z_size
                ]
            )
                roundedPane(
                    [
                        embed_x_size,
                        embed_y_size,
                        cassette_z_size + 1
                    ],
                    embed_round_radius,
                    embed_round_radius,
                    $fn=100
                );
        }


        // Throws CNY70
        translate(
            [
                getSizeFromPointCount(cny70set_x_point_coord - 1) - 2.23 - cny70set_x_y_margin,
                getSizeFromPointCount(cny70set_y_point_coord - 1) - 2.23 - cny70set_x_y_margin,
                -1
            ]
        )
            cube([
                getSizeFromPointCount(9) + (2.23 * 2) + (cny70set_x_y_margin * 2),
                getSizeFromPointCount(0) + (2.23 * 2) + (cny70set_x_y_margin * 2),
                20
            ]);



        // Throws
        translate([0, 0, -cassette_case_z_size / 2])
            forEachCoord([
                [throws_margin, throws_margin],
                [cassette_case_x_size - throws_margin, throws_margin],
                [throws_margin, cassette_case_y_size - throws_margin],
                [cassette_case_x_size - throws_margin, cassette_case_y_size - throws_margin,],
            ])
                cylinder(h = cassette_case_z_size * 2, d = throws_diameter, $fn = $fn);
    }
}




module cassetteCaseThrowsEnveloppe(
    cassette_case_x_size = cassette_case_x_size,
    cassette_case_y_size = cassette_case_y_size,
    cassette_case_z_size = cassette_case_z_size,
    throws_margin = cassette_case_throws_margin,
    throws_diameter = cassette_case_throws_diameter,

    embed_x_size = cassette_case_embed_x_size,
    embed_y_size = cassette_case_embed_y_size,
    embed_z_size = cassette_case_embed_z_size,

    cassette_z_size = cassette_z_size,
    embed_round_radius = cassette_case_embed_round_radius,

    embed_throw_margin = cassette_case_embed_throw_margin,

    $fn = 100
) {


    // Throws
    translate([0, 0, -cassette_case_z_size / 2])
        forEachCoord([
            [throws_margin, throws_margin],
            [cassette_case_x_size - throws_margin, throws_margin],
            [throws_margin, cassette_case_y_size - throws_margin],
            [cassette_case_x_size - throws_margin, cassette_case_y_size - throws_margin,],
        ])
            cylinder(h = cassette_case_z_size * 2, d = throws_diameter, $fn = $fn);



    translate(
        [
            (cassette_case_x_size - embed_x_size) / 2 - cassette_case_embed_throw_margin,
            (cassette_case_y_size - embed_y_size) / 2 - cassette_case_embed_throw_margin,
            -cassette_case_z_size / 2
        ]
    )
        roundedPane(
            [
                embed_x_size + cassette_case_embed_throw_margin * 2,
                embed_y_size + cassette_case_embed_throw_margin * 2,
                cassette_case_z_size * 2
            ],
            embed_round_radius + cassette_case_embed_throw_margin,
            embed_round_radius + cassette_case_embed_throw_margin,
            $fn=100
        );
}






cassetteCasePiece();


#cassetteCaseThrowsEnveloppe();