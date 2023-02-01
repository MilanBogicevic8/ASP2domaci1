#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "drugi.h"
#include "prvi.h"

int main() {
	int izb;
	printf("Koji zadatak radimo(1 ili 2):");
	scanf("%d", &izb);
	if (izb == 1) {
		prvi();
	}
	else if (izb == 2) {
		drugi();
	}
	else {
		printf("Pogresan izbor.");
	}
	return 0;
}