/*
*	Operating System Lab
*	    Lab2 (Synchronization)
*	    Student id : 
*	    Student name : 
*
*   lab2_bst.c :
*       - thread-safe bst code.
*       - coarse-grained, fine-grained lock code
*
*   Implement thread-safe bst for coarse-grained version and fine-grained version.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>

#include "lab2_sync_types.h"

/*
 * TODO
 *  Implement funtction which traverse BST in in-order
 *  
 *  @param lab2_tree *tree  : bst to print in-order. 
 *  @return                 : status (success or fail)
 */
int lab2_node_print_inorder(lab2_tree *tree) {
    // You need to implement lab2_node_print_inorder function.
}

/*
 * TODO
 *  Implement function which creates struct lab2_tree
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_tree )
 * 
 *  @return                 : bst which you created in this function.
 */
lab2_tree *lab2_tree_create() {
    // You need to implement lab2_tree_create function.
    struct lab2_tree *res = malloc (sizeof(struct lab2_tree));
	res->root = NULL;
	return res;
}

/*
 * TODO
 *  Implement function which creates struct lab2_node
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param int key          : bst node's key to creates
 *  @return                 : bst node which you created in this function.
 */
lab2_node * lab2_node_create(int key) {
    // You need to implement lab2_node_create function.
    struct lab2_node *res = malloc(sizeof(struct lab2_node));
	pthread_mutex_init(&res->mutex, NULL);
    res->left = NULL;
    res->right = NULL;
    res->key = key;
    return res;
}

/* 
 * TODO
 *  Implement a function which insert nodes from the BST. 
 *  
 *  @param lab2_tree *tree      : bst which you need to insert new node.
 *  @param lab2_node *new_node  : bst node which you need to insert. 
 *  @return                 : satus (success or fail)
 */
int lab2_node_insert(lab2_tree *tree, lab2_node *new_node){
    // You need to implement lab2_node_insert function.
	if (tree->root == NULL)
		tree->root = new_node;
	else {
		lab2_node *temp = tree->root;
		while (1) {
			if (temp->key > new_node->key)
				if (temp->left == NULL) {
					temp->left = new_node;
					break;
				}
				else
					temp = temp->left;
			else if (temp->key < new_node->key)
				if (temp->right == NULL) {
					temp->right = new_node;
					break;
				}
				else
					temp = temp->right;
		}
		printf("new node key : %d\n", new_node->key);
	}
}

/* 
 * TODO
 *  Implement a function which insert nodes from the BST in fine-garined manner.
 *
 *  @param lab2_tree *tree      : bst which you need to insert new node in fine-grained manner.
 *  @param lab2_node *new_node  : bst node which you need to insert. 
 *  @return                     : status (success or fail)
 */
int lab2_node_insert_fg(lab2_tree *tree, lab2_node *new_node){
      // You need to implement lab2_node_insert_fg function.
}

/* 
 * TODO
 *  Implement a function which insert nodes from the BST in coarse-garined manner.
 *
 *  @param lab2_tree *tree      : bst which you need to insert new node in coarse-grained manner.
 *  @param lab2_node *new_node  : bst node which you need to insert. 
 *  @return                     : status (success or fail)
 */
int lab2_node_insert_cg(lab2_tree *tree, lab2_node *new_node){
    // You need to implement lab2_node_insert_cg function.
}

/* 
 * TODO
 *  Implement a function which remove nodes from the BST.
 *
 *  @param lab2_tree *tree  : bst tha you need to remove node from bst which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove(lab2_tree *tree, int key) {
    // You need to implement lab2_node_remove function.
    lab2_node *temp = tree->root;
    lab2_node *parent;
    lab2_node *del;

    while (temp->key != key) {
    	parent = temp;
    	if (temp->key > key)
    		temp = temp->left;
    	else
    		temp = temp->right;
    }
    del = temp;
    
    if (temp->left == NULL && temp->right == NULL) {
    	printf("both null\n");
    	if (parent->left)
    		if (temp->key == parent->left->key)
    			parent->left = NULL;
    		else
    			parent->right = NULL;
    	else
    		parent->right = NULL;
    }
    else if (temp->left != NULL && temp->right != NULL) {
       	printf("both not null\n");
    	temp = temp->left;
    	if (temp->right == NULL) {
    		del->key = temp->key;
    		del->left = temp->left;
    	}
    	else {
    		while (1) {
    			if (temp->right == NULL) {	
    				del->key = temp->key;
    				if (temp->left)
	    				parent->right = temp->left;
	    			else
	    				parent->right = NULL;
    				break;
    			}
    			else {
    				parent = temp;
    				temp = temp->right;
    			}
    		}
    	}
    }
    else {
       	printf("one null\n");
    	if (temp->right != NULL)
    		if (parent->left->key == key)
    			parent->left = temp->right;
    		else
    			parent->right = temp->right;
    	else
    		if (parent->left->key == key)
    			parent->left = temp->left;
    		else
    			parent->right = temp->left;
    }
}

/* 
 * TODO
 *  Implement a function which remove nodes from the BST in fine-grained manner.
 *
 *  @param lab2_tree *tree  : bst tha you need to remove node in fine-grained manner from bst which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove_fg(lab2_tree *tree, int key) {
    // You need to implement lab2_node_remove_fg function.
}


/* 
 * TODO
 *  Implement a function which remove nodes from the BST in coarse-grained manner.
 *
 *  @param lab2_tree *tree  : bst tha you need to remove node in coarse-grained manner from bst which contains key.
 *  @param int key          : key value that you want to delete. 
 *  @return                 : status (success or fail)
 */
int lab2_node_remove_cg(lab2_tree *tree, int key) {
    // You need to implement lab2_node_remove_cg function.
}


/*
 * TODO
 *  Implement function which delete struct lab2_tree
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param lab2_tree *tree  : bst which you want to delete. 
 *  @return                 : status(success or fail)
 */
void lab2_tree_delete(lab2_tree *tree) {
    // You need to implement lab2_tree_delete function.
    free(tree);
}

/*
 * TODO
 *  Implement function which delete struct lab2_node
 *  ( refer to the ./include/lab2_sync_types.h for structure lab2_node )
 *
 *  @param lab2_tree *tree  : bst node which you want to remove. 
 *  @return                 : status(success or fail)
 */
void lab2_node_delete(lab2_node *node) {
    // You need to implement lab2_node_delete function.
    free(node);
}

