#include "user_interaction2.h"
#include "dict.h"
#include "node.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "translator.h"
#include <ctype.h>

void printCommands(){
	printf("Here are the commands you can issue, with their expected input arguments:\n");
	printf("-define 'word'\t\t\t\t\t-import 'textfile.csv'\t\t\t-insert 'word' 'definition'\n");
	printf("-delete 'word'\t\t\t\t\t-scroll 'word'\t\t\t\t-subset 'start' 'length'\n");
	printf("-startWith 'word'\t\t\t\t-closeTo 'word' 'threshold'\t\t-size\n");
	printf("-translate 'word' 'language' (ISO 639-1)\t-save\t\t\t\t\t-exit\n\n");
}

int main(){
	printf("\n\n\n\n*************************************************************************************\n");
	printf("Welcome to the dictionary!\n");
	printCommands();
	printf("*This dictionary was written by Terry Wu and Tristan Robitaille and is preloaded with words from The Project Gutenberg Etext of Webster’s Unabridged Dictionary\n\n\n");

	//Preload all CSV files
	struct linkedDict **dict = createDict();

	for (int i = 0; i < 25; i++){
		char fn[500] = "data/";
		char letter[10];
		sprintf(letter, "%c", i + 65);
		strcat(fn, letter);
		strcat(fn, ".csv");
		loadTree_fromFile(fn, dict);
	}
	dummyLoad(dict);

	//Wait for user input
	char str[10000];
	char *command;

	while(1){
	    fgets(str, 10000, stdin);
	    command = strtok (str, " ");

	    if (!strcmp("define", command) || !strcmp("define\n", command)){ //Command to get defintion - COMPLETE
		    command = strtok (NULL, " ");
		    command[strcspn(command, "\n")] = 0; //Remove newline character

		    struct dictNode *node = returnNode(dict[toupper(command[0]) - 65]->root, command);

		    if (node == NULL) printf("Word not found\n");
		    else printf("Definition of %s is %s\n\n", command, node->def);

	    }else if (!strcmp("import", command) || !strcmp("import\n", command)){ //Command to import a CSV dictionary
		    char *fn;
		    command = strtok (NULL, " ");
		    fn = command;
		    fn[strcspn(fn, "\n")] = 0; //Remove newline character

		    printf("fn: %s\n", fn);
	    	loadTree_fromFile(fn, dict);

	    	printf("%s imported\n\n", fn);

	    }else if (!strcmp("insert", command) || !strcmp("insert\n", command)){ //Command to insert a new word - COMPLETE
		    char *word;
		    command = strtok (NULL, " ");
		    word = command;
		    word[strcspn(word, "\n")] = 0; //Remove newline character

		    char *definition;
		    command = strtok (NULL, " ");
		    definition = command;
		    definition[strcspn(definition, "\n")] = 0; //Remove newline character

		    struct dictNode *newNode = createNode(word, definition);

		    //Get translation
			char *filename = "translated.txt";
			char *destLanguage = "es"; //Code for translation destination language. Follows ISO 639-1
			translate(newNode->word, 10000, filename, destLanguage);
			FILE *transFile = fopen(filename, "r");
			char str[10000];
			fgets(str, 10000, transFile);
			fclose(transFile);
		    newNode->wordTranslation = str;

		    insert(newNode, dict[toupper(command[0]) - 65]->root);

		    printf("Insertion complete\n\n");


	    }else if (!strcmp("delete", command) || !strcmp("delete\n", command)){ //Command to delete a word - COMPLETED
		    char *word;
		    command = strtok (NULL, " ");
		    word = command;
		    word[strcspn(word, "\n")] = 0; //Remove newline character

		    struct dictNode *node = returnNode(dict[toupper(command[0]) - 65]->root, command);

		    if (node == NULL) printf("Word not found\n");
		    else {
			    deleteNode(node, dict[toupper(command[0]) - 65]);
			    printf("Node deleted\n\n");

		    }

	    }else if (!strcmp("scroll", command) || !strcmp("scroll\n", command)){ //Command to scroll around a word
		    char *word;
		    command = strtok (NULL, " ");
		    word = command;
		    word[strcspn(word, "\n")] = 0; //Remove newline character

		    printf("Enter 'u' to scroll up and 'd' to scroll down around %s.\nEnter ok to exit scroll mode.\n", word);

		    char str[20];

		    while (strcmp(str, "ok") != 0){
			    fgets(str, 10000, stdin);
			    str[strcspn(str, "\n")] = 0; //Remove newline character

			    if (!strcmp("u", str)){
			    	word = scroll(dict[toupper(command[0]) - 65], word, "up");
			    	printf("%s\n", word);
			    } else if (!strcmp("d", str)){
			    	word = scroll(dict[toupper(command[0]) - 65], word, "down");
			    	printf("%s\n", word);
			    }
		    }
		    printf("Exited scroll mode\n\n");

	    }else if (!strcmp("subset", command) || !strcmp("subset\n", command)){ //Command to get a subset of words of the same length that are close together - COMPLETE
		    char *word;
		    command = strtok (NULL, " ");
		    word = command;
		    word[strcspn(word, "\n")] = 0; //Remove newline character

		    char *length;
		    command = strtok (NULL, " ");
		    length = command;
		    length[strcspn(length, "\n")] = 0; //Remove newline character

	    	print_subset(word, atoi(length), 10, dict);
	    	printf("\n");

	    }else if (!strcmp("startWith", command) || !strcmp("startWith\n", command)){ //Command to get a subset of words starting with the same sequence of characters - COMPLETE
		    char *word;
		    command = strtok (NULL, " ");
		    word = command;
		    word[strcspn(word, "\n")] = 0; //Remove newline character

	    	print_words_same_start(word, dict);
	    	printf("\n");

	    }else if (!strcmp("closeTo", command) || !strcmp("closeTo\n", command)){ //Command to get all words that are close to the reference word within a threshold - COMPLETE
		    char *word;
		    command = strtok (NULL, " ");
		    word = command;
		    word[strcspn(word, "\n")] = 0; //Remove newline character

		    char *threshold;
		    command = strtok (NULL, " ");
		    threshold = command;
		    threshold[strcspn(threshold, "\n")] = 0; //Remove newline character

	    	print_lev(word, atoi(threshold), dict);

	    }else if (!strcmp("size", command) || !strcmp("size\n", command)){ //Command to get the size of the dictionary - COMPLETE
		    int totalSize = 0;

		    for (int i = 0; i < 26; i++){
		    	totalSize += getSize(dict[i]);
		    }

		    printf("Size of dictionary is: %d\n\n", totalSize);

	    }else if (!strcmp("translate", command) || !strcmp("translate", command)){ //Command to translate a word to another language - COMPLETE
		    char *word;
		    command = strtok (NULL, " ");
		    word = command;
		    word[strcspn(word, "\n")] = 0; //Remove newline character

		    char *language;
		    command = strtok (NULL, " ");
		    language = command;
		    language[strcspn(language, "\n")] = 0; //Remove newline character

		    //Get translation
			char *filename = "translated.txt";
			translate(word, 10000, filename, language);
			FILE *transFile = fopen(filename, "r");
			char str[10000];
			fgets(str, 10000, transFile);
			fclose(transFile);
			printf("Translation is %s\n\n", str);

	    }else if (!strcmp("save", command) || !strcmp("save\n", command)){ //Command to export dictionary content to a CSV file
	    	FILE *output = fopen("saved_dictionary.txt", "w");

		    for (int i = 0; i < 26; i++){
		    	save_traversal(dict[i]->root, output);
		    }

		    fclose(output);
		    printf("Dictionary saved to 'saved_dictionary.txt'\n\n");

	    }else if (!strcmp("exit", command) || !strcmp("exit\n", command)){ //Command to exit program - COMPLETE
	    	//Free all memory
	    	//deleteEverything(dict);
	    	return 0;


	    }else if (!strcmp("command", command) || !strcmp("command\n", command)){ //Print available commands - COMPLETE
	    	printCommands();

	    }else{ //Inform that command is invalid
	    	printf("Invalid command. Type 'command' to view a list of commands\n\n");
	    }
	}
}
