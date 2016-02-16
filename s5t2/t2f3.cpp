#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int printM(const int n, const int m, double *myM, const char *str);
int fAlmost(const int n, const int k, double *M);

int fAbout(const int n, double *M) {
    int i = 1;
    double epsilon = 1e-30;
	while (i < n - 1) {
        int j = i + 1;
		while (j < n) {
            double r = sqrt(M[i * n + i - 1] * M[i * n + i - 1] + M[j * n + i - 1] * M[j * n + i - 1]);
			if ((fabs(M[j * n + i - 1]) > epsilon) && (r > epsilon)) {
                double cosA = M[i * n + i - 1] / r;
                double sinA = -M[j * n + i - 1] / r;
                M[i * n + i - 1] = r;
                M[(i - 1) * n + i] = r;
                M[j * n + i - 1] = 0.;
                M[(i - 1) * n + j] = 0.;
                int k = i + 1;
                while (k < n)
                {
                    if (k != j) {
                        double tmp = M[i * n + k];
                        M[i * n + k] = M[i * n + k] * cosA - M[j * n + k] * sinA;
                        M[j * n + k] = tmp * sinA + M[j * n + k] * cosA;
                        M[k * n + i] = M[i * n + k];
                        M[k * n + j] = M[j * n + k];
                    }
                    ++k;
                }
                double aii = M[i * n + i] * cosA - M[j * n + i] * sinA;
                double aji = M[i * n + i] * sinA + M[j * n + i] * cosA;
                double aij = M[i * n + j] * cosA - M[j * n + j] * sinA;
                double ajj = M[i * n + j] * sinA + M[j * n + j] * cosA;
                M[i * n + i] = aii * cosA - aij * sinA;
                M[j * n + i] = aii * sinA + aij * cosA;
                M[i * n + j] = M[j * n + i];
                M[j * n + j] = aji * sinA + ajj * cosA;
            }
            ++j;
		}
        ++i;
	}
    i = 0;
    while(i < n - 1) {
        M[i] = M[i + i * n];
        M[i + n] = M[i + (1 + i) * n];
        ++i;
    }
    M[n - 1] = M[n * n - 1];
    M[2 * n - 1] = 0.;
    fAlmost(n, n, M);
    return 0;
}

int fAlmost(const int n, const int k, double *M) {
    double *a = M;
    double *a2 = M + n;
    double *l = M + 2 * n;
    double *l2 = M + 3 * n;
    int i = 1;
    l[0] = sqrt(a[0]);
    l2[0] = a2[0]/l[0];
    while(i < k) {
        l[i] = sqrt(a[i] - l2[i - 1] * l2[i - 1]);
        l2[i] = a2[i]/a[i];
        ++i;
    }
    i = 0;
    while(i < k - 1) {
        a[i] = l[i] * l[i] + l2[i] * l2[i];
        a2[i] = l[i] * l2[i];
        ++i;
    }
    return 0;
}
    
/*
    i = n;
    while(i > 2) {
        printM(n, 10, M, "3-Diagonal:\n");
        printf("%i\t%g\n", i, fabs(M[(i - 1) * n + i - 2]));
        while(fabs(M[(i - 1) * n + i - 2]) > epsilon) {
	    printf("Ok?\n");
            fAlmost(n, i, M);
	}
        --i;
    }
    return 0;
}

int fAlmost(const int n, const int k, double *M) {
    double a11 = M[0];
    double a21;
    double l11 = sqrt(a11);
    double l21 = 0.;
    int i = 0;
printf("NNNNNNNN:%i\n", k);
    while(i < (k - 1)) {
        a21 = M[i + (i + 1) * n];
//	printf("++++: %g\t%g\t%g\t%i\t%i\n", a21, l21, l11, i, k);
        l21 = a21/l11;
//	printf("-+++: %g\t%g\t%g\t%i\t%i\n", a21, l21, l11, i, k);
        M[i + i * n] = l11 * l11 + l21 * l21;
        ++i;
        a11 = M[i + i * n];
//	printf("--++: %g\t%g\t%g\t%i\t%i\n", a21, l21, a11 - l21 * l21, i, k);
        l11 = sqrt(fabs(a11 - l21 * l21));
//	printf("---+: %g\t%g\t%g\t%i\t%i\n", a21, l21, l11, i, k);
        M[i - 1 + i * n] = l21 * l11;
        M[i + (i - 1) * n] = M[i - 1 + i * n];
    }
//    printf("----%.1g\t%.1g\t%.1g\t%i\t%i\n", M[k - 1 + k * n], a11, l11, i, k);
    M[k + k * n - 1] = l11 * l11;
//    printf("%g\n", M[k * k - 1]);
    return 0;
}*/
