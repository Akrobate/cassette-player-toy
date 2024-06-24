use <./subpieces/rounded-pane.scad>

use <./../libraries/commons.scad>
use <./../libraries/electronics.scad>
use <./cassette-case-piece.scad>


include <./../configurations/global.scad>




/**
 * facadeFrontPiece
 * @name facadeFrontPiece
 * @description Piece can be printed or CNC cutted #3DPrint, #CNC
 * @type piece
 * @parent housingComponent
 * @stl
 */
module facadeFrontPiece(
    x_size = case_external_x_size,
    y_size = case_external_y_size,
    z_size = case_external_panes_thickness,
    throws_margin = facade_throws_margin,
    round_edges_radius = facade_front_round_edges_radius,
    throws_diameter = housing_facades_throws_diameter,

    facade_cassette_case_coords = facade_cassette_case_coords,
    facade_speaker_40mm_coords = facade_speaker_40mm_coords,
    $fn = facade_fn
) {
    echo(str("facadeFrontPiece ", "x_size: ", x_size, " y_size: ", y_size, " z_size: ", z_size));

    difference() {
        color("BurlyWood")
            roundedPane(
                [x_size, y_size, z_size],
                r1 = round_edges_radius,
                r2 = round_edges_radius,
                center = false,
                $fn = $fn
            );

        translate([0, 0, -z_size / 2])
            forEachCoord([
                [throws_margin, throws_margin],
                [x_size - throws_margin, throws_margin],
                [throws_margin, y_size - throws_margin],
                [x_size - throws_margin, y_size - throws_margin,],
            ])
                cylinder(h = z_size * 2, d = throws_diameter, $fn = $fn);


        translate(
            [
                facade_cassette_case_coords[0],
                facade_cassette_case_coords[1]
            ]
        )
            cassetteCaseThrowsEnveloppe();

        translate(
            [
                facade_speaker_40mm_coords[0],
                facade_speaker_40mm_coords[1],
                -z_size / 2
            ]
        )
            cylinder(h = z_size * 2, d = 40, $fn = $fn);

    




    }
}

facadeFrontPiece();


