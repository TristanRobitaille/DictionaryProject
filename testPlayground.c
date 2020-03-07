#include "testPlayground.h"

int main(){

	struct dictNode *parentNode = createNode(NULL);
	struct dictNode *oneChild = createNode(parentNode);
	struct dictNode *childToTheChild = createNode(oneChild);

	parentNode->word = "I am the parent";
	oneChild->word = "I am the first child";
	childToTheChild = createNode(oneChild);

	oneChild->leftChild = childToTheChild;

	printf("What does the parent say: %s\n", parentNode->word);
	printf("What does the first child say: %s\n", oneChild->word);

	deleteNode(parentNode);
	deleteNode(oneChild);
	return 1;
}
