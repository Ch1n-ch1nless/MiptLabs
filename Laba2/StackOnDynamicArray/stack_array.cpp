#include "stack_array.h"

static int StackReallocUp(struct Stack* const stack)
{
    assert((stack != NULL) && "Pointer to \"stack\" is nort NULL!!!");

    stack->capacity *= 2;

    stk_elem_t* new_data_array = NULL;

    new_data_array = (stk_elem_t*) calloc(stack->capacity, sizeof(stk_elem_t));
    if (new_data_array == NULL)
        return ERROR;

    stack->data = new_data_array;
    
    return OK;
}

static int StackReallocDown(struct Stack* const stack)
{
    assert((stack != NULL) && "Pointer to \"stack\" is nort NULL!!!");

    stk_elem_t* new_data_array = NULL;

    new_data_array = (stk_elem_t*) calloc(stack->capacity / STACK_SIZE_DOWN, sizeof(stk_elem_t));
    if (new_data_array == NULL)
        return ERROR;

    stack->data     = new_data_array;
    stack->capacity /= STACK_SIZE_DOWN;

    return OK;
}

struct Stack* StackCtor(const size_t size)
{
    struct Stack* new_stack = NULL;

    new_stack = (struct Stack*) calloc(1, sizeof(struct Stack));
    if (new_stack == NULL)
        return NULL;

    new_stack->capacity = size;
    new_stack->size     = 0;
    
    new_stack->data = (stk_elem_t*) calloc(size, sizeof(stk_elem_t));
    if (new_stack->data == NULL)
        return NULL;
    
    return new_stack;
}

int Push(struct Stack* stack, stk_elem_t* const buffer)
{
    assert((stack  != NULL) && "Pointer to \"stack\"  is not NULL!!!");
    assert((buffer != NULL) && "Pointer to \"buffer\" is not NULL!!!");

    if (stack->size >= stack->capacity)
    {
        if (StackReallocUp(stack) == ERROR)
        {
            return ERROR;
        }
    }

    stack->data[stack->size] = *buffer;
    stack->size += 1;

    return OK;
}

int Top(struct Stack* const stack, stk_elem_t* const buffer)
{
    assert((stack  != NULL) && "Pointer to \"stack\"  is not NULL!!!");
    assert((buffer != NULL) && "Pointer to \"buffer\" is not NULL!!!");

    *buffer = stack->data[stack->size-1];

    return OK;
}

int Pop(struct Stack* const stack, stk_elem_t* const buffer)
{
    assert((stack  != NULL) && "Pointer to \"stack\"  is not NULL!!!");
    assert((buffer != NULL) && "Pointer to \"buffer\" is not NULL!!!");

    if (stack->size <= (stack->capacity / STACK_COEF_TO_REDUCE))
    {
        if (StackReallocDown(stack) == ERROR)
        {
            return ERROR;
        }
    }

    *buffer = stack->data[stack->size-1];
    stack->size -= 1;

    return OK;
}

struct Stack* StackDtor(struct Stack* const stack)
{
    assert((stack != NULL) && "Pointer to \"stack\" is not NULL!!!");

    free(stack->data);
    stack->data = NULL;

    stack->size     = 0;
    stack->capacity = 0;

    return stack;
}

struct Stack* StackClear(struct Stack* const stack)
{
    assert((stack != NULL) && "Pointer to \"stack\" is not NULL!!!");

    free(stack->data);

    stack->data = (stk_elem_t*) calloc(START_CAPACITY, sizeof(stk_elem_t));

    stack->size = 0;
    stack->capacity = START_CAPACITY;

    return stack;
}