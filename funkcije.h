#ifndef _FUNKCIJE_H_
# define _FUNKCIJE_H_

typedef struct bst {
	char kljuc[20];
	char prevod[20];
	int brpojavljivanja;//broj pojavljivanja tog broja u svim nivima ispod tog broja
	struct bst* left;
	struct bst* right;
	struct bst* parent;
}Bst;

typedef struct node {
	int br;
	Bst* info;
	struct node* next;
}Node;




#endif