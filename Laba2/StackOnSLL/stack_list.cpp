#include "stack_list.h"

struct Stack* StackCtor(void)
{
    struct Stack* new_stack = NULL;

    new_stack = (struct Stack*) calloc(1, sizeof(struct Stack));

    new_stack->size = 0;
    new_stack->head = NULL;
    
    return new_stack;
}

int Push(struct Stack* stack, stk_elem_t* const buffer)
{
    assert((stack  != NULL) && "Pointer to \"stack\"  is not NULL!!!");
    assert((buffer != NULL) && "Pointer to \"buffer\" is not NULL!!!");

    struct Node* new_node = (struct Node*) calloc(1, sizeof(struct Node));

    new_node->data = *buffer;
    new_node->next = stack->head;

    stack->head = new_node;
    stack->size ++;

    return 1;
}

int Top(struct Stack* const stack, stk_elem_t* const buffer)
{
    assert((stack  != NULL) && "Pointer to \"stack\"  is not NULL!!!");
    assert((buffer != NULL) && "Pointer to \"buffer\" is not NULL!!!");

    *buffer = stack->head->data;

    return 1;
}

int Pop(struct Stack* const stack, stk_elem_t* const buffer)
{
    assert((stack  != NULL) && "Pointer to \"stack\"  is not NULL!!!");
    assert((buffer != NULL) && "Pointer to \"buffer\" is not NULL!!!");

    *buffer = stack->head->data;
    
    struct Node* next_node= stack->head->next;

    free(stack->head);

    stack->head = next_node;
    stack->size --;

    return 1;
}

struct Stack* StackDtor(struct Stack* const stack)
{
    assert((stack  != NULL) && "Pointer to \"stack\"  is not NULL!!!");

    struct Node* next_node = NULL;

    while(stack->size != 0)
    {
        next_node = stack->head->next;
        free(stack->head);
        stack->head = next_node;
        stack->size --;
    }

    return stack;
}
