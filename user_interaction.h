#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dict.h"

void print_lev(char *refWord, int threshold, struct linkedDict **dict);
void lev_traversal_printer(struct dictNode *node, char *refWord, int threshold);
void print_words_same_start(char *refStart, struct linkedDict **dict);
void words_same_start_traversal(struct dictNode *node, char *refStart);
void print_subset(char *refWord, int targetLen, int numOutput, struct linkedDict **dict);
