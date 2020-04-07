/*
 * dict.c
 *
 *  Created on: Apr 6, 2020
 *      Author: wtyte
 */
#include "node.h"
#include <string.h>
#include <math.h>
#include "dict.h"

struct linkedDict** createDict(){
	struct linkedDict **dict = calloc(26, sizeof(struct linkedDict *));

	for(int i=0; i<26; i++){
		dict[i] = malloc(sizeof(struct linkedDict));
		dict[i]->name = malloc(sizeof(char));
		*(dict[i]->name) = (char)(i+65);
		dict[i]->root = NULL;
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



