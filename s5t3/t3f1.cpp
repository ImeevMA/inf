#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "t3.h"

typedef struct _ARGS {
    int n;
    int t;
    int tNum;
    double *iM;
    double *oM;
} ARGS;

int eChecker(const int eNumber, int n, void **arrays);
void * parallel (void * vArgs);

int main(int argc, char **argv) {
    int n;
    int m = 0;
    int i = 0;
    int t;
    void *arrays[4] = {NULL};
    if(argc == 3) {
        n = atoi(argv[2]);
        t = atoi(argv[1]);
        m = 0;
    } else {
        printf("Size of the matrix: ");
        if(scanf("%i", &n) < 1) {
            printf("Error: scanf\n");
            return -1;
        }
        printf("Number of threads: ");
        if(scanf("%i", &t) < 1) {
            printf("Error: scanf\n");
            return -1;
        }
        printf("Input from file? (yes = 1, no != 1):");
        if(scanf("%i", &m) < 1) {
            printf("Error: scanf\n");
            return -1;
        }
    }
    if(n < 1) {
        printf("n is bad!\n");
        return -1;
    }
    arrays[0] = malloc(n * n * (sizeof(double)));
    arrays[1] = malloc(n * n * (sizeof(double)));
    arrays[2] = malloc(t * sizeof(pthread_t));
    arrays[3] = malloc(t * sizeof(ARGS));
    if((arrays[0] == NULL) || (arrays[1] == NULL) || (arrays[2] == NULL) || (arrays[3] == NULL)) {
        eChecker(-3, 3, arrays);
        return -1;
    }
    double *iM = (double*)arrays[0];
    double *oM = (double*)arrays[1];
    pthread_t *threads = (pthread_t *)arrays[2];
    ARGS *args = (ARGS *)arrays[3];
    if(eChecker(setA(n, m, iM), 4, arrays) < 0) return -1;
    if(eChecker(setB(n, oM), 4, arrays) < 0) return -1;
    i = 0;
    while(i < t) {
        args[i].n = n;
        args[i].t = t;
        args[i].tNum = i;
        args[i].iM = iM;
        args[i].oM = oM;
        ++i;
    }
    long int time = get_time();
    i = 0;
    while(i < t) {
        pthread_create (threads + i, 0, parallel, args + i);
        ++i;
    }
    i = 0;
    while(i < t) {
        pthread_join(threads[i], 0);
        ++i;
    }
    time = get_time() - time;
    printf("time: %ld sec, %ld usec\n", time / 1000000, time % 1000000);
    if(eChecker(setA(n, m, iM), 4, arrays) < 0) return -1;
    if(eChecker(printM(n, 10, iM, "Matrix\n"), 4, arrays) < 0) return -1;
    if(eChecker(printM(n, 10, oM, "Matrix 2\n"), 4, arrays) < 0) return -1;
    printf("Delta: %g\n", getDelta(n, iM, oM));
    eChecker(-100, 4, arrays);
    return 0;
}

int eChecker(const int errNum, int n, void **arrays) {
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
    int i = 0;
    while(i < n) {
        if(arrays[i] != NULL) free(arrays[i]);
        ++i;
    }
    return -1;
}

void * parallel (void * vArgs) {
    ARGS *pargs = (ARGS *)vArgs;
    getB (pargs->n, pargs->t, pargs->tNum, pargs->iM, pargs->oM);
    return 0;
}
