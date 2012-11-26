#----------------------------------------------------------------------------
# NAME: Erin Torbiak
# ONECARD ID: 1205196
# UNIX ID: torbiak
# INSTRUCTOR: Davood Refiei
# LECTURE SECTION: A2
# TA: Aleksander Micic
# LAB SECTION: D02
#----------------------------------------------------------------------------
# DESCRIPTION 

# Checks sketchpad file syntax.
# Adds up occurances of the 8 keywords and prints out a summary of the file.
# Checks various limitations on name size, number of draw commands in a figure,
# line length, figure name length, etc.
#----------------------------------------------------------------------------

CC = gcc
CFLAGS = -Wall -std=c99
HEADERS = error.h rocketship.h landscape.h
OBJECTS = lunar_lander.o error.o rocketship.o landscape.o

lander: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lncurses -lm -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


#draw1b: draw1b.c 
#	 $(CC) $(CFLAGS) -o draw1b draw1b.c 

clean:
		-rm -f *.o lunar_lander core
		-rm -f $(OBJECTS)
#		-rm -f *.o draw1a core
#		-rm -f *.o draw1b core
