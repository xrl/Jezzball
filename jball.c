#include "jball.h"
#include "jwall.h"
#include "constants.h"
#include <time.h>
#include "search_cursor.h"
#include "draw.h"

extern int BALL_COUNT;

void move_ball(jball *ball){
   int xstep, ystep;
   int collision_on_x, collision_on_y;
   
   jwall *game_wall = NULL;
   
   collision_on_x = wall_or_ball_located_to(ball->x_dir,ball->x_loc,ball->y_loc);
   collision_on_y = wall_or_ball_located_to(ball->y_dir,ball->x_loc,ball->y_loc);
   
   // We need to make the collision was not caused by an in game wall
   // because we do not want to change direction on that, plus
   // we want to disable that wall
   if(collision_on_x == 1 && collision_on_y == 1){
      game_wall = game_wall_at(ball->x_loc+ball_step(ball->x_dir),
                               ball->y_loc+ball_step(ball->y_dir));
      if(game_wall != NULL){
         collision_on_x = 0;
         collision_on_y = 0;
      }
   }
   else if(collision_on_x == 1){
      game_wall = game_wall_at(ball->x_loc+ball_step(ball->x_dir),
                               ball->y_loc);
      if(game_wall != NULL){
         collision_on_x = 0;
      }
   }
   else if(collision_on_y == 1){
      game_wall = game_wall_at(ball->x_loc,
                               ball->y_loc+ball_step(ball->y_dir));
      if(game_wall != NULL){ // This collision doesn't count, we'll keep going in the y_dir
         collision_on_y = 0;
      }
   }
   
   deactivate_game_wall(game_wall); // It checks for NULL
   
   
   ball->x_dir = new_ball_dir(collision_on_x,ball->x_dir);
   ball->y_dir = new_ball_dir(collision_on_y,ball->y_dir);
   xstep = ball_step(ball->x_dir);
   ystep = ball_step(ball->y_dir);
   
   ball->x_loc = ball->x_loc+xstep;
   ball->y_loc = ball->y_loc+ystep;
   return;
}

enum DIRECTION new_ball_dir(int hit, enum DIRECTION dir){
   if(hit != 1){
      return dir;
   }
   
   switch(dir){
      case N:
      return S;
      case S:
      return N;
      case E:
      return W;
      case W:
      return E;
   }
}

int ball_step(enum DIRECTION dir){
   switch(dir){
      case N:
      return -DBALL;
      case E:
      return DBALL;
      case S:
      return DBALL;
      case W:
      return -DBALL;
      default:
      return 0; // If you see a ball stop moving at a 45 degree... look here!
   };
   
}

int contains_ball_at(int x, int y, int show_cursor){
   int k, retval=0;
   for(k=0; k<BALL_COUNT; k++){
      if(BALL_ARR[k].active == 1 && BALL_ARR[k].y_loc == y && BALL_ARR[k].x_loc == x){
         retval = 1;
         break;
      }
      if(retval == 1){
         break;
      }
   }
   
   #if SHOW_SCURSOR == 1
   struct timespec refresh_rate;
   if(show_cursor == 1){
      refresh_rate.tv_sec = 0;
      refresh_rate.tv_nsec = SCURSOR_REFRESH_RATE;
   
      SCURSOR.active = 1;
      SCURSOR.hit = retval; // Is it a hit?
      SCURSOR.x = x;
      SCURSOR.y = y;
      render();
      print_screen();
      nanosleep(&refresh_rate,NULL);
      SCURSOR.active = 0;
      SCURSOR.hit = 0;
   }
   #endif
   
   
   return retval;
}

int ball_located_to(enum DIRECTION dir, int x, int y){
   switch(dir){
      case N:
      return contains_ball_at(x,y-DBALL,0);
      break;
      case E:
      return contains_ball_at(x+DBALL,y,0);
      break;
      case S:
      return contains_ball_at(x,y+DBALL,0);
      break;
      case W:
      return contains_ball_at(x-DBALL,y,0);
      break;
      default:
      break;
   };
}

int wall_or_ball_located_to(enum DIRECTION dir, int x, int y){
   return wall_located_to(dir, x, y) || ball_located_to(dir, x, y);
}

void add_ball(int x, int y, enum DIRECTION y_dir, enum DIRECTION x_dir){
   if(BALL_COUNT >= MAX_BALL_COUNT){
      return;
   }
   BALL_ARR[BALL_COUNT-1].x_loc = x;
   BALL_ARR[BALL_COUNT-1].y_loc = y;
   BALL_ARR[BALL_COUNT-1].x_dir = x_dir;
   BALL_ARR[BALL_COUNT-1].y_dir = y_dir;
   BALL_ARR[BALL_COUNT-1].active = 1;
   
   BALL_COUNT = BALL_COUNT+1;
}

void deactivate_all_balls(){
   int i;
   for(i=0; i<MAX_BALL_COUNT; i++){
      BALL_ARR[i].active = 0;
   }
}

void reset_game_state(){
   deactivate_all_balls();
   deactivate_all_walls();
}