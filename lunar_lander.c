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
#include <time.h>
#include <unistd.h> //getopt

#include "error.h"
#include "landscape.h"
#include "rocketship.h"

#define FRAME_LENGTH .05

const char sketchpad_exec[] = "java -jar Sketchpad.jar ";

int main(int argc, char* argv[]){
  FILE *sketchpad_stream;
  int gravity, thrust;
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
  init_rocketship(gravity, max_x/2, 20);
  draw_rocketship(sketchpad_stream, 0, 0, 0);

  int alive = 1;
  while (alive){
    time_t start_time;
    time(&start_time);
  }

    sleep(60);
  }
