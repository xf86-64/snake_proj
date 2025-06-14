#include <stdio.h>
#include "snake.h"
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
// #include <ncurses.h>

struct termios terminal;
tcflag_t oldTerminal_lFlags; 

char** gen = NULL;

struct FieldPos pos = {54, 27};

int characterIsInUnacceptableZone(struct FieldPos* p)
{
    if(p->snakeX == 0 || p->snakeY == 0 || p->snakeX == p->fieldWidth-1 || p->snakeY == p->fieldHeight-1)
    {
        return 0;
    } 
    return 1;   
} 
void signalOfImmediateGameExit(int sig) // signal function (handler)
{
    if(gen != NULL)
    {
        printf("\033[2J");
        printf("\033[3J");
        printf("\033[H");
        fflush(stdout);
        printf("You successfully immediate exit from snake game\n");
        terminal.c_lflag = oldTerminal_lFlags;

        tcsetattr(0, TCSANOW, &terminal);
        freeMemoryField(&pos, gen); 
        exit(1);  
    }
    else
        printf("no data\n");
}

int main(int argc, char* argv[])
{
     srand(time(0));
     tcgetattr(0, &terminal); 

     oldTerminal_lFlags = terminal.c_lflag;
     terminal.c_lflag &= ~(ECHO | ICANON);

     tcsetattr(0, TCSANOW, &terminal);
 
     gen = (char**)generatePlayingField(&pos);

     if(gen == NULL) return 1;

     struct FieldPos* p = initializeSnake(&pos, gen, '*');

    char buf;
    struct Rand rnd = {0, 0};
    signal(SIGINT, signalOfImmediateGameExit);
    renderField(p, gen);
    int isWin = 1;
    int isStartGame = 0;

    int characterIsPickUp = 1;
    char *directions[4] = {"left", "right", "top", "down"};
    int isLastKeyDown = 1; 
    printf("\033[2J\033[1;1H");   

               while(isWin)
               { 
                   if(p->snakeX==rnd.randCoordX && p->snakeY==rnd.randCoordY)
                   {
                        characterIsPickUp = 1; 
                   }

                   fd_set fds;
                   FD_ZERO(&fds);
                   FD_SET(STDIN_FILENO, &fds);
                   struct timeval timeout={0, 100000};
                   int ready = select(STDIN_FILENO+1, &fds, NULL, NULL, &timeout);
                   if(ready>0 && FD_ISSET(STDIN_FILENO, &fds))
                   {
                           isStartGame = 1;              
                           char buf;        
                           read(STDIN_FILENO, &buf, 1);  
                             if (buf== '\x1B')
                             {
                                 char tmp[2];
                                 if(read(0, &tmp[0], 1) != 1) break;
                                 if(read(0, &tmp[1], 1) != 1) break; 
                                 
                                 if (tmp[0]=='[')
                                 {
                                     switch(tmp[1])
                                     {
                                         case 'C': // right arrow

                                             printf("\033[3J\033[H");

                                             fflush(stdout); // clean terminal buffer

                                             moveSnake(p, &gen, '*', "right", 1);
                                             isLastKeyDown = 1; 
                                             isWin = characterIsInUnacceptableZone(p); 
                                             renderField(p, gen);    
                                             break;
                                         case 'D': // left arrow
                                             printf("\033[3J\033[H");
                                             fflush(stdout);
                                             moveSnake(p, &gen, '*', "left", 1);
                                             isLastKeyDown = 0;
                                             isWin=characterIsInUnacceptableZone(p);
                                             renderField(p, gen); 

                                             break;
                                   
                                          case 'B': // top arrow
                                             printf("\033[3J\033[H");
                                             fflush(stdout);

                                             moveSnake(p, &gen, '*', "top", 1);
                                             isLastKeyDown = 2;
                                             isWin=characterIsInUnacceptableZone(p);
                                             renderField(p, gen);
                                             break;
                                           case 'A': // down arrow 
                                             printf("\033[3J\033[H");
                                             fflush(stdout);
                                             moveSnake(p, &gen, '*', "down", 1);
                                             isLastKeyDown = 3;
                                             isWin=characterIsInUnacceptableZone(p);
                                             renderField(p, gen);  
                                             break;
                                     }                                                      
                                 }
                              } 
                           }
                   else 
                   { 
                               isWin = characterIsInUnacceptableZone(p); 
                               switch(isLastKeyDown)
                               {
                                   case 0:
                                       moveSnake(p, &gen, '*', directions[0], 1);
                                       break;
                                   case 1:
                                       moveSnake(p, &gen, '*', directions[1], 1); 
                                       break;
                                   case 2:
                                      moveSnake(p, &gen, '*', directions[2], 1); 
                                      break;
                                   case 3:
                                      moveSnake(p, &gen, '*', directions[3], 1); 
                                      break; 

                               }
                               isWin = characterIsInUnacceptableZone(p);

                           if(characterIsPickUp && isStartGame)
                           {
                               createSnakeFood(p, &rnd, &gen, ')');
                               characterIsPickUp = 0;
                           }
                           printf("\033[3J\033[H");
                           renderField(p, gen);
                           fflush(stdout);



                    } 
}
   printf("\033[2J");
   printf("\033[3J");
   printf("\033[H");
   fflush(stdout);

   if(isWin)
       printf("You win in snake game!\n");
   else
       printf("You lost in snake game\n");


    terminal.c_lflag = oldTerminal_lFlags;

    tcsetattr(0, TCSANOW, &terminal);

    freeMemoryField(p, gen);
    return 0;
}
