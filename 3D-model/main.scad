include <./configurations/global.scad>

use <./libraries/electronics.scad>
use <./libraries/breadboard.scad>


use <./pieces/cassette-piece.scad>
use <./pieces/cassette-case-piece.scad>
use <./pieces/bolt-join-mother-board-piece.scad>




use <./components/mother-board-component.scad>
use <./components/housing-component.scad>


housingComponent();



translate(
    [
        facade_cassette_case_coords[0],
        facade_cassette_case_coords[1],
         + case_external_z_size - case_external_panes_thickness - 10  + 0.615 - case_external_panes_thickness
    ]
) {


    translate([0,0,10])
        cassetteCasePiece();

    motherBoardComponent();

    translateBreadboard(2, 2, 1.5)
        boltJoinMotherBoardPiece();

    translateBreadboard(28, 20, 1.5)
        boltJoinMotherBoardPiece();

    translateBreadboard(2, 20, 1.5)
        boltJoinMotherBoardPiece();

    translateBreadboard(28, 2, 1.5)
        boltJoinMotherBoardPiece();

    *translate(
        [
            (cassette_case_x_size - cassette_x_size) / 2,
            (cassette_case_y_size - cassette_y_size) / 2,
            10 + 4
        ]
    )
        cassettePiece();

}