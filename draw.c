#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "draw.h"
#include "jball.h"
#include "jwall.h"
#include "search_cursor.h"

#if CONSOLE_VERSION==0
#include "jezzball.h"
#endif

extern int WALL_COUNT;
extern char SCREEN_BUFFER[Y_MAX][X_MAX];

void print_screen(){
   int j;
   int length;
   char line_buf[X_MAX+1];
   for(j=0; j<Y_MAX; j++){
      strncpy(line_buf, SCREEN_BUFFER[j], X_MAX);
      line_buf[X_MAX] = '\0';
      length = strlen(line_buf);
      printf("%s\n", line_buf);
   }
}

void render(){
   int i,j,k;
   for(j=0; j<Y_MAX; j++){
      for(i=0; i<X_MAX; i++){
         #if SHOW_SCURSOR == 1 && CONSOLE_VERSION == 1
         if(SCURSOR.active == 1 && SCURSOR.x == i && SCURSOR.y == j){
            if(SCURSOR.hit == 1){
               SCREEN_BUFFER[j][i] = '!';
            }
            else{
               SCREEN_BUFFER[j][i] = '@';
            }
         }
         else
         #endif
         #if CONSOLE_VERSION == 1
         if(contains_ball_at(i,j,0) == 1){
            SCREEN_BUFFER[j][i] = '*';
         }
         else if(contains_wall_at(i,j) == 1){
            SCREEN_BUFFER[j][i] = '#';
         }
         else{
            SCREEN_BUFFER[j][i] = ' ';
         }
         #endif
         #if CONSOLE_VERSION == 0
         if(contains_ball_at(i,j,0) == 1){
            Ball[j] |= 0x8000000000000000 >> i;
         }
         else if(contains_wall_at(i,j) == 1){
            Wall[j] |= 0x8000000000000000 >> i;
         }
         #endif
         
      }
   }
}