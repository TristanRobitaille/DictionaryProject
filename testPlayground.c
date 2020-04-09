/*
 * testPlayground.c
 *
 *  Created on: Apr 7, 2020
 *      Author: wtyte
 */
#include "testPlayground.h"


int main(){
	/*!A place to test all functions as it goes
	 * Each comment block contains a specific types of operation test
	 * Hope everything works
	 */
	//create dict
	struct linkedDict **dict = createDict();

	//create node tristan
	char w[] = "Trist";
	char d[] = "Robitaille";
	struct dictNode *n = createNode(w,d);
	n->previousWord = NULL;

	//create node terry
	char w2[] = "Terry";
	char d2[] = "Wu";
	struct dictNode *m = createNode(w2, d2);
	m->previousWord = n;
	n->nextWord = m;

	//create node tina
	char w3[] = "Treee";
	char d3[] = "Zhang";
	struct dictNode *k = createNode(w3, d3);
	k->previousWord = m;
	m->nextWord = k;

	//create node tina
	char w4[] = "Treas";
	char d4[] = "Zhang";
	struct dictNode *l = createNode(w4, d4);
	l->previousWord = k;
	k->nextWord = l;

	//create node tina
	char w5[] = "Troph";
	char d5[] = "Zhang";
	struct dictNode *p = createNode(w5, d5);
	p->previousWord = l;
	l->nextWord = p;

	p->nextWord = NULL;

	//find tree index
	int c = findDict(n);

	//insert nodes
	dict[c]->root = insertNode(n, dict[c]);
	dict[c]->root = insertNode(m, dict[c]);
	dict[c]->root = insertNode(k, dict[c]);
	dict[c]->root = insertNode(l, dict[c]);
	dict[c]->root = insertNode(p, dict[c]);

	//delete nodes
//	dict[c]->root = deleteNode(k, dict[c]);

	//get dict tree size
	int tree_size = getSize(dict[c]);
	printf("dict size with getSize function: %d\n", tree_size);
	printf("dict size: %d\n", dict[c]->size);

	//get root of the tree
	//to ensure balance tree & deletion works
	printf("root word: %s\n\n", dict[c]->root->word);
	
	print_lev("Trip", 3, dict);
	print_words_same_start("T", dict);
	print_subset("Treas", 5, 4, dict);
	/*
	//Translate a string and save it to char translated
	char *stringToTranslate = "This is cool";
	const int stringLen = 4; //Number of characters (including "\0" of string to translate)
	char *filename = "translated.txt";
	char *destLanguage = "es"; //Code for translation destination language. Follows ISO 639-1

	char *translated = translate(stringToTranslate, stringLen, filename, destLanguage);
	printf("Finally: %s\n", translated);*/

	return 0;
}
