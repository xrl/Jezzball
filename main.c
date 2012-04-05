// ECE412 Spring 2009
// Xavier Lange
// Majid Hassan
// A jezz ball game simulation based in the terminal
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Custom includes
#include "constants.h"
#include "draw.h"
#include "direction.h"
#include "jball.h"
#include "jwall.h"

#if CONSOLE_VERSION == 0
#include "jezzball.h"
#endif

extern int WALL_COUNT;
extern int BALL_COUNT;

int clk=0;
int initialized = 0;

#if CONSOLE_VERSION == 1
int main(){
   game();
   return 0;
}
#endif

int game(){
   struct timespec refresh_rate;
   refresh_rate.tv_sec = 0;
   refresh_rate.tv_nsec = REFRESH_RATE;//190000000;
   
   int i;
   #if CONSOLE_VERSION == 1
   reset_game_state();
   #endif
   #if CONSOLE_VERSION == 0
   if(initialized == 0 || RestartGame == 1){
      reset_game_state();
      RestartGame = 0;
      initialized = 1;
   }
   #endif
   
   // add_ball(0,0,S,E);
   // add_ball(15,15,N,W);
   
   #if CONSOLE_VERSION == 1
   while(1){
   #endif
   
      #if DEBUG == 1
      if(clk < 1000){
         clk+=1;
      }
      if(clk == 2){
         add_wall(15,15,NS);
      }
      #endif
      
      for(i=0; i<WALL_COUNT; i++){
         update_wall(&WALL_ARR[i]);
      }
      for(i=0; i<BALL_COUNT; i++){ // swap ball_trigger for BALL_COUNT
         move_ball(&BALL_ARR[i]);
      }
      render();
   #if CONSOLE_VERSION ==1
      print_screen();  
      nanosleep(&refresh_rate,NULL);
   }
   #endif

   return 0;
}

// Functions you should care about
// add_ball(x,y,y_dir,x_dir)
// add_wall(x,y,dir)
// reset_game_state()