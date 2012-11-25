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
  int point_count;
  struct point points[20];
} landscape;

void build_landscape(char *input_file){
  char line[256];
  landscape.point_count = 0;
  landscape_stream = fopen(input_file, "r"); 

  if (landscape_stream == NULL){
    die("Landscape File Invalid.\n");
  } 

  while (1){
    if(!fgets(line, 256, landscape_stream)){
      if (feof(landscape_stream)){
	return;
      }
    }

    struct point point;

    sscanf(line, "%lu %lu", &point.x, &point.y);
    landscape.points[landscape.point_count] = point;
    landscape.point_count++;
  }
}

void draw_landscape(FILE *sketchpad_stream, char *input_file){
  build_landscape(input_file);
  for(int i = 0; i < landscape.point_count - 1; i++){
    fprintf(sketchpad_stream, "drawSegment");
    fprintf(sketchpad_stream, " %lu", landscape.points[i].x);
    fprintf(sketchpad_stream, " %lu", landscape.points[i].y);
    fprintf(sketchpad_stream, " %lu", landscape.points[i+1].x);
    fprintf(sketchpad_stream, " %lu\n", landscape.points[i+1].y);
  }
  fflush(sketchpad_stream);
}

int get_max_x(){
  return landscape.points[landscape.point_count - 1].x;
}
