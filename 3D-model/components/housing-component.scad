use <./../pieces/facade-front-piece.scad>
use <./../pieces/facade-back-piece.scad>
use <./../pieces/facade-top-piece.scad>
use <./../pieces/facade-left-piece.scad>
use <./../pieces/facade-corner-piece.scad>

include <./../configurations/global.scad>

/**
 * housingComponent
 * @name housingComponent
 * @description The box casing of the device
 * @type component
 * @parent root
 */
module housingComponent() {
    translate([0, 0, case_external_z_size - case_external_panes_thickness])
        facadeFrontPiece();

    *translate([0, 0, 0])
        facadeBackPiece();

    translate([facade_corners_offset_lenght, case_external_panes_thickness - 0.01, case_external_panes_thickness])
        rotate([90,0,0])
            facadeTopPiece();

    translate([facade_corners_offset_lenght, case_external_y_size + 0.01, case_external_panes_thickness])
        rotate([90,0,0])
            facadeTopPiece();

    translate([0 - 0.01, facade_corners_offset_lenght, case_external_panes_thickness])
        rotate([90,0,90])
            facadeLeftPiece();

    translate([case_external_x_size - case_external_panes_thickness + 0.01, facade_corners_offset_lenght, case_external_panes_thickness])
        rotate([90,0,90])
            facadeLeftPiece();

    module corners() {
        // Corner (bottom left)
        translate([0, 0, case_external_panes_thickness])
            facadeCornerPiece();

        // Corner (bottom right)
        translate([case_external_x_size, 0, case_external_panes_thickness])
            rotate([0, 0, 90])
                facadeCornerPiece();

        // Corner (top left)
        translate([0, case_external_y_size, case_external_panes_thickness])
            rotate([0, 0, -90])
                facadeCornerPiece();

        // Corner (bottom right)
        translate([case_external_x_size, case_external_y_size, case_external_panes_thickness])
            rotate([0, 0, -180])
                facadeCornerPiece();
    }

    corners();
}


housingComponent();

