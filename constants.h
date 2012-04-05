#ifndef CONSTANTS_H
#define CONSTANTS_H

#define CONSOLE_VERSION 1
#define DEBUG 1

#if CONSOLE_VERSION == 1
#define X_MAX 80
#define Y_MAX 23
#endif

#if CONSOLE_VERSION == 0
#define X_MAX 40
#define Y_MAX 30
#endif

#define INITIAL_BALL_COUNT 0
#define INITIAL_WALL_COUNT 0

#define MAX_WALL_COUNT 40
#define MAX_BALL_COUNT 20

#define DBALL 1

#define REFRESH_RATE 80000000

#if CONSOLE_VERSION == 1
#define SHOW_SCURSOR 1
#define SCURSOR_REFRESH_RATE 10000000
#endif
#endif