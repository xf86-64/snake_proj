#include "snake.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void* generatePlayingField(struct FieldPos* pos)
{
    char** field = (char**)malloc(pos->fieldHeight*sizeof(char*));
    if (field==NULL)
    {
        printf("failed to allocate memory\n");
        return NULL;
    }

    unsigned int fieldHeight = pos->fieldHeight;
    unsigned int fieldWidth = pos->fieldWidth;
    for (int i = 0; i < fieldHeight; i++)
    {
        field[i] = (char*)malloc(fieldWidth*sizeof(char));
    }

    for (unsigned int i = 1;  i < fieldHeight-1; i++)
    {
        field[i][0] = '#';
        field[i][fieldWidth-1] = '#';
        for (unsigned int j = 1; j < fieldWidth-1; j++)
        {
            field[i][j] = ' ';
        }
        for (unsigned d = 0; d < fieldWidth; d++)
        {
            field[0][d] = '#';
            field[fieldHeight-1][d] = '#';
        }
    }


    return field;

}

struct FieldPos* initializeSnake(struct FieldPos* pos, char** field, char snakeRenderSymbol)
{
    unsigned int x;
    unsigned int y;
    x = (unsigned int) (pos->fieldWidth)/2;

    y = (unsigned int) (pos->fieldHeight)/2;
    pos->snakeX = x;
    pos->snakeY = y;

    field[y][x] = snakeRenderSymbol;   
    return pos;
}
void moveSnake(struct FieldPos* pos, char*** field, char snakeRenderSymbol, short int direction, unsigned int moveDistance, unsigned int snakeSize, char** snake)
{
    // (*field)[pos->snakeY][pos->snakeX] = ' ';
    unsigned int newX = 0, newY = 0;
    //char buf[3] = {'*', '*', '*'}; 
    
    unsigned int curSnakePosX = pos->snakeX;
    unsigned int curSnakePosY = pos->snakeY;

    unsigned int newPointX;
    unsigned int newPointY;

    unsigned int i = 0;
   // switch(direction)
   // {
   //     case 1:
   //       
   //         for (; i < snakeSize; i++)
   //         {
   //             (*field)[curSnakePosY][(curSnakePosX+i)] = ' ';
   //            
   //             (*field)[curSnakePosY][(curSnakePosX+i)+snakeSize] = (*snake)[i]; 
   //            
   //         }
   //         pos->snakeX = curSnakePosX+i;
   //         (*field)[curSnakePosY][pos->snakeX] = ' '; 
   //         break;
   //     case 0:
   //         
   //         for(; i < snakeSize; i++)
   //         {
   //             (*field)[curSnakePosY][(curSnakePosX-i)] = ' ';

 
   //             (*field)[curSnakePosY][(curSnakePosX-i)+snakeSize] = (*snake)[i]; 
   //        }
   //         pos->snakeX = curSnakePosX-i;
   //         (*field)[curSnakePosY][pos->snakeX] = ' '; 
   //         break;
   // }
   switch(direction)
   {
       case 0:
           for(; i < snakeSize; i++)
           {
                (*field)[curSnakePosY][curSnakePosX+1] = ' ';
                (*field)[curSnakePosY][curSnakePosX-1] = (*snake)[i]; 
                pos->snakeX = curSnakePosX-1;
           } 
           break;
       case 1:
           for(; i < snakeSize; i++)
           {
                (*field)[curSnakePosY][curSnakePosX-1] = ' ';
                (*field)[curSnakePosY][curSnakePosX+1] = (*snake)[i]; 
                pos->snakeX = curSnakePosX+1;
           }
            break;
   }
    printf("%d %d", pos->snakeX, pos->snakeY);
}
void addSize(char snakeRenderSymbol, unsigned int snakeSize, char** snake)
{
    (*snake)[snakeSize] = snakeRenderSymbol; 
}
void renderField(struct FieldPos* pos, char** field)
{ 
    unsigned int i, j;
    for (i = 0; i < pos->fieldHeight; i++)
    {         
        printf("\n");
        for (j = 0; j < pos->fieldWidth; j++)
        {
            printf("%c", field[i][j]); 
        }
    }
    printf("\r");
    fflush(stdout);

}

void freeMemoryField(struct FieldPos *pos, char** field)
{
    for (int i = 0; i < pos-> fieldHeight; i++)
    {
        free(field[i]); 
    }
    free(field);    
}

void createSnakeFood(struct FieldPos* pos, struct Rand* rnd, char*** field, char foodSymbol)
{
    unsigned int minCoordX = 1;
    unsigned int maxCoordX = pos->fieldWidth-1;

    unsigned int minCoordY = 1;
    unsigned int maxCoordY = pos->fieldHeight-1;

    unsigned int randCoordX = rand()%(maxCoordX-minCoordX+1);
    unsigned int randCoordY = rand()%(maxCoordY-minCoordY+1);

    if ((randCoordX == rnd->randCoordX && randCoordY == rnd->randCoordY) || (randCoordX == rnd->randCoordX || randCoordY == rnd->randCoordY) || (*field)[randCoordY][randCoordX] == '#')
    {
        createSnakeFood(pos, rnd, field, foodSymbol);
    }
    else 
    {
        rnd->randCoordX = randCoordX;
        rnd->randCoordY = randCoordY;
        (*field)[rnd->randCoordY][rnd->randCoordX] = foodSymbol;
    }
}



