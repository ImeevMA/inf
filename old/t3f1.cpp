#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "t3.h"

int eChecker(const int eNumber);

int main(int argc, char **argv) {
    int n, i;
    if(argc == 2) {
        n = atoi(argv[1]);
        i = 0;
    } else {
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

    double *oM = (double*)malloc(n * n * (sizeof(double)));
    if(oM == NULL) {
        printf("Error: malloc\n");
    	free(iM);
    	return -1;
    }
    if(eChecker(setB(n, oM)) < 0) {
        free(iM);
        free(oM);
    	return -1;
    }

    long int time;
    time = getTime();
    if(eChecker(getB(n, iM, oM)) < 0) {
        free(iM);
        free(oM);
	    return -1;
    }
    time = getTime() - time;
    if(printf("Time: %li sec %li usec\n", time / 1000000, time % 1000000) < 0) {
        printf("Error: printf");
        return -1;
    }

    if(eChecker(setA(n, i, iM)) < 0) {
        free(iM);
        free(oM);
	return -1;
    }
    if(eChecker(printM(n, 10, iM, "Matrix\n") < 0)) {
        free(iM);
        free(oM);
	return -1;
    }
    if(eChecker(printM(n, 10, oM, "Matrix 2\n") < 0)) {
        free(iM);
        free(oM);
	return -1;
    }

/*    if(eChecker(getDelta(n, iM, oM)) < 0) {
        free(iM);
        free(oM);
        return -1;
    }*/
    if(printf("Delta: %g\n", getDelta(n, iM, oM)) < 0) {
        printf("Error: printf");
        return -1;
    }

    free(iM);
    free(oM);
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
