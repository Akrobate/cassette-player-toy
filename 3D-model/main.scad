
use <./assets/cny70.scad>

use <./libraries/electronics.scad>

use <./pieces/subpieces/breadboard.scad>
use <./pieces/cassette.scad>




breadboard(19, 20, draw_throws = false, $fn=20);



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


translateBreadboard(5, 5, 1.5)
    cny70set();


translate([0, 0, 1.51])
    difference() {
        #cube([
            getSizeFromPointCount(19),
            getSizeFromPointCount(10),
            7
        ]);


        translate([getSizeFromPointCount(4) - 2.23, getSizeFromPointCount(4) - 2.23, -1])
            cube([
                getSizeFromPointCount(9) + 2.23 * 2,
                getSizeFromPointCount(0) + 2.23 * 2,
                9
            ]);
    }

*translate([0, 0, 20])
    cassette();