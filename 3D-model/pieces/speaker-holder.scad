include <./../configurations/global.scad>
use <./../libraries/commons.scad>
use <./../libraries/electronics.scad>

use <./subpieces/rounded-pane.scad>
use <../enveloppes/speaker-40mm-throws-enveloppe.scad>

/**
 * speakerFacadePiece
 * @name speakerFacadePiece
 * @description Speaker protection
 * @type piece
 * @parent root
 * @stl
 */
module speakerHolder(
    x_size = speaker_facade_x_size,
    y_size = speaker_facade_y_size,
    z_size = 5,
    throws_margin = speaker_facade_fixation_throws_margin,
    rounded_radius = speaker_facade_rounded_radius,
    throws_diameter = speaker_facade_fixation_throws_diameter,
    $fn = 100
) {

    difference() {

        //translate([0, 0, z_size / 2])
        //roundedPane([x_size, y_size, z_size], r1 = rounded_radius, r2 = rounded_radius);

        hull(){

            translate([rounded_radius, rounded_radius])
                cylinder(h = z_size, r = rounded_radius, $fn = $fn);

            
            translate([x_size / 2, y_size / 2])
                cylinder(h = z_size, d = 31, $fn = $fn);
            
            translate([-rounded_radius, -rounded_radius])
                translate([x_size, y_size])
                    cylinder(h = z_size, r = rounded_radius, $fn = $fn);

        }
        

        translate([x_size / 2, y_size / 2])
            cylinder(h = z_size * 4, d = 19, center=true, $fn = $fn);
            
        speakerFacadePieceFixationThrows();
    }
}


module speakerFacadePieceFixationThrows(
    x_size = speaker_facade_x_size,
    y_size = speaker_facade_y_size,
    z_size = 5,
    throws_margin = speaker_facade_fixation_throws_margin,
    throws_diameter = speaker_facade_fixation_throws_diameter,
    $fn = 100
) {
    translate([0, 0, -z_size / 2])
        forEachCoord([
            [throws_margin, throws_margin],
            [x_size - throws_margin, throws_margin],
            [throws_margin, y_size - throws_margin],
            [x_size - throws_margin, y_size - throws_margin,],
        ])
            cylinder(h = z_size * 2, d = throws_diameter, $fn = $fn);
}



speakerFacadePiece();