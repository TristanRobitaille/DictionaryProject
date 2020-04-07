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



