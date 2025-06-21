#include <stdio.h>
#include "../include/snake.h"

int main(int argc, char* argv[])
{
    initscr();
    keypad(stdscr, 1); 
    enum Direction dir=RIGHT;
   int x_max, y_max; 
       getmaxyx(stdscr, x_max, y_max);
    Field field = {x_max, y_max};
       char* format;
    Node* snake = init_snake(field);

    while(snake)
    {
        
        mvaddch(snake->y, snake->x, ACS_BLOCK);
        snake=snake->next;

    }

    while(1)
    {
        dir = handle_keyboard();
        clear();
        move_snake(snake, dir);
        mvaddch(snake->y, snake->x, ACS_BLOCK);

 
      refresh();
    } 

       refresh();
    endwin();


     delete_list(snake); 


    return 0;
}

