#pragma once

#define FPS 30 

//cap the speed of a moving entity
#define SPEED_CAP 5

//the maximum and minimum force applied to an entity
#define MAX_FORCE 0.1
#define MIN_FORCE 0.001

//width and height of windows
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

//definitions for steering sprite's steering behaviors
#define SEEK		0b00000000000000000000000000000001
#define FLEE		0b00000000000000000000000000000010
#define ARRIVE		0b00000000000000000000000000000100
#define WANDER		0b00000000000000000000000000001000
#define PURSUE		0b00000000000000000000000000010000
#define EVADE		0b00000000000000000000000000100000
