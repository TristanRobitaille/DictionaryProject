#include "node.h"
#include <string.h>
#include <ctype.h>
#include <math.h>


struct dictNode *createNode(char *w, char *d){
	/*! Allocates memory for a new node, passes in the address to the parent node in the BST and initializes balance factor at 0.
	 * Returns NULL is allocation is unsuccessful, or pointer to new node is successful.
	 */

	struct dictNode *newNode = malloc(sizeof(struct dictNode)); //Allocate memory for the node to be initialized

	*w = toupper(*w); //convert the first letter to uppercase

	newNode->word = strdup(w);
	newNode->def = strdup(d);
	newNode->wordLength = strlen(w);
	newNode->defLength = strlen(d);

	newNode->balanceFactor = 0; //Initialize balance factor at 0
	newNode->height = 1;

	newNode->wordTranslation = NULL;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	newNode->nextWord = NULL;
	newNode->previousWord = NULL;
	return newNode;
};


struct dictNode *createNode_fromFile(char *w, char *d, struct dictNode *pw, struct dictNode *nw){
	/*! Allocates memory for a new node, passes in the address to the parent node in the BST and initializes balance factor at 0.
	 * Returns NULL is allocation is unsuccessful, or pointer to new node is successful.
	 */

	struct dictNode *newNode = malloc(sizeof(struct dictNode)); //Allocate memory for the node to be initialized

	*w = toupper(*w); //convert the first letter to uppercase

	newNode->word = strdup(w);
	newNode->def = strdup(d);
	newNode->wordLength = strlen(w);
	newNode->defLength = strlen(d);

	newNode->balanceFactor = 0; //Initialize balance factor at 0
	newNode->height = 0;

	newNode->wordTranslation = NULL;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	newNode->previousWord = pw;
	newNode->nextWord = nw;
	return newNode;
};


struct dictNode *delete(struct dictNode *subroot, struct dictNode *tobeDeleted){
	/*!The recursive function takes the node going to be deleted, and the subroot of the tree
	 * The subroot is being recursively changed
	 * Return the new subroot
	 */
//	printf("location: %s\n", subroot->word);
//	printf("Being deleted: %s\n", tobeDeleted->word);
	if(strcmp((tobeDeleted->word), (subroot->word)) < 0){
		subroot = delete(tobeDeleted, subroot->leftChild);
	}
	else if(strcmp((tobeDeleted->word), (subroot->word)) > 0){
		subroot =  delete(tobeDeleted, subroot->rightChild);
	}
	else{
		//one child case
		if((subroot->leftChild == NULL) || (subroot->rightChild == NULL)){
			struct dictNode *temp = subroot->leftChild ? subroot->leftChild : subroot->rightChild;
			// No child case
			if (temp == NULL)
			{
				temp = subroot;
				subroot = NULL;
			}
			else // One child case
			 *(subroot) = *temp; // Copy the contents of
							// the non-empty child
			free(temp);
		}
		//two child case
		else{
			// Get the inorder successor (smallest in the right subtree)
			struct dictNode* temp = minValueNode(subroot->rightChild);
			struct dictNode* leftbranch = subroot->leftChild;

			// Copy the inorder successor's data to this node
			*(subroot) = *temp;

			//retain its original leftbranch
			subroot->leftChild = leftbranch;

			// Delete the inorder successor
			subroot->rightChild = delete(subroot->rightChild, temp);
			free(leftbranch);
			//free(temp); not sure whether to free it here
		}
	}
	/*!update balance factor
	 *rotate
	 */
	subroot = balanceTree(subroot, tobeDeleted);

	return subroot;
}



struct dictNode * minValueNode(struct dictNode* node){
	/*!The function gives the minimum valued node
	 * return the node pointer
	 */
    struct dictNode* current = node;

    /* loop down to find the leftmost leaf */
    while (current->leftChild != NULL)
        current = current->leftChild;

    return current;
}



struct dictNode *insert(struct dictNode *tobeInserted, struct dictNode *subroot){
	/*!The recursive function takes the node going to be inserted, and the subroot of the tree
	 * The subroot is being recursively changed
	 * Return the new subroot
	 */
//	printf("tobeinserted: %s\n", tobeInserted->word);
	if(subroot == NULL){
		subroot = malloc(sizeof(struct dictNode));
		subroot = tobeInserted;
	}

	else{
		//check word ascii value
		if(strcmp((tobeInserted->word), (subroot->word)) < 0){
			subroot->leftChild = insert(tobeInserted, subroot->leftChild);
		}
		else if(strcmp((tobeInserted->word), (subroot->word)) > 0){
			subroot->rightChild = insert(tobeInserted, subroot->leftChild);
		}

		//if the word already exists in the dict
		else if(strcmp((tobeInserted->word), (subroot->word)) == 0){
			//int originaldef = sizeof(subroot->def);//or strlen, unsure
			//subroot->def = realloc(subroot->def, (originaldef + sizeof(tobeInserted->def)) * sizeof(char));//sizeof or strlen?
			//*(subroot->def + originaldef) = tobeInserted->def;
			strcat(subroot->def, tobeInserted->def);
			//free(tobeInserted);//no need to assign a value if the function is changed to void
		}
	}

	/*!update balance factor
	 *rotate
	 */
	subroot = balanceTree(subroot, tobeInserted);
//	printf("return subroot: %s\n", subroot->word);
	return subroot;
}



int getHeight(struct dictNode *node){
	if (node == NULL){
		return 0;
	}
	return node->height;
}


int getBalance(struct dictNode *node){
	if(node == NULL){
		return 0;
	}
	return getHeight(node->leftChild) - getHeight(node->rightChild);
}


struct dictNode *returnNode(struct dictNode *node, char *wordToFind){
    if (node == NULL || !strcmp(node->word, wordToFind)) return node;

    if(strcmp(wordToFind, node->word) < 0){
		node = returnNode(node->leftChild, wordToFind);
	}else if(strcmp(wordToFind, node->word) > 0){
		node = returnNode(node->rightChild, wordToFind);
	}
//    printf("returning: %s\n", node->word);
    return node;
}

//Function Declaration
int max(int a, int b);

//Tried putting it to macro, but gives warning somehow
int max(int a, int b)
{
    return (a > b)? a : b;
}


struct dictNode *rightRotate(struct dictNode *node){
	/*!right rotate at node
	 * update height
	 * return the new subroot
	 */
//	printf("right rotate");
	struct dictNode *leftnode = node->leftChild;
	struct dictNode *temp = leftnode->rightChild;

	leftnode->rightChild = node;
	node->leftChild = temp;

	node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
	leftnode->height = max(getHeight(leftnode->leftChild), getHeight(leftnode->rightChild)) + 1;

	return leftnode;
}



struct dictNode *leftRotate(struct dictNode *node){
	/*!left rotate at node
	 * update height
	 * return the new subroot
	 */
//	printf("left rotate");
	struct dictNode *rightnode = node->rightChild;
	struct dictNode *temp = rightnode->leftChild;

	rightnode->leftChild = node;
	node->rightChild = temp;

	node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
	rightnode->height = max(getHeight(rightnode->leftChild), getHeight(rightnode->rightChild)) + 1;

	return rightnode;
}



struct dictNode* balanceTree(struct dictNode *root, struct dictNode *tobeInserted){
	//check if root exists
	if(root == NULL){
		return NULL;
	}

	//update height
	root->height = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));
	//printf("%s, height: %d\n", root->word, root->height);

	int balance = getBalance(root);
	//printf("balance: %d\n", balance);

	//four cases
	if (balance > 1 && strcmp(tobeInserted->word, root->leftChild->word) < 0)
	    return rightRotate(root);

	// Right Right Case
	if (balance < -1 && strcmp(tobeInserted->word, root->rightChild->word) > 0)
		return leftRotate(root);

	// Left Right Case
	if (balance > 1 && strcmp(tobeInserted->word, root->leftChild->word) > 0){
		root->leftChild =  leftRotate(root->leftChild);
		return rightRotate(root);
	}

	// Right Left Case
	if ((balance < -1) && (strcmp(tobeInserted->word, root->rightChild->word) < 0)){
		root->rightChild = rightRotate(root->rightChild);
		return leftRotate(root);
	}

	//printf("no change \n");
	return root;
}
