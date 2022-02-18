#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>

RBTree* RBTreeInit(int (*_compare)(void*, void* b)) {
    //Make sure that a valid comparison function for data is provided.
    if(_compare == NULL) {
        fprintf(stderr, "No comparison function is provided.\n");
        return 0;
    }

    //Allocate a dynamic instance of the Red Black Tree structure
    RBTree* new_tree = (RBTree*) malloc(sizeof(RBTree));
    if(new_tree == NULL) {
        fprintf(stderr, "Internal Error:"
                "Failed to allocate a Red Black Tree instance.\n");

        return 0;
    }

    //Assign all values of the nil node to 0 and set it to root
    new_tree->nil = (RBNode) {BLACK, NULL, NULL, NULL, NULL};
    new_tree->root = &new_tree->nil;

    //Set the comparison function of the 
    new_tree->compare = _compare;

    new_tree->size = 0;

    return new_tree;
}

/* Below is the standard Left Rotate for a Red-Black Tree
 * For detailed overview, please consult the book "Introduction to Algorithms"
 * */
void RBLeftRotate(RBTree* tree, RBNode* primary) {
    //Make sure the provided pointers are not NULL
    if(!tree || !primary) {
        fprintf(stderr, "Error: Invalid tree or node provided.\n");
        return;
    }

    //Assign the right child of the primary to be the secondary target
    RBNode* secondary = primary->child_r;

    //Set the secondary's left child to be the right child of the primary
    primary->child_r = secondary->child_l;

    //If it was not nil, set the parent accordingly
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
    //Make sure the provided pointers are not NULL
    if(!tree || !primary) {
        fprintf(stderr, "Error: Invalid tree or node provided.\n");
        return;
    }

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
    //Make sure valid data is provided
    //NOTE: This is necessary since insertion depends on the comparison of keys.
    if(data == NULL) {
        fprintf(stderr, "Error: No data provided for insertion.\n");
        return NULL;
    }

    //Allocate a new empty node
    RBNode* new_node = (RBNode*) malloc(sizeof(RBNode));
    if(!new_node) {
        fprintf(stderr, "Internal Error: Failed to allocate a new node.\n");
        return 0;
    }
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

    RBInsertFixup(tree, new_node);

    return new_node;
}

void RBInsertFixup(RBTree* tree, RBNode* target) {
    //Repeat while the parent is RED
    while(target->parent->color == RED) {
        //If the parent is a left child of the grandparent
        if(target->parent == target->parent->parent->child_l) {
            //Get the uncle (right child of the grandparent) of the target
            RBNode* uncle = target->parent->parent->child_r;
            //If the uncle is red
            if(uncle->color = RED) {
                //Color both parent and uncle black and color grandparent red
                target->parent->color = BLACK;
                uncle->color = BLACK;
                target->parent->parent->color = RED;
                
                //Select grandparent for the next iteration
                target = target->parent->parent;

            //Else if uncle is black
            } else{

                //If the target is a right child
                if(target == target->parent->child_r) {
                    //Set the parent as target and perform a left rotation.
                    target = target->parent;
                    RBLeftRotate(tree, target);
                }

                //Change the parent's color to black
                target->parent->color = BLACK;
                target->parent->parent->color = RED;
                RBRightRotate(tree, target->parent->parent);
            }
        } else {
            
            //Get the uncle (left child of the grandparent) of the target
            RBNode* uncle = target->parent->parent->child_l;
            //If the uncle is red
            if(uncle->color = RED) {
                //Color both parent and uncle black and color grandparent red
                target->parent->color = BLACK;
                uncle->color = BLACK;
                target->parent->parent->color = RED;
                
                //Select grandparent for the next iteration
                target = target->parent->parent;

            //Else if uncle is black
            } else{

                //If the target is a right child
                if(target == target->parent->child_l) {
                    //Set the parent as target and perform a left rotation.
                    target = target->parent;
                    RBRightRotate(tree, target);
                }

                //Change the parent's color to black
                target->parent->color = BLACK;
                //Change grandparent to red;
                target->parent->parent->color = RED;
                //Perform a left rotation on the grandparent
                RBLeftRotate(tree, target->parent->parent);
            }
        }
    }

    tree->root->color = BLACK;
}
