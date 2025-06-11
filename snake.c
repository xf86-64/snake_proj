#include "snake.h"
#include <stdlib.h>
#include <string.h>

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
    // printf("%d %d\n", pos->snakeX, pos->snakeY);
    return pos;
}
void moveSnake(struct FieldPos* pos, char*** field, char snakeRenderSymbol, const char* direction, unsigned int moveDistance)
{
    // int isNotThere = 0;
    (*field)[pos->snakeY][pos->snakeX] = ' ';
    unsigned int newX, newY;
    newX=newY=0;
    if(strcmp(direction, "left") == 0)
    {
        newX = (pos->snakeX)-moveDistance;
        pos->snakeX = newX;
        (*field)[pos->snakeY][pos->snakeX] = snakeRenderSymbol;  
    }
    else if(strcmp(direction, "right") == 0)
    { 
        newX = (pos->snakeX)+moveDistance;
        pos->snakeX = newX;
        (*field)[pos->snakeY][pos->snakeX] = snakeRenderSymbol;  
    }
    else if(strcmp(direction, "top") == 0)
    {
         newY = (pos->snakeY)+moveDistance;
         pos->snakeY = newY;
        (*field)[pos->snakeY][pos->snakeX] = snakeRenderSymbol;  
    }
    else if(strcmp(direction, "down") == 0)
    {
         newY = (pos->snakeY)-moveDistance;
         pos->snakeY = newY;
        (*field)[pos->snakeY][pos->snakeX] = snakeRenderSymbol;  
    }
    else 
        return;

   //    if(isTopArrow || isDownArrow)
//        pos->snakeY = newY;
//
     
    printf("%d %d\r", pos->snakeX, pos->snakeY);
    
    //(*field)[pos->snakeY][pos->snakeX] = snakeRenderSymbol;  
}
void renderField(struct FieldPos* pos, char** field)
{
    // printf("%d %d\n", pos->snakeX, pos->snakeY);
    unsigned int i, j;
    for (i = 0; i < pos->fieldHeight; i++)
    {         
        printf("\n");
        for (j = 0; j < pos->fieldWidth; j++)
        {
            printf("%c", field[i][j]); 
        }
    }
//      printf("\n");
       printf("\r");
          fflush(stdout);

        // printf("\033[%d;%dH", j, i);

}
void freeMemoryField(struct FieldPos *pos, char **field)
{
    for (int i = 0; i < pos-> fieldHeight; i++)
    {
        free(field[i]); 
    }
    free(field);    
}
