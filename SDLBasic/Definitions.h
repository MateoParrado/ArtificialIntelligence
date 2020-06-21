#pragma once

#define FPS 30 

//width and height of windows
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

//whisker length (for wall avoidance)
#define SIDE_WHISKER_LENGTH 50
#define FRONT_WHISKER_LENGTH 100

//minimum length of obstacle checking for obstacle avoiding sprites
#define MIN_BOX_LENGTH 40.0

//the distance that a hiding spot should be away from an obstacle
#define HIDE_DIST 50

//definitions for steering sprite's steering behaviors
#define SEEK			  0b00000000000000000000000000000001
#define FLEE			  0b00000000000000000000000000000010
#define ARRIVE		 	  0b00000000000000000000000000000100
#define WANDER	 	 	  0b00000000000000000000000000001000
#define PURSUE			  0b00000000000000000000000000010000
#define EVADE		      0b00000000000000000000000000100000
#define WANDER_OBS_AVOID  0b00000000000000000000000001000000
#define WANDER_WALL_AVOID 0b00000000000000000000000010000000
#define INTERPOSE         0b00000000000000000000000100000000
#define HIDE              0b00000000000000000000001000000000