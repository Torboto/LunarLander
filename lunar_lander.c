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
#include <time.h>
#include <unistd.h> //getopt
#include <sys/time.h>

#include "error.h"
#include "landscape.h"
#include "rocketship.h"

/* in microseconds */
#define FRAME_DURATION 50000


const char sketchpad_exec[] = "java -jar Sketchpad.jar ";
FILE *sketchpad_stream;
int gravity, thrust;
WINDOW *win;

void run_flight(){
  int alive = 1;
  while (alive){
    int keypress;
    int thrust = 0;
    int right = 0;
    int left = 0;
    struct timeval start_time, cur_time;
    long dt;
    
    gettimeofday(&start_time, NULL);

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
    gettimeofday(&cur_time, NULL);
    dt = cur_time.tv_usec - start_time.tv_usec;
    //printw("%8lld", FRAME_DURATION - dt);
    if (dt > 0){
      usleep(FRAME_DURATION - dt);
      //DEBUG
      //usleep(5000000);
    }
  }
}


int main(int argc, char* argv[]){
  int opt = 0;

  if (argc != 7){
    die("-g: takes integer for gravity \n"
	"-t: takes integer for rocketship thrust\n"
	"-f: filename of landscape file\n");
  }

  sketchpad_stream = popen(sketchpad_exec, "w");

  while ((opt = getopt(argc, argv, "g:t:f:")) != -1){
    switch(opt){
      case 'g':
	gravity = atoi(optarg);
	break;
      case 't':
	thrust = atoi(optarg);
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
