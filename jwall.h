#ifndef JWALL_H
#define JWALL_H

#include <stdio.h>
#include "direction.h"
#include "constants.h"

typedef struct {
   int x_left;
   int x_right;
   int y_top;
   int y_bottom;
   enum DIRECTION dir;
   int active;
} jwall;

jwall WALL_ARR[MAX_WALL_COUNT];

int update_wall(jwall *wall);
int contains_wall_at(int x, int y);
int wall_to_the(enum DIRECTION dir, int x, int y);
jwall *game_wall_at(int x, int y);
void deactive_game_wall(jwall *wall);
void add_wall(int x, int y, enum DIRECTION dir);
void deactivate_all_wals();
#endif