#include "stack_array.h"

void Test1(struct Stack* const stack)
{
    assert((stack != NULL) && "Pointer to \"stack\" is not NULL!!!");

    size_t new_stk_size = 0;
    stk_elem_t buffer = 0;

    clock_t time_start = clock();

    for (int i = 0; i < 1e6; i++)
    {
        buffer = rand();
        Push(stack, &buffer);
    }

    while (stack->size >= 1e5)
    {
        new_stk_size = stack->size / 2;

        while (stack->size != new_stk_size)
        {
            Pop(stack, &buffer);
        }

        new_stk_size = stack->size / 2;

        for (int i = 0; i < new_stk_size; i++)
        {
            buffer = rand();
            Push(stack, &buffer);
        }
    }

    clock_t time_end  = clock();

    double time = (double) (time_end - time_start) / CLOCKS_PER_SEC;

    printf("Test1: %f\n", time * 1e3);
}

void Test2(struct Stack* const stack)
{
    assert((stack != NULL) && "Pointer to \"stack\" is not NULL!!!");

    size_t new_stk_size = 0;
    stk_elem_t buffer = 0;

    clock_t time_start = clock();

    for (int i = 0; i < 1e6; i++)
    {
        buffer = rand();
        Push(stack, &buffer);
    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 1e4; j++)
        {
            Pop(stack, &buffer);
        }

        for (int j = 0; j < 1e4; j++)
        {
            Push(stack, &buffer);
        }
    }

    while (stack->size >= 1e5)
    {
        new_stk_size = stack->size / 2;

        while (stack->size != new_stk_size)
        {
            Pop(stack, &buffer);
        }

        new_stk_size = stack->size / 2;

        for (int i = 0; i < new_stk_size; i++)
        {
            buffer = rand();
            Push(stack, &buffer);
        }
    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 1e4; j++)
        {
            Pop(stack, &buffer);
        }

        for (int j = 0; j < 1e4; j++)
        {
            Push(stack, &buffer);
        }
    }

    clock_t time_end = clock();

    double time = (double) (time_end - time_start )/ CLOCKS_PER_SEC;

    printf("Test2: %f\n", time * 1e3);
}

void Test3(struct Stack* const stack)
{
    assert((stack != NULL) && "Pointer to \"stack\" is not NULL!!!");

    stk_elem_t buffer = 0;
    int operation = 0;     

    for (int i = 0; i < 1e6; i++)
    {
        buffer = rand();
        Push(stack, &buffer);
    }  

    clock_t time_start = clock();

    for (int i = 0; i < 1e6; i++)
    {
        buffer = rand();
        operation = 1 + rand() % 2;

        switch(operation)
        {
            case 1:
            {
                Push(stack, &buffer);
                break;
            }

            case 2:
            {
                Pop(stack, &buffer);
                break;
            }

            default:
                break;
        }
    }

    clock_t time_end = clock();

    double time = (double) (time_end - time_start )/ CLOCKS_PER_SEC;

    printf("Test3: %f\n", time * 1e3);
}

void Test4(struct Stack* const stack)
{
    assert((stack != NULL) && "Pointer to \"stack\" is not NULL!!!");

    FILE* results_output = fopen("da_graphic_points.txt", "w");

    clock_t time_start  = clock();
    clock_t time_end    = clock();

    double time = 0;

    stk_elem_t  buffer = 0;


    for (int n = 1e3; n <= 1e6; n += 1e3)
    {
        for (int j = 0; j <=1e3; j++)
        {
            buffer = rand();
            Push(stack, &buffer);
        }

        time_end = clock();
        time = (double) (time_end - time_start) / CLOCKS_PER_SEC;

        fprintf(results_output, "%d; %f\n", n, time * 1e3);
    }

    fclose(results_output);
}

int main()
{
    struct Stack* stack = StackCtor(START_CAPACITY);

    Test1(stack);
    stack = StackClear(stack);

    Test2(stack);
    stack = StackClear(stack);

    Test3(stack);
    stack = StackClear(stack);

    Test4(stack);

    stack = StackDtor(stack);

    return 0;
}
