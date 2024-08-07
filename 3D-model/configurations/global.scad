// gold_number = 1.618;

housing_facades_throws_diameter = 3.8;

// external size
case_external_x_size = 165;
case_external_y_size = 92;
case_external_z_size = 38;
case_external_panes_thickness = 4.8;

facade_front_round_edges_radius = 5;
facade_throws_margin = 5;

// facade corners
facade_corners_offset_lenght = 9;
facade_corners_main_x_size = 19;
facade_corners_main_y_size = 19;
facade_corners_main_thickness = 11;
facade_corners_correction_offset_length = 0.2;
facade_corners_correction_offset_thickness = 0.0;
facade_fn = 100;


// Generics
insert_throw_diameter = 4.2;
insert_throw_length = 6 + 2;


// mother board
mother_board_cny70set_x_point_coord = 10;
mother_board_cny70set_y_point_coord = 7;



// Cassette
cassette_x_size = 50;
cassette_y_size = 31;
cassette_z_size = 4.8;
cassette_round_radius = 4;

// Cassette case
cassette_case_x_size = 76.2;
cassette_case_y_size = 55.88;
cassette_case_z_size = 9;
cassette_case_round_radius = 1;

cassette_case_x_y_margin = 0.75;

cassette_case_embed_x_size = 62;
cassette_case_embed_y_size = 42;
cassette_case_embed_z_size = 4.8;
cassette_case_embed_offsets = 10;
cassette_case_embed_round_radius = 6;

cassette_case_throws_margin = 2.54 * 2;
cassette_case_throws_diameter = 3.5;
cassette_case_grip_enveloppe_diameter = 15;
cassette_case_grip_enveloppe_offset = 3;

cassette_case_cny70set_x_point_coord = mother_board_cny70set_x_point_coord;
cassette_case_cny70set_y_point_coord = mother_board_cny70set_y_point_coord;
cassette_case_cny70set_x_y_margin = 0.5;

// Front panel throw cassette case mounting 
cassette_case_embed_throw_margin = 0.5;


// Mother board joins
bolt_join_mother_board_internal_diameter = 3.5;
bolt_join_mother_board_external_diameter = 3.5 + (0.4 * 12);
bolt_join_mother_board_height = 8.5;
bolt_join_fn = 200;


// speaker facade
speaker_facade_x_size = 50;
speaker_facade_y_size = cassette_case_y_size - cassette_case_throws_margin * 2 + 7;
speaker_facade_z_size = 2;
speaker_facade_rounded_radius = 3;
speaker_facade_fixation_throws_margin = 3.5;
speaker_facade_fixation_throws_diameter = 3.5;
speaker_facade_throw_diameter = 40+1;
// 
facade_top_on_off_button_throw_diameter = 12.8;


facade_cassette_case_coords = [
    60 + 5,
    23,
];

facade_speaker_40mm_coords = [
    32 + 5,
    facade_cassette_case_coords[1] + (cassette_case_y_size / 2),
];

batteries_holder_coords = [
    8 + 5,
    20
];

volume_buttons_spacing = 20;
//volume_buttons_coords = [145,50];
volume_buttons_coords = [
    145 + 5 ,
    facade_cassette_case_coords[1] + (cassette_case_y_size / 2),
];

controller_buttons_spacing = 20;
//controller_buttons_coords = [98,14];
controller_buttons_coords = [
    facade_cassette_case_coords[0] + (cassette_case_x_size / 2),
    14
];

controller_onoff_coords = [
    32 + 5,
    14
];


