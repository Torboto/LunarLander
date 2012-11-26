/*---------------------------------------------------------------------------
NAME: Erin Torbiak
ONECARD ID: 1205196
UNIX ID: torbiak
INSTRUCTOR: Davood Refiei
LECTURE SECTION: A2
TA: Aleksander Micic
LAB SECTION: D02
---------------------------------------------------------------------------*/

void init_rocketship(int gravity, int thrust, int x_midpoint, int y_midpoint);

void draw_rocketship(
    FILE *sketchpad_stream, 
    int thrust, 
    int right, 
    int left);

int get_velocity();
