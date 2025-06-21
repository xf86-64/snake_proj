#include <ncurses.h>
#include <stdio.h>
#include "../include/snake.h"


Node* create_node(unsigned int xPos, unsigned int yPos)
{
    Node* tmp_node = malloc(sizeof(Node));
    tmp_node->x = xPos;
    tmp_node->y = yPos;
    tmp_node->next = NULL;
    return tmp_node;
}
void head_insert(Node** head, Node* insert_node)
{
    insert_node->next = (*head);
    *head = insert_node;
}
void delete_list(Node* head)
{
    Node* ptr = head;
    while(head)
    {
        Node* next = ptr->next;
        free(ptr);
        ptr=next;

    }
}
Node* init_snake(Field field)
{
   Node* snake = create_node(3, 4); 
   Node* head_snake = create_node(2, 4);
   head_insert(&snake, head_snake);

    snake=head_snake;
   return snake;
}
enum Direction handle_keyboard(void)
{
    char symbol = getch();
    enum Direction new_dir;
    switch(symbol)
    {
        case KEY_RIGHT:
            new_dir = RIGHT;
            break;
        case KEY_LEFT:
            new_dir = LEFT;
            break;
        case KEY_UP:
            new_dir = UP;
            break;
        case KEY_DOWN:
            new_dir = DOWN;
            break;

    }
    return new_dir;
}  
void move_snake(Node* snake, enum Direction direction)
{
    switch(direction)
    {
        case RIGHT:
            while(snake)
            {
                (snake->x)+=2;
                snake=snake->next;
            }
            break;
        default:
            break;
    } 
}
