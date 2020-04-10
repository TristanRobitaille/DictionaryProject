#include <stdlib.h>
#include <stdio.h>

//#define max(x,y) ((x>y)?x:y);
#ifndef NODE_H_
#define NODE_H_


struct dictNode *createNode(char *w, char *d);
struct dictNode *insert(struct dictNode *, struct dictNode*);
struct dictNode *delete(struct dictNode *, struct dictNode*);
struct dictNode *minValueNode(struct dictNode* );
struct dictNode *balanceTree(struct dictNode *, struct dictNode *);
struct dictNode *returnNode(struct dictNode *node, char *wordToFind);
struct dictNode *createNode_fromFile(char *w, char *d, struct dictNode *pw, struct dictNode *nw);

//Declare node struct
struct dictNode {
	/*! \struct
	 * Smallest data structure, to be inserted in dictionary BST's (based on alphabetical order of word).
	 * Contains all attributes that may be needed.
	 * Must be initialized with *createNode(int *parentPtr), where *parentPtr is a pointer to the parent node (set to NULL if the node is the root)
	 */

	int balanceFactor; //Balance factor for AVL BST (+- 1 for AVL; initialize at 0)
	int wordLength; //Length of the node's word char array (max. 2^16)
	int defLength; //Length of the node's word's definition (max. 2^16)
	int height; //the height of AVL tree at the node

	char *word; //Pointer to the first char of the word
	char *def; //Pointer to the first char of the word's English definition
	char *wordTranslation; //Pointer to the first char of the word's translation (obtained from Google Translate Google API)

	struct dictNode *previousWord; //Pointer node of the previous word in alphabetical order
	struct dictNode *nextWord; //Pointer node of the previous word in alphabetical order

	//struct dictNode *parent; //(Address of the node's parent) Recursive Code, no need for parent linkage
	struct dictNode *leftChild; //Address of the node's left child
	struct dictNode *rightChild; //Address of the node's right child
};

#endif /* NODE_H_ */
