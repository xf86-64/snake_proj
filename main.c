#include <stdio.h>
#include "snake.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h> // signal handler(ctrl+c detected)


int main(int argc, char* argv[])
{
//    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
//    if(flags == -1)
//    {
//        perror("fcntl F_GETFL error\n"); 
//        return 1;
//    }
//    if (fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK) == -1)
//    {
//        perror("fcntl F_SETFL error\n");
//        return 1;
//    }
//

    struct termios terminal;
    tcflag_t oldTerminal_lFlags;
    tcgetattr(0, &terminal); 

    oldTerminal_lFlags = terminal.c_lflag;
    terminal.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(0, TCSANOW, &terminal);

    struct FieldPos pos = {25, 10};
    char** gen = (char**)generatePlayingField(&pos);
    
    struct FieldPos* p = initializeSnake(&pos, gen, '*');
    char buf;
     renderField(p, gen);
     printf("\033[H");   

   
                    while(read(STDIN_FILENO, &buf, 1))
                    { 
                              printf("\033[H");

                              if (buf == '\x1B')
                              {
                                  char tmp[2];
                                  if(read(0, &tmp[0], 1) != 1) break;
                                  if(read(0, &tmp[1], 1) != 1) break; 
                                  
                                  if (tmp[0]=='[')
                                  {
                                      switch(tmp[1])
                                      {
                                          case 'C': // right arrow
                                              moveSnake(p, &gen, '*', "right", 1);
                                               
                                              renderField(p, gen);

                                              break;
                                          case 'D': // left arrow
                                              moveSnake(p, &gen, '*', "left", 1);
                                              renderField(p, gen); 
                                              break;

                                           case 'B': // top arrow
                                              moveSnake(p, &gen, '*', "top", 1);
                                              renderField(p, gen);
       
                                              break;
                                            case 'A': // down arrow 
                                              moveSnake(p, &gen, '*', "down", 1);
                                              renderField(p, gen);  
                                              break;
                                      }                                                      
                                  }
                              }
                              else if (buf==4) {break;}
}
    printf("\033[2J");
    printf("\033[3J");
    printf("\033[H");

    terminal.c_lflag = oldTerminal_lFlags;

    tcsetattr(0, TCSANOW, &terminal);

    freeMemoryField(p, gen);
    return 0;
}
