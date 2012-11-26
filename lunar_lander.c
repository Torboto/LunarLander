/*---------------------------------------------------------------------------
NAME: Erin Torbiak
ONECARD ID: 1205196
UNIX ID: torbiak
INSTRUCTOR: Davood Refiei
LECTURE SECTION: A2
TA: Aleksander Micic
LAB SECTION: D02
---------------------------------------------------------------------------*/
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <unistd.h> //getopt
#include <sys/time.h>

#include "error.h"
#include "rocketship.h"
#include "landscape.h"

/* in microseconds */
#define FRAME_DURATION 50000

extern FILE *popen(const char *command, const char *type); 
extern int pclose(FILE *stream); 
extern int usleep(useconds_t usec);
extern int getopt(int argc, char * const argv[], const char *optstring);

const char sketchpad_exec[] = "java -jar Sketchpad.jar ";
FILE *sketchpad_stream;
int gravity, thrust;
int Alive, Win;

int ccw(struct point A, struct point B, struct point C){
  return (C.y-A.y)*(B.x-A.x) > (B.y-A.y)*(C.x-A.x);
}

int intersect(struct point A, struct point B, struct point C, struct point D){
  if (ccw(A,C,D) == ccw (B,C,D)){
    return 0;
  }
  else if (ccw(A,B,C) == ccw(A,B,D)){
    return 0;
  }
  else {
    return 1;
  }
}

void collision_check(){
  int contact = 0;
  for (int i = 0; i < landscape.point_count - 1; i++){
    for(int j = 0; j < ship.point_count - 1; j++){
      struct point ship_begin = ship.points[j];
      ship_begin.x = ship_begin.x + ship.x_midpoint;
      ship_begin.y = ship_begin.y + ship.y_midpoint;
      struct point ship_end= ship.points[j+1];
      ship_end.x = ship_end.x + ship.x_midpoint;
      ship_end.y = ship_end.y + ship.y_midpoint;

      struct point land_begin = landscape.points[i];
      struct point land_end = landscape.points[i+1];

      contact = intersect(ship_begin, ship_end, land_begin, land_end);

      if (contact == 1){
	/*mvprintw(12, 4,"MID:%f\nShip_begin: %f\nShip_End: %f\nLand_Y: %f\n", 
	    ship.y_midpoint, ship.points[1].y + ship.y_midpoint,
	    ship.points[1].y + ship.y_midpoint,land_end.y);
	    */
	//mvprintw(12, 4,"X_VEL: %f\nY_VEL: %f\n", 
	//ship.x_velocity, ship.y_velocity);
	Alive = 0;
	//check if land
	if (lround(ship.points[1].y + ship.y_midpoint) == land_begin.y && 
	    lround(ship.points[2].y + ship.y_midpoint) == land_begin.y){
	  if (ship.x_velocity < 10 && ship.y_velocity < 10){
	    Win = 1;
	  }
	} else {
	  Win = 0;
	}
	return;
      } 
    }
  }
}

void run_flight(){
  Alive = 1;
  while (Alive){
    int keypress;
    int thrust = 0;
    int right = 0;
    int left = 0;
    struct timeval start_time, cur_time;
    long dt;

    gettimeofday(&start_time, NULL);
    //printw("%d\n", keypress);
    nodelay(stdscr, TRUE);
    keypress = getch();

    switch (keypress){
      case KEY_RIGHT:
	right = 1;
	break;
      case KEY_LEFT: 
	left = 1;
	break;
      case ' ':
	thrust = 1;
	break;
      case 'q':
	fprintf(sketchpad_stream, "end");
	fflush(sketchpad_stream);
	pclose(sketchpad_stream);
	clrtoeol();
	refresh();
	endwin();
	exit(1);
	break;
      default:
	break;
    }

    draw_rocketship(sketchpad_stream, thrust, right, left);
    collision_check();
    gettimeofday(&cur_time, NULL);
    dt = cur_time.tv_usec - start_time.tv_usec;
    //printw("%8lld", FRAME_DURATION - dt);
    if (dt > 0){
      usleep(FRAME_DURATION - dt);
      //DEBUG
      //usleep(5000000);
    }
  }

  if (Win == 1){
    mvprintw(10, 4, "%s", "LANDED!");
  } else {
    mvprintw(10, 4, "%s", "CRASH! ");
  }

  //Loop to wait for user to press q to exit.
  while(1){
    int keypress = getch();
    switch (keypress){
      case 'q':
	fprintf(sketchpad_stream, "end");
	fflush(sketchpad_stream);
	pclose(sketchpad_stream);
	clrtoeol();
	refresh();
	endwin();
	exit(1);
	break;
      default:
	break;
    }
  }
}


int main(int argc, char* argv[]){
  int opt = 0;

  if (argc != 7){
    die("-g: takes integer for gravity (Suggested value: 10) \n"
	"-t: takes integer for rocketship thrust (Suggested value: 200)\n"
	"-f: filename of landscape file\n");
  }

  sketchpad_stream = popen(sketchpad_exec, "w");

  while ((opt = getopt(argc, argv, "g:t:f:")) != -1){
    switch(opt){
      case 'g':
	gravity = atoi(optarg);
	if (atoi(optarg) < 0 || atoi(optarg) > 20){
	  die("gravity > 0, < 20 not allowed\n");
	}
	break;
      case 't':
	thrust = atoi(optarg);
	if (atoi(optarg) > 0 || atoi(optarg) < -20){
	  //die("thrust > 0, < -20 not allowed\n");
	}
	break;
      case 'f':
	draw_landscape(sketchpad_stream, optarg);
	break;
      case '?':
	die("-g: takes integer for gravity \n"
	    "-t: takes integer for rocketship thrust\n"
	    "-f: filename of landscape file\n");
	break;
    }
  }
  int max_x = get_max_x();
  init_rocketship(gravity, thrust, max_x/2, 20);
  draw_rocketship(sketchpad_stream, 0, 0, 0);
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  char *directions = "Press any key to begin!\n"
    "    SPACEBAR to accelerate\n"
    "    LEFT/RIGHT arrows to rotate ship\n"
    "    q to quit\n";
  mvprintw(4, 4, "%s", directions);
  if (getch() != ERR){
    run_flight();
  }
}
