#ifndef JBALL_H
#define JBALL_H

#include <stdio.h>
#include "direction.h"
#include "constants.h"

typedef struct {
   int x_loc;
   int y_loc;
   enum DIRECTION x_dir;
   enum DIRECTION y_dir;
   int active;
} jball;

jball BALL_ARR[MAX_BALL_COUNT];

void move_ball(jball *ball);
enum DIRECTION new_ball_dir(int hit, enum DIRECTION dir);
int ball_step(enum DIRECTION dir);
int contains_ball_at(int x, int y, int show_cursor);
int ball_located_to(enum DIRECTION dir, int x, int y);
int wall_or_ball_located_to(enum DIRECTION dir, int x, int y);
void add_ball(int x, int y, enum DIRECTION y_dir, enum DIRECTION x_dir);
void deactivate_all_balls();
void reset_game_state();
#endif