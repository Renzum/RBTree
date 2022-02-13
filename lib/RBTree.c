#include "RBTree.h"
#include <stdlib.h>

/* Below is the standard Left Rotate for a Red-Black Tree
 * For detailed overview, please consult the book "Introduction to Algorithms"
 * */
void RBLeftRotate(RBTree* tree, RBNode* primary) {
    //Assign the right child of the primary to be the secondary target
    RBNode* secondary = primary->child_r;

    //Set the secondary's left child to be the right child of the primary
    primary->child_r = secondary->child_l;

    //If it was non-empty, set the parent
    if(secondary->child_l != &tree->nil)
        secondary->child_l->parent = primary;

    //Set secondary's parent to be the primary's parent
    secondary->parent = primary->parent;

    //If primary was the root of the tree, set secondary to be the new root
    if(primary->parent == &tree->nil)
        tree->root = secondary;
    //If primary was a left child, put secondary in its place
    else if(primary == primary->parent->child_l)
        primary->parent->child_l = secondary;
    //If primary was a right child, put secondary in its place
    else
        primary->parent->child_r = secondary;

    //Link primary and secondary together
    secondary->child_l = primary;
    primary->parent = secondary;
}

void RBRightRotate(RBTree* tree, RBNode* primary) {
    //Assign the left child of the primary to be the secondary target
    RBNode* secondary = primary->child_l;

    //Set the secondary's right child to be the left child of the primary
    primary->child_l = secondary->child_r;

    //If it was non-empty, set the parent
    if(secondary->child_r != &tree->nil)
        secondary->child_r->parent = primary;

    //Set secondary's parent to be the primary's parent
    secondary->parent = primary->parent;

    //If primary was the root of the tree, set secondary to be the new root
    if(primary->parent == &tree->nil)
        tree->root = secondary;
    //If primary was a left child, put secondary in its place
    else if(primary == primary->parent->child_l)
        primary->parent->child_l = secondary;
    //If primary was a right child, put secondary in its place
    else
        primary->parent->child_r = secondary;

    //Link primary and secondary together
    secondary->child_r = primary;
    primary->parent = secondary;
}

RBNode* RBInsert(RBTree* tree, void* data) {
    //Allocate a new empty node
    RBNode* new_node = (RBNode*) malloc(sizeof(RBNode));
    new_node->child_r = new_node->child_l = new_node->parent = &tree->nil;
    new_node->color = RED;

    //Set the node to hold the data
    new_node->data = data;

    RBNode* temp = &tree->nil;
    RBNode* cursor = tree->root;

    //Loop through the tree until the leaves
    while(cursor != &tree->nil) {
        temp = cursor;

        //Proceed down on the left side if data is less than cursor
        if(tree->compare(data, temp->data) < 0) {
            cursor = cursor->child_l;
        //Proceed down on the right side if data is larger than cursor
        } else {
            cursor = cursor->child_r;
        }
    }

    //Set the new_node parent
    new_node->parent = temp;

    //Assign the new_node to the parent as a child according to data comparison
    if(temp == &tree->nil)
        tree->root = new_node;
    else if(tree->compare(data, temp->data))
        temp->child_l = new_node;
    else
        temp->child_r = new_node;

    //Call fixup
}
