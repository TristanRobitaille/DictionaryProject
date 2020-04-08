#include "node.h"
//#include "dict.h"
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
	newNode->height = 0;

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




struct linkedDict *deleteNode(struct dictNode *tobeDeleted, struct linkedDict *dict){
	/*! Frees memory used by the node toBeDeleted
	 * Returns the new root after deletion
	 */
	if(tobeDeleted == NULL){
		return NULL;
	}

	else{
		//check if the dictionary is empty
		if(dict->root == NULL){
			dict->root = NULL;
		}

		else{
			//check word ascii value
			if(strcmp((tobeDeleted->word), (dict->root->word)) < 0){
				dict->root->leftChild = delete(tobeDeleted, dict->root->leftChild);
			}
			else if(strcmp((tobeDeleted->word), (dict->root->word)) > 0){
				dict->root->rightChild =  delete(tobeDeleted, dict->root->rightChild);
			}
			else{
				//one child case
				if((dict->root->leftChild == NULL) || (dict->root->rightChild == NULL)){
				   struct dictNode *temp = dict->root->leftChild ? dict->root->leftChild : dict->root->rightChild;

					// No child case
					if (temp == NULL)
					{
						temp = dict->root;
						dict->root = NULL;
					}
					else // One child case
					 *(dict->root) = *temp; // Copy the contents of
									// the non-empty child
					free(temp);
				}
				//two child case
				else{
					// Get the inorder successor (smallest in the right subtree)
					struct dictNode* temp = minValueNode(dict->root->rightChild);
					struct dictNode* leftbranch = dict->root->leftChild;

					// Copy the inorder successor's data to this node
					*(dict->root) = *temp;

					//retain its original leftbranch
					dict->root->leftChild = leftbranch;

					// Delete the inorder successor
					dict->root->rightChild = delete(dict->root->rightChild, temp);
					free(leftbranch);
					//free(temp); not sure whether to free it here
				}
			}
		}
	}

	return dict;
}

struct dictNode *delete(struct dictNode *tobeDeleted, struct dictNode *subroot){
	/*!The recursive function takes the node going to be deleted, and the subroot of the tree
	 * The subroot is being recursively changed
	 * Return the new subroot
	 */
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


struct dictNode *insertNode(struct dictNode *tobeInserted, struct linkedDict *dict){
	/*!The function takes the precreated node that is going to be inserted to the tree,
	 * also the correct tree in the linked list, which needs to be generated by another function
	 * The function returns the new root of the AVL tree or no return but update the root of the tree directly
	 */

	//if the inserting node is empty
	//struct dictNode* r = malloc(sizeof(struct dictNode));
	if (tobeInserted == NULL){
		return NULL;
	}

	//if the inserting node is not empty
	else{
		//check if the dictionary is empty
		if(dict->root == NULL){
			dict->root = tobeInserted;
		}

		else{
			//check word ascii value
			if(strcmp((tobeInserted->word), (dict->root->word)) < 0){
				printf("Terry is smaller\n");
				dict->root->leftChild = insert(tobeInserted, dict->root->leftChild);
			}
			else if(strcmp((tobeInserted->word), (dict->root->word)) > 0){
				printf("Terry is bigger\n");
				dict->root->rightChild =  insert(tobeInserted, dict->root->rightChild);
			}

			//This is can be written as a separate function void append(struct dictNode *tobeInserted, sturct dictNode *subroot)
			//if the word already exists in the dict
			else if(strcmp((tobeInserted->word), (dict->root->word)) == 0){
				//static char *start = dict->root->def;
				//int originaldef = sizeof(dict->root->def); //original def size, unsure to use strlen or sizeof
				//dict->root->def = realloc(dict->root->def, (originaldef + sizeof(tobeInserted->def)) * sizeof(char));//sizeof or strlen?
				//dict->root->def = dict->root->def + originaldef;
				strcat(dict->root->def, tobeInserted->def); //update def
				//free(tobeInserted);//no need to assign a value if the function is changed to void
			}
		}
	}
	dict->size = dict->size + 1;
	//r = dict->root;
	printf("how");
	printf("it returned: %s", dict->root->word);
	return dict->root;
}

struct dictNode *insert(struct dictNode *tobeInserted, struct dictNode *subroot){
	/*!The recursive function takes the node going to be inserted, and the subroot of the tree
	 * The subroot is being recursively changed
	 * Return the new subroot
	 */
	printf("tobeinserted: %s", tobeInserted->word);
	if(subroot == NULL){
		printf("update subroot here\n");
		subroot = malloc(sizeof(struct dictNode));
		subroot = tobeInserted;
		printf("new subroot: %s", subroot->word);
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
	printf("return subroot: %s", subroot->word);
	return subroot;
}

int getHeight(struct dictNode *node){
	if (node == NULL){
		return 0;
	}
	return node->height;
}
int getBalance(struct dictNode *node){
	if(node){
		return 0;
	}
	return getHeight(node->leftChild) - getHeight(node->rightChild);
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

	struct dictNode *rightnode = node->rightChild;
	struct dictNode *temp = rightnode->leftChild;

	rightnode->leftChild = node;
	node->rightChild = temp;

	node->height = max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
	rightnode->height = max(getHeight(rightnode->leftChild), getHeight(rightnode->rightChild)) + 1;

	return rightnode;
}

struct dictNode* balanceTree(struct dictNode *root, struct dictNode *tobeInserted){
	//update height
	root->height = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));

	int balance = getBalance(root);
	printf("balance: %d", balance);

	//four cases
	if (balance > 1 && strcmp(tobeInserted->def, root->leftChild->def) < 0)
	        return rightRotate(root);

	// Right Right Case
	if (balance < -1 && strcmp(tobeInserted->def, root->rightChild->def) > 0)
		return leftRotate(root);

	// Left Right Case
	if (balance > 1 && strcmp(tobeInserted->def, root->leftChild->def) > 0){
		root->leftChild =  leftRotate(root->leftChild);
		return rightRotate(root);
	}

	// Right Left Case
	if ((balance < -1) && (strcmp(tobeInserted->def, root->rightChild->def) < 0)){
		root->rightChild = rightRotate(root->rightChild);
		return leftRotate(root);
	}
	return root;
}

/*
 * dict.c
 *
 *  Created on: Apr 6, 2020
 *      Author: wtyte
 */

struct linkedDict** createDict(){
	struct linkedDict **dict = calloc(26, sizeof(struct linkedDict *));

	for(int i=0; i<26; i++){
		dict[i] = malloc(sizeof(struct linkedDict));
		dict[i]->name = malloc(sizeof(char));
		*(dict[i]->name) = (char)(i+65);
		dict[i]->root = NULL;
		dict[i]->size = 0;
	}

	return dict;
}

int findDict(struct dictNode* target){
	//need to convert all word to uppercase when making the node
	return ((int)*(target->word) - 65);
}

int getSize(struct linkedDict* dict){
	return dict->size;
}

char* getAuthor(struct linkedDict* dict){
	return dict->author;
}

char* getDef(struct dictNode* target, struct linkedDict** dict){
	int c = findDict(target);

	if(strcmp(target->word, dict[c]->root->word) == 0){
		return dict[c]->root->def;
	}
	else if(strcmp(target->word, dict[c]->root->word) < 0){
		return getDef_Helper(target, dict[c]->root->leftChild);
	}
	else if(strcmp(target->word, dict[c]->root->word) > 0){
		return getDef_Helper(target, dict[c]->root->rightChild);
	}

	printf("%s not found in dict.\n", target->word);
	return NULL;
}

char* getDef_Helper(struct dictNode* target, struct dictNode* subroot){
	if(strcmp(target->word, subroot->word) == 0){
		return subroot->def;
	}
	else if(strcmp(target->word, subroot->word) < 0){
		return getDef_Helper(target, subroot->leftChild);
	}
	else if(strcmp(target->word, subroot->word) > 0){
		return getDef_Helper(target, subroot->rightChild);
	}

	printf("%s not found in dict.\n", target->word);
	return NULL;
}

/*
struct linkedDict* loadTree_fromFile(char* filename){
	FILE *fptr = fopen(filename, "r");

	fclose(fptr);
}*/






