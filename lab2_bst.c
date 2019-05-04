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

void inorder_recur(lab2_node *node) {
	if (node == NULL)
		return;
	inorder_recur(node->left);
	//printf("%d ", node->key);
	inorder_recur(node->right);
}

/*
 * TODO
 *  Implement funtction which traverse BST in in-order
 *  
 *  @param lab2_tree *tree  : bst to print in-order. 
 *  @return                 : status (success or fail)
 */
int lab2_node_print_inorder(lab2_tree *tree) {
    // You need to implement lab2_node_print_inorder function.
    inorder_recur(tree->root);
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
	pthread_mutex_init(&res->mutex, NULL);
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
    res->parent = NULL;
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
	if (tree->root == NULL) {
		tree->root = new_node;
		//printf("new root key : %d\n", new_node->key);
	}
	else {
		lab2_node *temp = tree->root;
		while (1) {
			if (temp->key > new_node->key)
				if (temp->left == NULL) {
					temp->left = new_node;
					new_node->parent = temp;
					break;
				}
				else
					temp = temp->left;
			else if (temp->key < new_node->key)
				if (temp->right == NULL) {
					temp->right = new_node;
					new_node->parent = temp;
					break;
				}
				else
					temp = temp->right;
			else
				break;
		}
		//printf("new node key : %d\n", new_node->key);
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
    if (tree->root == NULL) {
    	pthread_mutex_lock(&tree->mutex);
		tree->root = new_node;
		//printf("new root key : %d\n", new_node->key);
		pthread_mutex_unlock(&tree->mutex);
	}
	else {
		lab2_node *temp = tree->root;
		while (1) {
			if (temp->key > new_node->key)
				if (temp->left == NULL) {
    				pthread_mutex_lock(&temp->mutex);
					temp->left = new_node;
					new_node->parent = temp;
    				pthread_mutex_unlock(&temp->mutex);
					break;
				}
				else
					temp = temp->left;
			else if (temp->key < new_node->key)
				if (temp->right == NULL) {
    				pthread_mutex_lock(&temp->mutex);
					temp->right = new_node;
					new_node->parent = temp;
    				pthread_mutex_unlock(&temp->mutex);
					break;
				}
				else
					temp = temp->right;
			else
				break;
		}
		//printf("new node key : %d\n", new_node->key);
	}
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
    pthread_mutex_lock(&tree->mutex);
    if (tree->root == NULL) {
		tree->root = new_node;
		//printf("new root key : %d\n", new_node->key);
	}
	else {
		lab2_node *temp = tree->root;
		while (1) {
			if (temp->key > new_node->key)
				if (temp->left == NULL) {
					temp->left = new_node;
					new_node->parent = temp;
					break;
				}
				else
					temp = temp->left;
			else if (temp->key < new_node->key)
				if (temp->right == NULL) {
					temp->right = new_node;
					new_node->parent = temp;
					break;
				}
				else
					temp = temp->right;
			else
				break;
		}
		//printf("new node key : %d\n", new_node->key);
	}
    pthread_mutex_unlock(&tree->mutex);
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
    lab2_node *del;

	if (tree->root == NULL) {
		return 0;
	}
    while (temp->key != key) {
    	if (temp->key > key)
    		temp = temp->left;
    	else
    		temp = temp->right;
    }
    del = temp;
	//lab2_node_print_inorder(tree);
    if (temp->left == NULL && temp->right == NULL) {
    	printf("both null : %d\n", key);
 		if (temp == tree->root) {
    		printf("both null root : %d\n", key);
 			tree->root = NULL;
 			return 0;
 		}
    	if (temp->parent->left) {
    		if (temp->key == temp->parent->left->key)
    			temp->parent->left = NULL;
    		else
    			temp->parent->right = NULL;
    	}
    	else
    		temp->parent->right = NULL;
    }
    else if (temp->left != NULL && temp->right != NULL) {
       	printf("both not null : %d\n", key);
    	temp = temp->left;
    	if (temp->right == NULL) {
    		del->key = temp->key;
    		printf("both not null 1 : %d\n", key);
    		if (temp->left) {
    			temp->left->parent = del;
    			del->left = temp->left;
    		}
    	}
    	else {
    		printf("both not null 2 : %d\n", key);
    		while (1) {
    			if (temp->right == NULL) {	
    				printf("both not null 3 : %d\n", key);
    				del->key = temp->key;
    				if (temp->left) {
    					temp->left->parent = temp->parent;
	    				temp->parent->right = temp->left;
	    			}
	    			else
	    				temp->parent->right = NULL;
    				break;
    			}
    			else {
    				temp = temp->right;
    			}
    		}
    	}
    }
    else {
       	printf("one null %d\n", key);
       	//printf("temp : %d\n", temp->key);
       	if (temp == tree->root) {
			if (temp->left) {
				temp->left->parent = NULL;
				tree->root = temp->left;
			}
			else {
				temp->right->parent = NULL;
				tree->root = temp->right;
			}
			return 0;
		}
		
    	if (temp->right != NULL) {
    		//printf("b1\n");
			temp->right->parent = temp->parent;
    		if (temp->parent->left) {
    			//printf("plk : %d\n", temp->parent->left->key);
    			if (temp->parent->left->key == key)
	    			temp->parent->left = temp->right;
	    		else
	    			temp->parent->right = temp->right;
    		}
    		else {
    			if (temp->parent->right->key == key)
	    			temp->parent->right = temp->right;
	    		else
	    			temp->parent->left = temp->right;
    		}
    	}
    	else {
	   		//printf("b2\n");
			temp->left->parent = temp->parent;
    		if (temp->parent->left) {
    			//printf("plk : %d\n", temp->parent->left->key);
    			if (temp->parent->left->key == key)
	    			temp->parent->left = temp->left;
	    		else
	    			temp->parent->right = temp->left;
    		}
    		else {
    			if (temp->parent->right->key == key)
	    			temp->parent->right = temp->left;
	    		else
	    			temp->parent->left = temp->left;
    		}
	    }
	}
	//printf("cur root : %d\n", tree->root->key);
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
    lab2_node *temp = tree->root;
    lab2_node *del;

	if (tree->root == NULL) {
		return 0;
	}
    while (temp->key != key) {
    	if (temp->key > key)
    		temp = temp->left;
    	else
    		temp = temp->right;
    }
    del = temp;
	//lab2_node_print_inorder(tree);
    if (temp->left == NULL && temp->right == NULL) {
    	//printf("both null : %d\n", key);
 		if (temp == tree->root) {
 			tree->root = NULL;
 			return 0;
 		}
    	if (temp->parent->left) {
    		if (temp->key == temp->parent->left->key) {
				pthread_mutex_lock(&temp->parent->mutex);
    			temp->parent->left = NULL;
				pthread_mutex_unlock(&temp->parent->mutex);
    		}
    		else {
				pthread_mutex_lock(&temp->parent->mutex);
    			temp->parent->right = NULL;
				pthread_mutex_unlock(&temp->parent->mutex);
    		}
    	}
    	else {
			pthread_mutex_lock(&temp->parent->mutex);
    		temp->parent->right = NULL;
			pthread_mutex_unlock(&temp->parent->mutex);
    	}
    }
    else if (temp->left != NULL && temp->right != NULL) {
       	//printf("both not null : %d\n", key);
    	temp = temp->left;
    	if (temp->right == NULL) {
			pthread_mutex_lock(&del->mutex);
    		del->key = temp->key;
    		temp->left->parent = del;
    		del->left = temp->left;
			pthread_mutex_unlock(&del->mutex);
    	}
    	else {
    		while (1) {
    			if (temp->right == NULL) {
					pthread_mutex_lock(&del->mutex);
    				del->key = temp->key;
    				if (temp->left) {
    					temp->left->parent = temp->parent;
	    				temp->parent->right = temp->left;
	    			}
	    			else
	    				temp->parent->right = NULL;
					pthread_mutex_unlock(&del->mutex);
    				break;
    			}
    			else {
    				temp = temp->right;
    			}
    		}
    	}
    }
    else {
       	//printf("one null %d\n", key);
       	//printf("temp : %d\n", temp->key);
       	if (temp == tree->root) {
			if (temp->left) {
				pthread_mutex_lock(&tree->mutex);
				temp->left->parent = NULL;
				tree->root = temp->left;
				pthread_mutex_unlock(&tree->mutex);
			}
			else {
				pthread_mutex_lock(&tree->mutex);
				temp->right->parent = NULL;
				tree->root = temp->right;
				pthread_mutex_unlock(&tree->mutex);
			}
			return 0;
		}
    	if (temp->right != NULL) {
			pthread_mutex_lock(&temp->parent->mutex);
			temp->right->parent = temp->parent;
    		if (temp->parent->left) {
    			if (temp->parent->left->key == key) {
	    			temp->parent->left = temp->right;
	    		}
	    		else {
	    			temp->parent->right = temp->right;
	    		}
    		}
    		else {
    			if (temp->parent->right->key == key) {
	    			temp->parent->right = temp->right;
	    		}
	    		else {
	    			temp->parent->left = temp->right;
	    		}
    		}
			pthread_mutex_unlock(&temp->parent->mutex);
    	}
    	else {
    		if (temp->parent->left) {
				pthread_mutex_lock(&temp->parent->mutex);
    			temp->left->parent = temp->parent;
    			if (temp->parent->left->key == key) {
	    			temp->parent->left = temp->left;
	    		}
	    		else {
	    			temp->parent->right = temp->left;
	    		}
    		}
    		else {
    			if (temp->parent->right->key == key) {
	    			temp->parent->right = temp->left;
	    		}
	    		else {
	    			temp->parent->left = temp->left;
	    		}
    		}
			pthread_mutex_unlock(&temp->parent->mutex);
	    }
	}
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
    pthread_mutex_lock(&tree->mutex);
    lab2_node *temp = tree->root;
    lab2_node *parent = temp;
    lab2_node *del;

	if (tree->root != NULL) {
    	pthread_mutex_unlock(&tree->mutex);
		return 0;
	}
    while (temp->key != key) {
    	parent = temp;
    	if (temp->key > key)
    		temp = temp->left;
    	else
    		temp = temp->right;
    }
    del = temp;
	//lab2_node_print_inorder(tree);
    if (temp->left == NULL && temp->right == NULL) {
    	//printf("both null : %d\n", key);
 		if (temp == tree->root) {
 			tree->root = NULL;
    		pthread_mutex_unlock(&tree->mutex);
 			return 0;
 		}
    	if (parent->left) {
    		if (temp->key == parent->left->key)
    			parent->left = NULL;
    		else
    			parent->right = NULL;
    	}
    	else
    		parent->right = NULL;
    }
    else if (temp->left != NULL && temp->right != NULL) {
       	//printf("both not null : %d\n", key);
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
       	//printf("one null %d\n", key);
       	//printf("temp : %d\n", temp->key);
       	if (temp == tree->root) {
			if (temp->left)
				tree->root = temp->left;
			else
				tree->root = temp->right;
    		pthread_mutex_unlock(&tree->mutex);
			return 0;
		}
		
    	if (temp->right != NULL) {
    		//printf("b1\n");
    		if (parent->left) {
    			//printf("plk : %d\n", parent->left->key);
    			if (parent->left->key == key)
	    			parent->left = temp->right;
	    		else
	    			parent->right = temp->right;
    		}
    		else {
    			if (parent->right->key == key)
	    			parent->right = temp->right;
	    		else
	    			parent->left = temp->right;
    		}
    	}
    	else {
	   		//printf("b2\n");
    		if (parent->left) {
    			//printf("plk : %d\n", parent->left->key);
    			if (parent->left->key == key)
	    			parent->left = temp->left;
	    		else
	    			parent->right = temp->left;
    		}
    		else {
    			if (parent->right->key == key)
	    			parent->right = temp->left;
	    		else
	    			parent->left = temp->left;
    		}
	    }
	}
	pthread_mutex_unlock(&tree->mutex);
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
    if (tree->root)
	    lab2_node_delete(tree->root);
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
    if (node->left)
	    lab2_node_delete(node->left);
	if (node->right)
	    lab2_node_delete(node->right);
    free(node);
}

