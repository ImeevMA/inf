#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double myF(const int i, const int j) {
    return (double) 1 / (i + j + 1);
}

int setA(const int n, const int m, double *myM) {
    if(m == 1) {
        char tIn[] = "matrix.txt";
        FILE* fIn = fopen(tIn, "rt");
        if(fIn == NULL) return -4;
        int i = 0;
        while(i < n) {
            int j = 0;
            while(j < n) {
                if(fscanf(fIn, "%lf", &myM[j + n * i]) < 1) {
                    fclose(fIn);
                    return -2;
                }
                ++j;
            }
            ++i;
        }
	fclose(fIn);
    } else {
        int i = 0;
        while(i < n) {
            int j = 0;
            while(j < n) {
                myM[j + n * i] = myF(i, j);
                ++j;
            }
            ++i;
        }
    }
    return 0;
}

int printM(const int n, const int m, double *myM, const char *str) {
    if(printf("%s", str) < 1) return -1;
    int i = 0;
    int k = n;
    if(m < n) k = m;
    while(i < k) {
        int j = 0;
        while(j < k) {
            if(printf("%.2g\t", myM[j + n * i]) < 1) return -1;
            ++j;
        }
        if(printf("\n") < 1) return -1;
        ++i;
    }
    return 0;
}

int printV(const int n, const int m, double *myM, const char *str) {
    if(printf("%s", str) < 1) return -1;
    int i = 0;
    int k = n;
    if(m < n) k = m;
    while(i < k) {
        if(printf("%g\n", myM[i]) < 1) return -1;
        ++i;
    }
    printf("\n");
    return 0;
}
double nrmM(const int n, double *myM) {
    int i = 0;
    double s = 0.;
    while(i < n * n) {
        s += myM[i] * myM[i];
        ++i;
    }
    s = sqrt(s);
    s /= n*n;
    return s;
}

int nrmDiff(const int n, double *A, double *B) {
    double *tM = (double*)malloc(n * n * sizeof(double));
    if(tM == NULL) return -3;
    int i = 0;
    while(i < n) {
        int j = 0;
	while(j < n) {
	    tM[j + n * i] = 0.;
	    int k = 0;
	    while(k < n) {
	        tM[j + n * i] += A[k + n * i] * B[j + n * k];
		++k;
	    }
	    ++j;
	}
	++i;
    }
    i = 0;
    while(i < n) {
        tM[i + n * i] -= 1.;
	++i;
    }
    if(printf("||AB - I|| = %g\n", nrmM(n, tM)) < -1)  {
        free(tM);
        return -1;
    }
    free(tM);
    return 0;
}
