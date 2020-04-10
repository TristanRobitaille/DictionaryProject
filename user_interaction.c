#include "user_interaction.h"

void print_lev(char *refWord, int threshold, struct linkedDict **dict){
	/*! Print all words with a Levenshtein distance lower or equal to the threshold
	 *
	 */

	printf("Words with a Levenshtein distance of %d or lower to %s:\n", threshold, refWord);

	for (int i = 0; i < 26; i++){
		if (dict[i]->root != NULL) lev_traversal_printer(dict[i]->root, refWord, threshold);
	}
}

void lev_traversal_printer(struct dictNode *node, char *refWord, int threshold){
	if (node == NULL) return;

	//Recursion of the left subtree
	lev_traversal_printer(node->leftChild, refWord, threshold);

	//Print word if Levenshtein distance is below or equal to threshold
	if (levenshtein(node->word, strlen(node->word), refWord , strlen(node->word)) <= threshold) printf("%s\n", node->word);

	//Recursion of the right subtree
	lev_traversal_printer(node->rightChild, refWord, threshold);
}

void print_words_same_start(char *refStart, struct linkedDict **dict){
	/*! Prints words that start with the sequence of characters refStart
	 *
	 */

	printf("Words that start with %s:\n", refStart);
	words_same_start_traversal(dict[refStart[0] - 65]->root, refStart);
}

void words_same_start_traversal(struct dictNode *node, char *refStart){
	if (node == NULL) return;

	//Recursion of the left subtree
	words_same_start_traversal(node->leftChild, refStart);

	//Print word if it starts with refWord
	if (strlen(node->word) >= strlen(refStart)){ //If the word is at the same length or longer than refStart
		int pass = 1;

		//Ensure that every character until the end of refStart are equal
		//to the corresponding character in the current node's word
		for (int i = 0; i <= (strlen(refStart) - 1); i++){
			if (node->word[i] != refStart[i]){
				pass = 0;
				break;
			}
		}

		if (pass == 1) printf("%s\n", node->word);
	}

	//Recursion of the right subtree
	words_same_start_traversal(node->rightChild, refStart);
}

void print_subset(char *refWord, int targetLen, int numOutput, struct linkedDict **dict){
	/*!Find the numOutput words that have targetLen closest to refWord. Idea is to find
	 * all closest numOutput/2 predecessors and successors to targetLen that have targetLen
	 * length and store them in a temporary BST. Then, print the tree inorder.
	 */

	int numPredecessor = floor(numOutput/2);
	int numSuccessor = numOutput - numPredecessor;
	printf("The closest words to %s that are of length %d are:\n", numOutput, targetLen);

	int predCnt = 0;
	int sucCnt = 0;
	struct dictNode *node = returnNode(dict[toupper(refWord[0]) - 65]->root, refWord);

	if (node == NULL){
		printf("Reference word could not be found\n");
		return;
	}

	node = node->previousWord; //First, look at the previous word
	while (predCnt < numPredecessor && node != NULL){
		if (strlen(node->word) == targetLen){ //If this word fits the length requirement, print it
			printf("%s\n", node->word);
			predCnt++;
		}
		node = node->previousWord; //Find the node for the previous word
	}

	node = returnNode(dict[refWord[0] - 65]->root, refWord); //Now, look at the next word
	node = node->nextWord;
	while (sucCnt < numSuccessor && node != NULL){
		if (strlen(node->word) == targetLen){ //If this word fits the length requirement, print it
			printf("%s\n", node->word);
			sucCnt++;
		}
		node = node->nextWord; //Find the node for the previous word
	}
}
