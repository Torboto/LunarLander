/*---------------------------------------------------------------------------
NAME: Erin Torbiak
ONECARD ID: 1205196
UNIX ID: torbiak
INSTRUCTOR: Davood Refiei
LECTURE SECTION: A2
TA: Aleksander Micic
LAB SECTION: D02
---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "error.h"

struct point{
  int x,y;
};

//Rocketship points are relational to the midpoint of the ship.
struct rocketship{
  int point_count;
  struct point points[4];
};

struct rocketship rocketship;

void build_rocketship(){
  rocketship.point_count = 4;
  struct point point;
  point.x = 0;
  point.y = -10;
  rocketship.points[0] = point;
  point.x = -10;
  point.y = 10;
  rocketship.points[1] = point;
  point.x = 10;
  point.y = 10;
  rocketship.points[2] = point;
  point.x = 0;
  point.y = -10;
  rocketship.points[3] = point;
}

void draw_rocketship(FILE *sketchpad_stream, int x_midpoint, int y_midpoint){
  build_rocketship();
  for(int i = 0; i < rocketship.point_count - 1; i++){
    fprintf(sketchpad_stream, "drawSegment");
    fprintf(sketchpad_stream, " %d", x_midpoint + rocketship.points[i].x);
    fprintf(sketchpad_stream, " %d", y_midpoint + rocketship.points[i].y);
    fprintf(sketchpad_stream, " %d", x_midpoint + rocketship.points[i+1].x);
    fprintf(sketchpad_stream, " %d\n", y_midpoint + rocketship.points[i+1].y);
  }
  fflush(sketchpad_stream);
  fprintf(sketchpad_stream, "pause 5\n");
}
