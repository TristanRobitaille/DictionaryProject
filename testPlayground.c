#include "testPlayground.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

	struct dictNode *parentNode = createNode(NULL);
	struct dictNode *leftCchild = createNode(parentNode);
	struct dictNode *rightCchild = createNode(parentNode);

	parentNode->word = "I am the parent";
	leftCchild->word = "I am the left child";
	rightCchild->word = "I am the right child";

	parentNode->leftChild = leftCchild;
	parentNode->rightChild = leftCchild;

	//Adding attributes to the parent node
	parentNode->balanceFactor = 22;
	parentNode->wordLength = 120;
	parentNode->defLength = 1200;

	parentNode->def = "My test word's definition";
	parentNode->wordTranslation = "Mot de test";

	//Test
	printf("What does the parent say: %s\n", parentNode->word);
	printf("What does the left child say: %s\n", parentNode->leftChild->word);
	printf("What does the right child say: %s\n", parentNode->rightChild->word);

	printf("Balance factor: %d\n", parentNode->balanceFactor);
	printf("Word length: %d\n", parentNode->wordLength);
	printf("Definition length: %d\n", parentNode->defLength);

	printf("The actual definition: %s\n", parentNode->def);
	printf("The translation: %s\n", parentNode->wordTranslation);

	deleteNode(parentNode);
	deleteNode(leftCchild);
	deleteNode(rightCchild);

	return 1;
}
