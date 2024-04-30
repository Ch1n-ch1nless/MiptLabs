#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*=============================================*/

typedef int stk_elem_t;

/*=============================================*/

const size_t    START_CAPACITY          = 0x1000;          
const size_t    STACK_COEF_TO_REDUCE    = 4;        //Constant between size and capacity, when we can call realloc down
const size_t    STACK_SIZE_DOWN         = 2;        //Constant, by which we increase the stack capacity
const size_t    STACK_SIZE_UP           = 2;        //Constant, by which we reduce the stack capacity

enum ERRORS : int
{
    ERROR   = 0,
    OK      = 1,
};

struct Stack 
{
    size_t      size;
    size_t      capacity;
    stk_elem_t* data;
};

/*=============================================*/

struct Stack*   StackCtor(const size_t size);
int             Push(struct Stack* stack, stk_elem_t* const buffer);
int             Top(struct Stack* const stack, stk_elem_t* const buffer);
int             Pop(struct Stack* const stack, stk_elem_t* const buffer);
struct Stack*   StackDtor(struct Stack* const stack);
struct Stack*   StackClear(struct Stack* const stack);

/*=============================================*/