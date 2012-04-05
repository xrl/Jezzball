#ifndef SEARCH_CURSOR_H
#define SEARCH_CURSOR_H
typedef struct{
   int x;
   int y;
   int active;
   int hit;
} search_cursor;

search_cursor SCURSOR;
#endif