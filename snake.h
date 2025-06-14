#include <stdio.h>

struct FieldPos
{
    unsigned int fieldWidth;
    unsigned int fieldHeight;
    unsigned int snakeX;
    unsigned int snakeY;
};
struct Rand
{
    unsigned int randCoordX;
    unsigned int randCoordY;
};

void* generatePlayingField(struct FieldPos* pos);

struct FieldPos* initializeSnake(struct FieldPos* pos, char** field, char snakeRenderSymbol);

void moveSnake(struct FieldPos* pos, char*** field, char snakeRenderSymbol, short int direction, unsigned int moveDistance);

void renderField(struct FieldPos* pos, char** field);

void freeMemoryField(struct FieldPos* pos, char** field);

void createSnakeFood(struct FieldPos* pos, struct Rand* rnd, char*** field, char foodSymbol);
