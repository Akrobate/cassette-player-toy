use <../../libraries/commons.scad>


module cny70() {

    width = 7;
    step = 2.54;
    margin = (width - step) / 2;    // 2.23

    translate([-margin, -margin, 0]) {
        color("grey")
            cube([width, width, 6]);

        translate([0, 0, -6])
            forEachCoord([
                [margin, margin],
                [margin, width - margin],
                [7 - margin, margin],
                [width - margin, width - margin]
            ])
                cylinder(d=0.4, h=6, $fn=32);
    }
}


cny70();
