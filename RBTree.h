#ifndef RBTREE_H
#define RBTREE_H

/* A macro Definition for the understanding of color RED */
#define RED 255
/* A macro Definition for the understanding of color BLACK */
#define BLACK 0

/*
 * RBTreeNode structure is the foundation of a Red-Black Tree.
 *
 * A node holds data, is either RED or BLACK,
 * as well as, it also knows its parent, and its right and left children.
 */
typedef struct RBTreeNode {
    unsigned char color;
    void* data;
    struct RBTreeNode* parent, *child_l, *child_r;
} RBNode;

/*
 * RBTree  structure is the Red-Black Tree itself.
 *
 * It holds the root of the tree,
 * keeps track of the number of nodes in the tree, and it also holds the method
 * for comparing each node via their data.
 */
typedef struct RBTree {
    RBNode* root;
    unsigned long size;
    int (*compare)(void*, void*);
} RBTree;

/*
 * RBLeftRotate and RBRightRotate swap 2 parent-children nodes 
 * while keeping the correct structure of the Tree.
 */
void RBLeftRotate(RBTree*, RBNode*);
void RBRightRotate(RBTree*, RBNode*);

/*
 * RBInsert is for creating a new node and inserting it in an existing tree. It
 * uses RBInsertFixup to check whether the properties of the Red-Black tree were
 * violated and fixes accordingly.
 */
RBNode* RBInsert(RBTree*, void*);
RBNode* RBInsertFixup(RBTree*, RBNode*);

#endif 
