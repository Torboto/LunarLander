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

FILE *landscape_stream;

struct point{
  long x,y;
};
struct landscape{
  struct point points[20];
};

void build_landscape(FILE *sketchpad_pipe, char *input_file){
  landscape_stream = fopen(input_file, "r"); 
   if (landscape_stream == NULL){
    die("File Invalid.\n");
  }
}

void print_landscape(){
}

int get_rocketship_spawnpoint(){
}
