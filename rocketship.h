/*---------------------------------------------------------------------------
NAME: Erin Torbiak
ONECARD ID: 1205196
UNIX ID: torbiak
INSTRUCTOR: Davood Refiei
LECTURE SECTION: A2
TA: Aleksander Micic
LAB SECTION: D02
---------------------------------------------------------------------------*/
struct point{
  float x,y;
};

//Rocketship points are relative to the midpoint of the ship.
struct rocketship{
  int point_count;
  float x_velocity;
  float y_velocity;
  int thrust;
  int angle;
  float x_midpoint;
  float y_midpoint;
  struct point points[4];
};

extern struct rocketship ship;

void init_rocketship(int gravity, int thrust, int x_midpoint, int y_midpoint);

void draw_rocketship(
    FILE *sketchpad_stream, 
    int thrust, 
    int right, 
    int left);

int get_velocity();
