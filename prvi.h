#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define kreiraj(x) x=malloc(sizeof(*x))


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

#define fo(x) x=(Node*) malloc(sizeof(Node))


Bst* form(char* kljuc, char* prevod) {//formira cvor
	Bst* node = 0;
	kreiraj(node);
	strcpy(node->kljuc, kljuc);
	strcpy(node->prevod, prevod);
	node->brpojavljivanja = 1;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return node;
}

Bst* dodaj(Bst* root, Bst* node) {
	Bst* pom1 = 0, * pom2 = root;
	if (!root) {
		root = node;
	}
	else {
		while (pom2) {
			pom1 = pom2;
			if (strcmp(node->kljuc, pom2->kljuc) < 0) {
				pom2 = pom2->left;
			}
			else {
				if (strcmp(pom2->kljuc, node->kljuc) == 0) {
					pom2->brpojavljivanja += 1;
				}
				pom2 = pom2->right;
			}
		}

		if (strcmp(node->kljuc, pom1->kljuc) < 0) {
			pom1->left = node;
			node->parent = pom1;
		}
		else {
			pom1->right = node;
			node->parent = pom1;
		}
	}
	return root;
}
Bst* formirajstablo(Bst* root) {
	char kljuc[20] = { 0 };
	char prevod[20] = { 0 };
	FILE* file = fopen("dat.txt", "r");
	while (fscanf(file, "%s - %s", kljuc, prevod) == 2) {
		if (strcmp(kljuc, "end") == 0) {
			fclose(file);
			return root;
		}
		Bst* node = form(kljuc, prevod);
		root = dodaj(root, node);
	}

	fclose(file);
	return root;
}

void nadjiprevod(Bst* root, char* rec) {
	Bst* pok1 = 0, * pok2 = root;

	while (pok2) {
		pok1 = pok2;
		if (strcmp(pok2->kljuc, rec) == 0) {
			printf("Prevodi reci su: %s ", pok1->prevod);
			break;
		}
		else if (strcmp(pok2->kljuc, rec) > 0) {
			pok2 = pok2->left;
		}
		else {
			pok2 = pok2->right;
		}
	}
	pok1 = pok2;
	if (pok1) {
		while (pok1) {
			pok1 = pok1->right;
			if (pok1) {
				Bst* f = pok1;
				while (f) {
					pok2 = f;
					f = f->left;
				}
				if (strcmp(pok2->kljuc, rec) == 0) {
					printf("%s ", pok2->prevod);
				}
				pok1 = pok2;
			}
			else {
				break;
			}
		}
	}
	else {
		printf("Dati kljuc ne postoji u BST-u!!!");
	}
}

int svenule(Node* head) {
	for (Node* curr = head; curr; curr = curr->next) {
		if (curr->info != 0) {
			return 0;
		}
	}
	return 1;
}

void ispisi(Bst* root, int nivo) {
	if (root) {
		ispisi(root->right, nivo + 1);
		printf("%*s%s\n", 4 * nivo, " ", root->kljuc);
		ispisi(root->left, nivo + 1);
	}
}
void formatiranispis(Bst* root) {
	Node* x = 0, * head = 0, * tail = 0;
	fo(x);
	int i = 10;
	int j = 1;
	if (root) {
		x->info = root;
		x->br = 1;
		x->next = NULL;
		head = x;
		tail = x;
		fo(x);
		//granicnik
		x->info = NULL;
		x->br = -1;
		x->next = NULL;
		tail->next = x;
		tail = x;
		int pom = 1;
		while (head) {
			if (head->br == 1) {// postoji broj u ovom cvoru
				if (i == 10) {
					printf("%*s ", (--i), " ");
					printf("%s%d ", head->info->kljuc, head->info->brpojavljivanja);
				}
				else {
					printf("%s%d   ", head->info->kljuc, head->info->brpojavljivanja);
				}
			}
			else if (head->br == 0) {// ne postoji broj, taj node je list
				printf("x     ");
			}
			else if (head->br == -1) {//granicnik, za prelazak u novi red i ispis /\
                printf("\n");
				printf("\n%*s", i, " ");
				//for (int k = 0; k < j; k++) {
				//	printf("/\\ ");
				//}
				printf("\n");
				j *= 2;
				printf("%*s", i -= 1, " ");
			}

			//levi sin postoji
			if (head->br == 1 && head->info && head->info->left) {
				fo(x);
				x->br = 1;
				x->info = head->info->left;
				x->next = NULL;
				tail->next = x;
				tail = x;
			}
			if ((head->br == 1 && head->info && head->info->left == NULL) || head->br == 0) {
				fo(x);
				x->br = 0;
				x->info = NULL;
				x->next = NULL;
				tail->next = x;
				tail = x;
			}

			//desni sin postoji
			if (head->br == 1 && head->info && head->info->right) {
				fo(x);
				x->br = 1;
				x->info = head->info->right;
				x->next = NULL;
				tail->next = x;
				tail = x;
			}

			if ((head->br == 1 && head->info && head->info->right == NULL) || head->br == 0) {
				fo(x);
				x->br = 0;
				x->info = NULL;
				x->next = NULL;
				tail->next = x;
				tail = x;
			}

			//naisli smo na granicnik koji izbacujemo i ponovo ubacujemo
			if (head->br == -1) {
				fo(x);
				x->info = NULL;
				x->br = -1;
				x->next = NULL;
				tail->next = x;
				tail = x;
			}

			Node* old = head;
			head = head->next;
			//print(head);
			free(old);

			//ako lista nodova sadrzi samo nule to je kraj izvrsavanja, nema novih brojeva nego su samo x-evi
			if (svenule(head)) {
				break;
			}

			pom += 1;

		}

	}

	else {// ne postoji stablo, root je NULL
		free(x);
		printf("Prazno drvo.");
	}
}

int obrisi(Bst** root, char* rec) {
	if (!*root) exit(0);

	Bst* p = *root, * q = NULL;

	while (p && strcmp(p->kljuc, rec) != 0) {
		q = p;
		if (strcmp(p->kljuc, rec) > 0) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}

	Bst* rc = NULL;
	Bst* s = NULL;
	Bst* f = NULL;
	if (p == NULL) return 0;

	if (p->left == NULL) {
		rc = p->right;
	}
	else if (p->right == NULL) {
		rc = p->left;
	}
	else {
		f = p;
		rc = p->right;
		s = rc->left;
		while (s != NULL) {
			f = rc;
			rc = s;
			s = rc->left;
		}

		if (f != p) {
			f->left = rc->right;
			rc->right = p->right;
		}
		rc->left = p->left;
	}

	if (q == NULL) {
		*root = rc;
	}
	else if (p == q->left) {
		q->left = rc;
	}
	else {
		q->right = rc;
	}

	int n = p->brpojavljivanja;
	free(p);
	return n;
}



char* nadjinajucestalijurec(Bst* root, int* pojavljivanje) {
	if (!root) { printf("Pogresna rec"); exit(0); }
	char maxrec[20] = { 0 };
	int n;
	Node* head = NULL, * tail = NULL, * node = NULL;
	node = malloc(sizeof(*node));
	node->info = root;
	strcpy(maxrec, root->kljuc);
	n = node->info->brpojavljivanja;
	head = tail = node;
	while (head) {
		if (head && head->info && head->info->left) {
			node = malloc(sizeof(*node));
			node->next = NULL;
			node->info = head->info->left;
			tail->next = node;
			tail = node;
		}

		if (head && head->info && head->info->right) {
			node = malloc(sizeof(*node));
			node->next = NULL;
			node->info = head->info->right;
			tail->next = node;
			tail = node;
		}

		if (head && head->info && head->info->brpojavljivanja > n) {
			strcpy(maxrec, head->info->kljuc);
			n = head->info->brpojavljivanja;
		}

		if (head) {
			Node* nop = head;
			head = head->next;
			free(nop);

			//ispisi(head);
		}
	}

	(*pojavljivanje) = n;

	return maxrec;
}


void meni() {
	printf("1.Formiraj stablo\n"
		"2.Prevedi rec\n"
		"3.Umetni novi par reci\n"
		"4.Ispis\n"
		"5.Brisanje zadatog kljuca\n"
		"6.Brisanje stabla\n"
		"7. Odredjivanje reci sa najvecim brojem razlicitih prevoda.\n"
		"0.Kraj\n"
	);
}

void prvi() {
	int kraj = 0;
	Bst* root = NULL;
	while (!kraj) {
		printf("\nIzaberite operaciju nad BST-om:\n");
		int op;
		meni();
		scanf("%d", &op);
		switch (op) {
		case 1:
			//printf("Unesite parovereci(kluc-prevod):\n");
			root = formirajstablo(root);
			break;
		case 2:
			printf("Unesite rec koju hocete da prevedete:");
			char rec[20] = { 0 };
			scanf("%s%*c", rec);
			nadjiprevod(root, rec);
			break;
		case 3:
			printf("Unesite par reci za dodavanje(kljuc-prevod):");
			char klj[20] = { 0 };
			char prev[20] = { 0 };
			scanf("%s - %s%*c", klj, prev);
			Bst* node = form(klj, prev);
			root = dodaj(root, node);
			break;
		case 4:
			formatiranispis(root);
			//ispisi(root, 0);

			break;

		case 5:
			printf("Unesite rec za brisanje:");
			char ucitaj[20] = { 0 };
			scanf("%s%*c", ucitaj);
			int n = obrisi(&root, ucitaj);
			formatiranispis(root);
			printf("\n");
			for (int i = 0; i < n - 1; i++) {
				obrisi(&root, ucitaj);
				formatiranispis(root);
				printf("\n\n\n");
			}
			break;
		case 6:
			while (root) {
				char brisanje[20] = { 0 };
				strcpy(brisanje, root->kljuc);
				obrisi(&root, brisanje);
			}
			printf("BST stablo je uspesno obrisano");
			break;

		case 7:

			printf("Najucestalija rec je:");
			int pojavljivanje;
			char* naj[20] = { 0 };
			strcpy(naj, nadjinajucestalijurec(root, &pojavljivanje));
			printf("%s\n", naj);
			printf("Ova rec se pojavljuje %d puta", pojavljivanje);

			break;

		case 0:
			kraj = 1;
			break;

		default:
			printf("Pogresan izbor!");
			break;
		}

	}

}
