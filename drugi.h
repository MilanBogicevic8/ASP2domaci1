#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void meni2() {
	printf("1.Unos opsega\n"
		   "2.Pretraga\n"
	       "3. Kraj\n ");
}

void interpolacija(int* low, int* high,int br,int preciznost,int n) {
	int dvadeset = *low+(((*high - *low) * 20) / 100);
	int osamdeset = *low+(((*high - *low) * 80 )/ 100);
	int l = *low, h = *high;
	int vr;

	if (br == 1) {
		while (l <= h) {
			int mid = l + (dvadeset - l) * (h - l) / (*high - *low);
			if (mid == dvadeset) {
				printf("\nDa li je dati broj %.*f",n,(float)mid / preciznost);
				printf(" manji ili veci ili jednak zamisljenom broju(-1,1,0):");
				scanf("%d", &vr);
				if (vr == 0) {
					printf("Broj pokusaja je 1.\n");
				}
				else if (vr == 1) {
					*high = dvadeset - 1;
				}
				else if (vr == -1) {
					*low = dvadeset + 1;
				}
				else {
					printf("Pogresan izbor");
					continue;
				}
			}
			else if (dvadeset < mid) {
				h = mid;
			}
			else {
				l = mid;
			}
			break;
		}
	}else{
		while (l < h) {
			int mid = l + (osamdeset - l) * (h - l) / (*high - *low);
			if (mid == osamdeset) {
				printf("Da li je broj %.*f",n,(float) mid / preciznost);
				printf(" veci,manji ili jednak zamisljenom(1,-1,0):");
				int vr = 0;
				scanf("%d", &vr);
				if (vr ==0){
					printf(" Broj pokusaja je 2.");
				}
				else if (vr == 1) {
					*high = osamdeset - 1;
				}
				else if (vr == -1) {
					*low = osamdeset + 1;
				}
				else {
					printf("Pogrean izbor pokusaj ponovo");
					continue;
				}

			}
			else if (mid > osamdeset) {
				h = mid;
			}
			else {
				l = mid;
			}
			break;
		}
	}
}

void pretraga(float low, float high, int num,int no) {
	int l = low * num, h = high * num;
	interpolacija(&l, &h, 1, num,no);
	interpolacija(&l, &h, 2, num,no);
	int n = 3;

	while (l <= h) {
		int mid = l + (h - l) / 2;
		printf(" Da li je broj %.*f veci,manji,jednak zamisljenom broju:",no,(float) mid / num);
		int vr = 0;
		scanf("%d", &vr);
		if (vr == 0) {
			printf("Potreban broj pokusaja %d\n", n);
			break;
		}
		else if (vr == 1) {
			h = mid - 1;
		}

		else if (vr == -1) {
			l = mid + 1;
		}
		n++;
	}

	if (l > h) {
		printf("Broj nije u opsegu\n");
	}
	return;
}

void drugi() {
	int kra = 0;
	float low = 0, high = 0;
	int tacnost = 0;
	int num;

	while (!kra) {
		meni2();
		int izbo;
		printf("Unesite izbor:");
		scanf("%d",&izbo);
		switch (izbo) {
		case 1:
			printf("Unesite donju granicu, gornju granicu, opseg tacnosti(broj decimala):");
			scanf("%f %f %d", &low, &high, &tacnost);
			num = pow(10, tacnost);
			break;
		case 2:
			if (high == 0) {
				printf("Izaberi prvo opciju 1.\n");
				continue;
			}
			pretraga(low, high, num, tacnost);
			break;
		case 3:
			kra = 1;
			break;
		default:
			printf("Pogresan izbor");
			break;
		}
	}
}