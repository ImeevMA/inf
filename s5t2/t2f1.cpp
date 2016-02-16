#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

int eChecker(const int eNumber);
int setA(const int n, const int m, double *myM);
int fAbout(const int n, double *M);
int printM(const int n, const int m, double *myM, const char *str);
int printV(const int n, const int m, double *myM, const char *str);
int nrmDiff(const int n, double *A, double *B);
long int get_time();

int main() {
    int n, i;
    double trace = 0.;
    double norm = 0.;
    if(printf("Size of the matrix: ") < 0) {
        printf("Error: printf\n");
	return -1;
    }
    if(scanf("%i", &n) < 1) {
        printf("Error: scanf\n");
	    return -1;
    }
    if(printf("Input from file? (yes = 1, no != 1):") < 1) {
        printf("Error: printf");
    	return -1;
    }
    if(scanf("%i", &i) < 1) {
        printf("Error: scanf\n");
	    return -1;
    }
    double *iM = (double*)malloc(n * n * (sizeof(double)));
    if(iM == NULL) {
        printf("Error: malloc\n");
	    return -1;
    }
    if(eChecker(setA(n, i, iM)) < 0) {
        free(iM);
	    return -1;
    }
    i = 0;
    while(i < n) {
        trace += iM[i + n * i];
        int j = 0;
        while(j < n) {
            norm += iM[j + n * i] * iM[j + n * i];
            ++j;
        }
        ++i;
    }
    if(eChecker(printM(n, 8, iM, "Matrix\n") < 0)) {
        free(iM);
	    return -1;
    }
    //---
    long int sec, usec;
    struct timeval buf;
    gettimeofday(&buf, 0);
    sec = buf.tv_sec;
    usec = buf.tv_usec;
    if(eChecker(fAbout(n, iM)) < 0) {
        free(iM);
	    return -1;
    }
    gettimeofday(&buf, 0);
    sec = buf.tv_sec - sec;
    usec = buf.tv_usec - usec;
	printf("Time = %li sec %li usec.\n", sec, usec);
    //---
    i = 0;
    while(i < n) {
        trace -= iM[i];
        norm -= iM[i] * iM[i] + 2 * iM[i + n] * iM[i + n];
        ++i;
    }
    printf("Trace: %g\nDelta of norm: %g\n", trace, norm);
    if(eChecker(printV(n, 10, iM, "\nMatrix 1\n") < 0)) {
        free(iM);
	    return -1;
    }
    free(iM);
    return 0;
}

int eChecker(const int errNum) {
    if(errNum == 0)
        return 0;
    if(errNum == -1)
        printf("Error: printf\n");
    if(errNum == -2)
        printf("Error: scanf\n");
    if(errNum == -3)
        printf("Error: malloc\n");
    if(errNum == -4)
        printf("Error: fopen\n");
    if(errNum == -5)
        printf("Error: det of matrix is 0\n");
    return -1;
}
