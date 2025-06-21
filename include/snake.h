#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

enum Direction 
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};
typedef struct Node
{
    unsigned int x;
    unsigned int y;
    struct Node* next;
} Node;
typedef struct Field
{
    unsigned int x_max;
    unsigned int y_max;
} Field;
Node* create_node(unsigned int xPos, unsigned int yPos);
Node* init_snake(Field field);
void move_snake(Node* snake, enum Direction direction);
enum Direction handle_keyboard(void); 
void head_insert(Node** head, Node* insert_node);
void delete_list(Node* head);
