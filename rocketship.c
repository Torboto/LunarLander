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

#define FRAME_DURATION 0.05
#define PI acos(-1.0)
//#define FRAME_DURATION 1

int Gravity;
int Angle;
struct point{
  float x,y;
};

//Rocketship points are relational to the midpoint of the ship.
struct rocketship{
  int point_count;
  float x_velocity;
  float y_velocity;
  int thrust;
  float x_midpoint;
  float y_midpoint;
  struct point points[4];
} ship;

void init_rocketship(int gravity, int thrust, int x_midpoint, int y_midpoint){
  Gravity = gravity;
  Angle = 90;
  ship.thrust = thrust;
  ship.x_velocity = 0;
  ship.y_velocity = 0;
  ship.x_midpoint = x_midpoint;
  ship.y_midpoint = y_midpoint;
  ship.point_count = 4;

  struct point point;
  point.x = 0;
  point.y = -10;
  ship.points[0] = point;
  point.x = -10;
  point.y = 10;
  ship.points[1] = point;
  point.x = 10;
  point.y = 10;
  ship.points[2] = point;
  point.x = 0;
  point.y = -10;
  ship.points[3] = point;
}

void velocity(int thrust){
  float x_acc;
  float y_acc;
  float angle_radian = (Angle * PI) / 180;
  fprintf(stderr, "%d ", Angle);

  if (thrust){
    x_acc = ship.thrust * cos(angle_radian);
    y_acc = -ship.thrust + Gravity * sin(angle_radian);

  } else {
    x_acc = 0;
    y_acc = Gravity;
  }

  ship.x_midpoint = ship.x_midpoint + 
    ship.x_velocity * FRAME_DURATION +
    1/2 * x_acc * FRAME_DURATION * FRAME_DURATION;

  ship.y_midpoint = ship.y_midpoint + 
    ship.y_velocity * FRAME_DURATION +
    1/2 * y_acc * FRAME_DURATION * FRAME_DURATION;

  ship.x_velocity = ship.x_velocity + (x_acc * FRAME_DURATION);
  ship.y_velocity = ship.y_velocity + (y_acc * FRAME_DURATION);
}

void rotate(int right, int left){
  double rotate_radian;
  if (right){
    rotate_radian = (10 * PI) / 180;
    Angle -= 10;
  } else if (left){
    rotate_radian = (-10 * PI) / 180;
    Angle += 10;
  }
  for(int i = 0; i < ship.point_count; i++){
    float x = ship.points[i].x;
    float y = ship.points[i].y;

    float rotated_x = x * cos(rotate_radian) - y * sin(rotate_radian);
    float rotated_y = x * sin(rotate_radian) + y * cos(rotate_radian);
    ship.points[i].x = (rotated_x);
    ship.points[i].y = (rotated_y);
  }

}



int get_velocity(){
  return ship.y_velocity;
}

void draw_rocketship(
    FILE *sketchpad_stream, 
    int thrust, 
    int right, 
    int left){

  for(int i = 0; i < ship.point_count - 1; i++){
    fprintf(sketchpad_stream, "eraseSegment");
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.x_midpoint + ship.points[i].x));
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.y_midpoint + ship.points[i].y));
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.x_midpoint + ship.points[i+1].x));
    fprintf(sketchpad_stream, " %ld\n", 
	lround(ship.y_midpoint + ship.points[i+1].y));
  }

  velocity(thrust);

  if (right == 1 || left == 1){
    rotate(right, left);
  }

  for(int i = 0; i < ship.point_count - 1; i++){
    fprintf(sketchpad_stream, "drawSegment");
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.x_midpoint + ship.points[i].x));
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.y_midpoint + ship.points[i].y));
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.x_midpoint + ship.points[i+1].x));
    fprintf(sketchpad_stream, " %ld\n", 
	lround(ship.y_midpoint + ship.points[i+1].y));
  }
  fflush(sketchpad_stream);
  right= 0;
  left= 0;
  thrust = 0;
}
