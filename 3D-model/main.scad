include <./configurations/global.scad>

use <./assets/on-off-button/on-off-button.scad>
use <./assets/batteries-holder/batteries-holder.scad>
use <./assets/speaker40mm/speaker40mm.scad>

use <./libraries/electronics.scad>
use <./libraries/breadboard.scad>

use <./pieces/cassette-cnc-piece.scad>
use <./pieces/cassette-3D-print-piece.scad>
use <./pieces/cassette-case-piece.scad>
use <./pieces/speaker-facade-piece.scad>
use <./pieces/speaker-holder.scad>

use <./pieces/bolt-join-mother-board-piece.scad>

use <./components/mother-board-component.scad>
use <./components/housing-component.scad>


housingComponent();


translate([facade_speaker_40mm_coords[0], facade_speaker_40mm_coords[1], case_external_z_size])
    translate([-speaker_facade_x_size / 2 , -speaker_facade_y_size / 2])
    speakerFacadePiece();

translate([facade_speaker_40mm_coords[0], facade_speaker_40mm_coords[1], 21])
    translate([-speaker_facade_x_size / 2 , -speaker_facade_y_size / 2])
    speakerHolder();

translate([facade_speaker_40mm_coords[0], facade_speaker_40mm_coords[1], case_external_z_size])
    speaker40mm();

*translate([batteries_holder_coords[0], batteries_holder_coords[1], case_external_panes_thickness])
    batteriesHolder();


// On off button
translate([controller_onoff_coords[0], controller_onoff_coords[1], case_external_z_size ])
    onOffButton();

// Controll button
translate(controller_buttons_coords) {
    translate([-volume_buttons_spacing, 0, case_external_z_size ])
        onOffButton();

    translate([0, 0, case_external_z_size ])
        onOffButton();

    translate([volume_buttons_spacing, 0, case_external_z_size])
        onOffButton();
}

// Volume
translate(volume_buttons_coords) {
    translate([0, -controller_buttons_spacing / 2, case_external_z_size ])
        onOffButton();

    translate([0, controller_buttons_spacing /2, case_external_z_size ])
        onOffButton();

}

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

    translate(
        [
            (cassette_case_x_size - cassette_x_size) / 2,
            (cassette_case_y_size - cassette_y_size) / 2,
            10 + 4
        ]
    ) {
        *cassetteCncPiece();
        cassette3DPrintPiece();
    }
}