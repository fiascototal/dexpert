#include <stdlib.h>
#include <stdio.h>
#include <dexpert/dxp_rbtree.h>
#include <dexpert/error_codes.h>


/*
Every node is either red or black.
Every leaf (NULL) is black.
If a node is red, then both its children are black.
Every simple path from a node to a descendant leaf contains the same number of black nodes. 
*/

enum e_rbtree_color
{
    RED,
    BLACK,
};

struct s_rbtree
{
    struct s_rbtree_node *root;
    uint32_t              size;
    f_rbtree_cmp          cmp_fct;
};

struct s_rbtree_node
{
    struct s_rbtree_node *left;
    struct s_rbtree_node *right;
    struct s_rbtree_node *father;

    void                 *data;
    enum e_rbtree_color   color;
};

struct s_rbtree_iterator
{
    struct s_rbtree      *tree;
    struct s_rbtree_node *current;
};


// create a new RBTREE object. Don't forget to add the fct to compare 2 nodes
dxp_rbtree dxp_rbtree_new(f_rbtree_cmp cmp_fct)
{
    struct s_rbtree *result = NULL;

    result = (struct s_rbtree *)malloc(sizeof (struct s_rbtree));
    result->cmp_fct = cmp_fct;
    result->root = NULL;
    result->size = 0;

    return ((dxp_rbtree)result);
}

static void rec_delete_node(struct s_rbtree_node *cur_node)
{
    if (cur_node)
    {
        if (cur_node->left)
            rec_delete_node(cur_node->left);
        if (cur_node->right)
            rec_delete_node(cur_node->right);
        if (cur_node->data)
        {
            free(cur_node->data);
            cur_node->data = NULL;
        }
        cur_node->left = NULL;
        cur_node->right = NULL;
        cur_node->father = NULL;
        free(cur_node);
        cur_node = NULL;
    }
}

// delete the given rbtree (and all nodes)
int dxp_rbtree_delete(dxp_rbtree t)
{
    struct s_rbtree *tree = (struct s_rbtree *)t;

    if (tree == NULL)
        return (ERR_INVALID_ARG);

    rec_delete_node(tree->root);
    tree->root = NULL;
    tree->cmp_fct = NULL;
    tree->size = 0;
    free(tree);
    tree = NULL;

    return (ERR_SUCCESS);
}

// create a new node
static struct s_rbtree_node *_create_node(void *data)
{
    struct s_rbtree_node *result = NULL;

    result = (struct s_rbtree_node *)malloc(sizeof (struct s_rbtree_node));
    result->data = data;
    result->left = NULL;
    result->right = NULL;
    result->father = NULL;
    result->color = RED;

    return (result);
}

static void _insert_rec(struct s_rbtree_node *root, struct s_rbtree_node *new_node, f_rbtree_cmp cmp_fct)
{
    if (root != NULL)
    {
        if (cmp_fct(root->data, new_node->data) > 0)
        {
            if (root->left != NULL)
            {
                _insert_rec(root->left, new_node, cmp_fct);
                return;
            }
            root->left = new_node;
        }
        else
        {
            if (root->right != NULL)
            {
                _insert_rec(root->right, new_node, cmp_fct);
                return;
            }
            root->right = new_node;
        }
    }
    new_node->father = root;
}

static int _rotate_left(struct s_rbtree_node *x)
{
    struct s_rbtree_node *y = NULL;

    y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->father = x;

    y->father = x->father;

    if (x->father)
    {
        if (x == x->father->left)
            x->father->left = y;
        else
            x->father->right = y;
    }
    
    y->left = x;
    x->father = y;

    return (0);
}

static int _rotate_right(struct s_rbtree_node *x)
{
    struct s_rbtree_node *y = NULL;

    y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->father = x;

    y->father = x->father;

    if (x->father)
    {
        if (x == x->father->right)
            x->father->right = y;
        else
            x->father->left = y;
    }
    
    y->right = x;
    x->father = y;

    return (0);
}

static struct s_rbtree_node *_grand_father(struct s_rbtree_node *n)
{
    if (n->father == NULL)
        return (NULL);
    return (n->father->father);
}

static struct s_rbtree_node *_brother(struct s_rbtree_node *n)
{
    struct s_rbtree_node *father = n->father;

    if (father == NULL)
        return (NULL);
    if (n == father->left)
        return (father->right);
    else
        return (father->left);
}

static struct s_rbtree_node *_uncle(struct s_rbtree_node *n)
{
    struct s_rbtree_node *father = n->father;

    if (father == NULL)
        return (NULL);
    return (_brother(father));
}

static void _fix_rbtree(struct s_rbtree_node *n)
{
    struct s_rbtree_node *u = NULL,
                         *p = NULL,
                         *g = NULL;

    if (n->father == NULL)
    {
        // no father means root! so the color of the node is black
        n->color = BLACK;
    }
    else if (n->father->color == BLACK)
    {
        /* everything is ok in this case */
    }
    else
    {   
        // so we have a father RED, so there is a problem. The rule says that we can't have 2 consecutive RED nodes

        u = _uncle(n);
        if (u != NULL && u->color == RED)
        {
            n->father->color = BLACK;
            u->color = BLACK;
            g = _grand_father(n);
            g->color = RED;

            _fix_rbtree(g);
        }
        else
        {
            p = n->father;
            g = _grand_father(n);

            if (g->left && n == g->left->right)
            {
                _rotate_left(p);
                n = n->left;
            }
            else if (g->right && n == g->right->left)
            {
                _rotate_right(p);
                n = n->right;
            }

            p = n->father;
            g = _grand_father(n);

            if (n == p->left)
                _rotate_right(g);
            else
                _rotate_left(g);
            
            p->color = BLACK;
            g->color = RED;
        }
    }
}

// add a new element
int dxp_rbtree_insert(dxp_rbtree t, void *data)
{
    struct s_rbtree      *tree     = (struct s_rbtree *)t;
    struct s_rbtree_node *new_node = NULL;

    if (tree == NULL || data == NULL)
        return (ERR_INVALID_ARG);

    if (tree->root == NULL)
    {
        tree->root = _create_node(data);
        tree->root->color = BLACK;
        tree->size = 1;
        return (ERR_SUCCESS);
    }

    new_node = _create_node(data);
    _insert_rec(tree->root, new_node, tree->cmp_fct);
    _fix_rbtree(new_node);

    // update root
    tree->root = new_node;
    while (tree->root->father != NULL)
        tree->root = tree->root->father;

    return (ERR_SUCCESS);
}

// return the size of the rbtree
uint32_t dxp_rbtree_length(dxp_rbtree t)
{
    struct s_rbtree *tree = (struct s_rbtree *)t;
    return (tree->size);
}

//
// Iterator stuff
//

// return a new iterator
dxp_rbtree_iterator dxp_rbtree_begin(dxp_rbtree t)
{
    struct s_rbtree *tree = (struct s_rbtree *)t;
    struct s_rbtree_iterator *result = NULL;

    result = (struct s_rbtree_iterator *)malloc(sizeof (struct s_rbtree_iterator));
    result->tree = (struct s_rbtree *)t;
    result->current = tree->root;

    if (result->current == NULL)
        return result;

    while (result->current->left)
        result->current = result->current->left;
    
    return (result);
}

// return 1 if the iterator is at the end of the rbtree
int dxp_rbtree_end(dxp_rbtree_iterator it)
{
    struct s_rbtree_iterator *_it = (struct s_rbtree_iterator *)it;
    if (_it->current == NULL)
    {
        _it->tree = NULL;
        free(_it); _it = NULL;
        return (1);
    }
    return (0);
}

// move the iterator to the next item
int dxp_rbtree_next(dxp_rbtree_iterator it)
{
    struct s_rbtree_iterator *_it = (struct s_rbtree_iterator *)it;

    if (_it == NULL)
        return (ERR_INVALID_ARG);
    if (_it->current == NULL)
        return (ERR_ITEM_NOT_FOUND);

    if (_it->current->right != NULL)
    {
        _it->current = _it->current->right;
        while (_it->current->left)
            _it->current = _it->current->left;
    }
    else
    {
        // no right node, so we go up in the tree
        // we just take care: we go up only to climb the tree from the right
        while (_it->current->father != NULL &&
               _it->current ==_it->current->father->right)
            _it->current = _it->current->father;
        _it->current = _it->current->father;
    }
        
    return (ERR_SUCCESS);
}

// return the element of the current position of the given iterator
void *dxp_rbtree_data(dxp_rbtree_iterator it)
{
    struct s_rbtree_iterator *_it = (struct s_rbtree_iterator *)it;
    if (_it == NULL || _it->current == NULL)
        return (NULL);
    return (_it->current->data);
}

// search if the given item is present in the rbtree. Return an iterator if found, NULL else.
dxp_rbtree_iterator dxp_rbtree_find(dxp_rbtree t, void *data)
{
    struct s_rbtree *tree     = (struct s_rbtree *)t;
    void            *cur_data = NULL;

    for (
        dxp_rbtree_iterator it = dxp_rbtree_begin(t);
        dxp_rbtree_end(it) != 1;
        dxp_rbtree_next(it))
    {
        cur_data = dxp_rbtree_data(it);
        if (cur_data)
        {
            if (tree->cmp_fct(cur_data, data) == 0)
                return (it);
        }
    }

    return (NULL);
}


static void _dxp_rbtree_print_rec(struct s_rbtree_node *cur_node, f_rbtree_print_node printer)
{
    
    if (cur_node->left)
    {
        printf("    %d -> %d\n", (unsigned int)cur_node, (unsigned int)cur_node->left);
        _dxp_rbtree_print_rec(cur_node->left, printer);
    }
    if (cur_node->right)
    {
        printf("    %d -> %d\n", (unsigned int)cur_node, (unsigned int)cur_node->right);
        _dxp_rbtree_print_rec(cur_node->right, printer);
    }
    printf("    %d [color=%s, label=\"", (unsigned int)cur_node, (cur_node->color == RED) ? "red": "black");
    printer(cur_node->data);
    printf("\"];\n");
}

void dxp_rbtree_print(dxp_rbtree t, f_rbtree_print_node printer, const char *tree_name)
{
    struct s_rbtree *tree = (struct s_rbtree *)t;

    printf("digraph %s {\n", tree_name);
    _dxp_rbtree_print_rec(tree->root, printer);
    printf("}\n");
}
