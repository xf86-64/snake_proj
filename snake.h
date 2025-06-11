#include <stdio.h>
//
//typedef union 
//{
//    unsigned int x; 
//    unsigned int y;
//} snakeStartPos; 
//
//
struct FieldPos
{
    unsigned int fieldWidth;
    unsigned int fieldHeight;
    unsigned int snakeX;
    unsigned int snakeY;
    // snakeStartPos snakePos ;
};
void* generatePlayingField(struct FieldPos* pos);

struct FieldPos* initializeSnake(struct FieldPos* pos, char** field, char snakeRenderSymbol);

void moveSnake(struct FieldPos* pos, char*** field, char snakeRenderSymbol, const char* direction, unsigned int moveDistance);

void renderField(struct FieldPos* pos, char** field);

void freeMemoryField(struct FieldPos* pos, char** field);
