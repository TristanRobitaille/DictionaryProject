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
	printf("The %d words closest to %s that are of length %d are:\n", numOutput, refWord, targetLen);

	int predCnt = 0;
	struct dictNode *node = returnNode(dict[refWord[0] - 65]->root, refWord);

	if (node == NULL){
		printf("Reference word could not be found\n");
		return;
	}

	//BELOW IS NOT DONE - WE WANT TO USE PREVIOUSWORD AND NEXTWORD IN NODES TO CLIMB UP AND DOWN THE ALPHABET

//	while (predCnt < numPredecessor){
//		char *currWord = inorder_pred(node, NULL, refWord);
//
//		if (strlen(currWord) == targetLen){
//			printf("%s\n", currWord);
//			predCnt++;
//		}
//		node = returnNode(dict[refWord[0] - 65]->root, currWord);
//	}
//
//	int sucCnt = 0;
//	node = returnNode(dict[refWord[0] - 65]->root, refWord);
//	while (sucCnt < numSuccessor){
//
//		char *currWord = inorder_suc(node, NULL, refWord);
//
//		if (strlen(currWord) == targetLen){
//			printf("%s\n", currWord);
//			sucCnt++;
//		}
//		node = returnNode(dict[refWord[0] - 65]->root, currWord);
//	}

}

//char* inorder_pred(struct dictNode *node, struct dictNode *pre, char *refWord){
//	//Base case
//    if (node == NULL) return NULL;
//
//    //If word is present at root
//    if (!strcmp(node->word, refWord)){
//        // the maximum value in left subtree is predecessor
//        if (node->leftChild != NULL){
//        	struct dictNode *tmp = node->leftChild;
//
//            while (tmp->rightChild)
//                tmp = tmp->rightChild;
//            pre = tmp ;
//        }
//        return node->word;
//    }
//
//    // If key is smaller than root's key, go to left subtree
//    if(strcmp(refWord, node->word) > 0){
//        pre = node ;
//		printf("Current word predecessor: %s\n", pre->word);
//        inorder_pred(node->rightChild, pre, refWord) ;
//    }
//}
//
//char* inorder_suc(struct dictNode *node, struct dictNode *suc, char *refWord){
//	//Base case
//    if (node == NULL) return NULL;
//
//    //If word is present at root
//    if (!strcmp(node->word, refWord)){
//        // the maximum value in left subtree is predecessor
//        if (node->rightChild != NULL){
//        	struct dictNode *tmp = node->rightChild;
//
//            while (tmp->leftChild)
//                tmp = tmp->leftChild;
//            suc = tmp ;
//        }
//        return node->word;
//    }
//
//    // If key is smaller than root's key, go to left subtree
//    if(strcmp(refWord, node->word) < 0){
//        suc = node ;
//		printf("Current word successor: %s\n", suc->word);
//        inorder_pred(node->leftChild, suc, refWord) ;
//    }
//}
