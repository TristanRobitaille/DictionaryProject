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
	char w[] = "tristan";
	char d[] = "Robitaille";
	struct dictNode *n = createNode(w,d);
	//printf("node word: %s\n", n->word);
	//printf("node def: %s\n", n->def);

	//create node terry
	char w2[] = "terry";
	char d2[] = "Wu";
	struct dictNode *m = createNode(w2, d2);
	//printf("node word: %s\n", m->word);
	//printf("node def: %s\n", m->def);

	//create node tina
	char w3[] = "tina";
	char d3[] = "Zhang";
	struct dictNode *k = createNode(w3, d3);
	//printf("node word: %s\n", k->word);
	//printf("node def: %s\n", k->def);

	//find tree index
	int c = findDict(n);
	//printf("Dict name: %s\n", dict[c]->name);
	//printf("Dict index for n: %d\n", c);

	//insert nodes
	dict[c]->root = insertNode(n, dict[c]);
	dict[c]->root = insertNode(m, dict[c]);
	dict[c]->root = insertNode(k, dict[c]);

	//delete nodes
	dict[c]->root = deleteNode(k, dict[c]);

	//get dict tree size
	int tree_size = getSize(dict[c]);
	printf("dict size with getSize function: %d\n", tree_size);
	printf("dict size: %d\n", dict[c]->size);

	//get root of the tree
	//to ensure balance tree & deletion works
	printf("root word: %s", dict[c]->root->word);
	
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
