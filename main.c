#include <stdio.h>
#include "snake.h"
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

struct termios terminal;
tcflag_t oldTerminal_lFlags; 

char** gen = NULL;
char* snake = NULL;

struct FieldPos pos = {54, 27};

enum directions
{
   LEFT,
   RIGHT,
   TOP,
   DOWN
};

int characterIsInUnacceptableZone(struct FieldPos* p)
{
    if(gen[p->snakeY][p->fieldWidth-1] != '#' || gen[p->snakeY][0] != '#')
    {
        return 0;
    } 
    return 1;   
} 
void signalOfImmediateGameExit(int sig) // signal function (handler)
{
    if(gen != NULL && snake!= NULL)
    {
        printf("\033[2J");
        printf("\033[3J");
        printf("\033[H");
        fflush(stdout);
        printf("You successfully immediate exit from snake game\n");
        terminal.c_lflag = oldTerminal_lFlags;

        tcsetattr(0, TCSANOW, &terminal);
        freeMemoryField(&pos, gen); 
        free(snake);
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
    unsigned int snakeSize = 1;
    snake=(char*)malloc(snakeSize*sizeof(char));
    snake[0] = '*';
    snakeSize++;
    snake[1] = '*';
    int characterIsPickUp = 1;
    int isLastKeyDown = 1; 
    printf("\033[2J\033[1;1H");   

               while(isWin)
               { 
                    isWin=characterIsInUnacceptableZone(p);
                                             
                   printf("\033[H");
                   //printf("snakesize=%d", snakeSize);
                   if(p->snakeX==rnd.randCoordX && p->snakeY==rnd.randCoordY)
                   {
                      characterIsPickUp = 1;
                      addSize('*', ++snakeSize, &snake);
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

                                             moveSnake(p, &gen, '*', RIGHT, 1, snakeSize, &snake);
                                             isLastKeyDown = RIGHT; 
                                             isWin = characterIsInUnacceptableZone(p); 
                                             renderField(p, gen);    
                                             break;
                                         case 'D': // left arrow
                                             printf("\033[3J\033[H");
                                             fflush(stdout);
                                             moveSnake(p, &gen, '*', LEFT, 1, snakeSize, &snake);
                                             isLastKeyDown = LEFT;
                                             isWin=characterIsInUnacceptableZone(p);
                                             renderField(p, gen); 

                                             break;
                                   
                                          case 'B': // top arrow
                                             printf("\033[3J\033[H");
                                             fflush(stdout);

                                             moveSnake(p, &gen, '*', TOP, 1, snakeSize, &snake);
                                             isLastKeyDown = TOP;
                                             isWin=characterIsInUnacceptableZone(p);
                                             renderField(p, gen);
                                             break;
                                           case 'A': // down arrow 
                                             printf("\033[3J\033[H");
                                             fflush(stdout);
                                             moveSnake(p, &gen, '*', DOWN, 1, snakeSize, &snake);
                                             isLastKeyDown = DOWN;
                                             isWin=characterIsInUnacceptableZone(p);
                                             renderField(p, gen);  
                                             break;
                                            default:
                                                goto A;
                                     }                                                      
                                 }
                                 else
                                     goto A;
                              }
                             else 
                                goto A;
                             
                           }

                   else 
                   { 
                               isWin = characterIsInUnacceptableZone(p); 
A:                             switch(isLastKeyDown)
                               {
                                   case LEFT: 
                                       moveSnake(p, &gen, '*', LEFT, 1, snakeSize, &snake);
                                       break;
                                   case RIGHT:
                                       moveSnake(p, &gen, '*', RIGHT, 1, snakeSize, &snake); 
                                       break;
                                   case TOP:
                                      moveSnake(p, &gen, '*', TOP, 1, snakeSize, &snake); 
                                      break;
                                   case DOWN:
                                      moveSnake(p, &gen, '*', DOWN, 1, snakeSize, &snake); 
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
    
   for(int i = 0; i <= snakeSize; i++)
        printf("%c", snake[i]);
//   if(isWin)
//       printf("You win in snake game!\n");
//   else
//       printf("You lost in snake game\n");
//

    terminal.c_lflag = oldTerminal_lFlags;

    tcsetattr(0, TCSANOW, &terminal);

    freeMemoryField(p, gen);
    free(snake);
    return 0;
}
