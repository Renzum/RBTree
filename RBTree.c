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
    if(secondary->child_l != NULL)
        secondary->child_l->parent = primary;

    //Set secondary's parent to be the primary's parent
    secondary->parent = primary->parent;

    //If primary was the root of the tree, set secondary to be the new root
    if(primary->parent == NULL)
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
    if(secondary->child_r != NULL)
        secondary->child_r->parent = primary;

    //Set secondary's parent to be the primary's parent
    secondary->parent = primary->parent;

    //If primary was the root of the tree, set secondary to be the new root
    if(primary->parent == NULL)
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
