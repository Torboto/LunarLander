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
#include <unistd.h> //getopt

#include "error.h"
#include "landscape.h"
#include "rocketship.h"

const char sketchpad_exec[] = "java -jar Sketchpad.jar -d";

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
  //TODO Get spawn coordinates from landscape.
  int max_x = get_max_x();
  draw_rocketship(sketchpad_stream, max_x/2 , 20); 

  //sleep(60);
}
