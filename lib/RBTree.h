/**
 * @file RBTree.h
 * @brief A declaration file for the classes and the methods used in the library.
 *
 * Some stuff idk.
 */
#ifndef RBTREE_H
#define RBTREE_H

#include <stdlib.h>


#define RED 255 ///< a macro definition for the understanding of color Red.
#define BLACK 0 ///< a macro definition for the understanding of color Black.

/**
 * @brief Node data structure for the Red Black Tree.
 *
 * RBTreeNode structure is the foundation of a Red-Black Tree.
 * A node in a Red Black Tree is either Red or Black, holds data (aka. Key),
 * and it points towards its parent, and its left and right children.
 */
typedef struct RBTreeNode {
    unsigned char color; ///< The color of the red black node. 
    void* data; ///< A pointer to the data stored in the node.
    struct RBTreeNode* parent; ///< Pointer to the parent node
    struct RBTreeNode* child_l; ///< Pointer to the left child node.
    struct RBTreeNode* child_r; ///< Pointer to the right child node.
} RBNode;

/**
 * @brief The Red Black Tree.
 *
 * RBTree  structure is the Red-Black Tree itself.
 * It holds the root of the tree,
 * keeps track of the number of nodes in the tree, and it also holds the method
 * for comparing each node via their data.
 */
typedef struct RBTree {
    RBNode* root; ///< A pointer to the root node of the tree.
    unsigned long size; ///< The number of nodes currently present.
    
    /**
     * @brief A function to compare the nodes.
     * 
     * A user defined function that will be used in the tree
     * to compare the nodes based on their data.
     *
     * @param a void pointer to data
     * @param b void pointer to data
     *
     * @return 1 if a > b, -1 if a < b, and 0 if a = b.
     */
    int (*compare)(void* a, void* b); 

    RBNode nil; ///< A special null node to be used in the Red Black Tree.
} RBTree;

/**
 * @brief A function that performs a left rotation on a given node.
 *
 * @param tree The tree in which the rotation is performed.
 * @param primary The target node which the rotation is performed on.
 *
 * Given a target tree and a node within it,
 * the function performs a left rotation on that node.
 * It makes the right child of the target node,
 * become the parent of the target node,
 * and the target node itself become the left child of the new parent.
 * This function preserves the properties of the Binary Tree
 * by repositioning the other children as well.
 */
void RBLeftRotate(RBTree* tree, RBNode* primary);

/**
 * @brief A function that performs a right rotation on a given node.
 *
 * @param tree The tree in which the rotation is performed.
 * @param primary The target node which the rotation is performed on.
 *
 * Given a target tree and a node within it,
 * the function performs a left rotation on that node.
 * It makes the left child of the target node,
 * become the parent of the target node,
 * and the target node itself become the right child of the new parent.
 * This function preserves the properties of the Binary Tree
 * by repositioning the other children as well.
 */
void RBRightRotate(RBTree* tree, RBNode* primary);

/**
 * @brief Inserts a new node with the provided data in to the given tree.
 *
 * @param tree The Red Black Tree in which to insert the new node.
 * @param data The data which the new node will hold.
 */
RBNode* RBInsert(RBTree* tree, void* data);
RBNode* RBInsertFixup(RBTree*, RBNode*);


#endif 
