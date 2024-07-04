
use <../assets/cny70/cny70.scad>
use <../libraries/electronics.scad>
use <../libraries/breadboard.scad>

include <../configurations/global.scad>


module motherBoardComponent(
    cny70set_x_point_coord = mother_board_cny70set_x_point_coord,
    cny70set_y_point_coord = mother_board_cny70set_y_point_coord,
) {

    breadboard(29, 21, draw_throws = true, $fn=4);

    translateBreadboard(
        cny70set_x_point_coord,
        cny70set_y_point_coord,
        6.25 + 1.5
        
    )
        cny70set();

    translateBreadboard(1, 12, 1.50)
        genericModule(
            x_points = 14,
            y_points = 4,
            z_size = 8,
            color = "Grey"
        );

    translateBreadboard(21, 7, -10.0)
        genericModule(
            x_points = 8,
            y_points = 8,
            z_size = 10,
            color = "Blue"
        );
}


module cny70set() {
    translateBreadboard(0, 0, 0)
        cny70();

    translateBreadboard(3, 0, 0)
        cny70();

    translateBreadboard(6, 0, 0)
        cny70();

    translateBreadboard(9, 0, 0)
        cny70();
}


motherBoardComponent();

