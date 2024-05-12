#include "treap.h"

static void     ReadArguments(int argc, const char** argv, const char** input_file, int* number_of_elems);
static int      TranslateStringToNumber(const char* string);

static double   InsertElements(Treap* treap, int* array_of_elems, int number_of_elems);
static double   DeleteElements(Treap* treap, int* array_of_elems, int number_of_elems);

int main(int argc, const char* argv[])
{
    const char* input_file      = NULL;
    int         number_of_elems = 0;

    ReadArguments(argc, argv, &input_file, &number_of_elems);

    //Create array of elements
    int* array_of_elems = (int*) calloc(number_of_elems, sizeof(int));
    assert((array_of_elems != NULL) && "ERROR!!! Program can not allocate memory!\n");

    //Open file to read the elements
    FILE* input = fopen(input_file, "r");
    assert((input != NULL) && "ERROR!!! Program can not open the file!\n");

    //Read elemets
    for (int i = 0; i < number_of_elems; i++)
    {
        fscanf(input, "%d", array_of_elems + i);
    }

    Treap* treap = TreapCtor();

    double time = InsertElements(treap, array_of_elems, number_of_elems);

    printf("%d, %lg\n", number_of_elems, time);

    time = DeleteElements(treap, array_of_elems, number_of_elems / 2);

    printf("%d, %lg\n", number_of_elems / 2, time);

    free(array_of_elems);
    TreapDtor(treap);

    return 0;
}

static void ReadArguments(int argc, const char** argv, const char** input_file, int* number_of_elems)
{
    assert((argc == 3)      && "ERROR!!! You have put incorrect number of arguments!\n");
    assert((argv != NULL)   && "ERROR!!! Pointer to \"argv\" is NULL!!!\n");

    *number_of_elems    = TranslateStringToNumber(argv[1]);

    *input_file         = argv[2];

    return;
}

static int TranslateStringToNumber(const char* string)
{
    assert((string != NULL) && "ERROR!!! Pointer to \"string\" is NULL!!!\n");

    int index = 0;
    int number = 0;

    while (string[index] != '\0')
    {
        assert(('0' <= string[index] && string[index] <= '9') && "ERROR!!! Program has got not number!!!\n");

        number *= 10;
        number += string[index] - '0';

        index++;
    }

    return number;
}

static double DeleteElements(Treap* treap, int* array_of_elems, int number_of_elems)
{
    double time = 0;

    clock_t time_start  = 0;
    clock_t time_end    = 0;

    for (int j = 0; j < 5; j++)
    {
        time_start  = clock();

        for (int i = 0; i < number_of_elems; i++)
        {
            TreapDelete(treap, array_of_elems[i]);
        }

        time_end    = clock();

        for (int i = 0; i < number_of_elems; i++)
        {
            TreapInsert(treap, array_of_elems[i]);
        }

        time += ((double)(time_end - time_start)) / (CLOCKS_PER_SEC / 1000.0);
    }

    time = time / 5.0;

    return time;
}

static double InsertElements(Treap* treap, int* array_of_elems, int number_of_elems)
{
    assert((treap != NULL) && "ERROR!!! Pointer to \'treap\' is NULL!\n");

    double time = 0;

    clock_t time_start  = 0;
    clock_t time_end    = 0;

    for (int j = 0; j < 5; j++)
    {
        TreapClear(treap);

        time_start  = clock();

        for (int i = 0; i < number_of_elems; i++)
        {
            TreapInsert(treap, array_of_elems[i]);
        }

        time_end    = clock();

        time += ((double)(time_end - time_start)) / (CLOCKS_PER_SEC / 1000.0);
    }

    time = time / 5.0;

    return time;
}