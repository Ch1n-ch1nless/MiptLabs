#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*=============================================*/

typedef int stk_elem_t;

/*=============================================*/

struct Node
{
    stk_elem_t      data;
    struct Node*    next;
};

struct Stack 
{
    size_t          size;
    struct Node*    head;
};

/*=============================================*/

struct Stack*   StackCtor(void);
int             Push(struct Stack* stack, stk_elem_t* const buffer);
int             Top(struct Stack* const stack, stk_elem_t* const buffer);
int             Pop(struct Stack* const stack, stk_elem_t* const buffer);
struct Stack*   StackDtor(struct Stack* const stack);

/*=============================================*/