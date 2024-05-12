#include "splay_tree.h"

static void     ReadArguments(int argc, const char** argv, const char** input_file, int* number_of_elems);
static int      TranslateStringToNumber(const char* string);

static double   InsertElements(SplayTree* splay_tree, int* array_of_elems, int number_of_elems);
static double   DeleteElements(SplayTree* splay_tree, int* array_of_elems, int number_of_elems);

static void NodeGraphDump(Node* node, FILE* dot_file)
{
    if (node == NULL)
    {
        return;
    }

    fprintf(dot_file, "\tnode_%p[label = \"%d\"];\n", node, node->key);

    NodeGraphDump(node->left_child,  dot_file);

    NodeGraphDump(node->right_child, dot_file);
}

static void EdgeGraphDump(Node* node, FILE* dot_file)
{
    if (node->left_child != NULL)
    {
        fprintf(dot_file, "node_%p -> node_%p [color = \"#00FF41\", label = \"L\"];\n",
                           node, node->left_child);

        fprintf(dot_file, "node_%p -> node_%p [color = \"#4100FF\", label = \"P\"];\n",
                           node->left_child, node->left_child->parent);

        EdgeGraphDump(node->left_child, dot_file);
    }

    if (node->right_child != NULL)
    {
        fprintf(dot_file, "node_%p -> node_%p [color = \"#FF4001\", label = \"R\"];\n",
                           node, node->right_child);

        fprintf(dot_file, "node_%p -> node_%p [color = \"#4100FF\", label = \"P\"];\n",
                           node->right_child, node->right_child->parent);

        EdgeGraphDump(node->right_child, dot_file);
    }

}

void Dump(SplayTree* splay_tree)
{
    assert((splay_tree != NULL) && "Pointer to tree is NULL!!!\n");

    FILE* dot_file = NULL;

    dot_file = fopen("tree.dot", "w");

    //========================================================================================

    fprintf(dot_file, "digraph G\n"
                      "{\n"
                      "\tgraph [dpi = 100];\n\n"
                      "\trankdir = TB;\n\n"
                      "\tedge[minlen = 3, arrowsize = 2, penwidth = 1.5];\n"
                      "\tnode[shape = Mrecord, style = \"rounded, filled\", "
                      "fillcolor = \"yellow\", fontsize = 20, "
                      "penwidth = 3];\n\n");

    //========================================================================================

    NodeGraphDump(splay_tree->root, dot_file);
    fprintf(dot_file, "\n");

    EdgeGraphDump(splay_tree->root, dot_file);
    fprintf(dot_file, "\n");

    //========================================================================================

    fprintf(dot_file, "}\n");

    fclose(dot_file);

    system("dot tree.dot -T png -o tree.png");
}

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

    SplayTree* splay_tree = SplayTreeCtor();

    double time = InsertElements(splay_tree, array_of_elems, number_of_elems);

    printf("%d, %lg\n", number_of_elems, time);

    time = DeleteElements(splay_tree, array_of_elems, number_of_elems / 2);

    printf("%d, %lg\n", number_of_elems / 2, time);

    free(array_of_elems);
    SplayTreeDtor(splay_tree);

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

static double DeleteElements(SplayTree* splay_tree, int* array_of_elems, int number_of_elems)
{
    double time = 0;

    clock_t time_start  = 0;
    clock_t time_end    = 0;

    for (int j = 0; j < 5; j++)
    {
        time_start  = clock();

        for (int i = 0; i < number_of_elems; i++)
        {
            SplayTreeDelete(splay_tree, array_of_elems[i]);
        }

        time_end    = clock();

        for (int i = 0; i < number_of_elems; i++)
        {
            SplayTreeInsert(splay_tree, array_of_elems[i]);
        }

        time += ((double)(time_end - time_start)) / (CLOCKS_PER_SEC / 1000.0);
    }

    time = time / 5.0;

    return time;
}

static double InsertElements(SplayTree* splay_tree, int* array_of_elems, int number_of_elems)
{
    assert((splay_tree != NULL) && "ERROR!!! Pointer to \'SplayTree\' is NULL!\n");

    double time = 0;

    clock_t time_start  = 0;
    clock_t time_end    = 0;

    for (int j = 0; j < 5; j++)
    {
        SplayTreeClear(splay_tree);

        time_start  = clock();

        for (int i = 0; i < number_of_elems; i++)
        {
            SplayTreeInsert(splay_tree, array_of_elems[i]);
        }

        time_end    = clock();

        time += ((double)(time_end - time_start)) / (CLOCKS_PER_SEC / 1000.0);
    }

    time = time / 5.0;

    return time;
}