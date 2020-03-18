#include "node.h"

struct dictNode *createNode(struct dictNode *parentPtr){
	/*! Allocates memory for a new node, passes in the address to the parent node in the BST and initializes balance factor at 0.
	 * Returns NULL is allocation is unsuccessful, or pointer to new node is successful.
	 */

	struct dictNode *newNode = malloc(sizeof(struct dictNode)); //Allocate memory for the node to be initialized

	if (newNode == NULL){
		printf("Initialization of a new node has failed (malloc returned NULL).\n");
		return NULL;
	}

	newNode->parent = parentPtr; //Pass in the value of the node's parent
	newNode->balanceFactor = 0; //Initialize balance factor at 0
	return newNode;
};

int deleteNode(struct dictNode *toBeDeleted){
	/*! Frees memory used by the node toBeDeleted
	 * Returns 1 if deletion was successful
	 */

	free(toBeDeleted);

	return 1;
}

void insertNode(struct dictNode *node){

}
