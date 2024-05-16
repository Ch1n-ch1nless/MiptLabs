#include "segment_tree.h"

void ReadArguments(int argc, const char** argv, const char** file_with_numbers, const char** file_with_requests)
{
    assert((argc == 3)                   && "ERROR!!! Invalid value of \'argc\'!\n");
    assert((argv != NULL)                && "ERROR!!! Invalid value of \'argv\'!\n");
    assert((file_with_numbers  != NULL)  && "ERROR!!! Invalid value of \'file_with_numbers\'!\n");
    assert((file_with_requests != NULL)  && "ERROR!!! Invalid value of \'file_with_requests\'!\n");

    *file_with_numbers  = argv[1];
    *file_with_requests = argv[2];
}

//----------------------------------------------

SegmentTree* SegmentTreeCtor(size_t init_size, int* array)
{
    SegmentTree* seg_tree = (SegmentTree*) calloc(1, sizeof(SegmentTree));
    assert((seg_tree != NULL) && "ERROR!!! Program can not allocate memory!\n");

    seg_tree->size   = 1;

    while (seg_tree->size < init_size)
    {
        seg_tree->size  *= 2;
    }
    
    seg_tree->data  = (int*) calloc(seg_tree->size * 2, sizeof(int));
    assert((seg_tree->data != NULL) && "ERROR!!! Program can not allocate memory!\n");

    for (size_t i = 0; i < init_size; i++)
    {
        seg_tree->data[i+seg_tree->size] = array[i];
    }

    for (size_t i = seg_tree->size - 1; i > 0; i--)
    {
        seg_tree->data[i] = seg_tree->data[i*2] + seg_tree->data[i*2+1];
    }

    return seg_tree;
}

void SegmentTreeDtor(SegmentTree* seg_tree)
{
    assert((seg_tree != NULL) && "ERROR!!! Pointer to \'seg_tree\' is NULL!\n");

    for (size_t i = 0; i < 2 * seg_tree->size; i++)
    {
        seg_tree->data[i] = 0;
    }

    free(seg_tree->data);

    seg_tree->size  = 0;
    seg_tree->data  = NULL;

    free(seg_tree);
}

void SegmentTreeUpdate(SegmentTree* seg_tree, int index, int new_value)
{
    assert((seg_tree != NULL) && "ERROR!!! Pointer to \'seg_tree\' is NULL!\n");

    int cur_pose = index + seg_tree->size;

    seg_tree->data[cur_pose] = new_value;

    do 
    {
        cur_pose                    /= 2;
        seg_tree->data[cur_pose]     = seg_tree->data[cur_pose * 2] + seg_tree->data[cur_pose * 2 + 1];
    }
    while (cur_pose > 0);
}

static int _RecursiveSegmentTreeFindSum(SegmentTree* seg_tree, int arr_left, int arr_right, int node,  int tree_left, int tree_right)
{
    if (tree_right < arr_left || tree_left  >  arr_right) return 0;
    if (arr_left <= tree_left && tree_right <= arr_right) return seg_tree->data[node];

    int med = tree_left + (tree_right - tree_left) / 2;
    return  _RecursiveSegmentTreeFindSum(seg_tree, arr_left, arr_right, node * 2,     tree_left, med       ) + 
            _RecursiveSegmentTreeFindSum(seg_tree, arr_left, arr_right, node * 2 + 1, med + 1,   tree_right);
}

int SegmentTreeFindSum(SegmentTree* seg_tree, int left, int right)
{
    assert((seg_tree != NULL) && "ERROR!!! Pointer to \'seg_tree\' is NULL!\n");

    return _RecursiveSegmentTreeFindSum(seg_tree, left, right, 1, 0, seg_tree->size - 1);
}

//----------------------------------------------

int* ReadArrayWithNumbers(const char* const filename, size_t number_of_elements)
{
    assert((filename            != NULL) && "ERROR!!! Pointer to \'filename\' is NULL!\n");
    assert((number_of_elements  != 0)    && "ERROR!!! Invalid value of \'number_of_elements\'!\n");

    FILE* input = fopen(filename, "r");
    assert((input != NULL) && "ERROR!!! Program can not open file!\n");

    int* array = (int*) calloc(number_of_elements, sizeof(int));

    for (size_t i = 0; i < number_of_elements; i++)
    {
        if (fscanf(input, "%d", array + i) == 0)
        {
            assert(false && "ERROR!!! Program can not read the number!\n");
        }
    }

    return array;
}

Request* ReadArrayWithRequests(const char* const filename, size_t number_of_elements)
{
    assert((filename            != NULL) && "ERROR!!! Pointer to \'filename\' is NULL!\n");
    assert((number_of_elements  != 0)    && "ERROR!!! Invalid value of \'number_of_elements\'!\n");

    FILE* input = fopen(filename, "r");
    assert((input != NULL) && "ERROR!!! Program can not open file!\n");

    Request* array = (Request*) calloc(number_of_elements, sizeof(Request));

    for (size_t i = 0; i < number_of_elements; i++)
    {
        if (fscanf(input, "%d %d", &(array [i].left), &(array[i].right)) == 0)
        {
            assert(false && "ERROR!!! Program can not read the number!\n");
        }
    }

    return array;
}

//----------------------------------------------

double MeasureTimeOfRequests(SegmentTree* seg_tree, Request* request_array, size_t number_of_requests)
{
    assert((seg_tree        != NULL) && "ERROR!!! Pointer to \'segment_tree\' is NULL!\n");
    assert((request_array       != NULL) && "ERROR!!! Pointer to \'request_array\' is NULL!\n");
    assert((number_of_requests  != 0)    && "ERROR!!! Invalid value of \'number_of_requests\'!\n");

    double time = 0.0;

    int answer = 0;

    clock_t time_begin  = clock();

    for (size_t i = 0; i < number_of_requests; i++)
    {
        answer = SegmentTreeFindSum(seg_tree, request_array[i].left, request_array[i].right);

    }
    
    clock_t time_end    = clock();

    time = (double)(time_end - time_begin) / ((double) CLOCKS_PER_SEC / 1e3);

    return time;
}