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
//	struct linkedDict **dict = createDict();

	struct linkedDict **dict = createDict();
	loadTree_fromFile("data/test.txt", dict);
//	char w[] = "Trist/0";
//	char d[] = "Robitaille/0";
//	struct dictNode *n = createNode(w,d);
//	int c = findDict(n);
//
//	//delete nodes
////	dict[c]->root = deleteNode(k, dict[c]);
//
//	//get dict tree size
//	int tree_size = getSize(dict[c]);
//	printf("dict size with getSize function: %d\n", tree_size);
//	printf("dict size: %d\n", dict[c]->size);
//
//	//get root of the tree
//	//to ensure balance tree & deletion works
//	printf("root word: %s\n\n", dict[c]->root->word);
//
//	print_lev("Trip", 3, dict);
//	print_words_same_start("T", dict);
	print_subset("Treas", 5, 4, dict);
	
	//Translate a string and save it to char translated
	char *stringToTranslate = "This is cool";
	const int stringLen = 4000; //Number of characters (including "\0" of string to translate)
	char *filename = "translated.txt";
	char *destLanguage = "es"; //Code for translation destination language. Follows ISO 639-1
	translate(stringToTranslate, stringLen, filename, destLanguage);
	FILE *transFile = fopen(filename, "r");
	char str[500 + stringLen];
	fgets(str, (500 + stringLen), transFile);
	fclose(transFile);
	printf("Finally: %s\n", str);

	return 0;
}
