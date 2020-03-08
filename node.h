
struct dictNode *createNode(struct dictNode *parentPtr);
int deleteNode(struct dictNode *toBeDeleted);

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

	char *word; //Pointer to the first char of the word
	char *def; //Pointer to the first char of the word's English definition
	char *wordTranslation; //Pointer to the first char of the word's translation (obtained from Google Translate Google API)

	struct dictNode *previousWord; //Pointer node of the previous word in alphabetical order
	struct dictNode *nextWord; //Pointer node of the previous word in alphabetical order

	struct dictNode *parent; //Address of the node's parent
	struct dictNode *leftChild; //Address of the node's left child
	struct dictNode *rightChild; //Address of the node's right child
};
