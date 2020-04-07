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

//#define max(x,y) ((x>y)?x:y);



//static const unsigned char alphabet [26] = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};


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
