#include "quick_sort_partition.h"

int main()
{
    const char* dir_path = TEST_MOST_DUBLICATES_PATH;
    size_t from = 0;
    size_t to   = 1000000;
    size_t step = 10000;

    size_t number_of_repetitions = 1;

    //Create time files on big_tests
    FILE* time_list = fopen("TimeFiles/lomuto_partition_time_no_dub.csv", "w");
    TestCorrectnessOfSortings(dir_path, from, to, step, time_list, number_of_repetitions, QuickSortWithLomutoPartition);
    fclose(time_list);

    time_list = fopen("TimeFiles/hoar_partition_1_time_no_dub.csv", "w");
    TestCorrectnessOfSortings(dir_path, from, to, step, time_list, number_of_repetitions, QuickSortWithHoarPartitionOneBranch);
    fclose(time_list);

    time_list = fopen("TimeFiles/hoar_partition_2_time_no_dub.csv", "w");
    TestCorrectnessOfSortings(dir_path, from, to, step, time_list, number_of_repetitions, QuickSortWithHoarPartitionTwoBranches);
    fclose(time_list);

    time_list = fopen("TimeFiles/flag_partition_time_no_dub.csv", "w");
    TestCorrectnessOfSortings(dir_path, from, to, step, time_list, number_of_repetitions, QuickSortWithFlagPartition);
    fclose(time_list);

    //Create time files on test_most_dublicates
    time_list = fopen("TimeFiles/lomuto_partition_time_dub.csv", "w");
    TestCorrectnessOfSortings(dir_path, from, to, step, time_list, number_of_repetitions, QuickSortWithLomutoPartition);
    fclose(time_list);

    time_list = fopen("TimeFiles/hoar_partition_1_time_dub.csv", "w");
    TestCorrectnessOfSortings(dir_path, from, to, step, time_list, number_of_repetitions, QuickSortWithHoarPartitionOneBranch);
    fclose(time_list);

    time_list = fopen("TimeFiles/hoar_partition_2_time_dub.csv", "w");
    TestCorrectnessOfSortings(dir_path, from, to, step, time_list, number_of_repetitions, QuickSortWithHoarPartitionTwoBranches);
    fclose(time_list);

    time_list = fopen("TimeFiles/flag_partition_time_dub.csv", "w");
    TestCorrectnessOfSortings(dir_path, from, to, step, time_list, number_of_repetitions, QuickSortWithFlagPartition);
    fclose(time_list);

    return 0;
}

FILE* OpenFile(const char* const dir_path, const size_t cur_size, const size_t k, const char* const extension)
{
    assert((dir_path != NULL) && "Pointer to \'dir_path\' is NULL!!!\n");

    char* file_name = (char*) calloc(128, sizeof(char));
    assert((file_name != NULL) && "Program can not allocate memory!!\n");

    strncpy(file_name, dir_path, strlen(dir_path));

    sprintf(file_name + strlen(file_name), "%ld_%ld", cur_size, k);   

    strncat(file_name, extension, strlen(extension));

    FILE* file = fopen(file_name, "rb+");

    assert((file != NULL) && "pointer to \'file\' is NULL!!!\n");

    return file;
}

void TestCorrectnessOfSortings(const char* const dir_path, const size_t from, const size_t to, 
                               const size_t step, FILE* time_list, size_t number_of_repetitions,
                               void (*sort_function) (int* const array, const size_t array_size))
{
    assert((dir_path      != NULL) && "Pointer to string \'dir_path\' is NULL!!!\n");
    assert((sort_function != NULL) && "Pointer to function \'sort_function\' is NULL!!!\n");

    size_t number_of_tests = (to - from) / step + 1;
    size_t index = 0;

    int* array = (int*) calloc(to, sizeof(int));
    assert((array != NULL) && "Program can not allocate memory!\n");

    GraphicPoint* time_array = (GraphicPoint*) calloc(number_of_tests, sizeof(GraphicPoint));
    assert((time_array != NULL) && "Program can not allocate memory!\n");

    for (size_t cur_size = from; cur_size <= to; cur_size += step)
    {
        for (size_t k = 0; k < number_of_repetitions; k++)
        {
            FILE* input  = OpenFile(dir_path, cur_size, k, ".in");
            FILE* output = OpenFile(dir_path, cur_size, k, ".out");

            for (size_t i = 0; i < cur_size; i++)
            {
                if (fscanf(input, "%d", &(array[i])) == 0)
                {
                    assert(FALSE && "Program cannot read from file the number!!!\n");
                }
            }

            double time = 0;
            clock_t time_start = clock();
            sort_function(array, cur_size);
            clock_t time_end = clock();

            time = (double)(time_end - time_start) / (CLOCKS_PER_SEC / 1000000);

            int elem = 0;

            for (size_t i = 0; i < cur_size; i++)
            {
                if (fscanf(output, "%d", &elem) == 0)
                {
                    assert(FALSE && "Program can not read from file the number!!!\n");
                }

                assert((elem == array[i]) && "Wrong sort function!!!\n");
            }

            time_array[index].time += time;
            time_array[index].size += cur_size;
        }

        time_array[index].time /= (double) number_of_repetitions;
        time_array[index].size /= (double) number_of_repetitions;

        fprintf(time_list, "%ld; %lf\n", time_array[index].size, time_array[index].time);

        index++;
    }

    free(array);
    free(time_array);
}