/*---------------------------------------------------------------------------
NAME: Erin Torbiak
ONECARD ID: 1205196
UNIX ID: torbiak
INSTRUCTOR: Davood Refiei
LECTURE SECTION: A2
TA: Aleksander Micic
LAB SECTION: D02
---------------------------------------------------------------------------*/

struct landscape{
  int point_count;
  struct point points[20];
};

extern struct landscape landscape;

void draw_landscape(FILE *sketchpad_stream, char *input_file);

int get_max_x();
