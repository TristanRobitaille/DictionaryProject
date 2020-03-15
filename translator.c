#include <Python.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

char *translate(char *toTranslate, const int strLen, char *filename, char *destLang){

	//Concatenate strings to create the Python line to open/create a text file.
	char strFile[256] = "f = open('"; //Max. filename length is 238 characters
	strcat(strFile, filename);
	strcat(strFile, "', 'w')\n");

	//Concatenate strings to create the Python line to open/create a text file.
	char *strTranslation = malloc((50 + strLen)*sizeof(char));
	strcpy(strTranslation, "translatedWord = trans.translate('");
	strcat(strTranslation, toTranslate);
	strcat(strTranslation, "', '");
	strcat(strTranslation, destLang);
	strcat(strTranslation, "', 'en')\n");

	//Concatenante whole program
	char *pythonTrans = malloc((500 + strLen)*sizeof(char));
	strcpy(pythonTrans, "from googletrans import Translator\n");
	strcat(pythonTrans, "trans = Translator()\n");
	strcat(pythonTrans, strTranslation);
	strcat(pythonTrans, strFile);
	strcat(pythonTrans, "f.write(translatedWord.text)\n");
	strcat(pythonTrans, "f.close()\n");

	//Run Python program
	Py_Initialize();
	PyRun_SimpleString(pythonTrans);
	Py_Finalize();

	//Free memory allocated to Python program strings
	free(strTranslation);
	free(pythonTrans);

	//Retrieve translated string
	FILE *transFile = fopen(filename, "r");
	char str[500 + strLen];
	fgets(str, (500 + strLen), transFile);
	fclose(transFile);

	return str;
}
