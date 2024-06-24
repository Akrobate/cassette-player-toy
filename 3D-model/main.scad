include <./configurations/global.scad>

use <./libraries/electronics.scad>

use <./pieces/cassette-piece.scad>
use <./pieces/cassette-case-piece.scad>

use <./components/mother-board-component.scad>

translate([0,0,10])
    cassetteCasePiece();

motherBoardComponent();

translate(
    [
        (cassette_case_x_size - cassette_x_size) / 2,
        (cassette_case_y_size - cassette_y_size) / 2,
        10 + 4
    ]
)
    cassettePiece();

