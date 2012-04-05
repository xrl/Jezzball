#include "constants.h"
#include "jwall.h"
#include "jball.h"

extern int WALL_COUNT;

int update_wall(jwall *wall){
   int x_left = wall->x_left, x_right = wall->x_right,
       y_top = wall->y_top, y_bottom = wall->y_bottom;
   
   int max_x_left, max_x_right, max_y_top, max_y_bottom;
   
   int empty_region;
   
   if(wall->active == 1){
      if(wall->dir == EW){
         if(wall_located_to(W, x_left, y_top) == 0){
            x_left = x_left-1;
         }
         else{
            max_x_left = 1;
         }
         if(wall_located_to(E, x_right, y_top) == 0){
            x_right = x_right+1;
         }
         else{
            max_x_right = 1;
         }
         
         if(max_x_right == 1 && max_x_left == 1){
            wall->active = 0;
         }
      }
      if(wall->dir == NS){
         if(wall_located_to(N, x_left, y_top) == 0){
            y_top = y_top-1;
         }
         else{
            max_y_top = 1;
         }
         if(wall_located_to(S, x_left, y_bottom) == 0){
            y_bottom = y_bottom+1;
         }
         else{
            max_y_bottom = 1;
         }
         
         if(max_y_top == 1 && max_y_bottom == 1){
            wall->active = 0;
         }
      }
      wall->x_left = x_left;
      wall->x_right = x_right;
      wall->y_top = y_top;
      wall->y_bottom = y_bottom;
   
      if(wall->active == 0){ // The wall has just gone inactive
         // Search up/down or left/right of the wall
         // And set the regions the wall covers accordingly
         if(wall->dir == EW){
            wall->y_top = is_region_empty_north_of(wall);
            wall->y_bottom = is_region_empty_south_of(wall);
         }
         else if(wall->dir == NS){
            wall->x_right = is_region_empty_east_of(wall);
            wall->x_left = is_region_empty_west_of(wall);
         }
      }
   }
   
   return 0;
}

int is_region_empty_north_of(jwall *wall){
   // Find out how far north before we find a wall
   int i,j;
   int max;
   
   // Have to start searching off the wall
   max = wall->y_top-1;
   
   while(contains_wall_at(wall->x_left,max) == 0){
      max = max-1;
   }
   
   for(i=wall->x_left; i<=wall->x_right; i++){
      for(j=wall->y_top-1; j >=max; j--){
         if(contains_ball_at(i,j,1)==1){
            // Contains a ball... no go
            return wall->y_top;
         }
      }
   }
   // Okay, no balls in area
   return max;//max;
}

int is_region_empty_south_of(jwall *wall){
   // Find out how far south before we find a wall
   int i,j;
   int max;
   
   // Have to start searching off the wall
   max = wall->y_bottom+1;
   
   while(contains_wall_at(wall->x_left,max) == 0){
      max = max+1;
   }
   
   for(i=wall->x_left; i<=wall->x_right; i++){
      for(j=wall->y_bottom+1; j<=max; j++){
         if(contains_ball_at(i,j,1)==1){
            // Contains a ball... no go
            return wall->y_bottom;
         }
      }
   }
   // Okay, no balls in area
   return max;//max;
}

int is_region_empty_east_of(jwall *wall){
   // Find out how far east before we find a wall
   int i,j;
   int max;
   
   // Have to start searching off the wall
   max = wall->x_right+1;
   
   while(contains_wall_at(max,wall->y_top) == 0){
      max = max+1;
   }
   
   for(i = wall->x_right+1; i<=max; i++){
      for(j = wall->y_top; j <= wall->y_bottom; j++){
         if(contains_ball_at(i,j,1)==1){
            // Contains a ball... no go
            return wall->x_right;
         }
      }
   }
   // Okay, no balls in area
   return max;//max;
}

int is_region_empty_west_of(jwall *wall){
   // Find out how far east before we find a wall
   int i,j;
   int max;
   
   // Have to start searching off the wall
   max = wall->x_left-1;
   
   while(contains_wall_at(max,wall->y_top) == 0){
      max = max-1;
   }
   
   for(i = wall->x_left-1; i>=max; i--){
      for(j = wall->y_top; j <= wall->y_bottom; j++){
         if(contains_ball_at(i,j,1)==1){
            // Contains a ball... no go
            return wall->x_left;
         }
      }
   }
   // Okay, no balls in area
   return max;//max;
}

int contains_wall_at(int x, int y){
   if((x >= X_MAX || x <= -1) || (y >= Y_MAX || y <= -1)){
      return 1;
   }
   int k;
   for(k=0; k<WALL_COUNT; k++){
      if(x >= WALL_ARR[k].x_left && x <= WALL_ARR[k].x_right){ // within the x range
         if(y >= WALL_ARR[k].y_top && y <= WALL_ARR[k].y_bottom){
               return 1;
         }
      }
   }
   return 0;
}

// x - x location
// y - y location
// current_state - what state must the wall be in?

jwall *game_wall_at(int x, int y){
   int k;
   for(k=0; k<WALL_COUNT; k++){
      if(x >= WALL_ARR[k].x_left && x <= WALL_ARR[k].x_right){ // within the x range
         if(y >= WALL_ARR[k].y_top && y <= WALL_ARR[k].y_bottom){
            if(WALL_ARR[k].active == 1){
               return &WALL_ARR[k];
            }
         }
      }
   }
   return NULL;
}

void deactivate_game_wall(jwall *wall){
   if(wall == NULL){
      return;
   }
   wall->active = 0;
   wall->x_right = -1;
   wall->x_left = -1;
   wall->y_top = -1;
   wall->y_bottom = -1;
}

int wall_located_to(enum DIRECTION dir, int x, int y){
   switch(dir){
      case N:
      return contains_wall_at(x,y-DBALL);
      break;
      case E:
      return contains_wall_at(x+DBALL,y);
      break;
      case S:
      return contains_wall_at(x,y+DBALL);
      break;
      case W:
      return contains_wall_at(x-DBALL,y);
      break;
      default:
      break;
   };
}

void add_wall(int x, int y, enum DIRECTION dir){
   if(WALL_ARR[WALL_COUNT-1].active == 1){
      return;
   }
   jwall *ptr = &WALL_ARR[WALL_COUNT];
   ptr->x_left = x;
   ptr->x_right = x;
   ptr->y_top = y;
   ptr->y_bottom = y;
   ptr->active = 1;
   ptr->dir = dir;
   WALL_COUNT+=1;
}

void deactivate_all_walls(){
   int i;
   for(i=0; i<MAX_WALL_COUNT; i++){
      WALL_ARR[i].active = 0;
   }
}