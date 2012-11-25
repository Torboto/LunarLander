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

#define FRAME_LENGTH 0.05
int gravity;
int thrust;
int right_rotation;
int left_rotation;
struct point{
  int x,y;
};

//Rocketship points are relational to the midpoint of the ship.
struct rocketship{
  int point_count;
  int velocity;
  int x_midpoint;
  int y_midpoint;
  struct point points[4];
} rocketship;

void velocity(){
  rocketship.y_midpoint = rocketship.y_midpoint + 
    rocketship.velocity * 
    (FRAME_LENGTH + 1/2) * 
    gravity *
    FRAME_LENGTH * FRAME_LENGTH;
  rocketship.velocity = rocketship.velocity + (gravity * FRAME_LENGTH);
}

int rotate_right(){
  //10 degrees
  return 0;
}

int rotate_left(){
  //355 degrees
  return 0;
}

void init_rocketship(int gravity, int x_midpoint, int y_midpoint){
  gravity = gravity;
  right_rotation = 0;
  left_rotation = 0;
  thrust = 0;
  rocketship.velocity = 0;
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

  if (right_rotation){
    //rotate_right();
  }
  else if (left_rotation){
    //rotate_left();
  }

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

  velocity();

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
