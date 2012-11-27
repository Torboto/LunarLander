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
#include "rocketship.h"

#define FRAME_DURATION 0.05
#define PI acos(-1.0)
//#define FRAME_DURATION 1

int Gravity;

struct rocketship ship;
struct fire{
  int point_count;
  struct point points[9];
} fire;

void init_fire(){
  fire.point_count = 9;
  struct point point;
  /*
  point.x = 0;
  point.y = 15;
  fire.points[0] = point;
  point.x = 0;
  point.y = 20;
  fire.points[1] = point;
 */ 
     point.x = -5;
  point.y = 15;
  fire.points[0] = point;
  point.x = -8;
  point.y = 20;
  fire.points[1] = point;
  point.x = -4;
  point.y = 17;
  fire.points[2] = point;
  point.x = -2;
  point.y = 20;
  fire.points[3] = point;
  point.x = 0;
  point.y = 17;
  fire.points[4] = point;
  point.x = 2;
  point.y = 20;
  fire.points[5] = point;
  point.x = 4;
  point.y = 17;
  fire.points[6] = point;
  point.x = 8;
  point.y = 20;
  fire.points[7] = point;
  point.x = 5;
  point.y = 15;
  fire.points[8] = point;
}

void init_rocketship(int gravity, int thrust, int x_midpoint, int y_midpoint){
  init_fire();
  Gravity = gravity;
  ship.angle = 90;
  ship.thrust = -thrust;
  ship.x_velocity = 0;
  ship.y_velocity = 0;
  ship.x_midpoint = x_midpoint;
  ship.y_midpoint = y_midpoint;
  ship.point_count = 11;
  //TOP TRIANGLE 
   struct point point;
  point.x = 5;
  point.y = -5;
  ship.points[0] = point;
  point.x = 0;
  point.y = -15;
  ship.points[1] = point;
  point.x = -5;
  point.y = -5;
  ship.points[2] = point;
  point.x = 5;
  point.y = -5;
  ship.points[3] = point;
//BODY of ship
  point.x = 5;
  point.y = 10;
  ship.points[4] = point;

  point.x = 2;
  point.y = 10;
  ship.points[5] = point;
  point.x = 5;
  point.y = 15;
  ship.points[6] = point;
  point.x = -5;
  point.y = 15;
  ship.points[7] = point;
  point.x = -2;
  point.y = 10;
  ship.points[8] = point;
  point.x = -5;
  point.y = 10;
  ship.points[9] = point;
  point.x = -5;
  point.y = -5;
  ship.points[10] = point;
}

void velocity(int thrust){
  float x_acc;
  float y_acc;
  float angle_radian = (ship.angle * PI) / 180;
  //fprintf(stderr, "%d ", ship.angle);

  if (thrust){
    x_acc = ship.thrust * cos(angle_radian);
    y_acc = Gravity + -ship.thrust * sin(angle_radian);

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
    ship.angle -= 10;
    if (ship.angle == -10){
      ship.angle = 355;
    }
  } else if (left){
    rotate_radian = (-10 * PI) / 180;
    ship.angle += 10;
    if (ship.angle == 365){
      ship.angle = 0;
    }
  }
  for(int i = 0; i < ship.point_count; i++){
    float x = ship.points[i].x;
    float y = ship.points[i].y;

    float rotated_x = x * cos(rotate_radian) - y * sin(rotate_radian);
    float rotated_y = x * sin(rotate_radian) + y * cos(rotate_radian);
    ship.points[i].x = (rotated_x);
    ship.points[i].y = (rotated_y);
  }
  for(int i = 0; i < fire.point_count; i++){
    float x = fire.points[i].x;
    float y = fire.points[i].y;

    float rotated_x = x * cos(rotate_radian) - y * sin(rotate_radian);
    float rotated_y = x * sin(rotate_radian) + y * cos(rotate_radian);
    fire.points[i].x = (rotated_x);
    fire.points[i].y = (rotated_y);
  }

}

int get_velocity(){
  return ship.y_velocity;
}

void draw_fire(FILE *sketchpad_stream){
  for(int i = 0; i < fire.point_count - 1; i++){
    fprintf(sketchpad_stream, "drawSegment");
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.x_midpoint + fire.points[i].x));
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.y_midpoint + fire.points[i].y));
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.x_midpoint + fire.points[i+1].x));
    fprintf(sketchpad_stream, " %ld\n", 
	lround(ship.y_midpoint + fire.points[i+1].y));
  }
}
void erase_fire(FILE *sketchpad_stream){
  for(int i = 0; i < fire.point_count - 1; i++){
    fprintf(sketchpad_stream, "eraseSegment");
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.x_midpoint + fire.points[i].x));
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.y_midpoint + fire.points[i].y));
    fprintf(sketchpad_stream, " %ld", 
	lround(ship.x_midpoint + fire.points[i+1].x));
    fprintf(sketchpad_stream, " %ld\n", 
	lround(ship.y_midpoint + fire.points[i+1].y));
  }
}

void draw_rocketship(FILE *sketchpad_stream, int thrust, int right, int left){

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
  erase_fire(sketchpad_stream);

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
  if (thrust == 1){
    draw_fire(sketchpad_stream);
  }

  fflush(sketchpad_stream);
}
