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
  int gravity;
  int thrust;
  int right_rotation;
  int left_rotation;
  int x_midpoint;
  int y_midpoint;
  struct point points[4];
} rocketship;

int velocity(int gravity, int thrust){
  return 0;
}

int rotate_right(){
  return 0;
}

int rotate_left(){
  return 0;
}

void init_rocketship(int gravity, int x_midpoint, int y_midpoint){
  rocketship.gravity = gravity;
  rocketship.thrust = 0;
  rocketship.right_rotation = 0;
  rocketship.left_rotation = 0;
  rocketship.x_midpoint = x_midpoint;
  rocketship.y_midpoint = y_midpoint;
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

void draw_rocketship(
    FILE *sketchpad_stream, 
    int thrust, 
    int right_rotation, 
    int left_rotation){
  
  for(int i = 0; i < rocketship.point_count - 1; i++){
    fprintf(sketchpad_stream, "eraseSegment");
    fprintf(sketchpad_stream, " %d", 
	rocketship.x_midpoint + rocketship.points[i].x);
    fprintf(sketchpad_stream, " %d", 
	rocketship.y_midpoint + rocketship.points[i].y);
    fprintf(sketchpad_stream, " %d", 
	rocketship.x_midpoint + rocketship.points[i+1].x);
    fprintf(sketchpad_stream, " %d\n", 
	rocketship.y_midpoint + rocketship.points[i+1].y);
  }

  for(int i = 0; i < rocketship.point_count - 1; i++){
    fprintf(sketchpad_stream, "drawSegment");
    fprintf(sketchpad_stream, " %d", 
	rocketship.x_midpoint + rocketship.points[i].x);
    fprintf(sketchpad_stream, " %d", 
	rocketship.y_midpoint + rocketship.points[i].y);
    fprintf(sketchpad_stream, " %d", 
	rocketship.x_midpoint + rocketship.points[i+1].x);
    fprintf(sketchpad_stream, " %d\n", 
	rocketship.y_midpoint + rocketship.points[i+1].y);
  }
  fflush(sketchpad_stream);
}
