/*
 * dict.h
 *
 *  Created on: Apr 6, 2020
 *      Author: wtyte
 */

#ifndef DICT_H_
#define DICT_H_

#include <stdlib.h>
#include <stdio.h>
#include "node.h"


//#define max(x,y) ((x>y)?x:y);



int findDict(struct dictNode* target);
struct linkedDict** createDict();
char* getDef(struct dictNode* target, struct linkedDict** dict);
char* getDef_Helper(struct dictNode* target, struct dictNode* subroot);
struct dictNode *insertNode(struct dictNode *tobeInserted, struct linkedDict *dict);
struct dictNode *deleteNode(struct dictNode *tobeDeleted, struct linkedDict *dict);
int getSize(struct linkedDict* dict);
char* getAuthor(struct linkedDict* dict);
int levenshtein(const char *strA, int lenA, const char *strB, int lenB);
void dummyLoad(struct linkedDict **dict);
char* scroll(struct linkedDict* dict, char* target, char* direction);
struct linkedDict** loadTree_fromFile(char* filename, struct linkedDict** dict);

struct linkedDict {
	/*! \struct
	 * Biggest data structure, where each linked list node is a pointer to the root a AVL tree.
	 * Contains all attributes that may be needed.
	 * 2 options: either created priorily, or created as inserting
	 */
	int size; //Size of the dictionary, increment with each insert

	char *name; //Name of the dictionary, abcdefg......
	char *author;//Author of the dictionary

	struct dictNode *root; //Pointer to the root of the AVL tree;
};




#endif /* DICT_H_ */
