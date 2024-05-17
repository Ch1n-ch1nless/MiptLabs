#include "avl_tree.h"

static Node* NodeCtor(int key)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));
    assert((new_node != NULL) && "ERROR!!! Program can not allocate memory!\n");

    new_node->key       = key;
    new_node->height    = 1;
    new_node->left      = NULL;
    new_node->right     = NULL;

    return new_node;
}

static void NodeDtor(Node* node)
{
    assert((node != NULL) && "ERROR!!! Pointer to \'node\' is NULL!\n");

    node->key       = 0;
    node->height    = 0;
    node->left      = NULL;
    node->right     = NULL;

    free(node);
}

static size_t Height(Node* node)
{
    return (node == NULL) ? 0 : node->height;
}

static void FixHeight(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    
    node->height = MAX(Height(node->left), Height(node->right));
    node->height = node->height + 1;
}

static int CalculateBalance(Node* node)
{
    if (node == NULL)
    {
        return 0;
    }

    return Height(node->right) - Height(node->left);
}

static Node* RotateLeft(Node* parent)
{
    Node* right_child   = parent->right;
    parent->right       = right_child->left;
    right_child->left   = parent;
    FixHeight(parent);
    FixHeight(right_child);
    return right_child;
}

static Node* RotateRight(Node* parent)
{
    Node* left_child    = parent->left;
    parent->left        = left_child->right;
    left_child->right   = parent;
    FixHeight(parent);
    FixHeight(left_child);
    return left_child;
}

static Node* FixBalanceInSubTree(Node* subtree_root)
{
    FixHeight(subtree_root);

    if (CalculateBalance(subtree_root) == 2)
    {
        if (CalculateBalance(subtree_root->right) < 0)
        {
            subtree_root->right = RotateRight(subtree_root->right);
        }
        return RotateLeft(subtree_root);
    }
    else if (CalculateBalance(subtree_root) == -2)
    {
        if (CalculateBalance(subtree_root->left) > 0) {
          subtree_root->left = RotateLeft(subtree_root->left);
        }
        return RotateRight(subtree_root);
    }

    return subtree_root;
}

static Node* SubTreeSearch(Node* root, int key)
{
    while (root != NULL)
    {
        if (root->key > key)
        {
            root = root->left;
        }
        else if (root->key < key)
        {
            root = root->right;
        }
        else
        {
            break;
        }
    }
    
    return root;
}

static Node* SubTreeInsert(Node* root, int key)
{
    if (root == NULL)
    {
        return NodeCtor(key);
    }

    if (root->key >= key)
    {
        root->left  = SubTreeInsert(root->left, key);
    }
    else
    {
        root->right = SubTreeInsert(root->right, key);
    }

    return FixBalanceInSubTree(root);
}

static Node* FindMinKeyInSubTree(Node* root)
{
    assert((root != NULL) && "ERROR Invalid value of root\n");

    while (root->left != NULL)
    {
        root = root->left;
    }

    return root;
}

static Node* UnlinkMinKeyInSubTree(Node* root)
{
    if (root->left == NULL)
    {
        return root->right;
    }

    root->left = UnlinkMinKeyInSubTree(root->left);

    return FixBalanceInSubTree(root);
}

static Node* SubTreeDelete(Node* root, int key)
{
    if (root == NULL) return NULL;

    if (root->key > key)
    {
        root->left  = SubTreeDelete(root->left, key);
    }
    else if (root->key < key)
    {
        root->right = SubTreeDelete(root->right, key);
    }
    else
    {
        Node* left  = root->left;
        Node* right = root->right;

        NodeDtor(root);

        if (right == NULL)
        {
            return left;
        }
        else
        {
            Node* min_right     = FindMinKeyInSubTree(right);
            min_right->right    = UnlinkMinKeyInSubTree(right);
            min_right->left     = left;

            return FixBalanceInSubTree(min_right);
        }
    }

    return FixBalanceInSubTree(root);
}

static void SubTreeDtor(Node* root)
{
    if (root == NULL) return;

    SubTreeDtor(root->left);
    SubTreeDtor(root->right);

    NodeDtor(root);
}

AVLTree* AVLTreeCtor(void)
{
    AVLTree* avl_tree = (AVLTree*) calloc(1, sizeof(AVLTree));
    assert((avl_tree != NULL) && "ERROR!!! Program can not allocate memory!\n");

    avl_tree->root  = NULL;
    avl_tree->size  = 0;

    return avl_tree;
}

void AVLTreeClear(AVLTree* avl_tree)
{
    assert((avl_tree != NULL) && "ERROR!!! Pointer to \'avl_tree\' is NULL!\n");

    SubTreeDtor(avl_tree->root);

    avl_tree->root  = NULL;
    avl_tree->size  = 0;
}

void AVLTreeDtor(AVLTree* avl_tree)
{
    assert((avl_tree != NULL) && "ERROR!!! Pointer to \'avl_tree\' is NULL!\n");

    SubTreeDtor(avl_tree->root);

    avl_tree->root  = NULL;
    avl_tree->size  = 0;

    free(avl_tree);
}

bool AVLTreeSearch(AVLTree* avl_tree, int key)
{
    assert((avl_tree != NULL) && "ERROR!!! Pointer to \'avl_tree\' is NULL!\n");

    return (SubTreeSearch(avl_tree->root, key) != NULL) ? true : false; 
}

void AVLTreeInsert(AVLTree* avl_tree, int key)
{
    assert((avl_tree != NULL) && "ERROR!!! Pointer to \'avl_tree\' is NULL!\n");

    avl_tree->root  = SubTreeInsert(avl_tree->root, key);
}

void AVLTreeDelete(AVLTree* avl_tree, int key)
{
    assert((avl_tree != NULL) && "ERROR!!! Pointer to \'avl_tree\' is NULL!\n");

    avl_tree->root  = SubTreeDelete(avl_tree->root, key);
}