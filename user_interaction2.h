/** \file user_interaction2.h
 * A brief file description.
 * A more elaborated file description.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "dict.h"

void print_lev(char *refWord, int threshold, struct linkedDict **dict);
void lev_traversal_printer(struct dictNode *node, char *refWord, int threshold);
void print_words_same_start(char *refStart, struct linkedDict **dict);
void words_same_start_traversal(struct dictNode *node, char *refStart);
void print_subset(char *refWord, int targetLen, int numOutput, struct linkedDict **dict);
void save_traversal(struct dictNode *node, FILE *fn);
/*! \fn int open(const char *pathname,int flags)
    \brief Opens a file descriptor.

    \param pathname The name of the descriptor.
    \param flags Opening flags.
*/
void deleteEverything(struct linkedDict **dict);
