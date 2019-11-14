#include <stdio.h>
#include <stdlib.h>
#include <dexpert/dxp_rbtree.h>


int int_cmp(void *a, void *b)
{
    int aa = *(int *)a;
    int bb = *(int *)b;
    return (aa - bb);
}

void insert_int(int val, dxp_rbtree tree)
{
    int *pval = (int *)malloc(sizeof (int));
    *pval = val;
    dxp_rbtree_insert(tree, pval);
}

void print_int_node(void *data)
{
    int *pval = (int *)data;
    printf("%d", *pval);
}

int main(void)
{
    dxp_rbtree tree;

    tree = dxp_rbtree_new(int_cmp);
    insert_int(10, tree);
    insert_int(20, tree);
    insert_int(50, tree);
    insert_int(5, tree);
    insert_int(6, tree);
    insert_int(30, tree);
    insert_int(100, tree);
    insert_int(99, tree);
    insert_int(31, tree);
    insert_int(101, tree);
    insert_int(102, tree);
    insert_int(2, tree);
    insert_int(1, tree);
    insert_int(3, tree);

    dxp_rbtree_print(tree, print_int_node, "test_RBtree");
    dxp_rbtree_delete(tree);

    return (0);
}
