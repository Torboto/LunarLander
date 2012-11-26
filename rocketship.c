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
#include <math.h>

#include <ncurses.h>

#include "error.h"

#define FRAME_LENGTH 0.05
#define PI acos(-1.0)
//#define FRAME_LENGTH 1

int gravity;
int thrusting;
struct point{
  int x,y;
};

//Rocketship points are relational to the midpoint of the ship.
struct rocketship{
  int point_count;
  float velocity;
  int thrust;
  int x_midpoint;
  int y_midpoint;
  struct point points[4];
} rocketship;

void velocity(){
  rocketship.y_midpoint = rocketship.y_midpoint + 
    rocketship.velocity * FRAME_LENGTH +
    1/2 * gravity * FRAME_LENGTH * FRAME_LENGTH;
  rocketship.velocity = rocketship.velocity + (gravity * FRAME_LENGTH);
  //fprintf(stderr, "VEL: %f", rocketship.velocity + (gravity * FRAME_LENGTH));
  //fprintf(stderr, "YAXIS: %d", rocketship.y_midpoint);
}

void rotate(int right, int left){
  double rotate_radian;
  if (right){
    rotate_radian = (10 * PI) / 180;
  } else if (left){
    rotate_radian = (-10 * PI) / 180;
  }
  for(int i = 0; i < rocketship.point_count; i++){
    int x = rocketship.points[i].x;
    int y = rocketship.points[i].y;

    int rotated_x = x * cos(rotate_radian) - y * sin(rotate_radian);
    int rotated_y = x * sin(rotate_radian) + y * cos(rotate_radian);
    rocketship.points[i].x = rotated_x;
    rocketship.points[i].y = rotated_y;
    fprintf(stderr, "X%dY%d ", rotated_x, rotated_y);
  }

}


void init_rocketship(int gravity, int thrust, int x_midpoint, int y_midpoint){
  gravity = gravity;
  rocketship.thrust = thrust;
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

int get_velocity(){
  return rocketship.velocity;
}

void draw_rocketship(
    FILE *sketchpad_stream, 
    int thrust, 
    int right, 
    int left){

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

  if (thrust){
    //calc velocity
  }
  if (right == 1 || left == 1){
    rotate(right, left);
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
  right= 0;
  left= 0;
  thrust = 0;
}
